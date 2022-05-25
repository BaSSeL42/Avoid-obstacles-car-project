/**********new_timer.c***********/

#include "timers_grp_25.h"
#include "DIO.h"
#include "MCU_ATMEGA32.h"
#include "bit_math.h"
#include <avr/interrupt.h>

#define clk_cpu		16
#define ICR			6
#define ICES1		6
#define CS10		0

#define ICR			6

#define trig		0

timer_cbk_ptr timer_cbk = NULL_POINTER ;



Uint8    u8_init_value = 0;
Uint32   u32_number_of_ovfs = 0;


void Timer0_Init(void)
{
	/*Normal mode. Disable OCR0 PIN toggling and no clock source*/
	TCCR0 |= 0x00;
	
	/*Enable Timer 0 Normal Mode Interrupt*/
	TIMSK |= 0x01;
	
	/*Enable Global Interrupt*/
	SREG |= 0x80;
	
}

void Timer2_Init(void)
{
	/*Normal mode. Disable OCR0 PIN toggling and no clock source*/
	TCCR2 |= 0x00;
	
	/*Enable Timer 0 Normal Mode Interrupt*/
	TIMSK |= 0x40;
	
	/*Enable Global Interrupt*/
	SREG |= 0x80;
	
}

void Timer0_Start(void)
{
	/*Enable 1024 Prescaler on the MC clock source*/
	TCCR0 |= 0x05;
}

void Timer0_Stop(void)
{
	/*Shut down the clock on the timer clock source*/
	Clear_Bit(TCCR0,0);
	Clear_Bit(TCCR0,1);
	Clear_Bit(TCCR0,2);
}



void Timer0_SetDelay(Uint32 u32_delay_ms)
{
	
	Uint8 u8_tick_time = (1024 / clk_cpu) ;
	
	Uint32 u32_total_ticks = (u32_delay_ms * 1000) / u8_tick_time ;
	
	u32_number_of_ovfs = u32_total_ticks / 256 ;
	
	u8_init_value  =   256 - (u32_total_ticks % 256) ;
	
	TCNT0 = u8_init_value ;
	
	/*Incrementing the total number of overflows by one. as the u32_isr_cnt variable in the isr is incremented by 1 in the first time*/
	u32_number_of_ovfs++;
	
}



void Timer1_Init(void)
{
	/*Enable CTC Mode on timer 1*/
	TCCR1B |= 0X08;
	/*Enable Output compare match A interrupt*/
	TIMSK  |= 0X10;
	/*Enable the global interrupt*/
	SREG   |= 0X80;
}

void Timer1_Start(void)
{
	/*Start prescalar on timer 1*/
	TCCR1B |= 0X05 ;
}

void Timer1_Stop(void)
{
	/*Stop the timer*/
	Clear_Bit(TCCR1B,0);
	Clear_Bit(TCCR1B,1);
	Clear_Bit(TCCR1B,2);
}


void Timer1_SetDelay(Uint32 u32_delay_ms)
{
	
	if(u32_delay_ms <= 4000)
	{
		Uint8 u8_tick_time = 1024 / clk_cpu;
		
		Uint32 u32_number_of_ticks = (u32_delay_ms * 1000) / u8_tick_time ;
		
		OCR1A = u32_number_of_ticks - 1;
	}
	
}

void TIMER1_ICR_init(void)
{
	cli(); // clear all global interrupt
	
	Clear_Bit(DDRD, ICR); // set bin 6 (input capture) on portD as input 
	//DDRD = 0xFF;
	
	TCNT1 = 0;
	
	
	
	TCCR1A |= 0x00;  // set wave generation mode as normal mode (ovf)
	
	/*enable ICR &set to rising edge and set prescalar to 1*/
	Set_Bit(TCCR1B, ICES1);
	Set_Bit(TCCR1B, CS10);
	
	/*Enable ovf and icr interrupt*/
	Set_Bit(TIMSK, TOIE1);
	Set_Bit(TIMSK, TICIE1);
	
	sei(); // set global interrupt
}

void icr_init(void)
{
		DDRC |= 0xFF;		
		Set_Bit(DDRA, trig); /* Make trigger pin as output */
		
		//PORTD = 0xFF;		/* Turn on Pull-up */
		
		sei();			/* Enable global interrupt */	
		Set_Bit(TIMSK, TOIE1); /* Enable Timer1 overflow interrupts */
		TCCR1A = 0;		/* Set all bit to zero Normal operation */
	
}

void Set_CallBack(timer_cbk_ptr ptr_func_timer_cbk)
{
	
	timer_cbk = ptr_func_timer_cbk ;
	
}



ISR(TIMER0_OVF_vect)
{
	static Uint32 u32_isr_cnt = 0;
	
	u32_isr_cnt++;
	
	if(u32_isr_cnt == u32_number_of_ovfs)
	{
		TCNT0 = u8_init_value;
		
		u32_isr_cnt = 0;
		
		timer_cbk();
	}
}



ISR(TIMER1_COMPA_vect)
{
	static Uint32 u32_isr_cnt = 0;
	
	u32_isr_cnt++;
	
	if(u32_isr_cnt == 1)
	{
		u32_isr_cnt = 0;
		
		timer_cbk();
	}
}


void PWM0_Init(ENU_PWM pwm)
{
	if (pwm != INVALID)
	{
		/*Setting the PIN to high*/
		DDRB |= 0x08;
		
		switch (pwm)
		{
			case FAST_PWM:
			{
				/*Fast PWM mode with prescalar 8*/
				TCCR0 |= 0x68;
				break;
			}
			case PHASE_CORRECT:
			{
				/*phase correct mode with prescalar 8*/
				TCCR0 |= 0x28;
				break;
			}
			default:
			{
				break;
			}
		}
	}
	
	else
	{
		
	}

	
}


void PWM0_Generate(Uint16 u16_duty_cycle)
{
	/*Equation from datasheet. Subtracting 1 to handle the corner case of 100% DC*/
	OCR0 = ((u16_duty_cycle * 256 ) /100 ) - 1;
}



void PWM0_Start(enu_prescalar prescal)
{
	/*Enable the clock from the datasheet*/
	switch (prescal)
	{
		case NO_PRESCAL:
		{
			TCCR0 |= 0x01;
			break;
		}
		case PRESCALE_8:
		{
			TCCR0 |= 0x02;
			break;
		}
		case PRESCALE_64:
		{
			TCCR0 |= 0x03;
			break;
		}
		case PRESCALE_256:
		{
			TCCR0 |= 0x04;
			break;
		}
		case PRESCALE_1024:
		{
			TCCR0 |= 0x05;
			break;
		}
		case EXT_CLK_FALLING_EDGE:
		{
			TCCR0 |= 0x06;
			break;
		}
		case EXT_CLK_RISING_EDGE:
		{
			TCCR0 |= 0x07;
			break;
		}
		default :
		break;
	}
}


void PWM2_Init(ENU_PWM pwm)
{
	if (pwm != INVALID)
	{
		/*Setting the PIN to high*/
		//DDRD |= 0x08;
		Set_Bit(DDRD,7);
		
		switch (pwm)
		{
			case FAST_PWM:
			{
				/*Fast PWM mode with prescalar 8*/
				TCCR2 |= 0x68;
				break;
			}
			case PHASE_CORRECT:
			{
				/*phase correct mode with prescalar 8*/
				TCCR2 |= 0x28;
				break;
			}
			default:
			{
				break;
			}
		}
	}
	
	else
	{
		
	}

	
}


void PWM2_Generate(Uint16 u16_duty_cycle)
{
	/*Equation from datasheet. Subtracting 1 to handle the corner case of 100% DC*/
	OCR2 = ((u16_duty_cycle * 256 ) /100 ) - 1;
}



void PWM2_Start(enu_prescalar prescal)
{
	/*Enable the clock from the datasheet*/
	switch (prescal)
	{
		case NO_PRESCAL:
		{
			TCCR2 |= 0x01;
			break;
		}
		case PRESCALE_8:
		{
			TCCR2 |= 0x02;
			break;
		}
		case PRESCALE_64:
		{
			TCCR2 |= 0x03;
			break;
		}
		case PRESCALE_256:
		{
			TCCR2 |= 0x04;
			break;
		}
		case PRESCALE_1024:
		{
			TCCR2 |= 0x05;
			break;
		}
		case EXT_CLK_FALLING_EDGE:
		{
			TCCR2 |= 0x06;
			break;
		}
		case EXT_CLK_RISING_EDGE:
		{
			TCCR2 |= 0x07;
			break;
		}
		default :
		break;
	}
}

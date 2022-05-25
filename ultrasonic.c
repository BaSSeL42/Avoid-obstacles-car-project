/*
* ultrasonic.c
*
* Created: 5/20/2022 12:07:01 AM
*  Author: yasser
*/

#define F_CPU		16000000UL
#include "ultrasonic.h"
#include <util//delay.h>
#include <avr/interrupt.h>
#include "timers_grp_25.h"

#define trig			0  //trigger bin for for ultrasonic

#define	ICES1		6
#define	ICF1		5
#define	TOV1		2
#define	TOIE1		2
#define	TICIE1		5

#define trig		0

/*****  For input capture and ovf interrupt (ISR)   *****/
volatile Uint8 ovf , ov;
volatile Uint16 cap1, cap2;
volatile Uint8 mask = 0;
/*******************************************/

/* Some variables */
Uint32 t_ticks;
f64 distance;   // double distance
f64 dist;   // double distance
/*********************/

#define  Trigger_pin	0	/* Trigger pin */
volatile int TimerOverflow = 0;
long count;

volatile Uint8 flag = 1; // for external interrupt


/********************************  CODE ***************************/

void ultrasonic_trig(void){
	DDRA = (1<<Trigger_pin);		/* Make trigger pin as output */
	/* Give 10us trigger pulse on trig. pin to HC-SR04 */
	PORTA |= (1 << Trigger_pin);
	_delay_us(10);
	PORTA &= (~(1 << Trigger_pin));
}



f64 UltrasonicRead(void)
{
	Set_Bit(DDRA,trig);
	
	
	/* send high to trigger bin within 10 us turn it off or send one pulse at a time */
	Clear_Bit(PORTA, trig);
	_delay_us(2);
	
	Set_Bit(PORTA, trig);
	_delay_us(10);
	Clear_Bit(PORTA, trig);
	/***************************************************/
	
	if (mask == 2)
	{
		mask = 0;
		t_ticks = (Uint32) cap2 + (Uint32) (65536*ovf) - (Uint32) cap1;
		
		// sound velocity = 34300 cm/sec
		// tick time = 1/(F_CPU) as 1 is prescalar -> tick_time = 62.5 ns -> 62.5e-9 sec
		// total_time = t_ticks * 62.5e-9 sec
		// distance = (sound_velocity * total_time)/2 -> (343000 * total_time)/2 -> (17150 * t_ticks * 62.5e-9) -> (t_ticks / 932.95)
		distance = (f64) t_ticks / 932.95;
		
		//strcat(string, "cm    ");
		//dtostrf(distance,3,2, string); //  to print distance on LCD
		
		ovf=0; ov=0;
		
		Set_Bit(TCCR1B, ICES1); // return to captue from rising edge
		
		/* set input capture flag and ovf flag to 1 to disable it */
		Set_Bit(TIFR, ICF1);
		Set_Bit(TIFR, TOV1);
		/*************************/
		
		/* enable input capture and overflow interrupt */
		Set_Bit(TIMSK, TOIE1);
		Set_Bit(TIMSK, TICIE1);
		/**************************/
		
	}
	return distance;
	
}



/*********** external interrupt **********************************/

void extInt_init(void)
{
	
	Clear_Bit(DDRD, 2);  // set PD2 as input for external interrupt
	//DDRC |= 0xFF;
	Set_Bit(DDRA, trig); /* Make trigger pin as output */
	
	Set_Bit(DDRC, 7);
	
	/*  set external interrupt sense rising edge */
	Set_Bit(MCUCR, ISC00);
	Set_Bit(MCUCR, ISC01);
	
	//PORTD = 0xFF;		/* Turn on Pull-up */
	
	sei();			/* Enable global interrupt */
	Set_Bit(TIMSK, TOIE1); /* Enable Timer1 overflow interrupts */
	Set_Bit(GICR, INT0); // enable interrupt 0
	TCCR1A = 0;		/* Set all bit to zero Normal operation */
	
	Set_Bit(TCCR1B, CS11); // set prescalar to 8
	ultrasonic_trig();
	
	
}

/************************************************************************************************************/



f64 ultrasonic_read(void)
{
	/* Give 10us trigger pulse on trig. pin to HC-SR04 */
	PORTA |= (1 << Trigger_pin);
	_delay_us(10);
	PORTA &= (~(1 << Trigger_pin));
	
	TCNT1 = 0;	/* Clear Timer counter */
	TCCR1B = 0x41;	/* Capture on rising edge, No prescaler*/
	TIFR = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
	TIFR = 1<<TOV1;	/* Clear Timer Overflow flag */

	/*Calculate width of Echo by Input Capture (ICP) */
	
	while ((TIFR & (1 << ICF1)) == 0);/* Wait for rising edge */
	TCNT1 = 0;	/* Clear Timer counter */
	TCCR1B = 0x01;	/* Capture on falling edge, No prescaler */
	TIFR = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
	TIFR = 1<<TOV1;	/* Clear Timer Overflow flag */
	TimerOverflow = 0;/* Clear Timer overflow count */

	while ((TIFR & (1 << ICF1)) == 0);/* Wait for falling edge */
	count = ICR1 + (65535 * TimerOverflow);	/* Take count */
	/* 8MHz Timer freq, sound speed =343 m/s */
	dist = (double)count / 466.47;
	return dist;
}




/*************************************  Some ISR ***********************************************************/
ISR(TIMER1_OVF_vect)
{
	ov++;
}


		
		
ISR(INT0_vect)
{
	if (flag == 1)
	{
		Clear_Bit(MCUCR, ISC00);
		Set_Bit(MCUCR, ISC01);
		
		TCNT1 = 0;
		flag = 0;
	}
	else
	{
		Uint32 count;
		f64 dist;
		
		count = TCNT1 + (65535 * ov);
		
		dist = (f64) count /  466.47;
		
		if (dist < 15.0)
		{
			Set_Bit(PORTC, 7);
		}
		else
		{
			Clear_Bit(PORTC, 7);
		}
		
		ultrasonic_trig();
		
		flag = 1;
	}
}

//cap1 = ICR1L | (ICR1H << 8);
 ISR(TIMER1_CAPT_vect)
 {
 	if (mask == 0)
 	{
 		cap1 = ICR1;
 		Clear_Bit(TCCR1B, ICES1);
 		ov = 0;
 	}
 	else if (mask == 1)
 	{
 		
 		cap2 = ICR1;
 		ovf = ov;

 		/*disable any interrupt to prevent any nested interrupt*/
 		Clear_Bit(TIMSK, TOIE1);
 		Clear_Bit(TIMSK, TICIE1);
 		/****************************/

 	}
 	mask++;
 }
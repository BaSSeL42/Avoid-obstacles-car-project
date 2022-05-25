/**********timers_grp_25.h***********/

#ifndef __TIMER_H__
#define __TIMER_H__

#include "std.h"
#include "MC_Selector.h"
#include "Bit_Math.h"
/*************************** Types *****************************************/
typedef void (*timer_cbk_ptr)(void);

typedef enum
{
	NO_CLK = 0,
	NO_PRESCAL,
	PRESCALE_8,
	PRESCALE_64,
	PRESCALE_256,
	PRESCALE_1024,
	EXT_CLK_FALLING_EDGE,
	EXT_CLK_RISING_EDGE,
	
}enu_prescalar;

typedef enum
{
	FAST_PWM=0,
	PHASE_CORRECT,
	INVALID,
	}ENU_PWM;
/**************************** Timer 0 Normal Mode **************************************/
void Timer0_Init(void);

void Timer0_Start(void);

void Timer0_Stop(void);

void Timer0_SetDelay(Uint32 u32_delay_ms);

/**************************** Timer 0 CTC Mode **************************************/
void PWM0_Init(ENU_PWM pwm);

void PWM0_Generate(Uint16 u16_duty_cycle);

void PWM0_Start(enu_prescalar);

void Set_CallBack(timer_cbk_ptr ptr_func_timer_cbk);

/**************************** Timer 1 **************************************/
void Timer1_Init(void);

void Timer1_Start(void);

void Timer1_Stop(void);

void Timer1_SetDelay(Uint32 u32_delay_ms);

void TIMER1_ICR_init(void);

void icr_init(void);

/************ Timer2********************/
void PWM2_Init(ENU_PWM pwm);

void PWM2_Generate(Uint16 u16_duty_cycle);

void PWM2_Start(enu_prescalar prescal);

void Timer2_Init(void);

#endif		/*__TIMER_H__*/


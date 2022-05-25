/*
 * servo.c
 *
 * Created: 5/19/2022 11:18:50 PM
 *  Author: yasser
 */ 
#include "servo.h"

#include "MC_Selector.h"
#include "Bit_Math.h"


#define	COM1A1		7	
#define WGM10		0
#define	WGM11		1
#define	WGM12		3
#define	WGM13		4
#define	CS10		0
#define	CS11		1
#define CS12		2

Uint16 icr;
void servoMotorInit(void)
{
	
	Set_Bit(DDRD, 5); // set OC1A (bin 5) as output

	Set_Bit(TCCR1A,	COM1A1); // clear OC1A on compare match
	/*  SET fast pwm with ICR1 as top  */
	Clear_Bit(TCCR1A, WGM10);
	Set_Bit(TCCR1A, WGM11);
	Set_Bit(TCCR1B, WGM12);
	Set_Bit(TCCR1B, WGM13);
	/**********************************/
	Clear_Bit(TCCR1B, CS10); // SET PRESCALAR 8
	Set_Bit(TCCR1B, CS11);
	Clear_Bit(TCCR1B, CS12);
	
	// law F_pwm = f_cpu / ( N*(1+TOP) )
	// servo motor needs 50 HZ according to law ---> TOP = 39999
	// store 39999 inside ICR1 as top
	icr = 39999;
	
	ICR1H = (icr>>8);
	ICR1L = icr;
	
	TCNT1 = 0;
}

void servoMotorRotate(Uint32 value)
{
	//OCR1A = ((icr * value)/100)-1; // 3000+1 =ICR1*value/  100      // 0 (5) 90 (7.5)  180 (10)
	OCR1A = value;
}

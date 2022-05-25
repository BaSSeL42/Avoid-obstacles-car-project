/*
* dcMotor.c
*
* Created: 5/21/2022 4:35:13 PM
*  Author: yasser
*/

#include "dcMotor.h"

#include "std.h"
#include "MC_Selector.h"
#include "Bit_Math.h"
/* define H-bridge bins for motor1 & motor2 */
#define IN1		3
#define IN2		4
#define IN3		5
#define IN4		6
/***************************************/

#define EN1		5
#define EN2		6



void motorInit(void)
{
	/*  Set these H-bridge bins as output  */
	Set_Bit(DDRC, IN4);
	Set_Bit(DDRC, IN3);
	Set_Bit(DDRC, IN2);
	Set_Bit(DDRC, IN1);
	/************************************/
	
	/**   set enable bins on H-bridge to Hight   **/
	Set_Bit(DDRB, EN1);
	Set_Bit(DDRB, EN2);
	
	Set_Bit(PORTB, EN1);
	Set_Bit(PORTB, EN2);
	/*************************/
}

void motorStop (void)
{
	Clear_Bit   (PORTC, IN2);
	Clear_Bit (PORTC, IN1);
	Clear_Bit   (PORTC, IN4);
	Clear_Bit (PORTC, IN3);
}

void motorStart(void)
{
	Set_Bit   (PORTC, IN2);
	Clear_Bit (PORTC, IN1);
	Set_Bit   (PORTC, IN4);
	Clear_Bit (PORTC, IN3);
}

void turnRight(void)
{
	Clear_Bit   (PORTC, IN2);
	Clear_Bit (PORTC, IN1);
	Set_Bit   (PORTC, IN4);
	Clear_Bit (PORTC, IN3);
}

void turnLeft(void)
{
	Set_Bit   (PORTC, IN2);
	Clear_Bit (PORTC, IN1);
	Clear_Bit   (PORTC, IN4);
	Clear_Bit (PORTC, IN3);
}


void backward(void)
{
	Clear_Bit   (PORTC, IN2);
	Set_Bit (PORTC, IN1);
	Clear_Bit   (PORTC, IN4);
	Set_Bit (PORTC, IN3);
}
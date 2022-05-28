/*
* AMIT-PROJECT.c
*
* Created: 5/19/2022 11:06:35 PM
* Author : yasser
*/
#define F_CPU		16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

#include "servo.h"
#include "ultrasonic.h"
#include "LCD.h"

//#include "timers_grp_25.h"
#include "dcMotor.h"




int main(void)
{
	LCD_INIT();
	//TIMER1_ICR_init();
	servoMotorInit();
	extInt_init();
	motorInit();
	//Timer0_Init();
	//Timer0_Start();
	
	f64 distR, distL;
	
	Set_Bit(DDRC, 7);
	
	while (1)
	{


		servoMotorRotate(3000);   // set servo at 0 degree
		
		motorStart();
		
		if (ultraRead() < 50.0)
		{
			motorStop();
			Set_Bit(PORTC, 7);
			
			servoMotorRotate(2000);
			distL = ultraRead();
			_delay_ms(250);
			servoMotorRotate(5250);
			distR = ultraRead();
			_delay_ms(250);
			
			if (distL > distR)
			{
				LCD_Clear();
				LCD_GoTo(1,1);
				LCD_WriteSTRING("Turn Left");
				LCD_GoTo(2,1);
				LCD_WriteINTEGER((Uint32) distL);
				backward();
				_delay_ms(1000);
				turnLeft();
				//Timer0_SetDelay(500);
				//Set_CallBack(motorStop);
			}
			else
			{
				LCD_Clear();
				LCD_GoTo(1,1);
				LCD_WriteSTRING("Turn Right");
				LCD_GoTo(2,1);
				LCD_WriteINTEGER((Uint32) distR);
				
				backward();
				_delay_ms(1000);
				turnRight();
				//Timer0_SetDelay(500);
				//Set_CallBack(motorStop);
			}
		}
	}
}


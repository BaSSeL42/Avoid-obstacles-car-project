/*
* AMIT-PROJECT.c
*
* Created: 5/19/2022 11:06:35 PM
* Author : yasser
*/
#define F_CPU		16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "servo.h"
#include "ultrasonic.h"

#include "timers_grp_25.h"
#include "dcMotor.h"




int main(void)
{
	
	TIMER1_ICR_init();
	servoMotorInit();
	motorInit();
	//Timer0_Init();
	//Timer0_Start();
	
	Set_Bit(DDRC, 7);

	f64 distR, distL;
	
	while (1)
	{

		servoMotorRotate(3000);   // set servo at 0 degree
		motorStart();
		
		if (UltrasonicRead() < 50.0)
		{
			motorStop();
			
			
			servoMotorRotate(2000);
			distL = ultrasonic_read();
			_delay_ms(1000);
			servoMotorRotate(5250);
			distR = ultrasonic_read();
			_delay_ms(1000);
			
			if (distL > distR)
			{
				backward();
				_delay_ms(1000);
				turnLeft();
				//Timer0_SetDelay(500);
				//Set_CallBack(motorStop);
			}
			else
			{
				backward();
				_delay_ms(1000);
				turnRight();
				//Timer0_SetDelay(500);
				//Set_CallBack(motorStop);
			}
		}

	}
}


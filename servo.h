/*
 * servo.h
 *
 * Created: 5/19/2022 11:19:04 PM
 *  Author: yasser
 */ 


#ifndef SERVO_H_
#define SERVO_H_

//#include "std.h"
//#include "MC_Selector.h"
//#include "Bit_Math.h"

//#include "timers_grp_25.h"

#include "std.h"


void servoMotorInit(void);

void servoMotorRotate(Uint32 value);




#endif /* SERVO_H_ */
/*
 * ultrasonic.h
 *
 * Created: 5/20/2022 12:06:45 AM
 *  Author: yasser
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "timers_grp_25.h"

void ultrasonic_trig(void);

f64 UltrasonicRead(void);

f64 ultrasonic_read(void);

void extInt_init(void);




#endif /* ULTRASONIC_H_ */
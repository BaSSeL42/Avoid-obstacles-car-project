/*
 * b_USART.h
 *
 * Created: 5/1/2022 12:00:24 PM
 *  Author: biso
 */ 


#ifndef B_USART_H_
#define B_USART_H_

#include "Bit_Math.h"
#include "MCU_ATMEGA32.h"
#include "DIO.h"
#include "std.h"

void USART_Init(Uint32 BAUD);
void USART_Transmit(Uint8 tx_data);
void USART_TransmitString(Uint8* string);

Uint8 USART_Recieve(void);




#endif /* B_USART_H_ */
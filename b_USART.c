/*
* b_USART.c
*
* Created: 5/1/2022 11:59:57 AM
*  Author: biso
*/


#include "b_USART.h"

#define FOSC	16000000

/******** UCSRA register ************/
#define UDRE		5
#define RXC			7				
/************************************************************************/

/******** UCSRB register ************/
#define UCSZ2		2
#define TXEN		3
#define RXEN		4
/************************************************************************/

/******** UCSRC register ************/
#define UCSZ0		1
#define UCSZ1		2
#define USBS		3
#define UMSEL		6
/************************************************************************/

void USART_Init(Uint32 BAUD)
{
	DIO_SetPinDir(DIO_PORTD, DIO_PIN_0, DIO_PIN_IN);
	DIO_SetPinDir(DIO_PORTD, DIO_PIN_1, DIO_PIN_OUT);
	
	/* set baud rate  */
	Uint16 ubrr = (FOSC/(16*BAUD))-1;
	
	UBRRH = (unsigned char) (ubrr >> 8);
	UBRRL = (unsigned char) ubrr;
	
	/* enable tx and rx */
	Set_Bit(UCSRB, TXEN);
	Set_Bit(UCSRB, RXEN);
	
	/* 8 data bit,  1 stop bit, asynch. mode*/
	
	Set_Bit(UCSRC, UCSZ0);
	Set_Bit(UCSRC, UCSZ1);
	Clear_Bit(UCSRB, UCSZ2);
	
	Clear_Bit(UCSRC, USBS);
	
	Clear_Bit(UCSRC, UMSEL);

}



void USART_Transmit(Uint8 tx_data)
{
	while( (Get_Bit(UCSRA, UDRE)) == 0 );
	UDR = tx_data;
}


void USART_TransmitString(Uint8* string)
{
	Uint32 i =0;
	while(string[i] != '\0')
	{
		USART_Transmit(string[i++]);
	}
}



Uint8 USART_Recieve(void)
{
	while( Get_Bit(UCSRA, RXC) == 0);
	
	return UDR;
}
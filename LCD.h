/*
 * LCD.h
 *
 *  Created on: Feb 1, 2019
 *      Author: Mina Raouf
 */
#ifndef LCD_H_
#define LCD_H_

#include "LCD_CFG.h"

/*LCD Commands*/

#define Clear_Display_Screen                 0x01
#define Return_Home                          0x02
#define Shift_Cursor_Left_Per_Read_Write     0x04
#define Shift_cursor_Right_Per_Read_Write    0x06
#define Shift_Display_Right_Per_Read_Write   0x05
#define Shift_Display_Left_Per_Read_Write    0x07
#define Display_Cursor_Blink_ALL_OFF         0x08
#define Display_OFF_Cursor_ON                0x0A
#define Display_ON_Cursor_OFF                0x0C
#define Display_ON_Cursor_Blink              0x0E
#define Shift_Cursor_Position_Left           0x10
#define Shift_Cursor_Position_Right          0x14
#define Shift_Entire_Display_Left            0x18
#define Shift_Entire_Display_Right           0x1C
#define Cursor_Begin_1st_Line                0x80
#define Cursor_Begin_2st_Line                0xC0
#define LCD_4_Bit_Mode                       0x28
#define LCD_8_Bit_Mode                       0x38

void LCD_INIT(void);
void LCD_WriteCMD(Uint8 cmd);
void LCD_WriteCHAR(Uint8 chr);
void LCD_WriteSTRING(Uint8 * str);
void LCD_WriteINTEGER(Uint32 integer);
void LCD_WriteDECIMAL(f32 decimal);
void LCD_BurnCustomCHAR(Uint8 loc, Uint8 *arr);
void LCD_ModifyDDRAM_CHAR(Uint8 loc, Uint8 *arr);
void LCD_GoTo(Uint8 row, Uint8 col);
void LCD_Clear(void);



#endif /* LCD_H_ */
/*
 * LCD_interface.h
 *
 *  Created on: Aug 17, 2024
 *      Author: Mariam
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#include "LCD_config.h" // to khow the mode


/***************************************************************************************/
/********************************** Macros *********************************************/
/***************************************************************************************/


/********/
#define    LCD_8_BIT_MODE    1
#define    LCD_4_BIT_MODE    2
/********/
/*List of instruction codes*/

#define Clear_Display         0x01               //replace all characters with ASCII 'space'
#define Return_Home           0x02               // return cursor to first position on first line
#define Display_Off           0x08               // turn display off
#define Cursor_Shift_Left     0x10
#define Cursor_Shift_Right    0x14
#define Display_shift_Left    0x18
#define Display_shift_Right   0x1C
#define DDRAM_CONST           0x80              // set cursor position
#define CGRAM_CONST           0x40              // the first Place/Address at CGRAM
#define lcd_EntryMode         0x06             // shift cursor from left to right on read/write
#define DisplayOn_CursorOff   0x0c             // display on, cursor off, don't blink character
#define DisplayOn_CursorOn    0x0F             // display on, cursor on,blink character
#define DisplayOff_CursorOff  0x08             // turn display off
#define FunctionReset         0x30             // reset the LCD


/********/
#define LCD_ROW_1   1
#define LCD_ROW_2   2

#define LCD_COL_1   1
#define LCD_COL_2   2
#define LCD_COL_3   3
#define LCD_COL_4   4
#define LCD_COL_5   5
#define LCD_COL_6   6
#define LCD_COL_7   7
#define LCD_COL_8   8
#define LCD_COL_9   9
#define LCD_COL_10  10
#define LCD_COL_11  11
#define LCD_COL_12  12
#define LCD_COL_13  13
#define LCD_COL_14  14
#define LCD_COL_15  15
#define LCD_COL_16  16


#define LCD_SHIFT_LEFT       0
#define LCD_SHIFT_RIGHT      1

/*Functions*/

void LCD_voidInit                  (void);
void LCD_voidDisplayChar           (u8 copy_u8Data);
void LCD_voidSendCommand           (u8 copy_u8Command);
void LCD_voidClear                 (void);
void LCD_voidSendString            (u8 *copy_u8PtrString);
void LCD_voidSendNumber            (u32 copy_u32Number);
void LCD_voidShift                 (u8 copy_u8ShifttingDirection); // cmnd
void LCD_voidGoToSpecificPosition  (u8 copy_u8LineNumber, u8 copy_u8Position); // cmnd
void LCD_voidSendExtraChar         ( u8 copy_u8Row , u8 copy_u8Col );



#endif /* LCD_INTERFACE_H_ */

/*
 * LCD_interface.h
 *
 *  Created on: Aug 17, 2024
 *      Author: Mariam
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

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


#define LCD_SHIFT_LEFT      0
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



#endif /* LCD_INTERFACE_H_ */

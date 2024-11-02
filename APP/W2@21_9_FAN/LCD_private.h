/*
 * LCD_private.h
 *
 *  Created on: Aug 17, 2024
 *      Author: Mariam
 */

#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

#include "LCD_config.h"

static void PRV_voidEnableTriggerWrite    (void);
static void PRV_voidWriteHalfPort  (u8 copu_u8Val);

/*List of instruction codes*/

#define Clear_Display         0x01
#define Return_Home           0x02
#define Display_Off           0x08
#define Cursor_Shift_Left     0x10
#define Cursor_Shift_Right    0x14
#define Display_shift_Left    0x18
#define Display_shift_Right   0x1C
#define DDRAM_CONST           0x80
#define CGRAM_CONST           0x40
#define lcd_EntryMode         0x06          // shift cursor from left to right on read/write

#endif /* LCD_PRIVATE_H_ */

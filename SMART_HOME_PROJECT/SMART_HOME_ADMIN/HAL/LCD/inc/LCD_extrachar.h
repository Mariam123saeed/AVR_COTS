/*
 * LCD_extrachar.h
 *
 *  Created on: Sep 25, 2024
 *      Author: Mariam
 */

#ifndef LCD_EXTRACHAR_H_
#define LCD_EXTRACHAR_H_

/*

 We draw each char on website ===>> https://maxpromer.github.io/LCD-Character-Creator/

 Hint : *this website already neglect the first 3 bits in each byte = 0 (on the left side)
        *take the hex value or ad 000 on the left
*/


u8 LCD_u8ExtraChar[] = {

		 0x0D,0x1F,0x13,0x10,0x10,0x10,0x10,0x00,
		 0x03,0x0B,0x0C,0x08,0x08,0x10,0x00,0x00
};

#endif /* LCD_EXTRACHAR_H_ */

/*
 * KEYPAD_interface.h
 *
 *  Created on: Aug 23, 2024
 *      Author: Mariam
 */

#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_


/**********************************************************APIS PROTO TYPE ************************************************/

#define KPD_NOT_PRESSED       0xFF


void   KEYPAD_voidInit      (void);
void   KEYPAD_voidGetValue  (u8 * copy_u8ReturnedValue);

#endif /* KEYPAD_INTERFACE_H_ */

/*
 * EEPROM_interface.h
 *
 *  Created on: Oct 4, 2024
 *      Author: Mariam
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

/*********************************************************************APIS PROTO TYPES****************************************************************************/
void EEPROM_voidInit (void);
void EEPROM_voidSendDataByte(u16 copy_u16WordAddress, u8 copy_u8Data);
void EEPROM_voidReadDataByte(u16 copy_u16WordAddress ,u8 *copy_u8Data);
void EEPROM_voidWriteDataPage(u16 copy_u16BaseAddress, u8 copy_u8DataLength,u8* copy_u8DataArray);
void EEPROM_voidReadDataPage(u16 copy_u16BaseAddress, u8 copy_u8DataLength,u8* copy_u8DataPassOutArray);



#endif /* EEPROM_INTERFACE_H_ */

/*
 * EEPROM_program.c
 *
 *  Created on: Oct 4, 2024
 *      Author: Mariam
 */
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"


/*MCAL*/
#include "TWI_interface.h"

/*HAL*/
#include "EEPROM_interface.h"
#include "EEPROM_private.h"


void EEPROM_voidInit (void)
{
	TWI_voidInitMaster (90);
}

void EEPROM_voidSendDataByte(u16 copy_u16WordAddress, u8 copy_u8Data)
{

	u8 local_u8DeviceAdd = (copy_u16WordAddress>>8) |EEPROM_FIXED_ADDRESS;
	/*Send start condition*/
	TWI_SendStartCondition();
	/*Send device Address(W)*/
	TWI_SendSlaveAddressWithWrite (local_u8DeviceAdd);
	/*Send Word Address*/
	TWI_SendMasterDataByte ((u8)copy_u16WordAddress);
	/*Send data*/
	TWI_SendMasterDataByte ((u8)copy_u8Data);
	/*Send Stop condetion*/
	TWI_SendStopCondition ();
	/*Self time life cycle delay*/
	_delay_ms (5);
}
void EEPROM_voidReadDataByte(u16 copy_u16WordAddress ,u8 *copy_u8Data)
{
	if (copy_u8Data != NULL)
	{
		u8 local_u8DeviceAdd = (copy_u16WordAddress>>8) |EEPROM_FIXED_ADDRESS;
		/*Send start condition*/
		TWI_SendStartCondition();
		/*Send device Address (W)*/
		TWI_SendSlaveAddressWithWrite (local_u8DeviceAdd);
		/*Send Word Address*/
		TWI_SendMasterDataByte ((u8)copy_u16WordAddress);
		/*Send repeated start condition to switch I2C operation from W TO R*/
		TWI_SendRepeatedStart();
		/*Send device Address (R)*/
		TWI_SendSlaveAddressWithRead (local_u8DeviceAdd);
		/*Recieve byte  data */
		TWI_RecieveMasterDataByteWithOutAck(copy_u8Data);
		/*Self time life cycle delay*/
		_delay_ms (5);

	}


}

void EEPROM_voidWriteDataPage(u16 copy_u16BaseAddress, u8 copy_u8DataLength,u8* copy_u8DataArray)
{
	u8 local_u8Iterator;
	 if (copy_u8DataArray != NULL && copy_u8DataLength <= 16)
	    {
	        u8 local_u8DeviceAdd = (copy_u16BaseAddress >> 8) | EEPROM_FIXED_ADDRESS;
	        /* Send start condition */
	        TWI_SendStartCondition();
	        /* Send device Address (W) */
	        TWI_SendSlaveAddressWithWrite(local_u8DeviceAdd);
	        /* Send Base Address */
	        TWI_SendMasterDataByte((u8)copy_u16BaseAddress);

	        for (local_u8Iterator = 0; local_u8Iterator < copy_u8DataLength; local_u8Iterator++)
	        {
	            /* Send data byte by byte */
	            TWI_SendMasterDataByte(copy_u8DataArray[local_u8Iterator]);
	        }

	        /* Send Stop condition */
	        TWI_SendStopCondition();
	        /* Self time life cycle delay */
	        _delay_ms(5);
	    }
	    else
	    {
	         //return error state
	    }
}
void EEPROM_voidReadDataPage(u16 copy_u16BaseAddress, u8 copy_u8DataLength, u8* copy_u8DataPassOutArray)
{
    u8 local_u8Iterator;
    if (copy_u8DataPassOutArray != NULL && copy_u8DataLength <= 16)
    {
        u8 local_u8DeviceAdd = (copy_u16BaseAddress >> 8) | EEPROM_FIXED_ADDRESS;
        /* Send start condition */
        TWI_SendStartCondition();
        /* Send device Address (W) */
        TWI_SendSlaveAddressWithWrite(local_u8DeviceAdd);
        /* Send Base Address */
        TWI_SendMasterDataByte((u8)copy_u16BaseAddress);
        /* Send repeated start condition to switch I2C operation from W to R */
        TWI_SendRepeatedStart();
        /* Send device Address (R) */
        TWI_SendSlaveAddressWithRead(local_u8DeviceAdd);

        for (local_u8Iterator = 0; local_u8Iterator < (copy_u8DataLength-1); local_u8Iterator++)
        {

                /* Receive byte with ACK */
            	TWI_RecieveMasterDataByteWithAck(&copy_u8DataPassOutArray[local_u8Iterator]);

        }
           /*Recieve data with nACK */
        		TWI_RecieveMasterDataByteWithOutAck(&copy_u8DataPassOutArray[local_u8Iterator]);

        /* Send Stop condition */
        TWI_SendStopCondition();
        /* Self time life cycle delay */
        _delay_ms(5);
    }
    else
    {
    	//return error state
    }
}

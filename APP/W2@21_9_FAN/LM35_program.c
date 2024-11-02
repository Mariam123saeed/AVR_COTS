/*
 * LM35_program.c
 *
 *  Created on: Sep 13, 2024
 *      Author: Mariam
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "ADC_interface.h"

#include "LM35_interface.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function initialize the refrence voltage of ADC
* Parameters :
            => copy_u8ReferenceVoltage {AVCC , AREF ,INTERNAL}
* return : Nothing
*/
void LM35_voidInit(LM35_sensorChannel_t copy_tChannelId)
{
	DIO_enumSetPinDirection(DIO_PORTA, copy_tChannelId, DIO_PIN_INPUT);

	ADC_voidInit(INTERNAL_2_56);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function convert from mV to C degree
* Parameters :
            => struct has the LM35 Channel, ADC VoltageReference , ADCResolution
			=> Pointer to TEMP Variable which will return in it
* return : Nothing
*/
void LM35_voidGetTemperature(LM35_sensorChannel_t copy_tChannelId, u8* copy_u8Temperature)
{
	if(copy_u8Temperature != NULL)
	{
		u16 local_u16DigitalVal, local_u16AnalogVal;
		ADC_voidGetDigitalValue(copy_tChannelId, &local_u16DigitalVal);

		local_u16AnalogVal = (local_u16DigitalVal * 2560UL) / 1024;
		*copy_u8Temperature = local_u16AnalogVal / 10;
	}
	else
	{
		//return Error State
	}
}

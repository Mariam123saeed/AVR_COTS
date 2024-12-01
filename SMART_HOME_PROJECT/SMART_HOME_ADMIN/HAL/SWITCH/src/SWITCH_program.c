/*
 * SWITCH_program.c
 *
 *  Created on: ???/???/????
 *      Author: Kareem Hussein
 */

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "SWITCH_interface.h"


void SWITCH_voidInit(u8 copy_u8SwitchPort, u8 copy_u8SwitchPin)
{
	DIO_enumSetPinDirection(copy_u8SwitchPort, copy_u8SwitchPin, DIO_PIN_INPUT);
}


void SWITCH_voidGetState(u8 copy_u8SwitchPort, u8 copy_u8SwitchPin, u8 copy_u8SwitchConnectionType, u8* copy_pu8SwitchState)
{
	if(copy_pu8SwitchState != NULL)
	{
		u8 local_u8SwitchVal;
		switch(copy_u8SwitchConnectionType)
		{
		case SWITCH_FORWARD_CONNECTION:
			DIO_enumGetPinValue(copy_u8SwitchPort, copy_u8SwitchPin, &local_u8SwitchVal);
			switch(local_u8SwitchVal)
			{
			case DIO_PIN_HIGH:
				*copy_pu8SwitchState = SWITCH_PRESSED;
				break;

			case DIO_PIN_LOW:
				*copy_pu8SwitchState = SWITCH_NOT_PRESSED;
				break;
			}
			break;

			case SWITCH_REVERSE_CONNECTION:
				DIO_enumGetPinValue(copy_u8SwitchPort, copy_u8SwitchPin, &local_u8SwitchVal);
				switch(local_u8SwitchVal)
				{
				case DIO_PIN_HIGH:
					*copy_pu8SwitchState = SWITCH_NOT_PRESSED;
					break;

				case DIO_PIN_LOW:
					*copy_pu8SwitchState = SWITCH_PRESSED;
					break;
				}
				break;
		}
	}
	else
	{
		// return Error State
	}
}

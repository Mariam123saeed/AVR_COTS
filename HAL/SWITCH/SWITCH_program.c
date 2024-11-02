/*
 * SWITCH_program.c
 *
 *  Created on: Aug 17, 2024
 *      Author: Mariam
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "SWITCH_interface.h"


//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function initialize the pin which connected to Push Button as Pull Up Input pin
* Parameters :   => struct has the switch porn , pin , status
* return : void
*/
void SWITCH_voidInit   (SW_Type SW_Config  )
{
	DIO_enumSetPinDirection (SW_Config.Port , SW_Config.Pin, DIO_PIN_INPUT);
	if(SW_Config.Pull_State == SWITCH_Int_PULL_UP )
	{
		DIO_enumSetPinValue    ( SW_Config.Port , SW_Config.Pin , DIO_PIN_HIGH  );
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function read Button status
* Parameters :   => struct has the switch porn , pin , status
* return : switch status
*/

u8 SWITCH_u8GetState( SW_Type SW_Config)
{
	u8 LOC_u8Result = SWITCH_NOT_PRESSED ;
		u8 LOC_u8PinVal = SWITCH_NOT_PRESSED ;
		/* REVERSED_CONNECTION*/
		if ( (SW_Config.Pull_State == SWITCH_Int_PULL_UP) || (SW_Config.Pull_State == SWITCH_Ext_PULL_UP) )
		{
			DIO_enumGetPinValue( SW_Config.Port , SW_Config.Pin , &LOC_u8PinVal );

			if (0==LOC_u8PinVal)
			{
				LOC_u8Result = SWITCH_PRESSED ;
			}
			else if (1==LOC_u8PinVal)
			{
				LOC_u8Result = SWITCH_NOT_PRESSED ;
			}

		}
		/*FORWARD_CONNECTION*/
		else if (SW_Config.Pull_State == SWITCH_Ext_PULL_DOWN)
		{
			DIO_enumGetPinValue( SW_Config.Port , SW_Config.Pin , &LOC_u8PinVal );

			if (0==LOC_u8PinVal )
			{
				LOC_u8Result = SWITCH_NOT_PRESSED ;
			}
			else if (1==LOC_u8PinVal)
			{
				LOC_u8Result = SWITCH_PRESSED ;
			}
		}

		return LOC_u8Result ;
}

/*
 * BUZZER_program.c
 *
 *  Created on: Aug 17, 2024
 *      Author: Mariam
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "BUZZER_interface.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function initialize the pin which connected to BUZZER as output pin
* Parameters :
            => struct has the BUZ porn , pin , status
* return : void
*/
void BUZZER_voidInit     (BUZ_Type BUZ_Configuration)
{
	DIO_enumSetPinDirection (BUZ_Configuration.Port , BUZ_Configuration.Pin,DIO_PIN_OUTPUT);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function set high on BUZZER pin ( BUZ on )
* Parameters :
            => struct has the BUZ porn , pin , status
* return : void
*/
void BUZZER_voidOn       (BUZ_Type BUZ_Configuration)
{
	if(BUZ_Configuration.Active_State==ACTIVE_HIGH)
	{
		DIO_enumSetPinValue (BUZ_Configuration.Port , BUZ_Configuration.Pin,DIO_PIN_HIGH);
	}
	else if(BUZ_Configuration.Active_State==ACTIVE_LOW)
	{
		DIO_enumSetPinValue (BUZ_Configuration.Port , BUZ_Configuration.Pin,DIO_PIN_LOW);
	}

}
//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function set low on BUZZER pin ( BUZ on )
* Parameters :
            => struct has the BUZ porn , pin , status
* return : void
*/
void BUZZER_voidOff      (BUZ_Type BUZ_Configuration)
{
	if(BUZ_Configuration.Active_State==ACTIVE_HIGH)
		{
			DIO_enumSetPinValue (BUZ_Configuration.Port , BUZ_Configuration.Pin,DIO_PIN_LOW);
		}
		else if(BUZ_Configuration.Active_State==ACTIVE_LOW)
		{
			DIO_enumSetPinValue (BUZ_Configuration.Port , BUZ_Configuration.Pin,DIO_PIN_HIGH);
		}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function toggle BUZ pin
* Parameters :
             => struct has the BUZ porn , pin , status
* return : void
*/
void BUZZER_voidToggle      ( BUZ_Type BUZ_Configuration )
{
	DIO_enumTogglePinValue  ( BUZ_Configuration.Port , BUZ_Configuration.Pin );
}

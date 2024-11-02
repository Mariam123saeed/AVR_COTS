/*
 * LED_program.c
 *
 *  Created on: Aug 16, 2024
 *      Author: Mariam
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "LED_interface.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function initialize the pin which connected to led as output pin
* Parameters :
            => struct has the led port , pin , status
* return : void
*/
void LED_voidInit( LED_Type LED_Configuration )
{

	DIO_enumSetPinDirection( LED_Configuration.Port , LED_Configuration.Pin , DIO_PIN_OUTPUT );

}
//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function set high on led pin ( led on )
* Parameters :
            => struct has the led port , pin , status
* return : void
*/

void LED_voidOn    (LED_Type LED_Configuration)
{
	DIO_Errorstatus LOC_enumstate=DIO_OK;
	switch( LED_Configuration.Connection_Type)
	{
	   case  LED_FORWARD_CONNECTION :
			DIO_enumSetPinValue( LED_Configuration.Port , LED_Configuration.Pin , DIO_PIN_HIGH );
			break;
	   case LED_REVERSE_CONNECTION :
		   DIO_enumSetPinValue( LED_Configuration.Port , LED_Configuration.Pin , DIO_PIN_LOW  );
		   break;
	   default :
		   LOC_enumstate=DIO_NOK;
		   break;

	}

}
//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function set low on led pin ( led off )
* Parameters :
            => struct has the led port , pin , status
* return : void
*/
void LED_voidOff    (LED_Type LED_Configuration)
{
	DIO_Errorstatus LOC_enumstate=DIO_OK;
		switch( LED_Configuration.Connection_Type)
		{
		   case  LED_FORWARD_CONNECTION :
				DIO_enumSetPinValue( LED_Configuration.Port , LED_Configuration.Pin , DIO_PIN_LOW );
				break;
		   case LED_REVERSE_CONNECTION :
			   DIO_enumSetPinValue( LED_Configuration.Port , LED_Configuration.Pin , DIO_PIN_HIGH  );
			   break;
		   default :
			   LOC_enumstate=DIO_NOK;
			   break;

		}

}
//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function toggle led pin
* Parameters :
             => struct has the led port , pin , status
* return : void
*/
void LED_voidToggle  (LED_Type LED_Configuration)
{
	DIO_enumTogglePinValue  ( LED_Configuration.Port , LED_Configuration.Pin );
}



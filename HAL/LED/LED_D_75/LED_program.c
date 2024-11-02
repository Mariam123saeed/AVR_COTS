/*
 * LED_program.c
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
#include "LED_interface.h"


void LED_voidInit(u8 copy_u8LedPort, u8 copy_u8LedPin)
{
	DIO_enumSetPinDirection(copy_u8LedPort, copy_u8LedPin, DIO_PIN_OUTPUT);
}


void LED_voidOn(u8 copy_u8LedPort, u8 copy_u8LedPin, u8 copy_u8LedConnectionType)
{
	switch(copy_u8LedConnectionType)
	{
	case LED_FORWARD_CONNECTION:
		DIO_enumSetPinValue(copy_u8LedPort, copy_u8LedPin, DIO_PIN_HIGH);
		break;

	case LED_REVERSE_CONNECTION:
		DIO_enumSetPinValue(copy_u8LedPort, copy_u8LedPin, DIO_PIN_LOW);
		break;

	default :
		// return Error State
		break;
	}
}


void LED_voidOff(u8 copy_u8LedPort, u8 copy_u8LedPin, u8 copy_u8LedConnectionType)
{
	switch(copy_u8LedConnectionType)
	{
	case LED_FORWARD_CONNECTION:
		DIO_enumSetPinValue(copy_u8LedPort, copy_u8LedPin, DIO_PIN_LOW);
		break;

	case LED_REVERSE_CONNECTION:
		DIO_enumSetPinValue(copy_u8LedPort, copy_u8LedPin, DIO_PIN_HIGH);
		break;

	default :
		// return Error State
		break;
	}
}


void LED_voidToggle(u8 copy_u8LedPort, u8 copy_u8LedPin)
{
	DIO_enumTogglePinValue(copy_u8LedPort, copy_u8LedPin);
}

/*
 * DIO_interface.h
 *
 *  Created on: Aug 10, 2024
 *  Author: Mariam Saeed
 */

#ifndef MCAL_DIO_DIO_INTERFACE_H_
#define MCAL_DIO_DIO_INTERFACE_H_


// PIN Directions
#define DIO_PIN_OUTPUT		1
#define DIO_PIN_INPUT	    0

// PIN Value Options
#define DIO_PIN_HIGH		1
#define DIO_PIN_LOW			0

// PORT Directions
#define DIO_PORT_OUTPUT		0xFF
#define DIO_PORT_INPUT		0

// PORT Value Options
#define DIO_PORT_HIGH 		0xFF
#define DIO_PORT_LOW  		0


/*DIO_PORTS*/

#define DIO_PORTA           0
#define DIO_PORTB           1
#define DIO_PORTC           2
#define DIO_PORTD           3

/*DIO_PINS*/

#define DIO_PIN0            0
#define DIO_PIN1            1
#define DIO_PIN2            2
#define DIO_PIN3            3
#define DIO_PIN4            4
#define DIO_PIN5            5
#define DIO_PIN6            6
#define DIO_PIN7            7

/*Enumeration*/
typedef enum{
	DIO_NOK,
	DIO_OK

} DIO_Errorstatus;

/*DIO_PINS_FUNCTION*/

DIO_Errorstatus DIO_enumSetPinDirection  (u8 copy_u8PortId , u8 copy_u8PinId , u8 copy_u8PinDirection);
DIO_Errorstatus DIO_enumSetPinValue      (u8 copy_u8PortId , u8 copy_u8PinId , u8 copy_u8PinValue);
DIO_Errorstatus DIO_enumGetPinValue      (u8 copy_u8PortId , u8 copy_u8PinId , u8 *copy_u8PinValue);
DIO_Errorstatus DIO_enumTogglePinValue   (u8 copy_u8PortId , u8 copy_u8PinId );

/*DIO_INPUT_PULL_UP_PESISTANCE*/

DIO_Errorstatus DIO_enumActivatePinInPUR  (u8 copy_u8PortId , u8 copy_u8PinId );

/*DIO_PORTS_FUNCTION*/

DIO_Errorstatus DIO_enumSetPortDirection  (u8 copy_u8PortId , u8 copy_u8PortDirection);
DIO_Errorstatus DIO_enumSetPortValue      (u8 copy_u8PortId , u8 copy_u8PortValue);
DIO_Errorstatus DIO_enumGetPortValue      (u8 copy_u8PortId , u8 *copy_u8PortValue);
DIO_Errorstatus DIO_enumTogglePortValue   (u8 copy_u8PortId );

DIO_Errorstatus DIO_enumActivePortInPullUpResistance(u8 copy_u8PortId);
#endif /* MCAL_DIO_DIO_INTERFACE_H_ */

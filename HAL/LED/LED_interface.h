/*
 * LED_interface.h
 *
 *  Created on: Aug 16, 2024
 *      Author: Mariam
 */

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_



#define LED_FORWARD_CONNECTION    1
#define LED_REVERSE_CONNECTION    2

typedef struct{

	u8 Port         ;
	u8 Pin          ;
	u8 Connection_Type ;

}LED_Type;

//.................................PROTOTYPES OF FUNCTIONS.......................................

void LED_voidInit     (LED_Type LED_Configuration);
void LED_voidOn       (LED_Type LED_Configuration);
void LED_voidOff      (LED_Type LED_Configuration);
void LED_voidToggle   (LED_Type LED_Configuration);


#endif /* LED_INTERFACE_H_ */

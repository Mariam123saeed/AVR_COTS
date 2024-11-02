/*
 * SWITCH_interface.h
 *
 *  Created on: Aug 17, 2024
 *      Author: Mariam
 */

#ifndef SWITCH_INTERFACE_H_
#define SWITCH_INTERFACE_H_


#define SWITCH_NOT_PRESSED  0
#define SWITCH_PRESSED      1

#define SWITCH_REVERSED_CONNECTION    0
#define SWITCH_FORWARD_CONNECTION     1

/*
     $ Optins of State :-
	 1- SW_Int_PULL_UP
	 2- SW_Ext_PULL_UP
	 3- SW_Ext_PULL_DOWN
	 4- SW_FLOATING

 */
/*******/
#define SWITCH_Int_PULL_UP     0
#define SWITCH_Ext_PULL_UP     1
#define SWITCH_Ext_PULL_DOWN   2
#define SWITCH_FLOATING        3
/*******/



typedef struct{

	u8 Port;
	u8 Pin ;
	u8 Pull_State;

}SW_Type;


                       /******************APIS PROTO TYPE******************/
void SWITCH_voidInit        ( SW_Type SW_Config );
u8 SWITCH_u8GetState    ( SW_Type SW_Config);


#endif /* SWITCH_INTERFACE_H_ */

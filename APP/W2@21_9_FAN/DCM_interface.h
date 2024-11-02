/*
 * DCM_interface.h
 *
 *  Created on: Sep 21, 2024
 *      Author: Mariam
 */

#ifndef DCM_INTERFACE_H_
#define DCM_INTERFACE_H_

#define DCMOTOR_CW		0
#define DCMOTOR_CCW		1
#define DCMOTOR_STOP	2

#define DCM_A      0
#define DCM_B      1

#define DCM_WITH_CTRL_SREED       0
#define DCM_WITHOUT_CTRL_SREED    1


/***************************************************************APIS PROTO TYPES****************************************************************************/
void DCM_voidInit (u8 copy_u8DcMotorSpeed , u8 copy_u8DcMotorNumber) ;
void DCM_voidOn   (u8 copy_u8DcMotorState, u8 copy_u8DcMotorNumber );
void DCM_voidOnWithControlSpeed (u8 copy_u8DcMotorState, u8 copy_u8DcMotorNumber,u8 copy_u8DcMotorSpeed);
void DCM_voidOff  (u8 copy_u8DcMotorSpeed  , u8 copy_u8DcMotorNumber);




#endif /* DCM_INTERFACE_H_ */

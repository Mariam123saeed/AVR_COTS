/*
 * BUZZER_interface.h
 *
 *  Created on: Aug 17, 2024
 *      Author: Mariam
 */

#ifndef INC_BUZZER_INTERFACE_H_
#define INC_BUZZER_INTERFACE_H_


#define ACTIVE_HIGH    1
#define ACTIVE_LOW     0

typedef struct{

	u8 Port         ;
	u8 Pin          ;
	u8 Active_State ;

}BUZ_Type;

//.................................PROTOTYPES OF FUNCTIONS.......................................

void BUZZER_voidInit     (BUZ_Type BUZ_Configuration);
void BUZZER_voidOn       (BUZ_Type BUZ_Configuration);
void BUZZER_voidOff      (BUZ_Type BUZ_Configuration);
void BUZZER_voidToggle   (BUZ_Type BUZ_Configuration);


#endif /* INC_BUZZER_INTERFACE_H_ */

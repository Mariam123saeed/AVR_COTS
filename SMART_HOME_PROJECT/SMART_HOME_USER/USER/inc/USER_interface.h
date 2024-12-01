/*
 * USER_interface.h
 *
 *  Created on: Nov 27, 2024
 *      Author: Mariam
 */

#ifndef USER_INC_USER_INTERFACE_H_
#define USER_INC_USER_INTERFACE_H_

                                                         /* APIS PROTO TYPES */
void USER_voidInit                      (void);
void USER_voidLogIn                     (void);
void USER_voidLogInRemotly              (void);
void USER_voidUserMenu                  (void);
void USER_voidUserMenuRemotly          (void);
void USER_voidControlLeds               (void);
void USER_voidControlDimmerLed          (void);
void USER_voidControlAirCondition       (void);
void USER_voidGetInput(u8 *copy_pu8Buffer, u8 copy_u8Length);
void USER_voidGetRemoteInput(u8 *copy_pu8Buffer, u8 copy_u8Length);
u8 USER_voidSendDataAndReceiveResponse(u8 *copy_pu8UserID, u8 *copy_pu8UserPass);
void ISR_Reset                          (void);

#endif /* USER_INC_USER_INTERFACE_H_ */

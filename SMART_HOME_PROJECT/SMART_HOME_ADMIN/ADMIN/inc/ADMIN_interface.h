/*
 * ADMIN_interface.h
 *
 *  Created on: Nov 25, 2024
 *      Author: Mariam
 */

#ifndef ADMIN_ADMIN_INTERFACE_H_
#define ADMIN_ADMIN_INTERFACE_H_

                                                           /* APIS PROTO TYPES */
void ADMIN_voidInit               (void);
void ADMIN_voidLogIn              (void);
void ADMIN_voidAdminMenu          (void);
void ADMIN_voidAddUser            (void);
void ADMIN_voidDeleteUser         (void);
void ADMIN_voidEditUser           (void);
void ADMIN_voidDisplayAdminMenu   (void);
void ADMIN_voidDisplayAllUsers    (void);
void ADMIN_voidOpenDoor           (void);
void ADMIN_voidCloseDoor          (void);
//void ADMIN_voidCheckLogin         (void);

void ISR_Reset                    (void);
void ISR_UserDataReceived(void);
#endif /* ADMIN_ADMIN_INTERFACE_H_ */

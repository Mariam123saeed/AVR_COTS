/*
 * USART_interface.h
 *
 *  Created on: Sep 28, 2024
 *      Author: Mariam
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

/******************************************************************************APIS PROTO TYPES*********************************************************************************/

void USART_voidInit   (void);
void USART_voidTxChar (u8 copy_u8TxData);
void USART_voidRxChar (u8 *copy_pu8RxData);
void USART_voidTxString  (u8* copy_u8TxString);
void USART_voidRxString  (u8* copy_u8RxString);

#endif /* USART_INTERFACE_H_ */

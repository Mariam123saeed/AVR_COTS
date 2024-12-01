/*
 * TWI_interface.h
 *
 *  Created on: Oct 4, 2024
 *      Author: Mariam
 */

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

/* Prescalers */
#define PRESCALLER_BY_1    1
#define PRESCALLER_BY_4    4
#define PRESCALLER_BY_16   16
#define PRESCALLER_BY_64   64

/*****************************************************************************APIS PROTOTYPES*******************************************************************/
/*SET MASTER APIS*/
void TWI_voidInitMaster                  (u8 copy_u8Address);
void TWI_SendStartCondition              (void);
void TWI_SendRepeatedStart               (void);
void TWI_SendSlaveAddressWithWrite       (u8 copy_u8SlaveAddress);
void TWI_SendSlaveAddressWithRead        (u8 copy_u8SlaveAddress);
void TWI_SendMasterDataByte              (u8 copy_u8TxData );
void TWI_RecieveMasterDataByteWithAck    (u8* copy_pu8RxData );
void TWI_RecieveMasterDataByteWithOutAck (u8* copy_pu8RxData );
void TWI_SendStopCondition(void);

void TWI_voidInitSlave(u8 copy_u8Address);
void TWI_SlaveWriteDataByte(u8 copy_u8DataByte);
void TWI_SlaveReadDataByte(u8* copy_pu8DataByte);


#endif /* TWI_INTERFACE_H_ */

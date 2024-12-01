/*
 * TWI_program.c
 *
 *  Created on: Oct 4, 2024
 *      Author: Mariam
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TWI_config.h"
#include "TWI_interface.h"
#include "TWI_private.h"
#include "TWI_register.h"


void TWI_voidInitMaster                  (u8 copy_u8Address)
{
	if (copy_u8Address<128 && copy_u8Address>0)
	{
		/*Set the required address in the 7 MSB of TWAR*/
		TWAR_REG = (copy_u8Address<<1);
		/*Set SCL frequency to 400kHz, with 16Mhz system frequency*/
		TWBR_REG =12;
		CLR_BIT (TWSR_REG,TWPS1);
		CLR_BIT (TWSR_REG,TWPS0);
		/*Disable TWI Interrupt*/
		CLR_BIT (TWCR_REG ,TWIE);
		/*Enable TWI Peripheral*/
		SET_BIT (TWCR_REG ,TWEN);


	}
	else
	{
	    //return error state
	}
}
void TWI_SendStartCondition (void)
{
	/*Send start condition*/
		SET_BIT(TWCR_REG, TWSTA);
	/*Clear the interrupt flag to start the previous operation*/
	   SET_BIT(TWCR_REG,TWINT);
	 /*wait until the operation finishes and the flag is raised(Busy wait on the flag)*/
	   	while(0 == (GET_BIT(TWCR_REG,TWINT)));
	 /*Check the operation status (Bit Masking) */
	   while((TWI_STATUS_VALUE) != START_ACK );

}
void TWI_SendRepeatedStart (void)
{
	/*Send start condition*/
	  SET_BIT(TWCR_REG, TWSTA);
	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR_REG,TWINT);
	/*wait until the operation finishes and the flag is raised(Busy wait on the flag)*/
	while(0 == (GET_BIT(TWCR_REG,TWINT)));
    /*Check the operation status (Bit Masking) */
	while((TWI_STATUS_VALUE) != REP_START_ACK );
}
void TWI_SendStopCondition(void)
{
	/*Sent a stop condition on the bus*/
		SET_BIT(TWCR_REG,TWSTO);

	/*Clear the interrupt flag to start the previous operation*/
		SET_BIT(TWCR_REG,TWINT);
}
void TWI_SendSlaveAddressWithWrite(u8 copy_u8SlaveAddress)
{
	if (copy_u8SlaveAddress<128 )
	{
		/*send the 7bit slave address to the bus*/
		TWDR_REG = (copy_u8SlaveAddress<<1) ;
		/*set the write request in the LSB in the data register*/
			CLR_BIT(TWDR_REG,0);
		/*Clear the start condition bit*/
			CLR_BIT(TWCR_REG,TWSTA);
		/*Clear the interrupt flag to start the previous operation*/
		    SET_BIT(TWCR_REG,TWINT);
		/*wait until the operation finishes and the flag is raised(Busy wait on the flag)*/
		    while(0 == (GET_BIT(TWCR_REG,TWINT)));
		/*Check the operation status (Bit Masking) */
		   while((TWI_STATUS_VALUE) != SLAVE_ADD_AND_WR_ACK );
	}
	else
	{
          //return error state
	}

}
void TWI_SendSlaveAddressWithRead        (u8 copy_u8SlaveAddress)
{
	if (copy_u8SlaveAddress<128 )
		{
			/*send the 7bit slave address to the bus*/
			TWDR_REG = (copy_u8SlaveAddress<<1) ;
			/*set the write request in the LSB in the data register*/
				SET_BIT(TWDR_REG,0);
			/*Clear the start condition bit*/
			    CLR_BIT(TWCR_REG,TWSTA);
			/*Clear the interrupt flag to start the previous operation*/
			    SET_BIT(TWCR_REG,TWINT);
			/*wait until the operation finishes and the flag is raised(Busy wait on the flag)*/
			    while(0 == (GET_BIT(TWCR_REG,TWINT)));
			/*Check the operation status (Bit Masking) */
			   while((TWI_STATUS_VALUE) != SLAVE_ADD_AND_RD_ACK );
		}
		else
		{
	          //return error state
		}
}
void TWI_SendMasterDataByte              (u8 copy_u8TxData )
{
	/*Write the data byte on the bus*/
		TWDR_REG = copy_u8TxData;
		/*Clear the interrupt flag to start the previous operation*/
			SET_BIT(TWCR_REG,TWINT);
		/*wait until the operation finishes and the flag is raised(Busy wait on the flag)*/
			while(0 == (GET_BIT(TWCR_REG,TWINT)));
		/*Check the operation status (Bit Masking) */
			while((TWI_STATUS_VALUE) !=  MSTR_WR_BYTE_ACK );

}
void TWI_RecieveMasterDataByteWithAck    (u8* copy_pu8RxData )
{
	if(copy_pu8RxData != NULL)
	{
		/*Enable ACK PIN*/
		SET_BIT (TWCR_REG ,TWEA);
		/*Clear the interrupt flag to start the previous operation*/
		SET_BIT(TWCR_REG,TWINT);
		/*wait until the operation finishes and the flag is raised(Busy wait on the flag)*/
		while(0 == (GET_BIT(TWCR_REG,TWINT)));
		/*Check the operation status (Bit Masking) */
		while((TWI_STATUS_VALUE) != MSTR_RD_BYTE_WITH_ACK );
		/*Recieve data*/
		*copy_pu8RxData = TWDR_REG;
		/*Disable ACK PIN*/
		CLR_BIT (TWCR_REG ,TWEA);
	}
	else
	{
		//return state 0;
	}
}
void TWI_RecieveMasterDataByteWithOutAck (u8* copy_pu8RxData )
{
	if(copy_pu8RxData != NULL)
	{

		/*Clear the interrupt flag to start the previous operation*/
			SET_BIT(TWCR_REG,TWINT);
		/*wait until the operation finishes and the flag is raised(Busy wait on the flag)*/
			while(0 == (GET_BIT(TWCR_REG,TWINT)));
		/*Check the operation status (Bit Masking) */
			while((TWI_STATUS_VALUE) != MSTR_RD_BYTE_WITH_NACK );
			/*Recieve data*/
			*copy_pu8RxData = TWDR_REG;

	}
	else
	{
			//return state 0;
	}
}

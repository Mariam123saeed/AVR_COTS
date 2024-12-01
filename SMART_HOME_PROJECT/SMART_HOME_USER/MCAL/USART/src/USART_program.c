/*
 * USART_program.c
 *
 *  Created on: Sep 28, 2024
 *      Author: Mariam
 */

/*UTILS LIB*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*MCAL*/
#include "USART_interface.h"
#include "USART_register.h"

//-------------------------------------------------------------------------------------------------------------------------------

/*
 * Breif : This Function initialize USART
 * Parameters :  Nothing
 * return : Nothing
 */
void USART_voidInit   (void)
{
	u8 local_u8UCSRC = 0 ;

     /*Set baud rate as 9600 when F_CPU = 16000000UL  & Double speed disabled from equation : ((SYSTEM_FREQUENCY / (16 * USART_BAUD_RATE)) - 1)*/
	UBRRL_REG = 103;
	CLR_BIT (UCSRA_REG , U2X);
	//reading UCSRC_REG
	SET_BIT (local_u8UCSRC,URSEL);
	// SELECT  Asynchronous Operation
	CLR_BIT (local_u8UCSRC,UMSEL);
	/*No parity*/
	CLR_BIT (local_u8UCSRC,UPM1);
	CLR_BIT (local_u8UCSRC,UPM0);
	//Select 1bit stop
	CLR_BIT (local_u8UCSRC,USBS);
	/*Select Character Size 8bit*/
	CLR_BIT (UCSRB_REG,UCSZ2) ;
	SET_BIT (local_u8UCSRC,UCSZ1);
	SET_BIT (local_u8UCSRC,UCSZ0);
	//Disable clk polarity
	CLR_BIT (local_u8UCSRC,UCPOL);

	UCSRC_REG = local_u8UCSRC ;


	/*Rx Enable*/
	SET_BIT(UCSRB_REG , RXEN) ;
	/*Tx Enable*/
	SET_BIT(UCSRB_REG , TXEN) ;


}
//-------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function Send data by writing copy_u8TxData into UDR_REG and blocking on flag
 * Parameters : copy_u8TxData
 * return : Nothing
 */
void USART_voidTxChar (u8 copy_u8TxData)
{
    /* Put data into buffer, sends the data */
       UDR_REG = copy_u8TxData;
    /* Wait for empty transmit buffer */
       while (0 == GET_BIT(UCSRA_REG,UDRE));
}
//-------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function Recieved data by reading copy_u8RxData from UDR_REG after blocking on flag
 * Parameters : copy_u8TxData
 * return : Nothing
 */
void USART_voidRxChar (u8 *copy_pu8RxData)
{
    if (copy_pu8RxData !=NULL)
    {
    	// Wait until data is received
    	 while (0 == GET_BIT(UCSRA_REG,RXC));

       // Read the received data from the USART Data Register
    	*copy_pu8RxData = UDR_REG;
    }
    else
    {
    	//return error state
    }


}

void USART_voidTxString  (u8* copy_u8TxString)
{
	if (copy_u8TxString !=NULL)
	{
		u8 local_u8Conter=0;
		while (copy_u8TxString [local_u8Conter] !='\0')
		{
			USART_voidTxChar(copy_u8TxString [local_u8Conter]);
			local_u8Conter ++;
		}
	}
}
void USART_voidRxString  (u8* copy_u8RxString)
{
	if (copy_u8RxString !=NULL)
	{
		u8 local_u8Conter=0;
		while (1)
		{
			USART_voidRxChar(&copy_u8RxString[local_u8Conter]);
			if(copy_u8RxString[local_u8Conter] == '#')
			{
				break;
			}
			else
			{
				local_u8Conter ++;
			}

		}
		copy_u8RxString[local_u8Conter] = '\0';
	}
}

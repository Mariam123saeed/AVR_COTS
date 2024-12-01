/*
 * SPI_interface.h
 *
 *  Created on: Oct 1, 2024
 *      Author: Mariam
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

                         /*****************************MACROS***********************************/
#define SPI_INTERRUPT_DISABLE					1
#define SPI_INTERRUPT_ENABLE 					2
 //------------------------------------------------------------------------------------------------------------------------------------
#define SPI_DISABLE								0
#define SPI_ENABLE 								1
//------------------------------------------------------------------------------------------------------------------------------------
#define SPI_DATA_LSB_FIRST 						0
#define SPI_DATA_MSB_FIRST 						1
//------------------------------------------------------------------------------------------------------------------------------------
#define SPI_MASTER								1
#define SPI_SLAVE 								2
//------------------------------------------------------------------------------------------------------------------------------------
#define SPI_RISING_LEADING_FALLING_TRAILING 	0
#define SPI_FALLING_LEADING_RISING_TRAILING		1
//------------------------------------------------------------------------------------------------------------------------------------
#define SPI_SAMPLE_LEADING_SETUP_TRAILING 		0
#define SPI_SETUP_LEADING_SAMPLE_TRAILING		1
//------------------------------------------------------------------------------------------------------------------------------------
#define SPI_FREQ_DIVIDED_BY_4					0
#define SPI_FREQ_DIVIDED_BY_16					1
#define SPI_FREQ_DIVIDED_BY_64					2
#define SPI_FREQ_DIVIDED_BY_128					3
#define SPI_FREQ_DIVIDED_BY_2					4
#define SPI_FREQ_DIVIDED_BY_8					5
#define SPI_FREQ_DIVIDED_BY_32					6

/*****************************************************************************APIS PROTO TYPES**********************************************************************************/

void SPI_voidInit          (void);
void SPI_voidTransmiteData (u8 copy_u8TxData);
void SPI_voidRecieveData   (u8 *copy_pu8RxData);
u8 SPI_u8TrancieveData (u8 copy_u8TxData ,u8 *copy_pu8RxData);

void SPI_voidTxString      (u8* copy_u8TxString);
void SPI_voidRxString      (u8* copy_u8RxString);

void SPI_voidTranceiveAsynch(u8 copy_u8TxData, u8 *copy_pu8RxData, void (*copy_NotificationFunc)(void));



#endif /* SPI_INTERFACE_H_ */

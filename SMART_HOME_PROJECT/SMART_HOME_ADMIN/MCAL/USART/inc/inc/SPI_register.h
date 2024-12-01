/*
 * SPI_register.h
 *
 *  Created on: Oct 1, 2024
 *      Author: Mariam
 */

#ifndef SPI_REGISTER_H_
#define SPI_REGISTER_H_

                             /****************************SPI Registers Definition***************************/

/*SPCRSPI Control Register */
#define SPCR_REG				* ((volatile u8 *)0x2D)

#define SPIE			7       //SPE: SPI Enable
#define SPE			    6       //SPE: SPI Enable
#define DORD			5       //DORD: Data Order
#define MSTR			4       //MSTR: Master/Slave Select
#define CPOL			3       //CPOL: Clock Polarity
#define CPHA			2       //CPHA: Clock Phase
#define SPR1			1       //SPR1, SPR0: SPI Clock Rate Select 1 and 0
#define SPR0			0

/*SPI Status Register – SPSR*/
#define SPSR_REG		    	* ((volatile u8 *)0x2E)

#define SPIF			7      //SPIF: SPI Interrupt Flag
#define WCOL			6      //WCOL: Write COLlision Flag
#define SPI2X			0      //SPI2X: Double SPI Speed Bit

/*SPI Data Register – SPDR*/
#define SPDR_REG			    * ((volatile u8 *)0x2F)


#endif /* SPI_REGISTER_H_ */

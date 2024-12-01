/*
 * TWI_register.h
 *
 *  Created on: Oct 4, 2024
 *      Author: Mariam
 */

#ifndef TWI_REGISTER_H_
#define TWI_REGISTER_H_

                                                                 /* Registers */

/*TWI Control Register*/
#define TWCR_REG		*((volatile u8*)0x56)

#define TWINT	7							/*Interrupt Flag*/
#define TWEA	6                           /*Enable Acknowledge*/
#define TWSTA	5                           /*Start Condition*/
#define TWSTO	4                           /*Stop Condition*/
#define TWWC	3                           /*Write Collision*/
#define TWEN	2                           /*Enable*/
#define TWIE	0                           /*Interrupt Enable*/

/*TWI Data Register*/
#define TWDR_REG 		*((volatile u8*)0x23)

/*TWI Address Register*/
#define	TWAR_REG		*((volatile u8*)0x22)
#define TWGCE	0							/*General Call recognition Enable*/
#define TWA1    1
#define TWA2    2
#define TWA3    3
#define TWA4    4
#define TWA5    5
#define TWA6    6

/*TWI Status Register*/
#define TWSR_REG		*((volatile u8*)0x21)
#define TWS7	7                           /*TWI Status*/
#define TWS6	6
#define TWS5	5
#define TWS4	4
#define TWS3	3
#define TWPS1	1							/*Prescaler Bit1*/
#define TWPS0	0							/*Prescaler Bit0*/


/*TWI Bit Rate Register*/
#define TWBR_REG		*((volatile u8*)0x20)

#endif /* TWI_REGISTER_H_ */

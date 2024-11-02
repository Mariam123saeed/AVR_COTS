/*
 * USART_register.h
 *
 *  Created on: Sep 28, 2024
 *      Author: Mariam
 */

#ifndef USART_REGISTER_H_
#define USART_REGISTER_H_

              /*************************************************************USART REGISTERS******************************************************************/

/*USART I/O Data Register – UDR*/
#define   UDR_REG        *((volatile u8 *)0x2C)

/*USART Control and Status Register A – UCSRA*/
#define   UCSRA_REG        *((volatile u8 *)0x2B)

#define     RXC          7   // RXC: USART Receive Complete
#define     TXC          6   // TXC: USART Transmit Complete
#define     UDRE         5   // UDRE: USART Data Register Empty
#define     FE           4   // FE: Frame Error
#define     DOR          3   // DOR: Data OverRun
#define     PE           2   // PE: Parity Error
#define     U2X          1   // U2X: Double the USART Transmission Speed
#define     MPCM         0   // MPCM: Multi-processor Communication Mode

/*USART Control and Status Register B – UCSRB*/
#define UCSRB_REG           * ((volatile u8 *) 0X2A)

#define RXCIE		7      //RXCIE: RX Complete Interrupt Enable
#define TXCIE		6      //TXCIE: TX Complete Interrupt Enable
#define UDRIE		5      //UDRIE: USART Data Register Empty Interrupt Enable
#define RXEN		4      //RXEN: Receiver Enable
#define TXEN		3      //TXEN: Transmitter Enable
#define UCSZ2		2      //UCSZ2: Character Size
#define RXB8		1      //RXB8: Receive Data Bit 8
#define TXB8		0      //TXB8: Transmit Data Bit 8

/*USART Control and Status Register C – UCSRC*/
#define UCSRC_REG           * ((volatile u8 *) 0X40)

#define URSEL 	    7      // URSEL: Register Select
#define UMSEL		6      //UMSEL: USART Mode Select
#define UPM1		5      //UPM1:0: Parity Mode
#define UPM0		4
#define USBS		3      //USBS: Stop Bit Select
#define UCSZ1		2      //UCSZ1:0: Character Size
#define UCSZ0		1
#define UCPOL		0      //UCPOL: Clock Polarity

/*USART Baud Rate Registers – UBRRL and UBRRH*/
#define UBRRL_REG           * ((volatile u8 *) 0X29)

#define UBRRH_REG           * ((volatile u8 *) 0X40)
#define URSEL		7     // URSEL: Register Select

#endif /* USART_REGISTER_H_ */

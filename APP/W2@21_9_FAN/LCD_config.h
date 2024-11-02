/*
 * LCD_config.h
 *
 *  Created on: Aug 17, 2024
 *      Author: Mariam
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/* LCD Mode */

	/* Choose 8 for 8_bit connection, 4 for 4_bit connection */

#define LCD_MODE  4

#define LCD_DATA_PORT     DIO_PORTA
/*RS,R/W,EN*/
#define LCD_CONTROL_PORT  DIO_PORTB




/* Macros For Rs configuration */
#define LCD_RS_PORT			DIO_PORTB
#define LCD_RS_PIN          DIO_PIN1

/* Macros For RW configuration */
#define LCD_RW_PORT			DIO_PORTB
#define LCD_RW_PIN          DIO_PIN2

/* Macros For Enable configuration */
#define LCD_EN_PORT			DIO_PORTB
#define LCD_EN_PIN           DIO_PIN3


/* 4 Bit Mode Data Pins Configurtion */
#define LCD_D4_PORT			DIO_PORTA
#define LCD_D4_PIN          DIO_PIN4

#define LCD_D5_PORT			DIO_PORTA
#define LCD_D5_PIN          DIO_PIN5

#define LCD_D6_PORT			DIO_PORTA
#define LCD_D6_PIN          DIO_PIN6

#define LCD_D7_PORT			DIO_PORTA
#define LCD_D7_PIN          DIO_PIN7








#endif /* LCD_CONFIG_H_ */

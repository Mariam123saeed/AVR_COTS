/*
 * KEYPAD_config.h
 *
 *  Created on: Aug 23, 2024
 *      Author: Mariam
 */

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_


                                 //C0, C1 ,C2  ,C3
#define KPD_KEYS			    {{'1','2','3','A'},\
                                 {'4','5','6','B'},\
	                             {'7','8','9','C'},\
	                             {'*','0','#','D'}}
      /*Options:-

             DIO_PORTA
             DIO_PORTB
             DIO_PORTC
             DIO_PORTD

    */

#define KEYPAD_R1_PORT       DIO_PORTC
#define KEYPAD_R2_PORT       DIO_PORTC
#define KEYPAD_R3_PORT       DIO_PORTC
#define KEYPAD_R4_PORT       DIO_PORTC

#define KEYPAD_C1_PORT       DIO_PORTD
#define KEYPAD_C2_PORT       DIO_PORTD
#define KEYPAD_C3_PORT       DIO_PORTA
#define KEYPAD_C4_PORT       DIO_PORTA

         /*
            Options:-

                       DIO_PIN0
                       DIO_PIN1
                       DIO_PIN2
                       DIO_PIN3
                       DIO_PIN4
                       DIO_PIN5
                       DIO_PIN6
                       DIO_PIN7

*/

#define KEYPAD_R1  DIO_PIN4
#define KEYPAD_R2  DIO_PIN5
#define KEYPAD_R3  DIO_PIN6
#define KEYPAD_R4  DIO_PIN7

#define KEYPAD_C1  DIO_PIN0
#define KEYPAD_C2  DIO_PIN1
#define KEYPAD_C3  DIO_PIN3
#define KEYPAD_C4  DIO_PIN2





#endif /* KEYPAD_CONFIG_H_ */

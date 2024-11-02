/*
 * TIMER0_register.h
 *
 *  Created on: Sep 6, 2024
 *      Author: Mariam
 */

#ifndef TIMER0_REGISTER_H_
#define TIMER0_REGISTER_H_


                                /***************************************TIMER0 REGISTERS**************************************/
/*Timer/Counter Control Register*/
#define TCCR0_REG                *((volatile u8 *)0x53)

#define FOC0        7
#define WGM00		6
#define COM01		5
#define COM00		4
#define WGM01		3
#define CS02        2
#define CS01		1
#define CS00		0

/*Timer/Counter Register*/
#define  TCNT0_REG             *((volatile u8 *)0x52)
/*Output Compare Register*/
#define  OCR0_REG              *((volatile u8 *)0x5C)
/*Timer/Counter Interrupt Mask Register*/
#define  TIMSK_REG             *((volatile u8 *)0x59)
#define  OCIE0      1
#define  TOIE0      0
/*Timer/Counter Interrupt Flag Register */
#define  TIFR_REG              *((volatile u8 *)0x58)
#define  OCF0      1
#define  TOV0      0



#endif /* TIMER0_REGISTER_H_ */

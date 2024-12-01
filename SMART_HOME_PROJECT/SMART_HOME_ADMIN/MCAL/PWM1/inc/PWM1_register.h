/*
 * PWM1_register.h
 *
 *  Created on: Sep 14, 2024
 *      Author: Mariam
 */

#ifndef PWM1_REGISTER_H_
#define PWM1_REGISTER_H_
                                 /***************************************PWM0 REGISTERS**************************************/

#define TCCR1A_REG			*((volatile u8*)0X4F)

#define COM1A1		7
#define COM1A0		6
#define COM1B1		5
#define COM1B0		4
#define WGM11		1
#define WGM10		0

#define TCCR1B_REG			*((volatile u8*)0X4E)

#define ICNC1		7
#define ICES1		6
#define WGM13		4
#define WGM12		3
#define CS12        2
#define CS11        1
#define CS10        0

#define TCNT1H_REG          *((volatile u8 *)0x4D)
#define TCNT1L_REG          *((volatile u8 *)0x4C)
#define TCNT1_REG			*((volatile u16*)0X4C)    /* u16 for HIGH & LOW */

#define OCR1AL_REG          *((volatile u8 *)0x4A)
#define OCR1AH_REG          *((volatile u8 *)0x4B)
#define OCR1A_REG			*((volatile u16*)0X4A)

#define OCR1BL_REG          *((volatile u8 *)0x48)
#define OCR1BH_REG          *((volatile u8 *)0x49)
#define OCR1B_REG			*((volatile u16*)0X48)

#define ICR1H_REG           *((volatile u8 *)0x47)
#define ICR1L_REG           *((volatile u8 *)0x46)
#define ICR1_REG			*((volatile u16*)0X46)

/*Timer/Counter Interrupt Mask Register*/
#define  TIMSK_REG             *((volatile u8 *)0x59)

#define TOIE1   2        //Timer/Counter1, Overflow Interrupt Enable
#define OCIE1B	3       // Timer/Counter1, Output Compare B Match Interrupt Enable
#define OCIE1A	4      // Timer/Counter1, Output Compare A Match Interrupt Enable
#define TICIE1	5     //  Timer/Counter1, Input Capture Interrupt Enable

/*Timer/Counter Interrupt Flag Register */
#define  TIFR_REG              *((volatile u8 *)0x58)

#define TOV1		2
#define OCF1B		3
#define OCF1A		4
#define ICF1		5
#endif /* PWM1_REGISTER_H_ */

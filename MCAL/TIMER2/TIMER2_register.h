/*
 * TIMER2_register.h
 *
 *  Created on: Sep 12, 2024
 *      Author: Mariam
 */

#ifndef TIMER2_REGISTER_H_
#define TIMER2_REGISTER_H_

                        /***************************************TIMER2 REGISTERS**************************************/

/*Timer/Counter Control Register*/
#define   TCCR2_REG                *((volatile u8 *)0x45)

#define    CS20       0     // Clock Select
#define    CS21       1     // Clock Select
#define    CS22       2     // Clock Select
#define    WGM21      3     //Waveform Generation Mode
#define    COM20      4     //Compare Match Output Mode
#define    COM21      5     //Compare Match Output Mode
#define    WGM20      6     //Waveform Generation Mode
#define    FOC2       7     // Force Output Compare

/*Timer/Counter Register  */
#define   TCNT2_REG                *((volatile u8 *)0x44)

/*Output Compare Register */
#define    OCR2_REG                *((volatile u8 *)0x43)

/*Asynchronous Status Register */
#define    ASSR_REG                *((volatile u8 *)0x42)

#define    TCR2UB      0               //Timer/Counter Control Register2 Update Busy
#define    OCR2UB      1               // Output Compare Register2 Update Busy
#define    TCN2UB      2               //Timer/Counter2 Update Busy
#define    AS2         3                // Asynchronous Timer/Counter2

/*Timer/Counter Interrupt Mask Register */
#define   TIMSK_REG                *((volatile u8 *)0x59)

#define   TOIE2      6               //Timer/Counter2 Overflow Interrupt Enable
#define   OCIE2      7               //Timer/Counter2 Output Compare Match Interrupt Enable

/*Timer/Counter Interrupt Flag Register */
#define    TIFR_REG                *((volatile u8 *)0x58)

#define    TOV2     6          //Timer/Counter2 Overflow Flag
#define    OCF2     7           // Output Compare Flag 2


#endif /* TIMER2_REGISTER_H_ */

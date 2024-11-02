/*
 * TIMER2_interface.h
 *
 *  Created on: Sep 12, 2024
 *      Author: Mariam
 */

#ifndef TIMER2_INTERFACE_H_
#define TIMER2_INTERFACE_H_

/* TIMER2 MODES*/

#define TIMER2_NORMAL_MODE          0
#define TIMER2_CTC_MODE             1


/* TIMER2 PreScaller*/

#define TIMER2_NO_CLOCK       0
#define TIMER2_NO_PRE         1
#define TIMER2_8_PRE          2
#define TIMER2_32_PRE         3
#define TIMER2_64_PRE         4
#define TIMER2_128_PRE        5
#define TIMER2_256_PRE        6
#define TIMER2_1024_PRE       7




/**********************************************************APIS PROTOTYPES*******************************************************************/

void TIMER2_voidInit(void);
void TIMER2_voidStart (void);
void TIMER2_voidStop (void);
void TIMER2_voidSetCompareMatchDelayms (u16 copy_u16Delay_ms);
void TIMER2_voidSetCompareMatchDelayus (u16 copy_u16Delay_us);
void TIMER2_voidSetCallBack (void (* copy_ptrToFunction)(void),u8 copy_u8InterruptSrc);


#endif /* TIMER2_INTERFACE_H_ */

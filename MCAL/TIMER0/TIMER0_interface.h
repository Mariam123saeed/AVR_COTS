/*
 * TIMER0_interface.h
 *
 *  Created on: Sep 6, 2024
 *      Author: Mariam
 */

#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

/* TIMER0 MODES*/

#define TIMER0_NORMAL_MODE          0
#define TIMER0_CTC_MODE             1
#define TIMER0_PWM_Phase_MODE       2
#define TIMER0_FAST_PWM_MODE        3

/* TIMER0 PreScaller*/

#define TIMER0_NO_CLOCK       0
#define TIMER0_NO_PRE         1
#define TIMER0_8_PRE          2
#define TIMER0_64_PRE         3
#define TIMER0_256_PRE        4
#define TIMER0_1024_PRE       5
#define TIMER0_EXT_FALLING    6
#define TIMER0_EXT_RISING     7


/* TIMER0 INTERRUPT*/

#define TIMER0_INT_DISABLE    0
#define TIMER0_INT_OVERFLOW   1
#define TIMER0_INT_COMP_MATCH 2
#define TIMER0_INT_BOTH       3

/* TIMER0 COMPARE MATCH OUTPUT MODE*/
#define TIMER0_DISCONNECTED_OC0  0
#define TIMER0_TOGGLE_OC0        1
#define TIMER0_CLEAR_OC0         2
#define TIMER0_SET_OC0           3

/**********************************************************APIS PROTOTYPES*******************************************************************/

void TIMER0_voidInit(void);
void TIMER0_voidStart (void);
void TIMER0_voidStop (void);
void TIMER0_voidSetCompareMatchDelayms (u16 copy_u16Delay_ms);
void TIMER0_voidSetCompareMatchDelayus (u16 copy_u16Delay_us);
void TIMER0_voidSetCallBack (void (* copy_ptrToFunction)(void),u8 copy_u8InterruptSrc);


#endif /* TIMER0_INTERFACE_H_ */

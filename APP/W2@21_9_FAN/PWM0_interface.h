/*
 * PWM0_interface.h
 *
 *  Created on: Sep 13, 2024
 *      Author: Mariam
 */

#ifndef PWM0_INTERFACE_H_
#define PWM0_INTERFACE_H_

/* TIMER0 MODES*/

#define TIMER0_FAST_PWM_MODE        0
#define TIMER0_PWM_PHASE_MODE       1

/* TIMER0 PreScaller*/

#define TIMER0_NO_CLOCK       0
#define TIMER0_NO_PRE         1
#define TIMER0_8_PRE          2
#define TIMER0_64_PRE         3
#define TIMER0_256_PRE        4
#define TIMER0_1024_PRE       5
#define TIMER0_EXT_FALLING    6
#define TIMER0_EXT_RISING     7

/* fast PWM0 OPTION*/
#define  PWM0_NON_INVERTING  0
#define  PWM0_INVERTING      1




/**********************************************************APIS PROTOTYPES*******************************************************************/

void PWM0_voidInit(void);
void PWM0_voidGeneratePWM (u8 copu_u8DutyCycle);
void PWM0_voidStop (void);



#endif /* PWM0_INTERFACE_H_ */

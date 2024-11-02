/*
 * PWM2_interface.h
 *
 *  Created on: Sep 14, 2024
 *      Author: Mariam
 */

#ifndef PWM2_INTERFACE_H_
#define PWM2_INTERFACE_H_

/* PWM2 MODES*/

#define TIMER2_FAST_PWM_MODE        0
#define TIMER2_PWM_PHASE_MODE       1

/* PWM2 PreScaller*/

#define TIMER2_NO_CLOCK       0
#define TIMER2_NO_PRE         1
#define TIMER2_8_PRE          2
#define TIMER2_32_PRE         3
#define TIMER2_64_PRE         4
#define TIMER2_128_PRE        5
#define TIMER2_256_PRE        6
#define TIMER2_1024_PRE       7

/* fast PWM0 OPTION*/
#define  PWM2_NON_INVERTING  0
#define  PWM2_INVERTING      1



/**********************************************************APIS PROTOTYPES*******************************************************************/

void PWM2_voidInit(void);
void PWM2_voidGeneratePWM (u8 copu_u8DutyCycle);
void PWM2_voidStop (void);




#endif /* PWM2_INTERFACE_H_ */

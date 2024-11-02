/*
 * PWM1_interface.h
 *
 *  Created on: Sep 14, 2024
 *      Author: Mariam
 */

#ifndef PWM1_INTERFACE_H_
#define PWM1_INTERFACE_H_

/* TIMER0 MODES*/

#define TIMER1_NORMAL_MODE								0
#define TIMER1_PWM_8_BIT_MODE							1
#define TIMER1_PWM_9_BIT_MODE							2
#define TIMER1_PWM_10_BIT_MODE							3
#define TIMER1_CTC_OCR1A_MODE							4
#define TIMER1_FAST_PWM_8_BIT_MODE						5
#define TIMER1_FAST_PWM_9_BIT_MODE 						6
#define TIMER1_FAST_PWM_10_BIT_MODE						7
#define TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE		8
#define TIMER1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_MODE	9
#define TIMER1_PWM_PHASE_CORRECT_ICR1_MODE				10
#define TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE				11
#define TIMER1_CTC_ICR1_MODE							12
#define TIMER1_FAST_PWM_ICR1_MODE						14
#define TIMER1_FAST_PWM_OCR1A_MODE						15

/* fast PWM0 OPTION*/
#define  PWM0_NON_INVERTING  0
#define  PWM0_INVERTING      1

/**********************************************************APIS PROTOTYPES*******************************************************************/
void PWM1_voidInit(void);
void PWM1_voidGeneratePWM (u16 copy_u16FrequencyHZ,f32 copu_f32DutyCycle);
void PWM1_voidStop (void);


#endif /* PWM1_INTERFACE_H_ */

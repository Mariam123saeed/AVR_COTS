/*
 * PWM1_program.c
 *
 *  Created on: Sep 14, 2024
 *      Author: Mariam
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PWM1_interface.h"
#include "PWM1_register.h"
#include "PWM1_config.h"

void PWM1_voidInit(void)
{
#if    TIMER1_MODE==TIMER1_FAST_PWM_ICR1_MODE
	/*Set Waveform generation mode as FAST_PWM_ICR1 mode */
		CLR_BIT(TCCR1A_REG,WGM10);
		SET_BIT(TCCR1A_REG,WGM11);
		SET_BIT(TCCR1B_REG,WGM12);
		SET_BIT(TCCR1B_REG,WGM13);
#endif
		/*Select non inverting pwm*/
		SET_BIT (TCCR1A_REG,COM1A1);
		CLR_BIT (TCCR1A_REG,COM1A0);
}
void PWM1_voidGeneratePWM (u16 copy_u16FrequencyHZ,f32 copu_f32DutyCycle)
{
	 if (copu_f32DutyCycle <= 100)
	 {
		 /*SET_DESIRED Freq*/
		 ICR1_REG = ((1000000UL/copy_u16FrequencyHZ)/4) - 1 ;
		 /*SET DUTY RATIO*/
		 OCR1A_REG = (((ICR1_REG+1)* copu_f32DutyCycle)/100) - 1;
		 /*set 64 prescaller*/
		 SET_BIT(TCCR1B_REG,CS10);
		 SET_BIT(TCCR1B_REG,CS11);
		 CLR_BIT(TCCR1B_REG,CS12);
	 }


}
void PWM1_voidStop (void)
{
	CLR_BIT(TCCR1B_REG,CS10);
	CLR_BIT(TCCR1B_REG,CS11);
	CLR_BIT(TCCR1B_REG,CS12);
}

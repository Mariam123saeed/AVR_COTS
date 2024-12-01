/*
 * PWM2_program.c
 *
 *  Created on: Sep 14, 2024
 *      Author: Mariam
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PWM2_interface.h"
#include "PWM2_register.h"
#include "PWM2_config.h"

void PWM2_voidInit(void)
{
	/*Initialize Waveform Generation Mode as fast PWM Mode*/
#if        TIMER2_MODE == TIMER2_FAST_PWM_MODE
	           SET_BIT(TCCR2_REG , WGM21) ;
		       SET_BIT(TCCR2_REG , WGM20) ;
    /*Initialize Waveform Generation Mode as PWM PHASE Mode*/
#elif      TIMER2_MODE == TIMER2_PWM_PHASE_MODE
		       CLR_BIT(TCCR2_REG , WGM21) ;
		       SET_BIT(TCCR2_REG , WGM20) ;
#else
			#error "Wrong TIMER2_WAVEFORM_GENERATION_MODE Config"
#endif
     /*Select non inverting pwm*/
#if    PWM0_OUTPUT_MODE == PWM2_NON_INVERTING
		       SET_BIT (TCCR2_REG,COM21);
		       CLR_BIT (TCCR2_REG,COM20);
     /*Select inverting pwm*/
#elif  PWM0_OUTPUT_MODE == PWM2_INVERTING
		       SET_BIT (TCCR2_REG,COM21);
		       SET_BIT (TCCR2_REG,COM20);
#else
			#error "Wrong TIMER2_PWM_OUTPUT_MODE Config"
#endif




}
void PWM2_voidGeneratePWM (u8 copu_u8DutyCycle)
{
	if (copu_u8DutyCycle <= 100)
	{
	    #if    PWM0_OUTPUT_MODE == PWM0_NON_INVERTING
		        OCR2_REG = ((copu_u8DutyCycle * 256) / 100) - 1;
	   #elif  PWM0_OUTPUT_MODE == PWM0_INVERTING
		        OCR0_REG = 255 - ((copu_u8DutyCycle * 256) / 100);
	   #endif
    }
	/*SET PRESCALLER VALUE*/
#if     TIMER2_PRESCALLER==TIMER2_NO_PRE
	      CLR_BIT (TCCR2_REG,CS22);
	      CLR_BIT (TCCR2_REG,CS21);
	      SET_BIT (TCCR2_REG,CS20);
#elif    TIMER2_PRESCALLER==TIMER2_8_PRE
	      CLR_BIT (TCCR2_REG,CS22);
	      SET_BIT (TCCR2_REG,CS21);
	      CLR_BIT (TCCR2_REG,CS20);
#elif    TIMER2_PRESCALLER==TIMER2_32_PRE
	      CLR_BIT (TCCR2_REG,CS22);
	      SET_BIT (TCCR2_REG,CS21);
	      SET_BIT (TCCR2_REG,CS20);
#elif    TIMER2_PRESCALLER==TIMER2_64_PRE
	      SET_BIT (TCCR2_REG,CS22);
	      CLR_BIT (TCCR2_REG,CS21);
	      CLR_BIT (TCCR2_REG,CS20);
#elif    TIMER2_PRESCALLER==TIMER2_128_PRE
	      SET_BIT (TCCR2_REG,CS22);
	      CLR_BIT (TCCR2_REG,CS21);
	      SET_BIT (TCCR2_REG,CS20);
#elif    TIMER2_PRESCALLER==TIMER2_256_PRE
	      SET_BIT (TCCR2_REG,CS22);
	      SET_BIT (TCCR2_REG,CS21);
	      CLR_BIT (TCCR2_REG,CS20);
#elif    TIMER2_PRESCALLER==TIMER2_1024_PRE
	      SET_BIT (TCCR2_REG,CS22);
	      SET_BIT (TCCR2_REG,CS21);
	      SET_BIT (TCCR2_REG,CS20);
#else
          #error "Wrong TIMER2_PRESCALLER Config"
#endif
}
void PWM2_voidStop (void)
{
	/*TIMER2_NO_CLOCK*/
	CLR_BIT (TCCR2_REG,CS22);
	CLR_BIT (TCCR2_REG,CS21);
    CLR_BIT (TCCR2_REG,CS20);
}

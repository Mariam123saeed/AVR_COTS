/*
 * PWM0_program.c
 *
 *  Created on: Sep 13, 2024
 *      Author: Mariam
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PWM0_interface.h"
#include "PWM0_register.h"
#include "PWM0_config.h"

void PWM0_voidInit(void)
{
	/*Initialize Waveform Generation Mode as fast PWM Mode*/
#if    PWM0_MODE==TIMER0_FAST_PWM_MODE
		SET_BIT(TCCR0_REG , WGM00) ;
		SET_BIT(TCCR0_REG , WGM01) ;
		/*Select non inverting pwm*/
      #if    FAST_PWM0_OUTPUT_MODE==PWM0_NON_INVERTING
		      CLR_BIT(TCCR0_REG,COM00);
		      SET_BIT(TCCR0_REG,COM01);
		 /*Select inverting pwm*/
     #elif  FAST_PWM0_OUTPUT_MODE==PWM0_INVERTING
		      SET_BIT(TCCR0_REG,COM00);
		      SET_BIT(TCCR0_REG,COM01);
     #else
			  #error "Wrong FAST_PWM0_OUTPUT_MODE Config"
     #endif
       /*Initialize Waveform Generation Mode as phase correct PWM Mode*/
#elif  PWM0_MODE==TIMER0_PWM_PHASE_MODE
		SET_BIT(TCCR0_REG , WGM00) ;
		CLR_BIT(TCCR0_REG , WGM01) ;
		/*Select non inverting pwm*/
	  #if    PHASE_PWM0_OUTPUT_MODE==PWM0_NON_INVERTING
			   CLR_BIT(TCCR0_REG,COM00);
		       SET_BIT(TCCR0_REG,COM01);
		/*Select inverting pwm*/
	  #elif   PHASE_PWM0_OUTPUT_MODE==PWM0_INVERTING
			    SET_BIT(TCCR0_REG,COM00);
			    SET_BIT(TCCR0_REG,COM01);
	  #else
			 #error "Wrong PHASE_CORRECT_PWM0_OUTPUT_MODE Config"
      #endif

#else
			#error "Wrong TIMER0_WAVEFORM_GENERATION_MODE Config"
#endif



}
void PWM0_voidGeneratePWM (u8 copu_u8DutyCycle)
{
   if (copu_u8DutyCycle <= 100)
	{
          #if    PWM0_OUTPUT_MODE == PWM0_NON_INVERTING
	                OCR0_REG = ((copu_u8DutyCycle * 256) / 100) - 1;
          #elif  PWM0_OUTPUT_MODE == PWM0_INVERTING
	                OCR0_REG = 255 - ((copu_u8DutyCycle * 256) / 100);
          #endif
	}
   /* Select prescaler value as 8 */
   #if    PWM0_PRESCALLER==TIMER0_8_PRE
            CLR_BIT(TCCR0_REG, CS00);
   	        SET_BIT(TCCR0_REG, CS01);
   	        CLR_BIT(TCCR0_REG, CS02);
	/* Select prescaler value as 64 */
   #elif    PWM0_PRESCALLER==TIMER0_64_PRE
	         SET_BIT(TCCR0_REG, CS00);
	         SET_BIT(TCCR0_REG, CS01);
	         CLR_BIT(TCCR0_REG, CS02);
	/* Select prescaler value as 256 */
   #elif   PWM0_PRESCALLER==TIMER0_256_PRE
	         CLR_BIT(TCCR0_REG, CS00);
	         CLR_BIT(TCCR0_REG, CS01);
	         SET_BIT(TCCR0_REG, CS02);
	/* Select prescaler value as 1024 */
   #elif   PWM0_PRESCALLER==TIMER0_1024_PRE
	         SET_BIT(TCCR0_REG, CS00);
	         CLR_BIT(TCCR0_REG, CS01);
	         SET_BIT(TCCR0_REG, CS02);
   #else
            #error "Wrong TIMER0_PRESCALLER Config"
   #endif

}
void PWM0_voidStop (void)
{
	/*TIMER0_NO_CLOCK*/
	CLR_BIT(TCCR0_REG,CS00);
	CLR_BIT(TCCR0_REG,CS01);
	CLR_BIT(TCCR0_REG,CS02);
}

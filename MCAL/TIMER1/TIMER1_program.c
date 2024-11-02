/*
 * TIMER1_program.c
 *
 *  Created on: Sep 7, 2024
 *      Author: Mariam
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER1_interface.h"
#include "TIMER1_register.h"
#include "TIMER1_config.h"
#include "TIMER1_private.h"

static void (*  PRV_pCallBackFuncOVR)(void)= NULL;
static void (*  PRV_pCallBackFuncCTC)(void)= NULL;
void TIMER1_voidInit(void)
{

#if    TIMER1_MODE==TIMER1_NORMAL_MODE
	/*Set Waveform generation mode as Normal mode */
		CLR_BIT(TCCR1A_REG,WGM10);
		CLR_BIT(TCCR1A_REG,WGM11);
		CLR_BIT(TCCR1B_REG,WGM12);
		CLR_BIT(TCCR1B_REG,WGM13);
	/*Timer1 Overflow Interrupt Enable*/
		SET_BIT(TIMSK_REG , TOIE1) ;
	/*Set the require Preload Value*/
		TCNT1_REG = TIMER1_PRELOAD_VAL ;
#elif  TIMER1_MODE==TIMER1_CTC_MODE
		/*Set Waveform generation mode as Normal mode */
	         CLR_BIT(TCCR1A_REG,WGM10);
			 CLR_BIT(TCCR1A_REG,WGM11);
			 SET_BIT(TCCR1B_REG,WGM12);
			 CLR_BIT(TCCR1B_REG,WGM13);

			 OCR1A_REG= TIMER1_OUTPUT_COMPARE_VALUE_A ;
#endif




}
void TIMER1_voidStart (void)
{
	SET_BIT(TCCR1B_REG,CS10);
	SET_BIT(TCCR1B_REG,CS11);
	CLR_BIT(TCCR1B_REG,CS12);
}

void TIMER1_voidStop (void)
{
	CLR_BIT(TCCR1B_REG,CS10);
	CLR_BIT(TCCR1B_REG,CS11);
	CLR_BIT(TCCR1B_REG,CS12);
}
void TIMER1_voidSetCallBack (void (* copy_ptrToFunction)(void),u8 copy_u8InterruptSrc)
{
	switch (copy_u8InterruptSrc)
	{
	  case TIMER1_NORMAL_MODE :
		if( copy_ptrToFunction!=NULL)
		{
			PRV_pCallBackFuncOVR = copy_ptrToFunction ;
		}
	   else
	    {
	       //return error status
	     }
	  break;
	case TIMER1_CTC_MODE :
	    if( copy_ptrToFunction!=NULL)
		 {
			PRV_pCallBackFuncCTC = copy_ptrToFunction;
		 }
		else
		 {
	        //return error status
		 }
		   break;
	}
}

//ISR TIMER1 (OVERFLOW)
void __vector_9(void) __attribute__ ((signal));
void __vector_9(void)
{
    static u8 local_u8Counter = 0;
    local_u8Counter++;

    if (TIMRE1_OVERFLOW_COUNTER == local_u8Counter)
    {
        TCNT1_REG = TIMER1_PRELOAD_VAL;
        local_u8Counter = 0;

        if (PRV_pCallBackFuncOVR != NULL)
        {
            PRV_pCallBackFuncOVR();
        }
    }
}

void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{
    static u8 local_u8Counter1 = 0;
    local_u8Counter1++;

    if (TIMRE1_CTC_COUNTER_A == local_u8Counter1)
    {
        local_u8Counter1 = 0;

        if (PRV_pCallBackFuncCTC != NULL)
        {
            PRV_pCallBackFuncCTC();
        }
    }
}



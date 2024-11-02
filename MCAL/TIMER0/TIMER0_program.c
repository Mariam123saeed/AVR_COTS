/*
 * TIMER0_program.c
 *
 *  Created on: Sep 6, 2024
 *      Author: Mariam
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER0_interface.h"
#include "TIMER0_register.h"
#include "TIMER0_config.h"
#include "TIMER0_private.h"

static void (*  PRV_CallBackFuncOvr)(void)= NULL;
static void (*  PRV_CallBackFuncCTC)(void)= NULL;
static u16 PRV_u16CTC_counter;
void TIMER0_voidInit(void)
{

#if    TIMER0_MODE==TIMER0_NORMAL_MODE
	   /*Initialize Waveform Generation Mode as Normal Mode*/
	CLR_BIT(TCCR0_REG , WGM00) ;
	CLR_BIT(TCCR0_REG , WGM01) ;

	/*Set the Required Preload Value*/
	TCNT0_REG = TIMER0_PRELOAD_VAL ;

	/*Timer0 Overflow Interrupt Enable*/
	SET_BIT(TIMSK_REG ,TOIE0) ;

#elif  TIMER0_MODE==TIMER0_CTC_MODE
	/*Initialize Waveform Generation Mode as PWM Mode*/
	  CLR_BIT(TCCR0_REG , WGM00) ;
	  SET_BIT(TCCR0_REG , WGM01) ;

	/*Timer0 Compare Match Interrupt Enable*/
	  SET_BIT(TIMSK_REG , OCIE0) ;

	/*Set the Required CTC Value*/
	  OCR0_REG = TIMER0_OUTPUT_COMPARE_VALUE ;
#else
			#error "Wrong TIMER0_WAVEFORM_GENERATION_MODE Config"

#endif

}
void TIMER0_voidSetCompareMatchDelayms (u16 copy_u16Delay_ms)
{

	    // Under condition: Tick time = 4us, OCR0 = 249
	    u32 local_u32TickTime;
	    OCR0_REG = 249;
	    //PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_ms * 1000 / ((249 + 1) * 4)); // *1000 to convert from ms to us

	#if TIMER0_PRESCALLER == TIMER0_8_PRE
	    local_u32TickTime = (u32)(8000000 / F_CPU);
	    PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_ms * 1000 / ((OCR0_REG + 1) * local_u32TickTime));
	#elif TIMER0_PRESCALLER == TIMER0_64_PRE
	    local_u32TickTime = (u32)((u32)64000000 / F_CPU);
	    PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_ms * 1000 / ((OCR0_REG + 1) * local_u32TickTime));
	#elif TIMER0_PRESCALLER == TIMER0_256_PRE
	    local_u32TickTime = (u32)((u32)256000000 / F_CPU);
	    PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_ms * 1000 / ((OCR0_REG + 1) * local_u32TickTime));
	#elif TIMER0_PRESCALLER == TIMER0_1024_PRE
	    local_u32TickTime = (u32)((u32)1024000000 / F_CPU);
	    PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_ms * 1000 / ((OCR0_REG + 1) * local_u32TickTime));
	#else
	    #error "Wrong TIMER0_PRESCALLER_Config"
	#endif

}
void TIMER0_voidSetCompareMatchDelayus (u16 copy_u16Delay_us)
{
	 u32 local_u32TickTime;
		    OCR0_REG = 249;


		#if TIMER0_PRESCALLER == TIMER0_8_PRE
		    local_u32TickTime = (u32)(8000000 / F_CPU);
		    PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_us / ((OCR0_REG + 1) * local_u32TickTime));
		#elif TIMER0_PRESCALLER == TIMER0_64_PRE
		    local_u32TickTime = (u32)((u32)64000000 / F_CPU);
		    PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_us  / ((OCR0_REG + 1) * local_u32TickTime));
		#elif TIMER0_PRESCALLER == TIMER0_256_PRE
		    local_u32TickTime = (u32)((u32)256000000 / F_CPU);
		    PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_us  / ((OCR0_REG + 1) * local_u32TickTime));
		#elif TIMER0_PRESCALLER == TIMER0_1024_PRE
		    local_u32TickTime = (u32)((u32)1024000000 / F_CPU);
		    PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_us  / ((OCR0_REG + 1) * local_u32TickTime));
		#else
		    #error "Wrong TIMER0_PRESCALLER_Config"
		#endif
}

void TIMER0_voidStart (void)
{
	SET_BIT(TCCR0_REG,CS00);
	SET_BIT(TCCR0_REG,CS01);
	CLR_BIT(TCCR0_REG,CS02);


}

void TIMER0_voidStop (void)
{
	CLR_BIT(TCCR0_REG,CS00);
	CLR_BIT(TCCR0_REG,CS01);
	CLR_BIT(TCCR0_REG,CS02);

}

void TIMER0_voidSetCallBack (void (* copy_ptrToFunction)(void),u8 copy_u8InterruptSrc)
{
	switch (copy_u8InterruptSrc)
	{
	case TIMER0_NORMAL_MODE :
		if( copy_ptrToFunction!=NULL)
		  {
		       PRV_CallBackFuncOvr = copy_ptrToFunction ;
		  }
		else
		  {
              //return error status
		  }
		break;
	case TIMER0_CTC_MODE :
	     if( copy_ptrToFunction!=NULL)
	      {
		     PRV_CallBackFuncCTC = copy_ptrToFunction;
	      }
	    else
	      {
                //return error status
	      }
	   break;



	}

}
//ISR TIMER0 (CTC)
void __vector_10(void) __attribute__ ((signal));
void __vector_10(void)
{
	static u16 local_u16Counter = 0;
		local_u16Counter++;

		if(PRV_u16CTC_counter  == local_u16Counter)
		{
			local_u16Counter = 0;
			if (PRV_CallBackFuncCTC!=NULL)
			{
				PRV_CallBackFuncCTC();
			}
		}
}

//ISR TIMER0 (OVERFLOW)
void __vector_11(void) __attribute__ ((signal));
void __vector_11(void)
{
	static u16 local_u16Counter = 0;
	local_u16Counter++;

	if(TMR0_OVERFLOW_COUNTER == local_u16Counter)
	{
		TCNT0_REG = TIMER0_PRELOAD_VAL;

		local_u16Counter = 0;
		if (PRV_CallBackFuncOvr!=NULL)
		{
			PRV_CallBackFuncOvr();
		}


	}
}

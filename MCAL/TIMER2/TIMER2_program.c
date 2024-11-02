/*
 * TIMER2_program.c
 *
 *  Created on: Sep 12, 2024
 *      Author: Mariam
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER2_interface.h"
#include "TIMER2_register.h"
#include "TIMER2_config.h"
#include "TIMER2_private.h"

/*Global Pointer to Function => Carry The Adress of ISR (Over flow) func in the main*/
static void (*  PRV_CallBackFuncOvr)(void)= NULL;
/*Global Pointer to Function => Carry The Adress of ISR (CTC) func in the main*/
static void (*  PRV_CallBackFuncCTC)(void)= NULL;
/*Global variable => SET Number of INT'S on CTC mode */
static u16 PRV_u16CTC_counter;
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function Init THE TIMER2
 * Parameters : Nothing
 * return : Nothing
 */
void TIMER2_voidInit(void)
{

#if    TIMER2_MODE==TIMER2_NORMAL_MODE
	   /*Initialize Waveform Generation Mode as Normal Mode*/
	       CLR_BIT(TCCR2_REG , WGM21) ;
	       CLR_BIT(TCCR2_REG , WGM20) ;

	  /*Set the Required Preload Value*/
	       TCNT2_REG = TIMER2_PRELOAD_VAL ;

	 /*Timer2 Overflow Interrupt Enable*/
	      SET_BIT(TIMSK_REG ,TOIE2) ;

#elif  TIMER2_MODE==TIMER2_CTC_MODE
	/*Initialize Waveform Generation Mode as PWM Mode*/
	     SET_BIT(TCCR2_REG , WGM21) ;
		 CLR_BIT(TCCR2_REG , WGM20) ;

	/*Timer2 Compare Match Interrupt Enable*/
	  SET_BIT(TIMSK_REG , OCIE2) ;

	/*Set the Required CTC Value*/
	  OCR2_REG  = TIMER2_OUTPUT_COMPARE_VALUE ;
#else
			#error "Wrong TIMER2_WAVEFORM_GENERATION_MODE Config"

#endif
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function Set the Prescaller value of  TIMER2
 * Parameters : Nothing
 * return : Nothing
 */
void TIMER2_voidStart (void)
{
	/*select the value of prescaller*/
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
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function Stopped TIMER2
 * Parameters : Nothing
 * return : Nothing
 */
void TIMER2_voidStop (void)
{
	/*TIMER2_NO_CLOCK*/
	CLR_BIT (TCCR2_REG,CS22);
    CLR_BIT (TCCR2_REG,CS21);
    CLR_BIT (TCCR2_REG,CS20);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function Set the delay value by milly_second
 * Parameters : copy_u16Delay_ms => delay value which desured by milly_second
 * return : Nothing
 */
void TIMER2_voidSetCompareMatchDelayms (u16 copy_u16Delay_ms)
{
	u32 local_u32TickTime;
    OCR2_REG = 249;
#if    TIMER2_PRESCALLER == TIMER2_8_PRE
	    local_u32TickTime = (u32)(8000000 / F_CPU);
	    PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_ms * 1000 / ((OCR2_REG + 1) * local_u32TickTime));

#elif   TIMER2_PRESCALLER == TIMER2_32_PRE
	    local_u32TickTime = (u32)(32000000 / F_CPU);
	    PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_ms * 1000 / ((OCR2_REG + 1) * local_u32TickTime));
#elif  TIMER2_PRESCALLER == TIMER2_64_PRE
	    local_u32TickTime = (u32)((u32)64000000 / F_CPU);
	    PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_ms * 1000 / ((OCR2_REG + 1) * local_u32TickTime));

#elif   TIMER2_PRESCALLER == TIMER2_128_PRE
	    local_u32TickTime = (u32)((u32)128000000 / F_CPU);
	    PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_ms * 1000 / ((OCR2_REG + 1) * local_u32TickTime));

#elif  TIMER2_PRESCALLER == TIMER2_256_PRE
	    local_u32TickTime = (u32)((u32)256000000 / F_CPU);
	    PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_ms * 1000 / ((OCR2_REG + 1) * local_u32TickTime));

#elif  TIMER2_PRESCALLER == TIMER2_1024_PRE
	    local_u32TickTime = (u32)((u32)1024000000 / F_CPU);
	    PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_ms * 1000 / ((OCR2_REG + 1) * local_u32TickTime));
#else
	    #error "Wrong TIMER2_PRESCALLER_Config"
#endif

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function Set the delay value by micro_second
 * Parameters : copy_u16Delay_ms => delay value which desured by micro_second
 * return : Nothing
 */
void TIMER2_voidSetCompareMatchDelayus (u16 copy_u16Delay_us)
{
	u32 local_u32TickTime;
	    OCR2_REG = 249;
	#if    TIMER2_PRESCALLER == TIMER2_8_PRE
		    local_u32TickTime = (u32)(8000000 / F_CPU);
		    PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_us / ((OCR2_REG + 1) * local_u32TickTime));

	#elif   TIMER2_PRESCALLER == TIMER2_32_PRE
		    local_u32TickTime = (u32)(32000000 / F_CPU);
		    PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_us / ((OCR2_REG + 1) * local_u32TickTime));
	#elif  TIMER2_PRESCALLER == TIMER2_64_PRE
		    local_u32TickTime = (u32)((u32)64000000 / F_CPU);
		    PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_us / ((OCR2_REG + 1) * local_u32TickTime));

	#elif   TIMER2_PRESCALLER == TIMER2_128_PRE
		    local_u32TickTime = (u32)((u32)128000000 / F_CPU);
		    PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_us / ((OCR2_REG + 1) * local_u32TickTime));

	#elif  TIMER2_PRESCALLER == TIMER2_256_PRE
		    local_u32TickTime = (u32)((u32)256000000 / F_CPU);
		    PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_us / ((OCR2_REG + 1) * local_u32TickTime));

	#elif  TIMER2_PRESCALLER == TIMER2_1024_PRE
		    local_u32TickTime = (u32)((u32)1024000000 / F_CPU);
		    PRV_u16CTC_counter = (u16)((u32)copy_u16Delay_us / ((OCR2_REG + 1) * local_u32TickTime));
	#else
		    #error "Wrong TIMER2_PRESCALLER_Config"
	#endif

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function Init THE TIMER2
 * Parameters :
				=> The Adress of ISR Func (* copy_ptrToFunction())
				=> copy_u8InterruptSrc --> [TIMER2_NORMAL_MODE , TIMER2_CTC_MODE]
 * return : Nothing
 */
void TIMER2_voidSetCallBack (void (* copy_ptrToFunction)(void),u8 copy_u8InterruptSrc)
{
	switch (copy_u8InterruptSrc)
	{
	case TIMER2_NORMAL_MODE :
		if( copy_ptrToFunction!=NULL)
		  {
		       PRV_CallBackFuncOvr = copy_ptrToFunction ;
		  }
		else
		  {
              //return error status
		  }
		break;
	case TIMER2_CTC_MODE :
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
//---------------------------------------------------------------------------------------------------------------------------------------------------
//ISR TIMER2 (CTC)
void __vector_4(void) __attribute__ ((signal));
void __vector_4(void)
{
	static u16 local_u16Counter = 0;
		local_u16Counter++;

		if(TIMER2_CTC_COUNTER   == local_u16Counter)
		{
			local_u16Counter = 0;
			if (PRV_CallBackFuncCTC!=NULL)
			{
				PRV_CallBackFuncCTC();
			}
		}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------

//ISR TIMER2 (OVERFLOW)
void __vector_5(void) __attribute__ ((signal));
void __vector_5(void)
{
	static u16 local_u16Counter = 0;
	local_u16Counter++;

	if(TIMER2_OVERFLOW_COUNTER == local_u16Counter)
	{
		TCNT2_REG = TIMER2_PRELOAD_VAL ;

		local_u16Counter = 0;
		if (PRV_CallBackFuncOvr!=NULL)
		{
			PRV_CallBackFuncOvr();
		}


	}
}

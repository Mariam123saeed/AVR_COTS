/*
 * EXTI_program.c
 *
 *  Created on: Aug 31, 2024
 *      Author: Mariam
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_register.h"

/*
	Global Pointer to Function => Carry The Adress of ISR func in the main
	Hint : I Made an array of pointers to carry EXTI 0,1,2 according to its index

*/
void (*EXTI_CallBack[3]) (void) = {NULL};

//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function Init THE EXTI
 * Parameters : copy_tIntSource -> {EXTI_INT0,EXTI_INT1,EXTI_INT2}
 *              copy_tIntSenceCtrl -> {EXTI_RISING_EDGE , EXTI_FALLING_EDGE , EXTI_LOW_LEVEL , EXTI_NO_CHANGE}
 * return : Nothing
 */
void EXTI_voidInit (EXTI_intSrc_t copy_tIntSource , EXTI_intSenceCtrl_t copy_tIntSenceCtrl )
{

	switch(copy_tIntSource)
		{
			case EXTI_INT0:
			switch(copy_tIntSenceCtrl)
			{
				case EXTI_RISING_EDGE:
				SET_BIT(MCUCR_REG, ISC00);
				SET_BIT(MCUCR_REG, ISC01);
				break;

				case EXTI_FALLING_EDGE:
				CLR_BIT(MCUCR_REG, ISC00);
				SET_BIT(MCUCR_REG, ISC01);
				break;

				case EXTI_LOW_LEVEL:
				CLR_BIT(MCUCR_REG, ISC00);
				CLR_BIT(MCUCR_REG, ISC01);
				break;

				case EXTI_NO_CHANGE:
				SET_BIT(MCUCR_REG, ISC00);
				CLR_BIT(MCUCR_REG, ISC01);
				break;
			}
			break;

			case EXTI_INT1:
			switch(copy_tIntSenceCtrl)
			{
				case EXTI_RISING_EDGE:
				SET_BIT(MCUCR_REG, ISC10);
				SET_BIT(MCUCR_REG, ISC11);
				break;

				case EXTI_FALLING_EDGE:
				CLR_BIT(MCUCR_REG, ISC10);
				SET_BIT(MCUCR_REG, ISC11);
				break;

				case EXTI_LOW_LEVEL:
				CLR_BIT(MCUCR_REG, ISC10);
				CLR_BIT(MCUCR_REG, ISC11);
				break;

				case EXTI_NO_CHANGE:
				SET_BIT(MCUCR_REG, ISC10);
				CLR_BIT(MCUCR_REG, ISC11);
				break;
			}
			break;

			case EXTI_INT2:
			switch(copy_tIntSenceCtrl)
			{
				case EXTI_RISING_EDGE:
				SET_BIT(MCUCSR_REG, ISC2);
				break;

				case EXTI_FALLING_EDGE:
				CLR_BIT(MCUCSR_REG, ISC2);
				break;
			}
			break;
		}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function ENABLE THE EXTI
 * Parameters : copy_tIntSource -> {EXTI_INT0,EXTI_INT1,EXTI_INT2}
 * return : Nothing
 */
void EXTI_voidEnable(EXTI_intSrc_t copy_tIntSource)
{
		switch(copy_tIntSource)
		{
			case EXTI_INT0:
			SET_BIT(GICR_REG, INT0);
			break;

			case EXTI_INT1:
			SET_BIT(GICR_REG, INT1);
			break;

			case EXTI_INT2:
			SET_BIT(GICR_REG, INT2);
			break;
		}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function DISABLE THE EXTI
 * Parameters : copy_tIntSource -> {EXTI_INT0,EXTI_INT1,EXTI_INT2}
 * return : Nothing
 */
void EXTI_voidDisable(EXTI_intSrc_t copy_tIntSource)
{
		switch(copy_tIntSource)
		{
			case EXTI_INT0:
			CLR_BIT(GICR_REG, INT0);
			break;

			case EXTI_INT1:
			CLR_BIT(GICR_REG, INT1);
			break;

			case EXTI_INT2:
			CLR_BIT(GICR_REG, INT2);
			break;
		}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function CLEAR the flag of EXTI
 * Parameters : copy_tIntSource -> {EXTI_INT0,EXTI_INT1,EXTI_INT2}
 * return : Nothing
 */

void EXTI_voidClearFlag ( EXTI_intSrc_t copy_tIntSource )
{
	switch(copy_tIntSource)
	{
		case EXTI_INT0: SET_BIT(GIFR_REG, INTF0);break;
		case EXTI_INT1: SET_BIT(GIFR_REG, INTF1);break;
		case EXTI_INT2: SET_BIT(GIFR_REG, INTF2);break;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function Init THE EXTI
 * Parameters :
				=> The Adress of ISR Func (copy_pvoidCallBack())
				=> copy_tIntSource --> [EXTI_INT0 , EXTI_INT1 , EXTI_INT2]
 * return : Nothing
 */
void EXTI_voidSetCallBack (void*(copy_pvoidCallBack)(void), EXTI_intSrc_t copy_tIntSource)
{
	switch (copy_tIntSource)
	{
		case EXTI_INT0 :
			if( copy_pvoidCallBack!=NULL)
			  {
				EXTI_CallBack[EXTI_INT0] = copy_pvoidCallBack ;
			  }
			else
			  {
	              //return error status
			  }
			break;
		case EXTI_INT1 :
		     if( copy_pvoidCallBack!=NULL)
		      {
		    	 EXTI_CallBack[EXTI_INT1] = copy_pvoidCallBack;
		      }
		    else
		      {
	                //return error status
		      }
		   break;
		case EXTI_INT2 :
			 if( copy_pvoidCallBack!=NULL)
			   {
				 EXTI_CallBack[EXTI_INT2] = copy_pvoidCallBack;
			   }
		      else
				{
			          //return error status
				 }
			break;
	}


}
//______________________________________________________

//ISR
void __vector_1(void) __attribute__ ((signal));
void __vector_1(void)
{
		 if(EXTI_CallBack !=NULL)
		 {
			 EXTI_CallBack [0]();  /*  Call The Global Pointer to Func   */
			 EXTI_voidClearFlag(EXTI_INT0);  /*Clear flag after execution */
		 }
}
void __vector_2(void) __attribute__ ((signal));
void __vector_2(void)
{
		 if(EXTI_CallBack !=NULL)
		 {
			 EXTI_CallBack [1]();
			 EXTI_voidClearFlag(EXTI_INT1);
		 }
}
void __vector_3(void) __attribute__ ((signal));
void __vector_3(void)
{
		 if(EXTI_CallBack !=NULL)
		 {
			 EXTI_CallBack [2]();
			 EXTI_voidClearFlag(EXTI_INT2);
		 }
}
//______________________________________________

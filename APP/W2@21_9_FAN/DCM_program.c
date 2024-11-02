/*
 * DCM_program.c
 *
 *  Created on: Sep 21, 2024
 *      Author: Mariam
 */

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */

#include "DIO_interface.h"
#include "PWM2_interface.h"

/* HAL */
#include "DCM_interface.h"
#include "DCM_config.h"

void DCM_voidInit (u8 copy_u8DcMotorSpeed , u8 copy_u8DcMotorNumber)
{
   switch (copy_u8DcMotorSpeed)
   {
      case DCM_WITH_CTRL_SREED :
    	  switch (copy_u8DcMotorNumber)
    	  {
    	    case DCM_A :
    	    	DIO_enumSetPinDirection(DCM_INPUT_1_PORT, DCM_INPUT_1_PIN, DIO_PIN_OUTPUT);//in_1
    	    	DIO_enumSetPinDirection(DCM_INPUT_2_PORT, DCM_INPUT_2_PIN, DIO_PIN_OUTPUT);//in_2

    	    break;
    	    case DCM_B :
    	    	DIO_enumSetPinDirection(DCM_INPUT_3_PORT, DCM_INPUT_3_PIN, DIO_PIN_OUTPUT);//in_3
    	    	DIO_enumSetPinDirection(DCM_INPUT_4_PORT, DCM_INPUT_4_PIN, DIO_PIN_OUTPUT);//in_4

    	    break;
    	  }
    	  DIO_enumSetPinDirection (DIO_PORTD,DIO_PIN7 , DIO_PIN_OUTPUT); //OC2
    	  PWM2_voidInit ();
      break;
      case DCM_WITHOUT_CTRL_SREED :
    	  switch (copy_u8DcMotorNumber)
    	  {
    	    case DCM_A :
    	      	 DIO_enumSetPinDirection(DCM_INPUT_1_PORT, DCM_INPUT_1_PIN, DIO_PIN_OUTPUT);//in_1
    	      	 DIO_enumSetPinDirection(DCM_INPUT_2_PORT, DCM_INPUT_2_PIN, DIO_PIN_OUTPUT);//in_2
    	      	 DIO_enumSetPinDirection(DCM_ENABLE_A_PORT, DCM_ENABLE_A_PIN, DIO_PIN_OUTPUT);//en_A
            break;
    	    case DCM_B :
    	      	 DIO_enumSetPinDirection(DCM_INPUT_3_PORT, DCM_INPUT_3_PIN, DIO_PIN_OUTPUT);//in_3
    	      	 DIO_enumSetPinDirection(DCM_INPUT_4_PORT, DCM_INPUT_4_PIN, DIO_PIN_OUTPUT);//in_4
    	      	 DIO_enumSetPinDirection(DCM_ENABLE_B_PORT, DCM_ENABLE_B_PIN, DIO_PIN_OUTPUT);//en_B
            break;
    	  }

      break;
   }

}

void DCM_voidOn   (u8 copy_u8DcMotorState, u8 copy_u8DcMotorNumber )
{

	    	  switch (copy_u8DcMotorNumber)
	    	  	{
	    	  	  case DCM_A:
	    	  	    switch (copy_u8DcMotorState)
	    	  		{
	    	  		  case DCMOTOR_CW :
	    	  			  DIO_enumSetPinValue(DCM_ENABLE_A_PORT, DCM_ENABLE_A_PIN, DIO_PIN_HIGH);//en_A
	    	  			  DIO_enumSetPinValue(DCM_INPUT_1_PORT, DCM_INPUT_1_PIN, DIO_PIN_HIGH);//in_1
	    	  			  DIO_enumSetPinValue(DCM_INPUT_2_PORT, DCM_INPUT_2_PIN, DIO_PIN_LOW);//in_2
	    	  		  break;
	    	  		  case DCMOTOR_CCW :
	    	  			  DIO_enumSetPinValue(DCM_ENABLE_A_PORT, DCM_ENABLE_A_PIN, DIO_PIN_HIGH);//en_A
	    	  			  DIO_enumSetPinValue(DCM_INPUT_1_PORT, DCM_INPUT_1_PIN, DIO_PIN_LOW);//in_1
	    	  			  DIO_enumSetPinValue(DCM_INPUT_2_PORT, DCM_INPUT_2_PIN, DIO_PIN_HIGH);//in_2
	    	  		  break;

	    	  		}
	    	  	 break;
	    	  	 case DCM_B:
	    	  	    switch (copy_u8DcMotorState)
	    	  	    {
	    	  	    	case DCMOTOR_CW :
	    	  	    	    DIO_enumSetPinValue(DCM_ENABLE_B_PORT, DCM_ENABLE_B_PIN, DIO_PIN_HIGH);//en_B
	    	  	    		DIO_enumSetPinValue(DCM_INPUT_3_PORT, DCM_INPUT_3_PIN, DIO_PIN_HIGH);//in_3
	    	  	    		DIO_enumSetPinValue(DCM_INPUT_4_PORT, DCM_INPUT_4_PIN, DIO_PIN_LOW);//in_4
	    	            break;
	    	  	    	case DCMOTOR_CCW :
	    	  	    	    DIO_enumSetPinValue(DCM_ENABLE_B_PORT, DCM_ENABLE_B_PIN, DIO_PIN_HIGH);//en_B
	    	  	    	    DIO_enumSetPinValue(DCM_INPUT_3_PORT, DCM_INPUT_3_PIN, DIO_PIN_LOW);//in_3
	    	  	    	    DIO_enumSetPinValue(DCM_INPUT_4_PORT, DCM_INPUT_4_PIN, DIO_PIN_HIGH);//in_4
	    	  	    	break;

	    	  	    }
	    	  	break;
	    	 }



}
void DCM_voidOnWithControlSpeed (u8 copy_u8DcMotorState, u8 copy_u8DcMotorNumber,u8 copy_u8DcMotorSpeed)
{
	switch (copy_u8DcMotorNumber)
	{
		 case DCM_A:
		      switch (copy_u8DcMotorState)
		        {
		    	   case DCMOTOR_CW :
	                    DIO_enumSetPinValue(DCM_INPUT_1_PORT, DCM_INPUT_1_PIN, DIO_PIN_HIGH);//in_1
		    	  	    DIO_enumSetPinValue(DCM_INPUT_2_PORT, DCM_INPUT_2_PIN, DIO_PIN_LOW);//in_2
		    	   break;
		    	   case DCMOTOR_CCW :
		    	  	    DIO_enumSetPinValue(DCM_INPUT_1_PORT, DCM_INPUT_1_PIN, DIO_PIN_LOW);//in_1
		    	  	    DIO_enumSetPinValue(DCM_INPUT_2_PORT, DCM_INPUT_2_PIN, DIO_PIN_HIGH);//in_2
		    	   break;

		    	 }
		  break;
		  case DCM_B:
		       switch (copy_u8DcMotorState)
		    	{
		    	  	case DCMOTOR_CW :
		    	  	     DIO_enumSetPinValue(DCM_INPUT_3_PORT, DCM_INPUT_3_PIN, DIO_PIN_HIGH);//in_3
		    	  	     DIO_enumSetPinValue(DCM_INPUT_4_PORT, DCM_INPUT_4_PIN, DIO_PIN_LOW);//in_4
		    	    break;
		    	  	case DCMOTOR_CCW :
		    	  	     DIO_enumSetPinValue(DCM_INPUT_3_PORT, DCM_INPUT_3_PIN, DIO_PIN_LOW);//in_3
		    	  	     DIO_enumSetPinValue(DCM_INPUT_4_PORT, DCM_INPUT_4_PIN, DIO_PIN_HIGH);//in_4
		    	  	break;

		    	 }
		  break;
     }
	PWM2_voidGeneratePWM (copy_u8DcMotorSpeed);
}
void DCM_voidOff   (u8 copy_u8DcMotorSpeed  , u8 copy_u8DcMotorNumber)
{
	switch (copy_u8DcMotorSpeed)
     {
		case DCM_WITH_CTRL_SREED :
			switch (copy_u8DcMotorNumber)
		     {
				 case DCM_A:
					 PWM2_voidStop();
			     break;
				 case DCM_B:
					 PWM2_voidStop();
				 break;
		     }
		break;
		case DCM_WITHOUT_CTRL_SREED :
			switch (copy_u8DcMotorNumber)
			{
			     case DCM_A:
			    	 DIO_enumSetPinValue(DCM_ENABLE_A_PORT, DCM_ENABLE_A_PIN, DIO_PIN_LOW);//en_A
			     break;
			     case DCM_B:
			    	 DIO_enumSetPinValue(DCM_ENABLE_B_PORT, DCM_ENABLE_B_PIN, DIO_PIN_LOW);//en_B
				break;
			}
	    break;
     }
}








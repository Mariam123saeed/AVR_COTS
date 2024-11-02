/*
 * DIO_program.c
 *
 *  Created on: Aug 10, 2024
 *      Author: Mariam
 */


#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "DIO_register.h"

//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function set the direction of the Pin  (INPUT || OUTPUT)
 * Parameters :
  	  =>Copy_u8PortID --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
  	  =>Copy_u8PinId  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
  	  =>Copy_u8PinDirection --> Pin Direction [ DIO_PIN_OUTPUT , DIO_PIN_INPUT ]

 */

DIO_Errorstatus DIO_enumSetPinDirection  (u8 copy_u8PortId , u8 copy_u8PinId , u8 copy_u8PinDirection)
{
	DIO_Errorstatus LOC_enumstate=DIO_OK;
	if((copy_u8PortId<=DIO_PORTD)&&(copy_u8PinId<=DIO_PIN7))
	{
		if(copy_u8PinDirection==DIO_PIN_OUTPUT)
		{
			 switch(copy_u8PortId)
			 {
			     case DIO_PORTA: SET_BIT(DDRA_REG,copy_u8PinId) ;  break;
			     case DIO_PORTB: SET_BIT(DDRB_REG,copy_u8PinId) ;  break;
			     case DIO_PORTC: SET_BIT(DDRC_REG,copy_u8PinId) ;  break;
			     case DIO_PORTD: SET_BIT(DDRD_REG,copy_u8PinId) ;  break;

			 }
		}
		else if(copy_u8PinDirection==DIO_PIN_INPUT)
		{
			switch(copy_u8PortId)
			  {
				   case DIO_PORTA: CLR_BIT(DDRA_REG,copy_u8PinId) ;  break;
				   case DIO_PORTB: CLR_BIT(DDRB_REG,copy_u8PinId) ;  break;
	 		       case DIO_PORTC: CLR_BIT(DDRC_REG,copy_u8PinId) ;  break;
			       case DIO_PORTD: CLR_BIT(DDRD_REG,copy_u8PinId) ;  break;

			 }
		}
		else
		{
				LOC_enumstate=DIO_OK;
		}
	}
	else
	{
		LOC_enumstate=DIO_OK;
	}
	return LOC_enumstate;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function set the value of the Pin  (HIGH || LOW)
 * Parameters :
  	  =>Copy_u8PortId --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
  	  =>Copy_u8PinId  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
  	  =>Copy_u8PinValue --> Pin Value [ DIO_HIGH , DIO_LOW ]
 */
DIO_Errorstatus DIO_enumSetPinValue      (u8 copy_u8PortId , u8 copy_u8PinId , u8 copy_u8PinValue)
{
	DIO_Errorstatus LOC_enumstate=DIO_OK;
   if((copy_u8PortId<=DIO_PORTD)&&(copy_u8PinId<=DIO_PIN7)&&((copy_u8PinValue==DIO_PIN_HIGH)||(copy_u8PinValue==DIO_PIN_LOW)))
   {
	   switch (copy_u8PortId)
	   {
	    case DIO_PORTA :
	    	switch(copy_u8PinValue)
	    	{
	    	  case DIO_PIN_HIGH :SET_BIT(PORTA_REG,copy_u8PinId);break;
	    	  case DIO_PIN_LOW  :CLR_BIT(PORTA_REG,copy_u8PinId);break;
	    	}
	    	break;
	    case DIO_PORTB :
	    	switch(copy_u8PinValue)
	    	{
	    	   case DIO_PIN_HIGH :SET_BIT(PORTB_REG,copy_u8PinId);break;
	    	   case DIO_PIN_LOW  :CLR_BIT(PORTB_REG,copy_u8PinId);break;
	    	}
	    	break;
	    case DIO_PORTC :
	    	switch(copy_u8PinValue)
	    	{
	    	   case DIO_PIN_HIGH :SET_BIT(PORTC_REG,copy_u8PinId);break;
	    	   case DIO_PIN_LOW  :CLR_BIT(PORTC_REG,copy_u8PinId);break;
	    	}
	    	break;
	    case DIO_PORTD :
	    	switch(copy_u8PinValue)
	    	{
	    	   case DIO_PIN_HIGH :SET_BIT(PORTD_REG,copy_u8PinId);break;
	    	   case DIO_PIN_LOW  :CLR_BIT(PORTD_REG,copy_u8PinId);break;
	    	}
	       break;
	   default :  LOC_enumstate=DIO_NOK;
	       break;
	  }
    }
    else
    {
	     LOC_enumstate=DIO_NOK;
    }
   return LOC_enumstate;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function get the value of the Pin
 * Parameters :
  	  =>Copy_u8PortId --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
  	  =>Copy_u8PinId  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
  	  =>*copy_u8PinValue --> pointer to recieve the pin value
 */
DIO_Errorstatus DIO_enumGetPinValue      (u8 copy_u8PortId , u8 copy_u8PinId , u8 *copy_u8PinValue)
{
	DIO_Errorstatus LOC_enumstate=DIO_OK;
	if((copy_u8PortId<=DIO_PORTD)&&(copy_u8PinId<=DIO_PIN7))
	{
		switch (copy_u8PortId)
		{
	  	    case DIO_PORTA : *copy_u8PinValue = GET_BIT (PINA_REG,copy_u8PinId);break;
	  	    case DIO_PORTB : *copy_u8PinValue = GET_BIT (PINB_REG,copy_u8PinId);break;
			case DIO_PORTC : *copy_u8PinValue = GET_BIT (PINC_REG,copy_u8PinId);break;
	  	    case DIO_PORTD : *copy_u8PinValue = GET_BIT (PIND_REG,copy_u8PinId);break;
	  	    default        : LOC_enumstate=DIO_NOK;                             break;
		}
	}
	else
	{
		LOC_enumstate=DIO_NOK;
	}
	return LOC_enumstate;

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function toggle the value of the Pin
 * Parameters :
  	  =>Copy_u8PortId --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
  	  =>Copy_u8PinId  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]

 */
DIO_Errorstatus DIO_enumTogglePinValue   (u8 copy_u8PortId , u8 copy_u8PinId )
{
	DIO_Errorstatus LOC_enumstate=DIO_OK;
	if(copy_u8PinId<=DIO_PIN7)
	{
		switch(copy_u8PortId)
		{
		     case DIO_PORTA : TOG_BIT (PORTA_REG,copy_u8PinId);break;
			 case DIO_PORTB : TOG_BIT (PORTB_REG,copy_u8PinId);break;
			 case DIO_PORTC : TOG_BIT (PORTC_REG,copy_u8PinId);break;
			 case DIO_PORTD : TOG_BIT (PORTD_REG,copy_u8PinId);break;
			 default        : LOC_enumstate=DIO_NOK;           break;
		}
	}
	else
	{
		LOC_enumstate=DIO_NOK;
	}
	return LOC_enumstate;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function set the direction of the Port  (INPUT || OUTPUT)
 * Parameters :
  	  =>Copy_u8PortID --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
  	  =>Copy_u8PortDirection --> Port Direction [ DIO_Port_OUTPUT , DIO_Port_INPUT ]

 */
DIO_Errorstatus DIO_enumSetPortDirection  (u8 copy_u8PortId , u8 copy_u8PortDirection)
{
	DIO_Errorstatus LOC_enumstate=DIO_OK;
	if((copy_u8PortId <= DIO_PORTD)&&((copy_u8PortDirection == DIO_PORT_OUTPUT) || (copy_u8PortDirection == DIO_PORT_INPUT)))
	{
		switch(copy_u8PortId)
		{
		  case DIO_PORTA :
			  switch(copy_u8PortDirection)
			  {
			    case DIO_PORT_INPUT  : DDRA_REG = 0x00; break;
			    case DIO_PORT_OUTPUT : DDRA_REG = 0xFF; break;
			  } break;
		  case DIO_PORTB :
			  switch(copy_u8PortDirection)
		      {
		       case DIO_PORT_INPUT  : DDRB_REG = 0x00; break;
		       case DIO_PORT_OUTPUT : DDRB_REG = 0xFF; break;
		      } break;
		  case DIO_PORTC :
			  switch(copy_u8PortDirection)
			  {
			  	case DIO_PORT_INPUT  : DDRC_REG = 0x00; break;
			  	case DIO_PORT_OUTPUT : DDRC_REG = 0xFF; break;
			  } break;
		  case DIO_PORTD :
			  switch(copy_u8PortDirection)
			  {
			  	 case DIO_PORT_INPUT  : DDRD_REG = 0x00; break;
			  	 case DIO_PORT_OUTPUT : DDRD_REG = 0xFF; break;
			  } break;
		  default        : LOC_enumstate=DIO_NOK;           break;
		}
	}
	else
	{
		LOC_enumstate=DIO_NOK;
	}
	return LOC_enumstate;

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function set the value of the Port  (HIGH || LOW)
 * Parameters :
  	  =>Copy_u8PortId --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
  	  =>Copy_u8PortValue --> Port Value [ DIO_HIGH , DIO_LOW ]
 */
DIO_Errorstatus DIO_enumSetPortValue      (u8 copy_u8PortId , u8 copy_u8PortValue)
{
	DIO_Errorstatus LOC_enumstate=DIO_OK;
	if ( (copy_u8PortId <= DIO_PORTD) && ( (copy_u8PortValue<=255) || (copy_u8PortValue==DIO_PORT_LOW) || (copy_u8PortValue==DIO_PORT_HIGH) ) )
		{
			switch(copy_u8PortId)
			{
				  case DIO_PORTA : PORTA_REG = copy_u8PortValue; break;
				  case DIO_PORTB : PORTB_REG = copy_u8PortValue; break;
				  case DIO_PORTC : PORTC_REG = copy_u8PortValue; break;
				  case DIO_PORTD : PORTD_REG = copy_u8PortValue; break;
				  default        : LOC_enumstate=DIO_NOK;        break;
			}
		}
		else
		{
			LOC_enumstate=DIO_NOK;
		}
		return LOC_enumstate;

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function get the value of the Port
 * Parameters :
  	  =>Copy_u8PortId --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
  	  =>*copy_u8PortValue --> pointer to recieve the port value
 */
DIO_Errorstatus DIO_enumGetPortValue      (u8 copy_u8PortId , u8 *copy_u8PortValue)
{
	DIO_Errorstatus LOC_enumstate=DIO_OK;
	if(copy_u8PortId<=DIO_PORTD)
	{
		switch (copy_u8PortId)
		{
		    case DIO_PORTA : *copy_u8PortValue =PINA_REG ;break;
		    case DIO_PORTB : *copy_u8PortValue =PINB_REG ;break;
		    case DIO_PORTC : *copy_u8PortValue =PINC_REG ;break;
		    case DIO_PORTD : *copy_u8PortValue =PIND_REG ;break;
		    default        : LOC_enumstate=DIO_NOK;       break;
		}
	}
	else
	{
		LOC_enumstate=DIO_NOK;
	}
	return LOC_enumstate;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function toggle the value of the Port
 * Parameters :
  	  =>Copy_u8PortId --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]


 */
DIO_Errorstatus DIO_enumTogglePortValue   (u8 copy_u8PortId )
{
	DIO_Errorstatus LOC_enumstate=DIO_OK;
	if(copy_u8PortId<=DIO_PORTD)
	{
		switch(copy_u8PortId)
		{
			 case DIO_PORTA :PORTA_REG = ~PORTA_REG ;break;
			 case DIO_PORTB :PORTB_REG = ~PORTB_REG ;break;
		     case DIO_PORTC :PORTC_REG = ~PORTC_REG ;break;
			 case DIO_PORTD :PORTD_REG = ~PORTD_REG ;break;
			 default        :LOC_enumstate=DIO_NOK;  break;
		}
	}
	else
	{
		LOC_enumstate=DIO_NOK;
	}
	return LOC_enumstate;

}
//----------------------------------------------------------------------------------------------------------------------------------------------
DIO_Errorstatus DIO_enumActivatePinInPUR  (u8 copy_u8PortId , u8 copy_u8PinId )
{
	DIO_Errorstatus LOC_enumstate=DIO_OK;
	if((copy_u8PortId<=DIO_PORTD)&&(copy_u8PinId<=DIO_PIN7))
	{
		switch(copy_u8PortId)
		{
		     case DIO_PORTA :SET_BIT(PORTA_REG,copy_u8PinId);break;
			 case DIO_PORTB :SET_BIT(PORTB_REG,copy_u8PinId);break;
			 case DIO_PORTC :SET_BIT(PORTC_REG,copy_u8PinId);break;
			 case DIO_PORTD :SET_BIT(PORTD_REG,copy_u8PinId);break;
			 default        :LOC_enumstate=DIO_NOK;          break;
		}
	}
	else
	{
		LOC_enumstate=DIO_NOK;
	}
	return LOC_enumstate;
}
//----------------------------------------------------------------------------------------------------------------------------------------------

DIO_Errorstatus DIO_enumActivePortInPullUpResistance(u8 copy_u8PortId)
{
	DIO_Errorstatus LOC_enumstate=DIO_OK;
		if(copy_u8PortId<=DIO_PORTD)
		{
			switch(copy_u8PortId)
			{
			    case DIO_PORTA: PORTA_REG = 0xFF; break;
			    case DIO_PORTB: PORTB_REG = 0xFF; break;
			    case DIO_PORTC: PORTC_REG = 0xFF; break;
			    case DIO_PORTD: PORTD_REG = 0xFF; break;
		    }
		}
		else
		{
			LOC_enumstate=DIO_NOK;
		}
		return LOC_enumstate;
}

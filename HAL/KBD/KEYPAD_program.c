/*
 * KEYPAD_program.c
 *
 *  Created on: Aug 23, 2024
 *      Author: Mariam
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "KEYPAD_interface.h"
#include "kEYPAD_config.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function initialize the pin which connected to KEYPAD as input pullup pins in case of rows
 *          and as output high initially in case of cols
 * Parameters : Nothing
 * return : Nothing
 */
void KEYPAD_voidInit      (void)
{
	     /*config rows pins as input pins then activete internal pull up*/

	    DIO_enumSetPinDirection (KEYPAD_R1_PORT ,KEYPAD_R1 ,DIO_PIN_INPUT);
		DIO_enumSetPinDirection (KEYPAD_R2_PORT ,KEYPAD_R2 ,DIO_PIN_INPUT);
		DIO_enumSetPinDirection (KEYPAD_R3_PORT ,KEYPAD_R3 ,DIO_PIN_INPUT);
		DIO_enumSetPinDirection (KEYPAD_R4_PORT ,KEYPAD_R4 ,DIO_PIN_INPUT);

		DIO_enumActivatePinInPUR(KEYPAD_R1_PORT ,KEYPAD_R1);
		DIO_enumActivatePinInPUR(KEYPAD_R2_PORT ,KEYPAD_R2);
		DIO_enumActivatePinInPUR(KEYPAD_R3_PORT ,KEYPAD_R3);
		DIO_enumActivatePinInPUR(KEYPAD_R4_PORT ,KEYPAD_R4);


		DIO_enumSetPinDirection (KEYPAD_C1_PORT ,KEYPAD_C1 ,DIO_PIN_OUTPUT);
		DIO_enumSetPinDirection (KEYPAD_C2_PORT ,KEYPAD_C2 ,DIO_PIN_OUTPUT);
		DIO_enumSetPinDirection (KEYPAD_C3_PORT ,KEYPAD_C3 ,DIO_PIN_OUTPUT);
		DIO_enumSetPinDirection (KEYPAD_C4_PORT ,KEYPAD_C4 ,DIO_PIN_OUTPUT);

		DIO_enumSetPinValue(KEYPAD_C1_PORT ,KEYPAD_C1 ,DIO_PIN_HIGH);
		DIO_enumSetPinValue(KEYPAD_C2_PORT ,KEYPAD_C2 ,DIO_PIN_HIGH);
		DIO_enumSetPinValue(KEYPAD_C3_PORT ,KEYPAD_C3 ,DIO_PIN_HIGH);
		DIO_enumSetPinValue(KEYPAD_C4_PORT ,KEYPAD_C4 ,DIO_PIN_HIGH);

}
//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function used to get the pressed button of the keypad
 * Parameters [out]: * copy_u8ReturnedValue ->> The ASCII of pressed key there is one
 * return : Nothing
 */
void   KEYPAD_voidGetValue  (u8 * copy_u8ReturnedValue)
{
 if(* copy_u8ReturnedValue!= NULL)
  {
	u8 local_u8ColCounter ,local_u8RowCounter ;
	u8 local_u8PinState;
	u8 local_u8ColPorts[4]={KEYPAD_C1_PORT,KEYPAD_C2_PORT,KEYPAD_C3_PORT,KEYPAD_C4_PORT};
	u8 local_u8ColPins [4]={KEYPAD_C1,KEYPAD_C2,KEYPAD_C3,KEYPAD_C4};
	u8 local_u8RowPorts[4]={KEYPAD_R1_PORT,KEYPAD_R2_PORT,KEYPAD_R3_PORT,KEYPAD_R4_PORT};
	u8 local_u8RowPins [4]={KEYPAD_R1,KEYPAD_R2,KEYPAD_R3,KEYPAD_R4};
	u8 local_u8KPD_Chars[4][4] = KPD_KEYS;


    	 * copy_u8ReturnedValue = KPD_NOT_PRESSED ;
         for(local_u8ColCounter=0 ; local_u8ColCounter<4 ; local_u8ColCounter++)
         {
        	 /*ACTIVATE EACH COL*/
        	 DIO_enumSetPinValue(local_u8ColPorts[local_u8ColCounter] ,local_u8ColPins[local_u8ColCounter] , DIO_PIN_LOW);

        	 for(local_u8RowCounter=0 ; local_u8RowCounter<4 ; local_u8RowCounter++)
        	 {
        		 /* Check Each Row (if == 0?) */
        		 DIO_enumGetPinValue(local_u8RowPorts[local_u8RowCounter] , local_u8RowPins [local_u8RowCounter],&local_u8PinState);
        		 /* Is Pressed? */
        		 if(0==local_u8PinState)
        		 {
        			 while(0==local_u8PinState)
        			 {
        				 DIO_enumGetPinValue(local_u8RowPorts[local_u8RowCounter] , local_u8RowPins [local_u8RowCounter],&local_u8PinState);

        			 }
        			 * copy_u8ReturnedValue = local_u8KPD_Chars[local_u8RowCounter][local_u8ColCounter];
   				     break;


        		 }

        	 }
        	 /*DEACTIVATE EACH COL*/
        	 DIO_enumSetPinValue(local_u8ColPorts[local_u8ColCounter] ,local_u8ColPins[local_u8ColCounter] , DIO_PIN_HIGH);
        	 if(local_u8RowCounter<4)
        	 {
        		 break;
        	 }
         }
    }
    else
    {
    	//error state
    }
}

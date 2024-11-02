/*
 * LCD_program.c
 *
 *  Created on: Aug 17, 2024
 *      Author: Mariam
 */

#define F_CPU 16000000UL
#include "util/delay.h"

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO_interface.h"


#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"
#include "LCD_extrachar.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function Apply initialization sequence for LCD module
* Parameters : nothing
* return : nothing
*/
LCD_voidInit               (void)
{
	DIO_enumSetPinDirection(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_OUTPUT);
	DIO_enumSetPinDirection(LCD_RW_PORT, LCD_RW_PIN, DIO_PIN_OUTPUT);
	DIO_enumSetPinDirection(LCD_EN_PORT ,LCD_EN_PIN , DIO_PIN_OUTPUT);
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     8 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#if    LCD_MODE ==  LCD_8_BIT_MODE
	// 1- must wait more than 30 ms before any action (VDD rises to 4.5 v)
		_delay_ms(50);

		// All Pins as OutPut pins
		DIO_enumSetPortDirection ( LCD_DATA_PORT, DIO_PORT_OUTPUT);

	    /*FUNCTION SET Command : 2 lines , 5*7 font size */
	    // set Rs pin = 0 (command)
	    DIO_enumSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_LOW);
	    // set RW pin = 0 (write)
	    DIO_enumSetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_PIN_LOW);
	    LCD_voidSendCommand( 0b001110000 ); // 8 Bit Mode ==> 0x70


	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      4 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#elif   LCD_MODE ==  LCD_4_BIT_MODE
	// Intialize LCD pins As OutPut Pins

		DIO_enumSetPinDirection(LCD_D4_PORT, LCD_D4_PIN, DIO_PIN_OUTPUT);
		DIO_enumSetPinDirection(LCD_D5_PORT, LCD_D5_PIN, DIO_PIN_OUTPUT);
		DIO_enumSetPinDirection(LCD_D6_PORT, LCD_D6_PIN, DIO_PIN_OUTPUT);
		DIO_enumSetPinDirection(LCD_D7_PORT, LCD_D7_PIN, DIO_PIN_OUTPUT);

		_delay_ms(35);

		/* Function Set (2Lines, 5*7 font)*/
			// set Rs pin = 0 (command)
			DIO_enumSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_LOW);
			// set RW pin = 0 (write)
			DIO_enumSetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_PIN_LOW);

			PRV_voidWriteHalfPort(0b0010);
			PRV_voidEnableTriggerWrite();
			LCD_voidSendCommand(0b00101000);



#endif
		_delay_us(45); // wait more than 39 Ms
	    /* DISPLAY & Cursor (ON / OFF) Control (Display On, Cursor On, Blink On*/
	    LCD_voidSendCommand( DisplayOn_CursorOn);
	    _delay_us(45);
	    /* DISPLAY CLEAR */
	    LCD_voidSendCommand(Clear_Display );
	   _delay_ms(2);
       /* Entery Mode Set (Increment on, Shift off) */
	    LCD_voidSendCommand(lcd_EntryMode);


}
//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send data to the port which is defined in config.h
* Parameters :
            => Copy_u8Data --> Data that you want to display (for every pixel )
* return : nothing
*/
void LCD_voidDisplayChar           (u8 copy_u8Data)
{
	    // set Rs pin = 1 (data)
		DIO_enumSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_HIGH);

		// set RW pin = 0 (write)
		DIO_enumSetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_PIN_LOW);
#if     LCD_MODE ==  LCD_8_BIT_MODE

		DIO_enumSetPortValue (LCD_DATA_PORT ,copy_u8Data);
		/* Enable */
		PRV_voidEnableTriggerWrite();

#elif   LCD_MODE == LCD_4_BIT_MODE

	    // Write The Most 4 bits Of data on Data Pins
		PRV_voidWriteHalfPort(copy_u8Data>>4);

		/* Enable */
		PRV_voidEnableTriggerWrite();

		// Write The Least 4 bits Of data on Data Pins
		PRV_voidWriteHalfPort(copy_u8Data);

		/* Enable */
		PRV_voidEnableTriggerWrite();
#endif

}
//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function Interface to send the configuration commands to the LCD Driver
* Parameters :
            => Copy_u8Command --> Command number
* return : nothing
*Hint : RS pin Mode is the difference between this function and the previous (LCD_voidSendData)
*/
void LCD_voidSendCommand        (u8 copy_u8Command)
{
	//set  RS pin =0 (COMMAND)
	DIO_enumSetPinValue  ( LCD_RS_PORT , LCD_RS_PIN , DIO_PIN_LOW  );
	//set  RW pin =0 (Write)
	DIO_enumSetPinValue  ( LCD_RW_PORT , LCD_RW_PIN , DIO_PIN_LOW  );
#if     LCD_MODE ==  LCD_8_BIT_MODE

		DIO_enumSetPortValue (LCD_DATA_PORT ,copy_u8Command);
		/* Enable */
		PRV_voidEnableTriggerWrite();

#elif   LCD_MODE == LCD_4_BIT_MODE
	/*Send MSB of data*/
	PRV_voidWriteHalfPort(copy_u8Command>>4);
	/*Enable*/
	PRV_voidEnableTriggerWrite();
	/*Send LSB of data*/
	PRV_voidWriteHalfPort(copy_u8Command);
	/*Enable*/
	PRV_voidEnableTriggerWrite();
#endif

}
//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function clear LCD
* Parameters : nothing
* return : nothing
*/
void LCD_voidClear                 (void)
{
	LCD_voidSendCommand (Clear_Display);
	_delay_ms(2);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send string to the port which is defined in config.h
* Parameters :
            => * Copy_u8ptrString  --> Pointer to the string
* return : nothing
*/
void LCD_voidSendString            (u8 *copy_u8PtrString)
{
	u8 local_u8Iterator=0;
	while (copy_u8PtrString[local_u8Iterator]!='\0')
	{
		LCD_voidDisplayChar (copy_u8PtrString[local_u8Iterator]);
		local_u8Iterator++;
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send number to the port which is defined in config.h
* Parameters :
            => Copy_u32Number --> number that you want to display
* return : nothing
*/
void LCD_voidSendNumber            (u32 copy_u32Number)
{
	u32 local_u32Reversed = 1 ;

		if( copy_u32Number == 0 ){ LCD_voidDisplayChar('0'); }

		else
		{

			while( copy_u32Number != 0 )
			{

				local_u32Reversed = ( local_u32Reversed * 10 ) + ( copy_u32Number % 10 );
				copy_u32Number /= 10 ;

			}
			while( local_u32Reversed != 1 )
			{

				LCD_voidDisplayChar( ( local_u32Reversed % 10 ) + 48 );
				local_u32Reversed /= 10 ;

			}

	  }

}
//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function shift the data on lcd
* Parameters :
            => copy_u8ShifttingDirection --> Command
* return : nothing

*/
void LCD_voidShift                 (u8 copy_u8ShifttingDirection)
{
	switch (copy_u8ShifttingDirection)
	{
	   case LCD_SHIFT_LEFT :
		   LCD_voidSendCommand(Display_shift_Left);
		   _delay_us(45);
		   break;
	   case LCD_SHIFT_RIGHT :
		   LCD_voidSendCommand(Display_shift_Right );
		   _delay_us(45);
		   break;

	}



}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void LCD_voidGoToSpecificPosition  (u8 copy_u8LineNumber, u8 copy_u8Position)
{

		if(copy_u8LineNumber>2||copy_u8LineNumber<1||copy_u8Position>16||copy_u8Position<1)
		{
			LCD_voidSendCommand(DDRAM_CONST );  //0x80
		}
		else if(copy_u8LineNumber==LCD_ROW_1)
		{
			LCD_voidSendCommand(DDRAM_CONST+(copy_u8Position));
		}
		else if(copy_u8LineNumber==LCD_ROW_2)
		{
			LCD_voidSendCommand(0b11000000+(copy_u8Position));  // 64 is dec of 0x40 the address of line2
		}

		_delay_ms(1);

}
//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send extra char
* Parameters :
            => copy_u8Row --> row number (LCD_ROW_1 or LCD_ROW_2)
			=> copy_u8Col --> column number (LCD_COL_1 ... LCD_COL_16)
* return : nothing
* Hint :-
	Address Counter can refer to CGRAM and DDRAM
*/
void LCD_voidSendExtraChar( u8 copy_u8Row , u8 copy_u8Col )
{

	u8 local_u8Iterator = 0 ;
	/* 1- Go To CGRAM            */
	LCD_voidSendCommand( CGRAM_CONST );  // Make AC refers to the first Place/Address at CGRAM


	/* 2- Draw Character in CGRAM        */
	/* Hint : it will be copied to DDRAM automatically */
	for(local_u8Iterator = 0 ;local_u8Iterator < sizeof(LCD_u8ExtraChar) / sizeof(LCD_u8ExtraChar[0]) ; local_u8Iterator++){

		LCD_voidDisplayChar( LCD_u8ExtraChar[local_u8Iterator] );

	}


	/* 3- Back (AC) To DDRAM          */
	LCD_voidGoToSpecificPosition(copy_u8Row,copy_u8Col);


	/* 4- Send Character Address */
	for( local_u8Iterator = 0 ; local_u8Iterator < 8 ; local_u8Iterator++ ){

		LCD_voidDisplayChar( local_u8Iterator );

	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function Interface to send data on 4_bit mode to the LCD Driver
* Parameters :
            => copu_u8Val --> Command / number
* return : nothing

*/
static void PRV_voidWriteHalfPort  (u8 copu_u8Val)
{
	if(0==GET_BIT(copu_u8Val,0))
	{
		DIO_enumSetPinValue (LCD_D4_PORT ,LCD_D4_PIN, DIO_PIN_LOW);
	}
	else
	{
		DIO_enumSetPinValue (LCD_D4_PORT ,LCD_D4_PIN, DIO_PIN_HIGH);
	}
	if(0==GET_BIT(copu_u8Val,1))
	{
		DIO_enumSetPinValue (LCD_D5_PORT ,LCD_D5_PIN,DIO_PIN_LOW);
	}
	else
	{
		DIO_enumSetPinValue (LCD_D5_PORT ,LCD_D5_PIN,DIO_PIN_HIGH);
	}
	if(0==GET_BIT(copu_u8Val,2))
	{
		DIO_enumSetPinValue (LCD_D6_PORT ,LCD_D6_PIN,DIO_PIN_LOW);
	}
	else
	{
		DIO_enumSetPinValue (LCD_D6_PORT ,LCD_D6_PIN,DIO_PIN_HIGH);
	}
	if(0==GET_BIT(copu_u8Val,3))
	{
		DIO_enumSetPinValue (LCD_D7_PORT ,LCD_D7_PIN,DIO_PIN_LOW);
	}
	else
	{
		DIO_enumSetPinValue (LCD_D7_PORT ,LCD_D7_PIN,DIO_PIN_HIGH);
	}
	/*
	    DIO_voidSetPinValue (LCD_D4_PORT ,LCD_D4_PIN,GET_BIT(copu_u8Val,0));
	    DIO_voidSetPinValue (LCD_D5_PORT ,LCD_D5_PIN,GET_BIT(copu_u8Val,1));
	    DIO_voidSetPinValue (LCD_D6_PORT ,LCD_D6_PIN,GET_BIT(copu_u8Val,2));
	    DIO_voidSetPinValue (LCD_D7_PORT ,LCD_D7_PIN,GET_BIT(copu_u8Val,3));
	*/
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send a pulse (falling edge ) to Enable Pin
* Parameters : nothing
* return : nothing
*
* Hint : static Function to forbid calling it out this file
*
*/
static void PRV_voidEnableTriggerWrite    (void)
{
	DIO_enumSetPinValue (LCD_EN_PORT ,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_enumSetPinValue (LCD_EN_PORT ,LCD_EN_PIN,DIO_PIN_LOW);
	_delay_ms(1);

}

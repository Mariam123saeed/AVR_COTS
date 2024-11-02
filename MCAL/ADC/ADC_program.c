/*
 * ADC_program.c
 *
 *  Created on: Aug 31, 2024
 *      Author: Mariam
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_register.h"


void ADC_voidInit(ADC_refVolt_t copy_tReferenceVoltage)
{
	switch(copy_tReferenceVoltage)
	{
	  case AVCC         : CLR_BIT(ADMUX_REG,REFS1);SET_BIT(ADMUX_REG,REFS0);break;
	  case AREF         : CLR_BIT(ADMUX_REG,REFS1);CLR_BIT(ADMUX_REG,REFS0);break;
	  case INTERNAL_2_56: SET_BIT(ADMUX_REG,REFS1);SET_BIT(ADMUX_REG,REFS0);break;

	}
	 CLR_BIT(ADMUX_REG,ADLAR);//select Right adjustment

	 CLR_BIT(ADCSRA_REG,ADATE); // ADC Auto Trigger disable

	 CLR_BIT(ADCSRA_REG,ADIE);  //ADC Interrupt disable

	 // Prescaler 128 For 16MHZ (128 KHZ)
	 	SET_BIT(ADCSRA_REG, ADPS0);
	 	SET_BIT(ADCSRA_REG, ADPS1);
	 	SET_BIT(ADCSRA_REG, ADPS2);

	 SET_BIT(ADCSRA_REG,ADEN);    //  ADC Enable


}
void ADC_voidGetDigitalValue(ADC_channelIds_t copy_tChannelId, u16* copy_pu16DigitalValue)
{
	if((copy_pu16DigitalValue != NULL)&&(copy_tChannelId <= 31))
	{
		//Clear ADMUX Channel Bits
		ADMUX_REG &= 0xE0 ; //0b11100000
		// Select Channel Number
		ADMUX_REG |= copy_tChannelId;

        /*ADC Start Conversion*/
		SET_BIT(ADCSRA_REG ,ADSC);

		// Busy Wait for ADC Flag  /* Time Out */
		while (0 == GET_BIT(ADCSRA_REG,ADIF));
		// Clear ADC flag (WROC >> Write One to Clear)
		SET_BIT(ADCSRA_REG,ADIF);
		// Pass out ADC data
		*copy_pu16DigitalValue=ADC_u16_REG;
	}
	else
	{
		//return error status
	}
	//return local_enumState;
}

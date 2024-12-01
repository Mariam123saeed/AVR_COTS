/*
 * ADC_interface.h
 *
 *  Created on: Aug 31, 2024
 *      Author: Mariam
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_
/* Enum for Reference Voltage */
typedef enum
{
	AVCC = 0,
	AREF,
	INTERNAL_2_56,
}ADC_refVolt_t;

/* Enum for Channel Number as Single Ended Input */
typedef enum
{
	ADC_CHANNEL_0 = 0,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_7,
}ADC_channelIds_t;

                 /*************** APIS PROTOTYPES ***************/

void ADC_voidInit           (ADC_refVolt_t copy_tReferenceVoltage);
void ADC_voidGetDigitalValue(ADC_channelIds_t copy_tChannelId, u16* copy_pu16DigitalValue);



#endif /* ADC_INTERFACE_H_ */

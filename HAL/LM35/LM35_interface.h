/*
 * LM35_interface.h
 *
 *  Created on: Sep 13, 2024
 *      Author: Mariam
 */

#ifndef LM35_INTERFACE_H_
#define LM35_INTERFACE_H_

#define ADC_RESOLUTION_10_BIT 0
#define ADC_RESOLUTION_8_BIT  1




typedef enum
{
	LM35_ADC_CHANNEL_0 = 0,
	LM35_ADC_CHANNEL_1,
	LM35_ADC_CHANNEL_2,
	LM35_ADC_CHANNEL_3,
	LM35_ADC_CHANNEL_4,
	LM35_ADC_CHANNEL_5,
	LM35_ADC_CHANNEL_6,
	LM35_ADC_CHANNEL_7,
}LM35_sensorChannel_t;

              /*************** APIS PROTOTYPES ***************/
void LM35_voidInit          (LM35_sensorChannel_t copy_tChannelId);
void LM35_voidGetTemperature(LM35_sensorChannel_t copy_tChannelId, u8* copy_u8Temperature);


#endif /* LM35_INTERFACE_H_ */

/*
 * ADC_register.h
 *
 *  Created on: Aug 31, 2024
 *      Author: Mariam
 */

#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

                                                          /************ADC REGISTERS**************************/
/*ADC Multiplexer Selection Register*/
#define ADMUX_REG       *((volatile u8*)0x27)
// ADMUX bits
#define REFS1   7      //Reference selection bit1
#define REFS0   6      //Reference selection bit0
#define ADLAR   5      // Left Adjust Result
#define MUX4    4
#define MUX3    3
#define MUX2    2
#define MUX1    1
#define MUX0    0
/*ADC Control and Status Register*/
#define ADCSRA_REG      *((volatile u8*)0x26)
// ADCSRA bits
#define ADEN    7      //  ADC Enable
#define ADSC    6      //  ADC Start Conversion
#define ADATE   5      //  ADC Auto Trigger Enable
#define ADIF    4      //  ADC Interrupt Flag
#define ADIE    3      //  ADC Interrupt Enable
#define ADPS2   2      //  ADC Prescaler Select Bit2
#define ADPS1   1      //  ADC Prescaler Select Bit1
#define ADPS0   0      //  ADC Prescaler Select Bit0

/***************************************/
//Data Registers
#define ADCH_REG        *((volatile u8*)0x25)
#define ADCL_REG       *((volatile u8*)0x24)
#define ADC_u16_REG     *((volatile u16*)0x24)

/***************************************/
#define  SFIOR_REG     *((volatile u8*)0x50)
//SFIOR bits
#define  ADTS2   7      //Auto Trigger Source bit2
#define  ADTS1   6      //Auto Trigger Source bit1
#define  ADTS0   5      //Auto Trigger Source bit0




#endif /* ADC_REGISTER_H_ */

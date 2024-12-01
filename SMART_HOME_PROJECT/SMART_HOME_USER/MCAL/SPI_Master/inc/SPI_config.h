/*
 * SPI_config.h
 *
 *  Created on: Oct 1, 2024
 *      Author: Mariam
 */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

/*Set Data Order
 * Options :-
 * 1. SPI_DATA_LSB_FIRST
 * 2. SPI_DATA_MSB_FIRST
 */
#define SPI_DATA_ORDER						SPI_DATA_LSB_FIRST

/*Select Master/Slave
 * Options :-
 * 1. SPI_MASTER
 * 2. SPI_SLAVE
 */
#define SPI_MASTER_SLAVE_SELECT			SPI_MASTER

/*Set Clock Polarity
 * Options :-
 * 1. SPI_RISING_LEADING_FALLING_TRAILING
 * 2. SPI_FALLING_LEADING_RISING_TRAILING
 */
#define SPI_CLK_POLARITY				SPI_FALLING_LEADING_RISING_TRAILING

/*Set Clock Phase
 * Options :-
 * 1. SPI_SAMPLE_LEADING_SETUP_TRAILING
 * 2. SPI_SETUP_LEADING_SAMPLE_TRAILING
 */
#define SPI_CLK_PHASE					SPI_SETUP_LEADING_SAMPLE_TRAILING

/*Set Clock Rate Divide
 * 1. SPI_FREQ_DIVIDED_BY_2
 * 2. SPI_FREQ_DIVIDED_BY_4
 * 3. SPI_FREQ_DIVIDED_BY_8
 * 4. SPI_FREQ_DIVIDED_BY_16
 * 5. SPI_FREQ_DIVIDED_BY_32
 * 6. SPI_FREQ_DIVIDED_BY_64
 * 7. SPI_FREQ_DIVIDED_BY_128
 */
#define SPI_CLK_RATE					SPI_FREQ_DIVIDED_BY_128

/*Set SPI Interrupt Enable
 * Options :-
 * 1. SPI_INTERRUPT_DISABLE
 * 2. SPI_INTERRUPT_ENABLE
 */
#define SPI_INTERRUPT_MODE			SPI_INTERRUPT_ENABLE

/*Set SPI Enable
 * Options :-
 * 1. SPI_DISABLE
 * 2. SPI_ENABLE
 */
#define SPI_ENABLE_MODE					SPI_ENABLE



#endif /* SPI_CONFIG_H_ */

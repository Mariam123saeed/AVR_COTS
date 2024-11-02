/*
 * TIMER1_config.h
 *
 *  Created on: Sep 7, 2024
 *      Author: Mariam
 */

#ifndef TIMER1_CONFIG_H_
#define TIMER1_CONFIG_H_

/* SET TIMER1 MODE*/
#define TIMER1_MODE            TIMER1_NORMAL_MODE

/* SET TIMER1 PRESCALLER*/
#define TIMER1_PRESCALLER      TIMER0_8_PRE

/* SET TIMER0 COMPARE MATCH OUTPUT MODE*/
#define TIMER1_OCR0_MODE       TIMER0_CLEAR_OC0

/* SET TIMER0 INTERRUPT*/
#define TIMER1_INTERRUPT       TIMER1_INT_DISABLE

#define        TIMER1_PRELOAD_VAL      60752

#define        TIMRE1_OVERFLOW_COUNTER			20
#define        TIMER1_OUTPUT_COMPARE_VALUE_A             5
#define       TIMRE1_CTC_COUNTER_A             5
#endif /* TIMER1_CONFIG_H_ */

/*
 * TIMER2_config.h
 *
 *  Created on: Sep 12, 2024
 *      Author: Mariam
 */

#ifndef TIMER2_CONFIG_H_
#define TIMER2_CONFIG_H_

/* SET TIMER2 MODE*/
#define TIMER2_MODE            TIMER2_CTC_MODE

/* SET TIMER2 PRESCALLER*/
#define TIMER2_PRESCALLER      TIMER2_64_PRE

/* SET TIMER2 Preload value when desired time 1sec*/
#define TIMER2_PRELOAD_VAL               113

/*Set the value of system clock*/
#define   F_CPU       16000000UL

/* SET Number of OVF when desired time 1sec*/
#define TIMER2_OVERFLOW_COUNTER			 977

/* SET TIMER2 OCR2 value when desired time 1.5sec*/
#define TIMER2_OUTPUT_COMPARE_VALUE      249

/* SET Number of INT'S when desired time 1.5sec*/
#define TIMER2_CTC_COUNTER               1500


#endif /* TIMER2_CONFIG_H_ */

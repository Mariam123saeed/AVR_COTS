/*
 * RTOS_private.h
 *
 *  Created on: Nov 1, 2024
 *      Author: Mariam
 */

#ifndef RTOS_PRIVATE_H_
#define RTOS_PRIVATE_H_


/* @brief Scheduler function for the RTOS.
 *  This function is responsible for managing task execution based on their periodicity.
 *  It will be set as the callback function for the TIMER2 interrupt. */
void PRV_voidScheduler (void);

#endif /* RTOS_PRIVATE_H_ */

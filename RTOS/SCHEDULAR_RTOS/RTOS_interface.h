/* * RTOS_interface.h
 * *  Created on: Nov 1, 2024
 * *      Author: Mariam
 */

#ifndef RTOS_INTERFACE_H_
#define RTOS_INTERFACE_H_

// Definition of the Task_t structure
typedef struct {
    u16 TaskPeriodicity;  // Task periodicity in ticks
    void (*TaskPtoFunc)(void);  // Pointer to the task function
    u8 TaskState;  // Task state (suspended or resumed)
} Task_t;

// Task states
#define RTOS_TASK_SUSBENDED     0  // Task suspended state
#define RTOS_TASK_RESUMED       1  // Task resumed state

/*********************************************************** APIS PROTOTYPES***********************************************************/

/**
 * @brief Starts the RTOS scheduler.
 * Initializes TIMER2 and sets the scheduler as its callback function.
 * Enables global interrupts and starts TIMER2.
 */
void RTOS_voidStartScheduilling(void);

/**
 * @brief Creates a new task in the RTOS.
 *
 * @param copy_u8Priorety Task priority (0 being the highest).
 * @param copy_u16Periodicity Task periodicity in ticks.
 * @param copy_pFuncTaskCode Pointer to the task function.
 */
void RTOS_voidCreatTask(u8 copy_u8Priorety, u16 copy_u16Periodicity, void (*copy_pFuncTaskCode)(void));

/**
 * @brief Deletes a task from the RTOS.
 *
 * @param copy_u8Priorety Task priority to delete.
 */
void RTOS_voidDeleteTask(u8 copy_u8Priorety);

/**
 * @brief Suspends a task in the RTOS.
 *
 * @param copy_u8Priorety Task priority to suspend.
 */
void RTOS_voidSusbendTask(u8 copy_u8Priorety);

/**
 * @brief Resumes a suspended task in the RTOS.
 *
 * @param copy_u8Priorety Task priority to resume.
 */
void RTOS_voidResumeTask(u8 copy_u8Priorety);

#endif /* RTOS_INTERFACE_H_ */

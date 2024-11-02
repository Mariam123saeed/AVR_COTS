/* * RTOS_program.c
 * *  Created on: Nov 1, 2024
 * *      Author: Mariam
 */
/*UTILS LIB*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/*MCAL*/
#include "GI_interface.h"
#include "TIMER2_interface.h"
/*RTOS*/
#include "RTOS_interface.h"
#include "RTOS_config.h"
#include "RTOS_private.h"

// Array to hold all tasks
static Task_t PRV_arrayoftasks[RTOS_TASK_NUM];

/**
 * @brief Starts the RTOS scheduler.
 * Enables global interrupts and initializes TIMER2.
 * Sets the callback function for TIMER2 and starts the timer.
 */
void RTOS_voidStartScheduilling(void)
{
	GI_voidEnable();                               // Enable global interrupts
	TIMER2_voidInit();                             // Initialize TIMER2
	TIMER2_voidSetCallBack(&PRV_voidScheduler, TIMER2_CTC_MODE); // Set TIMER2 callback function
	TIMER2_voidStart();                            // Start TIMER2 (SET Prescaller value)
}

/**
 * @brief Creates a new task in the RTOS.
 *
 * @param copy_u8Priorety ->> Priority of the task.
 * @param copy_u16Periodicity ->> Periodicity of the task.
 * @param copy_pFuncTaskCode ->> Pointer to the task function.
 */
void RTOS_voidCreatTask(u8 copy_u8Priorety, u16 copy_u16Periodicity, void (*copy_pFuncTaskCode)(void))
{
	// Check if priority is valid, function pointer is not NULL, and no task exists at the given priority
	if ((copy_u8Priorety < RTOS_TASK_NUM) && (copy_pFuncTaskCode != NULL) && (PRV_arrayoftasks[copy_u8Priorety].TaskPtoFunc == NULL))
	{
		PRV_arrayoftasks[copy_u8Priorety].TaskPtoFunc = copy_pFuncTaskCode;   // Assign task function
		PRV_arrayoftasks[copy_u8Priorety].TaskPeriodicity = copy_u16Periodicity; // Assign task periodicity
		PRV_arrayoftasks[copy_u8Priorety].TaskState = RTOS_TASK_RESUMED;      // Set task state to resumed
	}
	else
	{
		// Return error state
	}
}

/**
 * @brief Deletes a task from the RTOS.
 *
 * @param copy_u8Priorety ->> Priority of the task to delete.
 */
void RTOS_voidDeleteTask(u8 copy_u8Priorety)
{
	if (copy_u8Priorety < RTOS_TASK_NUM)
	{
		PRV_arrayoftasks[copy_u8Priorety].TaskPtoFunc = NULL; // Set task function to NULL to delete the task
	}
	else
	{
		// Return error state
	}
}

/**
 * @brief Suspends a task in the RTOS.
 *
 * @param copy_u8Priorety ->>Priority of the task to suspend.
 */
void RTOS_voidSusbendTask(u8 copy_u8Priorety)
{
	if (copy_u8Priorety < RTOS_TASK_NUM)
	{
		PRV_arrayoftasks[copy_u8Priorety].TaskState = RTOS_TASK_SUSBENDED; // Set task state to suspended
	}
	else
	{
		// Return error state
	}
}

/**
 * @brief Resumes a suspended task in the RTOS.
 *
 * @param copy_u8Priorety ->> Priority of the task to resume.
 */
void RTOS_voidResumeTask(u8 copy_u8Priorety)
{
	if (copy_u8Priorety < RTOS_TASK_NUM)
	{
		PRV_arrayoftasks[copy_u8Priorety].TaskState = RTOS_TASK_RESUMED; // Set task state to resumed
	}
	else
	{
		// Return error state
	}
}

/**
 * @brief Scheduler function to execute tasks based on their periodicity.
 * This function is called by the TIMER2 interrupt handler.
 */
void PRV_voidScheduler(void) {
	static u16 local_u16TickCounter = 0; // Counter to track ticks
	local_u16TickCounter++;              // Increment tick counter

	u8 local_u8TaskCounter;
	// Iterate through all tasks
	for (local_u8TaskCounter = 0; local_u8TaskCounter < RTOS_TASK_NUM; local_u8TaskCounter++)
	{
		// Check if it's time to execute the task
		if (local_u16TickCounter % (PRV_arrayoftasks[local_u8TaskCounter].TaskPeriodicity) == 0)
		{
			// Check if the task is resumed
			if (PRV_arrayoftasks[local_u8TaskCounter].TaskState == RTOS_TASK_RESUMED)
			{
				// Check if the task function is not NULL
				if (PRV_arrayoftasks[local_u8TaskCounter].TaskPtoFunc != NULL)
				{
					PRV_arrayoftasks[local_u8TaskCounter].TaskPtoFunc(); // Execute the task
				}
				else
				{
					// Return error state
				}
			}
			else
			{
				// Return error state
			}
		}
		else
		{
			// Return error state
		}
	}
}

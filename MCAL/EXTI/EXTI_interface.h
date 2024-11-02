/*
 * EXTI_interface.h
 *
 *  Created on: Aug 31, 2024
 *      Author: Mariam
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

// External_interrupt

typedef enum
{
	EXTI_INT0=0,
	EXTI_INT1,
	EXTI_INT2,

}EXTI_intSrc_t;

//----------------------------------------

// Sense_mode
typedef enum
{
	EXTI_RISING_EDGE=0,
	EXTI_FALLING_EDGE,
    EXTI_LOW_LEVEL,
	EXTI_NO_CHANGE,


}EXTI_intSenceCtrl_t;



/***********************************************************APIS PROT TYPES*******************************************************************/

void EXTI_voidInit      (EXTI_intSrc_t copy_tIntSource , EXTI_intSenceCtrl_t copy_tIntSenceCtrl );
void EXTI_voidEnable    (EXTI_intSrc_t copy_tIntSource );
void EXTI_voidDisable   (EXTI_intSrc_t copy_tIntSource );
void EXTI_voidClearFlag ( EXTI_intSrc_t copy_tIntSource );

void EXTI_voidSetCallBack (void*(copy_pvoidCallBack)(void), EXTI_intSrc_t copy_tIntSource);




#endif /* EXTI_INTERFACE_H_ */

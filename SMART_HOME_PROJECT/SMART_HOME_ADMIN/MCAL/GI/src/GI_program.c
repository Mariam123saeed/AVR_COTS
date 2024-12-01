/*
 * GI_program.c
 *
 *  Created on: Aug 31, 2024
 *      Author: Mariam
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GI_interface.h"
#include "GI_register.h"


void GI_voidEnable      (void)
{
	SET_BIT(SREG_REG , GIE);
}
void GI_voidDisable    (void)
{
	CLR_BIT(SREG_REG , GIE);
}

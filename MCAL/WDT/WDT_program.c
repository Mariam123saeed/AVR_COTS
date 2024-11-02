/*
 * WDT_program.c
 *
 *  Created on: Sep 21, 2024
 *      Author: Mariam
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "WDT_interface.h"
#include "WDT_register.h"


void WDC_voidEnable (WDT_Prescaller_t copy_tTimeOut)
{
	/*CLR prescaller bit*/
	WDTCR_REG &= (~(0b00000111));
	/*Select prescaller*/
	WDTCR_REG |= copy_tTimeOut;

		SET_BIT (WDTCR_REG,WDE);

}
void WDC_voidDisable (void)
{
	WDTCR_REG |= ( 1<<WDTOE  ) | (1<<WDE);
	 WDTCR_REG = 0x00;
}


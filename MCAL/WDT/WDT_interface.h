/*
 * WDT_interface.h
 *
 *  Created on: Sep 21, 2024
 *      Author: Mariam
 */

#ifndef WDT_INTERFACE_H_
#define WDT_INTERFACE_H_


typedef enum
{
	WDT_TIME_16_3_ms=0,
	WDT_TIME_32_5_ms,
	WDT_TIME_65_ms,
	WDT_TIME_0_13_s,
	WDT_TIME_0_26_s,
	WDT_TIME_0_52_s,
	WDT_TIME_1_0_s,
	WDT_TIME_2_1_s,

}WDT_Prescaller_t;


void WDC_voidEnable (WDT_Prescaller_t copy_tTimeOut);
void WDC_voidDisable (void);


#endif /* WDT_INTERFACE_H_ */

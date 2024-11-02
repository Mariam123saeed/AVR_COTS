/*
 * WDT_register.h
 *
 *  Created on: Sep 21, 2024
 *      Author: Mariam
 */

#ifndef WDT_REGISTER_H_
#define WDT_REGISTER_H_

#define WDTCR_REG             *((volatile u8 *)(0x41))
#define WDP0     0
#define  WDP1    1
#define  WDP2    2
#define  WDE     3
#define WDTOE    4

#endif /* WDT_REGISTER_H_ */

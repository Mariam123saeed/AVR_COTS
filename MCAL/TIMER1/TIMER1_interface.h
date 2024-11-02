/*
 * TIMER1_interface.h
 *
 *  Created on: Sep 7, 2024
 *      Author: Mariam
 */

#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

/* TIMER0 MODES*/

#define TIMER1_NORMAL_MODE          1
#define TIMER1_CTC_MODE             2
/**********************************************************APIS PROTOTYPES*******************************************************************/

void TIMER1_voidInit(void);
void TIMER1_voidStart (void);
void TIMER1_voidStop (void);
void TIMER1_voidSetCallBack (void (* copy_ptrToFunction)(void),u8 copy_u8InterruptSrc);

#endif /* TIMER1_INTERFACE_H_ */

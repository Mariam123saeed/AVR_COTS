/*
 * BIT_MATH.h
 *
 *  Created on:  Aug ,9 2024
 *      Author: Mariam
 */

#ifndef LIB_BIT_MATH_H_
#define LIB_BIT_MATH_H_

#define SET_BIT(REG,BIT_NUM) (REG |=(1<<BIT_NUM))
#define CLR_BIT(REG,BIT_NUM) (REG &=(~(1<<BIT_NUM)))
#define TOG_BIT(REG,BIT_NUM) (REG ^=(1<<BIT_NUM))
#define GET_BIT(REG,BIT_NUM) ((REG>>BIT_NUM)&1)      //OR :((REG &(1<<BIT_NUM))>>BIT_NUM)


#endif /* LIB_BIT_MATH_H_ */

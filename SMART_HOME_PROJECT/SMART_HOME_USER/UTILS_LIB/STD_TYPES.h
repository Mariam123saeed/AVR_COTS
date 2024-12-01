/*
 * STD_TYPES.h
 *
 *  Created on: Aug 9, 2024
 *      Author: Mariam
 */

#ifndef LIB_STD_TYPES_H_
#define LIB_STD_TYPES_H_

typedef unsigned char         u8;
typedef signed char           s8;
typedef unsigned short int    u16;
typedef signed short int      s16;
typedef unsigned long         u32;
typedef signed long           s32;
typedef unsigned long long    u64;
typedef signed long long      s64;

typedef float                 f32;
typedef double                f64;

typedef enum e
{
    FALSE,
    TRUE,
}BOOL;

#define  NULL        (void *)0
/* Func States  */
#define IDLE 			0
#define BUSY			1


#endif /* LIB_STD_TYPES_H_ */

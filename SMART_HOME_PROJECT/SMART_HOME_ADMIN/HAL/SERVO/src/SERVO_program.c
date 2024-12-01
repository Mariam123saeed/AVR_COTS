/*
 *   SERVO_program.c
 *
 *   Created on: Sep 21, 2024
 *   Author: Mariam
 *   */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "PWM1_interface.h"
/************************************************************************************************************************************************/
// Function to initialize the servo motor
void SERVO_voidInit(void)
{
    DIO_enumSetPinDirection(DIO_PORTD, DIO_PIN5, DIO_PIN_OUTPUT); // Set PD5 (OC1A) as output
    PWM1_voidInit(); // Initialize PWM1
}
/************************************************************************************************************************************************/
// Function to turn on the servo motor (set to 90 degrees)
void SERVO_voidOn(void)
{
    PWM1_voidGeneratePWM(50, 10); // Generate PWM signal with 10% duty cycle (+90 degrees)
}
/************************************************************************************************************************************************/
// Function to turn off the servo motor (stop PWM)
void SERVO_voidOff(void)
{
	PWM1_voidGeneratePWM(50, 7.5); // Generate PWM signal with 7.5% duty cycle (0 degrees)

}
/************************************************************************************************************************************************/
// Function to set the angle of the servo motor
void SERVO_voidSetPosition (s8 copy_s8Angle)
{
    // Ensure the input angle is within the valid range of -90 to +90
    if (copy_s8Angle < -90)
    {
        copy_s8Angle = -90;
    }
    else if (copy_s8Angle > 90)
    {
        copy_s8Angle = 90;
    }

    // Convert angle to duty cycle for PWM (mapping -90 to +90 degrees to 5-10% duty cycle)
    f32 local_f32DutyCycle = ((copy_s8Angle + 90) / 180.0f * 5.0f) + 5.0f;

    // Generate PWM signal with calculated duty cycle
    PWM1_voidGeneratePWM(50, local_f32DutyCycle); // Assuming 50Hz frequency for the servo motor
}

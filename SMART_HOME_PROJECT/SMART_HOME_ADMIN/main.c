#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

/* MCAL */
#include "DIO_interface.h"
#include "PWM1_interface.h"
#include "USART_interface.h"
#include "TWI_interface.h"
#include "GI_interface.h"
#include "EXTI_interface.h"
#include "SPI_interface.h"

/* HAL */
#include "EEPROM_interface.h"
#include "LCD_interface.h"
#include "KEYPAD_interface.h"
#include "SERVO_interface.h"
#include "SWITCH_interface.h"
#include "BUZZER_interface.h"

#include "ADMIN_interface.h"

int main(void)
{
    // Initialize system for Admin mode
    ADMIN_voidInit();

    // Perform login procedure
    ADMIN_voidLogIn();

    // Infinite loop to keep checking for user input
    while (1)
    {
        // The system waits for interrupts to be triggered and processes them
        // Admin menu or other system tasks could be added here
    }

    return 0;
}

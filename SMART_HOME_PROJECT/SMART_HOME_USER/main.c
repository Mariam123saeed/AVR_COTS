/*
 * main.c
 *
 *  Created on: Nov 27, 2024
 *      Author: Mariam
 */
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"
#include "PWM2_interface.h"
#include "PWM0_interface.h"
#include "ADC_interface.h"
#include "GI_interface.h"
#include "EXTI_interface.h"
#include "SPI_interface.h"
#include "USART_interface.h"

/* HAL */
#include "LCD_interface.h"
#include "LED_interface.h"
#include "KEYPAD_interface.h"
#include "DCM_interface.h"
#include "LM35_interface.h"
#include "SWITCH_interface.h"
#include "BUZZER_interface.h"

/* USER Program */
#include "USER_interface.h"

int main(void)
{
    // Initialization
    USER_voidInit();  // Initialize peripherals and configurations

    while (1)
    {
        // Display login mode options
        LCD_voidClear();
        LCD_voidSendString((u8 *)"Select Mode:");
        LCD_voidGoToSpecificPosition(LCD_ROW_2, LCD_COL_1);
        LCD_voidSendString((u8 *)"1: Local 2: Remote");

        u8 choice = KPD_NOT_PRESSED;

        // Wait for user to select a login mode
        do {
            KEYPAD_voidGetValue(&choice);
        } while (choice == KPD_NOT_PRESSED);

        // Process the selected mode
        if (choice == '1') {
            // Local Login
            LCD_voidClear();
            LCD_voidSendString((u8 *)"Local Login");
            _delay_ms(1000);
            USER_voidLogIn();  // Call the local login function
        } else if (choice == '2') {
            // Remote Login
            LCD_voidClear();
            LCD_voidSendString((u8 *)"Remote Login");
            _delay_ms(1000);
            USER_voidLogInRemotly();  // Call the remote login function
        } else {
            // Invalid input handling
            LCD_voidClear();
            LCD_voidSendString((u8 *)"Invalid Choice");
            _delay_ms(1000);
        }
    }

    return 0;
}

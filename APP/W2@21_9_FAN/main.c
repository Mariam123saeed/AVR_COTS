#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "ADC_interface.h"
#include "PWM2_interface.h"

#include "LCD_interface.h"
#include "LM35_interface.h"
#include "DCM_interface.h"

int main ()
{
    u8 local_u8TempValue;

    // Initialize the LCD, LM35 sensor, and PWM
    LCD_voidInit();
    LM35_voidInit(LM35_ADC_CHANNEL_0);
    DCM_voidInit  (DCM_WITH_CTRL_SREED,DCM_A);

    while(1)
    {
        // Get the temperature value from the LM35 sensor
        LM35_voidGetTemperature(LM35_ADC_CHANNEL_0, &local_u8TempValue);

        // Display the temperature value on the LCD
        LCD_voidSendString((u8*)"Temp is : ");
        LCD_voidSendNumber(local_u8TempValue);
        LCD_voidSendString((u8*)"C");

        // Add a delay to allow the user to read the value
        _delay_ms(2000);
        LCD_voidClear();

        if (local_u8TempValue < 20)
        {
        	DCM_voidOff( DCM_WITH_CTRL_SREED,DCM_A);  // Stop the motor
        }
        else if (local_u8TempValue >= 20 && local_u8TempValue < 25)
        {
             DCM_voidOnWithControlSpeed( DCMOTOR_CW,DCM_A,50);// 50% duty cycle
        }
        else if (local_u8TempValue >= 25 && local_u8TempValue < 30)
        {
        	 DCM_voidOnWithControlSpeed( DCMOTOR_CW,DCM_A,75); // 75% duty cycle
        }
        else if (local_u8TempValue >= 30 && local_u8TempValue < 35)
        {
        	 DCM_voidOnWithControlSpeed( DCMOTOR_CW,DCM_A,85);// 85% duty cycle

        }
        else if (local_u8TempValue >= 35)
        {
        	DCM_voidOn(DCMOTOR_CW, DCM_A); // 100% duty cycle
        }
        DCM_voidInit (DCM_WITHOUT_CTRL_SREED,DCM_B);
        DCM_voidOn(DCMOTOR_CW, DCM_B);
    }

    return 0;
}

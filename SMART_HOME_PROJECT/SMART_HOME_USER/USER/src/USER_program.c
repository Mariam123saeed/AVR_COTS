/*
 * USER_program.c
 *
 *  Created on: Nov 27, 2024
 *      Author: Mariam
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

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

#include "USER_interface.h"

#define MAX_USER_ID_LENGTH      3
#define MAX_PASSWORD_LENGTH     3
#define LOGIN_ATTEMPTS_LIMIT    3
#define MAX_RETRIES             5
#define SPI_MAX_RETRIES         3  // Maximum number of retries for SPI communication

/* Global Variables */

u8 global_u8UserCount = 0;
volatile u8 global_u8Lockdown = 0; // Indicates if the system is locked down
volatile u8 global_vu8SwitchPressed = 0; // Switch press flag for ISR
volatile u8 global_u8ResetState = 0; // Reset flag
BUZ_Type BUZ1 = {DIO_PORTA, DIO_PIN2, ACTIVE_HIGH};
volatile u8 SPI_Response=0;
volatile u8 SPI_CommandDone = 0; // Flag for SPI transaction completion


void USER_voidInit(void)
{
	// Initialize SPI as Master
	DIO_enumSetPinDirection(DIO_PORTB, DIO_PIN5, DIO_PIN_OUTPUT);   // MOSI
	DIO_enumSetPinDirection(DIO_PORTB, DIO_PIN6, DIO_PIN_INPUT);  // MISO
	DIO_enumSetPinDirection(DIO_PORTB, DIO_PIN7, DIO_PIN_OUTPUT);   // SCK
	DIO_enumSetPinDirection(DIO_PORTB, DIO_PIN4, DIO_PIN_OUTPUT);   // SS
	SPI_voidInit();

	// Initialize USART for debugging
	USART_voidInit();


	// Initialize ADC for dimmer LED control
	ADC_voidInit(AREF);

	// Initialize PWM (for dimmer LED)
	DIO_enumSetPinDirection(DIO_PORTB, DIO_PIN3, DIO_PIN_OUTPUT);  // OC0
	PWM0_voidInit();

	// Initialize peripherals
	BUZZER_voidInit(BUZ1);
	LCD_voidInit();
	KEYPAD_voidInit();



	LM35_voidInit(LM35_ADC_CHANNEL_0);
	DCM_voidInit(DCM_WITHOUT_CTRL_SREED, DCM_A);
	SWITCH_voidInit(DIO_PORTD, DIO_PIN2);

	// Configure External Interrupt INT0
	DIO_enumSetPinDirection(DIO_PORTD, DIO_PIN2, DIO_PIN_INPUT);  // INT0 pin as input
	EXTI_voidInit(EXTI_INT0, EXTI_FALLING_EDGE);
	EXTI_voidEnable(EXTI_INT0);
	EXTI_voidSetCallBack(&ISR_Reset, EXTI_INT0);

	// Enable global interrupts
	GI_voidEnable();

}


// User Login Function
void USER_voidLogIn(void) {
	u8 local_u8UserID[MAX_USER_ID_LENGTH] = {KPD_NOT_PRESSED, KPD_NOT_PRESSED, KPD_NOT_PRESSED};
	u8 local_u8UserPass[MAX_PASSWORD_LENGTH] = {KPD_NOT_PRESSED, KPD_NOT_PRESSED, KPD_NOT_PRESSED};
	u8 local_u8LoginAttempts = 0;

	LCD_voidClear();
	LCD_voidSendString((u8 *)"WELCOME :)");
	LCD_voidGoToSpecificPosition(LCD_ROW_2, LCD_COL_1);
	LCD_voidSendString((u8 *)"USER MODE..");
	_delay_ms(1000);

	while (local_u8LoginAttempts < LOGIN_ATTEMPTS_LIMIT)
	{
		// Collect User ID
		LCD_voidClear();
		LCD_voidSendString((u8 *)"Enter ID:");
		USER_voidGetInput(local_u8UserID, MAX_USER_ID_LENGTH);

		// Collect Password
		LCD_voidClear();
		LCD_voidSendString((u8 *)"Enter Pass:");
		USER_voidGetInput(local_u8UserPass, MAX_PASSWORD_LENGTH);
		_delay_ms(1000);

		// Send login data and receive response
		u8 response = USER_voidSendDataAndReceiveResponse(local_u8UserID, local_u8UserPass);

		if (response == 0x01) {  // Successful login
			LCD_voidClear();
			LCD_voidSendString((u8 *)"Login Success!");
			_delay_ms(1000);
			USER_voidUserMenu();  // Proceed to user menu
			return;
		}
		else
		{  // Invalid login
			LCD_voidClear();
			LCD_voidSendString((u8 *)"Invalid ID/Pass");
			_delay_ms(1000);
			local_u8LoginAttempts++;
		}
	}

	// Lock system after max attempts
	LCD_voidClear();
	LCD_voidSendString((u8 *)"System Locked");
	BUZZER_voidToggle(BUZ1);
	_delay_ms(2000);
	return;  // Return to the main menu or login function


}

// Function to collect user input (User ID or Password)
void USER_voidGetInput(u8 *copy_pu8Buffer, u8 copy_u8Length) {
	for (u8 local_u8Counter = 0; local_u8Counter < copy_u8Length; local_u8Counter++) {
		u8 keyPressed = KPD_NOT_PRESSED;
		do {
			KEYPAD_voidGetValue(&keyPressed);
			_delay_ms(50);  // Debouncing
		} while (keyPressed == KPD_NOT_PRESSED);

		if (keyPressed >= '0' && keyPressed <= '9') {
			copy_pu8Buffer[local_u8Counter] = keyPressed;
			LCD_voidDisplayChar('*');  // Mask input
		} else {
			local_u8Counter--;  // Retry for valid input
		}
	}
}


u8 USER_voidSendDataAndReceiveResponse(u8 *copy_pu8UserID, u8 *copy_pu8UserPass) {
	u8 SPI_Response = 0;
	u16 IntUserID = ((copy_pu8UserID[0] - '0') * 100) + ((copy_pu8UserID[1] - '0') * 10) + (copy_pu8UserID[2] - '0');
	u16 IntUserPass = ((copy_pu8UserPass[0] - '0') * 100) + ((copy_pu8UserPass[1] - '0') * 10) + (copy_pu8UserPass[2] - '0');
	u8 retryCount = 0;

	DIO_enumSetPinValue(DIO_PORTB, DIO_PIN4, DIO_PIN_LOW);  // Activate SS

	while (retryCount < SPI_MAX_RETRIES) {
		// Transmit data in sequence
		if (SPI_u8TrancieveData((u8)(IntUserID >> 8), NULL) &&
				SPI_u8TrancieveData((u8)(IntUserID & 0xFF), NULL) &&
				SPI_u8TrancieveData((u8)(IntUserPass >> 8), NULL) &&
				SPI_u8TrancieveData((u8)(IntUserPass & 0xFF), NULL)) {

			// Receive response from Admin
			if (SPI_u8TrancieveData(0xFF, &SPI_Response)) {
				break;  // Successful transmission
			}
		}
		retryCount++;
	}

	DIO_enumSetPinValue(DIO_PORTB, DIO_PIN4, DIO_PIN_HIGH);  // Deactivate SS

	if (retryCount >= SPI_MAX_RETRIES) {
		SPI_Response = 0x00;  // Return failure if retries exceeded
	}

	return SPI_Response;
}
void USER_voidLogInRemotly(void)
{
	u8 local_u8UserID[MAX_USER_ID_LENGTH] = {0};  // Buffer for User ID
	u8 local_u8UserPass[MAX_PASSWORD_LENGTH] = {0};  // Buffer for Password
	u8 local_u8LoginAttempts = 0;

	USART_voidTxString((u8 *)"Welcome to Remote Login!\r\n");

	while (local_u8LoginAttempts < LOGIN_ATTEMPTS_LIMIT)
	{
		// Prompt for User ID
		USART_voidTxString((u8 *)"Enter User ID (3 digits): ");
		USER_voidGetRemoteInput(local_u8UserID, MAX_USER_ID_LENGTH);

		// Prompt for Password
		USART_voidTxString((u8 *)"Enter Password (3 digits): ");
		USER_voidGetRemoteInput(local_u8UserPass, MAX_PASSWORD_LENGTH);

		// Send login data and receive response
		u8 response = USER_voidSendDataAndReceiveResponse(local_u8UserID, local_u8UserPass);

		if (response == 0x01)  // Successful login
		{
			USART_voidTxString((u8 *)"\r\nLogin Successful!\r\n");
			USER_voidUserMenuRemotly();  // Proceed to user menu
			return;
		}
		else  // Invalid login
		{
			USART_voidTxString((u8 *)"\r\nInvalid ID/Password.\r\n");
			local_u8LoginAttempts++;
		}
	}

	// Lock system after max attempts
	USART_voidTxString((u8 *)"System Locked due to too many invalid attempts.\r\n");
	BUZZER_voidToggle(BUZ1);  // Trigger buzzer
	while (1);  // Lock system indefinitely
}
void USER_voidGetRemoteInput(u8 *copy_pu8Buffer, u8 copy_u8Length)
{
	for (u8 local_u8Counter = 0; local_u8Counter < copy_u8Length; local_u8Counter++)
	{
		u8 keyPressed;
		USART_voidRxChar(&keyPressed);  // Receive character via USART

		if (keyPressed >= '0' && keyPressed <= '9')  // Validate numeric input
		{
			copy_pu8Buffer[local_u8Counter] = keyPressed;
			USART_voidTxChar('*');  // Echo a masked character
		}
		else
		{
			USART_voidTxString((u8 *)"\r\nInvalid Input! Enter a digit (0-9).\r\n");
			local_u8Counter--;  // Retry on invalid input
		}
	}
}

void USER_voidUserMenuRemotly(void)
{
	u8 local_u8Choice;
	while (1)
	{
		// Display user menu
		USART_voidTxString((u8 *)"\r\nUser Menu:");
		USART_voidTxString((u8 *)"\r\n1. Control LEDs");
		USART_voidTxString((u8 *)"\r\n2. Control Dimmer LED");
		USART_voidTxString((u8 *)"\r\n3. Control Air Condition");
		USART_voidTxString((u8 *)"\r\n4. Exit");
		USART_voidTxString((u8 *)"\r\nEnter your choice: ");
		USART_voidRxChar(&local_u8Choice);

		switch (local_u8Choice)
		{
		case '1':
			USER_voidControlLeds();
			break;
		case '2':
			USER_voidControlDimmerLed();
			break;
		case '3':
			USER_voidControlAirCondition();
			break;
		case '4':
			return;  // Exit user menu
		default:
			USART_voidTxString((u8 *)"\r\nInvalid choice, please try again.");
			break;
		}
	}

}
void USER_voidUserMenu(void)
{
	u8 local_u8Choice;

	while (1)
	{
		// Display the user menu
		LCD_voidClear();
		LCD_voidSendString((u8 *)"1: LEDs");
		LCD_voidGoToSpecificPosition(LCD_ROW_2, LCD_COL_1);  // Move to the second line
		LCD_voidSendString((u8 *)"2: Dim 3: AC 4:Exit");

		// Prompt user for choice
		LCD_voidClear();
		LCD_voidSendString((u8 *)"Choose: ");

		// Wait for valid input from Keypad
		do {
			KEYPAD_voidGetValue(&local_u8Choice);
		} while (local_u8Choice == KPD_NOT_PRESSED);

		// Process the choice
		switch (local_u8Choice)
		{
		case '1':  // Control LEDs
			LCD_voidClear();
			LCD_voidSendString((u8 *)"LED Control");
			USER_voidControlLeds();
			break;

		case '2':  // Control Dimmer LED
			LCD_voidClear();
			LCD_voidSendString((u8 *)"Dimmer Control");
			USER_voidControlDimmerLed();
			break;

		case '3':  // Control Air Conditioning
			LCD_voidClear();
			LCD_voidSendString((u8 *)"AC Control");
			USER_voidControlAirCondition();
			break;

		case '4':  // Exit Menu
			LCD_voidClear();
			LCD_voidSendString((u8 *)"Exiting Menu...");
			_delay_ms(1000);
			return;

		default:  // Invalid input
			LCD_voidClear();
			LCD_voidSendString((u8 *)"Invalid choice!");
			_delay_ms(1000);
			break;
		}
	}
}


void USER_voidControlLeds(void)
{
	u8 local_u8Choice;
	u8 ledStates[4] = {0, 0, 0, 0}; // Array to track LED states (0 = OFF, 1 = ON)

	// Initialize the LEDs (assuming LEDs are on PORTC, PINs 0–3)
	for (u8 pin = 0; pin < 4; pin++) {
		LED_voidInit(DIO_PORTC, pin); // Initialize LED i
	}

	while (1)
	{
		// Display the LED control menu
		LCD_voidClear();
		LCD_voidSendString((u8 *)"1:LED1 2:LED2");
		LCD_voidGoToSpecificPosition(LCD_ROW_2, LCD_COL_1); // Move to the second row
		LCD_voidSendString((u8 *)"3:LED3 4:LED4");

		// Wait for user input
		do {
			KEYPAD_voidGetValue(&local_u8Choice);
		} while (local_u8Choice == KPD_NOT_PRESSED);

		// Process user input to toggle the corresponding LED
		switch (local_u8Choice)
		{
		case '1': // Toggle LED1
			ledStates[0] = !ledStates[0]; // Update state
			if (ledStates[0]) {
				LED_voidOn(DIO_PORTC, DIO_PIN0, LED_FORWARD_CONNECTION);
			} else {
				LED_voidOff(DIO_PORTC, DIO_PIN0, LED_FORWARD_CONNECTION);
			}
			break;

		case '2': // Toggle LED2
			ledStates[1] = !ledStates[1];
			if (ledStates[1]) {
				LED_voidOn(DIO_PORTC, DIO_PIN1, LED_FORWARD_CONNECTION);
			} else {
				LED_voidOff(DIO_PORTC, DIO_PIN1, LED_FORWARD_CONNECTION);
			}
			break;

		case '3': // Toggle LED3
			ledStates[2] = !ledStates[2];
			if (ledStates[2]) {
				LED_voidOn(DIO_PORTC, DIO_PIN2, LED_FORWARD_CONNECTION);
			} else {
				LED_voidOff(DIO_PORTC, DIO_PIN2, LED_FORWARD_CONNECTION);
			}
			break;

		case '4': // Toggle LED4
			ledStates[3] = !ledStates[3];
			if (ledStates[3]) {
				LED_voidOn(DIO_PORTC, DIO_PIN3, LED_FORWARD_CONNECTION);
			} else {
				LED_voidOff(DIO_PORTC, DIO_PIN3, LED_FORWARD_CONNECTION);
			}
			break;

		case '#': // Exit the LED control loop
			return;

		default: // Handle invalid input
			LCD_voidClear();
			LCD_voidSendString((u8 *)"Invalid Input!");
			_delay_ms(1000);
			break;
		}

		// Update the LED statuses on the LCD
		LCD_voidClear();
		LCD_voidSendString((u8 *)"LED1:");
		LCD_voidSendString(ledStates[0] ? (u8 *)"ON " : (u8 *)"OFF");
		LCD_voidSendString((u8 *)" LED2:");
		LCD_voidSendString(ledStates[1] ? (u8 *)"ON " : (u8 *)"OFF");
		LCD_voidGoToSpecificPosition(LCD_ROW_2, LCD_COL_1);
		LCD_voidSendString((u8 *)"LED3:");
		LCD_voidSendString(ledStates[2] ? (u8 *)"ON " : (u8 *)"OFF");
		LCD_voidSendString((u8 *)" LED4:");
		LCD_voidSendString(ledStates[3] ? (u8 *)"ON " : (u8 *)"OFF");

		_delay_ms(500); // Short delay for stability
	}
}

void USER_voidControlDimmerLed(void)
{
	u16 ADC_Value = 0;  // Variable to hold ADC reading
	u8 DutyCycle = 0;  // Variable to store calculated duty cycle

	while (1)
	{
		// Read the input voltage from the ADC (assuming channel 0)
		ADC_voidGetDigitalValue(ADC_CHANNEL_1, &ADC_Value);

		// Convert ADC value (0-1023) to duty cycle (0-100%)
		DutyCycle = (u8)((ADC_Value * 100) / 1023);

		// Generate PWM signal with the calculated duty cycle
		PWM0_voidGeneratePWM(DutyCycle);

		// Turn on the LED (with brightness controlled by PWM)
		DIO_enumSetPinDirection(DIO_PORTD, DIO_PIN3, DIO_PIN_OUTPUT);

		// Optional: Display the duty cycle on the LCD for debugging
		LCD_voidClear();
		LCD_voidSendString((u8 *)"Brightness:");
		LCD_voidSendNumber(DutyCycle);
		LCD_voidSendString((u8 *)"%");

		_delay_ms(500);  // Delay to reduce flickering and allow updates
	}
}
void USER_voidControlAirCondition(void)
{
	u8 local_u8TempValue;
	while (1)
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

		if (local_u8TempValue > 28)
		{
			DCM_voidOn( DCMOTOR_CW,DCM_A);  // Turn on the Air condition
		}
		else if ( local_u8TempValue < 21)
		{
			DCM_voidOff( DCM_WITHOUT_CTRL_SREED,DCM_A);  // Turn off the Air condition
		}
	}
}


void ISR_Reset(void)
{

	// Simple debounce: wait for a short delay to ensure the button press is stable
	_delay_ms(50);  // Add a small delay (50 ms for example)

	if (global_vu8SwitchPressed == 0)
	{  // Check if switch press is valid
		global_vu8SwitchPressed = 1;  // Set the flag
		// Reset the system

		// Deactivate the alarm
		BUZZER_voidOff(BUZ1);

		// Clear lockdown state and reset necessary variables
		global_u8Lockdown = 0;
		global_vu8SwitchPressed = 0; // Reset switch press flag
		global_u8ResetState = 1; // Indicate that the system was reset
		global_u8UserCount = 0; // Reset user count if needed


		// Perform necessary reset actions
		LCD_voidClear();
		LCD_voidSendString((u8 *)"System Reset!");
		// Reset peripherals or variables if required
		USER_voidLogIn(); // Return to user login

	}
}

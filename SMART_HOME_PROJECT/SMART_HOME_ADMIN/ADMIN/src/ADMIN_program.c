/*
 * ADMIN_program.c
 *
 *  Created on: Nov 25, 2024
 *      Author: Mariam
 */

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

#define MAX_USERS               8
#define ADMIN_PASS           "1234"
#define ADMIN_USERNAME       "Admin"
#define MAX_NUM_OF_PASS         3
#define MAX_NUM_OF_USERNAME     10
#define EEPROM_DEFAULT_VALUE  0xFF
#define LOGIN_ATTEMPTS_LIMIT    3

/* Global Variables */
u8 global_u8UserCount = 0;
volatile u8 global_u8Lockdown = 0; // Indicates if the system is locked down
volatile u8 global_vu8SwitchPressed = 0; // Switch press flag for ISR
volatile u8 global_u8ResetState = 0; // Reset flag, indicates if the system is just reset
BUZ_Type BUZ1 = {DIO_PORTA, DIO_PIN2, ACTIVE_HIGH};
volatile u8 SPI_Response = 0;
volatile u8 dataReceivedFlag = 0; // Flag to indicate data reception completion
typedef enum {
	SYSTEM_STATE_ADMIN,
	SYSTEM_STATE_USER
} SystemState;

volatile SystemState global_state = SYSTEM_STATE_ADMIN;

void ADMIN_voidInit(void) {
	// Initialize system components
	// slave configuration
	DIO_enumSetPinDirection(DIO_PORTB, DIO_PIN5, DIO_PIN_INPUT);  // MOSI
	DIO_enumSetPinDirection(DIO_PORTB, DIO_PIN6, DIO_PIN_OUTPUT);   // MISO
	DIO_enumSetPinDirection(DIO_PORTB, DIO_PIN7, DIO_PIN_INPUT);  // SCK
	DIO_enumSetPinDirection(DIO_PORTB, DIO_PIN4, DIO_PIN_INPUT);  // SS
	DIO_enumSetPinValue(DIO_PORTB, DIO_PIN4, DIO_PIN_HIGH);

	// Initialize SPI as Master
	SPI_voidInit();

	BUZZER_voidInit(BUZ1);
	USART_voidInit();
	EEPROM_voidInit();
	SERVO_voidInit();
	SERVO_voidOff();
	SWITCH_voidInit(DIO_PORTD, DIO_PIN2);

	// Configure INT0 (external interrupt)
	DIO_enumSetPinDirection(DIO_PORTD, DIO_PIN2, DIO_PIN_INPUT); // Set external interrupt pin as input
	EXTI_voidInit(EXTI_INT0, EXTI_FALLING_EDGE); // Configure INT0 to trigger on a falling edge (button press)
	EXTI_voidEnable(EXTI_INT0);  // Enable external interrupt

	// Set the callback for INT0
	EXTI_voidSetCallBack(&ISR_Reset, EXTI_INT0);

	// Enable global interrupt
	GI_voidEnable();

	// Configure EXTI for INT1 - Trigger on falling edge
	DIO_enumSetPinDirection(DIO_PORTD, DIO_PIN3, DIO_PIN_INPUT);
	DIO_enumSetPinValue(DIO_PORTD, DIO_PIN3, DIO_PIN_HIGH);
	EXTI_voidInit(EXTI_INT1, EXTI_FALLING_EDGE);  // Configure INT1 to trigger on a falling edge
	EXTI_voidEnable(EXTI_INT1);  // Enable external interrupt for INT1

	// Set the callback for INT1 (ISR for INT1)
	EXTI_voidSetCallBack(&ISR_UserDataReceived, EXTI_INT1);

	// Enable global interrupts
	GI_voidEnable();
}
void ADMIN_voidLogIn(void)
{
	u8 local_u8AdminUsername[MAX_NUM_OF_USERNAME];
	u8 local_u8AdminPass[MAX_NUM_OF_PASS + 1];
	u8 loginAttempts = 0;
	u8 isUsernameCorrect;
	u8 isPasswordCorrect;

	while (loginAttempts < LOGIN_ATTEMPTS_LIMIT)
	{
		isUsernameCorrect = 1; // Assume the username is correct initially
		isPasswordCorrect = 1; // Assume the password is correct initially
		USART_voidTxString((u8 *)"\r\nWelcome in ADMIN MODE:\r\nEnter Admin Username: ");
		USART_voidRxString(local_u8AdminUsername);
		// Check if the username matches
		for (u8 local_u8Counter = 0; ADMIN_USERNAME[local_u8Counter] != '\0'; local_u8Counter++)
		{
			if (local_u8AdminUsername[local_u8Counter] != ADMIN_USERNAME[local_u8Counter])
			{
				isUsernameCorrect = 0;
				break;
			}
		}

		if (!isUsernameCorrect)
		{
			USART_voidTxString((u8 *)"\r\nIncorrect Username.");
			loginAttempts++;
			continue;
		}

		USART_voidTxString((u8 *)"\r\nEnter Admin Password: ");
		USART_voidRxString(local_u8AdminPass);
		// Compare the entered password with the stored password
		for (u8 local_u8Counter = 0; local_u8Counter < MAX_NUM_OF_PASS; local_u8Counter++)
		{
			if (local_u8AdminPass[local_u8Counter] != ADMIN_PASS[local_u8Counter])
			{
				isPasswordCorrect = 0; // Password mismatch
				break;
			}
		}

		if (isPasswordCorrect)
		{
			USART_voidTxString((u8 *)"\r\nLogin Successful!");
			ADMIN_voidAdminMenu();
			return; // Exit after successful login
		}
		else
		{
			loginAttempts++;
			USART_voidTxString((u8 *)"\r\nIncorrect Password.");
		}
	}

	// Too many attempts, lock the system
	USART_voidTxString((u8 *)"\r\nToo many incorrect attempts! System locked.\r\n");
	BUZZER_voidToggle(BUZ1);
	while (1); // Lock the system indefinitely
}

void ADMIN_voidAdminMenu(void)
{
	u8 local_u8AdminChoice;

	while (1)
	{
		// Check for user data interrupt
		if (global_state == SYSTEM_STATE_USER) {
			return;  // Exit admin menu and allow user data processing
		}

		ADMIN_voidDisplayAdminMenu();
		USART_voidTxString((u8 *)"\r\nEnter your choice...");
		USART_voidRxChar(&local_u8AdminChoice);

		switch (local_u8AdminChoice) {
		case '1':
			ADMIN_voidAddUser();
			break;
		case '2':
			ADMIN_voidDeleteUser();
			break;
		case '3':
			ADMIN_voidEditUser();
			break;
		case '4':
			ADMIN_voidDisplayAllUsers();
			break;
		case '5':
			ADMIN_voidOpenDoor();
			break;
		case '6':
			ADMIN_voidCloseDoor();
			break;
		case '7':
			USART_voidTxString((u8 *)"\r\nReturning to Main Menu...");
			return;
		default:
			USART_voidTxString((u8 *)"\r\nInvalid Choice. Please Try Again.");
			break;
		}
	}
}
void ADMIN_voidAddUser(void)
{
	if (global_u8UserCount < MAX_USERS)
	{
		u8 local_u8UserID[MAX_NUM_OF_PASS];  // User input for ID as string
		u8 local_u8UserPass[MAX_NUM_OF_PASS];  // User input for Password as string
		u16 intUserID;    // Integer representation of User ID
		u16 intUserPass;  // Integer representation of Password

		// Prompt the user to enter a 3-digit User ID
		USART_voidTxString((u8 *)"\r\nEnter 3-digit User ID (0–255): ");
		USART_voidRxString(local_u8UserID);

		// Convert the entered ID to an integer
		intUserID = ((local_u8UserID[0] - '0') * 100) + ((local_u8UserID[1] - '0') * 10) + (local_u8UserID[2] - '0');

		// Validate the User ID range
		if (intUserID < 0 || intUserID > 255)
		{
			USART_voidTxString((u8 *)"\r\nInvalid User ID. Please enter a value between 0 and 255.");
			return;
		}

		// Prompt the user to enter a 3-digit Password
		USART_voidTxString((u8 *)"\r\nEnter 3-digit password (0–255): ");
		USART_voidRxString(local_u8UserPass);

		// Convert the entered Password to an integer
		intUserPass = ((local_u8UserPass[0] - '0') * 100) + ((local_u8UserPass[1] - '0') * 10) + (local_u8UserPass[2] - '0');

		// Validate the Password range
		if (intUserPass < 0 || intUserPass > 255)
		{
			USART_voidTxString((u8 *)"\r\nInvalid Password. Please enter a value between 0 and 255.");
			return;
		}

		// Store User ID and Password in EEPROM
		EEPROM_voidSendDataByte(global_u8UserCount * 4, (u8)(intUserID & 0xFF));         // Store User ID (low byte)
		EEPROM_voidSendDataByte((global_u8UserCount * 4) + 1, (u8)(intUserID >> 8));    // Store User ID (high byte)
		EEPROM_voidSendDataByte((global_u8UserCount * 4) + 2, (u8)(intUserPass & 0xFF)); // Store Password (low byte)
		EEPROM_voidSendDataByte((global_u8UserCount * 4) + 3, (u8)(intUserPass >> 8));   // Store Password (high byte)

		global_u8UserCount++;  // Increment the User Count
		USART_voidTxString((u8 *)"\r\nUser Added Successfully!");
	}
	else
	{
		USART_voidTxString((u8 *)"\r\nUser Limit Reached.");
	}
}

void ADMIN_voidDeleteUser(void)
{
	u8 UserToDelete;

	USART_voidTxString((u8 *)"\r\nEnter User Number to Delete (1-8): ");
	USART_voidRxChar(&UserToDelete);
	UserToDelete -= '0';

	if (UserToDelete >= 1 && UserToDelete <= MAX_USERS)
	{
		u8 EEpromIndex = (UserToDelete - 1) * 2; // Calculate EEPROM index for the user

		// Clear the User ID and Password in EEPROM
		EEPROM_voidSendDataByte(EEpromIndex, EEPROM_DEFAULT_VALUE);       // Clear ID
		EEPROM_voidSendDataByte(EEpromIndex + 1, EEPROM_DEFAULT_VALUE);  // Clear Password
		// Decrement user count
		if (global_u8UserCount > 0) {
			global_u8UserCount--;
		}

		USART_voidTxString((u8 *)"\r\nUser Deleted Successfully.");
	}
	else
	{
		USART_voidTxString((u8 *)"\r\nInvalid User Selection.");
	}
}
void ADMIN_voidEditUser(void)
{
	u8 UserToEdit;
	u8 NewID[MAX_NUM_OF_PASS];
	u8 NewPass[MAX_NUM_OF_PASS];
	u8 OldID, OldPass;  // Declare as u8 since EEPROM stores 8-bit values
	u16 IntNewID;
	u16 IntNewPass;

	USART_voidTxString((u8 *)"\r\nEnter User Number to Edit (1-8): ");
	USART_voidRxChar(&UserToEdit);
	UserToEdit -= '0';

	if (UserToEdit >= 1 && UserToEdit <= MAX_USERS)
	{
		u8 EEpromIndex = (UserToEdit - 1) * 2; // Calculate EEPROM index for the user

		// Edit User ID
		USART_voidTxString((u8 *)"\r\nEnter New 3-digit ID (0–255): ");
		USART_voidRxString(NewID);
		IntNewID = ((NewID[0] - '0') * 100) + ((NewID[1] - '0') * 10) + (NewID[2] - '0');

		if (IntNewID <= 255)  // Ensure valid range
		{
			//EEPROM_voidSendDataByte(EEpromIndex, (u8)IntNewID); // Update ID
			EEPROM_voidSendDataByte(EEpromIndex, (u8)(IntNewID & 0xFF)); // Store low byte of New ID
			EEPROM_voidSendDataByte(EEpromIndex + 1, (u8)(IntNewID >> 8)); // Store high byte of New ID

		}
		else
		{
			USART_voidTxString((u8 *)"\r\nInvalid ID. Edit Operation Aborted.");
			return;
		}

		// Edit User Password
		USART_voidTxString((u8 *)"\r\nEnter New 3-digit Password (0–255): ");
		USART_voidRxString(NewPass);
		IntNewPass = ((NewPass[0] - '0') * 100) + ((NewPass[1] - '0') * 10) + (NewPass[2] - '0');

		if (IntNewPass <= 255)  // Ensure valid range
		{
			//EEPROM_voidSendDataByte(EEpromIndex + 1, (u8)IntNewPass); // Update Password
			EEPROM_voidSendDataByte(EEpromIndex + 2, (u8)(IntNewPass & 0xFF)); // Store low byte of New Pass
			EEPROM_voidSendDataByte(EEpromIndex + 3, (u8)(IntNewPass >> 8)); // Store high byte of New Pass

			USART_voidTxString((u8 *)"\r\nUser Data Updated Successfully.");
		}
		else
		{
			USART_voidTxString((u8 *)"\r\nInvalid Password.");
		}
	}
	else
	{
		USART_voidTxString((u8 *)"\r\nInvalid User Selection.");
	}
}

void ADMIN_voidDisplayAllUsers(void)
{
	USART_voidTxString((u8 *)"\r\nDisplaying All Users:");
	USART_voidTxString((u8 *)"\r\n======================");

	USART_voidTxString((u8 *)"\r\nTotal Users: ");
	USART_voidTxChar(global_u8UserCount + '0');
}


void ADMIN_voidOpenDoor (void)
{
	SERVO_voidOn();
	USART_voidTxString((u8 *)"\r\nThe Door Opened.");
	_delay_ms(3000);
}
void ADMIN_voidCloseDoor (void)
{
	SERVO_voidOff();
	USART_voidTxString((u8 *)"\r\nThe Door Closed.");
	_delay_ms(3000);
}
void ADMIN_voidDisplayAdminMenu(void)
{
	USART_voidTxString((u8 *)"\r\nAdmin Menu:");
	USART_voidTxString((u8 *)"\r\n1. Add User");
	USART_voidTxString((u8 *)"\r\n2. Delete User");
	USART_voidTxString((u8 *)"\r\n3. Edit User");
	USART_voidTxString((u8 *)"\r\n4. Display All Users");
	USART_voidTxString((u8 *)"\r\n5. Open the Door");
	USART_voidTxString((u8 *)"\r\n6. Close the Door");
	USART_voidTxString((u8 *)"\r\n7. Return to Main Menu");
	USART_voidTxString((u8 *)"\r\nChoose an option: ");
}
void ISR_UserDataReceived(void)
{
	u8 pinValue = 0;  // Variable to hold the pin state
	if (global_state != SYSTEM_STATE_USER) {
		USART_voidTxString((u8 *)"\r\nIgnoring ISR (Admin Active)");
		return;
	}



	DIO_enumGetPinValue(DIO_PORTD, DIO_PIN3, &pinValue);
	USART_voidTxString((u8 *)"\r\nINT1 Pin Value: ");
	USART_voidTxChar(pinValue);
	// Check the SCK line to ensure communication is active
	if (pinValue == 0)
	{
		USART_voidTxString((u8 *)"\r\nReceiving User Credentials...");

		// Variables for User ID and Password
		u8 UserID[2] = {0};
		u8 UserPass[2] = {0};
		u16 ReceivedUserID = 0, ReceivedUserPass = 0;

		// Variables for stored data
		u8 StoredData[4] = {0};
		u16 StoredUserID = 0, StoredUserPass = 0;

		// Receive User ID and Password via SPI
		if (!SPI_u8TrancieveData(0xFF, &UserID[0])) {
			USART_voidTxString((u8 *)"\r\nError: Failed to receive ID High Byte.");
			return;
		}
		USART_voidTxString((u8 *)"\r\nReceived ID High Byte: ");
		USART_voidTxChar(UserID[0]);

		if (!SPI_u8TrancieveData(0xFF, &UserID[1])) {
			USART_voidTxString((u8 *)"\r\nError: Failed to receive ID Low Byte.");
			return;
		}
		USART_voidTxString((u8 *)"\r\nReceived ID Low Byte: ");
		USART_voidTxChar(UserID[1]);

		if (!SPI_u8TrancieveData(0xFF, &UserPass[0])) {
			USART_voidTxString((u8 *)"\r\nError: Failed to receive Pass High Byte.");
			return;
		}
		USART_voidTxString((u8 *)"\r\nReceived Pass High Byte: ");
		USART_voidTxChar(UserPass[0]);

		if (!SPI_u8TrancieveData(0xFF, &UserPass[1])) {
			USART_voidTxString((u8 *)"\r\nError: Failed to receive Pass Low Byte.");
			return;
		}
		USART_voidTxString((u8 *)"\r\nReceived Pass Low Byte: ");
		USART_voidTxChar(UserPass[1]);

		// Combine User ID and Password
		ReceivedUserID = (UserID[0] << 8) | UserID[1];
		ReceivedUserPass = (UserPass[0] << 8) | UserPass[1];

		// Read the stored User ID and Password from EEPROM
		EEPROM_voidReadDataPage((ReceivedUserID - 1) * 4, 4, StoredData);
		StoredUserID = (StoredData[0] << 8) | StoredData[1];
		StoredUserPass = (StoredData[2] << 8) | StoredData[3];

		// Validate User ID and Password
		if (ReceivedUserID == StoredUserID && ReceivedUserPass == StoredUserPass) {
			USART_voidTxString((u8 *)"\r\nLogin Successful!");
			ADMIN_voidOpenDoor ();
			ADMIN_voidCloseDoor ();
			SPI_u8TrancieveData(0x01, NULL);  // Feedback: Success
		} else {
			USART_voidTxString((u8 *)"\r\nLogin Failed!");
			SPI_u8TrancieveData(0x00, NULL);  // Feedback: Failure
		}
	}
	else
	{
		USART_voidTxString((u8 *)"\r\nInvalid Trigger");
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

		// Reinitialize the system components (or jump to reset vector)
		ADMIN_voidInit();  // Reinitialize the system components

		USART_voidTxString((u8 *)"\r\nSystem has been reset. Normal operation resumed.\r\n");
		// Now call the login function again after the reset
		ADMIN_voidLogIn(); // Prompt for login after reset
		global_u8ResetState = 0; // Reset the reset state flag
	}
}

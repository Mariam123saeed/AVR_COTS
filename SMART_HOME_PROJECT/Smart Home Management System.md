## Smart Home Management System

### Overview

The **Smart Home Management System** is a comprehensive solution designed to control and monitor home appliances and user access remotely and locally. It features an admin and user interface for efficient home management. The system includes functionalities such as user authentication, appliance control, and system resets, leveraging hardware components like   LCD, keypad, LEDs, and SPI communication for seamless interaction.

------

### Features

#### **Admin Mode**

1. Login System:
   - Secure login with a username and password.
   - Lock system after exceeding login attempts.
2. User Management:
   - Add, edit, and delete users.
   - Store user credentials in EEPROM for persistent memory.
3. System Monitoring:
   - Admin can remotely monitor and manage user activities.
4. Door Control:
   - Open/close doors remotely via servos.

#### **User Mode**

1. Login System:
   - Users authenticate using an ID and password.
   - Supports local and remote login options.
2. Appliance Control:
   - Control LEDs (on/off, brightness adjustment via PWM).
   - Air conditioning control based on temperature readings.
3. System Feedback:
   - Displays login results and appliance statuses on LCD or USART.

#### **Communication**

- Uses SPI for communication between user devices and the central admin system.
- INT1 interrupt to handle real-time user data transmission.

#### **Error Handling**

- Retries for SPI communication.
- Input validation for both keypad and USART-based interactions.

------

### Hardware Components

1. **Microcontroller : ATmega32-based development board.

2. Peripherals

   :

   - LCD (16x2) for displaying user/admin interactions.
   - Keypad for local input.
   - LEDs for appliance simulation.
   - Servos for door control.
   - Temperature sensor (LM35) for air conditioning.
   - Buzzer for alerts.

3. Communication

   :

   - SPI (for admin-user communication).
   - USART (for remote login and feedback).

4. **EEPROM**: To store persistent user data.

------

### Software Structure

#### **Admin Code Features**

- User authentication and management.
- EEPROM-based credential storage.
- SPI-based feedback to user devices.
- INT0 interrupt for reset functionality.

#### **User Code Features**

- Local and remote login.
- Appliance control (LEDs, air conditioning).
- LCD and USART feedback for system responses.

------

### Installation and Setup

1. **Hardware Connection**:
   - Connect peripherals (LCD, keypad, LEDs, servos, sensors) as per pin configurations in the code.
   - Ensure SPI connections between admin and user controllers.
2. **Software Setup**:
   - Compile the provided code using AVR GCC or an Arduino IDE.
   - Upload `ADMIN_program.c` to the admin microcontroller.
   - Upload `USER_program.c` to the user microcontroller.
3. **Power On**:
   - Ensure all connections are secure and power the system on.
   - The system is ready for admin and user interaction.

------

### Usage

#### **Admin Operations**

1. Login as Admin

   :

   - Enter the admin username and password on the serial interface.

2. Manage Users

   :

   - Add users by entering their ID and password via USART.
   - Edit or delete users through the admin menu.

#### **User Operations**

1. Login

   :

   - Select local or remote login mode.
   - Enter credentials via the keypad (local) or USART (remote).

2. Control Appliances

   :

   - Toggle LEDs or adjust brightness using the keypad.
   - Control air conditioning based on the temperature.

------

### Future Enhancements

1. Integrate IoT for global remote access.
2. Add a mobile app interface for better user interaction.
3. Implement advanced security protocols like OTP.

------

### Author

**Mariam Saeed**
 November 2024
 This project was developed to provide a secure and flexible smart home solution for managing user access and appliance control.
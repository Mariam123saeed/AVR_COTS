################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/BUZZER/BUZZER_program.c 

OBJS += \
./HAL/BUZZER/BUZZER_program.o 

C_DEPS += \
./HAL/BUZZER/BUZZER_program.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/BUZZER/%.o: ../HAL/BUZZER/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\AVR_CODES\SMART_HOME_ADMIN\ADMIN" -I"D:\AVR_CODES\SMART_HOME_ADMIN\HAL\BUZZER" -I"D:\AVR_CODES\SMART_HOME_ADMIN\HAL\EEPROM" -I"D:\AVR_CODES\SMART_HOME_ADMIN\HAL\LCD" -I"D:\AVR_CODES\SMART_HOME_ADMIN\HAL\KPD" -I"D:\AVR_CODES\SMART_HOME_ADMIN\HAL\SERVO" -I"D:\AVR_CODES\SMART_HOME_ADMIN\HAL\SWITCH" -I"D:\AVR_CODES\SMART_HOME_ADMIN\MCAL\DIO" -I"D:\AVR_CODES\SMART_HOME_ADMIN\MCAL\EXTI" -I"D:\AVR_CODES\SMART_HOME_ADMIN\MCAL\GI" -I"D:\AVR_CODES\SMART_HOME_ADMIN\MCAL\PWM1" -I"D:\AVR_CODES\SMART_HOME_ADMIN\MCAL\TWI" -I"D:\AVR_CODES\SMART_HOME_ADMIN\MCAL\USART" -I"D:\AVR_CODES\SMART_HOME_ADMIN\UTILS_LIB" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



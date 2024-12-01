################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/PWM1/PWM1_program.c 

OBJS += \
./MCAL/PWM1/PWM1_program.o 

C_DEPS += \
./MCAL/PWM1/PWM1_program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/PWM1/%.o: ../MCAL/PWM1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\AVR_CODES\SMART_HOME_ADMIN\ADMIN" -I"D:\AVR_CODES\SMART_HOME_ADMIN\HAL\BUZZER" -I"D:\AVR_CODES\SMART_HOME_ADMIN\HAL\EEPROM" -I"D:\AVR_CODES\SMART_HOME_ADMIN\HAL\LCD" -I"D:\AVR_CODES\SMART_HOME_ADMIN\HAL\KPD" -I"D:\AVR_CODES\SMART_HOME_ADMIN\HAL\SERVO" -I"D:\AVR_CODES\SMART_HOME_ADMIN\HAL\SWITCH" -I"D:\AVR_CODES\SMART_HOME_ADMIN\MCAL\DIO" -I"D:\AVR_CODES\SMART_HOME_ADMIN\MCAL\EXTI" -I"D:\AVR_CODES\SMART_HOME_ADMIN\MCAL\GI" -I"D:\AVR_CODES\SMART_HOME_ADMIN\MCAL\PWM1" -I"D:\AVR_CODES\SMART_HOME_ADMIN\MCAL\TWI" -I"D:\AVR_CODES\SMART_HOME_ADMIN\MCAL\USART" -I"D:\AVR_CODES\SMART_HOME_ADMIN\UTILS_LIB" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



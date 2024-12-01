################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main.c 

OBJS += \
./main.o 

C_DEPS += \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\AVR_CODES\SMART_HOME_USER\HAL\BUZZER\inc" -I"D:\AVR_CODES\SMART_HOME_USER\MCAL\SPI_Master\inc" -I"D:\AVR_CODES\SMART_HOME_USER\MCAL\PWM0\inc" -I"D:\AVR_CODES\SMART_HOME_USER\HAL\DC_MOTOR\inc" -I"D:\AVR_CODES\SMART_HOME_USER\HAL\KPD\inc" -I"D:\AVR_CODES\SMART_HOME_USER\HAL\LCD\inc" -I"D:\AVR_CODES\SMART_HOME_USER\HAL\LED\inc" -I"D:\AVR_CODES\SMART_HOME_USER\HAL\LM35\inc" -I"D:\AVR_CODES\SMART_HOME_USER\HAL\SWITCH\inc" -I"D:\AVR_CODES\SMART_HOME_USER\MCAL\ADC\inc" -I"D:\AVR_CODES\SMART_HOME_USER\MCAL\DIO\inc" -I"D:\AVR_CODES\SMART_HOME_USER\MCAL\EXTI\inc" -I"D:\AVR_CODES\SMART_HOME_USER\MCAL\GI\inc" -I"D:\AVR_CODES\SMART_HOME_USER\MCAL\PWM2\inc" -I"D:\AVR_CODES\SMART_HOME_USER\MCAL\USART\inc" -I"D:\AVR_CODES\SMART_HOME_USER\USER\inc" -I"D:\AVR_CODES\SMART_HOME_USER\UTILS_LIB" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



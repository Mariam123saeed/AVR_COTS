################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADMIN/src/ADMIN_program.c 

OBJS += \
./ADMIN/src/ADMIN_program.o 

C_DEPS += \
./ADMIN/src/ADMIN_program.d 


# Each subdirectory must supply rules for building sources it contributes
ADMIN/src/%.o: ../ADMIN/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\AVR_CODES\SMART_HOME_ADMIN\UTILS_LIB" -I"D:\AVR_CODES\SMART_HOME_ADMIN\MCAL\SPI_Slave\inc" -I"D:\AVR_CODES\SMART_HOME_ADMIN\MCAL\USART\inc" -I"D:\AVR_CODES\SMART_HOME_ADMIN\MCAL\TWI\inc" -I"D:\AVR_CODES\SMART_HOME_ADMIN\MCAL\PWM1\inc" -I"D:\AVR_CODES\SMART_HOME_ADMIN\MCAL\GI\inc" -I"D:\AVR_CODES\SMART_HOME_ADMIN\MCAL\EXTI\inc" -I"D:\AVR_CODES\SMART_HOME_ADMIN\MCAL\DIO\inc" -I"D:\AVR_CODES\SMART_HOME_ADMIN\HAL\BUZZER\inc" -I"D:\AVR_CODES\SMART_HOME_ADMIN\HAL\EEPROM\inc" -I"D:\AVR_CODES\SMART_HOME_ADMIN\HAL\KPD\inc" -I"D:\AVR_CODES\SMART_HOME_ADMIN\HAL\LCD\inc" -I"D:\AVR_CODES\SMART_HOME_ADMIN\HAL\SERVO\inc" -I"D:\AVR_CODES\SMART_HOME_ADMIN\HAL\SWITCH\inc" -I"D:\AVR_CODES\SMART_HOME_ADMIN\ADMIN\inc" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



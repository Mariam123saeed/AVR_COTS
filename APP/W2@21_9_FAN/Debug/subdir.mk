################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_program.c \
../DCM_program.c \
../DIO_program.c \
../GI_program.c \
../LCD_program.c \
../LM35_program.c \
../PWM0_program.c \
../PWM2_program.c \
../main.c 

OBJS += \
./ADC_program.o \
./DCM_program.o \
./DIO_program.o \
./GI_program.o \
./LCD_program.o \
./LM35_program.o \
./PWM0_program.o \
./PWM2_program.o \
./main.o 

C_DEPS += \
./ADC_program.d \
./DCM_program.d \
./DIO_program.d \
./GI_program.d \
./LCD_program.d \
./LM35_program.d \
./PWM0_program.d \
./PWM2_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



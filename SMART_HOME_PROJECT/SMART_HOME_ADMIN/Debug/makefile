################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/USART/src/subdir.mk
-include MCAL/TWI/src/subdir.mk
-include MCAL/SPI_Slave/src/subdir.mk
-include MCAL/PWM1/src/subdir.mk
-include MCAL/GI/src/subdir.mk
-include MCAL/EXTI/src/subdir.mk
-include MCAL/DIO/src/subdir.mk
-include HAL/SWITCH/src/subdir.mk
-include HAL/SERVO/src/subdir.mk
-include HAL/LCD/src/subdir.mk
-include HAL/KPD/src/subdir.mk
-include HAL/EEPROM/src/subdir.mk
-include HAL/BUZZER/src/subdir.mk
-include ADMIN/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
SMART_HOME_ADMIN.lss \

FLASH_IMAGE += \
SMART_HOME_ADMIN.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: SMART_HOME_ADMIN.elf secondary-outputs

# Tool invocations
SMART_HOME_ADMIN.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,SMART_HOME_ADMIN.map -mmcu=atmega32 -o "SMART_HOME_ADMIN.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SMART_HOME_ADMIN.lss: SMART_HOME_ADMIN.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S SMART_HOME_ADMIN.elf  >"SMART_HOME_ADMIN.lss"
	@echo 'Finished building: $@'
	@echo ' '

SMART_HOME_ADMIN.hex: SMART_HOME_ADMIN.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex SMART_HOME_ADMIN.elf  "SMART_HOME_ADMIN.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: SMART_HOME_ADMIN.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 SMART_HOME_ADMIN.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) SMART_HOME_ADMIN.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

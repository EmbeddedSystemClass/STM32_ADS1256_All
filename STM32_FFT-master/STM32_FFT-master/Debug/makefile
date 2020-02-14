################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include Src/subdir.mk
-include Inc/TransformFunctions/subdir.mk
-include Inc/SupportFunctions/subdir.mk
-include Inc/StatisticsFunctions/subdir.mk
-include Inc/MatrixFunctions/subdir.mk
-include Inc/FilteringFunctions/subdir.mk
-include Inc/FastMathFunctions/subdir.mk
-include Inc/ControllerFunctions/subdir.mk
-include Inc/ComplexMathFunctions/subdir.mk
-include Inc/CommonTables/subdir.mk
-include Inc/BasicMathFunctions/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ADD_CMSIS_TEST.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
ADD_CMSIS_TEST.list \


# All Target
all: ADD_CMSIS_TEST.elf secondary-outputs

# Tool invocations
ADD_CMSIS_TEST.elf: $(OBJS) $(USER_OBJS) ../STM32F407VG_FLASH.ld
	arm-none-eabi-gcc -o "ADD_CMSIS_TEST.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"../STM32F407VG_FLASH.ld" --specs=nosys.specs -Wl,-Map="ADD_CMSIS_TEST.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

ADD_CMSIS_TEST.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "ADD_CMSIS_TEST.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	arm-none-eabi-objcopy.exe -O ihex "ADD_CMSIS_TEST.elf" "ADD_CMSIS_TEST.hex"
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets

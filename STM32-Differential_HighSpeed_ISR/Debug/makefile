################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
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
Differential_HighSpeed_ISR.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Differential_HighSpeed_ISR.list \

OBJCOPY_BIN += \
Differential_HighSpeed_ISR.bin \


# All Target
all: Differential_HighSpeed_ISR.elf secondary-outputs

# Tool invocations
Differential_HighSpeed_ISR.elf: $(OBJS) $(USER_OBJS) C:\Users\user\Downloads\STM32_ADS1256_All-master\STM32_ADS1256_All-master\STM32-Differential_HighSpeed_ISR\STM32F407VGTX_FLASH.ld
	arm-none-eabi-gcc -o "Differential_HighSpeed_ISR.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\user\Downloads\STM32_ADS1256_All-master\STM32_ADS1256_All-master\STM32-Differential_HighSpeed_ISR\STM32F407VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Differential_HighSpeed_ISR.map" -Wl,--gc-sections -static -u _printf_float --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Differential_HighSpeed_ISR.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Differential_HighSpeed_ISR.list"
	@echo 'Finished building: $@'
	@echo ' '

Differential_HighSpeed_ISR.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Differential_HighSpeed_ISR.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

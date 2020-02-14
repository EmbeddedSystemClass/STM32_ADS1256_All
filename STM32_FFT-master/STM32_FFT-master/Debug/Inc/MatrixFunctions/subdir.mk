################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/MatrixFunctions/arm_mat_add_f32.c \
../Inc/MatrixFunctions/arm_mat_add_q15.c \
../Inc/MatrixFunctions/arm_mat_add_q31.c \
../Inc/MatrixFunctions/arm_mat_cmplx_mult_f32.c \
../Inc/MatrixFunctions/arm_mat_cmplx_mult_q15.c \
../Inc/MatrixFunctions/arm_mat_cmplx_mult_q31.c \
../Inc/MatrixFunctions/arm_mat_init_f32.c \
../Inc/MatrixFunctions/arm_mat_init_q15.c \
../Inc/MatrixFunctions/arm_mat_init_q31.c \
../Inc/MatrixFunctions/arm_mat_inverse_f32.c \
../Inc/MatrixFunctions/arm_mat_inverse_f64.c \
../Inc/MatrixFunctions/arm_mat_mult_f32.c \
../Inc/MatrixFunctions/arm_mat_mult_fast_q15.c \
../Inc/MatrixFunctions/arm_mat_mult_fast_q31.c \
../Inc/MatrixFunctions/arm_mat_mult_q15.c \
../Inc/MatrixFunctions/arm_mat_mult_q31.c \
../Inc/MatrixFunctions/arm_mat_scale_f32.c \
../Inc/MatrixFunctions/arm_mat_scale_q15.c \
../Inc/MatrixFunctions/arm_mat_scale_q31.c \
../Inc/MatrixFunctions/arm_mat_sub_f32.c \
../Inc/MatrixFunctions/arm_mat_sub_q15.c \
../Inc/MatrixFunctions/arm_mat_sub_q31.c \
../Inc/MatrixFunctions/arm_mat_trans_f32.c \
../Inc/MatrixFunctions/arm_mat_trans_q15.c \
../Inc/MatrixFunctions/arm_mat_trans_q31.c 

OBJS += \
./Inc/MatrixFunctions/arm_mat_add_f32.o \
./Inc/MatrixFunctions/arm_mat_add_q15.o \
./Inc/MatrixFunctions/arm_mat_add_q31.o \
./Inc/MatrixFunctions/arm_mat_cmplx_mult_f32.o \
./Inc/MatrixFunctions/arm_mat_cmplx_mult_q15.o \
./Inc/MatrixFunctions/arm_mat_cmplx_mult_q31.o \
./Inc/MatrixFunctions/arm_mat_init_f32.o \
./Inc/MatrixFunctions/arm_mat_init_q15.o \
./Inc/MatrixFunctions/arm_mat_init_q31.o \
./Inc/MatrixFunctions/arm_mat_inverse_f32.o \
./Inc/MatrixFunctions/arm_mat_inverse_f64.o \
./Inc/MatrixFunctions/arm_mat_mult_f32.o \
./Inc/MatrixFunctions/arm_mat_mult_fast_q15.o \
./Inc/MatrixFunctions/arm_mat_mult_fast_q31.o \
./Inc/MatrixFunctions/arm_mat_mult_q15.o \
./Inc/MatrixFunctions/arm_mat_mult_q31.o \
./Inc/MatrixFunctions/arm_mat_scale_f32.o \
./Inc/MatrixFunctions/arm_mat_scale_q15.o \
./Inc/MatrixFunctions/arm_mat_scale_q31.o \
./Inc/MatrixFunctions/arm_mat_sub_f32.o \
./Inc/MatrixFunctions/arm_mat_sub_q15.o \
./Inc/MatrixFunctions/arm_mat_sub_q31.o \
./Inc/MatrixFunctions/arm_mat_trans_f32.o \
./Inc/MatrixFunctions/arm_mat_trans_q15.o \
./Inc/MatrixFunctions/arm_mat_trans_q31.o 

C_DEPS += \
./Inc/MatrixFunctions/arm_mat_add_f32.d \
./Inc/MatrixFunctions/arm_mat_add_q15.d \
./Inc/MatrixFunctions/arm_mat_add_q31.d \
./Inc/MatrixFunctions/arm_mat_cmplx_mult_f32.d \
./Inc/MatrixFunctions/arm_mat_cmplx_mult_q15.d \
./Inc/MatrixFunctions/arm_mat_cmplx_mult_q31.d \
./Inc/MatrixFunctions/arm_mat_init_f32.d \
./Inc/MatrixFunctions/arm_mat_init_q15.d \
./Inc/MatrixFunctions/arm_mat_init_q31.d \
./Inc/MatrixFunctions/arm_mat_inverse_f32.d \
./Inc/MatrixFunctions/arm_mat_inverse_f64.d \
./Inc/MatrixFunctions/arm_mat_mult_f32.d \
./Inc/MatrixFunctions/arm_mat_mult_fast_q15.d \
./Inc/MatrixFunctions/arm_mat_mult_fast_q31.d \
./Inc/MatrixFunctions/arm_mat_mult_q15.d \
./Inc/MatrixFunctions/arm_mat_mult_q31.d \
./Inc/MatrixFunctions/arm_mat_scale_f32.d \
./Inc/MatrixFunctions/arm_mat_scale_q15.d \
./Inc/MatrixFunctions/arm_mat_scale_q31.d \
./Inc/MatrixFunctions/arm_mat_sub_f32.d \
./Inc/MatrixFunctions/arm_mat_sub_q15.d \
./Inc/MatrixFunctions/arm_mat_sub_q31.d \
./Inc/MatrixFunctions/arm_mat_trans_f32.d \
./Inc/MatrixFunctions/arm_mat_trans_q15.d \
./Inc/MatrixFunctions/arm_mat_trans_q31.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/MatrixFunctions/arm_mat_add_f32.o: ../Inc/MatrixFunctions/arm_mat_add_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_add_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_add_q15.o: ../Inc/MatrixFunctions/arm_mat_add_q15.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_add_q15.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_add_q31.o: ../Inc/MatrixFunctions/arm_mat_add_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_add_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_cmplx_mult_f32.o: ../Inc/MatrixFunctions/arm_mat_cmplx_mult_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_cmplx_mult_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_cmplx_mult_q15.o: ../Inc/MatrixFunctions/arm_mat_cmplx_mult_q15.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_cmplx_mult_q15.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_cmplx_mult_q31.o: ../Inc/MatrixFunctions/arm_mat_cmplx_mult_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_cmplx_mult_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_init_f32.o: ../Inc/MatrixFunctions/arm_mat_init_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_init_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_init_q15.o: ../Inc/MatrixFunctions/arm_mat_init_q15.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_init_q15.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_init_q31.o: ../Inc/MatrixFunctions/arm_mat_init_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_init_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_inverse_f32.o: ../Inc/MatrixFunctions/arm_mat_inverse_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_inverse_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_inverse_f64.o: ../Inc/MatrixFunctions/arm_mat_inverse_f64.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_inverse_f64.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_mult_f32.o: ../Inc/MatrixFunctions/arm_mat_mult_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_mult_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_mult_fast_q15.o: ../Inc/MatrixFunctions/arm_mat_mult_fast_q15.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_mult_fast_q15.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_mult_fast_q31.o: ../Inc/MatrixFunctions/arm_mat_mult_fast_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_mult_fast_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_mult_q15.o: ../Inc/MatrixFunctions/arm_mat_mult_q15.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_mult_q15.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_mult_q31.o: ../Inc/MatrixFunctions/arm_mat_mult_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_mult_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_scale_f32.o: ../Inc/MatrixFunctions/arm_mat_scale_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_scale_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_scale_q15.o: ../Inc/MatrixFunctions/arm_mat_scale_q15.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_scale_q15.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_scale_q31.o: ../Inc/MatrixFunctions/arm_mat_scale_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_scale_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_sub_f32.o: ../Inc/MatrixFunctions/arm_mat_sub_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_sub_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_sub_q15.o: ../Inc/MatrixFunctions/arm_mat_sub_q15.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_sub_q15.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_sub_q31.o: ../Inc/MatrixFunctions/arm_mat_sub_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_sub_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_trans_f32.o: ../Inc/MatrixFunctions/arm_mat_trans_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_trans_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_trans_q15.o: ../Inc/MatrixFunctions/arm_mat_trans_q15.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_trans_q15.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Inc/MatrixFunctions/arm_mat_trans_q31.o: ../Inc/MatrixFunctions/arm_mat_trans_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/MatrixFunctions/arm_mat_trans_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


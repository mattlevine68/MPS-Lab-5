################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Lab01_task2.c \
../src/init.c \
../src/uart.c 

OBJS += \
./src/Lab01_task2.o \
./src/init.o \
./src/uart.o 

C_DEPS += \
./src/Lab01_task2.d \
./src/init.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/Lab01_task2.o: ../src/Lab01_task2.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"C:/Users/levinm7/Desktop/LAB-05_Template/inc" -I"C:/Users/levinm7/STM32CubeIDE/workspace_1.0.2/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/levinm7/STM32CubeIDE/workspace_1.0.2/stm32lib/CMSIS/Include" -I"C:/Users/levinm7/STM32CubeIDE/workspace_1.0.2/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"src/Lab01_task2.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
src/init.o: ../src/init.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"C:/Users/levinm7/Desktop/LAB-05_Template/inc" -I"C:/Users/levinm7/STM32CubeIDE/workspace_1.0.2/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/levinm7/STM32CubeIDE/workspace_1.0.2/stm32lib/CMSIS/Include" -I"C:/Users/levinm7/STM32CubeIDE/workspace_1.0.2/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"src/init.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
src/uart.o: ../src/uart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"C:/Users/levinm7/Desktop/LAB-05_Template/inc" -I"C:/Users/levinm7/STM32CubeIDE/workspace_1.0.2/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/levinm7/STM32CubeIDE/workspace_1.0.2/stm32lib/CMSIS/Include" -I"C:/Users/levinm7/STM32CubeIDE/workspace_1.0.2/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"src/uart.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"


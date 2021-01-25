################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Synth/Src/oscillator.cpp \
../Synth/Src/soundgenerator.cpp \
../Synth/Src/synth.cpp 

OBJS += \
./Synth/Src/oscillator.o \
./Synth/Src/soundgenerator.o \
./Synth/Src/synth.o 

CPP_DEPS += \
./Synth/Src/oscillator.d \
./Synth/Src/soundgenerator.d \
./Synth/Src/synth.d 


# Each subdirectory must supply rules for building sources it contributes
Synth/Src/oscillator.o: ../Synth/Src/oscillator.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DSTM32F405xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DDEBUG -c -I../Core/Inc -I../Drivers/StdPeriph -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../App/Inc -I../Synth/Inc -O1 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Synth/Src/oscillator.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Synth/Src/soundgenerator.o: ../Synth/Src/soundgenerator.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DSTM32F405xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DDEBUG -c -I../Core/Inc -I../Drivers/StdPeriph -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../App/Inc -I../Synth/Inc -O1 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Synth/Src/soundgenerator.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Synth/Src/synth.o: ../Synth/Src/synth.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DSTM32F405xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DDEBUG -c -I../Core/Inc -I../Drivers/StdPeriph -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../App/Inc -I../Synth/Inc -O1 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Synth/Src/synth.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


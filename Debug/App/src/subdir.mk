################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../App/src/LCD.cpp \
../App/src/maincpp.cpp \
../App/src/menu.cpp 

OBJS += \
./App/src/LCD.o \
./App/src/maincpp.o \
./App/src/menu.o 

CPP_DEPS += \
./App/src/LCD.d \
./App/src/maincpp.d \
./App/src/menu.d 


# Each subdirectory must supply rules for building sources it contributes
App/src/LCD.o: ../App/src/LCD.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DSTM32F405xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DDEBUG -c -I../Core/Inc -I../Drivers/StdPeriph -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../App/inc -Og -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"App/src/LCD.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
App/src/maincpp.o: ../App/src/maincpp.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DSTM32F405xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DDEBUG -c -I../Core/Inc -I../Drivers/StdPeriph -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../App/inc -Og -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"App/src/maincpp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
App/src/menu.o: ../App/src/menu.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DSTM32F405xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DDEBUG -c -I../Core/Inc -I../Drivers/StdPeriph -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../App/inc -Og -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"App/src/menu.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


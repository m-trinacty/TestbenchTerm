################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/gpio.cpp \
../src/main.cpp \
../src/oDrive.cpp \
../src/port.cpp \
../src/pps.cpp 

OBJS += \
./src/gpio.o \
./src/main.o \
./src/oDrive.o \
./src/port.o \
./src/pps.o 

CPP_DEPS += \
./src/gpio.d \
./src/main.d \
./src/oDrive.d \
./src/port.d \
./src/pps.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-tdx-linux-gnueabi-g++  -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/tdx-xwayland/5.3.0/sysroots/armv7at2hf-neon-tdx-linux-gnueabi -O0 -g3 -Wall -O2 -pipe -g -feliminate-unused-debug-types  -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



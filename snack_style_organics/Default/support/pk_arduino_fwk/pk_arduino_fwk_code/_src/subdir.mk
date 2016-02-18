################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_adc.cpp \
../support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_clk.cpp \
../support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_dio.cpp \
../support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_isr.cpp \
../support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_lcd.cpp \
../support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_pwm.cpp \
../support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_sd.cpp \
../support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_spi.cpp \
../support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_stubs.cpp \
../support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_uart.cpp 

OBJS += \
./support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_adc.o \
./support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_clk.o \
./support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_dio.o \
./support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_isr.o \
./support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_lcd.o \
./support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_pwm.o \
./support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_sd.o \
./support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_spi.o \
./support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_stubs.o \
./support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_uart.o 

CPP_DEPS += \
./support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_adc.d \
./support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_clk.d \
./support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_dio.d \
./support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_isr.d \
./support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_lcd.d \
./support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_pwm.d \
./support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_sd.d \
./support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_spi.d \
./support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_stubs.d \
./support/pk_arduino_fwk/pk_arduino_fwk_code/_src/arduino_fwk_uart.d 


# Each subdirectory must supply rules for building sources it contributes
support/pk_arduino_fwk/pk_arduino_fwk_code/_src/%.o: ../support/pk_arduino_fwk/pk_arduino_fwk_code/_src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



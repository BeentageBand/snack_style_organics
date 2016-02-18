################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../support/pk_heater_ctl/pk_heater_ctl_code/_src/heater_ctl.cpp 

OBJS += \
./support/pk_heater_ctl/pk_heater_ctl_code/_src/heater_ctl.o 

CPP_DEPS += \
./support/pk_heater_ctl/pk_heater_ctl_code/_src/heater_ctl.d 


# Each subdirectory must supply rules for building sources it contributes
support/pk_heater_ctl/pk_heater_ctl_code/_src/%.o: ../support/pk_heater_ctl/pk_heater_ctl_code/_src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



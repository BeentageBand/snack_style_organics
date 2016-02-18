################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../support/pk_axial_fan_ctl/pk_axial_fan_ctl_code/_src/axial_fan_ctl.cpp 

OBJS += \
./support/pk_axial_fan_ctl/pk_axial_fan_ctl_code/_src/axial_fan_ctl.o 

CPP_DEPS += \
./support/pk_axial_fan_ctl/pk_axial_fan_ctl_code/_src/axial_fan_ctl.d 


# Each subdirectory must supply rules for building sources it contributes
support/pk_axial_fan_ctl/pk_axial_fan_ctl_code/_src/%.o: ../support/pk_axial_fan_ctl/pk_axial_fan_ctl_code/_src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



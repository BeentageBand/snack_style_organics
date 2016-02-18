################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../apps/pk_snacky_dehyd_ctl/pk_snacky_dehyd_ctl_code/_src/snacky_dehyd_ctl.cpp 

OBJS += \
./apps/pk_snacky_dehyd_ctl/pk_snacky_dehyd_ctl_code/_src/snacky_dehyd_ctl.o 

CPP_DEPS += \
./apps/pk_snacky_dehyd_ctl/pk_snacky_dehyd_ctl_code/_src/snacky_dehyd_ctl.d 


# Each subdirectory must supply rules for building sources it contributes
apps/pk_snacky_dehyd_ctl/pk_snacky_dehyd_ctl_code/_src/%.o: ../apps/pk_snacky_dehyd_ctl/pk_snacky_dehyd_ctl_code/_src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



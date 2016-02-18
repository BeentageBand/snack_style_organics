################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../process/pk_snack_style_org_main/_src/main.cpp 

OBJS += \
./process/pk_snack_style_org_main/_src/main.o 

CPP_DEPS += \
./process/pk_snack_style_org_main/_src/main.d 


# Each subdirectory must supply rules for building sources it contributes
process/pk_snack_style_org_main/_src/%.o: ../process/pk_snack_style_org_main/_src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../support/pk_hamatora_sched/pk_hamatora_sched_code/_src/hamatora_sched.cpp 

OBJS += \
./support/pk_hamatora_sched/pk_hamatora_sched_code/_src/hamatora_sched.o 

CPP_DEPS += \
./support/pk_hamatora_sched/pk_hamatora_sched_code/_src/hamatora_sched.d 


# Each subdirectory must supply rules for building sources it contributes
support/pk_hamatora_sched/pk_hamatora_sched_code/_src/%.o: ../support/pk_hamatora_sched/pk_hamatora_sched_code/_src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



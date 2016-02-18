################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../apps/pk_snack_org_lcd/pk_snack_org_lcd_code/_src/snack_org_lcd.cpp 

OBJS += \
./apps/pk_snack_org_lcd/pk_snack_org_lcd_code/_src/snack_org_lcd.o 

CPP_DEPS += \
./apps/pk_snack_org_lcd/pk_snack_org_lcd_code/_src/snack_org_lcd.d 


# Each subdirectory must supply rules for building sources it contributes
apps/pk_snack_org_lcd/pk_snack_org_lcd_code/_src/%.o: ../apps/pk_snack_org_lcd/pk_snack_org_lcd_code/_src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



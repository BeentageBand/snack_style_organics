################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := del

# All of the sources participating in the build are defined here
-include sources.mk
-include support/pk_temp_monitor/pk_temp_monitor_code/_src/subdir.mk
-include support/pk_pid_ctl/pk_pid_ctl_code/_src/subdir.mk
-include support/pk_heater_ctl/pk_heater_ctl_code/_src/subdir.mk
-include support/pk_hamatora_sched/pk_hamatora_sched_code/_src/subdir.mk
-include support/pk_daylight_monitor/pk_daylight_monitor_code/_src/subdir.mk
-include support/pk_axial_fan_ctl/pk_axial_fan_ctl_code/_src/subdir.mk
-include support/pk_arduino_fwk/pk_arduino_fwk_code/_src/subdir.mk
-include process/pk_snack_style_org_main/_src/subdir.mk
-include process/pk_snack_org_friends/_src/subdir.mk
-include apps/pk_snacky_dehyd_ctl/pk_snacky_dehyd_ctl_code/_src/subdir.mk
-include apps/pk_snack_power_mode/pk_snack_power_mode_code/_src/subdir.mk
-include apps/pk_snack_org_lcd/pk_snack_org_lcd_code/_src/subdir.mk
-include apps/pk_data_logger/pk_data_logger_code/_src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: 10029950_snack_dehydrator

# Tool invocations
10029950_snack_dehydrator: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cygwin C++ Linker'
	g++  -o "10029950_snack_dehydrator" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(CPP_DEPS)$(C_DEPS) 10029950_snack_dehydrator
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

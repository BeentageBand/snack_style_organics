#=======================================================================================#
# makefile
#=======================================================================================#
#  Created on: Dec 21, 2015
#      Author: puch
#=======================================================================================#

#=======================================================================================#
# PROJECT VARIABLES
#=======================================================================================#
#======================================================#
# BUILD_LIST
#======================================================#
_build_=avr
#======================================================#
# BUILD CONFIG
#======================================================#
#Flavor
host_FLAVOR=host
avr_FLAVOR=mega_328P

#MCU
$(avr_FLAVOR)_MCU=atmega328p

#MACRO
host_MACROS+=\
-DHOST=1     \
-DPROGMEM=   \

mega_328P_MACROS+=\
-DF_CPU=8000000L \
-DAT_328P=1      \

#======================================================#
# MAKE PROJECT
#======================================================#
$(_build_)_MAK_DIR:=pk_project

#======================================================#
# PROJECT INCLUDES SEARCH PATHS
#======================================================#
$(_build_)_PROJECT_INC_DIR+=\
setup             \

ifeq "$(_build_)" "avr"
$(_build_)_PROJECT_INC_DIR+=\
"C:/avr-gcc-4.9.2/avr-gcc/avr/include" \

endif

$(_build_)_PROJECT_DIR=$(realpath . )
#=======================================================================================#
# PROJECT DEFINES 
#=======================================================================================#
define Arduino_INCS

ifeq "$(_build_)" "avr"

#ifeq "$(OS)" "Windows_NT"
$(_build_)_PROJECT_INC_DIR+=\
"C:/Dropbox/Arduino/DIR/hardware/arduino/avr/cores/arduino"     \
"C:/Dropbox/Arduino/DIR/libraries"                              \
"C:/Dropbox/Arduino/DIR/hardware/arduino/avr/libraries"         \
"C:/Dropbox/Arduino/DIR/hardware/arduino/avr/libraries/SPI"     \
"C:/Dropbox/Arduino/DIR/hardware/arduino/avr/variants/standard" \
"C:/Dropbox/Arduino/DIR/libraries/SD/src"                       \

$(_build_)_PROJECT_LIB_DIR+=\
"C:/avr-gcc-4.9.2/avr-gcc/avr/lib"                              \
#else
#$(_build_)_PROJECT_INC_DIR+=\
$(HOME)/Dropbox/Arduino/DIR/hardware/arduino/avr/cores/arduino     \
$(HOME)/Dropbox/Arduino/DIR/libraries                              \
$(HOME)/Dropbox/Arduino/DIR/hardware/arduino/avr/libraries         \
$(HOME)/Dropbox/Arduino/DIR/hardware/arduino/avr/variants/standard \

#endif

endif

endef
#=======================================================================================#
# PROJECT DEFINE EXPANSIONS
#=======================================================================================#
$(eval $(Arduino_INCS) )
#=======================================================================================#
# PROJECT RULES EXPANSIONS
#=======================================================================================#

#=======================================================================================#
# INCLUDE MAKE PROJECT UTILITY
#=======================================================================================#
include $($(_build_)_MAK_DIR)/project.mk
#=======================================================================================#
# makefile
#=======================================================================================#
# Changes Log
#
#
#=======================================================================================#
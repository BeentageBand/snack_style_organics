#=======================================================================================#
# arduino_fwk_dio_makefile.mk
#=======================================================================================#
#  Created on: Oct 3, 2015
#      Author: puch
#=======================================================================================#

#=======================================================================================#
# DEFINE PACKAGE RULE
#=======================================================================================#
define $(_build_)_$(_curr_)_MAKE
#=======================================================================================#
# OBJECTS DIRECTORY
# e.g: 
#     $(_build_)_$(_curr_)_src_dir=pk_module_N_code/_src
#     or
#     $(_build_)_$(_curr_)_src_dir=_src
#=======================================================================================#
$(_build_)_$(_curr_)_src_dir=pk_arduino_fwk_code/_src
$(_build_)_$(_curr_)_lib_dir=pk_arduino_fwk_code/_lib

#=======================================================================================#
# LIB REQUISITES
#=======================================================================================#

##
 # Object Requisites
 # e.g: $(_build_)_$(_curr_)_lib_objs=$($(_build_)_OBJ_DIR)/my_lib_obj$(_obj_ext_) \
 ##
ifeq "host" "$(_build_)"
$(_build_)_$(_curr_)_lib_objs=\
   $($(_build_)_OBJ_DIR)/arduino_fwk_stubs$(_obj_ext_) \
   
endif

ifeq "avr" "$(_build_)"
$(_build_)_$(_curr_)_lib_objs=\
   $($(_build_)_OBJ_DIR)/arduino_fwk_adc$(_obj_ext_)  \
   $($(_build_)_OBJ_DIR)/arduino_fwk_clk$(_obj_ext_)  \
   $($(_build_)_OBJ_DIR)/arduino_fwk_dio$(_obj_ext_)  \
   $($(_build_)_OBJ_DIR)/arduino_fwk_iic$(_obj_ext_)  \
   $($(_build_)_OBJ_DIR)/arduino_fwk_isr$(_obj_ext_)  \
   $($(_build_)_OBJ_DIR)/arduino_fwk_lcd$(_obj_ext_)  \
   $($(_build_)_OBJ_DIR)/arduino_fwk_mgr$(_obj_ext_)  \
   $($(_build_)_OBJ_DIR)/arduino_fwk_pwm$(_obj_ext_)  \
   $($(_build_)_OBJ_DIR)/arduino_fwk_sd$(_obj_ext_)   \
   $($(_build_)_OBJ_DIR)/arduino_fwk_spi$(_obj_ext_)  \
   $($(_build_)_OBJ_DIR)/arduino_fwk_uart$(_obj_ext_) \
   
endif


##
 # Library Requisites
 # e.g: $(_build_)_$(_curr_)_lib_libs=$($(_build_)_LIB_DIR)/$(_lprefix_)my_lib_lib$(_lib_ext_) \
 ##
$(_build_)_$(_curr_)_lib_libs=

##
 # Target Library
 # e.g: $(_build_)_$(_curr_)_lib_name=my_lib_name
 ##
$(_build_)_$(_curr_)_lib_name=arduino_fwk

#=======================================================================================#
# BIN REQUISITES
#=======================================================================================#

##
 # Object Requisites
 # e.g: $(_build_)_$(_curr_)_bin_objs=$($(_build_)_OBJ_DIR)/my_bin_obj$(_obj_ext_) \
 ##
$(_build_)_$(_curr_)_bin_objs=

##
 # Library Requisites
 # e.g: $(_build_)_$(_curr_)_bin_libs=$($(_build_)_LIB_DIR)/$(_lprefix_)my_bin_lib$(_lib_ext_) \
 ##
$(_build_)_$(_curr_)_bin_libs=

##
 # Target Binary
 # e.g: $(_build_)_$(_curr_)_bin_name=my_bin_name
 ##
$(_build_)_$(_curr_)_bin_name=
#=======================================================================================#
# END PACKAGE RULE
#=======================================================================================#
endef
#=======================================================================================#
# LOCAL VARIABLES
#=======================================================================================#

#=======================================================================================#
# LOCAL DEFINES 
#=======================================================================================#
define Arduino_LIB_MAKE 

ifeq "$(_build_)" "avr"

$($(_build_)_LIB_DIR)/$(_lprefix_)arduino_core$(_lib_ext_) : $($(_build_)_LIB_DIR) $(_path_)$($(_build_)_$(_curr_)_lib_dir)/$(_lprefix_)arduino_core$(_lib_ext_)
	-cp -pf  $(_path_)$($(_build_)_$(_curr_)_lib_dir)/$(_lprefix_)arduino_core$(_lib_ext_) $$@

endif

endef
#=======================================================================================#
# LOCAL DEFINE EXPANSIONS
#=======================================================================================#

#=======================================================================================#
# INCLUDE PK PROJECT UTILITY
#=======================================================================================#
include $($(_build_)_PROJECT_DIR)/$($(_build_)_MAK_DIR)/epilog.mk
#=======================================================================================#
# LOCAL RULES EXPANSIONS
#=======================================================================================#
$(eval \
   $(call INFO_VERBOSE_template, $(Arduino_LIB_MAKE) )\
)
#=======================================================================================#
# arduino_fwk_dio_makefile.mk
#=======================================================================================#
# Changes Log
#
#
#=======================================================================================#

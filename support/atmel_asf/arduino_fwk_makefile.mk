define $(_flavor_)_$(_feat_)_MAKE

ifeq "host" "$(_flavor_)"
$(_flavor_)_$(_feat_)_lib_objs=arduino_fwk_stubs.cpp
   
endif

ifeq "avr" "$(_flavor_)"
$(_flavor_)_$(_feat_)_lib_objs=\
arduino_fwk_adc   \
arduino_fwk_clk   \
arduino_fwk_dio   \
arduino_fwk_isr   \
arduino_fwk_lcd   \
arduino_fwk_mgr   \
arduino_fwk_pwm   \
arduino_fwk_uart \
LiquidCrystal    \
   #  \          \
arduino_fwk_spi  \
arduino_fwk_sd   \
arduino_fwk_iic  \
   
endif


$(_flavor_)_$(_feat_)_lib=arduino_fwk

endef

define Arduino_LIB_MAKE 

ifeq "$(_flavor_)" "avr"

$($(_flavor_)_LIB_DIR)/$(_lprefix_)arduino_core$(_lib_ext_) : $($(_flavor_)_LIB_DIR) /cygdrive/c/Dropbox/AVR/out/core.a
	-cp -pf /cygdrive/c/Dropbox/AVR/out/core.a $$@

endif

endef

include $(PROJ_MAK_DIR)/epilog.mk

$(eval \
   $(call INFO_VERBOSE_template, $(Arduino_LIB_MAKE) )\
)

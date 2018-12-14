define $(_flavor_)_$(_feat_)_MAKE

$(_flavor_)_$(_feat_)_inc=heater_ctl.h heater_ctl_types.h heater_ctl_ext.h
$(_flavor_)_$(_feat_)_lib_objs=heater_ctl
$(_flavor_)_$(_feat_)_lib=heater_resistor_ctl

endef

include $(PROJ_MAK_DIR)/epilog.mk

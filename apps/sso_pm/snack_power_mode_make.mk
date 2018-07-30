define $(_flavor_)_$(_feat_)_MAKE

$(_flavor_)_$(_feat_)_inc=sso_power_mode.h sso_power_mode_evs.h sso_power_mode_types.h sso_power_mode_wn.h sso_power_mode_ext.h

$(_flavor_)_$(_feat_)_lib_objs=sso_power_mode sso_power_mode_fsm sso_power_mode_process sso_power_mode_wn

$(_flavor_)_$(_feat_)_lib=sso_power_mode

endef

include $(PROJ_MAK_DIR)/epilog.mk

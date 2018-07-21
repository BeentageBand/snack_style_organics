define $(_flavor_)_$(_feat_)_MAKE

$(_flavor_)_$(_feat_)_inc=sso_power_mode.h snack_power_mode_types.h

$(_flavor_)_$(_feat_)_lib_objs=sso_power_mode

$(_flavor_)_$(_feat_)_lib=sso_power_mode

endef

include $(PROJ_MAK_DIR)/epilog.mk

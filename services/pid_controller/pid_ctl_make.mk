define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=pid_ctl.h pid_ctl_types.h pid_driver.h
$(_flavor_)_$(_feat_)_lib_objs=pid_ctl pid_driver
$(_flavor_)_$(_feat_)_lib=pid_ctl
endef

include $(PROJ_MAK_DIR)/epilog.mk

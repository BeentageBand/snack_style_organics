define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=sso_task_def.h
$(_flavor_)_$(_feat_)_bin_objs=sso_launcher
$(_flavor_)_$(_feat_)_bin_libs=\
   application \
   cobject \
   chimney_ctl \
   dbg_log \
   heater_resistor_ctl \
   ipc \
   ipc_posix \
   pid_ctl \
   state_machine \
   sso_dehydrator \
   sso_friends \
   sso_hid \
   sso_lcd \
   sso_power_mode \
#\
    
$(_flavor_)_$(_feat_)_bin=sso_launcher

endef

-include $(PROJ_MAK_DIR)/epilog.mk

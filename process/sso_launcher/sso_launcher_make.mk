define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=sso_task_def.h
$(_flavor_)_$(_feat_)_bin_objs=sso_launcher
$(_flavor_)_$(_feat_)_bin_libs=\
   sso_dehydrator \
   sso_power_mode \
   sso_friends \
   application \
   pid_ctl \
   state_machine \
   ipc_posix \
   ipc \
   dbg_log \
   cobject \
#\
    
$(_flavor_)_$(_feat_)_bin=sso_launcher

endef

-include $(PROJ_MAK_DIR)/epilog.mk

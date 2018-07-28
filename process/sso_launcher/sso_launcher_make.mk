define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=sso_task_def.h
$(_flavor_)_$(_feat_)_bin_objs=sso_launcher
$(_flavor_)_$(_feat_)_bin_libs=\
   cobject \
   application \
   snack_org_friends \
   ipc \
   ipc_posix \
   state_machine \
   dbg_log \
   sso_power_mode \
#\
    
$(_flavor_)_$(_feat_)_bin=sso_launcher

endef

-include $(PROJ_MAK_DIR)/epilog.mk

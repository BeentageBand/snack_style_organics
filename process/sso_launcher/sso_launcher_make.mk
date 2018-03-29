define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=sso_task_def.h
 $(_flavor_)_$(_feat_)_bin_libs=\
   app \
   snack_org_lcd          \
   temp_monitor           \
   axial_fan_ctl          \
   heater_ctl             \
   daylight_monitor       \
   snacky_dehyd_ctl       \
   chimney_ctl            \
   pid_ctl                \
   snack_power_mode       \
   snack_org_friends      \
   arduino_fwk            \
   hama_dbg_trace         \
#\
   power_mode             \
    
$(_flavor_)_$(_feat_)_bin=sso_launcher

endef

include $(PROJ_MAK_DIR)/epilog.mk

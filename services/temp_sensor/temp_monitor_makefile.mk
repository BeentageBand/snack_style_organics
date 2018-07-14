define $(_build_)_$(_curr_)_MAKE
 
$(_build_)_$(_curr_)_lib_objs=\
   $($(_build_)_OBJ_DIR)/temp_monitor$(_obj_ext_) \

$(_build_)_$(_curr_)_lib=temp_monitor

endef

include $(PROJ_MAK_DIR)/epilog.mk

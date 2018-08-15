define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=sso_dehydrator_evs.h sso_dehydrator_cbk.h sso_dehydrator_types.h
$(_flavor_)_$(_feat_)_lib_objs=sso_dehydrator_process sso_dehydrator_fsm sso_dehydrator_worker
$(_flavor_)_$(_feat_)_lib=sso_dehydrator
endef

-include $(PROJ_MAK_DIR)/epilog.mk
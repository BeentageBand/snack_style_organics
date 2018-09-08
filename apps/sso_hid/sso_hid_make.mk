define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=sso_hid_cbk.h sso_hid_fsm.h sso_hid_types.h sso_hid_worker.h
$(_flavor_)_$(_feat_)_lib_objs=sso_hid_process sso_hid_worker
$(_flavor_)_$(_feat_)_lib=sso_hid
endef

-include $(PROJ_MAK_DIR)/epilog.mk
define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=sso_friends.h
$(_flavor_)_$(_feat_)_lib_objs=sso_friends sso_power_mode_friends
$(_flavor_)_$(_feat_)_lib=sso_friends
endef

-include $(PROJ_MAK_DIR)/epilog.mk

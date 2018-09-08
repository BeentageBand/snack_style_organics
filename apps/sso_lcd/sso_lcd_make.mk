define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=sso_lcd.h sso_lcd_cbk.h sso_lcd_mailist.h sso_lcd_types.h sso_lcd_worker.h
$(_flavor_)_$(_feat_)_lib_objs=sso_lcd sso_lcd_process sso_lcd_worker
$(_flavor_)_$(_feat_)_lib=sso_lcd
endef

-include $(PROJ_MAK_DIR)/epilog.mk
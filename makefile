PROJ_DIR=.
PROJ_MAK_DIR=$(PROJ_DIR)/project_make

include $(PROJ_MAK_DIR)/prolog.mk 

define Project_Make

PROJ_DIR=.
PROJ_MAK_DIR=$(PROJ_DIR)/project_make
#OUT_DIR=$(HOME)/projects/suite_object_out

FLAVOR_LIST=linux \
macos \
#arduino

#Flavor
arduino_build=arduino
linux_build=linux
macos_build=macos

#MACRO
arduino_PROJ_INC=include
linux_PROJ_INC=include \
include/linux
macos_PROJ_INC=include \
include/macos

endef

include $(PROJ_MAK_DIR)/project.mk

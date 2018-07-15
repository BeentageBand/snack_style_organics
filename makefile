PROJ_DIR=.
PROJ_MAK_DIR=$(PROJ_DIR)/project_make

include $(PROJ_MAK_DIR)/prolog.mk 

define Project_Make

PROJ_DIR=.
PROJ_MAK_DIR=$(PROJ_DIR)/project_make
#OUT_DIR=$(HOME)/projects/suite_object_out

FLAVOR_LIST=linux arduino

#Flavor
arduino_build=arduino
linux_build=linux

#MACRO
arduino_PROJ_INC=include
linux_PROJ_INC=include \
include/linux

endef

include $(PROJ_MAK_DIR)/project.mk

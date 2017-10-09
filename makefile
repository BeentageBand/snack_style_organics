#=======================================================================================#
# makefile
#=======================================================================================#
#  Created on: Dec 21, 2015
#      Author: puch
#=======================================================================================#

#=======================================================================================#
# PROJECT VARIABLES
#=======================================================================================#
PROJ_DIR=.
PROJ_MAK_DIR=$(PROJ_DIR)/project_make

#=======================================================================================#
# PROJECT DEFINES 
#=======================================================================================#
define Project_Make

#======================================================#
# MAKE PROJECT
#======================================================#
PROJ_DIR=.
PROJ_MAK_DIR=$(PROJ_DIR)/project_make

#======================================================#
# BUILD_LIST
#======================================================#
FLAVOR_LIST=host linux
#======================================================#
# BUILD CONFIG
#======================================================#
#Flavor
host_build=linux
linux_build=linux

#MACRO

#======================================================#
# PROJECT INCLUDES SEARCH PATHS
#======================================================#
host_PROJ_INC=include 
linux_PROJ_INC=include

endef
#=======================================================================================#
# PROJECT DEFINE EXPANSIONS
#=======================================================================================#

#=======================================================================================#
# PROJECT RULES EXPANSIONS
#=======================================================================================#

#=======================================================================================#
# INCLUDE MAKE PROJECT UTILITY
#=======================================================================================#

include $(PROJ_MAK_DIR)/project.mk
#=======================================================================================#
# makefile
#=======================================================================================#
# Changes Log
#
#
#=======================================================================================#
#=======================================================================================#

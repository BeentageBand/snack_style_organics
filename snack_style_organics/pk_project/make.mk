#=======================================================================================#
# make.mk
#=======================================================================================#
#  Created on: Oct 3, 2015
#      Author: puch
#=======================================================================================#

_gc_macros_=$($($(_build_)_FLAVOR)_MACROS)


define $(_build_)_$(_curr_)_ALL_INCS

$(_build_)_$(_curr_)_lib_incs=\
$(shell find $(_path_)$($(_build_)_$(_curr_)_src_dir) -name *.h )

$(_build_)_$(_curr_)_bin_incs=\
$(shell find $(_path_)$($(_build_)_$(_curr_)_src_dir) -name *.h )
 
endef

$(eval \
   $(call INFO_VERBOSE_template, $($(_build_)_$(_curr_)_ALL_INCS_N_SRCS) ) \
)
$(eval \
   $(call INFO_VERBOSE_template, \
      $(_build_)_$(_curr_)_lib_srcs=\
      $(patsubst \
         $($(_build_)_OBJ_DIR)/%$(_obj_ext_),\
         $(_path_)$($(_build_)_$(_curr_)_src_dir)/%$(_src_ext_),\
         $($(_build_)_$(_curr_)_lib_objs)\
      ) \
   ) \
)

$(eval \
   $(call INFO_VERBOSE_template, \
      $(_build_)_$(_curr_)_bin_srcs=\
      $(patsubst \
         $($(_build_)_OBJ_DIR)/%$(_obj_ext_),\
         $(_path_)$($(_build_)_$(_curr_)_src_dir)/%$(_src_ext_),\
         $($(_build_)_$(_curr_)_bin_objs)\
      ) \
   ) \
)

##
 # CALL MAKEFILE BUILD
 ##

# .PHONY : pk_name_N
#
# all : pk_name_N
#
# pk_name_N : _pk_name_N_lib_name _pk_name_N_bin_name
#
# _pk_name_N_bin_name : _pk_name_N_bin_libs _pk_name_N_bin_objs
#	cc -flags -I PROJECT_INCS -o _pk_name_N_bin_name _pk_name_N_bin_objs \
#      pk_name_N_lib_incs -L LIB_DIR -lpk_name_bin_libs
#
# _pk_name_N_lib_name _pk_name_N_bin_libs _pk_name_N_lib_libs : _pk_name_N_lib_objs
#	ar -qvc $$@ -L -l_pk_name_N_lib_libs _pk_name_lib_objs
#
# _pk_name_N_bin_objs _pk_name_N_lib_objs : _pk_name_N_bin_incs $(_pk_name_N_bin_objs:%.o=.cpp) \
# _pk_name_N_lib_incs $(_pk_name_N_lib_objs:%.o=.cpp);
#	cc -flags -I PROJECT_INCS -c $$^ -o $$@
#

##
 # BIN NAME MAKERULE
 ##
define $(_build_)_$(_curr_)_BIN_NAME_MAKE

ifneq "$($(_build_)_$(_curr_)_bin_name)" ""
$($(_build_)_BIN_DIR)/$($(_build_)_$(_curr_)_bin_name) : $($(_build_)_BIN_DIR) $($(_build_)_$(_curr_)_bin_objs) $($(_build_)_$(_curr_)_bin_libs)
	$(_gc_) $(_gc_flags_) $(_gc_macros_) $(addprefix -I, $($(_build_)_PROJECT_INC_DIR) ) \
      -o $$@ $($(_build_)_$(_curr_)_bin_objs) $(addprefix -L, $($(_build_)_PROJECT_LIB_DIR) ) \
      $(patsubst $($(_build_)_LIB_DIR)/$(_lprefix_)%$(_lib_ext_),-l%,$($(_build_)_$(_curr_)_bin_libs) ) \
      $(_lbs_)
endif
endef

$(info ****************************************** $(_build_)_$(_curr_) BIN MAKE ********************************)

$(eval \
   $(call INFO_VERBOSE_template, \
      $($(_build_)_$(_curr_)_BIN_NAME_MAKE) \
   ) \
)

##
 # LIB NAME MAKERULE
 ##
define $(_build_)_$(_curr_)_LIB_NAME_MAKE

ifneq "$($(_build_)_$(_curr_)_lib_name)" ""
$($(_build_)_LIB_DIR)/$(_lprefix_)$($(_build_)_$(_curr_)_lib_name)$(_lib_ext_) : $($(_build_)_LIB_DIR) $($(_build_)_$(_curr_)_lib_objs) $($(_build_)_$(_curr_)_lib_libs)
	$(_ar_) -rcs $$@ $($(_build_)_$(_curr_)_lib_objs) $($(_build_)_$(_curr_)_lib_libs)
endif 
endef

$(info ****************************************** $(_build_)_$(_curr_) LIB MAKE ********************************)

$(eval \
   $(call INFO_VERBOSE_template, \
      $($(_build_)_$(_curr_)_LIB_NAME_MAKE) \
   ) \
)

##
 # OBJ NAME MAKERULE
 ##
define $(_build_)_$(_curr_)_OBJ_MAKE
ifneq "$(_obj_)" ""
$(_obj_) : $($(_build_)_OBJ_DIR) $($(_build_)_$(_curr_)_$(_tar_)_incs) $(_src_)
	$(_gc_) $(_gc_flags_) $(_gc_macros_) $(addprefix -I, $($(_build_)_PROJECT_INC_DIR) ) \
    -c $(_src_) $($(_build_)_$(_curr_)_$(_tar_)_incs) -o $$@
endif
endef

define ITERATE_OBJ_MAKE_template
_obj_:=$(word $(_i_), $($(_build_)_$(_curr_)_$(_tar_)_objs) )
_src_:=$(word $(_i_), $($(_build_)_$(_curr_)_$(_tar_)_srcs) )
$(1)
endef

$(info ****************************************** $(_build_)_$(_curr_) OBJ MAKE ********************************)

$(foreach _tar_,lib bin, \
   $(foreach _i_, $(shell seq 1 $(words $(_i_), $($(_build_)_$(_curr_)_$(_tar_)_objs) ) ), \
      $(eval \
         $(call INFO_VERBOSE_template, \
            $(call ITERATE_OBJ_MAKE_template, $($(_build_)_$(_curr_)_OBJ_MAKE)) \
         ) \
      ) \
   ) \
)
##
 # LIB NAME MAKERULE
 ##

#=======================================================================================#
# make.mk
#=======================================================================================#
# Changes Log
#
#
#=======================================================================================#
#
#
# Title:        make.cfg.template.prog
# Project:	User
# Desc:
# 
#   Makefile for User.
# 
# Notes:
# 
# Author:	
# Created:	9/13/97 using MakeConfigs 5.02.00.b.02
#
# Revision History: (See end of file for Revision Log)
#
#   Last Mod By:    $Author$
#   Last Mod:	    $Date$
#   Version:	    $Revision$
#
#   $Id$
# 

#
# Do not modifiy 'makefile_type'
makefile_type = prog
# This is the make.cfg version that will be used
make_cfg_ver	= 5.02
# Default target type
make_target	= default
# Uncomment 'show_commands' to output compile command.
# Comment out proto_dep (or set to any value but true) to prevent
#     regen of proto header
show_commands = # true
proto_dep       = true

# Include standard MakeConfig configuration for GNU make required
include Make/make.cfg.$(make_cfg_ver)

# 
# =USE_CURRENT_MAKEFILE=
# When you re-gen a make file, every thing between 
# these tags will be kept int the new makefile
# if you want it re-gen'd, just delete the tags
#

NAME		= User

INSTALL_BINDIR	= $(LOCAL_BIN_DIR)

VER_MAJOR	= 1
VER_MINOR	= 00
VER_RELEASE	= 00.a.01
VERSION		= $(VER_MAJOR).$(VER_MINOR).$(VER_RELEASE)

PROGRAM_DEFAULT	= $(NAME)
PROGRAM_DEBUG	= $(NAME)_g
PROGRAM_PROFILE	= $(NAME)_pg
PROGRAM_STATIC	= $(NAME)_static


PRJ_TOPDIR	= ../../..

# include any arch specific makefile component
-include $(PRJ_TOPDIR)/src/arch/$(arch)/Makefile.Test

VPATH		= $(ARCH_VPATH):.

###### D E F I N E S  #####
# 
# Config defines avalable
#
#


SRC_DEFINES	= 
PRJ_DEFINES	= -DVERSION=\"$(VERSION)\" $(ARCH_DEFINES)

DEFAULT_DEFINES = -DUSER_DEFAULT=1
DEBUG_DEFINES	= -DCLUE_DEBUG=1
PROFILE_DEFINES	= -DUSER_PROFILE=1
STATIC_DEFINES	= -DUSER_STATIC=1

######  I N C L U D E S #####
#
# Config includes available (need to use -I)
#
# $(alpha_incdir) 	$(beta_incdir) 	$(local_incdir)
#


SRC_INC		= $(ARCH_INC) -I. $(CLUE_SRC_INC) -I$(PRJ_TOPDIR)/src/Clue 
PRJ_INC		= -I$(beta_incdir)

# Any other cpp flags to use on for all targets

CPP_FLAGS		= $(ARCH_CPP_FLAGS)

FLEX_FLAGS		=
BISON_FLAGS		=

###### C O M P I L E / C P P #####
#
# Config flags available
#
# $(cc_optimize) $(cxx_optimize)
# $(cc_debug)	 $(cxx_debug)
# $(cc_profile)	 $(cxx_profile)
# $(cc_warn)	 $(cxx_warn)
#


CC_FLAGS		= $(cc_warn_all) $(ARCH_CC_FLAGS)

DEFAULT_CC_FLAGS	= $(cc_optimize)
DEBUG_CC_FLAGS		= $(cc_debug)
PROFILE_CC_FLAGS	= $(cc_profile)
STATIC_CC_FLAGS		= $(cc_optimize)

CXX_FLAGS		= $(arch_cxx_flags) $(cxx_warn_all)

DEFAULT_CXX_FLAGS	= $(cxx_optimize)
DEBUG_CXX_FLAGS		= $(cxx_debug)
PROFILE_CXX_FLAGS	= $(cxx_profile)
STATIC_CXX_FLAGS	= $(cxx_optimize)

# ##### I N S T A L L #####

INSTALL_BIN_FLAGS	= 

# ##### L I N K  /  L I B R A R I E S #####
#
# Config flags available
#
# $(ld_optimize)
# $(ld_debug)
# $(ld_profile)
# $(ld_static)
#
# Config library directories available (need to use -L)
#
# $(alpha_libdir)	$(beta_libdir)	$(local_libdir)
#


LD_FLAGS		= $(ARCH_LD_FLAGS)

DEFAULT_LD_FLAGS	= $(ld_optimize)
DEBUG_LD_FLAGS		= $(ld_debug)
PROFILE_LD_FLAGS	= $(ld_profile)
STATIC_LD_FLAGS		= $(ld_static) $(ld_optimize)

DEFAULT_LD_LIBDIRS	= -L$(PRJ_TOPDIR)/src/Clue -L$(beta_libdir)
DEBUG_LD_LIBDIRS	= $(DEFAULT_LD_LIBDIRS)
PROFILE_LD_LIBDIRS	= $(DEFAULT_LD_LIBDIRS)
STATIC_LD_LIBDIRS	= $(DEFAULT_LD_LIBDIRS)

DEFAULT_LD_LIBS		= -lClue_g -lGnuRegex -lCommon
DEBUG_LD_LIBS		= $(DEFAULT_LD_LIBS)
PROFILE_LD_LIBS		= $(DEFAULT_LD_LIBS)
STATIC_LD_LIBS		= $(DEFAULT_LD_LIBS)

# DEP_LIBS - rebuild target if DEP_LIBS newer than target

DEFAULT_DEP_LIBS	=
DEBUG_DEP_LIBS		= $(PRJ_TOPDIR)/src/Clue/libClue_g.a
PROFILE_DEP_LIBS	=
STATIC_DEP_LIBS		=

#
# =USE_CURRENT_MAKEFILE=
#

# **** S O U R C E   F I L E S ****

GENERATED_SOURCES	=			

FLEX_C_SOURCES	=			
BISON_C_SOURCES	=			
FLEX_CXX_C_SOURCES	=			
BISON_CXX_C_SOURCES	=			
C_SOURCES	=			
CXX_C_SOURCES	=			\
	AppParam.C                      \
	main.C                          \
	$(ARCH_CXX_C_SOURCES)           \

CXX_CC_SOURCES	=			
CXX_CPP_SOURCES	=			

USER_HH_INCS	=			\
	AppParam.hh                     \
	$(ARCH_USER_HH_INCS)            \

USER_INCLUDES	=		\
	$(USER_H_INCS)		\
	$(USER_HH_INCS)		\
	$(USER_II_INCS)		\

CXX_HEADERS	=			\
	AppParam.hh                     \
	$(ARCH_CXX_HEADERS)             \



###### T A R G E T S #####
#
# Targets defined in make.cfg.targets.
#
# default: 	all
# depend:	create .depend_default
# profile:	MAKE CCDEBUG=CC_PROFILE all
# proto:	create $(PROTO_H)
# clean:  	rm -f LIB_OBJECTS LIBRARY
# realclean:	rm -f LIB_OBJECTS LIBRARY .depend.lib PROTO_H TAGS
# tags:		create TAGS using etags
#


include Make/make.cfg.targets.$(makefile_type).$(make_cfg_ver)

default debug profile:: $(generated_files)

default:: $(PROGRAM_DEFAULT)

debug profile static::
	$(hide) $(MAKE) make_target=$@ $(PROGRAM_$($@))

all::	default debug profile

install:: install_lib_check install_$(make_target)
	$(hide) echo + Installation Complete!

install_all:: install_lib_check

install_all:: install_default install_debug install_profile install_static
	$(hide) echo + Installation Complete!

install_default:: default $(INSTALL_BINDIR)/$(PROGRAM_DEFAULT)
install_debug::   debug   $(INSTALL_BINDIR)/$(PROGRAM_DEBUG)
install_profile:: profile $(INSTALL_BINDIR)/$(PROGRAM_PROFILE)
install_shared::  shared  $(INSTALL_BINDIR)/$(PROGRAM_SHARED)


test:	default

#
# include dependancies generated by 'make depend'
#
-include .depend_$(make_target)

#
# =MAKEFILE_LOG=
#
# $Log$
# Revision 1.1  1997/09/16 11:31:27  houghton
# Initial Version.
#
#
# =MAKEFILE_LOG=
#

# Local Variables:
# mode:makefile
# End:




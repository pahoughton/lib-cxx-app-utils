#
# Title:        Makefile
# Project:	StlUtils
# Desc:
# 
#   
# 
# Notes:
# 
#   This Makefile requres MakeConfig and GNU's make version 3.75
#
#   Try 'make help' for a list of standard targets.
# 
# Author:	Paul A. Houghton - (paul.houghton@wcom.com)
# Created:	06/06/1994 using MakeConfigs 5.01.00.a.02
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
# The following variables control the behavior of MakeConfigs.
#   makefile_type   is the type of object being build (do NOT change)
#   make_cfg_ver    is the version of MakeConfigs to use
#   make_target	    is the default target to build
#   show_commands   if this is true, the commands  will be output
#   proto_dep	    if this is true, the proto header will be rebuild when
#		    one of it's dependancies changes (ie a .c source)
#   check_install   if this is true, install and install_all will NOT
#		    overwrite an installed version.
#

makefile_type   = lib
make_cfg_ver	= 5.05
make_target	= default
show_commands 	= # true
proto_dep	= true
check_install	= true

# Include standard MakeConfig configuration for GNU make required
include Make/make.cfg.$(make_cfg_ver)

# 
# =USE_CURRENT_MAKEFILE=
# When you re-gen a make file, every thing between 
# these tags will be kept in the new makefile
# if you want it re-gen'd, just delete the tags
#

NAME		= StlUtils

INSTALL_LIB_DIR	= $(beta_libdir)
INSTALL_INC_DIR	= $(beta_incdir)

VER_MAJOR	= 4
VER_MINOR	= 00
VER_RELEASE	= 00.b.04
VERSION		= $(VER_MAJOR).$(VER_MINOR).$(VER_RELEASE)

LIBRARY_DEFAULT	= lib$(NAME).a
LIBRARY_DEBUG	= lib$(NAME)_g.a
LIBRARY_PROFILE	= lib$(NAME)_pg.a
LIBRARY_SHARED	= lib$(NAME)_s.$(shlib_ext)

PRJ_TOPDIR	= ../..

# include any arch specific makefile component
-include $(PRJ_TOPDIR)/src/arch/$(rpm_arch)$(arch)/Makefile.$(NAME)

VPATH		= $(ARCH_VPATH):.

###### D E F I N E S  #####
# 
# Config defines avalable
#
#


SRC_DEFINES	= 
PRJ_DEFINES	= -DVERSION=\"$(VERSION)\" $(ARCH_DEFINES)

DEFAULT_DEFINES = -DSTLUTILS_DEFAULT=1
DEBUG_DEFINES	= -DSTLUTILS_DEBUG=1
PROFILE_DEFINES	= -DSTLUTILS_PROFILE=1
SHARED_DEFINES	= -DSTLUTILS_SHARED=1

######  I N C L U D E S #####
#
# Config includes available
#
# $(alpha_incdir) 	$(beta_incdir) 	$(local_incdir)
#


SRC_INC		= $(ARCH_INC) -I. 
PRJ_INC		= -I$(beta_incdir)


# Any other cpp flags to use on for all targets

CPP_FLAGS		= $(ARCH_CPP_FLAGS)

###### C O M P I L E / C P P #####
#
# Config flags available
#
# $(cc_optimize) $(cxx_optimize)
# $(cc_debug)	 $(cxx_debug)
# $(cc_profile)	 $(cxx_profile)
# $(cc_warn)	 $(cxx_warn)
#


CC_FLAGS		= $(cc_warn_flags) $(ARCH_CC_FLAGS) $(CC_OTHER)

DEFAULT_CC_FLAGS	= $(cc_optimize_flags)
DEBUG_CC_FLAGS		= $(cc_debug_flags)
TEST_CC_FLAGS		= $(cc_debug_flags)
PROFILE_CC_FLAGS	= $(cc_profile_flags)
SHARED_CC_FLAGS		= $(cc_shared_flags) $(cc_optimize_flags)

CXX_OTHER		= 
CXX_FLAGS		= $(cxx_warn_flags) $(ARCH_CXX_FLAGS) $(CXX_OTHER)

DEFAULT_CXX_FLAGS	= $(cxx_optimize_flags)
DEBUG_CXX_FLAGS		= $(cxx_debug_flags)
TEST_CXX_FLAGS		= $(cxx_debug_flags)
PROFILE_CXX_FLAGS	= $(cxx_profile_flags)
SHARED_CXX_FLAGS	= $(cxx_shared_flags) $(cxx_optimize_flags)

# **** S H A R E D   D E P   L I B S *****

SHDEP_LIBS		= -L$(beta_libdir) -lGnuRegex_s -lCommon_s

# **** I N S T A L L ****

INSTALL_LIB_FLAGS	= -m 444
INSTALL_INC_FLAGS	= -m 444


# **** S O U R C E   F I L E S ****

GENERATED_SOURCES = $(ARCH_GENERATED_SOURCES)

C_SOURCES	=			\
	$(ARCH_C_SOURCES)               \

CXX_C_SOURCES =				\
	Bitmask.C			\
	ClassVersion.C                  \
	DateRange.C                     \
	DateRangeDaily.C                \
	DateRangeWeekly.C               \
	DateTime.C                      \
	DateTimeUtils.C                 \
	Directory.C			\
	FileStat.C			\
	FilePath.C                      \
	IosOpenModeFromString.C		\
	IosOpenModeToString.C		\
	IosSeekDirToString.C		\
	LibTest.C                       \
	Log.C				\
	LogBuf.C			\
	LogLevel.C			\
	MfNumTo.C			\
	Mutex.C                         \
	Param.C                         \
	RegexScan.C                     \
	SizeIt.C                        \
	Str.C                           \
	StrStreambuf.C                  \
	StringCapitalize.C              \
	StringCaseCompare.C             \
	StringCaseReverseSearch.C       \
	StringCaseSearch.C              \
	StringFirstNotOf.C		\
	StringFrom.C			\
	StringLower.C                   \
	StringReverseSearch.C           \
	StringReverseSearch.C           \
	StringSearch.C                  \
	StringTo.C			\
	StringUpper.C                   \
	StripTrailing.C			\
	StripWhite.C                    \
	SubStr.C                        \
	ThreadBase.C                    \
	Timer.C                         \
	Void.C                          \
	$(ARCH_CXX_C_SOURCES)

USER_H_INCS	=			\
	$(ARCH_USER_H_INCS)             \

USER_HH_INCS	=			\
	Bit.hh				\
	Bitmask.hh			\
	ClassVersion.hh                 \
	StlUtilsConfig.hh		\
	StlUtilsVersion.hh		\
	StlUtilsMisc.hh			\
	Compare.hh			\
	DateRange.hh                    \
	DateRangeDaily.hh               \
	DateRangeWeekly.hh              \
	DateTime.hh                     \
	DateTimeUtils.hh                \
	Directory.hh			\
	DumpInfo.hh			\
	FilePath.hh                     \
	FileStat.hh			\
	LibTest.hh                      \
	LibLog.hh			\
	Log.hh				\
	LogBuf.hh			\
	LogLevel.hh			\
	Mutex.hh                        \
	Net2Host.hh			\
	Param.hh                        \
	RegexScan.hh                    \
	SizeIt.hh                       \
	SortOrder.hh			\
	Str.hh                          \
	StrStreambuf.hh                 \
	StringUtils.hh			\
	SubStr.hh                       \
	ThreadBase.hh                   \
	Timer.hh                        \
	VectorResync.hh			\
	Void.hh                         \
	$(ARCH_USER_HH_INCS)		\

USER_II_INCS	=			\
	Bit.ii				\
	DateTimeUtils.ii                \
	DateTime.ii                     \
	DateRange.ii                    \
	DateRangeDaily.ii               \
	DateRangeWeekly.ii              \
	Directory.ii			\
	Param.ii                        \
	SizeIt.ii                       \
	SortOrder.ii			\
	Str.ii                          \
	StrStreambuf.ii                 \
	SubStr.ii                       \
	ThreadBase.ii                   \
	Timer.ii                        \
	Void.ii                         \
	ClassVersion.ii                 \
	StlUtilsMisc.ii			\
	StringUtils.ii			\
	Bitmask.ii			\
	FilePath.ii                     \
	FileStat.ii			\
	LogLevel.ii			\
	LogBuf.ii			\
	Log.ii				\
	Mutex.ii                        \
	Param.ii                        \
	$(ARCH_USER_II_INCS)		\

USER_INCLUDES	=		\
	$(USER_H_INCS)		\
	$(USER_HH_INCS)		\
	$(USER_II_INCS)		\

C_HEADERS	=			\
	$(ARCH_C_HEADERS)               \

CXX_HEADERS	=			\
	$(USER_HH_INCS)			\
	_StlUtils.hh                        \
	$(ARCH_CXX_HEADERS)             \

CXX_INLINES	=			\
	$(USER_II_INCS)			\
	$(ARCH_CXX_INLINES)             \


#
# =USE_CURRENT_MAKEFILE=
#

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

default debug profile shared:: $(generated_files)

default:: $(LIBRARY_$($(make_target)))

debug profile shared:: 
	$(hide) $(MAKE) make_target=$@ $(LIBRARY_$($@))

all::	default debug profile shared


install:: install_lib_check install_$(make_target)
	$(HIDE) echo Installation Complete!

install_all:: install_lib_check

install_all:: install_default install_debug install_profile install_shared
	$(HIDE) echo Installation Complete!

install_default:: default $(INSTALL_LIB_DIR)/$(LIBRARY_DEFAULT)
install_debug::   debug   $(INSTALL_LIB_DIR)/$(LIBRARY_DEBUG)
install_profile:: profile $(INSTALL_LIB_DIR)/$(LIBRARY_PROFILE)
install_shared::  shared  $(INSTALL_LIB_DIR)/$(LIBRARY_SHARED)


test::	default

FORCE: 

#
# include dependancies generated by 'make depend'
#
-include .depend_$(make_target)


#
# =MAKEFILE_LOG=
#
# $Log$
# Revision 4.13  1998/07/20 11:23:16  houghton
# Added CXX_OTHER variable.
#
# Revision 4.12  1998/03/23 10:43:50  houghton
# Changed to work with MakeConfigs 5.05.
#
# Revision 4.11  1998/02/02 15:22:38  houghton
# Fixed to work with MakeConfigs 5.04 correctly.\
#
# Revision 4.10  1998/01/30 12:40:10  houghton
# Changed to use MakeConfigs 5.04.
#
# Revision 4.9  1998/01/22 18:30:47  houghton
# Changed version number.
# Changed to use MakeConfigs 5.03
#
# Revision 4.8  1998/01/09 10:41:06  houghton
# Changed versin number.
#
# Revision 4.7  1998/01/05 13:08:17  houghton
# Added VectorResync.hh
#
# Revision 4.6  1997/12/20 16:09:28  houghton
# Added StripTrailing.
#
# Revision 4.5  1997/12/19 14:00:03  houghton
# Added cc_default and cxx_default vars.
#
# Revision 4.4  1997/11/18 15:06:50  houghton
# Added MfNumTo.
#
# Revision 4.3  1997/09/19 11:22:53  houghton
# Cleanup.
#
# Revision 4.2  1997/09/17 15:45:17  houghton
# Changed ver num.
# Renamed StlUtilsUtils to StlUtilsMisc.
#
# Revision 4.1  1997/09/17 15:12:39  houghton
# Changed to Version 4
#
# Revision 3.28  1997/09/17 11:08:33  houghton
# Changed: renamed library to StlUtils.
#
# Revision 3.27  1997/09/16 11:23:41  houghton
# Added IosSeekDirToString.C
#
# Revision 3.26  1997/09/02 13:05:45  houghton
# Changed Version number.
#
# Revision 3.25  1997/08/28 21:22:34  houghton
# Changed version num.
#
# Revision 3.24  1997/08/24 21:51:49  houghton
# Changed version number.
#
# Revision 3.23  1997/08/12 11:10:08  houghton
# Added StringFirstNotOf.
#
# Revision 3.22  1997/08/08 13:27:58  houghton
# Changed target dependancy to generated_files (was proto).
# Added GENERATED_SOURCES.
# Changed version number.
# Changed make_cfg_ver to use 5.02
#
# Revision 3.21  1997/07/19 18:15:53  houghton
# Added Directory.
#
# Revision 3.20  1997/05/02 12:18:08  houghton
# Added libCommon_s to shdep libs.
#
# Revision 3.19  1997/04/26 14:41:31  houghton
# Changed version number.
#
# Revision 3.18  1997/04/21 12:15:12  houghton
# Changed ver number.
#
# Revision 3.17  1997/04/04 20:53:53  houghton
# Added IosOpenModeFromString.
# Added IosOpenModeToSting.
# Changed ver num.
#
# Revision 3.16  1997/04/04 03:11:02  houghton
# Changed ver num.
#
# Revision 3.15  1997/04/02 13:45:09  houghton
# Changed ver num.
#
# Revision 3.14  1997/04/01 13:40:06  houghton
# Changed version num.
#
# Revision 3.13  1997/03/21 15:38:56  houghton
# Changed version number.
#
# Revision 3.12  1997/03/21 12:24:51  houghton
# Changed version number.
#
# Revision 3.11  1997/03/13 02:20:23  houghton
# Changed version number.
#
# Revision 3.10  1997/03/07 11:53:14  houghton
# Changed version num.
# Changed sh_deplibs.
#
# Revision 3.9  1997/03/03 15:03:47  houghton
# Changed ver num.
#
# Revision 3.8  1997/03/03 14:37:01  houghton
# Removed support for RW Tools++ & rpm.
#
# Revision 3.7  1997/03/02 13:19:23  houghton
# Added Net2Host
#
# Revision 3.6  1997/01/18 17:32:14  houghton
# Changed Ver number.
# Added Compare.hh, DumpInfo.hh, LibLog.hh, Bit.hh, SortOrder.hh,
#     Mutex.ii, Bit.ii & SortOrder.ii to installed headers.
#
# Revision 3.5  1996/11/22 12:27:04  houghton
# Cleanup.
#
# Revision 3.4  1996/11/20 12:13:51  houghton
# Major rework to support both rpm sources (for ani server) and
#     other sources (for distributor).
#
# Revision 3.3  1996/11/19 22:02:09  houghton
# Cleanup install stuff from libStlUtils2.
#
# Revision 3.2  1996/11/19 12:22:22  houghton
# Added -m flag to install includes.
# Added StringFrom
# Minor Cleanup.
#
# Revision 3.1  1996/11/14 01:23:50  houghton
# Changed to Release 3
#
# Revision 2.26  1996/11/13 16:58:52  houghton
# Renamed StlUtils.hh & StlUtils.ii to StlUtilsUtils.hh & StlUtilsUtils.ii.
#
# Revision 2.25  1996/11/08 11:45:08  houghton
# *** empty log message ***
#
# Revision 2.24  1996/11/04 18:21:56  houghton
# Changed version and install directory to beta.
#
# Revision 2.23  1996/11/04 14:19:53  houghton
# Changed to use rw inclues.
# Changed to only compile sources that are ready for latest release.
#
# Revision 2.22  1996/08/14 14:39:02  houghton
# Added FileBinStream Headers to USER_HH_INCS.
#
# Revision 2.21  1996/08/12 17:49:02  houghton
# Added FileBinStream sources.
#
# Revision 2.20  1996/07/04 10:29:19  houghton
# Change Version Number.
#
# Revision 2.19  1996/06/11 09:52:04  houghton
# *** empty log message ***
#
# Revision 2.18  1996/06/09 11:39:47  houghton
# Change Version Number.
#
# Revision 2.17  1996/05/25 12:35:29  houghton
# Change version number.
#
# Revision 2.16  1996/05/21 10:31:29  houghton
# Added vpt to show VPATH value.
#
# Revision 2.15  1996/05/18 12:56:21  houghton
# Cleanup & change version number.
#
# Revision 2.14  1996/05/14 14:18:11  houghton
# Rework SHDEP_LIBS for AIX.
#
# Revision 2.13  1996/05/14 14:03:04  houghton
# Change Version Number.
#
# Revision 2.12  1996/05/11 11:01:35  houghton
# Change Version number and cleanup.
#
# Revision 2.11  1996/05/02 11:04:44  houghton
# Changed version number.
#
# Revision 2.10  1996/05/01 11:34:23  houghton
# Restructure directories to Test01/src and Test01/data
# Added TEST_DATA_DIR define.
#
# Revision 2.9  1996/05/01 11:00:00  houghton
# Bug-Fix: Added c*shared flags to SHARED_C*FLAGS.
# Changed version number.
#
# Revision 2.8  1996/04/27 13:03:56  houghton
# Changed to use MakeConfigs 5
#
#
# =MAKEFILE_LOG=
#

# Local Variables:
# mode:makefile
# End:

#
# Title:        make.cfg.template.prog
# Project:	Test
# Desc:
# 
#   Makefile for Test.
# 
# Notes:
# 
#   This Makefile requres MakeConfig and GNU's make version 3.75
#
#   Try 'make help' for a list of standard targets.
# 
# Author:	Paul A. Houghton,,, (paul.houghton@wcom.com)
# Created:	4/2/98 using MakeConfigs 5.05.00.b.03
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

makefile_type   = prog
make_cfg_ver	= 5.06
make_target	= default
show_commands 	= # true
proto_dep	= true
check_install	= true


# Include standard MakeConfig configuration for GNU make required
include Make/make.cfg.$(make_cfg_ver)

# 
# =USE_CURRENT_MAKEFILE=
# When you re-gen a make file, every thing between 
# these tags will be kept int the new makefile
# if you want it re-gen'd, just delete the tags
#

NAME		= Test

PRJ_TOPDIR		= ../../..
PRJ_BINDIR		= $(PRJ_TOPDIR)/bin

INSTALL_BASE_DIR	= $(PRJ_TOPDIR)
INSTALL_BIN_DIR		= $(INSTALL_BASE_DIR)/bin

VER_MAJOR	= 4
VER_MINOR	= 00
VER_RELEASE	= 00.b.01
VERSION		= $(VER_MAJOR).$(VER_MINOR).$(VER_RELEASE)

PROGRAM_DEFAULT	= $(NAME)
PROGRAM_DEBUG	= $(NAME)_g
PROGRAM_TEST	= $(NAME)_tg
PROGRAM_PROFILE	= $(NAME)_pg
PROGRAM_STATIC	= $(NAME)_static
PROGRAM_SHARED	= $(NAME)_s


# include any arch specific makefile component
include $(PRJ_TOPDIR)/src/arch/$(arch)/Makefile.$(NAME)

VPATH		= $(ARCH_VPATH):.

###### D E F I N E S  #####
# 
# Config defines avalable
#
#


SRC_DEFINES	= -DTEST_DATA_DIR=\"$(TEST_DATA_DIR)\" 	\
		  -DTEST_USER=\"$(TEST_USER)\"		\
		  -DTEST_GROUP=\"$(TEST_GROUP)\"	\
		  -DTEST_UID=$(TEST_UID)		\
		  -DTEST_GID=$(TEST_GID)		\
		  -DTEST_LINE_PROGRESS=false		\
		  -DHOST_BLURR				\

PRJ_DEFINES	= -DVERSION=\"$(VERSION)\" $(ARCH_DEFINES)

DEFAULT_DEFINES = -DTEST_DEFAULT=1
DEBUG_DEFINES	= -DTEST_DEBUG=1 -DSTLUTILS_DEBUG=1
TEST_DEFINES	= -DSTLUTILS_TEST=1 $(DEBUG_DEFINES)
PROFILE_DEFINES	= -DTEST_PROFILE=1
STATIC_DEFINES	= -DTEST_STATIC=1
SHARED_DEFINES	= -DTEST_SHARED=1

######  I N C L U D E S #####
#
# Config includes available (need to use -I)
#
# $(alpha_incdir) 	$(beta_incdir) 	$(local_incdir)
#


SRC_INC		= $(ARCH_INC) -I. $($($(make_target))_PRJ_INC)
PRJ_INC		= -I$(local_incdir)

DEFAULT_PRJ_INC	= 
DEBUG_PRJ_INC	= $(STLUTILS_SRC_INC)
TEST_PRJ_INC	= $(STLUTILS_SRC_INC)
PROFILE_PRJ_INC = $(STLUTILS_SRC_INC)
STATIC_PRJ_INC	= 

# Any other cpp flags to use on for all targets

CPP_FLAGS		= $(ARCH_CPP_FLAGS)

FLEX_FLAGS		=
BISON_FLAGS		=

###### C O M P I L E / C P P #####
#
# Config flags available
#
# $(cc_optimize_flags) $(cxx_optimize_flags)
# $(cc_debug_flags)    $(cxx_debug_flags)
# $(cc_profile_flags)  $(cxx_profile_fllags)
# $(cc_warn)           $(cxx_warn)
#


CC_FLAGS		= $(ARCH_CC_FLAGS) $(CC_OTHER)

DEFAULT_CC_FLAGS	= $(cc_optimize_flags)
DEBUG_CC_FLAGS		= $(cc_debug_flags)
TEST_CC_FLAGS		= $(cc_debug_flags)
PROFILE_CC_FLAGS	= $(cc_profile_flags)
STATIC_CC_FLAGS		= $(cc_optimize_flags)
SHARED_CC_FLAGS		= $(cc_shared_flags) $(cc_optimize_flags)

CXX_FLAGS		= $(cxx_warn) $(ARCH_CXX_FLAGS) $(CXX_OTHER)

DEFAULT_CXX_FLAGS	= $(cxx_optimize_flags)
DEBUG_CXX_FLAGS		= $(cxx_debug_flags)
TEST_CXX_FLAGS		= $(cxx_debug_flags)
PROFILE_CXX_FLAGS	= $(cxx_profile_flags)
STATIC_CXX_FLAGS	= $(cxx_optimize_flags)
SHARED_CXX_FLAGS	= $(cxx_shared_flags) $(cxx_optimize_flags)

# ##### I N S T A L L #####

INSTALL_BIN_PERM	= 555
INSTALL_BIN_FLAGS	= -m $(INSTALL_BIN_PERM)

# ##### L I N K  /  L I B R A R I E S #####
#
# Config flags available
#
# $(ld_optimize_flags)
# $(ld_debug_flags)
# $(ld_profile_flags)
# $(ld_static_flags)
#
# Config library directories available (need to use -L)
#
# $(alpha_libdir)	$(beta_libdir)	$(local_libdir)
#


LD_FLAGS		= $(ARCH_LD_FLAGS) $(LD_OTHER)

DEFAULT_LD_FLAGS	= $(ld_optimize_flags)
DEBUG_LD_FLAGS		= $(ld_debug_flags)
TEST_LD_FLAGS		= $(ld_debug_flags)
PROFILE_LD_FLAGS	= $(ld_profile_flags)
STATIC_LD_FLAGS		= $(ld_static_flags) $(ld_optimize_flags)
SHARED_LD_FLAGS		= $(ld_shared_flags) $(ld_optimize_flags)

DEFAULT_LD_LIBDIRS	= -L$(local_libdir)
DEBUG_LD_LIBDIRS	= $(STLUTILS_SRC_LDIR) $(DEFAULT_LD_LIBDIRS)
TEST_LD_LIBDIRS		= $(DEBUG_LD_LIBDIRS)
PROFILE_LD_LIBDIRS	= $(DEFAULT_LD_LIBDIRS)
STATIC_LD_LIBDIRS	= $(DEFAULT_LD_LIBDIRS)
SHARED_LD_LIBDIRS	= $(DEFAULT_LD_LIBDIRS)

DEFAULT_LD_LIBS		= -lStlUtils -lCommon -lGnuRegex $(ARCH_DEFAULT_LIBS)
DEBUG_LD_LIBS		= -lStlUtils_g -lCommon_g -lGnuRegex $(ARCH_DEBUG_LIBS)
TEST_LD_LIBS		= -lStlUtils_tg -lCommon_g -lGnuRegex_g 	\
			  $(ARCH_DEBUG_LIBS)
PROFILE_LD_LIBS		= $(DEFAULT_LD_LIBS)
STATIC_LD_LIBS		= $(DEFAULT_LD_LIBS)
SHARED_LD_LIBS		= $(DEFAULT_LD_LIBS)

# DEP_LIBS - rebuild target if DEP_LIBS newer than target

DEFAULT_DEP_LIBS	= 
DEBUG_DEP_LIBS		= $(PRJ_TOPDIR)/src/StlUtils/libStlUtils_g.a
TEST_DEP_LIBS		= $(PRJ_TOPDIR)/src/StlUtils/libStlUtils_tg.a
PROFILE_DEP_LIBS	= 
STATIC_DEP_LIBS		= 
SHARED_DEP_LIBS		= 

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
	main.C				\
	tClassVersion.C			\
	tArraySize.C                    \
	tOpenFlags.C			\
	tAlign.C			\
	tDwordAlign.C                   \
	tMemOverlap.C                   \
	tBetween.C			\
	tAbsLong.C                      \
	tIsBaseDigit.C                  \
	tUnionOf.C                      \
	tRound.C                        \
	tBit.C                          \
	tCompare.C                      \
	tCompare01.C                    \
	tCompare02.C                    \
	tStripWhite.C                   \
	tStripTrailing.C		\
	tStringSearch.C                 \
	tStringCaseCompare.C            \
	tStringLower.C                  \
	tStringUpper.C                  \
	tStringCapitalize.C             \
	tStringTo.C                     \
	tStringFrom.C			\
	tStringFirstNotOf.C		\
	tbasename.C                     \
	tMfNumTo.C			\
	tSafeStrcpy.C			\
	tCharToInt.C			\
	tCharIsBaseDigit.C		\
	tBitmask.C                      \
	tBitmask01.C                    \
	tBitmask02.C                    \
	tBitmask03.C                    \
	tRegexScan.C                    \
	tUser.C                         \
	tUserGroup.C                    \
	tFileStat.C                     \
	tFileStat01.C                   \
	tFileStat02.C                   \
	tFileStat03.C                   \
	tFileStat04.C                   \
	tFileStat05.C                   \
	tFileStat06.C                   \
	tLogLevel.C                     \
	tLog.C                          \
	tLog01.C                        \
	tLog02.C                        \
	tLog03.C                        \
	tLog04.C                        \
	tLog05.C                        \
	tLog06.C			\
	tLog07.C			\
	tLog08.C			\
	tLog09.C			\
	tParam.C                        \
	tParam01.C                      \
	tParam03.C			\
	tFilePath.C                     \
	tFilePath01.C                   \
	tFilePath02.C                   \
	tFilePath03.C                   \
	tFilePath04.C                   \
	tStr.C                          \
	tStr01.C                        \
	tStr02.C                        \
	tStr03.C                        \
	tStr04.C                        \
	tStr05.C                        \
	tStr06.C                        \
	tStr07.C                        \
	tStr08.C                        \
	tStr09.C                        \
	tStr10.C                        \
	tStr11.C                        \
	tStr12.C                        \
	tStr13.C                        \
	tStr14.C                        \
	tStr15.C                        \
	tStr16.C                        \
	tStr17.C                        \
	tStr18.C                        \
	tStr19.C                        \
	tStr20.C                        \
	tStr21.C                        \
	tStr22.C                        \
	tStr23.C                        \
	tStr24.C                        \
	tStr25.C                        \
	tStr26.C                        \
	tStr27.C			\
	tSubStr.C                       \
	tSubStr01.C                     \
	tSubStr02.C                     \
	tSubStr03.C                     \
	tSubStr04.C                     \
	tSubStr05.C                     \
	tSubStr06.C                     \
	tSubStr07.C                     \
	tDateTimeUtils.C                \
	tDateTime.C                     \
	tDateTime01.C                   \
	tDateTime02.C                   \
	tDateTime03.C                   \
	tDateTime04.C                   \
	tDateTime05.C                   \
	tDateTime06.C                   \
	tDateTime07.C                   \
	tDateTime08.C                   \
	tDateRange.C                    \
	tDateRangeDaily.C               \
	tDateRangeWeekly.C              \
	tFileOp.C			\
	tFileOp01.C			\
	tFileOp02.C			\
	tSortOrder.C                    \
	tDirectory.C			\
	tDirectory01.C			\
	tTimeIt.C			\
	tTimeIt01.C			\
	tVectorResync.C			\
	tLruMap.C			\
	tLruMap01.C			\
	tLruSash.C			\
	tLruSash01.C			\
	$(ARCH_CXX_C_SOURCES)           \

CXX_CC_SOURCES	=			
CXX_CPP_SOURCES	=			

USER_HH_INCS	=			\
	StlUtilsTest.hh                 \
	TestFunctProto.hh               \
	$(ARCH_USER_HH_INCS)            \

USER_INCLUDES	=		\
	$(USER_H_INCS)		\
	$(USER_HH_INCS)		\
	$(USER_II_INCS)		\

CXX_HEADERS	=			\
	StlUtilsTest.hh                 \
	TestFunctProto.hh               \
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

default debug test profile static shared:: $(generated_files)

default:: $(PROGRAM_DEFAULT)

debug test profile static shared::
	$(hide) $(MAKE) make_target=$@ $(PROGRAM_$($@))

all::	default debug test profile shared

install:: install_$(make_target)
	$(hide) echo + Installation Complete!

install_all:: 

install_all:: install_default install_debug install_profile install_static
	$(hide) echo + Installation Complete!

install_default:: default $(INSTALL_BIN_DIR)/$(PROGRAM_DEFAULT)
install_debug::   debug   $(INSTALL_BIN_DIR)/$(PROGRAM_DEBUG)
install_test::    test    $(INSTALL_BIN_DIR)/$(PROGRAM_TEST)
install_profile:: profile $(INSTALL_BIN_DIR)/$(PROGRAM_PROFILE)
install_static::  static  $(INSTALL_BIN_DIR)/$(PROGRAM_STATIC)
install_shared::  shared  $(INSTALL_BIN_DIR)/$(PROGRAM_SHARED)

check_default: test_data default 
	LD_LIBRARY_PATH=$(local_libdir) $(PROGRAM_DEFAULT) $(TEST)

check: test_data test
	LD_LIBRARY_PATH=$(PRJ_TOPDIR)/src/StlUtils:$(local_libdir) \
	  $(PROGRAM_TEST) $(TEST)

check_debug: debug
	$(PROGRAM_DEBUG) $(TEST)

test_data:
	chmod g+s $(TEST_DATA_DIR)
	chgrp $(TEST_GROUP) $(TEST_DATA_DIR)/FileStat.01
	chmod 664 $(TEST_DATA_DIR)/FileStat.01
	(cd $(TEST_DATA_DIR); ln -s FileStat.01 FileStat.l1)
	-touch $(TEST_DATA_DIR)/FileStat.set
	chmod 6 $(TEST_DATA_DIR)/FileStat.set
	-touch $(TEST_DATA_DIR)/FileStat.h.t.yyy.yyy.yyy
	chmod 777 $(TEST_DATA_DIR)/FileStat.h.t.yyy.yyy.yyy
	-touch $(TEST_DATA_DIR)/FileStat.h.t.nnn.nnn.nnn
	chmod 000 $(TEST_DATA_DIR)/FileStat.h.t.nnn.nnn.nnn
	-touch $(TEST_DATA_DIR)/FileStat.h.t.nnn.yyy.nnn
	chmod 070 $(TEST_DATA_DIR)/FileStat.h.t.nnn.yyy.nnn
	touch test_data

clean:: clean_test_data

clean_test_data: 
	rm -f $(TEST_DATA_DIR)/Str.bin.data			\
		$(TEST_DATA_DIR)/Str.operator.output		\
		$(TEST_DATA_DIR)/SubStr.operator.output		\
		$(TEST_DATA_DIR)/FileStat.l1			\
		$(TEST_DATA_DIR)/FileStat.set			\
		$(TEST_DATA_DIR)/FileStat.h.t.yyy.yyy.yyy	\
		$(TEST_DATA_DIR)/FileStat.h.t.nnn.nnn.nnn	\
		$(TEST_DATA_DIR)/FileStat.h.t.nnn.yyy.nnn	\
		$(TEST_DATA_DIR)/log.stream.test		\
		$(TEST_DATA_DIR)/logfile.01			\
		$(TEST_DATA_DIR)/logfile.02			\
		$(TEST_DATA_DIR)/logfile.03			\
		$(TEST_DATA_DIR)/logfile.04			\
		$(TEST_DATA_DIR)/logfile.05			\
		$(TEST_DATA_DIR)/logfile.05.tee			\
		$(TEST_DATA_DIR)/logfile.06			\
		$(TEST_DATA_DIR)/logfile.07			\
		$(TEST_DATA_DIR)/logfile.08			\
		$(TEST_DATA_DIR)/logfile.09			\
		$(TEST_DATA_DIR)/logfile.10			\
		$(TEST_DATA_DIR)/logfile.11			\
		$(TEST_DATA_DIR)/logfile.12			\
		$(TEST_DATA_DIR)/param.log.01			\
		test_data					\


#
# include dependancies generated by 'make depend'
#
-include .depend_$(make_target)

#
# =MAKEFILE_LOG=
#
# $Log$
# Revision 4.16  1999/11/09 11:11:00  houghton
# Added tParam03.C.
#
# Revision 4.15  1999/05/01 12:56:16  houghton
# Added tStr27.C
#
# Revision 4.14  1999/03/02 12:53:50  houghton
# Added tBetween.
#
# Revision 4.13  1998/11/02 19:36:03  houghton
# Changed: the File class was renamed to FileOp.
#
# Revision 4.12  1998/11/02 15:28:31  houghton
# Added LruSash
#
# Revision 4.11  1998/10/23 13:08:31  houghton
# Changed to use MakeConfigs 5.06.
#
# Revision 4.10  1998/10/13 16:35:58  houghton
# Added check targets.
# Changed test target to compile 'test' version.
#
# Revision 4.9  1998/10/13 15:20:59  houghton
# Added LruMap tests.
#
# Revision 4.8  1998/08/13 10:56:10  houghton
# Changed to use -lCommon_g.
#
# Revision 4.7  1998/04/02 14:19:04  houghton
# Changed to use MakeConfigs 5.05
#
#
# =MAKEFILE_LOG=
#

# Local Variables:
# mode:makefile
# End:

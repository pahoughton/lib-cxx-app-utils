# -*- makefile -*- for tClue
#
# Created: 4/28/96 using MakeConfigs 5.01.00.a.03
#
# $Id$
#
# (see end of file for Log info)

#
# Do not modifiy 'makefile_type'
makefile_type = prog
# This is the make.cfg version that will be used
make_cfg_ver	= 5.01
# Default target type
make_target	= default
# Uncomment 'show_commands' to output compile command.
show_commands = # true

# Include standard MakeConfig configuration for GNU make required
include Make/make.cfg.$(make_cfg_ver)

# 
# =USE_CURRENT_MAKEFILE=
# When you re-gen a make file, every thing between 
# these tags will be kept int the new makefile
# if you want it re-gen'd, just delete the tags
#

NAME		= Test

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
-include $(PRJ_TOPDIR)/src/arch/$(arch)/Makefile.$(NAME)

VPATH		= $(ARCH_VPATH):.

###### D E F I N E S  #####
# 
# Config defines avalable
#
#

TEST_DATA_DIR	= ../data
TEST_USER	= houghton
TEST_GROUP	= cirinv# tools
TEST_UID	= 253
TEST_GID	= 233

SRC_DEFINES	= -DTEST_DATA_DIR=\"$(TEST_DATA_DIR)\" 	\
		  -DTEST_USER=\"$(TEST_USER)\"		\
		  -DTEST_GROUP=\"$(TEST_GROUP)\"	\
		  -DTEST_UID=$(TEST_UID)		\
		  -DTEST_GID=$(TEST_GID)		\
		  -DTEST_LINE_PROGRESS=false

PRJ_DEFINES	= -DVERSION=\"$(VERSION)\" $(ARCH_DEFINES)

DEFAULT_DEFINES = -DTEST_DEFAULT=1
DEBUG_DEFINES	= -DTEST_DEBUG=1 -DCLUE_DEBUG=1
PROFILE_DEFINES	= -DTCLUE_PROFILE=1
STATIC_DEFINES	= -DTCLUE_STATIC=1

######  I N C L U D E S #####
#
# Config includes available (need to use -I)
#
# $(alpha_incdir) 	$(beta_incdir) 	$(local_incdir)
#


SRC_INC		= $(ARCH_INC) -I. 
PRJ_INC		= $($($(make_target))_PRJ_INC)

DEFAULT_PRJ_INC	= -I$(alpha_incdir)
DEBUG_PRJ_INC	= $(CLUE_SRC_INC) -I$(alpha_incdir)
PROFILE_PRJ_INC = $(CLUE_SRC_INC) -I$(alpha_incdir)
STATIC_PRJ_INC	= -I$(alpha_incdir)

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

DEFAULT_LD_LIBDIRS	= -L$(alpha_libdir)
DEBUG_LD_LIBDIRS	= $(CLUE_SRC_LDIR) -L$(alpha_libdir)
PRIFLE_LD_LIBDIRS	= $(DEFAULT_LD_LIBDIRS)
STATIC_LD_LIBDIRS	= $(DEFAULT_LD_LIBDIRS)

DEFAULT_LD_LIBS		= -lClue_s -lCommon_s 
DEBUG_LD_LIBS		= -lClue_g -lCommon 
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

CXX_C_SOURCES	=			\
	main.C                          \
	tArraySize.C                    \
	tDwordAlign.C                   \
	tMemOverlap.C                   \
	tAbsLong.C                      \
	tIsBaseDigit.C                  \
	tUnionOf.C                      \
	tRound.C                        \
	tBit.C                          \
	tCompare.C                      \
	tCompare01.C                    \
	tCompare02.C                    \
	tCharToInt.C                    \
	tSafeStrcpy.C                   \
	tStringCapitalize.C             \
	tStringCaseCompare.C            \
	tStringLower.C                  \
	tStringSearch.C                 \
	tStringTo.C                     \
	tStringUpper.C                  \
	tStripWhite.C                   \
	tbasename.C                     \
	tHeapBinStream.C		\
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
	tSubStr.C                       \
	tSubStr01.C                     \
	tSubStr02.C                     \
	tSubStr03.C                     \
	tSubStr04.C                     \
	tSubStr05.C                     \
	tSubStr06.C                     \
	tSubStr07.C                     \
	tRegexScan.C                    \
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
	tBitmask.C                      \
	tBitmask01.C                    \
	tBitmask02.C                    \
	tBitmask03.C                    \
	tFilePath.C                     \
	tFilePath01.C                   \
	tFilePath02.C                   \
	tFilePath03.C                   \
	tFilePath04.C                   \
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
	tParam.C                        \
	tParam01.C                      \
	tSortOrder.C                    \

hold = \
	tStrSet.C                       \
	tWithCommon.C                   \
	tWithCommon01.C                 \
	tWithCommon02.C                 \
	tWithWcf.C                      \
	tWithWcf01.C                    \
	tWithWcf02.C                    \
	$(ARCH_CXX_C_SOURCES)           \


USER_HH_INCS	=			\
	AppParam.hh                     \
	AvlTestData.hh                  \
	ClueTest.hh                     \
	DavlTestData.hh                 \
	StaticBinStream.hh              \
	StaticStream.hh                 \
	$(ARCH_USER_HH_INCS)            \

USER_INCLUDES	=		\
	$(USER_H_INCS)		\
	$(USER_HH_INCS)		\
	$(USER_II_INCS)		\

CXX_HEADERS	=			\
	AppParam.hh                     \
	AvlTestData.hh                  \
	ClueTest.hh                     \
	DavlTestData.hh                 \
	StaticBinStream.hh              \
	StaticStream.hh                 \
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

default debug profile:: proto

default:: $(PROGRAM_DEFAULT)

debug prifle static::
	$(hide) $(MAKE) make_target=$@ $(PROGRAM_$($@))

all::	default debug profile

test: test_data default 
	 LD_LIBRARY_PATH=$(TOOL_DIR)/lib/alpha $(NAME)

test_debug: test_data debug
	 LD_LIBRARY_PATH=$(PRJ_TOPDIR)/src/Clue:/usr/local/lib/alpha $(NAME)_g

test_data: 
	chgrp $(TEST_GROUP) $(TEST_DATA_DIR)/FileStat.01
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
# Revision 2.11  1996/05/14 14:19:13  houghton
# Rework libs for AIX. (this will change)
#
# Revision 2.10  1996/05/11 11:03:36  houghton
# Cleanup.
#
# Revision 2.9  1996/05/03 16:17:19  houghton
# Added defines to easy multi platform test.
#
# Revision 2.8  1996/05/02 11:06:24  houghton
# Changed PRJ_TOPDIR for new dir structure.
# Rework test_data targets.
#
# Revision 2.7  1996/05/01 11:34:33  houghton
# Restructure directories to Test01/src and Test01/data
# Added TEST_DATA_DIR define.
#
# Revision 2.6  1996/05/01 11:05:07  houghton
# Changed to use MakeConfigs 5
#
#
# =MAKEFILE_LOG=
#




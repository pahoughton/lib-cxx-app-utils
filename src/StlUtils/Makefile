# -*- makefile -*- for Clue
#
# Created: 4/17/96 using MakeConfigs 5.01.00.a.02
#
# $Id$
#
# (see end of file for Log info)

#
# Do not modifiy 'makefile_type'
makefile_type   = lib
# This is the make.cfg version that will be used
make_cfg_ver	= 5.01
# Default target type
make_target	= default
# Uncomment 'show_compile_command' to output compile command.
show_commands 	= # true

# Include standard MakeConfig configuration for GNU make required
include Make/make.cfg.$(make_cfg_ver)

# 
# =USE_CURRENT_MAKEFILE=
# When you re-gen a make file, every thing between 
# these tags will be kept in the new makefile
# if you want it re-gen'd, just delete the tags
#

NAME		= Clue

INSTALL_LIBDIR	= $(alpha_libdir)
INSTALL_INCDIR	= $(alpha_incdir)

VER_MAJOR	= 2
VER_MINOR	= 01
VER_RELEASE	= 00.a.4
VERSION		= $(VER_MAJOR).$(VER_MINOR).$(VER_RELEASE)

LIBRARY_DEFAULT	= lib$(NAME).a
LIBRARY_DEBUG	= lib$(NAME)_g.a
LIBRARY_PROFILE	= lib$(NAME)_pg.a
LIBRARY_SHARED	= lib$(NAME)$(shlib_ext)

PRJ_TOPDIR	= .

# include any arch specific makefile component
-include ../arch/$(arch)/Makefile.$(NAME)

VPATH		= $(ARCH_VPATH):.

###### D E F I N E S  #####
# 
# Config defines avalable
#
#


SRC_DEFINES	= 
PRJ_DEFINES	= -DVERSION=\"$(VERSION)\" $(ARCH_DEFINES)

DEFAULT_DEFINES = -DCLUE_DEFAULT=1
DEBUG_DEFINES	= -DCLUE_DEBUG=1
PROFILE_DEFINES	= -DCLUE_PROFILE=1
SHARED_DEFINES	= -DCLUE_SHARED=1

######  I N C L U D E S #####
#
# Config includes available
#
# $(alpha_incdir) 	$(beta_incdir) 	$(local_incdir)
#


SRC_INC		= $(ARCH_INC) -I. -I$(PRJ_TOPDIR)
PRJ_INC		= -I$(alpha_incdir)


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


CC_FLAGS		= $(cc_warn) $(ARCH_CC_FLAGS)

DEFAULT_CC_FLAGS	= $(cc_optimize)
DEBUG_CC_FLAGS		= $(cc_debug)
PROFILE_CC_FLAGS	= $(cc_profile)
SHARED_CC_FLAGS		= $(cc_shared) $(cc_optimize)

CXX_FLAGS		= $(cxx_warn) $(ARCH_CXX_FLAGS)

DEFAULT_CXX_FLAGS	= $(cxx_optimize)
DEBUG_CXX_FLAGS		= $(cxx_debug)
PROFILE_CXX_FLAGS	= $(cxx_profile)
SHARED_CXX_FLAGS	= $(cxx_shared) $(cxx_optimize)

# **** S H A R E D   D E P   L I B S *****

SHDEP_LIBS		= -lc

# **** I N S T A L L ****

INSTALL_LIB_FLAGS	= 
INSTALL_INC_FLAGS	= 

#
# =USE_CURRENT_MAKEFILE=
#

# **** S O U R C E   F I L E S ****

C_SOURCES	=			\
	$(ARCH_C_SOURCES)               \

CXX_C_SOURCES	=			\
	BinStream.C                     \
	Bitmask.C                       \
	ClassVersion.C                  \
	DateRange.C                     \
	DateRangeDaily.C                \
	DateRangeWeekly.C               \
	DateTime.C                      \
	DateTimeUtils.C                 \
	FilePath.C                      \
	HeapBinStream.C                 \
	HeapNetStream.C                 \
	HeapStream.C                    \
	LibTest.C                       \
	Log.C                           \
	LogBuf.C                        \
	LogLevel.C                      \
	Mutex.C                         \
	NetStream.C                     \
	Param.C                         \
	RandomBinStream.C               \
	RandomStream.C                  \
	RegexScan.C                     \
	SizeIt.C                        \
	Str.C                           \
	StrStreambuf.C                  \
	StringCapitalize.C              \
	StringCaseCompare.C             \
	StringCaseReverseSearch.C       \
	StringCaseSearch.C              \
	StringLower.C                   \
	StringReverseSearch.C           \
	StringSearch.C                  \
	StringTo.C                      \
	StringUpper.C                   \
	StripWhite.C                    \
	SubStr.C                        \
	ThreadBase.C                    \
	Timer.C                         \
	Void.C                          \
	$(ARCH_CXX_C_SOURCES)           \


USER_H_INCS	=			\
	ClueVersion.h                   \
	$(ARCH_USER_H_INCS)             \

USER_HH_INCS	=			\
	BinStream.hh                    \
	Bit.hh                          \
	Bitmask.hh                      \
	ClassVersion.hh                 \
	Clue.hh                         \
	ClueVersion.hh                  \
	Compare.hh                      \
	DateRange.hh                    \
	DateRangeDaily.hh               \
	DateRangeWeekly.hh              \
	DateTime.hh                     \
	DateTimeUtils.hh                \
	FilePath.hh                     \
	HeapBinStream.hh                \
	HeapNetStream.hh                \
	HeapStream.hh                   \
	HeapStreambuf.hh                \
	LibLog.hh                       \
	LibTest.hh                      \
	Log.hh                          \
	LogBuf.hh                       \
	LogLevel.hh                     \
	MinMax.hh                       \
	Mutex.hh                        \
	NetStream.hh                    \
	Param.hh                        \
	RandomBinStream.hh              \
	RandomStream.hh                 \
	RegexScan.hh                    \
	SizeIt.hh                       \
	Sort.hh                         \
	SortOrder.hh                    \
	Str.hh                          \
	StrStreambuf.hh                 \
	StringUtils.hh                  \
	SubStr.hh                       \
	ThreadBase.hh                   \
	Timer.hh                        \
	Void.hh                         \
	$(ARCH_USER_HH_INCS)            \

USER_II_INCS	=			\
	BinStream.ii                    \
	Bit.ii                          \
	Bitmask.ii                      \
	ClassVersion.ii                 \
	Clue.ii                         \
	DateRange.ii                    \
	DateRangeDaily.ii               \
	DateRangeWeekly.ii              \
	DateTime.ii                     \
	DateTimeUtils.ii                \
	FilePath.ii                     \
	HeapStream.ii                   \
	Log.ii                          \
	LogBuf.ii                       \
	LogLevel.ii                     \
	Mutex.ii                        \
	Param.ii                        \
	RandomBinStream.ii              \
	RandomStream.ii                 \
	SizeIt.ii                       \
	SortOrder.ii                    \
	Str.ii                          \
	StrStreambuf.ii                 \
	StringUtils.ii                  \
	SubStr.ii                       \
	ThreadBase.ii                   \
	Timer.ii                        \
	ThreadBase.ii			\
	Void.ii                         \
	$(ARCH_USER_II_INCS)            \

USER_INCLUDES	=		\
	$(USER_H_INCS)		\
	$(USER_HH_INCS)		\
	$(USER_II_INCS)		\

C_HEADERS	=			\
	ClueVersion.h                   \
	rx.h                            \
	$(ARCH_C_HEADERS)               \

CXX_HEADERS	=			\
	BinStream.hh                    \
	Bit.hh                          \
	Bitmask.hh                      \
	ClassVersion.hh                 \
	Clue.hh                         \
	ClueVersion.hh                  \
	Compare.hh                      \
	DateRange.hh                    \
	DateRangeDaily.hh               \
	DateRangeWeekly.hh              \
	DateTime.hh                     \
	DateTimeUtils.hh                \
	FilePath.hh                     \
	HeapBinStream.hh                \
	HeapNetStream.hh                \
	HeapStream.hh                   \
	HeapStreambuf.hh                \
	LibLog.hh                       \
	LibTest.hh                      \
	Log.hh                          \
	LogBuf.hh                       \
	LogLevel.hh                     \
	MinMax.hh                       \
	Mutex.hh                        \
	NetStream.hh                    \
	Param.hh                        \
	RandomBinStream.hh              \
	RandomStream.hh                 \
	RegexScan.hh                    \
	SizeIt.hh                       \
	Sort.hh                         \
	SortOrder.hh                    \
	Str.hh                          \
	StrStreambuf.hh                 \
	StringUtils.hh                  \
	SubStr.hh                       \
	ThreadBase.hh                   \
	Threaded.hh                     \
	Timer.hh                        \
	Void.hh                         \
	_Clue.hh                        \
	$(ARCH_CXX_HEADERS)             \

CXX_INLINES	=			\
	BinStream.ii                    \
	Bit.ii                          \
	Bitmask.ii                      \
	ClassVersion.ii                 \
	Clue.ii                         \
	DateRange.ii                    \
	DateRangeDaily.ii               \
	DateRangeWeekly.ii              \
	DateTime.ii                     \
	DateTimeUtils.ii                \
	FilePath.ii                     \
	HeapStream.ii                   \
	Log.ii                          \
	LogBuf.ii                       \
	LogLevel.ii                     \
	Mutex.ii                        \
	Param.ii                        \
	RandomBinStream.ii              \
	RandomStream.ii                 \
	SizeIt.ii                       \
	SortOrder.ii                    \
	Str.ii                          \
	StrStreambuf.ii                 \
	StringUtils.ii                  \
	SubStr.ii                       \
	ThreadBase.ii                   \
	Timer.ii                        \
	Void.ii                         \
	$(ARCH_CXX_INLINES)             \



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

tvp:
	echo $(UNIX_VPATH)
	echo $(CLUE1_VPATH)
	echo $(ARCH_VPATH)

default debug profile shared:: proto

default:: $(LIBRARY_$($(make_target)))

debug profile shared:: 
	$(hide) $(MAKE) make_target=$@ $(LIBRARY_$($@))

all::	default debug profile shared


install:: install_lib_check install_$(make_target)
	$(HIDE) echo Installation Complete!

install_all:: install_lib_check

install_all:: install_default install_debug install_profile install_shared
	$(HIDE) echo Installation Complete!

install_default:: default $(INSTALL_LIBDIR)/$(LIBRARY_DEFAULT)
install_debug::   debug   $(INSTALL_LIBDIR)/$(LIBRARY_DEBUG)
install_profile:: profile $(INSTALL_LIBDIR)/$(LIBRARY_PROFILE)
install_shared::  shared  $(INSTALL_LIBDIR)/$(LIBRARY_SHARED)


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





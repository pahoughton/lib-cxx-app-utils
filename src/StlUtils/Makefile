#
# -*- Makefile -*- for Clue src/Clue dir
#
# Created: 11/21/95 using MakeConfigs 4.00.00.a.09
#
# $Id$
#
# (see end of file for Log info)

#
# Do not modifiy 'makefile_type'
makefile_type   = library
# Uncomment 'show_compile_command' to output compile command.
show_commands = # true

# Include standard MakeConfig configuration for GNU make required
include Make/make.cfg.4.01

# 
# =USE_CURRENT_MAKEFILE=
# When you re-gen a make file, every thing between 
# these tags will be kept in the new makefile
# if you want it re-gen'd, just delete the tags
#

NAME		= Clue

INSTALL_LIBDIR	= $(LOCAL_ALPHA_LIBDIR)
INSTALL_INCDIR	= $(LOCAL_ALPHA_INCDIR)

VER_MAJOR	= 2
VER_MINOR	= 00
VER_RELEASE	= 00.a.10
VERSION		= $(VER_MAJOR).$(VER_MINOR).$(VER_RELEASE)

LIBRARY_DEFAULT	= lib$(NAME).a
LIBRARY_DEBUG	= lib$(NAME)g.a
LIBRARY_PROFILE	= lib$(NAME)pg.a
LIBRARY_SHARED	= lib$(NAME)$(SHLIB_EXT)

include ../arch/$(arch)/src/Makefile.Clue

###### D E F I N E S  #####
# 
# Config defines avalable
#
# $(X11_DEF)	    defines for X11
# $(SYB_DEF)	    defines for SYB
# $(MMALLOC_DEF)    defines for libmmalloc
# $(DATA_DEF)	    defines for libData (C++)
# $(CLUE_DEF)	    defines for libClue (C++)
# $(COMMON_DEF)	    defines for libCommon
# $(WT_DEF)	    defines for libWt
# $(WCF_DEF)	    defines for libWcf (CommFabric)
#


SRCDEFINES	=

PRJDEFINES	= -DVERSION=\"$(VERSION)\" $(ARCH_DEFINES)

DEFINES		= $(PRJDEFINES) $(SRCDEFINES) 

######  I N C L U D E S #####
#
# Config includes available
#
# $(X11_INC)
# $(SYB_INC)
# $(MALLOC_ALPHA_INC)	$(MMALLOC_BETA_INC)	$(MMALLOC_INC)
# $(DATA_ALPHA_INC) 	$(DATA_BETA_INC) 	$(DATA_INC)
# $(CLUE_ALPHA_INC)	$(CLUE_BETA_INC) 	$(CLUE_INC)
# $(COMMON_ALPHA_INC)	$(COMMON_BETA_INC) 	$(COMMON_INC)
# $(WT_ALPHA_INC) 	$(WT_BETA_INC) 		$(WT_INC)
# $(WCF_ALPHA_INC) 	$(WCF_BETA_INC) 	$(WCF_INC)
#
# $(LOCAL_ALPHA_INC) 	$(LOCAL_BETA_INC) 	$(LOCAL_INC)
#


#TOPDIR		=

SRCINCDIR	= -I. $(ARCH_INCDIR) $(COMMON_ALPHA_INC) 
PRJINCDIR	= 

INCDIRS		= $(SRCINCDIR)	\
		  $(PRJINCDIR)

###### C O M P I L E / C P P #####
#
# Config flags available
#
# $(CC_OPTIMIZE) $(CXX_OPTIMIZE)
# $(CC_DEBUG)	 $(CXX_DEBUG)
# $(CC_PROFILE)	 $(CXX_PROFILE)
# $(CC_WARN)	 $(CXX_WARN)
#


CPPOTHER 	=

CCDEBUG		= $(CC_OPTIMIZE)
CCOTHER		= $(CC_WARN)

CXXDEBUG	= $(CXX_OPTIMIZE)
CXXOTHER	= $(CXX_WARN)

# **** I N S T A L L ****

INSTALL_LIB_FLAGS	= 
INSTALL_INC_FLAGS	= 


OBJECTS_DEFAULT	= $(ARCH_OBJECTS_DEFAULT)
OBJECTS_DEBUG	= $(ARCH_OBJECTS_DEBUG)
OBJECTS_PROFILE	= $(ARCH_OBJECTS_PROFILE)
OBJECTS_SHARED	= $(ARCH_OBJECTS_SHARED)

DEPEND_CXX_SOURCES = $(CXX_SOURCES) $(ARCH_DEPEND_CXX_SOURCES)

#
# =USE_CURRENT_MAKEFILE=
#

# **** S O U R C E   F I L E S ****

C_SOURCES	=			\
	$(ARCH_C_SOURCES)		\

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
	NetStream.C                     \
	Param.C                         \
	RandomBinStream.C               \
	RandomStream.C                  \
	RegexScan.C                     \
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
	Thread.C			\
	Timer.C                         \
	Void.C                          \
	$(ARCH_CXX_C_SOURCES)           \


USER_H_INCS	=			\
	$(ARCH_USER_H_INCS)		\

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
	LibTest.hh                      \
	Log.hh                          \
	LogBuf.hh                       \
	LogLevel.hh                     \
	MinMax.hh                       \
	NetStream.hh                    \
	Param.hh                        \
	RandomBinStream.hh              \
	RandomStream.hh                 \
	RegexScan.hh                    \
	SortOrder.hh                    \
	Str.hh                          \
	StrStreambuf.hh                 \
	StringUtils.hh                  \
	SubStr.hh                       \
	Thread.hh			\
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
	Param.ii                        \
	RandomBinStream.ii              \
	RandomStream.ii                 \
	SortOrder.ii                    \
	Str.ii                          \
	StrStreambuf.ii                 \
	StringUtils.ii                  \
	SubStr.ii                       \
	Thread.ii			\
	Timer.ii                        \
	Void.ii                         \
	$(ARCH_USER_II_INCS)            \

USER_INCLUDES	=		\
	$(USER_H_INCS)		\
	$(USER_HH_INCS)		\
	$(USER_II_INCS)		\

C_HEADERS	=			\
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
	LibTest.hh                      \
	Log.hh                          \
	LogBuf.hh                       \
	LogLevel.hh                     \
	MinMax.hh                       \
	NetBinStream.hh                 \
	NetStream.hh                    \
	Param.hh                        \
	RandomBinStream.hh              \
	RandomStream.hh                 \
	RegexScan.hh                    \
	Sort.hh                         \
	SortOrder.hh                    \
	Str.hh                          \
	StrStreambuf.hh                 \
	StringUtils.hh                  \
	SubStr.hh                       \
	Thread.hh			\
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
	Param.ii                        \
	RandomBinStream.ii              \
	RandomStream.ii                 \
	SortOrder.ii                    \
	Str.ii                          \
	StrStreambuf.ii                 \
	StringUtils.ii                  \
	SubStr.ii                       \
	Thread.ii			\
	Timer.ii                        \
	Void.ii                         \
	$(ARCH_CXX_INLINES)             \



###### T A R G E T S #####
#
# Targets defined in make.cfg.targets.
#
# default: 	all
# depend:	create .depend
# profile:	MAKE CCDEBUG=CC_PROFILE all
# proto:	create $(PROTO_H)
# clean:  	rm -f LIB_OBJECTS LIBRARY
# realclean:	rm -f LIB_OBJECTS LIBRARY .depend.lib PROTO_H TAGS
# tags:		create TAGS using etags
#


include Make/make.cfg.targets.4.00


default debug shared:: proto

default:: objects/default $(LIBRARY_DEFAULT)

all::	default debug profile shared

debug:: objects/debug
	$(HIDE) $(MAKE) CCDEBUG='$(CC_DEBUG)' CXXDEBUG='$(CXX_DEBUG)' \
			PRJDEFINES='$(PRJDEFINES) -DCLUE_DEBUG=1' \
			$(LIBRARY_DEBUG)

profile:: objects/profile
	$(HIDE) $(MAKE) CCDEBUG='$(CC_PROFILE)' CXXDEBUG='$(CXX_PROFILE)' \
			$(LIBRARY_PROFILE)

shared:: objects/shared
	$(HIDE) $(MAKE) CCDEBUG='$(CCDEBUG) $(CC_SHARED)' \
			CXXDEBUG='$(CXXDEBUG) $(CXX_SHARED)' \
			$(LIBRARY_SHARED)


install:: install_lib_check install_default
	$(HIDE) echo Installation Complete!

install_all:: install_lib_check

install_all:: install_default install_debug install_profile install_shared
	$(HIDE) echo Installation Complete!

install_default:: default $(INSTALL_LIBDIR)/$(LIBRARY_DEFAULT)
install_debug::   debug   $(INSTALL_LIBDIR)/$(LIBRARY_DEBUG)
install_profile:: profile $(INSTALL_LIBDIR)/$(LIBRARY_PROFILE)
install_shared::  shared  $(INSTALL_LIBDIR)/$(LIBRARY_SHARED)

tst:
	@echo $(OBJECTS_DEFAULT)

test::	default

FORCE: 

#
# include dependancies generated by 'make depend'
#
-include .depend


#
# =MAKEFILE_LOG=
#
# $Log$
# Revision 2.5  1996/02/29 19:05:52  houghton
# Changed to use MakeConfigs 4.01
#
# Revision 2.4  1995/12/04 11:18:02  houghton
# Changed to use MakeConfig 4.
#
# Revision 2.3  1995/11/12  18:07:15  houghton
# Change to use MakeConfigs 3.5.
# Added Void.(C,hh,ii).
# Removed regex.(c,h) (now in libCommon GnuRegex).
#
# Revision 2.2  1995/11/10  18:47:14  houghton
# *** empty log message ***
#
# Revision 2.1  1995/11/10  12:40:49  houghton
# Change to Version 2
#
# Revision 1.20  1995/11/10  12:03:21  houghton
# Change install dir from BETA to ALPHA
#
# Revision 1.19  1995/11/10  00:30:43  houghton
# Change to MakeConfigs 3.4
#
# =MAKEFILE_LOG=
#





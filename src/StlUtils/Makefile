#
# Makefile for Clue
#
#
# Created: 9/25/95
#
# $Id$
#
# (see end of file for Log info)

#
# Include standard MakeConfig configuration for GNU make required
#

makefile_type   = library

include Make/make.cfg.3.0

BETA_DIR	= /home/houghton/prj/CirInv
BETA_LIB_DIR	= $(BETA_DIR)/lib
BETA_INC_DIR	= $(BETA_DIR)/include

PROD_LIB_DIR	= 
PROD_INC_DIR	= 

LIBRARY		= libClue.a

PROTO_H		= _Clue_Proto.h

# **** S O U R C E   F I L E S ****

C_SOURCES	=			\
	regex.c                         \
	$(CLUE1_C_SOURCES)		\


CLUE1_C_SOURCES = 			\
	../Clue1/src/TeleNumDataFromString.c		\
	../Clue1/src/TeleNumDataToString.c		\

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
	Timer.C                         \
	$(ARCH_CXX_C_SOURCES)		\
	$(CLUE1_CXX_C_SOURCES)		\


UNIX_CXX_C_SOURCES    =			\
	../arch/Unix/src/basename.C	\
	../arch/Unix/src/OpenFlags.C	\
	../arch/Unix/src/User.C		\
	../arch/Unix/src/UserGroup.C	\
	../arch/Unix/src/FileStat.C	\

ifeq ($(arch),Linux)
ARCH_CXX_C_SOURCES = $(UNIX_CXX_C_SOURCES)	\

endif

ifeq ($(arch),AIX)
ARCH_CXX_C_SOURCES = $(UNIX_CXX_C_SOURCES)	\

endif


CLUE1_CXX_C_SOURCES =				\
	../Clue1/src/AvlTreeAddrBase.C		\
	../Clue1/src/AvlTreeOffsetBase.C	\
	../Clue1/src/DavlTreeOffsetBase.C	\
	../Clue1/src/Field.C			\
	../Clue1/src/FixedCharFile.C		\
	../Clue1/src/FixedCharRec.C		\
	../Clue1/src/MapFile.C			\
	../Clue1/src/MapMem.C			\
	../Clue1/src/MapMemFixedDynamic.C	\
	../Clue1/src/MultiMem.C			\
	../Clue1/src/MultiMemOffset.C		\
	../Clue1/src/MultiMemOffsetMapFixed.C	\
	../Clue1/src/Record.C			\
	../Clue1/src/TeleNum.C			\



CXX_CC_SOURCES	=			\

CXX_CPP_SOURCES	=			\

USER_INCS	=			\
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
	Timer.hh                        \
	regex.h                         \
	$(USER_INLINES)			\
	$(ARCH_CXX_INCLUDES)		\
	$(CLUE1_CXX_INCLUDES)		\
	$(CLUE1_INCLUDES)		\

USER_INLINES =				\
	ClassVersion.ii			\
	Clue.ii				\
	Bit.ii				\
	StringUtils.ii			\
	DateTimeUtils.ii		\
	SortOrder.ii			\


UNIX_CXX_INCLUDES    =			\
	../arch/Unix/src/ClueExceptions.hh	\
	../arch/Unix/src/User.hh		\
	../arch/Unix/src/UserGroup.hh		\
	../arch/Unix/src/FileStat.hh		\

ifeq ($(arch),Linux)
ARCH_CXX_INCLUDES = $(UNIX_CXX_INCLUDES)	\
	../arch/$(arch)/src/ClueConfig.hh	\
	../arch/$(arch)/stdc++/fstream		\
	../arch/$(arch)/stdc++/iomanip		\
	../arch/$(arch)/stdc++/iostream		\
	../arch/$(arch)/stdc++/strstream	\

endif

ifeq ($(arch),AIX)
ARCH_CXX_INCLUDES = $(UNIX_CXX_INCLUDES)	\
	../arch/$(arch)/src/ClueConfig.hh	\
	../arch/$(arch)/src/AnsiBool.hh		\
	../arch/$(arch)/stdc++/algo.h		\
	../arch/$(arch)/stdc++/algobase.h	\
	../arch/$(arch)/stdc++/algorithm	\
	../arch/$(arch)/stdc++/bool.h		\
	../arch/$(arch)/stdc++/bvector.h	\
	../arch/$(arch)/stdc++/cctype		\
	../arch/$(arch)/stdc++/cerrno		\
	../arch/$(arch)/stdc++/climits		\
	../arch/$(arch)/stdc++/cmath		\
	../arch/$(arch)/stdc++/cstddef		\
	../arch/$(arch)/stdc++/cstdio		\
	../arch/$(arch)/stdc++/cstdlib		\
	../arch/$(arch)/stdc++/cstring		\
	../arch/$(arch)/stdc++/ctime		\
	../arch/$(arch)/stdc++/defalloc.h	\
	../arch/$(arch)/stdc++/deque.h		\
	../arch/$(arch)/stdc++/faralloc.h	\
	../arch/$(arch)/stdc++/fdeque.h		\
	../arch/$(arch)/stdc++/flist.h		\
	../arch/$(arch)/stdc++/fmap.h		\
	../arch/$(arch)/stdc++/fmultmap.h	\
	../arch/$(arch)/stdc++/fmultset.h	\
	../arch/$(arch)/stdc++/fset.h		\
	../arch/$(arch)/stdc++/fstream		\
	../arch/$(arch)/stdc++/function.h	\
	../arch/$(arch)/stdc++/functional	\
	../arch/$(arch)/stdc++/hdeque.h		\
	../arch/$(arch)/stdc++/heap.h		\
	../arch/$(arch)/stdc++/hlist.h		\
	../arch/$(arch)/stdc++/hmap.h		\
	../arch/$(arch)/stdc++/hmultmap.h	\
	../arch/$(arch)/stdc++/hmultset.h	\
	../arch/$(arch)/stdc++/hset.h		\
	../arch/$(arch)/stdc++/hugalloc.h	\
	../arch/$(arch)/stdc++/hvector.h	\
	../arch/$(arch)/stdc++/iomanip		\
	../arch/$(arch)/stdc++/iostream		\
	../arch/$(arch)/stdc++/iterator		\
	../arch/$(arch)/stdc++/iterator.h	\
	../arch/$(arch)/stdc++/lbvector.h	\
	../arch/$(arch)/stdc++/ldeque.h		\
	../arch/$(arch)/stdc++/list.h		\
	../arch/$(arch)/stdc++/llist.h		\
	../arch/$(arch)/stdc++/lmap.h		\
	../arch/$(arch)/stdc++/lmultmap.h	\
	../arch/$(arch)/stdc++/lmultset.h	\
	../arch/$(arch)/stdc++/lngalloc.h	\
	../arch/$(arch)/stdc++/lset.h		\
	../arch/$(arch)/stdc++/map.h		\
	../arch/$(arch)/stdc++/multimap.h	\
	../arch/$(arch)/stdc++/multiset.h	\
	../arch/$(arch)/stdc++/neralloc.h	\
	../arch/$(arch)/stdc++/new		\
	../arch/$(arch)/stdc++/nmap.h		\
	../arch/$(arch)/stdc++/nmultmap.h	\
	../arch/$(arch)/stdc++/nmultset.h	\
	../arch/$(arch)/stdc++/nset.h		\
	../arch/$(arch)/stdc++/pair.h		\
	../arch/$(arch)/stdc++/projectn.h	\
	../arch/$(arch)/stdc++/set		\
	../arch/$(arch)/stdc++/set.h		\
	../arch/$(arch)/stdc++/stack.h		\
	../arch/$(arch)/stdc++/stddef		\
	../arch/$(arch)/stdc++/strstream	\
	../arch/$(arch)/stdc++/tempbuf.h	\
	../arch/$(arch)/stdc++/tree.h		\
	../arch/$(arch)/stdc++/vector		\
	../arch/$(arch)/stdc++/vector.h		\


endif

CLUE1_CXX_INCLUDES = 				\
	../Clue1/src/AvlTreeAddrBase.hh		\
	../Clue1/src/AvlTreeBase.hh		\
	../Clue1/src/AvlTreeOffset.hh		\
	../Clue1/src/AvlTreeOffsetBase.hh	\
	../Clue1/src/DavlTreeOffset.hh		\
	../Clue1/src/DavlTreeOffsetBase.hh	\
	../Clue1/src/Field.hh			\
	../Clue1/src/FixedCharFile.hh		\
	../Clue1/src/FixedCharRec.hh		\
	../Clue1/src/MapFile.hh			\
	../Clue1/src/MapMem.hh			\
	../Clue1/src/MapMemFixedDynamic.hh	\
	../Clue1/src/MultiMem.hh		\
	../Clue1/src/MultiMemOffset.hh		\
	../Clue1/src/MultiMemOffsetMapFixed.hh	\
	../Clue1/src/Record.hh			\
	../Clue1/src/TeleNum.hh			\

CLUE1_INCLUDES = 			\
	../Clue1/src/TeleNum.h


C_HEADERS	=			\
	regex.h                         \

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
	Timer.hh                        \
	_Clue.hh                        \

# 
# =USE_CURRENT_MAKEFILE=
# When you re-gen a make file, every thing between 
# these tags will be kept int the new makefile
# if you want it re-gen'd, just delete the tags
#

# *****  D E F I N E S  *****
#
# Config defines avalable
#
# $(MMALLOC_DEF)    defines for libmmalloc
# $(X11_DEF)	    defines for using X11
# $(CF_DEF)	    defineds for using libWcf (CommFabric)
#

SRCDEFINES	= 
PRJDEFINES	= -DCLUE_DEBUG

DEFINES		= $(PRJDEFINES) $(SRCDEFINES) 

# *****  I N C L U D E S *****
#
# Config includes available
#
# $(LOCAL_BETA_INC)
# $(LOCAL_INC)
# $(COMMON_BETA_INC)
# $(COMMON_INC)
# $(CF_BETA_INC)
# $(CF_INC)
# $(MMALLOC_BETA_INC)
# $(MMALLOC_INC)
# $(SYB_INC)
# $(X11_INC)

#TOPDIR		=

SRCINCDIR	= -I.
PRJINCDIR	= -I../arch/$(arch)/src \
		  -I../arch/$(arch)/stdc++ \
		  -I../arch/Unix/src \
		  -I../Clue1/src \
		  -I/home/houghton/prj/CirInv/include
		  


INCDIRS		= $(SRCINCDIR)	\
		  $(PRJINCDIR)


# **** C O M P I L E / C P P ****
#
# Config flags available
#
# $(CC_OPTIMIZE)
# $(CC_DEBUG)
# $(CC_PROFILE)
#

CPPOTHER 	=
CCDEBUG		= $(CC_DEBUG)
CCOTHER		=

# **** I N S T A L L ****

INSTALL_LIB_FLAGS	= -m 664
INSTALL_INC_FLAGS	= -m 664
INSTALL_MAN_FLAGS	= -m 664

# ***** D E P E N D A N C I E S *****

# =USE_CURRENT_MAKEFILE=

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
#

include Make/make.cfg.targets.3.0


all: $(PROTO_H) $(LIBRARY)

$(LIBRARY): $(OBJECTS) 
	$(UPDATELIB) $@ $?

install:
	mkdirhier $(BETA_LIB_DIR)/old
	mkdirhier $(BETA_INC_DIR)/old
	-( cd $(BETA_LIB_DIR)/old; rm -f $(LIBRARY); cd ..; mv $(LIBRARY) old )
	-( cd $(BETA_INC_DIR)/old; rm -f $(USER_INCS); cd ..; mv $(USER_INCS) old )
	$(INSTALL) $(INSTALL_LIB_FLAGS) $(LIBRARY) $(BETA_LIB_DIR)
	$(INSTALL) $(INSTALL_INC_FLAGS) $(USER_INCS) $(BETA_INC_DIR)
	echo 'Beta Install Complete!'


install_production:
	mkdirhier $(PROD_LIB_DIR)/old
	mkdirhier $(PROD_INC_DIR)/old
	-( cd $(PROD_LIB_DIR)/old; rm -f $(LIBRARY); cd ..; mv $(LIBRARY) old )
	-( cd $(PROD_INC_DIR)/old; rm -f $(USER_INCS); cd ..; mv $(USER_INCS) old )
	$(INSTALL) $(INSTALL_LIB_FLAGS) $(LIBRARY) $(PROD_LIB_DIR)
	$(INSTALL) $(INSTALL_INC_FLAGS) $(USER_INCS) $(PROD_INC_DIR)
	echo 'Production Install Complete!'

#
# include dependancies generated by 'make depend'
#
include .depend

# 
# $Log$
# Revision 1.18  1995/11/05 16:32:20  houghton
# Revised
#
# Revision 1.2  1995/02/13  17:35:10  houghton
# Major enhancements much cleaner
#
# Revision 1.1  1994/01/23  18:16:55  houghton
# Production release 1.0 of MakeConfig system
#
#




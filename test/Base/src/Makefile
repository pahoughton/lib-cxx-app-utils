#
# -*- Makefile -*- for t
#
# Created: 1/4/96 using MakeConfigs 4.00.00.a.12
#
# $Id$
#
# (see end of file for Log info)

#
# Include standard MakeConfig configuration for GNU make required
#

#
# Do not modifiy 'makefile_type'
makefile_type = program
# Uncomment 'show_commands' to output compile command.
show_commands = # true

# Include standard MakeConfig configuration for GNU make required
include Make/make.cfg.4.00

# 
# =USE_CURRENT_MAKEFILE=
# When you re-gen a make file, every thing between 
# these tags will be kept int the new makefile
# if you want it re-gen'd, just delete the tags
#

NAME		= t

INSTALL_BINDIR	= $(LOCAL_BIN_DIR)

VER_MAJOR	= 1
VER_MINOR	= 00
VER_RELEASE	= 00.a.01
VERSION		= $(VER_MAJOR).$(VER_MINOR).$(VER_RELEASE)

PROGRAM_DEFAULT	= $(NAME)
PROGRAM_DEBUG	= $(NAME)g
PROGRAM_PROFILE	= $(NAME)pg

include ../../src/arch/$(arch)/test/Makefile.Test


###### D E F I N E S  #####
# 
# Config defines avalable
#
# $(X11_DEF)	    defines for X11
# $(SYB_DEF)	    defines for SYB
#


SRCDEFINES	= 
PRJDEFINES	= -DVERSION=\"$(VERSION)\"

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


# TOPDIR	=

CLUE_SRC_DIR	= ../../src/Clue 
CLUE_INCDIR	= -I$(CLUE_SRC_DIR) \
		  -I../../src/Clue1/src \
		  -I../../src/arch/$(arch)/test

SRCINCDIR	= -I. $(CLUE_INCDIR) $(WCF_ALPHA_INC)
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

# ##### I N S T A L L #####

INSTALL_BIN_FLAGS	= 

# ##### L I N K  /  L I B R A R I E S #####
#
# Config flags available
#
# $(LD_OPTIMIZE)
# $(LD_DEBUG)
# $(LD_PROFILE)
#
# Config libraryies available
#
# $(X11_LIBS)
# $(XAW_LIBS)
# $(XM_LIBS)
# $(SYB_LIBS)
# $(MALLOC_ALPHA_LIBS)	$(MMALLOC_BETA_LIBS)	$(MMALLOC_LIBS)
# $(DATA_ALPHA_LIBS)	$(DATA_BETA_LIBS)	$(DATA_LIBS)
# $(CLUE_ALPHA_LIBS)	$(CLUE_BETA_LIBS)	$(CLUE_LIBS)
# $(COMMON_ALPHA_LIBS)	$(COMMON_BETA_LIBS)	$(COMMON_LIBS)
# $(WT_ALPHA_LIBS)	$(WT_BETA_LIBS)		$(WT_LIBS)
# $(WCF_ALPHA_LIBS)	$(WCF_BETA_LIBS)	$(WCF_LIBS)
#
# $(LOCAL_ALPHA_LDIR)	$(LOCAL_BETA_LDIR)	$(LOCAL_LDIR)
#
# $(X11_LDIR)
#


# remove comment on next line to use libraries with debuging info
DEBUG_LIBS	= g

LDDEBUG		= 
LDOTHER		=

LDLIBDIRS	= -L$(CLUE_SRC_DIR) -lClue$(DEBUG_LIBS) \
                  $(COMMON_ALPHA_LIBS) -lm
LDLIBS		= 

#
# =USE_CURRENT_MAKEFILE=
#

# **** S O U R C E   F I L E S ****

CXX_C_SOURCES	=			\
	main.C                          \
	tBitmask.C                      \
	tBitmask01.C                    \
	tBitmask02.C                    \
	tBitmask03.C                    \
	tLog.C                          \
	tLog01.C                        \
	tLog02.C                        \
	tLog03.C                        \
	tLog04.C                        \
	tLog05.C                        \
	tLogLevel.C                     \
	tParam.C                        \
	tParam01.C                      \
	tStrSet.C			\

hold = \
	main.C                          \
	tAbsLong.C                      \
	tArraySize.C                    \
	tBit.C                          \
	tBitmask.C                      \
	tBitmask01.C                    \
	tBitmask02.C                    \
	tBitmask03.C                    \
	tCharToInt.C                    \
	tCompare.C                      \
	tCompare01.C                    \
	tCompare02.C                    \
	tDateRange.C                    \
	tDateRangeDaily.C               \
	tDateRangeWeekly.C              \
	tDateTime.C                     \
	tDateTime01.C                   \
	tDateTime02.C                   \
	tDateTime03.C                   \
	tDateTime04.C                   \
	tDateTime05.C                   \
	tDateTime06.C                   \
	tDateTime07.C                   \
	tDateTime08.C                   \
	tDateTimeUtils.C                \
	tDwordAlign.C                   \
	tFilePath.C                     \
	tFilePath01.C                   \
	tFilePath02.C                   \
	tFilePath03.C                   \
	tFilePath04.C                   \
	tFileStat.C                     \
	tFileStat01.C                   \
	tFileStat02.C                   \
	tFileStat03.C                   \
	tFileStat04.C                   \
	tFileStat05.C                   \
	tFileStat06.C                   \
	tHeapBinStream.C                \
	tIsBaseDigit.C                  \
	tLog.C                          \
	tLog01.C                        \
	tLog02.C                        \
	tLog03.C                        \
	tLog04.C                        \
	tLog05.C                        \
	tLogLevel.C                     \
	tMemOverlap.C                   \
	tParam.C                        \
	tParam01.C                      \
	tRegexScan.C                    \
	tRound.C                        \
	tSafeStrcpy.C                   \
	tSortOrder.C                    \
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
	tStringCapitalize.C             \
	tStringCaseCompare.C            \
	tStringLower.C                  \
	tStringSearch.C                 \
	tStringTo.C                     \
	tStringUpper.C                  \
	tStripWhite.C                   \
	tSubStr.C                       \
	tSubStr01.C                     \
	tSubStr02.C                     \
	tSubStr03.C                     \
	tSubStr04.C                     \
	tSubStr05.C                     \
	tSubStr06.C                     \
	tSubStr07.C                     \
	tUnionOf.C                      \
	tUser.C                         \
	tUserGroup.C                    \
	tWithCommon.C                   \
	tWithCommon01.C                 \
	tWithCommon02.C                 \
	tWithWcf.C                      \
	tWithWcf01.C                    \
	tWithWcf02.C                    \
	tbasename.C                     \
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
# depend:	create .depend
# profile:	MAKE CCDEBUG=CC_PROFILE all
# proto:	create $(PROTO_H)
# clean:  	rm -f LIB_OBJECTS LIBRARY
# realclean:	rm -f LIB_OBJECTS LIBRARY .depend.lib PROTO_H TAGS
# tags:		create TAGS using etags
#


include Make/make.cfg.targets.4.00

default debug profile:: proto

default:: objects/default $(PROGRAM_DEFAULT)

all::	default debug profile

debug:: objects/debug
	$(HIDE) $(MAKE) SRCDEFINES='-DCLUE_DEBUG=1' \
			CCDEBUG='$(CC_DEBUG)' \
			CXXDEBUG='$(CXX_DEBUG)' \
			LDDEBUG='$(LD_DEBUG)' \
			$(PROGRAM_DEBUG)

profile:: objects/profile
	$(HIDE) $(MAKE) CCDEBUG='$(CC_PROFILE)' \
			CXXDEBUG='$(CXX_PROFILE)' \
			LDDEBUG='$(LD_PROFILE)'
			$(PROGRAM_PROFILE)

$(PROGRAM_DEFAULT):: $(OBJECTS:%=objects/default/%)
	$(LDXX) $(LDXX_FLAGS) $^ $(LDXX_LIBS) -o $@

$(PROGRAM_DEBUG):: $(OBJECTS:%=objects/debug/%) ../../src/Clue/libClueg.a
	$(LDXX) $(LDXX_FLAGS) $^ $(LDXX_LIBS) -o $@

$(PROGRAM_PROFILE):: $(OBJECTS:%=objects/profile/%)
	$(LDXX) $(LDXX_FLAGS) $^ $(LDXX_LIBS) -o $@

install:: default $(INSTALL_DIR)/$(PROGRAM_DEFAULT)


test:	default

#
# include dependancies generated by 'make depend'
#
-include .depend

#
# =MAKEFILE_LOG=
#
# $Log$
# Revision 2.5  1996/02/29 19:11:04  houghton
# *** empty log message ***
#
#
# =MAKEFILE_LOG=
#




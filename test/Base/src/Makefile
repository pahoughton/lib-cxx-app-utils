#
# Makefile for t
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

makefile_type = program

include Make/make.cfg.3.0

BETA_DIR	= 
PROD_DIR	= 
MAN_DIR		=


PROGRAM = t

PROTO_H	= _t_Proto.h

# **** S O U R C E   F I L E S ****

C_SOURCES	=			\

CXX_C_SOURCES	=			\
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

CXX_CC_SOURCES	=			\

CXX_CPP_SOURCES	=			\

C_HEADERS	=			\

CXX_HEADERS	=			\

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
PRJDEFINES	= -DCLUE_DEBUG=1 

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

USE_INST_INC	= -I/home/houghton/prj/CirInv/include

USE_SRC_INC	= -I../src \
		  -I../arch/$(arch)/src \
		  -I../arch/$(arch)/stdc++ \
		  -I../arch/Unix/src \
		  $(USE_INST_INC)


SRCINCDIR	= -I. -I../arch/$(arch)/test
PRJINCDIR	= $(USE_INST_INC) \
		  -I/home/houghton/prj/CommFabric/src

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

INSTALL_BIN_FLAGS   = -m 775

# ***** L I B R A R I E S *****
#
# Config libraryies available
#
# $(SOCKET_LIBS)
# $(CF_BETA_LIBS)
# $(CF_LIBS)
# $(COMMON_BETA_LIBS)
# $(COMMON_LIBS)
# $(MMALLOC_BETA_LIBS)
# $(MMALLOC_LIBS)
# $(SYB_LIBS)
# $(X11_LIBS)
# $(XAW_LIBS)
# $(XM_LIBS)
#
# $(LOCAL_BETA_LDIR)
# $(LOCAL_LDIR)
# $(X11_LDIR)
# $(XLIBS)
#

USE_SRC_LIBS	= -L../src
USE_INST_LIBS	= -L/home/houghton/prj/CirInv/lib

LDLIBS		= $(USE_INST_LIBS) -lClue \
		  $(USE_INST_LIBS) -lCommon \
		  -lm



# ***** D E P E N D A N C I E S *****

# =USE_CURRENT_MAKEFILE=

#
# Targets defined in make.cfg.*
#
# default: 	all
# depend:	create .depend
# proto:	create $(PROTO_H)
# clean:  	rm -f LIB_OBJECTS LIBRARY
# realclean:	rm -f LIB_OBJECTS LIBRARY .depend.lib PROTO_H TAGS
# tags:		create TAGS using etags
#

include Make/make.cfg.targets.3.0


all: $(PROGRAM)

$(PROGRAM): $(OBJECTS) ../src/libClue.a
	$(LDXX) -o $@ $(OBJECTS) $(LDFLAGS) $(LIBXXARCH)

install:
	mkdirhier $(BETA_DIR/old)
	-( cd $(BETA_DIR)/old; rm -f $(PROGRAM); cd ..; mv $(PROGRAM) old )
	$(INSTALL) $(INSTALL_BIN_FLAGS) $(PROGRAM) $(BETA_DIR)
	echo 'Beta Install Complete!'

install_production:
	mkdirhier $(PROD_DIR/old)
	-( cd $(PROD_DIR)/old; rm -f $(PROGRAM); cd ..; mv $(PROGRAM) old )
	$(INSTALL) $(INSTALL_BIN_FLAGS) $(PROGRAM) $(PROD_DIR)
	echo 'Production Install Complete!'


test:	all
	-touch data/FileStat.h.t.yyy.yyy.yyy
	-chmod 777 data/FileStat.h.t.yyy.yyy.yyy
	-touch data/FileStat.h.t.nnn.nnn.nnn
	-chmod 000 data/FileStat.h.t.nnn.nnn.nnn
	-touch data/FileStat.h.t.nnn.yyy.nnn
	-chmod 070 data/FileStat.h.t.nnn.yyy.nnn
	t

#
# include dependancies generated by 'make depend'
#
include .depend

# 
# $Log$
# Revision 2.1  1995/11/10 12:48:37  houghton
# Change to Version 2
#
# Revision 1.8  1995/11/05  16:33:15  houghton
# Revised
#
# Revision 1.3  1995/02/20  14:21:28  houghton
# Cleanup
#
# Revision 1.2  1995/02/13  17:35:10  houghton
# Major enhancements much cleaner
#
# Revision 1.1  1994/01/23  18:16:56  houghton
# Production release 1.0 of MakeConfig system
#




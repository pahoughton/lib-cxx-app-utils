#
# -*- Makefile -*- for Clue test dir
#
#
# Created: 10/10/95
#
# $Id$
#
# (see end of file for Log info)

#
# Include standard MakeConfig configuration for GNU make required
#

makefile_type = program

include Make/make.cfg.3.5

BETA_DIR	= 
PROD_DIR	= 
MAN_DIR		=


MAJOR_VER	= 2
MINOR_VER	= 00.00.a.01
VERSION		= $(MAJOR_VER).$(MINOR_VER)

PROGRAM = t

PROTO_H	= _t_Proto.h

# 
# =USE_CURRENT_MAKEFILE=
# When you re-gen a make file, every thing between 
# these tags will be kept int the new makefile
# if you want it re-gen'd, just delete the tags
#

include ../src/arch/$(arch)/test/Makefile.Test

# *****  D E F I N E S  *****
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

SRCDEFINES	= $(CLUE_DEF)
PRJDEFINES	= -DVERSION=\"$(VERSION)\"

DEFINES		= $(PRJDEFINES) $(SRCDEFINES) 

# *****  I N C L U D E S *****
#
# Config includes available
#
# $(X11_INC)
# $(SYB_INC)
# $(MMALLOC_BETA_INC)
# $(MMALLOC_INC)
# $(DATA_ALPHA_INC)
# $(DATA_BETA_INC)
# $(DATA_INC)
# $(CLUE_ALPHA_INC)
# $(CLUE_BETA_INC)
# $(CLUE_INC)
# $(COMMON_ALPHA_INC)
# $(COMMON_BETA_INC)
# $(COMMON_INC)
# $(WT_ALPHA_INC)
# $(WT_BETA_INC)
# $(WT_INC)
# $(WCF_ALPHA_INC)
# $(WCF_BETA_INC)
# $(WCF_INC)
#
# $(LOCAL_ALPHA_INC)
# $(LOCAL_BETA_INC)
# $(LOCAL_INC)
#

# TOPDIR	=

CLUE_SRC_DIR	= ../src/Clue 
CLUE_INCDIR	= -I$(CLUE_SRC_DIR) \
		  -I../src/Clue1/src \
		  -I../src/arch/$(arch)/test


SRCINCDIR	= -I. $(CLUE_INCDIR) $(WCF_ALPHA_INC)

PRJINCDIR	= 

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
CCDEBUG		= -g
CCOTHER		=

INSTALL_BIN_FLAGS   = -m 775

# ***** L I B R A R I E S *****
#
# Config libraryies available
#
# $(X11_LIBS)
# $(XAW_LIBS)
# $(XM_LIBS)
# $(SYB_LIBS)
# $(MMALLOC_BETA_LIBS)
# $(MMALLOC_LIBS)
# $(DATA_ALPHA_LIBS)
# $(DATA_BETA_LIBS)
# $(DATA_LIBS)
# $(CLUE_ALPHA_LIBS)
# $(CLUE_BETA_LIBS)
# $(CLUE_LIBS)
# $(COMMON_ALPHA_LIBS)
# $(COMMON_BETA_LIBS)
# $(COMMON_LIBS)
# $(WT_ALPHA_LIBS)
# $(WT_BETA_LIBS)
# $(WT_LIBS)
# $(WCF_ALPHA_LIBS)
# $(WCF_BETA_LIBS)
# $(WCF_LIBS)
#
# $(LOCAL_ALPHA_LDIR)
# $(LOCAL_BETA_LDIR)
# $(LOCAL_LDIR)
# $(X11_LDIR)
#

LDLIBS		= -L$(CLUE_SRC_DIR) -lClue $(COMMON_ALPHA_LIBS) -lm

#
# =USE_CURRENT_MAKEFILE=
#

# **** S O U R C E   F I L E S ****

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


USER_HH_INCS	=			\

USER_INCS	=	\
	$(USER_H_INCS)     \
	$(USER_HH_INCS)    \
	$(USER_II_INCS)    \

C_HEADERS	=			\
	_t_Proto.h                      \

CXX_HEADERS	=			\
	AppParam.hh                     \
	AvlTestData.hh                  \
	ClueTest.hh                     \
	DavlTestData.hh                 \
	StaticBinStream.hh              \
	StaticStream.hh                 \



# ***** T A R G E T S *****
#
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

include Make/make.cfg.targets.3.5


all: $(PROGRAM)

$(PROGRAM): $(OBJECTS) ../src/Clue/libClue.a
	$(LDXX) -o $@ $(OBJECTS) $(LDFLAGS) $(LIBXXARCH)

install: default
	$(MKDIRHIER) $(BETA_DIR)/old
	if [ -e $(BETA_DIR)/$(PROGRAM).$(VERSION) ] ; then \
	echo $(BETA_DIR)/$(PROGRAM).$(VERSION) already installed!; \
	echo Change version number in makefile and try again.; \
	exit 1; \
	fi
	if [ -e .installed.ver ] ; then \
	ver=`cat .installed.ver`; \
	for fn in `cat .installed.prog`; do \
	mv $(BETA_DIR)/$$fn $(BETA_DIR)/old; \
	done; \
	echo $(VERSION) >.installed.ver
	echo $(PROGRAM).$(VERSION) >.installed.prog
	$(INSTALL) $(INSTALL_BIN_FLAGS) \
		$(PROGRAM) $(BETA_DIR)/$(PROGAM).$(VERSION)
	(cd $(BETA_DIR); rm $(PROGRAM); \
	  ln -s $(PROGRAM).$(VERSION) $(PROGRAM) )
	echo 'Beta Install Complete!'

install_production: default
	$(MKDIRHIER) $(PROD_DIR)/old
	if [ -e $(PROD_DIR)/$(PROGRAM).$(VERSION) ] ; then \
	echo $(PROD_DIR)/$(PROGRAM).$(VERSION) already installed!; \
	echo Change version number in makefile and try again.; \
	exit 1; \
	fi
	if [ -e .installed.ver ] ; then \
	ver=`cat .installed.ver`; \
	for fn in `cat .installed.prog`; do \
	mv $(PROD_DIR)/$$fn $(PROD_DIR)/old; \
	done; \
	echo $(VERSION) >.installed.ver
	echo $(PROGRAM).$(VERSION) >.installed.prog
	$(INSTALL) $(INSTALL_BIN_FLAGS) \
		$(PROGRAM) $(PROD_DIR)/$(PROGAM).$(VERSION)
	(cd $(PROD_DIR); rm $(PROGRAM); \
	  ln -s $(PROGRAM).$(VERSION) $(PROGRAM) )
	echo 'Production Install Complete!'


test:	default test_data
	t

test_data: clean_test_data
	chgrp tools data/FileStat.01
	(cd data; ln -s FileStat.01 FileStat.l1)
	-touch data/FileStat.set
	chmod 6 data/FileStat.set
	-touch data/FileStat.h.t.yyy.yyy.yyy
	chmod 777 data/FileStat.h.t.yyy.yyy.yyy
	-touch data/FileStat.h.t.nnn.nnn.nnn
	chmod 000 data/FileStat.h.t.nnn.nnn.nnn
	-touch data/FileStat.h.t.nnn.yyy.nnn
	chmod 070 data/FileStat.h.t.nnn.yyy.nnn

clean:: clean_test_data

clean_test_data: 
	rm -f data/Str.bin.data			\
	      data/Str.operator.output		\
	      data/SubStr.operator.output	\
	      data/FileStat.l1			\
	      data/FileStat.set			\
	      data/FileStat.h.t.yyy.yyy.yyy	\
	      data/FileStat.h.t.nnn.nnn.nnn	\
	      data/FileStat.h.t.nnn.yyy.nnn	\
	      data/log.stream.test		\
	      data/logfile.01			\
	      data/logfile.02			\
	      data/logfile.03			\
	      data/logfile.04			\
	      data/logfile.05			\
	      data/logfile.05.tee		\
	      data/logfile.06			\
	      data/logfile.07			\
	      data/logfile.08			\
	      data/logfile.09			\
	      data/logfile.10			\
	      data/logfile.11			\
	      data/logfile.12			\
	      data/param.log.01			\



#
# include dependancies generated by 'make depend'
#
ifndef CLEANING
include .depend
endif

#
# =MAKEFILE_LOG=
#
# $Log$
# Revision 2.4  1995/11/12 22:08:30  houghton
# Use source directories
#
# Revision 2.3  1995/11/12  18:34:36  houghton
# Changed to use MakeConfigs 3.5.
#
# Revision 2.2  1995/11/10  18:50:26  houghton
# Changed to MakeConfigs 3.4
#
#
# =MAKEFILE_LOG=
#




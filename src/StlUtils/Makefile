#
# Makefile for Clue
#
#
# Created: 0/23/95
#
# $Id$
#
# (see end of file for Log info)

#
# Include standard MakeConfig configuration for GNU make required
#



include Make/make.cfg.2.1

BETA_LIB_DIR	= /rating/dev/lib
BETA_INC_DIR	= /rating/dev/include

PROD_INC_DIR	= 

LIBRARY		= libClue.a

USER_INCS	=			\
	Array.hh                        \
	Avl.hh                          \
	AvlTree.hh                      \
	AvlTreeAddrBase.hh              \
	AvlTreeBase.hh                  \
	AvlTreeOffset.hh                \
	AvlTreeOffsetBase.hh            \
	BillNum.hh  	    	    	\
	Clue.hh                         \
	Compare.hh  	    	    	\
	DLList.h                        \
	DateRange.hh                    \
	DateRangeDaily.hh               \
	DateRangeWeekly.hh              \
	DateTime.hh                     \
	DavlTreeOffset.hh               \
	DavlTreeOffsetBase.hh           \
	Directory.hh                    \
	DelimCharRec.hh			\
	DelimCharFile.hh		\
	DoubleLink.hh                   \
	Field.hh    	    	    	\
	FileStat.hh                     \
	FixedCharFile.hh    	    	\
	FixedCharRec.hh			\
	FixedNetBitRec.hh   	    	\
	Group.hh                        \
	JumpTable.hh                    \
	LogLevel.hh			\
	LogBuf.hh			\
	Log.hh                          \
	MapFile.hh                      \
	MapMem.hh                       \
	MapMemFixedDynamic.hh           \
	Mcr.hh                          \
	MultiMem.hh                     \
	MultiMemOffset.hh               \
	MultiMemOffsetMapFixed.hh       \
	NetBitPack.hh	    	    	\
	Record.hh			\
	Param.hh    	    	    	\
	Password.hh                     \
	Pind.hh	    	    	    	\
	Pix.hh                          \
	SLList.h                        \
	Stack.hh                        \
	State.hh                        \
	Str.hh                          \
	StringList.hh                   \
	SybaseParam.hh			\
	SybTable.hh			\
	TableMapFixedDynamic.hh		\
	Tbcd.hh	    	    	    	\
	TeleNum.h                       \
	TeleNum.hh                      \
	CdrBillNum.hh			\
	Timer.hh                        \

#	gnustd.h                        \
#	std.h                           \

PROTO_H		= _Clue_Proto.h

# **** S O U R C E   F I L E S ****

LIB_C_SOURCES	=			\
	TeleNumDataFromString.c         \
	TeleNumDataToString.c           \

LIB_CXX_SOURCES	=			\
	AvlTreeAddrBase.C               \
	AvlTreeOffsetBase.C             \
	BillNum.C                    	\
	ChangeFileDir.C			\
	DLList.C                        \
	DateRange.C                     \
	DateRangeDaily.C                \
	DateRangeWeekly.C               \
	DateTime.C                      \
	DavlTreeOffsetBase.C            \
	DelimCharRec.C			\
	DelimCharFile.C			\
	Directory.C                     \
	Field.C				\
	FileStat.C                      \
	FixedCharFile.C			\
	FixedCharRec.C			\
	FixedNetBitRec.C		\
	Group.C                         \
	JumpTable.C                     \
	LogLevel.C			\
	LogBuf.C			\
	Log.C                           \
	Mapped.C			\
	MapFile.C                       \
	MapMem.C                        \
	MapMemFixedDynamic.C            \
	Mcr.C				\
	MultiMem.C			\
	MultiMemOffset.C		\
	MultiMemOffsetMapFixed.C	\
	Param.C				\
	Password.C                      \
	Pind.C	    	    	    	\
	PrefixFileDir.C			\
	Record.C			\
	SLList.C                        \
	State.C                         \
	StateToStateCode.C              \
	StringList.C                    \
	SybTable.C			\
	TableMapFixedDynamic.C		\
	Tbcd.C	    	    	    	\
	TeleNum.C                       \
	CdrBillNum.C			\
	error.C				\

#	Mcr.C                           \

# 
# =USE_CURRENT_MAKEFILE=
# When you re-gen a make file, every thing between 
# these tags will be kept int the new makefile
# if you want it re-gen'd, just delete the tags
#

# *****  D E F I N E S  *****
#
# see MakeConfig(1) for portable library defines
#

DEFINES		= 

# *****  I N C L U D E S *****
#
# see MakeConfig(1) for portable library includes
#

ifeq ($(arch),AIX)
ARCHINCDIR = -Ignuinc
endif

SRCINCDIR	= -I. 
PRJINCDIR	= -I../../libCommon/src \
		  -I../../libmmalloc \
		  -I$(SYBASE)/include

INCDIRS		= $(SRCINCDIR)	\
		  $(ARCHINCDIR) \
		  $(PRJINCDIR)


# **** C O M P I L E / C P P ****

CPPOTHER 	=
CCDEBUG		= -g
CCOTHER		=

INSTALL_LIB_FLAGS = -m 664
INSTALL_INC_FLAGS = -m 664

# ***** D E P E N D A N C I E S *****

# =USE_CURRENT_MAKEFILE=

all: $(PROTO_H) $(LIBRARY)



$(LIBRARY): $(LIB_OBJECTS) 
	$(UPDATELIB) $@ $?

clean:
	rm -f $(LIBRARY) $(LIB_OBJECTS) 

realclean:
	rm -f $(LIBRARY) $(LIB_OBJECTS) $(PROTO_H) .depend.lib TAGS 

install:
	mkdirhier $(BETA_LIB_DIR)/old
	mkdirhier $(BETA_INC_DIR)/old
	-( cd $(BETA_LIB_DIR)/old; rm -f $(LIBRARY); cd ..; mv -f $(LIBRARY) old)
	-( cd $(BETA_INC_DIR)/old; rm -f $(USER_INCS); cd ..; mv -f $(USER_INCS) old)
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
	echo 'Beta Install Complete!'

proto: 
	$(MKPROTO) $(CPPFLAGS) $(LIB_C_SOURCES) >$(PROTO_H)

   
$(PROTO_H): $(LIB_C_SOURCES)
	$(MKPROTO) $(CPPFLAGS) $(LIB_C_SOURCES) >$@


tags: 
	etags -t *.h *.c *.C *.hh

depend: depend.lib

FORCE:
#
# include dependancies generated by 'make depend'
#
include .depend.lib

# 
# $Log$
# Revision 1.11  1995/07/21 15:43:14  ichudov
# DAVLs
#
# Revision 1.10  1995/03/02  16:35:35  houghton
# Linux ports & new Classes
#
# Revision 1.9  1995/02/20  14:24:27  houghton
# Linux port and Fix bugs in DateTime found with new test.
#
# Revision 1.8  1995/02/13  17:37:07  houghton
# Add SybaseParam
#
# Revision 1.7  1995/02/13  16:08:47  houghton
# New Style Avl an memory management. Many New Classes
#
# Revision 1.6  1995/01/13  20:27:48  ichudov
# Set the production destination
#
# Revision 1.5  1995/01/13  19:34:38  ichudov
# Corrected a bug in TeleNumCompare.
#
# Revision 1.4  1994/09/27  16:58:40  houghton
# Added RoundUp and some DateTime cleanup
#
# Revision 1.3  1994/08/16  20:50:17  houghton
# fixed datetime output if sec == 0
#
# Revision 1.2  1994/08/15  20:54:56  houghton
# Split Mapped out of mapped avl.
# Fixed a bunch of bugs.
# Fixed for ident of object modules.
# Prep for Rating QA Testing
#


#
# Makefile for Clue
#
# Created: 10/9/95
#
# $Id$
#
# (see end of file for Log info)

#
# Include standard MakeConfig configuration for GNU make required
#

makefile_type   = library

include Make/make.cfg.3.4

# 
# =USE_CURRENT_MAKEFILE=
# When you re-gen a make file, every thing between 
# these tags will be kept int the new makefile
# if you want it re-gen'd, just delete the tags
#

NAME		= Clue
BETA_LIB_DIR	= $(LOCAL_ALPHA_LIB_DIR)
BETA_INC_DIR	= $(LOCAL_ALPHA_INC_DIR)

PROD_LIB_DIR	= $(LOCAL_LIB_DIR)
PROD_INC_DIR	= $(LOCAL_INC_DIR)

MAJOR_VER	= 2
MINOR_VER	= 00.00.a.01
VERSION		= $(MAJOR_VER).$(MINOR_VER)

LIBRARY		= lib$(NAME).a

PROTO_H	= _$(NAME)_Proto.h

include ../arch/$(arch)/src/Makefile.Clue

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

SRCDEFINES	= -DCLUE_DEBUG=1
PRJDEFINES	= -DVERSION=\"$(VERSION)\" $(ARCH_DEFINES)

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

#TOPDIR		=

SRCINCDIR	= -I. $(ARCH_INCDIR) $(COMMON_ALPHA_INC) 
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
CCDEBUG		= $(CC_DEBUG)
CCOTHER		=

# **** I N S T A L L ****

INSTALL_LIB_FLAGS	= -m 664
INSTALL_INC_FLAGS	= -m 664
INSTALL_MAN_FLAGS	= -m 664

#
# =USE_CURRENT_MAKEFILE=
#

# **** S O U R C E   F I L E S ****

C_SOURCES	=			\
	$(ARCH_C_SOURCES)		\
	regex.c                         \

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

USER_H_INCS	=			\
	regex.h                         \
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
	Timer.hh                        \
	$(ARCH_USER_HH_INCS)		\

USER_II_INCS	=			\
	ClassVersion.ii			\
	Clue.ii				\
	Bit.ii				\
	StringUtils.ii			\
	DateTimeUtils.ii		\
	SortOrder.ii			\
	$(ARCH_USER_II_INCS)		\

USER_INCS	=	\
	$(USER_H_INCS)     \
	$(USER_HH_INCS)    \
	$(USER_II_INCS)    \

C_HEADERS	=			\
	ClueVersion.h                   \
	_Clue_Proto.h                   \
	regex.h                         \
	rx.h                            \
	$(ARCH_C_HEADER)		\

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
	Timer.hh                        \
	_Clue.hh                        \
	$(ARCH_CXX_HEADER)		\

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
	Timer.ii                        \
	$(ARCH_CXX_INLINES)		\



# ***** T A R G E T S *****
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

include Make/make.cfg.targets.3.4

all: $(PROTO_H) $(LIBRARY)

$(LIBRARY): $(OBJECTS) 
	$(UPDATELIB) $@ $?

install: beta_check_installed beta_install_lib
	@echo $(BETA_LIB_DIR)/$(LIBRARY).$(VERSION) installed!

beta_check_installed: 
	@if [ -e $(BETA_LIB_DIR)/$(LIBRARY).$(VERSION) ] ; then \
	  echo $(BETA_LIB_DIR)/$(LIBRARY).$(VERSION) already installed!; \
	  echo Change version number in makefile and try again.; \
	  exit 1; \
	fi
	@echo + Installing $(NAME) Version: $(VERSION)

beta_install_lib: default beta_move_installed beta_install_new

beta_move_installed: 
	@if [ -e .installed.ver ] ; then \
	  for line in `cat .installed.ver` ; do \
	    case $$line in \
	      installed_ver=*) \
		installed_ver=$${line#installed_ver=};; \
	      installed_inc_dir=*) \
		installed_inc_dir=$${line#installed_inc_dir=};; \
	      installed_lib_dir=*) \
		installed_lib_dir=$${line#installed_lib_dir=};; \
	    esac; \
	  done; \
	  echo + Moving Version $$installed_ver out of way; \
	  if [ -d $$installed_inc_dir ] ; then \
	    for fn in `cat .installed.inc` ; do \
	      $(MKDIRHIER) $$installed_inc_dir/old/$(NAME).$$installed_ver; \
	      echo  Moving $$installed_inc_dir/$$fn ; \
	      echo -n "    to "; \
	      echo $$installed_inc_dir/old/$(NAME).$$installed_ver/$$fn; \
	      mv $$installed_inc_dir/$$fn \
	         $$installed_inc_dir/old/$(NAME).$$installed_ver; \
	    done; \
	  fi; \
	  if [ -d $$installed_lib_dir ] ; then \
	    for fn in `cat .installed.lib` ; do \
	      $(MKDIRHIER) $$installed_lib_dir/old/$(NAME).$$installed_ver; \
	      echo  Moving $$installed_lib_dir/$$fn to; \
	      echo -n "    to "; \
	      echo $$installed_lib_dir/old/$(NAME).$$installed_ver/$(LIBRARY);\
	      mv $$installed_lib_dir/$$fn \
		 $$installed_lib_dir/old/$(NAME).$$installed_ver/$(LIBRARY); \
	    done; \
	  fi; \
	fi

beta_install_new: 
	@echo + Installing $(VERSION)
	@rm -f .installed.ver .installed.inc .installed.lib
	$(INSTALL) $(INSTALL_INC_FLAGS) \
	  $(USER_INCS) \
	  $(BETA_INC_DIR)
	@for fn in $(USER_INCS); do \
	  basename $$fn >>.installed.inc; done
	$(INSTALL) $(INSTALL_LIB_FLAGS) \
	  $(LIBRARY) \
	  $(BETA_LIB_DIR)/$(LIBRARY).$(VERSION)
	(cd $(BETA_LIB_DIR); \
	  rm $(LIBRARY); \
	  ln -s $(LIBRARY).$(VERSION) $(LIBRARY) )
	@echo $(LIBRARY).$(VERSION) >.installed.lib
	@echo installed_ver=$(VERSION) >.installed.ver
	@echo installed_inc_dir=$(BETA_INC_DIR) >>.installed.ver
	@echo installed_lib_dir=$(BETA_LIB_DIR) >>.installed.ver

install_production: default
	$(MKDIRHIER) $(PROD_LIB_DIR)/old
	$(MKDIRHIER) $(PROD_INC_DIR)/old
	if [ -e $(PROD_LIB_DIR)/$(LIBRARY).$(VERSION) ] ; then \
	echo $(PROD_LIB_DIR)/$(LIBRARY).$(VERSION) already installed!; \
	echo Change version number in makefile and try again.; \
	exit 1; \
	fi
	if [ -e .installed.prod.ver ] ; then \
	ver=`cat .installed.prod.ver`; \
	for fn in `cat .installed.prod.lib`; do \
	mv $(PROD_LIB_DIR)/$$fn $(PROD_LIB_DIR)/old; \
	done; \
	for fn in `cat .installed.prod.inc`; do \
	mv $(PROD_INC_DIR)/$$fn $(PROD_INC_DIR)/old/$$fn.$$ver; \
	done; \
	fi
	echo $(MAJOR_VER).$(MINOR_VER) >.installed.prod.ver
	echo $(LIBRARY).$(VERSION) >.installed.prod.lib
	rm -f .installed.prod.inc
	for fn in $(USER_INCS); do basename $$fn >>.installed.inc; done
	$(INSTALL) $(INSTALL_LIB_FLAGS) \
		$(LIBRARY) \
	  	$(PROD_LIB_DIR)/$(LIBRARY).$(VERSION)
	(cd $(PROD_LIB_DIR); \
	  rm $(LIBRARY); \
	  ln -s $(LIBRARY).$(VERSION) $(LIBRARY) )
	$(INSTALL) $(INSTALL_INC_FLAGS) $(USER_INCS) $(PROD_INC_DIR)
	echo 'Production Install Complete!'

test:	default

#
# include dependancies generated by 'make depend'
#
include .depend

#
# =MAKEFILE_LOG=
#
# $Log$
# Revision 1.20  1995/11/10 12:03:21  houghton
# Change install dir from BETA to ALPHA
#
# Revision 1.19  1995/11/10  00:30:43  houghton
# Change to MakeConfigs 3.4
#
#
# =MAKEFILE_LOG=
#





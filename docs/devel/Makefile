#
#
# Title:        Makefile
# Project:	StlUtils
# Desc:
# 
#   Makefile for Devel Documentation
# 
# Notes:
#
#   This Makefile requres MakeConfig and GNU's make version 3.75
#
#   Try 'make help' for a list of standard targets.
# 
# Author:	Paul Houghton (paul.houghton@wcom.com)
# Created:	6/2/100 useing MakeConfigs 5.06.01
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

makefile_type   = doc
make_cfg_ver	= 5.06
make_target	= default
show_commands 	= # true
proto_dep	= true
check_install	= true

# Include standard MakeConfig configuration for GNU make required
include Make/make.cfg.$(make_cfg_ver)

PROJECT		= StlUtils

PRJ_TOPDIR	= ../..
CFG_DIR		= $(PRJ_TOPDIR)/src/config

DOC_UP_DIR	= ..

ifeq ($(DOC_UP_DIR),.)
DOC_SUB_DIR	= .
else
DOC_SUBDIR	= $(subst $(shell cd $(DOC_UP_DIR); pwd)/,,$(shell pwd))
endif

# 
# =USE_CURRENT_MAKEFILE=
# When you re-gen a make file, every thing between 
# these tags will be kept in the new makefile
# if you want it re-gen'd, just delete the tags
#

-include $(CFG_DIR)/00-Makefile.cfg

define REPLACE_VARS_CMD
sed -e 's@=PROJECT=@$(PROJECT)@'					      \
    -e 's@=VERSION=@$(VER_MAJOR).$(VER_MINOR).$(VER_RELEASE)@'		      \
    -e 's@=VER_MAJOR=@$(VER_MAJOR)@'					      \
    -e 's@=VER_MINOR=@$(VER_MINOR)@'					      \
    -e 's@=LAST_MOD=@$(shell $(TOOL_DIR)/bin/LastMod $<)@'		      \
	$<
endef

#
# basefn_POD_HTML_OPTS variables are options to pass to pod2html
# that are only used when processing the 'basefn' file.
#
# i.e. 00-Index_POD_HTML_OPTS is only used when generating
# 00-Index.html from 00-Index.pod
#

00-Index_POD_HTML_OPTS		= -noindex
Prerequisites_POD_HTML_OPTS	= -noindex
#
# =USE_CURRENT_MAKEFILE=
#

# *** DOC FILES ***

SUBDIRS		=

MAN_PAGES	=

HTML_FILES	=							      \
	Version.html							      \
	PrjInstall.html							      \
	Install.html							      \
	Prerequisites.html						      \
	00-Index.html							      \
	$(GEN_POD_HTML_FILES)

GEN_POD_HTML_FILES	=						      \
	Library.html							      \
	Bit.html							      \
	Bitmask.html							      \
	ClassVersion.html						      \
	Compare.html							      \
	DateRange.html							      \
	DateTime.html							      \
	DumpInfo.html							      \
	FileStat.html							      \
	LibTest.html							      \
	Log.html							      \
	LogBuf.html							      \
	LogLevel.html							      \
	Param.html							      \
	RegexScan.html							      \
	SizeIt.html							      \
	StlUtilsConfig.html						      \
	StlUtilsMisc.html						      \
	StlUtilsVersion.html						      \
	Str.html							      \
	StringUtils.html						      \
	SubStr.html							      \
	VectorResync.html

POD_SOURCES	=

GEN_PODS	= $(GEN_POD_HTML_FILES:.html=.pod)

INSTALL_SPECIAL	= $(GEN_PODS)

include Make/make.cfg.targets.$(makefile_type).$(make_cfg_ver)

$(GEN_PODS):	gen_prj_pod

show_html:
	@echo "docs_html '$(docs_html)'"

gen_prj_pod:
	$(hide) GenC++Pods.pl $(PROJECT) $(PRJ_TOPDIR)/src Library
	@echo "+ GenC++Pods Complete."

help:
	@echo ""
	@echo "The following Targets are available:"
	@echo ""
	@echo "    install_man"
	@echo "    install_html"
	@echo ""

help_config:
	@echo ""
	@echo "The following configuration values will be used:"
	@echo ""
	@echo "    INSTALL_DOC_MAN_DIR="
	@echo "      '$(INSTALL_DOC_MAN_DIR)'"
	@echo ""
	@echo "    INSTALL_DOC_HTML_DIR="
	@echo "      '$(INSTALL_DOC_HTML_DIR)'"
	@echo ""

clean:
	rm -f pod2htm*
	rm -f $(GEN_PODS)

realclean:



#
# =MAKEFILE_LOG=
#
# $Log$
# Revision 1.3  2000/06/11 13:20:30  houghton
# Added Prerequisites.
#
# Revision 1.2  2000/06/05 13:13:07  houghton
# Fixed minor problems.
#
# Revision 1.1  2000/06/04 18:01:13  houghton
# Initial Version.
#
#
# =MAKEFILE_LOG=
#

# Local Variables:
# mode:makefile
# End:

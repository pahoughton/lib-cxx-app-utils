#
# Title:        Setup.Makefile
# Project:	StlUtils-4
# Desc:
# 
#   
# 
# Notes:
# 
# Author:	Paul Houghton - (paul.houghton@wcom.com)
# Created:	10/30/99 05:23
#
# Revision History: (See end of file for Revision Log)
#
#   Last Mod By:    $Author$
#   Last Mod:	    $Date$
#   Version:	    $Revision$
#
#   $Id$
# 

SHELL		= /bin/ksh

PROJECT		= libStlUtils-5
CFG_DIR		= $(PROJECT)/src/config

common_h	= $(INSTALL_INC_DIR)/Common.h
gnuregex_h	= $(INSTALL_INC_DIR)/GnuRegex.h
stdcxx_hh	= $(INSTALL_INC_DIR)/StdCxxConfig.hh

tools_build_dir		= $(TOOL_DIR)/src/Build/Tools
libs_build_dir		= $(TOOL_DIR)/src/Build/Libs

exports	    = 							\
	INSTALL_INC_DIR=$(INSTALL_INC_DIR)			\
	INSTALL_LIB_DIR=$(INSTALL_LIB_DIR)			\
	INSTALL_DOC_MAN_DIR=$(INSTALL_DOC_MAN_DIR)		\
	INSTALL_DOC_HTML_BASE_DIR=$(INSTALL_DOC_HTML_BASE_DIR)	\
	show_commands=$(show_commands)				\
	check_install=$(check_install)

no_target:

$(tools_archive_dir)/$(tools_cvs):
	cd $(libs_build_dir)						      \
	&& $(PROJECT)/support/AnonFtp.ksh				      \
	      $(tools_host)						      \
	      pub/tools/$(tools_cvs)					      \
	      $(tools_archive_dir)

$(TOOL_DIR)/bin/cvs: $(tools_archive_dir)/$(tools_cvs)			      \
		$(TOOL_DIR)/bin/gzip
	cd $(tools_build_dir)						      \
	&& zcat $(tools_archive_dir)/$(tools_cvs) | tar xf -
	cd $(tools_build_dir)/cvs*					      \
	&& ./configure --prefix=$(TOOL_DIR)				      \
	&& make								      \
	&& make install

cvs: $(TOOL_DIR)/bin/cvs

check_cvs:
	@if type cvs ; then						      \
	  echo " + cvs found.";						      \
	else								      \
	  echo " + cvs not found please install using the cvs target.";       \
	  echo "   (i.e. make -f $(PROJECT)/support/Setup.Makefile cvs";      \
	  exit 1;							      \
	fi

$(libs_build_dir)/libCommon-3:
	cd $(libs_build_dir)						      \
	&& cvs $(tools_cvsroot) co libCommon-3


$(common_h): $(libs_build_dir)/libCommon-3
	cd $(libs_build_dir)						      \
	&& $(MAKE) -f libCommon-3/Makefile setup $(exports)
	$(TOOL_DIR)/bin/make -C $(libs_build_dir)/libCommon-3		      \
	    install_lib_all $(exports) 

$(libs_build_dir)/libGnuRegex-2:
	cd $(libs_build_dir)						      \
	&& cvs $(tools_cvsroot) co libGnuRegex-2


$(gnuregex_h): $(libs_build_dir)/libGnuRegex-2
	cd $(libs_build_dir)						      \
	&& $(MAKE) -f libGnuRegex-2/Makefile setup $(exports)
	$(TOOL_DIR)/bin/make -C $(libs_build_dir)/libGnuRegex-2		      \
	    install_lib_all $(exports) 

$(libs_build_dir)/libStdC++-2:
	cd $(libs_build_dir)						      \
	&& cvs $(tools_cvsroot) co libStdC++-2


$(stdcxx_hh): $(libs_build_dir)/libStdC++-2
	cd $(libs_build_dir)						      \
	&& $(MAKE) -f libStdC++-2/Makefile setup $(exports)
	$(TOOL_DIR)/bin/make -C $(libs_build_dir)/libStdC++-2		      \
	    install_lib_all $(exports) 

gen_setup_cfg:
	rm -f $(CFG_DIR)/Setup.cfg
	sed								      \
	    -e 's!%INSTALL_INC_DIR%!$(INSTALL_INC_DIR)!'		      \
	    -e 's!%INSTALL_LIB_DIR%!$(INSTALL_LIB_DIR)!'		      \
	    -e 's!%INSTALL_DOC_MAN_DIR%!$(INSTALL_DOC_MAN_DIR)!'	      \
	    -e 's!%INSTALL_DOC_HTML_BASE_DIR%!$(INSTALL_DOC_HTML_BASE_DIR)!'  \
	  < $(CFG_DIR)/Setup.cfg.src					      \
	  > $(CFG_DIR)/Setup.cfg
	chmod 444 $(CFG_DIR)/Setup.cfg


setup: check_cvs $(common_h) $(gnuregex_h) $(stdcxx_hh) gen_setup_cfg


#
# $Log$
# Revision 5.2  2000/05/25 17:07:48  houghton
# Changed project version.
#
# Revision 5.1  2000/05/25 10:33:23  houghton
# Changed Version Num to 5
#
# Revision 1.4  2000/04/19 11:04:48  houghton
# Added INSTALL_DOC_HTML_BASE_DIR.
#
# Revision 1.3  2000/01/03 14:21:32  houghton
# Bug-Fix: forgot to use exports.
#
# Revision 1.2  1999/11/09 11:10:06  houghton
# Added gen_setup_cfg target.
#
# Revision 1.1  1999/10/30 10:41:02  houghton
# Initial Version.
#
#

# Local Variables:
# mode:makefile
# End:

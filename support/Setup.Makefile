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

make_cfg_ver	= 5.06
make_cfg_file	= $(TOOL_DIR)/include/Make/make.cfg.$(make_cfg_ver)

MAKECONFIGS	= MakeConfigs-$(make_cfg_ver)

common_h	= $(INSTALL_INC_DIR)/Common.h
gnuregex_h	= $(INSTALL_INC_DIR)/GnuRegex.h
# stdcxx_hh	= $(INSTALL_INC_DIR)/StdCxxConfig.hh

LIB_COMMON	= libCommon-3
LIB_GNUREGEX	= libGnuRegex-2
# LIB_STDCXX	= libStdC++-2

tools_archive_dir	= $(TOOL_DIR)/src/Tools
tools_build_dir		= $(TOOL_DIR)/src/Build/Tools
libs_build_dir		= $(TOOL_DIR)/src/Build/Libs

anon_ftp		= $(tools_bin_dir)/AnonFtp.ksh

cvs_ver			= 1.10
tools_cvs_pkg		= cvs-$(cvs_ver).tar.gz
tools_gzip_pkg		= gzip-1.2.4.tar
tools_host		= sideswipe.wcom.com

exports	    = 							\
	INSTALL_INC_DIR=$(INSTALL_INC_DIR)			\
	INSTALL_LIB_DIR=$(INSTALL_LIB_DIR)			\
	INSTALL_DOC_MAN_DIR=$(INSTALL_DOC_MAN_DIR)		\
	INSTALL_DOC_HTML_BASE_DIR=$(INSTALL_DOC_HTML_BASE_DIR)	\
	show_commands=$(show_commands)				\
	check_install=$(check_install)

no_default:
	$(hide) echo "++ ERROR: no default target available"
	$(hide) exit 1

$(tools_bin_dir) $(tools_build_dir) $(tools_archive_dir):
	$(hide) $(SHELL) $(PROJECT)/support/mkdirhier.sh $@

$(anon_ftp):
	$(hide) cp $(PROJECT)/support/AnonFtp.ksh $@
	$(hide) chmod 775 $@

$(TOOL_DIR)/bin/gzip:
	$(hide)								      \
	pkg=$(tools_gzip_pkg);						      \
	[ -f $(tools_archive_dir)/$$pkg ]				      \
	  || $(anon_ftp) $(tools_host)					      \
	         pub/tools/$$pkg					      \
	         $(tools_archive_dir) || exit 1;			      \
	$(hide) cd $(tools_build_dir)					      \
	&& tar xf $(tools_archive_dir)/$$pkg				      \
	&& cd gzip*							      \
	&& ./configure --prefix=$(TOOL_DIR)				      \
	&& make								      \
	&& make install

$(TOOL_DIR)/bin/cvs:
	$(hide)								      \
	pkg=$(tools_cvs_pkg);						      \
	[ -f $(tools_archive_dir)/$$pkg ]				      \
	  || $(anon_ftp) $(tools_host)					      \
	         pub/tools/$$pkg					      \
	         $(tools_archive_dir) || exit 1; 			      \
	$(hide) cd $(tools_build_dir)					      \
	&& $(TOOL_DIR)/bin/zcat $(tools_archive_dir)/$$pkg | tar xf -	      \
	&& cd cvs-$(cvs_ver)						      \
	&& ./configure --prefix=$(TOOL_DIR)				      \
	&& make								      \
	&& make install


cvs: 		$(tools_archive_dir)					      \
		$(tools_bin_dir)					      \
		$(tools_build_dir)					      \
		$(anon_ftp)						      \
		$(TOOL_DIR)/bin/gzip					      \
		$(TOOL_DIR)/bin/cvs
	$(hide) echo; echo " + CVS installation complete."; echo

check_cvs:
	@if type cvs ; then						      \
	  echo " + cvs found.";						      \
	else								      \
	  echo " + cvs not found please install using the cvs target.";       \
	  echo "   (i.e. make -f $(PROJECT)/support/Setup.Makefile cvs";      \
	  exit 1;							      \
	fi

$(make_cfg_file): 
	cd $(tools_build_dir)						      \
	&& ( [ -d $(MAKECONFIGS) ] || cvs co $(MAKECONFIGS) )		      \
	&& $(MAKE) -f $(MAKECONFIGS)/Makefile setup			      \
	&& $(TOOL_DIR)/bin/make -C $(MAKECONFIGS) install


$(common_h):
	cd $(libs_build_dir)						      \
	&& ( [ -d $(LIB_COMMON) ] || cvs co $(LIB_COMMON) )		      \
	&& $(TOOL_DIR)/bin/make -f $(LIB_COMMON)/Makefile setup	$(exports)    \
	&& $(TOOL_DIR)/bin/make -C $(LIB_COMMON) install_lib_all

$(gnuregex_h):
	cd $(libs_build_dir)						      \
	&& ( [ -d $(LIB_GNUREGEX) ] || cvs co $(LIB_GNUREGEX) )		      \
	&& $(TOOL_DIR)/bin/make -f $(LIB_GNUREGEX)/Makefile setup $(exports)  \
	&& $(TOOL_DIR)/bin/make -C $(LIB_GNUREGEX) install_lib_all

$(stdcxx_hh):
	cd $(libs_build_dir)						      \
	&& ( [ -d $(LIB_STDCXX) ] || cvs co $(LIB_STDCXX) )		      \
	&& $(TOOL_DIR)/bin/make -f $(LIB_STDCXX)/Makefile setup $(exports)  \
	&& $(TOOL_DIR)/bin/make -C $(LIB_STDCXX) install_lib_all


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


setup: 		check_cvs						      \
		$(libs_build_dir)					      \
		$(common_h)						      \
		$(gnuregex_h)						      \
		$(stdcxx_hh)						      \
		gen_setup_cfg


#
# $Log$
# Revision 5.4  2000/08/02 11:05:04  houghton
# Removed libStdC++
#
# Revision 5.3  2000/07/24 09:33:55  houghton
# Major rework to improve existing target detection (i.e. if it's there
#      dont rebuild it).
#
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

#
# Title:        Makefile
# Project:	StlUtils
# Desc:
# 
#   
# 
# Notes:
# 
# Author:	Paul Houghton - (paul.houghton@wcom.com)
# Created:	04/18/00 07:05
#
# Revision History: (See end of file for Revision Log)
#
#   Last Mod By:    $Author$
#   Last Mod:	    $Date$
#   Version:	    $Revision$
#
#   $Id$
# 

make_cfg_ver	= 5.06
show_commands 	= # true
check_install	= true

# Include standard MakeConfig configuration for GNU make required
include Make/make.cfg.$(make_cfg_ver)

PRJ_TOPDIR	= ../..
CFG_DIR		= $(PRJ_TOPDIR)/src/config

include $(CFG_DIR)/00-Makefile.cfg

INSTALL_HTML_DIR	= $(INSTALL_DOC_HTML_BASE_DIR)/user

HTML_FILES	=							      \
	00-Index.html							      \
	Param.html							      \
	Log.html

$(INSTALL_HTML_DIR):
	$(hide) $(mkdirhier_cmd) $@
	$(hide) chmod 777 $@

install_html: $(INSTALL_DOC_HTML_BASE_DIR)/user
	$(hide) for fn in $(HTML_FILES) ; do				      \
	  install -c -m 664 $$fn $(INSTALL_HTML_DIR)/$$fn ;		      \
	  echo "+ Installed $(INSTALL_HTML_DIR)/$$fn" ;			      \
	done



#
# $Log$
# Revision 1.1  2000/04/19 11:04:09  houghton
# Initial Version.
#
#

# Local Variables:
# mode:makefile
# End:

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

INSTALL_HTML_DIR	= $(INSTALL_DOC_HTML_DIR)/user

HTML_FILES	=							      \
	00-Index.html							      \
	Param.html							      \
	Log.html

$(INSTALL_HTML_DIR):
	$(hide) $(mkdirhier_cmd) $@
	$(hide) chmod 777 $@

install_html: $(INSTALL_HTML_DIR)
	$(hide) for fn in $(HTML_FILES) ; do				      \
	  install -c -m 664 $$fn $(INSTALL_HTML_DIR)/$$fn ;		      \
	  echo "+ Installed $(INSTALL_HTML_DIR)/$$fn" ;			      \
	done



#
# $Log$
# Revision 6.1  2003/08/09 11:22:40  houghton
# Changed to version 6
#
# Revision 5.2  2000/06/05 13:13:29  houghton
# Fixed problems.
#
# Revision 5.1  2000/05/25 10:33:13  houghton
# Changed Version Num to 5
#
# Revision 1.1  2000/04/19 11:04:09  houghton
# Initial Version.
#
#

# Local Variables:
# mode:makefile
# End:

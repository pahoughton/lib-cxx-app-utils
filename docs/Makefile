#
# Title:        Makefile
# Project:	StlUtils
# Desc:
# 
#   
# 
# Notes:
# 
# Author:	Paul A. Houghton - (paul.houghton@wcom.com)
# Created:	10/07/98 10:01
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

PRJ_TOPDIR	= ..
CFG_DIR		= $(PRJ_TOPDIR)/src/config

include $(CFG_DIR)/00-Makefile.cfg

INSTALL_HTML_DIR	= $(INSTALL_DOC_HTML_DIR)

HTML_FILES	=							      \
	00-Index.html

HTML_SUBDIRS	=							      \
	user								      \
	devel

MAN_SUBDIRS	=							      \
	devel

install install_docs:

install_man:

$(INSTALL_HTML_DIR):
	$(hide) $(mkdirhier_cmd) $@
	$(hide) chmod 777 $@

install_html: $(INSTALL_HTML_DIR)
	$(hide) for fn in $(HTML_FILES) ; do				      \
	  install -c -m 664 $$fn $(INSTALL_HTML_DIR)/$$fn ;		      \
	  echo "+ Installed $(INSTALL_HTML_DIR)/$$fn" ;			      \
	done
	$(hide) for dir in $(HTML_SUBDIRS) ; do				      \
	  echo "+ Making $@ in $$dir";					      \
	  $(MAKE) -C $$dir $@ $(exports) ;				      \
	done

install_man:
	$(hide) for dir in $(MAN_SUBDIRS) ; do				      \
	  echo "+ Making $@ in $$dir";					      \
	  $(MAKE) -C $$dir $@ $(exports) ;				      \
	done

clean:

realclean:




#
# $Log$
# Revision 5.2  2000/06/04 17:56:21  houghton
# Added devel subdir.
#
# Revision 5.1  2000/05/25 10:33:13  houghton
# Changed Version Num to 5
#
# Revision 1.4  2000/04/19 11:03:57  houghton
# Changed install_docs to install_man
# Added install_html.
#
# Revision 1.3  1999/10/30 10:40:26  houghton
# Changed install_doc to install_docs.
#
# Revision 1.2  1998/10/23 13:03:34  houghton
# Changed to use MakeConfigs 5.06.
#
# Revision 1.1  1998/10/13 16:12:11  houghton
# Initial Version.
#
#

# Local Variables:
# mode:makefile
# End:

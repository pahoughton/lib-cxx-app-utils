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
# Created:	10/07/98 10:03
#
# Revision History: (See end of file for Revision Log)
#
#   Last Mod By:    $Author$
#   Last Mod:	    $Date$
#   Version:	    $Revision$
#
#   $Id$
# 

show_commands 	= # true
force	 	= # true

PRJ_TOPDIR	= ..
config_dir	= $(PRJ_TOPDIR)/src/config

include $(config_dir)/00-Makefile.cfg
include Make/make.cfg.$(make_cfg_ver)


exports	    = 					\
	INSTALL_BIN_DIR=$(INSTALL_BIN_DIR)	\
	INSTALL_INC_DIR=$(INSTALL_INC_DIR)	\
	INSTALL_LIB_DIR=$(INSTALL_LIB_DIR)	\
	INSTALL_MAN_DIR=$(INSTALL_MAN_DIR)	\
	show_commands=$(show_commands)		\
	check_install=$(check_install)		\

depend depend_all depend_test depend_default depend_debug:
	$(hide) $(MAKE) -C Base/src $@ $(exports)

all default debug:
	$(hide) $(MAKE) -C Base/src $@ $(exports)

clean realclean:
	$(hide) $(MAKE) -C Base/src $@ $(exports)

test:
	$(hide) $(MAKE) -C Base/src $@ $(exports)

check:
	$(hide) $(MAKE) -C Base/src $@ $(exports)




#
# $Log$
# Revision 5.3  2001/07/30 12:28:09  houghton
# *** empty log message ***
#
# Revision 5.2  2001/07/26 19:28:57  houghton
# *** empty log message ***
#
# Revision 5.1  2000/05/25 10:33:24  houghton
# Changed Version Num to 5
#
# Revision 1.3  1999/10/30 10:40:37  houghton
# Added  check target.
#
# Revision 1.2  1998/10/23 13:08:17  houghton
# Changed to use MakeConfigs 5.06.
#
# Revision 1.1  1998/10/13 16:35:16  houghton
# Initial version.
#
#

# Local Variables:
# mode:makefile
# End:

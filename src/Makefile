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
# Created:	11/12/95
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

depend depend_all depend_test depend_default depend_debug:
	$(hide) $(MAKE) -C StlUtils $@ $(exports)

all default debug:
	$(hide) $(MAKE) -C StlUtils $@ $(exports)

clean realclean:
	$(hide) $(MAKE) -C StlUtils $@ $(exports)
	$(hide) $(MAKE) -C $(DOC_DIR) $@ $(exports)
	$(hide) $(MAKE) -C $(TEST_DIR) $@ $(exports)

test:
	$(hide) $(MAKE) -C StlUtils $@ $(exports)

check: test
	$(hide) $(MAKE) -C $(TEST_DIR) $@ $(exports)

install_docs:
	$(hide) $(MAKE) -C $(DOC_DIR) $@ $(exports)

install_all install install_default install_debug: install_docs
	$(hide) $(MAKE) -C StlUtils $@ $(exports)

install_lib_all:
	$(hide) $(MAKE) -C StlUtils $@ $(exports)



#
# $Log$
# Revision 4.7  1999/11/09 11:00:04  houghton
# Changed to use Setup.cfg.
#
# Revision 4.6  1999/10/30 11:20:39  houghton
# Bug-Fix: src dir is StlUtils
#
# Revision 4.5  1999/10/30 10:40:03  houghton
# Changed (complete rework) to support setup and other new targets.
#
# Revision 4.4  1999/05/04 11:57:21  houghton
# Cleanup only.
#
# Revision 4.3  1998/10/23 13:03:43  houghton
# Changed to use MakeConfigs 5.06.
#
# Revision 4.2  1998/10/13 16:12:28  houghton
# Complete rework.
#
# Revision 4.1  1997/09/17 15:12:05  houghton
# Changed to Version 4
#
# Revision 3.2  1997/09/17 11:08:02  houghton
# Changed: renamed library to StlUtils.
#
# Revision 3.1  1996/11/14 01:23:21  houghton
# Changed to Release 3
#
# Revision 1.1  1995/11/12 17:50:43  houghton
# Initial Version.
#
#

# Local Variables:
# mode:makefile
# End:
#


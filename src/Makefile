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

# Include standard MakeConfig configuration for GNU make required
include Make/make.cfg.$(make_cfg_ver)

INSTALL_BIN_DIR	= $(local_bindir)
INSTALL_INC_DIR = $(local_incdir)
INSTALL_LIB_DIR = $(local_libdir)
INSTALL_MAN_DIR = $(local_mandir)

exports	    = 					\
	INSTALL_BIN_DIR=$(INSTALL_BIN_DIR)	\
	INSTALL_INC_DIR=$(INSTALL_INC_DIR)	\
	INSTALL_LIB_DIR=$(INSTALL_LIB_DIR)	\
	INSTALL_MAN_DIR=$(INSTALL_MAN_DIR)	\
	show_commands=$(show_commands)		\
	check_install=$(check_install)		\

depend depend_all depend_test depend_default depend_debug:
	$(hide) if ! $(MAKE) -C StlUtils $@ $(exports); then exit; fi

all default debug:
	$(hide) if ! $(MAKE) -C StlUtils $@ $(exports); then exit; fi

clean realclean:
	$(hide) if ! $(MAKE) -C StlUtils $@ $(exports); then exit; fi

test:
	$(hide) if ! $(MAKE) -C StlUtils $@ $(exports); then exit; fi


install_all install install_default install_debug:
	$(hide) if ! $(MAKE) -C StlUtils $@ $(exports); then exit; fi


#
# $Log$
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


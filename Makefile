#
# -*- Makefile -*- for StlUtils root dir
#
# Author: Paul Houghton
#
# Created: 11/12/95
#
# $Id$
#

make_cfg_ver	= 5.06
show_commands 	= # true
check_install	= true

# Include standard MakeConfig configuration for GNU make required
include Make/make.cfg.$(make_cfg_ver)


INSTALL_INC_DIR = $(local_incdir)
INSTALL_LIB_DIR = $(local_libdir)
INSTALL_BIN_DIR	= $(local_bindir)
INSTALL_MAN_DIR = $(local_mandir)

SRC_DIR		= src
DOC_DIR		= docs
TEST_DIR	= test

exports	    = 					\
	INSTALL_BIN_DIR=$(INSTALL_BIN_DIR)	\
	INSTALL_INC_DIR=$(INSTALL_INC_DIR)	\
	INSTALL_LIB_DIR=$(INSTALL_LIB_DIR)	\
	INSTALL_MAN_DIR=$(INSTALL_MAN_DIR)	\
	show_commands=$(show_commands)		\
	check_install=$(check_install)		\

beta_exports	=				\
	INSTALL_BIN_DIR=$(INSTALL_BIN_DIR)	\
	INSTALL_INC_DIR=$(beta_incdir)		\
	INSTALL_LIB_DIR=$(beta_libdir)		\
	INSTALL_MAN_DIR=$(INSTALL_MAN_DIR)	\
	show_commands=$(show_commands)		\
	check_install=$(check_install)		\

.PHONY: test

depend depend_all depend_default depend_debug:
	$(hide) $(MAKE) -C $(SRC_DIR) $@ $(exports)

depend_test:
	$(hide) $(MAKE) -C $(SRC_DIR) $@ $(exports)
	$(hide) $(MAKE) -C $(TEST_DIR) $@ $(exports)

all default debug:
	$(hide) $(MAKE) -C $(SRC_DIR) $@ $(exports)

clean realclean:
	$(hide) $(MAKE) -C $(SRC_DIR) $@ $(exports)
	$(hide) $(MAKE) -C $(DOC_DIR) $@ $(exports)
	$(hide) $(MAKE) -C $(TEST_DIR) $@ $(exports)

test:
	$(hide) $(MAKE) -C $(SRC_DIR) $@ $(exports)
	$(hide) $(MAKE) -C $(TEST_DIR) $@ $(exports)

install_doc:
	$(hide) $(MAKE) -C $(DOC_DIR) $@ $(exports)

install_all install: install_doc
	$(hide) $(MAKE) -C $(SRC_DIR) $@ $(exports)

install_beta:
	$(hide) $(MAKE) -C $(SRC_DIR) install_all $(beta_exports)

install_default install_debug: 
	$(hide) $(MAKE) -C $(SRC_DIR) $@ $(exports)

#
# $Log$
# Revision 4.4  1999/05/09 11:32:13  houghton
# Cleanup.
#
# Revision 4.3  1998/10/23 13:03:26  houghton
# Changed to use MakeConfigs 5.06.
#
# Revision 4.2  1998/10/13 16:11:59  houghton
# Complete rework.
#
# Revision 4.1  1997/09/17 15:11:57  houghton
# Changed to Version 4
#
# Revision 3.2  1997/09/17 11:07:50  houghton
# Changed: renamed library to StlUtils.
#
# Revision 3.1  1996/11/14 01:23:03  houghton
# Changed to Release 3
#
# Revision 1.1  1995/11/12 17:50:21  houghton
# Initial Version.
#
#
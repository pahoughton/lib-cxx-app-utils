#
# -*- Makefile -*- for StlUtils root dir
#
# Author: Paul Houghton
#
# Created: 11/12/95
#
# $Id$
#

show_commands	= # true
check_install	= true

PROJECT		= libSqlClient-2

PRJ_TOPDIR	= .
CFG_DIR		= $(PRJ_TOPDIR)/src/config

INSTALL_INC_DIR = $(TOOL_DIR)/include/prod
INSTALL_LIB_DIR = $(TOOL_DIR)/lib/prod
INSTALL_BIN_DIR	= $(TOOL_DIR)/bin
INSTALL_MAN_DIR = $(TOOL_DIR)/man

common_h	= $(INSTALL_INC_DIR)/Common.h
gnuregex_h	= $(INSTALL_INC_DIR)/GnuRegex.h
stdcxx_hh	= $(INSTALL_INC_DIR)/StdCxxConfig.hh


exports	    = 					\
	INSTALL_BIN_DIR=$(INSTALL_BIN_DIR)	\
	INSTALL_INC_DIR=$(INSTALL_INC_DIR)	\
	INSTALL_LIB_DIR=$(INSTALL_LIB_DIR)	\
	INSTALL_MAN_DIR=$(INSTALL_MAN_DIR)	\
	show_commands=$(show_commands)		\
	check_install=$(check_install)

no_target: help

setup:
	$(MAKE) -f $(PROJECT)/support/Setup.Makefile $(exports) setup

verify_setup:
	@ if [ -z "$$TOOL_DIR" ] ; then					      \
	  echo "+ TOOL_DIR env var not set.";				      \
	  echo "  Please see $(PROJECT)/docs/devel/Dependencies.txt";	      \
	  echo "  for details.";					      \
	  exit 1;							      \
	fi
	@ if [ ! -f "$(common_h)" ] ; then				      \
	  echo "+ $(common_h) not found";				      \
	  echo "    run make -f $(PROJECT)/Makefile setup from the";	      \
	  echo "    \$TOOL_DIR/src/Build/Libs directory.";		      \
	  echo "    Please see $(PROJECT)/docs/devel/Dependencies.txt";	      \
	  echo "    for details.";					      \
	  exit 1;							      \
	fi
	@ if [ ! -f "$(gnuregex_h)" ] ; then				      \
	  echo "+ $(gnuregex_h) not found";				      \
	  echo "    run make -f $(PROJECT)/Makefile setup from the";	      \
	  echo "    \$TOOL_DIR/src/Build/Libs directory.";		      \
	  echo "    Please see $(PROJECT)/docs/devel/Dependencies.txt";	      \
	  echo "    for details.";					      \
	  exit 1;							      \
	fi
	@ if [ ! -f "$(stdcxx_hh)" ] ; then				      \
	  echo "+ $(stdcxx_hh) not found";				      \
	  echo "    run make -f $(PROJECT)/Makefile setup from the";	      \
	  echo "    \$TOOL_DIR/src/Build/Libs directory.";		      \
	  echo "    Please see $(PROJECT)/docs/devel/Dependencies.txt";	      \
	  echo "    for details.";					      \
	  exit 1;							      \
	fi


depend_all								      \
depend_debug								      \
depend_default								      \
debug									      \
default									      \
test									      \
shared									      \
all									      \
check									      \
clean									      \
realclean								      \
install_docs								      \
install_default								      \
install_debug								      \
install									      \
install_all: verify_setup
	@ $(TOOL_DIR)/bin/make -C $(PRJ_TOPDIR)/src $@ $(exports)
	@ echo + $(PROJECT) $@ complete

help targets:
	@ echo " + The following targets are available:"
	@ echo 
	@ echo "    setup"
	@ echo 
	@ echo "    depend_all"
	@ echo "    depend_debug"
	@ echo "    depend_default"
	@ echo "    debug"
	@ echo "    default"
	@ echo "    test (testing version)"
	@ echo "    shared"
	@ echo "    all"
	@ echo "    check (run tests)"
	@ echo "    clean"
	@ echo "    realclean"
	@ echo "    install_docs"
	@ echo "    install_default"
	@ echo "    install_debug"
	@ echo "    install"
	@ echo "    install_all"
	@ echo
	@ echo " + Use the help_config target to see the available"
	@ echo "   configuration overides."
	@ echo

help_config:
	@ echo " + The following configuration variables are available:"
	@ echo
	@ echo "    INSTALL_BIN_DIR=$(INSTALL_BIN_DIR)"
	@ echo "    INSTALL_INC_DIR=$(INSTALL_INC_DIR)"
	@ echo "    INSTALL_LIB_DIR=$(INSTALL_LIB_DIR)"
	@ echo "    INSTALL_MAN_DIR=$(INSTALL_MAN_DIR)"
	@ echo "    show_commands=$(show_commands)"
	@ echo "    check_install=$(check_install)"
	@ echo

#
# $Log$
# Revision 4.5  1999/10/30 10:39:57  houghton
# Changed (complete rework) to support setup and other new targets.
#
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
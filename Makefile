#
# -*- Makefile -*- for StlUtils root dir
#
# Author: Paul Houghton
#
# Created: 11/12/95
#
# $Id$
#

show_commands	= false
check_install	= true
hide		= @

PROJECT		= libStlUtils-4

PRJ_TOPDIR	= .
CFG_DIR		= $(PRJ_TOPDIR)/src/config

INSTALL_INC_DIR 	= $(TOOL_DIR)/include/prod
INSTALL_LIB_DIR 	= $(TOOL_DIR)/lib/prod
INSTALL_MAN_DIR 	= $(TOOL_DIR)/man

INSTALL_HTML_BASE_DIR	= \
	/usr/netscape/suitespot/docs/ObjectRepository/StlUtils

common_h	= $(INSTALL_INC_DIR)/Common.h
gnuregex_h	= $(INSTALL_INC_DIR)/GnuRegex.h
stdcxx_hh	= $(INSTALL_INC_DIR)/StdCxxConfig.hh

hide = @

setup_exports		=			\
	INSTALL_INC_DIR=$(INSTALL_INC_DIR)	\
	INSTALL_LIB_DIR=$(INSTALL_LIB_DIR)	\
	INSTALL_DOC_DIR=$(INSTALL_DOC_DIR)	\
	show_commands=$(show_commands)		\
	check_install=$(check_install)

exports			=			\
	show_commands=$(show_commands)		\
	check_install=$(check_install)

no_target: help

setup:
	$(MAKE) -f $(PROJECT)/support/Setup.Makefile $(setup_exports) setup
	$(TOOL_DIR)/bin/make -C $(PROJECT) realclean depend_all
	$(hide) echo 
	$(hide) echo "+ $(PROJECT) setup complete."
	$(hide) echo 


verify_setup:
	$(hide)								      \
	if [ ! -f $(CFG_DIR)/Setup.cfg ]				      \
	    && [ ! -f $(PROJECT)/$(CFG_DIR)/Setup.cfg ] ; then		      \
	  echo "+ Setup.cfg NOT FOUND!";				      \
	  echo " ";							      \
	  echo "    To install all the dependencies, please perform";	      \
	  echo "    the following:";					      \
	  echo " ";							      \
	  echo "      cd \$$TOOL_DIR/src/Build/Libs";			      \
	  echo "      make -f $(PROJECT)/Makefile setup";		      \
	  echo " ";							      \
	  echo "    Please see $(PROJECT)/docs/devel/Dependencies.txt";	      \
	  echo "    for details.";					      \
	  echo " ";							      \
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

install_lib_all: verify_setup
	@ $(TOOL_DIR)/bin/make -C $(PRJ_TOPDIR)/src install_all $(exports)
	@ echo + $(PROJECT) $@ complete

help targets:
	@ echo 
	@ echo "+ The following targets are available:"
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
	@ echo "+ Use the help_config target to see the available"
	@ echo "  configuration overides."
	@ echo

help_config:
	@ if [ -f $(CFG_DIR)/Setup.cfg ] ; then				      \
	  $(MAKE) -f $(CFG_DIR)/Setup.cfg help_config ;			      \
	else								      \
	  if [ -f $(PROJECT)/$(CFG_DIR) ] ; then			      \
	    $(MAKE) -f $(PROJECT)/$(CFG_DIR)/Setup.cfg help_config ;	      \
	  else								      \
	    echo ;							      \
	    echo "+ The following configuration variables are available:" ;   \
	    echo ;							      \
	    echo "    INSTALL_INC_DIR=$(INSTALL_INC_DIR)" ;		      \
	    echo "    INSTALL_LIB_DIR=$(INSTALL_LIB_DIR)" ;		      \
	    echo "    INSTALL_DOC_DIR=$(INSTALL_DOC_DIR)" ;		      \
	    echo "    INSTALL_HTML_BASE_DIR=";				      \
	    echo "      $(INSTALL_HTML_BASE_DIR)";			      \
	    echo ;							      \
	    echo "    show_commands=$(show_commands)" ;			      \
	    echo "    check_install=$(check_install)" ;			      \
	    echo ;							      \
	  fi ;								      \
	fi 

#
# $Log$
# Revision 4.10  2000/04/18 13:08:22  houghton
# Added INSTALL_HTML_BASE_DIR.
#
# Revision 4.9  2000/02/29 14:36:27  houghton
# Added install_lib_all target.
#
# Revision 4.8  1999/11/10 10:07:12  houghton
# Changed verify_setup to check Setup.cfg.
#
# Revision 4.7  1999/11/09 10:59:52  houghton
# Changed setup to generate Setup.cfg.
#
# Revision 4.6  1999/10/30 12:26:41  houghton
# Bug-Fix: typo.
# Cleanup verify_setup error message.
#
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
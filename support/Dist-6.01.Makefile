#
# File:         Dist-6.01.Makefile
# Project:	StlUtils (%PP%)
# Item:   	%PI% (%PF%)
# Desc:
#
#   
#
# Notes:
#
# Author:	Paul Houghton - <paul.houghton@wcom.com>
# Created:	08/05/01 05:50
#
# Revision History: (See end of file for Revision Log)
#
#   Last Mod By:    %PO%
#   Last Mod:	    %PRT%
#   Version:	    %PIV%
#   Status:	    %PS%
#
#   %PID%
#

#
# The following variables control the behavior of MakeConfigs.
#   make_target	    is the default target to build
#   show_commands   if this is true, the commands  will be output
#   check_install   if this is true, install and install_all will NOT
#		    overwrite an installed version.
#   force	    if this is true, targets will be rebuilt
#		    whether they need to be or not.

make_target	= help
show_commands 	= # true
check_install	= true
force		= # true

PRJ_TOPDIR	= ..
config_dir  	= $(PRJ_TOPDIR)/src/config

include $(config_dir)/00-Makefile.cfg
include Make/make.cfg.$(make_cfg_ver)

INSTALL_VER		= PROD
INSTALL_VER_PROD	= $(PROJECT_VER_PROD)
INSTALL_VER_PREV	= $(PROJECT_VER_PREV)

INSTALL_VERSION		= $(INSTALL_VER_$(INSTALL_VER))

INSTALL_TARGETS		= $(patsubst %,install_%,$(BUILD_TYPE_LIST))

DIST_INSTALL_DIR_EXPORTS	=				\
	$(foreach var,$(RUN_DIR_VAR_LIST),			\
  INSTALL_$(var)_DIR=$(strip $(subst $(RUN_BASE_DIR),		\
				     $(INSTALL_BASE_DIR),	\
				     $(RUN_$(var)_DIR))))

SUBDIRS		=

TARGETS		= dist_binary			\
		  clean				\
		  realclean

HELP_TARGETS	= $(TARGETS)

PHONY_TARGETS	= $(HELP_TARGETS)


include Make/make.cfg.targets.install.$(make_cfg_ver)


create_dist_cpio:
	$(hide) MakeInstallCpio						\
		--project=$(PROJECT_NAME)				\
		--prj-version=$(FULL_VERSION)				\
		$(if $(INSTALL_FS_BASE_DIR),				\
		     --install-fs-base-dir=$(INSTALL_FS_BASE_DIR),)	\
		--install-base-dir=$(INSTALL_BASE_DIR)			\
		$(if $(FS_BASE_DIR),					\
		     --fs-base-dir=$(FS_BASE_DIR),)			\
		--run-base-dir=$(RUN_BASE_DIR)				\
		--install-script=$(INSTALL_SCRIPT)

dist_binary: create_dist_cpio


#
# Revision Log:
#
# %PL%
#

# Set XEmacs mode
#
# Local Variables:
# mode:makefile
# End:

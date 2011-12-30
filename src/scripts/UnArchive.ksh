#!/usr/bin/ksh
#
# File:		UnArchive.ksh
# Project:	Trs 
# Desc:
#
#   
#
# Notes:
#
# Author(s):   Paul Houghton <paul4hough@gmail.com>
# Created:     04/25/2003 06:17
#
# Revision History: (See end of file for Revision Log)
#
#	$Author$
#	$Date$
#	$Name$
#	$Revision$
#	$State$
#
# $Id$
#


for fn in $*; do
  destfn=`basename $fn | sed 's/-[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9].[0-9][0-9][0-9][0-9][0-9][0-9]//'`
  mv $fn $destfn
  uncompress $destfn
  echo Un Archived $destfn
done

//
// File:        IosOpenModeToString.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for IosOpenModeToString
//  
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     04/04/97 08:59
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include "Str.hh"


STLUTILS_FUNCT_VERSION(
  IosOpenModeToString,
  "$Id$" );

const char *
IosOpenModeToString( ios::open_mode mode )
{
  static Str modeStr;

  modeStr = "";
  
  if( mode & ios::in )
    modeStr << "ios::in | ";

  if( mode & ios::out )
    modeStr << "ios::out | ";

  if( mode & ios::ate )
    modeStr << "ios::ate | ";

  if( mode & ios::app )
    modeStr << "ios::app | ";

  if( mode & ios::trunc )
    modeStr << "ios::trunc | ";

  if( mode & ios::nocreate )
    modeStr << "ios::nocreate | ";

  if( mode & ios::noreplace )
    modeStr << "ios::noreplace | ";

#if !defined( AIX41 )
  if( mode & ios::binary )
    modeStr << "ios::binary | ";
#endif
  
  if( modeStr.size() > 3 )
    modeStr.remove( modeStr.size() - 3 );

  return( modeStr.c_str() );
}

  
// Revision Log:
//
// $Log$
// Revision 4.1  1997/09/17 15:12:29  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:08:24  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1997/04/05 11:57:41  houghton
// Changed AIX41 does not have ios::binary.
//
// Revision 3.1  1997/04/04 20:51:48  houghton
// Initial Versionn.
//
//

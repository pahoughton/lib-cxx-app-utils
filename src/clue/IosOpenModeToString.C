//
// File:        IosOpenModeToString.C
// Project:	StlUtils ()
// Desc:        
//
//  Compiled sources for IosOpenModeToString
//  
// Author:      Paul A. Houghton - (paul4hough@gmail.com)
// Created:     04/04/97 08:59
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//

#include "Str.hh"


STLUTILS_FUNCT_VERSION(
  IosOpenModeToString,
  "$Id$ " );

const char *
IosOpenModeToString( std::ios::openmode mode );

const char *
IosOpenModeToString( std::ios::openmode mode )
{
  static Str modeStr;

  modeStr = "";
  
  if( mode & std::ios::in )
    modeStr << "ios::in | ";

  if( mode & std::ios::out )
    modeStr << "ios::out | ";

  if( mode & std::ios::ate )
    modeStr << "ios::ate | ";

  if( mode & std::ios::app )
    modeStr << "ios::app | ";

  if( mode & std::ios::trunc )
    modeStr << "ios::trunc | ";
  
  if( modeStr.size() > 3 )
    modeStr.remove( modeStr.size() - 3 );

  return( modeStr.c_str() );
}

  
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.3  2012/04/26 20:08:52  paul
// *** empty log message ***
//
// Revision 6.2  2011/12/30 23:57:14  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:41  houghton
// Changed to version 6
//
// Revision 5.3  2003/08/09 11:20:58  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:29:00  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:15  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:12:29  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:08:24  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1997/04/05 11:57:41  houghton
// Changed AIX41 does not have std::ios::binary.
//
// Revision 3.1  1997/04/04 20:51:48  houghton
// Initial Versionn.
//
//

//
// File:        IosOpenModeFromString.C
// Project:	StlUtils ()
// Desc:        
//
//  Compiled sources for IosOpenModeFromString
//  
// Author:      Paul A. Houghton - (paul.houghton@mci.com)
// Created:     04/04/97 08:24
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//

#include "StringUtils.hh"
#include <iostream>


STLUTILS_FUNCT_VERSION(
  IosOpenModeFromString,
  "$Id$ " );


ios::open_mode
IosOpenModeFromString( const char * modeString )
{
  ios::open_mode    mode = (ios::open_mode)0;

  if( StringCaseSearch( modeString, NPOS, "in", NPOS ) )
    mode = (ios::open_mode)( mode | ios::in);

  if( StringCaseSearch( modeString, NPOS, "out", NPOS ) )
    mode = (ios::open_mode)( mode | ios::out);

  if( StringCaseSearch( modeString, NPOS, "ate", NPOS ) )
    mode = (ios::open_mode)( mode | ios::ate);

  if( StringCaseSearch( modeString, NPOS, "app", NPOS ) )
    mode = (ios::open_mode)( mode | ios::app);

  if( StringCaseSearch( modeString, NPOS, "trunc", NPOS ) )
    mode = (ios::open_mode)( mode | ios::trunc);

  if( StringCaseSearch( modeString, NPOS, "nocreate", NPOS ) )
    mode = (ios::open_mode)( mode | ios::nocreate);
  
  if( StringCaseSearch( modeString, NPOS, "noreplace", NPOS ) )
    mode = (ios::open_mode)( mode | ios::noreplace);

#if !defined( AIX41 )
  if( StringCaseSearch( modeString, NPOS, "binary", NPOS ) )
    mode = (ios::open_mode)( mode | ios::binary);
#endif
  
  return( mode );
}

// Revision Log:
//
// 
// %PL%
// 
// $Log$
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
// Revision 3.2  1997/04/05 11:57:33  houghton
// Changed AIX41 does not have ios::binary.
//
// Revision 3.1  1997/04/04 20:51:45  houghton
// Initial Versionn.
//
//

//
// File:        OpenFlags.C
// Project:	StlUtils ()
// Desc:        
//
//  Source for OpenFlags function.
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     05/14/95 12:35 
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//
// $Id$ 


#include "StlUtilsMisc.hh"
#include <iostream>
#include <fcntl.h>

STLUTILS_FUNCT_VERSION(
  OpenFlags,
  "$Id$ " );

int
OpenFlags( std::ios::openmode openMode )
{
  int flags = 0;
  int mode = openMode;
  
  if( mode & (std::ios::app) )
    mode |= std::ios::out;

  if( (mode & (std::ios::in|std::ios::out)) == (std::ios::in|std::ios::out)) {
    flags = O_RDWR;
    
  } else if( (mode & (std::ios::in|std::ios::out)) == std::ios::in ) {
    flags = O_RDONLY;

  } else if( (mode & (std::ios::in|std::ios::out)) == std::ios::out ) {
    flags = O_WRONLY;

  }

  if( mode & std::ios::trunc)
    flags |= O_TRUNC;

  if( mode & std::ios::app )
    flags |= O_APPEND;

  return( flags );
}
    
  
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.3  2012/04/26 20:08:46  paul
// *** empty log message ***
//
// Revision 6.2  2011/12/30 23:57:33  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:46  houghton
// Changed to version 6
//
// Revision 5.3  2003/08/09 11:21:01  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:28:57  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:22  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:34  houghton
// Changed to Version 4
//
// Revision 3.5  1997/09/17 15:10:28  houghton
// Renamed StlUtilsUtils.hh to StlUtilsMisc.hh
//
// Revision 3.4  1997/09/17 11:09:22  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/09/16 11:27:58  houghton
// Changed to include StlUtilsUtils.hh
//
// Revision 3.2  1996/11/24 19:10:12  houghton
// Removed support for short filenames.
//
// Revision 3.1  1996/11/14 01:25:27  houghton
// Changed to Release 3
//
// Revision 2.1  1995/11/10 12:47:15  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  16:04:16  houghton
// Revised
//
//

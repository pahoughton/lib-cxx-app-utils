//
// File:        File.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     08/02/95 05:25
//
// Revision History:
//
// $Log$
// Revision 6.2  2011/12/30 23:57:28  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:45  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:20  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:22  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:09:14  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:25:20  houghton
// Changed to Release 3
//
// Revision 2.1  1995/11/10 12:47:08  houghton
// Change to Version 2
//
// Revision 1.1  1995/11/05  13:12:38  houghton
// Initial implementation of File Class
//
//

#include "File.hh"

#include <unistd.h>
#include <fcntl.h>
#include <cerrno>

#ifdef STLUTILS_DEBUG
#define inline
#include <File.ii>
#endif

bool
File::clear( int setState )
{
  state = setState;
  if( state == ios::goodbit )
    osErrno = 0;
  
  return( good() );
}




//
// File:        File.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld1.wiltel.com)
// Created:     08/02/95 05:25
//
// Revision History:
//
// $Log$
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

#ifdef CLUE_DEBUG
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




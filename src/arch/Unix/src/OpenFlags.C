//
// File:        OpenFlags.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/14/95 12:35 
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 12:23:03  houghton
// Initial OpenFlags Implementation
//
//
static const char * RcsId =
"$Id$";


#include <iostream>
#include <fcntl.h>

int
OpenFlags( ios::open_mode openMode )
{
  int flags = 0;
  int mode = openMode;
  
  if( mode & (ios::app) )
    mode |= ios::out;

  switch( mode & (ios::in|ios::out ) )
    {
    case ios::in:
      flags = O_RDONLY;
      break;

    case ios::out:
      flags = O_WRONLY;
      break;

    case (ios::in|ios::out):
      flags = O_RDWR;
      break;      
    }

  if( mode & ios::trunc)
    flags |= O_TRUNC;

  if( mode & ios::app )
    flags |= O_APPEND;

  if( !(mode & ios::nocreate) && mode != ios::in )
    flags |= O_CREAT;

  if( mode & ios::noreplace )
    flags |= O_EXCL;

  return( flags );
}
    
  

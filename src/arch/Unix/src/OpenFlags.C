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


#include "StlUtilsUtils.hh"
#include <iostream>
#include <fcntl.h>

STLUTILS_FUNCT_VERSION(
  OpenFlags,
  "$Id$" );

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
    
  

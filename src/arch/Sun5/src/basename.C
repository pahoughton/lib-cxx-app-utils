//
// File:        basename.C
// Project:	StlUtils
// Desc:        
//
//	const char *
//	basename( const char * fn );
//	    Returns a pointer to the filename from part of 'fn'
//	    without the directory part.
//	
//	char *
//	basename( char * fn );
//	    Returns a pointer to the filename from part of 'fn'
//	    without the directory part.
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     06/16/95 04:43 
//
// Revision History: (See end of file for Revision Log)
//

#include "StringUtils.hh"
#include <cstring>

STLUTILS_FUNCT_VERSION(
  basename,
  "$Id$" );


const char *
basename( const char * fn )
{
  if( ! fn ) return( fn );

  const char * name = strrchr( fn, STLUTILS_DIR_DELIM );

  if( name )
    return( name + 1 );
  else
    return( fn );
}

char *
basename( char * fn )
{
  if( ! fn ) return( fn );

  char * name = strrchr( fn, STLUTILS_DIR_DELIM );

  if( name )
    return( name + 1 );
  else
    return( fn );
}

//
// Revision Log:
//
// $Log$
// Revision 1.2  1997/09/17 11:09:18  houghton
// Changed: renamed library to StlUtils.
//
// Revision 1.1  1997/08/18 10:31:43  houghton
// Initial version.
//
// Revision 3.2  1996/11/24 19:15:04  houghton
// Removed support for short file names.
//
// Revision 3.1  1996/11/14 01:25:27  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:40:41  houghton
// Restructure header comments layout.
// Changed to use STLUTILS_DIR_DELIM (defined in StlUtilsConfig.hh).
//
// Revision 2.1  1995/11/10 12:47:16  houghton
// Change to Version 2
//
// Revision 1.1  1995/11/05  15:49:27  houghton
// Revised
//
//

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
// Revision 5.1  2000/05/25 10:33:19  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:15  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:09:09  houghton
// Changed: renamed library to StlUtils.
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

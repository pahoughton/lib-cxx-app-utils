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
// Revision 1.1  1998/07/20 11:28:20  houghton
// Initial Version.
//
//

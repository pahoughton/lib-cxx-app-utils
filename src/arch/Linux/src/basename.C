//
// File:        basename.C
// Project:	Clue
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

#if !defined( CLUE_SHOR_FN )
#include "StringUtils.hh"
#include <cstring>
#else
#include "StrUtil.hh"
#include <cstring>
#endif

CLUE_FUNCT_VERSION(
  basename,
  "$Id$" );


const char *
basename( const char * fn )
{
  if( ! fn ) return( fn );

  const char * name = strrchr( fn, CLUE_DIR_DELIM );

  if( name )
    return( name + 1 );
  else
    return( fn );
}

char *
basename( char * fn )
{
  if( ! fn ) return( fn );

  char * name = strrchr( fn, CLUE_DIR_DELIM );

  if( name )
    return( name + 1 );
  else
    return( fn );
}

//
// Revision Log:
//
// $Log$
// Revision 2.2  1996/11/04 14:40:41  houghton
// Restructure header comments layout.
// Changed to use CLUE_DIR_DELIM (defined in ClueConfig.hh).
//
// Revision 2.1  1995/11/10 12:47:16  houghton
// Change to Version 2
//
// Revision 1.1  1995/11/05  15:49:27  houghton
// Revised
//
//

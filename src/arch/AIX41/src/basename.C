//
// File:        basename.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     06/16/95 04:43 
//
// Revision History:
//
// $Log$
// Revision 2.1  1995/11/10 12:47:16  houghton
// Change to Version 2
//
// Revision 1.1  1995/11/05  15:49:27  houghton
// Revised
//
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

#ifndef DIR_DELIM
#define DIR_DELIM '/'
#endif

const char *
basename( const char * fn )
{
  if( ! fn ) return( fn );

  const char * name = strrchr( fn, DIR_DELIM );

  if( name )
    return( name + 1 );
  else
    return( fn );
}

char *
basename( char * fn )
{
  if( ! fn ) return( fn );

  char * name = strrchr( fn, DIR_DELIM );

  if( name )
    return( name + 1 );
  else
    return( fn );
}
	       
	       
    


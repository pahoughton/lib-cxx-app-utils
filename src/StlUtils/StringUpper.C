//
// File:        StringUpper.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/06/95 11:59 
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 13:23:39  houghton
// Initaial implementation
//
//

#include "StringUtils.hh"

#include <cstddef>
#include <cctype>

static const char * RcsId =
LIB_CLUE_VERSION
"$Id$";

char *
StringUpper( char * str, size_t len )
{
  if( len )
    {
      const char * end = str + len;
      for( char * s = str; s < end; s++ )
	if( islower(*s) )  *s = toupper( *s );
    }
  else
    {
      for( char * s = str; *s; s++ )
	if( islower(*s) ) *s = toupper( *s );
    }
  return( str );
}



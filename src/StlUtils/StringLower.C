//
// File:        StringLower.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/06/95 11:56 
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 13:23:37  houghton
// Initaial implementation
//
//

#include "StringUtils.hh"

#include <cctype>
#include <cstddef>

static const char * RcsId =
LIB_CLUE_VERSION
"$Id$";

char *
StringLower( char * str, size_t len )
{
  if( len )
    {
      const char * end = str + len;
      for( char * s = str; s < end; s++ )
	if( isupper(*s) )  *s = tolower( *s );
    }
  else
    {
      for( char * s = str; *s; s++ )
	if( isupper(*s) ) *s = tolower( *s );
    }
  return( str );
}
	  



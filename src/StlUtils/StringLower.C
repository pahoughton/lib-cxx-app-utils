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
// Revision 1.2  1995/11/05 14:44:49  houghton
// Ports and Version ID changes
//
//

#if !defined( CLUE_SHORT_FN )
#include "StringUtils.hh"
#include <cctype>
#include <cstddef>
#else
#include "StrUtil.hh"
#include <cctype>
#include <cstddef>
#endif

CLUE_FUNCT_VERSION(
  StringLower,
  "$Id$" );

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
	  



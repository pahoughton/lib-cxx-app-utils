//
// File:        StringLower.C
// Project:	Clue
// Desc:        
//
//    Convert all uppercase characters (A-Z) to lowercase (a-z).
//    Returns str.
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/06/95 11:56 
//
// Revision History: (See end of file for Revision Log)
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
  if( len != NPOS )
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
	  
//
// Revision Log:
//
// $Log$
// Revision 2.2  1996/11/04 14:31:20  houghton
// Restructure header comments layout.
// Changed default len to be NPOS instead of 0.
//
// Revision 2.1  1995/11/10 12:41:11  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:49  houghton
// Ports and Version ID changes
//



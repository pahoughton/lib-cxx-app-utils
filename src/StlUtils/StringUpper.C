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
// Revision 2.1  1995/11/10 12:41:14  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:51  houghton
// Ports and Version ID changes
//
//

#if !defined( CLUE_SHORT_FN )
#include "StringUtils.hh"
#include <cstddef>
#include <cctype>
#else
#include "StrUtil.hh"
#include <cstddef>
#include <cctype>
#endif

CLUE_FUNCT_VERSION(
  StringUpper,
  "$Id$" );

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



//
// File:        StringUpper.C
// Project:	Clue
// Desc:        
//
//    Convert all lowercase characters (a-z) to uppercase (A-Z).
//    Returns str.
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/06/95 11:59 
//
// Revision History: (See end of file for Revision Log)
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
  if( len != NPOS )
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

//
// Revision Log:
//
// $Log$
// Revision 3.1  1996/11/14 01:24:20  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:32:30  houghton
// Restructure header comments layout.
// Changed default len to be NPOS instead of 0.
//
// Revision 2.1  1995/11/10 12:41:14  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:51  houghton
// Ports and Version ID changes
//
//

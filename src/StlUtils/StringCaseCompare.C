//
// File:        StringCaseCompare.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/01/95 07:07 
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 13:23:35  houghton
// Initaial implementation
//
//

#include "StringUtils.hh"
#include "Compare.hh"

#include <functional>
#include <algorithm>

#include <cstddef>
#include <cctype>

static const char * RcsId =
LIB_CLUE_VERSION
"$Id$";

int
StringCaseCompare( const char * one, const char * two )
{
  register int diff;
  register const char * s1 = one;
  register const char * s2 = two;
  
  for( ; !( (diff = tolower( *s1 ) - tolower( *s2 ) ) ) ; s1++, s2++ )
    {
      if( !(*s1) )
	{
	  break;
	}
    }
  return( diff );
      
}

int
StringCaseCompare( const char * one, const char * two, size_t len )
{
  register int diff;
  register size_t maxChars = len;
  register const char * s1 = one;
  register const char * s2 = two;
  
  for( ; maxChars && !( (diff = tolower( *s1 ) - tolower( *s2 ) ) ) ;
	 s1++, s2++, maxChars-- )
    {
      if( !(*s1) )
	{
	  break;
	}
    }
  return( diff );
  ;
}

int
StringCaseCompare(
  const char * one,
  size_t lenOne,
  const char * two,
  size_t lenTwo
  )
{
  int diff = StringCaseCompare( one, two, min( lenOne, lenTwo ) );
  return( diff ? diff : compare( lenOne, lenTwo ) );
}


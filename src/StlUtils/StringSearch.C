//
// File:        StringSearch.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     04/29/95 11:56 
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 13:23:38  houghton
// Initaial implementation
//
//

#include "StringUtils.hh"

#include <cstddef>
#include <cstring>

static const char * RcsId =
"$Id$";


#define SAFETY_ON

const char *
StringSearch(
  const char *  haystack,
  size_t    	hayLen,
  const char *  needle,
  size_t    	needleLen
  )
{
#ifdef SAFETY_ON
  // check for valid input params
  if( ! haystack || ! needle ) return( 0 );
#endif
  
  size_t    nLen = (needleLen) ? needleLen : strlen( needle );
  size_t    hLen = (hayLen) ? hayLen : strlen( haystack );

#ifdef SAFETY_ON
  if( ! hLen || ! nLen || nLen > hLen ) return( 0 );
#endif
  
  const char * hEnd = &(haystack[ hLen - nLen ]);
  const char * nEnd = &(needle[ nLen ]);

  register const char *     hay = haystack;
  register const char 	    ndlOne = *needle;
  
  while( hay <= hEnd )
    {
      // find the first needle char in the remaining haystack
      
      for( ; hay <= hEnd && *hay != ndlOne; hay++ );

      // didn't find it bye-bye
      if( hay > hEnd ) return( 0 );

      hay++;

      // the rest of the haystack & needle
      
      register const char * rHay = hay;	
      register const char * rNdl = needle + 1;
      
      // now look for the rest of the needle in the reset of the hay
      
      for( ; *rHay == *rNdl && rNdl < nEnd; rHay++, rNdl++ );

	// found it ... bye bye
      if( rNdl >= nEnd ) return( (rHay - nLen) );
    }
  return( 0 );
}


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
// Revision 2.1  1995/11/10 12:41:12  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:49  houghton
// Ports and Version ID changes
//
//

#if !defined( CLUE_SHORT_FN )
#include "StringUtils.hh"
#include <cstddef>
#include <cstring>
#else
#include "StrUtil.hh"
#include <cstddef>
#include <cstring>
#endif


CLUE_FUNCT_VERSION(
  StringReverseSearch,
  "$Id$" );


const char *
StringReverseSearch(
  const char *  haystack,
  size_t    	hayLen,
  const char *  needle,
  size_t    	needleLen
  )
{
#ifdef CLUE_SAFETY_ON
  // check for valid input params
  if( ! haystack || ! needle ) return( 0 );
#endif
  
  size_t    nLen = (needleLen) ? needleLen : strlen( needle );
  size_t    hLen = (hayLen) ? hayLen : strlen( haystack );

#ifdef CLUE_SAFETY_ON
  if( ! hLen || ! nLen || nLen > hLen ) return( 0 );
#endif

  const char * hEnd = &(haystack[ hLen - 1 ]);
  const char * nEnd = &(needle[ nLen - 1 ]);

  register const char *     hay = haystack + (nLen - 1);
  register const char 	    ndlEnd = *nEnd;
  
  while( hay <= hEnd )
    {
      // find the first needle char in the remaining haystack
      
      for( ; hay <= hEnd && *hEnd != ndlEnd; hEnd-- );

      // didn't find it bye-bye
      if( hay > hEnd ) return( 0 );

      hEnd--;

      // the rest of the haystack & needle
      
      register const char * rHay = hEnd;	
      register const char * rNdl = nEnd - 1;
      
      // now look for the rest of the needle in the reset of the hay
      
      for( ; *rHay == *rNdl && rNdl >= needle; rHay--, rNdl-- );

	// found it ... bye bye
      if( rNdl < needle ) return( rHay + 1);
    }
  return( 0 );
}


//
// File:        StringCaseReverseSearch.C
// Project:	Clue
// Desc:        
//
//    Search the string 'haystack' for the string 'needle' starting
//    from the end of 'haystack' and ignoring case. If 'needle' is
//    found in 'haystack' a pointer to the first char of 'needle'
//    in 'haystack' is returned. If 'needle' is not found, a 0 is
//    returned. Use NPOS for the len parameters if the corisponding
//    string is null (0) terminated.
//    
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     04/29/95 11:56 
//
// Revision History: (See end of file for Revision Log)
//

#if !defined( CLUE_SHORT_FN )
#include "StringUtils.hh"
#include <cstddef>
#include <cstring>
#include <cctype>
#else
#include "StrUtil.hh"
#include <cstddef>
#include <cstring>
#include <cctype>
#endif

CLUE_FUNCT_VERSION(
  StringCaseReverseSearch,
  "$Id$" );

const char *
StringCaseReverseSearch(
  const char *  haystack,
  size_t    	hayLen,
  const char *  needle,
  size_t    	needleLen
  )
{
#ifdef CLUE_SAFETY_ON
  // check for valid input params
  if( ! haystack ||
      ! hayLen	 ||
      ! needle   ||
      ! needleLen )
    return( 0 );
#endif
  
  size_t    nLen = (needleLen != NPOS) ? needleLen : strlen( needle );
  size_t    hLen = (hayLen != NPOS ) ? hayLen : strlen( haystack );

#ifdef CLUE_SAFETY_ON
  if( ! hLen || ! nLen || nLen > hLen ) return( 0 );
#endif
  
  const char * hEnd = &(haystack[ hLen - 1 ]);
  const char * nEnd = &(needle[ nLen - 1 ]);

  register const char *     hay = haystack + (nLen - 1);
  register const char 	    ndlEnd = tolower( *nEnd );
  
  while( hay <= hEnd )
    {
      // find the first needle char in the remaining haystack
      
      for( ; hay <= hEnd && tolower(*hEnd) != ndlEnd; hEnd-- );

      // didn't find it bye-bye
      if( hay > hEnd ) return( 0 );

      hEnd--;

      // the rest of the haystack & needle
      
      register const char * rHay = hEnd;	
      register const char * rNdl = nEnd - 1;
      
      // now look for the rest of the needle in the reset of the hay
      
      for( ; tolower( *rHay ) == tolower( *rNdl ) && rNdl >= needle;
	     rHay--, rNdl-- );

	// found it ... bye bye
      if( rNdl < needle ) return( rHay + 1 );
    }
  return( 0 );
}

//
// Revision Log:
//
// $Log$
// Revision 3.1  1996/11/14 01:24:16  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:30:09  houghton
// Restructure header comments layout.
// Changed default len to be NPOS instead of 0.
//
// Revision 2.1  1995/11/10 12:41:10  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:48  houghton
// Ports and Version ID changes
//
//


     

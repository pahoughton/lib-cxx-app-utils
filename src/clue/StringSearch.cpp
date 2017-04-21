// 1995-04-29 (cc) <paul4hough@gmail.com>
/**

   Search a string 'haystack' for the string 'needle'. If
   'needle' is found in 'haystack' a pointer to the first char
   of 'needle' in 'haystack' is returned. If 'needle' is not found,
   a 0 is returned. Use NPOS for the len parameters if the
   corisponding string is null (0) terminated.
**/

#include "StringUtils.hpp"
#include <cstddef>
#include <cstring>


namespace clue {

const char *
StringSearch(
  const char *  haystack,
  size_t    	hayLen,
  const char *  needle,
  size_t    	needleLen
  )
{
  // check for valid input params
  if( ! haystack ||
      ! hayLen	 ||
      ! needle   ||
      ! needleLen )
    return( 0 );

  size_t    nLen = (needleLen != NPOS) ? needleLen : strlen( needle );
  size_t    hLen = (hayLen != NPOS ) ? hayLen : strlen( haystack );

  if( ! hLen || ! nLen || nLen > hLen ) return( 0 );

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
} // namespace clue

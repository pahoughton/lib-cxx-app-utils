// 1995-04-29 (cc) <paul4hough@gmail.com>

/**
   Search a string 'haystack' for the string 'needle' starting
   from the end of 'haystack'. If 'needle' is found in 'haystack'
   a pointer to the first char of 'needle' in 'haystack' is
   returned. If 'needle' is not found, a 0 is returned.
   Use NPOS for the len parameters if the corisponding string
   is null (0) terminated.
**/

#include "StringUtils.hpp"
#include <cstddef>
#include <cstring>


namespace clue {
const char *
StringReverseSearch(
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

}

// 1997-08-11 (cc) <paul4hough@gmail.com>

#include "StringUtils.hpp"
#include <cstddef>
#include <cstring>

namespace clue {

size_t
StringFirstNotOf(
  const char *  haystack,
  size_t        hayLen,
  const char *  needle,
  size_t        needleLen
  )
{
  // check for valid input params
  if( ! haystack ||
      ! hayLen	 ||
      ! needle   ||
      ! needleLen )
    return( NPOS );

  size_t    nLen = (needleLen != NPOS) ? needleLen : strlen( needle );
  size_t    hLen = (hayLen != NPOS ) ? hayLen : strlen( haystack );

  if( ! hLen || ! nLen ) return( NPOS );

  register const char *     hBeg = haystack;
  register const char *	    nBeg = needle;

  const char * hEnd = hBeg + hLen;
  const char * nEnd = nBeg + nLen;

  for( const char * h = hBeg; h < hEnd; h++ )
    {
      const char * n = nBeg;
      for( ; n < nEnd ; n++ )
	{
	  if( *h == *n )
	    {
	      break;
	    }
	}
      if( n == nEnd )
	{
	  return( h - hBeg );
	}
    }

  return( NPOS );
}

}; // namespace clue

// 1997-12-20 (cc) <paul4hough@gmail.com>

#include "StringUtils.hpp"

namespace clue {
char *
StripTrailing( char * buffer, const char * white, size_t bufferSize )
{
  long      len = ( bufferSize == NPOS ? strlen( buffer ) : bufferSize );
  long	    pos = len;

  for( ; pos >= 0 ; -- pos )
    if( ! strchr( white, buffer[pos] ) )
      break;

  if( pos < len )
    buffer[ pos + 1 ] = 0;

  return( buffer );
}
} // namepace clue

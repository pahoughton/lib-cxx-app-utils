// 1995-05-06 (cc) <paul4hough@gmail.com>

#include "StringUtils.hpp"
#include <cctype>
#include <cstddef>

namespace clue {
char *
StringLower( char * str, size_t len )
{
  if( len != NPOS )
    {
      const char * end = str + len;
      for( char * s = str; s < end; s++ )
	if( isupper(*s) )  *s = tolower( *s );
    }
  else
    {
      for( char * s = str; *s; s++ )
	if( isupper(*s) ) *s = tolower( *s );
    }
  return( str );
}
}

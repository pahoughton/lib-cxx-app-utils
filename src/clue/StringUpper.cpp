// 1995-05-06 (cc) <paul4hough@gmail.com>

#include "StringUtils.hpp"
#include <cstddef>
#include <cctype>

namespace clue {
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
}; // namespace clue

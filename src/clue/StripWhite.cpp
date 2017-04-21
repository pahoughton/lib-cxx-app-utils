// 1997-12-20 (cc) <paul4hough@gmail.com>

#include "StringUtils.hpp"

namespace clue {

char *
StripWhite( char * buffer, const char * white, size_t bufSize )
{

  const char *  beg;
  size_t    	len;

  if( bufSize == NPOS )
    {
      beg = buffer + strspn( buffer, white );
      len = strlen( buffer );
    }
  else
    {
      // if the buffer has no size, don't touch it.
      if( bufSize == 0 )
	return( buffer );

      size_t i;
      for( i = 0; i < bufSize; i++ )
	{
	  if( ! strchr( white, buffer[i] ) )
	    {
	      break;
	    }
	}
      beg = buffer + i;
      len = bufSize - 1;
    }

  for( ; len; len-- )
    {
      if( ! strchr( white, buffer[len] ) )
	{
	  break;
	}
    }

  memmove( buffer, beg, (len - (beg - buffer)) + 1);

  buffer[ (len - (beg - buffer)) + 1 ] = 0;

  return( buffer );
}
} // namespace clue

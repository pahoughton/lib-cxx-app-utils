// 1995-05-06 (cc) <paul4hough@gmail.com>

#include "StringUtils.hpp"
#include <cctype>
#include <cstddef>

namespace clue {
char *
StringCapitalize( char * str, size_t len )
{
  if( len != NPOS )
    {
      const char * end = str + len;
      for( char * s = str; s < end; s++ )
	{
	  int inword = islower(*s);

	  if( inword )
	    *s = toupper( *s );
	  else
	    inword = isupper(*s) || isdigit(*s);

	  if( inword )
	    {
	      for( s++; s < end; s++ )
		{
		  if( isupper(*s) )
		    *s = tolower(*s);
		  else
		    if( ! islower(*s) && ! isdigit(*s) && (*s != '\'' ) )
		      break;
		}
	    }
	}
    }
  else
    {
      for( char * s = str; *s; s++ )
	{
	  int inword = islower(*s);

	  if( inword )
	    *s = toupper( *s );
	  else
	    inword = isupper(*s) || isdigit(*s);

	  if( inword )
	    {
	      for( s++; *s; s++ )
		{
		  if( isupper(*s) )
		    *s = tolower(*s);
		  else
		    if( ! islower(*s) && ! isdigit(*s) && (*s != '\'' ) )
		      break;
		}
	    }
	}
    }
  return( str );
}

}

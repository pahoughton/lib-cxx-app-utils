
#include <LibTest.hh>
#include <StringUtils.hh>

#include <limits.h>


bool
tCharToInt( LibTest & test )
{
  for( char c = 0; c < CHAR_MAX; c++ )
    {
      int   n = CharToInt( c );

      test( ( ! isalpha( c ) && ! isdigit( c ) && n == -1 ) ||
	    ( isalpha(c) && ( n == ( 10 + (tolower(c) - 'a') ) ) ) ||
	    ( isdigit(c) && ( n == ( c - '0' ) ) ) );
      
    }
  return( true );
}

	  

#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StringUtils.hh>
#include <climits>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StrUtil.hh>
#include <climits>
#endif


bool
tCharToInt( LibTest & tester )
{
  for( char c = 0; c < CHAR_MAX; c++ )
    {
      int   n = CharToInt( c );

      TEST( ( ! isalpha( c ) && ! isdigit( c ) && n == -1 ) ||
	    ( isalpha(c) && ( n == ( 10 + (tolower(c) - 'a') ) ) ) ||
	    ( isdigit(c) && ( n == ( c - '0' ) ) ) );
      
    }
  return( true );
}

	  

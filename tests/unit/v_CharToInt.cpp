// 1996-10-30 (cc) <paul4hough@gmail.com>

#include <clue/StringUtils.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <climits>
#include <cctype>

static valid::verify verify("clue::CharToInt");
using namespace clue;


bool
v_CharToInt( void )
{
  for( char c = 0; c < CHAR_MAX; c++ )
    {
      int   n = CharToInt( c );

      TEST( ( ! isalpha( c ) && ! isdigit( c ) && n == -1 ) ||
	    ( isalpha(c) && ( n == ( 10 + (tolower(c) - 'a') ) ) ) ||
	    ( isdigit(c) && ( n == ( c - '0' ) ) ) );

    }
  return( verify.is_valid() );
}

// 1996-10-30 (cc) <paul4hough@gmail.com>

#include <clue/StringUtils.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::CharIsBaseDigit");
using namespace clue;


bool
v_CharIsBaseDigit( void )
{
  {
    // IsBaseDigit( char, unsigned short)

    for( unsigned short base = 2; base < 36; base++ )
      {
	{
	  for( char num = ('0' - 2 ); num <= '9'; num++ )
	    {
	      bool result = CharIsBaseDigit( num, base );

	      TEST( ( result == true && num >= '0' && (num - '0') < base ) ||
		    ( result == false && ( num < '0' || (num - '0') >= base ) ) );
	    }
	}

	{
	  for( char num = ('a' - 2 ); num <= 'z'; num++ )
	    {
	      bool result = CharIsBaseDigit( num, base );

	      TEST( ( result == true && ( base > 10 &&
					  (10 + (num - 'a')) >= 10 &&
					  (10 + (num - 'a')) < base ) ) ||
		    ( result == false && ( base < 10 ||
					   (10 + (num - 'a')) < 10 ||
					   (10 + (num - 'a')) >= base ) ) );
	    }
	}

	{
	  for( char num = ('A' - 2 ); num <= 'Z'; num++ )
	    {
	      bool result = CharIsBaseDigit( num, base );

	      TEST( ( result == true && ( base > 10 &&
					  (10 + (num - 'A')) >= 10 &&
					  (10 + (num - 'A')) < base ) ) ||
		    ( result == false && ( base < 10 ||
					   (10 + (num - 'A')) < 10 ||
					   (10 + (num - 'A')) >= base ) ) );
	    }
	}

      }
  }
  return( verify.is_valid() );
}

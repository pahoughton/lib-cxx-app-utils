// 1996-10-31 (cc) <paul4hough@gmail.com>

#include <clue/Clue.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::IsBaseDigit");
using namespace clue;



bool
v_IsBaseDigit( void )
{
  {
    // IsBaseDigit( int, unsigned short )

    for( unsigned short base = 2; base < 64; base++ )
      {
	for( int num = -2; num < base+2; num++ )
	  {
	    bool result = IsBaseDigit( num,  base );

	    TEST( ( result == true && num >= 0 && num < base )  ||
		  ( result == false && ( num < 0 || num >= base ) ) );
	  }
      }
  }
  return( verify.is_valid() );
}

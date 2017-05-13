// 1998-11-04 (cc) <paul4hough@gmail.com>

#include <clue/Clue.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::Between");
using namespace clue;


bool
v_Between( void )
{
  {
    long    a( 1023 );
    long    b( a + 2732 );

    {
      for( short t = a; t <= b; ++ t )
	{
	  TEST( Between( a, b, t ) );
	  TEST( Between( b, a, t ) );
	}
    }
    TEST( ! Between( a, b, a * -1 ) );
    TEST( ! Between( b, a, a * -1 ) );

    TEST( ! Between( a, b, 0 ) );
    TEST( ! Between( b, a, 0 ) );

    TEST( ! Between( a, b, a - 1 ) );
    TEST( ! Between( b, a, a - 1 ) );

    TEST( ! Between( a, b, b + 1 ) );
    TEST( ! Between( b, a, b + 1 ) );

    TEST( ! Between( a, b, b + a ) );
    TEST( ! Between( b, a, b + a ) );
  }

  return( verify.is_valid() );
}

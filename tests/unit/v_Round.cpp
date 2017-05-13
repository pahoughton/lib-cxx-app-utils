// 1996-10-31 (cc) <paul4hough@gmail.com>

#include <clue/Clue.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::Round");
using namespace clue;


bool
v_Round( void )
{
  {
    // Round( int, number )

    int t = 50;

    TEST( Round( t, 10 ) == 50 );
    t = 51;
    TEST( Round( t, 10 ) == 50 );
    t = 55;
    TEST( Round( t, 10 ) == 60 );
    t = 59;
    TEST( Round( t, 10 ) == 60 );

    t = 10;
    TEST( Round( t, 5 ) == 10 );
    t = 11;
    TEST( Round( t, 5 ) == 10 );
    t = 12;
    TEST( Round( t, 5 ) == 10 );
    t = 13;
    TEST( Round( t, 5 ) == 15 );
    t = 14;
    TEST( Round( t, 5 ) == 15 );


    t = -32;
    TEST( Round( t, 5 ) == -30 );
    t = -33;
    TEST( Round( t, 5 ) == -35 );
    t = -34;
    TEST( Round( t, 5 ) == -35 );

    t = -33;
    TEST( Round( t, 10 ) == -30 );
    t = -34;
    TEST( Round( t, 10 ) == -30 );
    t = -35;
    TEST( Round( t, 10 ) == -40 );
    t = -36;
    TEST( Round( t, 10 ) == -40 );

    TEST( Round( 23, 5 ) == 25 ); // doc example
  }

  {
    long t = 50;

    TEST( Round( t, 10 ) == 50 );
    t = 51;
    TEST( Round( t, 10 ) == 50 );
    t = 55;
    TEST( Round( t, 10 ) == 60 );
    t = 59;
    TEST( Round( t, 10 ) == 60 );

    t = 10;
    TEST( Round( t, 5 ) == 10 );
    t = 11;
    TEST( Round( t, 5 ) == 10 );
    t = 12;
    TEST( Round( t, 5 ) == 10 );
    t = 13;
    TEST( Round( t, 5 ) == 15 );
    t = 14;
    TEST( Round( t, 5 ) == 15 );
  }

  {
    // RoundUp( int, number )

    int t = 50;

    TEST( RoundUp( t, 10 ) == 50 );
    t = 51;
    TEST( RoundUp( t, 10 ) == 60 );
    t = 55;
    TEST( RoundUp( t, 10 ) == 60 );
    t = 59;
    TEST( RoundUp( t, 10 ) == 60 );

    t = 10;
    TEST( RoundUp( t, 5 ) == 10 );
    t = 11;
    TEST( RoundUp( t, 5 ) == 15 );
    t = 12;
    TEST( RoundUp( t, 5 ) == 15 );
    t = 13;
    TEST( RoundUp( t, 5 ) == 15 );
    t = 14;
    TEST( RoundUp( t, 5 ) == 15 );

    t = -30;
    TEST( RoundUp( t, 10 ) == -30 );
    t = -32;
    TEST( RoundUp( t, 10 ) == -30 );
    t = -34;
    TEST( RoundUp( t, 10 ) == -30 );
    t = -39;
    TEST( RoundUp( t, 10 ) == -30 );

    TEST( RoundUp( 22, 5 ) == 25 ); // doc example
  }

  {
    // RoundDown( int, number )

    int t = 50;

    TEST( RoundDown( t, 10 ) == 50 );
    t = 51;
    TEST( RoundDown( t, 10 ) == 50 );
    t = 55;
    TEST( RoundDown( t, 10 ) == 50 );
    t = 59;
    TEST( RoundDown( t, 10 ) == 50 );

    t = 10;
    TEST( RoundDown( t, 5 ) == 10 );
    t = 11;
    TEST( RoundDown( t, 5 ) == 10 );
    t = 12;
    TEST( RoundDown( t, 5 ) == 10 );
    t = 13;
    TEST( RoundDown( t, 5 ) == 10 );
    t = 14;
    TEST( RoundDown( t, 5 ) == 10 );

    t = -32;
    TEST( RoundDown( t, 10 ) == -40 );
    t = -34;
    TEST( RoundDown( t, 10 ) == -40 );
    t = -39;
    TEST( RoundDown( t, 10 ) == -40 );
    t = -40;
    TEST( RoundDown( t, 10 ) == -40 );

    TEST( RoundDown( 23, 5 ) == 20 ); // doc example
  }

  return( verify.is_valid() );
}

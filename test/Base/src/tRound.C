#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
#endif

bool
tRound( LibTest & tester )
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
  }

  return( true );
}

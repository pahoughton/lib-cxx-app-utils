#include <LibTest.hh>
#include <Clue.hh>

bool
tRound( LibTest & test )
{
  {
    // Round( int, number )

    int t = 50;

    test( Round( t, 10 ) == 50 );
    t = 51;
    test( Round( t, 10 ) == 50 );
    t = 55;
    test( Round( t, 10 ) == 60 );
    t = 59;
    test( Round( t, 10 ) == 60 );

    t = 10;
    test( Round( t, 5 ) == 10 );
    t = 11;
    test( Round( t, 5 ) == 10 );
    t = 12;
    test( Round( t, 5 ) == 10 );
    t = 13;
    test( Round( t, 5 ) == 15 );
    t = 14;
    test( Round( t, 5 ) == 15 );
  }

  {
    long t = 50;
   
    test( Round( t, 10 ) == 50 );
    t = 51;
    test( Round( t, 10 ) == 50 );
    t = 55;
    test( Round( t, 10 ) == 60 );
    t = 59;
    test( Round( t, 10 ) == 60 );

    t = 10;
    test( Round( t, 5 ) == 10 );
    t = 11;
    test( Round( t, 5 ) == 10 );
    t = 12;
    test( Round( t, 5 ) == 10 );
    t = 13;
    test( Round( t, 5 ) == 15 );
    t = 14;
    test( Round( t, 5 ) == 15 );
  }

  {
    // RoundUp( int, number )

    int t = 50;

    test( RoundUp( t, 10 ) == 50 );
    t = 51;
    test( RoundUp( t, 10 ) == 60 );
    t = 55;
    test( RoundUp( t, 10 ) == 60 );
    t = 59;
    test( RoundUp( t, 10 ) == 60 );

    t = 10;
    test( RoundUp( t, 5 ) == 10 );
    t = 11;
    test( RoundUp( t, 5 ) == 15 );
    t = 12;
    test( RoundUp( t, 5 ) == 15 );
    t = 13;
    test( RoundUp( t, 5 ) == 15 );
    t = 14;
    test( RoundUp( t, 5 ) == 15 );
  }
  
  {
    // RoundDown( int, number )

    int t = 50;

    test( RoundDown( t, 10 ) == 50 );
    t = 51;
    test( RoundDown( t, 10 ) == 50 );
    t = 55;
    test( RoundDown( t, 10 ) == 50 );
    t = 59;
    test( RoundDown( t, 10 ) == 50 );

    t = 10;
    test( RoundDown( t, 5 ) == 10 );
    t = 11;
    test( RoundDown( t, 5 ) == 10 );
    t = 12;
    test( RoundDown( t, 5 ) == 10 );
    t = 13;
    test( RoundDown( t, 5 ) == 10 );
    t = 14;
    test( RoundDown( t, 5 ) == 10 );
  }

  return( true );
}

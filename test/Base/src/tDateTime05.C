#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <DateTime.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <DateTime.hh>
#endif

bool
tDateTime05( LibTest & tester )
{
  
  {
    // add( const DateTime & )

    DateTime	dt( 300 );

    DateTime	value( 100 );

    TEST( dt.add( value ).getTimeT() == 400 );
    
  }

  {
    // add( long )

    DateTime	dt( "2/17/95 11:30:30" );

    time_t  orig = dt.getTimeT();
      
    TEST( dt.add( 100 ).getTimeT() == orig + 100 );
    
  }

  {
    // addSec( long )

    DateTime	dt( "2/17/95 11:30:30" );

    time_t  orig = dt.getTimeT();
      
    TEST( dt.addSec( 100 ).getTimeT() == orig + 100 );
    
  }

  {
    // addMin( long )

    DateTime	dt( "2/17/95 11:30:30" );

    time_t  orig = dt.getTimeT();
      
    TEST( dt.addMin( 30 ).getTimeT() == orig + (30 * 60) );

    TEST( dt.getHour() == 12 );
    TEST( dt.getMinute() == 0 );
    TEST( dt.getSecond() == 30 );
    
  }

  {
    // addHour( long )

    DateTime	dt( "2/17/95 11:30:30" );

    time_t  orig = dt.getTimeT();
      
    TEST( dt.addHour( 30 ).getTimeT() == orig + (30 * 60 * 60) );

    TEST( dt.getDayOfMonth() == 18 );
    TEST( dt.getHour() == 17 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );
    
  }

  {
    // addDay( long )

    DateTime	dt( "2/17/95 11:30:30" );

    time_t  orig = dt.getTimeT();
      
    TEST( dt.addDay( 30 ).getTimeT() == orig + (24 * 30 * 60 * 60) );

    TEST( dt.getMonth() == 3 );
    TEST( dt.getDayOfMonth() == 19 );
    TEST( dt.getHour() == 11 );
    TEST( dt.getMinute() == 30 );
    TEST( dt.getSecond() == 30 );
    
  }
  return( true );
}

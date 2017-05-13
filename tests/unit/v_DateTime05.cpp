// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/DateTime.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::DateTime05");
using namespace clue;

bool
v_DateTime05( void )
{

  {
    // add( const DateTime & )

    DateTime	dt( 300 );

    DateTime	value( 100 );

    TEST( dt.add( value ).timet() == 400 );

  }

  {
    // add( long )

    DateTime	dt( "2/17/95 11:30:30" );

    time_t  orig = dt.timet();

    TEST( dt.add( 100 ).timet() == orig + 100 );

  }

  {
    // addSec( long )

    DateTime	dt( "2/17/95 11:30:30" );

    time_t  orig = dt.timet();

    TEST( dt.addSec( 100 ).timet() == orig + 100 );

  }

  {
    // addMin( long )

    DateTime	dt( "2/17/95 11:30:30" );

    time_t  orig = dt.timet();

    TEST( dt.addMin( 30 ).timet() == orig + (30 * 60) );

    TEST( dt.hour() == 12 );
    TEST( dt.minute() == 0 );
    TEST( dt.second() == 30 );

  }

  {
    // addHour( long )

    DateTime	dt( "2/17/95 11:30:30" );

    time_t  orig = dt.timet();

    TEST( dt.addHour( 30 ).timet() == orig + (30 * 60 * 60) );

    TEST( dt.mday() == 18 );
    TEST( dt.hour() == 17 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

  }

  {
    // addDay( long )

    DateTime	dt( "2/17/95 11:30:30" );

    time_t  orig = dt.timet();

    TEST( dt.addDay( 30 ).timet() == orig + (24 * 30 * 60 * 60) );

    TEST( dt.month() == 3 );
    TEST( dt.mday() == 19 );
    TEST( dt.hour() == 11 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 30 );

  }
  return( verify.is_valid() );
}

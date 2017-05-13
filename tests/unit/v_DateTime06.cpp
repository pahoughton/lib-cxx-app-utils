// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/DateTime.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <functional>
#include <cstring>

static valid::verify verify("clue::DateTime06");
using namespace clue;

bool
v_DateTime06( void )
{
    // void setTm( void ) - NO TEST (tested by other test)

  {
    // compare( const DateTime & )

    DateTime	d1( "2/17/95 11:30:30" );
    DateTime	d2( d1 );

    TEST( d1 == d2 );
    TEST( ! d1.compare( d2 ) );
    TEST( ! compare( d1, d2 ) );

    TEST( d1 == d2 );
    TEST( ! d1.compare( d2 ) );
    TEST( ! compare( d1, d2 ) );

    TEST( d1 == d2 );
    TEST( ! d1.compare( d2 ) );
    TEST( ! compare( d1, d2 ) );

    d1.addMin();

    TEST( d1.compare( d2 ) > 0 );
    TEST( d1 > d2 );
    TEST( compare( d1, d2 ) > 0 );

  }

  {
    // operator time_t ( void ) const

    DateTime	dt( "2/17/95 11:30:30" );

    TEST( (time_t)dt == dt.timet() );

  }

  {
    // operator == ( const DateTime & ) const

    DateTime	d1( "2/17/95 11:30:30" );
    DateTime	d2( "2/17/95 11:30:30" );

    TEST( d1 == d2 );
    d2.addSec();
    TEST( d1 != d2 );

  }

  {
    // operator !=( const DateTime & ) const

    DateTime	d1( "2/17/95 11:30:30" );
    DateTime	d2( "2/17/95 11:30:30" );

    TEST( d1 == d2 );
    d2.addSec();
    TEST( d1 != d2 );

  }

  {
    // const char * getClassName(void) - NO TEST NEEDED

  }

  {
    // Bool 	     good( void ) - NO TEST (tested by setValid());

  }

  {
    // const char * error( void ) - NO TEST NEEDED

  }
  return( verify.is_valid() );
}

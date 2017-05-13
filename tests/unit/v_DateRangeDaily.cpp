// 1994-02-20 (cc) Paul Houghton <paul4hough@gmail.com>

#include <clue/DateRangeDaily.hpp>

#include <clue/DateTimeUtils.hpp>
#include <functional>
#include <sstream>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::DateRangeDaily");
using namespace clue;


bool
v_DateRangeDaily( void )
{
  {
    // DateRangeDaily( time_t, time_t )
    // getSecOfDay( void ) const
    // getDayOfWeek( void ) const
    // getStart( void ) const

    time_t  startTime = (6 * SecPerHour);
    time_t  duration  = 30;

    const DateRangeDaily  t( startTime, duration );

    TEST( t.secOfDay() == startTime );
    TEST( t.start() == startTime );
    TEST( t.dur() == duration );
  }

  {
    // in( const DateTime & ) const
    DateRangeDaily  t( 8 * SecPerHour, (17 - 8) * SecPerHour );

    {
      DateTime	dt( 2003, 5, 12, 6, 00, 00 );
      TEST( ! t.isIn( dt ) );
    }
    {
      DateTime	dt( 2003, 5, 12, 7, 59, 59 );
      TEST( ! t.isIn( dt ) );
    }
    {
      DateTime	dt( 2003, 5, 12, 8, 00, 00 );
      TEST( t.isIn( dt ) );
    }
    {
      DateTime	dt( 2003, 5, 12, 8, 00, 01 );
      TEST( t.isIn( dt ) );
    }
    {
      DateTime	dt( 2003, 5, 12, 12, 00, 00 );
      TEST( t.isIn( dt ) );
    }
    {
      DateTime	dt( 2003, 5, 12, 16, 59, 59 );
      TEST( t.isIn( dt ) );
    }
    {
      DateTime	dt( 2003, 5, 12, 17, 00, 00 );
      TEST( t.isIn( dt ) );
    }
    {
      DateTime	dt( 2003, 5, 12, 17, 00, 01 );
      TEST( ! t.isIn( dt ) );
    }
    {
      DateTime	dt( 2003, 5, 12, 20, 00, 00 );
      TEST( ! t.isIn( dt ) );
    }

    {
      DateTime	dt( 2003, 5, 11, 17, 00, 00 );
      TEST( t.isIn( dt ) );
    }
    {
      DateTime	dt( 2003, 5, 11, 17, 00, 01 );
      TEST( ! t.isIn( dt ) );
    }
  }

  {
    // secIn( const DateRange & ) const

    DateRangeDaily  t( 6 * SecPerHour, 30 );

    TEST( t.dur() == 30 );

    time_t  when = 699321600;	    // is 2/29/92 00:00:00 (gmt)

    DateRange	r( when, 60 );

    TEST( t.secIn( r ) == 0 );

    r.dur( (6 * SecPerHour) + 15 );

    TEST( t.secIn( r ) == 15 );

    r.timet( when + (6 * SecPerHour) + 15 );
    r.dur( 120 );
    TEST( t.secIn( r ) == 15 );

    r.timet( when + ( 7 * SecPerHour ) );
    TEST( t.secIn( r ) == 0 );

    r.dur( SecPerDay );
    TEST( t.secIn( r ) == 30 );

    r.dur( SecPerDay * 2 );
    TEST( t.secIn( r ) == 60 );
  }

  {
    // startsIn( const DateRange & ) const

    DateRangeDaily  t( 6 * SecPerHour, 30 );

    TEST( t.dur() == 30 );

    time_t  when = 699321600;	    // is 2/29/92 00:00:00 (gmt)

    DateRange	r( when, 60 );

    TEST( t.startsIn( r ) == 0 );

    r.dur( SecPerDay );
    TEST( t.startsIn( r ) == 0 );

    r.timet( when + ( 6 * SecPerHour ) );
    r.dur( 10 );

    TEST( t.startsIn( r ) == 10 );

    r.timet( when + ( 6 * SecPerHour ) + 15 );
    r.dur( ( 2 * SecPerDay ) + 60 );

    TEST( t.startsIn( r ) == 75 );
  }

  {
    // setStart( void )

    time_t  startTime = (6 * SecPerHour);
    time_t  duration  = 30;

    DateRangeDaily  t( startTime, duration );

    TEST( t.start( 5 * SecPerHour ).start() == ( 5 * SecPerHour ) );
  }

  {
    // compare( const DateRangeDaily & ) const
    // operator == ( const DateRangeDaily & )
    // operator <  ( const DateRangeDaily & )
    // operator >  ( const DateRangeDaily & )

    time_t  startTime = (6 * SecPerHour);
    time_t  duration  = 30;

    const DateRangeDaily    t1( startTime, duration );
    DateRangeDaily	    t2( startTime, duration );

    TEST( t1.compare( t2 ) == 0 );
    TEST( t1 == t2 );

    t2.dur( duration - 1 );

    TEST( t1.compare( t2 ) >  0 );
    TEST( t1 > t2 );

    TEST( t2.compare( t1 ) <  0 );
    TEST( t2 < t1 );

    t2.dur( duration );
    t2.start( startTime - 1 );
    TEST( t1.compare( t2 ) > 0 );
    TEST( t1 > t2 );

    TEST( t2.compare( t1 ) < 0 );
    TEST( t2 < t1 );
  }

  {
    // getBinSize( void ) const

    const DateRangeDaily tw( 6 * SecPerHour, 30 );

    TEST( tw.getBinSize() == (sizeof( time_t ) * 2 ) );
  }

  {
    // write( ostream & ) const
    // read( istream & )

    const DateRangeDaily tw( 6 * SecPerHour, 30 );
    DateRangeDaily	 tr( 0, 0 );

    std::stringstream tStrm;

    std::streampos gpos = tStrm.tellg();
    std::streampos ppos = tStrm.tellp();


    TEST( ppos == 0 );
    TEST( gpos == 0 );

    tw.write( tStrm );
    ppos += (std::streampos) tw.getBinSize();
    TEST( ppos == tStrm.tellp() );

    tr.read( tStrm );
    gpos += (std::streampos) tr.getBinSize();
    TEST( gpos == tStrm.tellg() );
    TEST( tr == tw );
    TEST( tr.timet() == tw.timet() );
    TEST( tr.start() == tw.start() );
    TEST( tr.dur() == tw.dur() );
  }

  {
    // toStream( ostream & dest ) const
    // operator << ( ostream &, const DateRangeDaily & )

    const DateRangeDaily  t( 6 * SecPerHour, 30 );

    std::stringstream tStream;
    t.toStream( tStream );
    tStream << t;
  }

  {
    // good( void ) const
    // error( void ) const

    const DateRangeDaily  t( 6 * SecPerHour, 30 );

    TEST( t.good() );
    TEST( t.error() != 0 );

  }

  {
    // ::compare( const DateRangeDaily &, const DateRangeDaily & )

    time_t  startTime = (6 * SecPerHour);
    time_t  duration  = 30;

    const DateRangeDaily    t1( startTime, duration );
    DateRangeDaily	    t2( startTime, duration );

    TEST( compare( t1, t2 ) == 0 );
    TEST( t1 == t2 );

    t2.dur( duration - 1 );

    TEST( compare( t1, t2 ) >  0 );
    TEST( t1 > t2 );

    TEST( compare( t2, t1 ) <  0 );
    TEST( t2 < t1 );

    t2.dur( duration );
    t2.start( startTime - 1 );
    TEST( compare( t1, t2 ) > 0 );
    TEST( t1 > t2 );

    TEST( compare( t2, t1 ) < 0 );
    TEST( t2 < t1 );
  }
  return( verify.is_valid() );
}

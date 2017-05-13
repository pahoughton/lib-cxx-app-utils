// 1994-02-20 (cc) Paul Houghton <paul4hough@gmail.com>

#include <clue/DateRange.hpp>

#include <clue/DateTimeUtils.hpp>
#include <functional>
#include <sstream>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::DateRange");
using namespace clue;

bool
v_DateRange( void )
{
  {
    // DateRange( time_t, time_t )
    // dur( void ) const

    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    time_t  dur  = SecPerDay;

    DateRange t( when, dur );

    TEST( t.timet() == when );
    TEST( t.dur() == dur );
  }

  {
    // DateRange( const DateTime &, time_t )

    const DateTime	dt( 699342350 );

    time_t	dur = SecPerDay;

    DateRange	t( dt, dur );

    TEST( t.timet() == dt.timet() );
    TEST( t.dur() == dur );
  }

  {
    // DateRange( const DateTime &, const DateTime & )

    time_t	when = 699342350;
    time_t	dur  = SecPerDay;

    const DateTime  start( when );
    const DateTime  stop( when + dur );

    DateRange	t( start, stop );

    TEST( t.timet() == when );
    TEST( t.dur() == dur );
  }

  {
    // setDur( time_t newDur )

    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)
    time_t  dur  = SecPerDay;

    DateRange t( when, dur );

    TEST( t.dur( 60 ).dur() == 60 );
    TEST( t.dur() == 60 );
  }

  {
    // getSecoOfDay( void ) const

    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)
    const DateRange t( when, 10 );

    TEST( t.secOfDay() == 20750 );
  }

  {
    // secIn( const DateRange & ) const

    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)
    time_t  dur  = SecPerDay;

    DateRange	t( when, dur );
    DateRange	r( when - 120, 60 );

    TEST( t.secIn( r ) == 0 );

    r.dur( 120 );
    TEST( t.secIn( r ) == 0 );

    r.dur( 125 );
    TEST( t.secIn( r ) == 5 );

    r.dur( 120 + dur );
    TEST( t.secIn( r ) == dur );

    r.dur( 120 + dur + 5 );
    TEST( t.secIn( r ) == dur );

    r.timet( when );
    TEST( t.secIn( r ) == dur );

    r.dur( dur );
    TEST( t.secIn( r ) == dur );

    r.dur( 20 );
    TEST( t.secIn( r ) == 20 );

    t.timet( when + dur );
    TEST( t.secIn( r ) == 0 );

    t.timet( when + dur + 5 );
    TEST( t.secIn( r ) == 0 );
  }

  {
    // startsIn( const DateRange & ) const

    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)
    time_t  dur  = SecPerDay;

    DateRange	t( when, dur );
    DateRange	r( when - 120, 60 );

    TEST( t.startsIn( r ) == 0 );

    r.timet( when - 30 );
    TEST( t.startsIn( r ) == 0 );

    r.timet( when );
    TEST( t.startsIn( r ) == 60 );

    r.timet( when + 60 );
    TEST( t.startsIn( r ) == 60 );

    r.timet( when + dur - 30 );
    TEST( t.startsIn( r ) == 30 );

    r.timet( when + dur );
    TEST( t.startsIn( r ) == 0 );

    r.timet( when + dur + 5 );
    TEST( t.startsIn( r ) == 0 );
  }

  {
    // compare( const DateRange & ) const
    // operator == ( const DateRange & ) const
    // operator <  ( const DateRange & ) const
    // operator >  ( const DateRange & ) const

    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    const DateRange t1( when, 50 );
    DateRange	    t2( when, 50 );

    TEST( t1.compare( t2 ) == 0 );
    TEST( t1 == t2 );

    t2.dur( 49 );

    TEST( t1.compare( t2 ) >  0 );
    TEST( t1 > t2 );

    TEST( t2.compare( t1 ) <  0 );
    TEST( t2 < t1 );

    t2.dur( 50 );
    t2.timet( when - 1 );
    TEST( t1.compare( t2 ) > 0 );
    TEST( t1 > t2 );

    TEST( t2.compare( t1 ) < 0 );
    TEST( t2 < t1 );
  }

  {
    // getBinSize( void ) const
    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    const DateRange tw( when, 30 );

    TEST( tw.getBinSize() == (sizeof( time_t ) * 2 ) );

  }

  {
    // write( ostream & ) const
    // read( istream & )

    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    const DateRange tw( when, 30 );
    DateRange	    tr( 0, 0 );

    std::stringstream tStrm;

    std::streampos gpos = tStrm.tellg();
    std::streampos ppos = tStrm.tellp();

#ifdef AIX
    ppos = 0;
    gpos = 0;
#endif

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
    TEST( tr.dur() == tw.dur() );
  }

  {
    // toStream( ostream & ) const
    // operator <<( ostream &, const DateTime & )

    std::stringstream tStrm;

    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    const DateRange  t( when, 30 );

    t.toStream( tStrm );
    tStrm << t;
  }

  {
    // good( void ) const
    // error( void ) const
    // getClassName( void ) const
    // getVersion( void ) const
    // getVersion( bool ) const

    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    const DateRange  t( when, 30 );

    TEST( t.good() );
    TEST( t.error() != 0 );
  }

  {
    // ::compare( const DateRange &, const DateRange & )

    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    const DateRange t1( when, 50 );
    DateRange	    t2( when, 50 );

    TEST( compare( t1, t2 ) == 0 );

    t2.dur( 49 );
    TEST( compare( t1, t2 ) >  0 );
    TEST( compare( t2, t1 ) <  0 );

    t2.dur( 50 );
    t2.timet( when - 1 );
    TEST( compare( t1, t2 ) > 0 );
    TEST( compare( t2, t1 ) < 0 );
  }
  return( verify.is_valid() );
}

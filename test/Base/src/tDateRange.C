#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <HeapBinStream.hh>
#include <DateRange.hh>
#include <DateTimeUtils.hh>
#include <functional>
#include <strstream>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <HBinStrm.hh>
#include <DateRg.hh>
#include <functional>
#include <strstream>
#endif


bool
tDateRange( LibTest & tester )
{
  {
    // DateRange( time_t, time_t )
    // getDur( void ) const
    
    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    time_t  dur  = SecPerDay;

    DateRange t( when, dur );

    TEST( t.getTimeT() == when );
    TEST( t.getDur() == dur );
  }

  {
    // DateRange( const DateTime &, time_t )

    const DateTime	dt( 699342350 );

    time_t	dur = SecPerDay;

    DateRange	t( dt, dur );

    TEST( t.getTimeT() == dt.getTimeT() );
    TEST( t.getDur() == dur );
  }

  {
    // DateRange( const DateTime &, const DateTime & )

    time_t	when = 699342350;
    time_t	dur  = SecPerDay;

    const DateTime  start( when );
    const DateTime  stop( when + dur );

    DateRange	t( start, stop );

    TEST( t.getTimeT() == when );
    TEST( t.getDur() == dur );
  }

  {
    // setDur( time_t newDur )

    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)
    time_t  dur  = SecPerDay;

    DateRange t( when, dur );

    TEST( t.setDur( 60 ) == dur );
    TEST( t.getDur() == 60 );
  }

  {
    // getSecoOfDay( void ) const

    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)
    const DateRange t( when, 10 );

    TEST( t.getSecOfDay() == 20750 );
  }
    
  {
    // secIn( const DateRange & ) const
    
    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)
    time_t  dur  = SecPerDay;

    DateRange	t( when, dur );
    DateRange	r( when - 120, 60 );

    TEST( t.secIn( r ) == 0 );

    r.setDur( 120 );
    TEST( t.secIn( r ) == 0 );
    
    r.setDur( 125 );
    TEST( t.secIn( r ) == 5 );

    r.setDur( 120 + dur );
    TEST( t.secIn( r ) == dur );

    r.setDur( 120 + dur + 5 );
    TEST( t.secIn( r ) == dur );

    r.set( when );
    TEST( t.secIn( r ) == dur );

    r.setDur( dur );
    TEST( t.secIn( r ) == dur );

    r.setDur( 20 );
    TEST( t.secIn( r ) == 20 );

    t.set( when + dur );
    TEST( t.secIn( r ) == 0 );

    t.set( when + dur + 5 );
    TEST( t.secIn( r ) == 0 );
  }

  {
    // startsIn( const DateRange & ) const
    
    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)
    time_t  dur  = SecPerDay;

    DateRange	t( when, dur );
    DateRange	r( when - 120, 60 );

    TEST( t.startsIn( r ) == 0 );

    r.set( when - 30 );
    TEST( t.startsIn( r ) == 0 );
    
    r.set( when );
    TEST( t.startsIn( r ) == 60 );

    r.set( when + 60 );
    TEST( t.startsIn( r ) == 60 );

    r.set( when + dur - 30 );
    TEST( t.startsIn( r ) == 30 );

    r.set( when + dur );
    TEST( t.startsIn( r ) == 0 );

    r.set( when + dur + 5 );
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
    
    t2.setDur( 49 );

    TEST( t1.compare( t2 ) >  0 );
    TEST( t1 > t2 );
    
    TEST( t2.compare( t1 ) <  0 );
    TEST( t2 < t1 );
    
    t2.setDur( 50 );
    t2.setTimeT( when - 1 );
    TEST( t1.compare( t2 ) > 0 );
    TEST( t1 > t2 );
    
    TEST( t2.compare( t1 ) < 0 );
    TEST( t2 < t1 );
  }

  {
    // getBinSize( void ) const
    // write( BinStream & ) const
    // read( BinStream & )
    
    HeapBinStream tStrm;
    
    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    const DateRange tw( when, 30 );
    DateRange	    tr( 0, 0 );

    TEST( tw.getBinSize() == (sizeof( time_t ) * 2 ) );

    tw.write( tStrm );
    tr.read( tStrm );

    TEST( tr == tw );
    TEST( tr.getTimeT() == tw.getTimeT() );
    TEST( tr.getDur() == tw.getDur() );
  }

  {
    // BinStream::write( const BinObject & );
    // BinStream::read( BinObject );
    
    HeapBinStream tStrm;
    
    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    const DateRange tw( when, 30 );
    DateRange	    tr( 0, 0 );

    tStrm.write( tw );
    tStrm.read( tr );

    TEST( tr == tw );
    TEST( tr.getTimeT() == tw.getTimeT() );
    TEST( tr.getDur() == tw.getDur() );
  }

  {
    // write( ostream & ) const
    // read( istream & )
    
    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    const DateRange tw( when, 30 );
    DateRange	    tr( 0, 0 );
    
    strstream tStrm;

    streampos gpos = tStrm.tellg();
    streampos ppos = tStrm.tellp();

#ifdef AIX
    ppos = 0;
    gpos = 0;
#endif
    
    TEST( ppos == 0 );
    TEST( gpos == 0 );
    
    tw.write( tStrm );
    ppos += tw.getBinSize();
    TEST( ppos == tStrm.tellp() );

    tr.read( tStrm );
    gpos += tr.getBinSize();
    TEST( gpos == tStrm.tellg() );
    TEST( tr == tw );
    TEST( tr.getTimeT() == tw.getTimeT() );
    TEST( tr.getDur() == tw.getDur() );
  }

  {
    // toStream( ostream & ) const
    // operator <<( ostream &, const DateTime & )

    strstream tStrm;
    
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
    TEST( t.getClassName() != 0 );
    TEST( t.getVersion() != 0 );
    TEST( t.getVersion( false ) != 0 );

  }

  {
    // dumpInfo( ostream &, const char *, bool ) const
    // version

    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    const DateRange  t( when, 30 );

    tester.getDump() << '\n' << t.getClassName() << " toStream:\n";
    t.toStream( tester.getDump() );
    tester.getDump() << '\n' << t.getClassName() << " dumpInfo:\n";
    t.dumpInfo( tester.getDump(), " -> ", true );
    tester.getDump() << '\n' << t.getClassName() << " version:\n";
    tester.getDump() << t.version;
    
    tester.getDump() << '\n' << tester.getCurrentTestName();
    
  }
  
  {
    // ::compare( const DateRange &, const DateRange & )
    
    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    const DateRange t1( when, 50 );
    DateRange	    t2( when, 50 );

    TEST( compare( t1, t2 ) == 0 );

    t2.setDur( 49 );
    TEST( compare( t1, t2 ) >  0 );    
    TEST( compare( t2, t1 ) <  0 );
    
    t2.setDur( 50 );
    t2.setTimeT( when - 1 );
    TEST( compare( t1, t2 ) > 0 );    
    TEST( compare( t2, t1 ) < 0 );
  }
  return( true );
}

    

     
    

    
    
      
    

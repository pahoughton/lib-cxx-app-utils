#include <LibTest.hh>
#include <DateRange.hh>

#include <strstream>

bool
tDateRange( LibTest & test )
{
  {
    // DateRange( time_t, time_t )
    // getDur( void ) const
    
    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    time_t  dur  = SecPerDay;

    DateRange t( when, dur );

    test( t.getTimeT() == when );
    test( t.getDur() == dur );
  }

  {
    // DateRange( const DateTime &, time_t )

    const DateTime	dt( 699342350 );

    time_t	dur = SecPerDay;

    DateRange	t( dt, dur );

    test( t.getTimeT() == dt.getTimeT() );
    test( t.getDur() == dur );
  }

  {
    // DateRange( const DateTime &, const DateTime & )

    time_t	when = 699342350;
    time_t	dur  = SecPerDay;

    const DateTime  start( when );
    const DateTime  stop( when + dur );

    DateRange	t( start, stop );

    test( t.getTimeT() == when );
    test( t.getDur() == dur );
  }

  {
    // setDur( time_t newDur )

    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)
    time_t  dur  = SecPerDay;

    DateRange t( when, dur );

    test( t.setDur( 60 ) == dur );
    test( t.getDur() == 60 );
  }

  {
    // getSecoOfDay( void ) const

    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)
    const DateRange t( when, 10 );

    test( t.getSecOfDay() == 20750 );
  }
    
  {
    // secIn( const DateRange & ) const
    
    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)
    time_t  dur  = SecPerDay;

    DateRange	t( when, dur );
    DateRange	r( when - 120, 60 );

    test( t.secIn( r ) == 0 );

    r.setDur( 120 );
    test( t.secIn( r ) == 0 );
    
    r.setDur( 125 );
    test( t.secIn( r ) == 5 );

    r.setDur( 120 + dur );
    test( t.secIn( r ) == dur );

    r.setDur( 120 + dur + 5 );
    test( t.secIn( r ) == dur );

    r.set( when );
    test( t.secIn( r ) == dur );

    r.setDur( dur );
    test( t.secIn( r ) == dur );

    r.setDur( 20 );
    test( t.secIn( r ) == 20 );

    t.set( when + dur );
    test( t.secIn( r ) == 0 );

    t.set( when + dur + 5 );
    test( t.secIn( r ) == 0 );
  }

  {
    // startsIn( const DateRange & ) const
    
    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)
    time_t  dur  = SecPerDay;

    DateRange	t( when, dur );
    DateRange	r( when - 120, 60 );

    test( t.startsIn( r ) == 0 );

    r.set( when - 30 );
    test( t.startsIn( r ) == 0 );
    
    r.set( when );
    test( t.startsIn( r ) == 60 );

    r.set( when + 60 );
    test( t.startsIn( r ) == 60 );

    r.set( when + dur - 30 );
    test( t.startsIn( r ) == 30 );

    r.set( when + dur );
    test( t.startsIn( r ) == 0 );

    r.set( when + dur + 5 );
    test( t.startsIn( r ) == 0 );
  }

  {
    // getStreamSize( void ) const
    // write( ostream & ) const
    // read( istream & )
    
    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    const DateRange tout( when, 30 );
    DateRange	    tin( 0, 0 );
    
    strstream testStream;

    streampos gpos = testStream.tellg();
    streampos ppos = testStream.tellp();

#ifdef AIX
    ppos = 0;
    gpos = 0;
#endif
    
    test( ppos == 0 );
    test( gpos == 0 );
    
    tout.write( testStream );
    ppos += tout.getStreamSize();
    test( ppos == testStream.tellp() );

    tin.read( testStream );
    gpos += tin.getStreamSize();
    test( gpos == testStream.tellg() );
    test( tin.getTimeT() == tout.getTimeT() );
    test( tin.getDur() == tout.getDur() );
  }

  {
    // compare( const DateRange & );
    // operator == ( const DateRange & )
    // operator <  ( const DateRange & )
    // operator >  ( const DateRange & )
    
    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    const DateRange t1( when, 50 );
    DateRange	    t2( when, 50 );

    test( t1.compare( t2 ) == 0 );
    test( t1 == t2 );
    
    t2.setDur( 49 );

    test( t1.compare( t2 ) >  0 );
    test( t1 > t2 );
    
    test( t2.compare( t1 ) <  0 );
    test( t2 < t1 );
    
    t2.setDur( 50 );
    t2.setTimeT( when - 1 );
    test( t1.compare( t2 ) > 0 );
    test( t1 > t2 );
    
    test( t2.compare( t1 ) < 0 );
    test( t2 < t1 );
  }

  {
    // good( void ) const
    // error( void ) const
    // getClassName( void ) const
    // toStream( ostream & ) const
    // dumpInfo( ostream & ) const
    // const char * version[]

    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    const DateRange  t( when, 30 );

    test( t.good() );
    test( t.error() != 0 );
    test( t.getClassName() != 0 );

    strstream  stream;

    t.toStream( stream );
    t.dumpInfo( stream );

    test( t.version != 0 );
  }

  {
    // operator <<( ostream &, const DateTime & )

    strstream tStream;
    
    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    const DateRange  t( when, 30 );

    tStream << t;
  }

  {
    // ::compare( const DateRange &, const DateRange & )
    
    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    const DateRange t1( when, 50 );
    DateRange	    t2( when, 50 );

    test( compare( t1, t2 ) == 0 );

    t2.setDur( 49 );
    test( compare( t1, t2 ) >  0 );    
    test( compare( t2, t1 ) <  0 );
    
    t2.setDur( 50 );
    t2.setTimeT( when - 1 );
    test( compare( t1, t2 ) > 0 );    
    test( compare( t2, t1 ) < 0 );
  }
  return( true );
}

    

     
    

    
    
      
    

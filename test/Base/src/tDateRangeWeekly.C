#include <LibTest.hh>
#include <DateRangeWeekly.hh>

#include <strstream>

bool
tDateRangeWeekly( LibTest & test )
{
  {
    // DateRangeWeekly( short, time_t, time_t )
    // getSecOfDay( void ) const
    // getDayOfWeek( void ) const
    // getStart( void ) const
    // getDur( void ) const

    const DateRangeWeekly t( Friday, 6 * SecPerHour, 30 );

    test( t.getSecOfDay() == (6 * SecPerHour) );
    test( t.getDayOfWeek() == Friday );
    test( t.getStart() == ( (Friday * SecPerDay) + (6 * SecPerHour ) ) );
    test( t.getDur() == 30 );
    
  }

  {
    // secIn( const DateRange & ) const;
    
    const DateRangeWeekly t( Friday, 6 * SecPerHour, 30 );

    time_t  when = 699321600;	    // is 2/29/92 00:00:00 (gmt) (Sat)

    DateRange	r( when, 60 );

    test( t.secIn( r ) == 0 );

    r.setDur( SecPerDay );
    test( t.secIn( r ) == 0 );
    
    r.set( when + (SecPerDay * 6) );
    r.setDur( (6 * SecPerHour) + 15 );
    test( t.secIn( r ) == 15 );

    r.set( when + (SecPerDay * 6) + (6 * SecPerHour) + 15 );
    r.setDur( 120 );
    test( t.secIn( r ) == 15 );

    r.set( when + (SecPerDay * 6 ) + ( 7 * SecPerHour ) );
    test( t.secIn( r ) == 0 );

    r.setDur( SecPerDay );
    test( t.secIn( r ) == 0 );

    r.set( when );
    r.setDur( (SecPerDay * 6) + ( 8 * SecPerHour ) );
    test( t.secIn( r ) == 30 );

    r.setDur( 14 * SecPerDay );
    test( t.secIn( r ) == 60 );
  }

  {
    // startsIn( const DateRange & ) const
    
    DateRangeWeekly  t( Friday, 6 * SecPerHour, 30 );

    test( t.getDur() == 30 );
    
    time_t  when = 699321600;	    // is 2/29/92 00:00:00 (gmt) (sat)

    DateRange	r( when, SecPerDay );

    test( t.startsIn( r ) == 0 );

    r.set( when + (SecPerDay * 6) + ( 6 * SecPerHour ) );
    r.setDur( 10 );

    test( t.startsIn( r ) == 10 );

    r.set( when + (SecPerDay * 6 ) + ( 6 * SecPerHour ) + 15 );
    r.setDur( ( 15 * SecPerDay ) + 60 );

    test( t.startsIn( r ) == 75 );
  }

  {
    // setStart( void )

    time_t  startTime = (6 * SecPerHour);
    time_t  duration  = 30;
    
    DateRangeWeekly  t( Wednesday, startTime, duration );

    test( t.setStart( 5 * SecPerHour ) == (Wednesday * SecPerDay) + startTime );
    test( t.getStart() == ( 5 * SecPerHour ) );
  }

  {
    // getStreamSize( void ) const
    // write( ostream & ) const
    // read( istream & )
    
    const DateRangeWeekly   tout( Friday, 6 * SecPerHour, 30 );
    DateRangeWeekly	    tin( Sunday, 0, 0 );
    
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
    test( tin.getStart() == tout.getStart() );
    test( tin.getDur() == tout.getDur() );
  }
    
  {
    // compare( const DateRangeDaily & ) const
    // operator == ( const DateRangeDaily & )
    // operator <  ( const DateRangeDaily & )
    // operator >  ( const DateRangeDaily & )

    time_t  startTime = (6 * SecPerHour);
    time_t  duration  = 30;
        
    const DateRangeWeekly    t1( Friday, startTime, duration );
    DateRangeWeekly	     t2( Friday, startTime, duration );

    test( t1.compare( t2 ) == 0 );
    test( t1 == t2 );
    
    t2.setDur( duration - 1 );

    test( t1.compare( t2 ) >  0 );
    test( t1 > t2 );
    
    test( t2.compare( t1 ) <  0 );
    test( t2 < t1 );
    
    t2.setDur( duration );
    t2.setStart( (Friday * SecPerDay) + startTime - 1 );
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
    // version

    const DateRangeWeekly  t( Friday, 6 * SecPerHour, 30 );

    test( t.good() );
    test( t.error() != 0 );
    test( t.getClassName() != 0 );

    strstream tStream;

    t.toStream( tStream );
    t.dumpInfo( tStream );

    test( t.version != 0 );
  }

  {
    // ::compare( const DateRangeDaily &, const DateRangeDaily & )
    
    time_t  startTime = (6 * SecPerHour);
    time_t  duration  = 30;
        
    const DateRangeDaily    t1( startTime, duration );
    DateRangeDaily	    t2( startTime, duration );

    test( compare( t1, t2 ) == 0 );
    test( t1 == t2 );
    
    t2.setDur( duration - 1 );

    test( compare( t1, t2 ) >  0 );
    test( t1 > t2 );
    
    test( compare( t2, t1 ) <  0 );
    test( t2 < t1 );
    
    t2.setDur( duration );
    t2.setStart( startTime - 1 );
    test( compare( t1, t2 ) > 0 );
    test( t1 > t2 );
    
    test( compare( t2, t1 ) < 0 );
    test( t2 < t1 );
  }
  
  {
    // operator << ( ostream &, const DateRangeDaily & )

    const DateRangeDaily  t( 6 * SecPerHour, 30 );

    strstream tStream;

    tStream << t;
  }
  return( true );
}

    
    
    
    
    

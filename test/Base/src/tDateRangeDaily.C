#include <TestConfig.hh>
#include <LibTest.hh>
#include <DateRangeDaily.hh>
#include <DateTimeUtils.hh>
#include <functional>
#if defined( Hpux10 )
#include <utility>
#endif
#include <strstream.h>

bool
tDateRangeDaily( LibTest & tester )
{
  {
    // DateRangeDaily( time_t, time_t )
    // getSecOfDay( void ) const
    // getDayOfWeek( void ) const
    // getStart( void ) const

    time_t  startTime = (6 * SecPerHour);
    time_t  duration  = 30;
    
    const DateRangeDaily  t( startTime, duration );

    TEST( t.getSecOfDay() == startTime );
    TEST( t.getDayOfWeek() == -1 );
    TEST( t.getStart() == startTime );
    TEST( t.getDur() == duration );
  }

  {
    // in( const DateTime & ) const
    DateRangeDaily  t( 8 * SecPerHour, (17 - 8) * SecPerHour );

    tester.getOutput() << t << endl;
    
    {
      DateTime	dt( 2003, 5, 12, 6, 00, 00 );
      TESTR( dt.getString(), ! t.in( dt ) );
    }
    {
      DateTime	dt( 2003, 5, 12, 7, 59, 59 );
      TESTR( dt.getString(), ! t.in( dt ) );
    }
    {
      DateTime	dt( 2003, 5, 12, 8, 00, 00 );
      TESTR( dt.getString(), t.in( dt ) );
    }
    {
      DateTime	dt( 2003, 5, 12, 8, 00, 01 );
      TESTR( dt.getString(), t.in( dt ) );
    }
    {
      DateTime	dt( 2003, 5, 12, 12, 00, 00 );
      TESTR( dt.getString(), t.in( dt ) );
    }
    {
      DateTime	dt( 2003, 5, 12, 16, 59, 59 );
      TESTR( dt.getString(), t.in( dt ) );
    }
    {
      DateTime	dt( 2003, 5, 12, 17, 00, 00 );
      TESTR( dt.getString(), t.in( dt ) );
    }
    {
      DateTime	dt( 2003, 5, 12, 17, 00, 01 );
      TESTR( dt.getString(), ! t.in( dt ) );
    }
    {
      DateTime	dt( 2003, 5, 12, 20, 00, 00 );
      TESTR( dt.getString(), ! t.in( dt ) );
    }

    {
      DateTime	dt( 2003, 5, 11, 17, 00, 00 );
      TESTR( dt.getString(), t.in( dt ) );
    }
    {
      DateTime	dt( 2003, 5, 11, 17, 00, 01 );
      TESTR( dt.getString(), ! t.in( dt ) );
    }
  }
    
  {
    // secIn( const DateRange & ) const
    
    DateRangeDaily  t( 6 * SecPerHour, 30 );

    TEST( t.getDur() == 30 );
    
    time_t  when = 699321600;	    // is 2/29/92 00:00:00 (gmt)

    DateRange	r( when, 60 );
    
    TEST( t.secIn( r ) == 0 );

    r.setDur( (6 * SecPerHour) + 15 );

    TEST( t.secIn( r ) == 15 );

    r.set( when + (6 * SecPerHour) + 15 );
    r.setDur( 120 );
    TEST( t.secIn( r ) == 15 );

    r.set( when + ( 7 * SecPerHour ) );
    TEST( t.secIn( r ) == 0 );

    r.setDur( SecPerDay );
    TEST( t.secIn( r ) == 30 );

    r.setDur( SecPerDay * 2 );
    TEST( t.secIn( r ) == 60 );
  }

  {
    // startsIn( const DateRange & ) const
    
    DateRangeDaily  t( 6 * SecPerHour, 30 );

    TEST( t.getDur() == 30 );
    
    time_t  when = 699321600;	    // is 2/29/92 00:00:00 (gmt)

    DateRange	r( when, 60 );

    TEST( t.startsIn( r ) == 0 );

    r.setDur( SecPerDay );
    TEST( t.startsIn( r ) == 0 );

    r.set( when + ( 6 * SecPerHour ) );
    r.setDur( 10 );

    TEST( t.startsIn( r ) == 10 );

    r.set( when + ( 6 * SecPerHour ) + 15 );
    r.setDur( ( 2 * SecPerDay ) + 60 );

    TEST( t.startsIn( r ) == 75 );
  }

  {
    // setStart( void )

    time_t  startTime = (6 * SecPerHour);
    time_t  duration  = 30;
    
    DateRangeDaily  t( startTime, duration );

    TEST( t.setStart( 5 * SecPerHour ) == startTime );
    TEST( t.getStart() == ( 5 * SecPerHour ) );
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
    
    t2.setDur( duration - 1 );

    TEST( t1.compare( t2 ) >  0 );
    TEST( t1 > t2 );
    
    TEST( t2.compare( t1 ) <  0 );
    TEST( t2 < t1 );
    
    t2.setDur( duration );
    t2.setStart( startTime - 1 );
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
    ppos += (streampos) tw.getBinSize();
    TEST( ppos == tStrm.tellp() );
      
    tr.read( tStrm );
    gpos += (streampos) tr.getBinSize();
    TEST( gpos == tStrm.tellg() );
    TEST( tr == tw );
    TEST( tr.getTimeT() == tw.getTimeT() );
    TEST( tr.getStart() == tw.getStart() );
    TEST( tr.getDur() == tw.getDur() );
  }

  {
    // toStream( ostream & dest ) const
    // operator << ( ostream &, const DateRangeDaily & )

    const DateRangeDaily  t( 6 * SecPerHour, 30 );

    strstream tStream;
    t.toStream( tStream );
    tStream << t;
  }

  {
    // good( void ) const
    // error( void ) const
    // getClassName( void ) const
    // getVersion( void ) const
    // getVersion( bool ) const
    
    const DateRangeDaily  t( 6 * SecPerHour, 30 );

    TEST( t.good() );
    TEST( t.error() != 0 );
    TEST( t.getClassName() != 0 );
    TEST( t.getVersion() != 0 );
    TEST( t.getVersion( true ) != 0 );
    
  }

  {
    // dumpInfo( ostream &, const char *, bool ) const
    // version

    const DateRangeDaily  t( 6 * SecPerHour, 30 );

    tester.getDump() << '\n' << t.getClassName() << " toStream:\n";
    t.toStream( tester.getDump() );
    tester.getDump() << '\n' << t.getClassName() << " dumpInfo:\n";
    t.dumpInfo( tester.getDump(), " -> ", true );
    tester.getDump() << '\n' << t.getClassName() << " version:\n";
    tester.getDump() << t.version;
    
    tester.getDump() << '\n' << tester.getCurrentTestName();
    
  }  
  
  {
    // ::compare( const DateRangeDaily &, const DateRangeDaily & )
    
    time_t  startTime = (6 * SecPerHour);
    time_t  duration  = 30;
        
    const DateRangeDaily    t1( startTime, duration );
    DateRangeDaily	    t2( startTime, duration );

    TEST( compare( t1, t2 ) == 0 );
    TEST( t1 == t2 );
    
    t2.setDur( duration - 1 );

    TEST( compare( t1, t2 ) >  0 );
    TEST( t1 > t2 );
    
    TEST( compare( t2, t1 ) <  0 );
    TEST( t2 < t1 );
    
    t2.setDur( duration );
    t2.setStart( startTime - 1 );
    TEST( compare( t1, t2 ) > 0 );
    TEST( t1 > t2 );
    
    TEST( compare( t2, t1 ) < 0 );
    TEST( t2 < t1 );
  }
  
  return( true );
}

    
    
    
    

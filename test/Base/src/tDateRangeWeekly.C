#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <DateRangeWeekly.hh>
#include <DateTimeUtils.hh>
#include <functional>
#include <strstream.h>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <HBinStrm.hh>
#include <DateRgWk.hh>
#include <functional>
#include <strstream>
#endif


bool
tDateRangeWeekly( LibTest & tester )
{
  {
    // DateRangeWeekly( short, time_t, time_t )
    // getSecOfDay( void ) const
    // getDayOfWeek( void ) const
    // getStart( void ) const
    // getDur( void ) const

    const DateRangeWeekly t( Friday, 6 * SecPerHour, 30 );

    TEST( t.getSecOfDay() == (6 * SecPerHour) );
    TEST( t.getDayOfWeek() == Friday );
    TEST( t.getStart() == ( (Friday * SecPerDay) + (6 * SecPerHour ) ) );
    TEST( t.getDur() == 30 );
    
  }

  {
    // secIn( const DateRange & ) const;
    
    const DateRangeWeekly t( Friday, 6 * SecPerHour, 30 );

    time_t  when = 699321600;	    // is 2/29/92 00:00:00 (gmt) (Sat)

    DateRange	r( when, 60 );

    TEST( t.secIn( r ) == 0 );

    r.setDur( SecPerDay );
    TEST( t.secIn( r ) == 0 );
    
    r.set( when + (SecPerDay * 6) );
    r.setDur( (6 * SecPerHour) + 15 );
    TEST( t.secIn( r ) == 15 );

    r.set( when + (SecPerDay * 6) + (6 * SecPerHour) + 15 );
    r.setDur( 120 );
    TEST( t.secIn( r ) == 15 );

    r.set( when + (SecPerDay * 6 ) + ( 7 * SecPerHour ) );
    TEST( t.secIn( r ) == 0 );

    r.setDur( SecPerDay );
    TEST( t.secIn( r ) == 0 );

    r.set( when );
    r.setDur( (SecPerDay * 6) + ( 8 * SecPerHour ) );
    TEST( t.secIn( r ) == 30 );

    r.setDur( 14 * SecPerDay );
    TEST( t.secIn( r ) == 60 );
  }

  {
    // startsIn( const DateRange & ) const
    
    DateRangeWeekly  t( Friday, 6 * SecPerHour, 30 );

    TEST( t.getDur() == 30 );
    
    time_t  when = 699321600;	    // is 2/29/92 00:00:00 (gmt) (sat)

    DateRange	r( when, SecPerDay );

    TEST( t.startsIn( r ) == 0 );

    r.set( when + (SecPerDay * 6) + ( 6 * SecPerHour ) );
    r.setDur( 10 );

    TEST( t.startsIn( r ) == 10 );

    r.set( when + (SecPerDay * 6 ) + ( 6 * SecPerHour ) + 15 );
    r.setDur( ( 15 * SecPerDay ) + 60 );

    TEST( t.startsIn( r ) == 75 );
  }

  {
    // setStart( void )

    time_t  startTime = (6 * SecPerHour);
    time_t  duration  = 30;
    
    DateRangeWeekly  t( Wednesday, startTime, duration );

    TEST( t.setStart( 5 * SecPerHour ) == (Wednesday * SecPerDay) + startTime );
    TEST( t.getStart() == ( 5 * SecPerHour ) );
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

    TEST( t1.compare( t2 ) == 0 );
    TEST( t1 == t2 );
    
    t2.setDur( duration - 1 );

    TEST( t1.compare( t2 ) >  0 );
    TEST( t1 > t2 );
    
    TEST( t2.compare( t1 ) <  0 );
    TEST( t2 < t1 );
    
    t2.setDur( duration );
    t2.setStart( (Friday * SecPerDay) + startTime - 1 );
    TEST( t1.compare( t2 ) > 0 );
    TEST( t1 > t2 );
    
    TEST( t2.compare( t1 ) < 0 );
    TEST( t2 < t1 );
  }

  {
    // getBinSize( void ) const
    
    const DateRangeWeekly   tw( Friday, 6 * SecPerHour, 30 );

    TEST( tw.getBinSize() == (sizeof( time_t ) * 2 ) );        
  }
  
  {
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
    
    TEST( ppos == 0 );
    TEST( gpos == 0 );
    
    tout.write( testStream );
    ppos += tout.getBinSize();
    TEST( ppos == testStream.tellp() );
      
    tin.read( testStream );
    gpos += tin.getBinSize();
    TEST( gpos == testStream.tellg() );
    TEST( tin.getTimeT() == tout.getTimeT() );
    TEST( tin.getStart() == tout.getStart() );
    TEST( tin.getDur() == tout.getDur() );
  }
    
  {
    // toStream( ostream & ) const
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
    
    const DateRangeWeekly  t( Friday, 6 * SecPerHour, 30 );

    TEST( t.good() );
    TEST( t.error() != 0 );
    TEST( t.getClassName() != 0 );
    TEST( t.getVersion() != 0 );
    TEST( t.getVersion( false ) != 0 );

  }

  {
    // dumpInfo( ostream &, const char *, bool ) const
    // version

    const DateRangeWeekly  t( Friday, 6 * SecPerHour, 30 );

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

    
    
    
    
    

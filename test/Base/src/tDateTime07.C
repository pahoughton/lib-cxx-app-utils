#include <TestConfig.hh>
#include <LibTest.hh>
#include <DateTime.hh>
#include <functional>
#if defined( Hpux10 )
#include <utility>
#endif
#include <strstream.h>
#include <cstring>

bool
tDateTime07( LibTest & tester )
{
  {
    // getBinSize( void )
    
    const char * d1String = "02/17/95 11:30:30";

    DateTime	d1w( d1String );

    TEST( d1w.getBinSize() == sizeof( time_t ) );
    
  }
  
  {
    // read( istream & )
    // write( ostream & )
    // toStream( ostream & ) const
    // operator << ( ostream &, const DateTime & )
    
    const char * d1String = "02/17/95 11:30:30";

    DateTime	d1( d1String );
    DateTime	d2( "2/17/95 11:30:31" );
    DateTime	dl( d1String );

    dl.setTimeZone();
    
    time_t  d1time = d1;
    time_t  dltime = dl;
    
    TEST( (time_t)d1 == d1.getTimeT() );
    TEST( d1time == dltime );
    TEST( d1 != d2 );
    TEST( ! strcmp( d1String, d1 ) );
    
    strstream testStream;

    streampos gpos = testStream.tellg();
    streampos ppos = testStream.tellp();

#ifdef AIX
    ppos = 0;
    gpos = 0;
#endif
    
    TEST( ppos == 0 );
    TEST( gpos == 0 );
    
    d1.write( testStream );
    ppos += (streampos) d1.getBinSize();
    TEST( ppos == testStream.tellp() );
      
    d2.write( testStream );
    ppos += (streampos) d2.getBinSize();
    TEST( ppos == testStream.tellp() );
      
    dl.write( testStream );
    ppos += (streampos) d1.getBinSize();
    TEST( ppos == testStream.tellp() );

    d1.toStream( testStream );
    testStream << d1;
    
    DateTime dr;

    dr.read( testStream );
    gpos += (streampos) dr.getBinSize();
    TEST( testStream.gcount() == dr.getBinSize() );
    TEST( gpos == testStream.tellg() );
    TEST( dr == d1 );

    dr.read( testStream );
    gpos += (streampos) dr.getBinSize();
    TEST( testStream.gcount() == dr.getBinSize() );
    TEST( gpos == testStream.tellg() );
    TEST( dr == d2 );

    dr.read( testStream );
    gpos += (streampos) dr.getBinSize();
    TEST( testStream.gcount() == dr.getBinSize() );
    TEST( gpos == testStream.tellg() );
    TEST( dr == dl );

    char dStr[ 50 ];

    testStream.read( dStr, strlen( d1String ) );
    TEST( testStream.gcount() == strlen( d1String ) );
    dStr[ strlen( d1String ) ] = 0;

    TEST( ! strcmp( dStr, d1String ) );
    
    testStream.read( dStr, strlen( d1String ) );
    TEST( testStream.gcount() == strlen( d1String ) );
    dStr[ strlen( d1String ) ] = 0;

    TEST( ! strcmp( dStr, d1String ) );
    
  }

  return( true );
}


#include <LibTest.hh>
#include <DateTime.hh>

#include <strstream.h>

bool
tDateTime07( LibTest & test )
{
  {
    // operator <<( ostream &, const DateTime & )
    // read( istream & )
    // write( ostream & )
    // getStreamSize( void ) const
    
    const char * d1String = "02/17/95 11:30:30";

    DateTime	d1( d1String );
    DateTime	d2( "2/17/95 11:30:31" );
    DateTime	dl( d1String );

    dl.setTimeZone();
    
    time_t  d1time = d1;
    time_t  dltime = dl;
    
    test( (time_t)d1 == d1.getTimeT() );
    test( d1time == dltime );
    test( d1 != d2 );
    test( ! strcmp( d1String, d1 ) );
    
    strstream testStream;

    streampos gpos = testStream.tellg();
    streampos ppos = testStream.tellp();

#ifdef AIX
    ppos = 0;
    gpos = 0;
#endif
    
    test( ppos == 0 );
    test( gpos == 0 );
    
    d1.write( testStream );
    ppos += d1.getStreamSize();
    test( ppos == testStream.tellp() );
      
    d2.write( testStream );
    ppos += d2.getStreamSize();
    test( ppos == testStream.tellp() );
      
    dl.write( testStream );
    ppos += d1.getStreamSize();
    test( ppos == testStream.tellp() );
      
    testStream << d1;
    
    DateTime dr;

    dr.read( testStream );
    gpos += dr.getStreamSize();
    test( testStream.gcount() == dr.getStreamSize() );
    test( gpos == testStream.tellg() );
    test( dr == d1 );

    dr.read( testStream );
    gpos += dr.getStreamSize();
    test( testStream.gcount() == dr.getStreamSize() );
    test( gpos == testStream.tellg() );
    test( dr == d2 );

    dr.read( testStream );
    gpos += dr.getStreamSize();
    test( testStream.gcount() == dr.getStreamSize() );
    test( gpos == testStream.tellg() );
    test( dr == dl );

    char dStr[ 50 ];

    testStream.read( dStr, strlen( d1String ) );
    test( testStream.gcount() == strlen( d1String ) );
    dStr[ strlen( d1String ) ] = 0;

    test( ! strcmp( dStr, d1String ) );
    
  }

  return( true );
}


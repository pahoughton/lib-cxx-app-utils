#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <HeapBinStream.hh>
#include <DateTime.hh>
#include <strstream>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <HBinStrm.hh>
#include <DateTime.hh>
#include <strstream>
#endif

bool
tDateTime07( LibTest & tester )
{
  {
    // getBinSize( void )
    // write( BinStream & dest ) const;
    // read( BinStream & src )
    
    HeapBinStream tStrm( 4096 );
    
    const char * d1String = "02/17/95 11:30:30";

    DateTime	d1w( d1String );
    DateTime	d2w( "2/17/95 11:30:31" );
    DateTime	dlw( d1String );

    dlw.setTimeZone();
    
    time_t  d1time = d1w;
    time_t  dltime = dlw;

    TEST( d1w.getBinSize() == sizeof( time_t ) );
    
    TEST( (time_t)d1w == d1w.getTimeT() );
    TEST( d1time == dltime );
    TEST( d1w != d2w );
    TEST( ! strcmp( d1String, d1w ) );
    
    d1w.write( tStrm );
    d2w.write( tStrm );
    dlw.write( tStrm );

    DateTime dr;

    dr.read( tStrm );
    TEST( dr == d1w );

    dr.read( tStrm );
    TEST( dr == d2w );

    dr.read( tStrm );
    TEST( dr == dlw );

  }
  
  {
    // BinStream::write( const BinObject & );
    // BinStream::read( BinObject );
    
    HeapBinStream tStrm;
    
    const char * d1String = "02/17/95 11:30:30";

    DateTime	d1w( d1String );
    DateTime	d2w( "2/17/95 11:30:31" );
    DateTime	dlw( d1String );

    dlw.setTimeZone();
    
    time_t  d1time = d1w;
    time_t  dltime = dlw;

    TEST( (time_t)d1w == d1w.getTimeT() );
    TEST( d1time == dltime );
    TEST( d1w != d2w );
    TEST( ! strcmp( d1String, d1w ) );
    
    tStrm.write( d1w );
    tStrm.write( d2w );
    tStrm.write( dlw );

    DateTime dr;

    tStrm.read( dr );
    TEST( dr == d1w );

    tStrm.read( dr );
    TEST( dr == d2w );

    tStrm.read( dr );
    TEST( dr == dlw );

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
    ppos += d1.getBinSize();
    TEST( ppos == testStream.tellp() );
      
    d2.write( testStream );
    ppos += d2.getBinSize();
    TEST( ppos == testStream.tellp() );
      
    dl.write( testStream );
    ppos += d1.getBinSize();
    TEST( ppos == testStream.tellp() );

    d1.toStream( testStream );
    testStream << d1;
    
    DateTime dr;

    dr.read( testStream );
    gpos += dr.getBinSize();
    TEST( testStream.gcount() == dr.getBinSize() );
    TEST( gpos == testStream.tellg() );
    TEST( dr == d1 );

    dr.read( testStream );
    gpos += dr.getBinSize();
    TEST( testStream.gcount() == dr.getBinSize() );
    TEST( gpos == testStream.tellg() );
    TEST( dr == d2 );

    dr.read( testStream );
    gpos += dr.getBinSize();
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


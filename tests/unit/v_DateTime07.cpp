// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/DateTime.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <functional>
#include <sstream>
#include <cstring>

static valid::verify verify("clue::DateTime07");
using namespace clue;

bool
v_DateTime07( void )
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

    time_t  d1time = d1;
    time_t  dltime = dl;

    TEST( (time_t)d1 == d1.timet() );
    TEST( d1time == dltime );
    TEST( d1 != d2 );
    TEST( d1.str() == d1String );

    std::stringstream testStream;

    std::streampos gpos = testStream.tellg();
    std::streampos ppos = testStream.tellp();


    TEST( ppos == 0 );
    TEST( gpos == 0 );

    d1.write( testStream );
    ppos += (std::streampos) d1.getBinSize();
    TEST( ppos == testStream.tellp() );

    d2.write( testStream );
    ppos += (std::streampos) d2.getBinSize();
    TEST( ppos == testStream.tellp() );

    dl.write( testStream );
    ppos += (std::streampos) d1.getBinSize();
    TEST( ppos == testStream.tellp() );

    d1.toStream( testStream );
    testStream << d1;

    DateTime dr;

    dr.read( testStream );
    gpos += (std::streampos) dr.getBinSize();
    TEST( testStream.gcount() == dr.getBinSize() );
    TEST( gpos == testStream.tellg() );
    TEST( dr == d1 );

    dr.read( testStream );
    gpos += (std::streampos) dr.getBinSize();
    TEST( testStream.gcount() == dr.getBinSize() );
    TEST( gpos == testStream.tellg() );
    TEST( dr == d2 );

    dr.read( testStream );
    gpos += (std::streampos) dr.getBinSize();
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
  {
    // good( void ) const
    // error( void  ) const

    DateTime  t( "7/1/95 07:03:40" );

    TEST( t.good() );
  }
  return( verify.is_valid() );
}

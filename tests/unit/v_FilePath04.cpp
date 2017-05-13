// 1995-06-15 (cc) Paul Houghton <paul4hough@gmail.com>

#include <clue/FilePath.hpp>
#include <clue/compare>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <sstream>

static valid::verify verify("clue::FilePath04");
using namespace clue;

bool
v_FilePath04( void )
{
  {
    // getBinSize( void ) const
    // write( ostream & ) const
    // read( istream & )

    const FilePath  tw( ":usr:src","libStlUtils.a", '/','.' );
    FilePath	    tr;

    std::stringstream tStrm;

    std::streampos gpos = tStrm.tellg();
    std::streampos ppos = tStrm.tellp();


    TEST( ppos == 0 );
    TEST( gpos == 0 );

    tw.write( tStrm );
    ppos += (std::streampos) tw.getBinSize();
    TEST( ppos == tStrm.tellp() );

    tr.read( tStrm );
    gpos += (std::streampos) tr.getBinSize();
    TEST( gpos == tStrm.tellg() );
    TEST( tr == tw );
  }

  {
    // toStream( ostream & ) const
    // operator << ( ostream &, const FilePath & )

    std::stringstream tStrm;
    const FilePath  t( ":usr:src","libStlUtils.a", '/','.' );

    t.toStream( tStrm );
    tStrm << t;
  }

  {
    // good( void ) const
    // error( void ) const

    const FilePath	t( ":usr:src", "test.c", ':' );

    TEST( t.good() );
    TEST( t.error() != 0 );
  }

  {
    // ::compare( const FilePath &, const FilePath & );

    const FilePath l( "dir/test.oper" );
    const FilePath re( "dir/test.oper" );
    const FilePath rl( "c/test.oper" );
    const FilePath rm( "e/test" );

    TEST( compare( l, re ) == 0 );
    TEST( compare( l, rm ) < 0 );
    TEST( compare( l, rl ) > 0 );
  }

  return( verify.is_valid() );
}

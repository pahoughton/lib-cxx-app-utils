// 1996-10-31 (cc) <paul4hough@gmail.com>

#include <clue/Str.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <fstream>
#include <sstream>
#include <cstring>
#include <iomanip>

static valid::verify verify("clue::SubStr05");
using namespace clue;

#define OutStr "This is an output test from SubStr\n"

#define TEST_DATA_DIR "data/SubStr"

bool
v_SubStr05( void )
{

  {
    // getBinSize( void )

    const Str stw( "123" OutStr "junk" );
    const SubStr tw( stw, 3, strlen( OutStr ) );

    TEST( tw.getBinSize() == (sizeof(size_t) + tw.size() ) );
  }

  {
    // write( ostream & dest ) const;
    // read( istream & src )

    const Str stw( "123" OutStr "junk" );
    const SubStr tw( stw, 3, strlen( OutStr ) );

    Str str( "123" "abc" "junk" );
    SubStr tr( str, 3, 3 );

    std::stringstream tStrm;

    tw.write( tStrm );
    tr.read( tStrm );

    TEST( tr == tw );
    TEST( str == stw );
  }

  {
    // toStream( ostream & ) const

    const char * fn = TEST_DATA_DIR "/SubStr.operator.output.01";
    std::ofstream out( fn );

    const Str t( "123" OutStr "junk" );

    t.substr( 3, strlen( OutStr ) ).toStream( out );
    out.close();

  }

  {
    // operator << ( ostream &, const Str & )

    const char * fn = TEST_DATA_DIR "/SubStr.operator.output.02";
    std::ofstream out( fn );

    Str t( "123" OutStr "junk" );

    out << t.substr( 3, strlen( OutStr ) );

    t = "substr width test";
    out.fill( '#' );
    out << '\'' <<  std::setw( 20 ) << t.substr( 0, 6 ) << '\'' << std::endl;

    out.setf( std::ios::left, std::ios::adjustfield );
    out << '\'' <<  std::setw(20) << t.substr( 0, 6 ) << '\'' <<  std::endl;

    out << '\'' <<  t.substr( 0, 6 ) << '\'' << std::endl;
    out.close();
  }

  {
    // good( void ) const
    // error( void ) const

    const Str st( "123" OutStr "junk" );
    const SubStr t( st, 3, strlen( OutStr ) );

    TEST( t.good() );
    TEST( t.error() != 0 );
  }

  return( verify.is_valid() );
}

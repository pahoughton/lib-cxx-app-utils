// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/Str.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <fstream>
#include <sstream>
#include <cstring>

static valid::verify verify("clue::Str22");
using namespace clue;

#define TEST_DATA_DIR "data/Str"

#define T1 "first part"
#define T2 "second part"
#define T3 "third part"
#define T4 "forth part"
#define T5 "fifth part"

bool
v_Str22( void )
{
  {
    // getline( istream & )

    const char * fn = TEST_DATA_DIR "/Str.getline.input";

    std::ifstream in( fn );

    TEST( in.good() );

    Str t;

    TEST( t.getline( in ).good() );
    TEST( t == "first input line" );
    TEST( t.getline( in ).good() );
    TEST( t == "last input line" );
    TEST( ! t.getline( in ).good() );
    TEST( t == "last input line" );
  }

  {
    // getDelim( istream &, const char * )

    const char * fn = TEST_DATA_DIR "/Str.getDelim.input";

    std::ifstream in( fn );

    TEST( in.good() );

    Str	t;

    TEST( t.getDelim( in, " \t\n" ).good() );
    TEST( t == "this" );
    TEST( t.getDelim( in, " \t\n" ).good() );
    TEST( t == "is" );
    TEST( t.getDelim( in, " \t\n" ).good() );
    TEST( t == "a" );
    TEST( t.getDelim( in, " \t\n" ).good() );
    TEST( t == "delimited" );
    TEST( t.getDelim( in, " \t\n" ).good() );
    TEST( t.empty() );
    TEST( t.getDelim( in, " \t\n" ).good() );
    TEST( t == "line" );
    TEST( t.getDelim( in, " \t\n" ).good() );
    TEST( t == "next" );
    TEST( t.getDelim( in, " \t\n" ).good() );
    TEST( t == "line" );
    TEST( ! t.getDelim( in, " \t\n" ).good() );
  }

  {
    // getDelim( istream &, const char *, bool )

    const char * fn = TEST_DATA_DIR "/Str.getDelim.input";

    std::ifstream in( fn );

    TEST( in.good() );

    Str t;

    TEST( t.getDelim( in, " \t\n", false ).good() );
    TEST( t == "this " );
    TEST( t.getDelim( in, " \t\n", false ).good() );
    TEST( t == "is\t" );
    TEST( t.getDelim( in, " \t\n", false ).good() );
    TEST( t == "a " );
    TEST( t.getDelim( in, " \t\n", false ).good() );
    TEST( t == "delimited\t" );
    TEST( t.getDelim( in, " \t\n", false ).good() );
    TEST( t == " " );
    TEST( t.getDelim( in, " \t\n", false ).good() );
    TEST( t == "line\n" );
    TEST( t.getDelim( in, " \t\n", false ).good() );
    TEST( t == "next " );
    TEST( t.getDelim( in, " \t\n", false ).good() );
    TEST( t == "line\n" );
    TEST( ! t.getDelim( in, " \t\n", false ).good() );
  }

  {
    // getDelim( istream &, char )

    const char * fn = TEST_DATA_DIR "/Str.getDelim.char.input";

    std::ifstream in( fn );

    TEST( in.good() );

    Str t;

    TEST( t.getDelim( in, " " ).good() );
    TEST( t == "test" );
    TEST( t.getDelim( in, " " ).good() );
    TEST( t == "char" );
    TEST( ! t.getDelim( in, " " ).good() );
    TEST( t == "delim\n" );
    TEST( ! t.getDelim( in, " " ).good() );
  }

  {
    // getDelim( istream &, char, bool )

    const char * fn = TEST_DATA_DIR "/Str.getDelim.char.input";

    std::ifstream in( fn );

    TEST( in.good() );

    Str t;

    TEST( t.getDelim( in, " ", false ).good() );
    TEST( t == "test " );
    TEST( t.getDelim( in, " ", false ).good() );
    TEST( t == "char " );
    TEST( ! t.getDelim( in, " ", false ).good() );
    TEST( t == "delim\n" );
    TEST( ! t.getDelim( in, " ", false ).good() );
  }

  {
    // getBinSize( void ) const

    Str t;

    const char * T = "the string to test";

    t = T;
    TEST( t.getBinSize() == strlen( T ) + sizeof( unsigned long ) );
  }

  {
    // write( ostream & )

    const char * fn = TEST_DATA_DIR "/Str.bin.data";

    std::ofstream out( fn );

    TEST( out.good() );

    Str t;

    t = T1;
    TEST( t.write( out ).good() );
    t = T2;
    TEST( t.write( out ).good() );
    t = T3;
    TEST( t.write( out ).good() );
    t = T4;
    TEST( t.write( out ).good() );
    t = T5;
    TEST( t.write( out ).good() );
  }

  {
    // read( istream & )

    const char * fn = TEST_DATA_DIR "/Str.bin.data";

    std::ifstream in( fn );

    TEST( in.good() );

    Str t;

    TEST( t.read( in ).good() );
    TEST( t == T1 );
    TEST( t.read( in ).good() );
    TEST( t == T2 );
    TEST( t.read( in ).good() );
    TEST( t == T3 );
    TEST( t.read( in ).good() );
    TEST( t == T4 );
    TEST( t.read( in ).good() );
    TEST( t == T5 );
  }

  {
    // toStream( ostream & ) const


    std::stringstream out;

    const Str t("This is an output test from Str\n" );
    t.toStream( out );
    TEST( out.str() == t.c_str() );
  }

  {
    // operator << ( ostream &, const Str & )

    std::stringstream out;

    const Str t("This is an output test from Str\n" );
    out <<  t;
    TEST( out.str() == t.c_str() );
  }

  {
    // operator >> ( istream &, Str & )

    const char * fn = TEST_DATA_DIR "/Str.operator.input";

    std::ifstream in( fn );

    TEST( in.good() );

    Str t;

    in >> t;
    TEST( t == "input" );
    in >> t;
    TEST( t == "string" );
  }

  {
    // good( void ) const
    // error( void ) const

    const Str t( "simple test string" );

    TEST( t.good() );
    TEST( t.error() != 0 );
  }

  return( verify.is_valid() );
}

#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <fstream>
#include <cstring>
#else
#include <TestConfig.hh>
#include <HBinStrm.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <fstream>
#include <cstring>
#endif

#define T1 "first part"
#define T2 "second part"
#define T3 "third part"
#define T4 "forth part"
#define T5 "fifth part"

bool
tStr22( LibTest & tester )
{
  {
    // getline( istream & )
    
#if !defined( STLUTILS_SHORT_FN )
    const char * fn = TEST_DATA_DIR "/Str.getline.input";
#else
    const char * fn = TEST_DATA_DIR "/strgl.in";
#endif

    ifstream in( fn );

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

#if !defined( STLUTILS_SHORT_FN )
    const char * fn = TEST_DATA_DIR "/Str.getDelim.input";
#else
    const char * fn = TEST_DATA_DIR "/strgd.in";
#endif

    ifstream in( fn );

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

#if !defined( STLUTILS_SHORT_FN )
    const char * fn = TEST_DATA_DIR "/Str.getDelim.input";
#else
    const char * fn = TEST_DATA_DIR "/strgd.in";
#endif

    ifstream in( fn );
    
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
    
#if !defined( STLUTILS_SHORT_FN )
    const char * fn = TEST_DATA_DIR "/Str.getDelim.char.input";
#else
    const char * fn = TEST_DATA_DIR "/strgdch.in";
#endif

    ifstream in( fn );

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
    
#if !defined( STLUTILS_SHORT_FN )
    const char * fn = TEST_DATA_DIR "/Str.getDelim.char.input";
#else
    const char * fn = TEST_DATA_DIR "/strgdch.in";
#endif

    ifstream in( fn );

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

#if !defined( STLUTILS_SHORT_FN )
    const char * fn = TEST_DATA_DIR "/Str.bin.data";
#else
    const char * fn = TEST_DATA_DIR "/strbin.dat";
#endif

    ofstream out( fn );

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

#if !defined( STLUTILS_SHORT_FN )
    const char * fn = TEST_DATA_DIR "/Str.bin.data";
#else
    const char * fn = TEST_DATA_DIR "/strbin.dat";
#endif

    ifstream in( fn );

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
    
#if !defined( STLUTILS_SHORT_FN )
    const char * fn = TEST_DATA_DIR "/Str.operator.output";
#else
    const char * fn = TEST_DATA_DIR "/stropout";
#endif

    ofstream out( fn );

    TEST( out.good() );

    const Str t("This is an output test from Str\n" );
    t.toStream( out );
    out.close();
    tester.file( __FILE__, __LINE__, fn );
  }

  {
    // operator << ( ostream &, const Str & )
    
#if !defined( STLUTILS_SHORT_FN )
    const char * fn = TEST_DATA_DIR "/Str.operator.output";
#else
    const char * fn = TEST_DATA_DIR "/stropout";
#endif

    ofstream out( fn );

    TEST( out.good() );

    Str t("This is an output test from Str\n" );
    out << t;
    out.close();
    tester.file( __FILE__, __LINE__, fn );
  }

  {
    // operator >> ( istream &, Str & )
    
#if !defined( STLUTILS_SHORT_FN )
    const char * fn = TEST_DATA_DIR "/Str.operator.input";
#else
    const char * fn = TEST_DATA_DIR "/strop.in";
#endif

    ifstream in( fn );

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
    // getClassName( void  ) const
    
    const Str t( "simple test string" );

    TEST( t.good() );
    TEST( t.error() != 0 );
    TEST( t.getClassName() != 0 );
    TEST( t.getVersion() != 0 );
  }

  {
    // dumpInfo( ostream &, const char *, bool ) const
    // version
    
    const Str t("This is an output test from Str\n" );

    tester.getDump() << '\n' << t.getClassName() << " toStream:\n";
    t.toStream( tester.getDump() );
    tester.getDump() << '\n' << t.getClassName() << " dumpInfo:\n";
    t.dumpInfo( tester.getDump(), " -> ", true );
    tester.getDump() << '\n' << t.getClassName() << " version:\n";
    tester.getDump() << t.version;
    
    tester.getDump() << '\n' << tester.getCurrentTestName();
    
  }
  
  return( true );
}


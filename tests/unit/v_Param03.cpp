// 1999-11-07 (cc) Paul Houghton - (paul4hough@gmail.com)

#include "clue/Param.hpp"
#include "clue/Clue.hpp"
#include "clue/compare"

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#define TEST_DATA_DIR "data/Param"

static valid::verify verify("clue::Param");
using namespace clue;

#define TEST_ARGFILE TEST_DATA_DIR "/param-03.args"
#define TEST_LOGFILE TEST_DATA_DIR "/param-03.log"

static const char * argv01[] =
{
  "test/test",
  "-argfile="	TEST_ARGFILE,
  "-log-file",	TEST_LOGFILE,
  "-gen-argfile",
  "-log-level",	"TEST | INFO",
  "-log-mode",  "ios::out",
  "-log-max",	"10240",
  "-log-trim",	"1024",
  "-string",	"test string",
  "-str",	"test str",
  "-int",	"-123",
  "-uint",	"123",
  "-short",	"-456",
  "-ushort=456",
  "-long",	"-789",
  "-ulong",	"789",
  "-double",	"10.10",
  "-bool",	"yes",
  "-flag",
  "-timet",	"7/15/95 08:15:15",
  "-datetime",	"8/1/95 06:00:10",
  0
};

bool
v_Param03( void )
{
  remove( TEST_LOGFILE );
  errno = 0;

  {
#if defined( STLUTILS_TEST )
    extern int Stlutils_Prama_Gen_NoDate;

    Stlutils_Prama_Gen_NoDate = 1;
#endif

    remove( TEST_ARGFILE );

    int argc = ArraySize( argv01 ) - 1;

    Param   t( argc, argv01, "ParamTest 03" );
    Param * App = &t;

    TEST( t.parseArgs() );
    TEST( t.good() );
    // tester.getDump() << t;

    t.log().setTimeStamp( false );
    t.log().setLevelStamp( false );

    TEST( t.log().getOutput() == ( LogLevel::Test | LogLevel::Info ) );

    TEST( t.log().getMaxSize() == 10240 );
    TEST( t.log().getTrimSize() == 1024 );

    ALog( LogLevel::Test ) << t;

    {
      for( int l = 0; l < 500; l++ )
	ALog( LogLevel::Info ) << "info message: " << l
			       << " to test log trimming\n";
    }

    char * string = (char *)"init";
    TEST( t.argStr( string,
		    "STRING",
		    "argString test args",
		    "long desc",
		    true,
		    "string" ) );
    TEST( compare( string, "test string" ) == 0 );

    Str str( "init" );
    TEST( t.argStr( str,
		    "STRING",
		    "argStr test args",
		    "long desc",
		    true,
		    "str" ) );
    TEST( compare( str.c_str(), "test str" ) == 0 );

    int i = 0;
    TEST( t.argInt( i,
		    "num",
		    "argInt test args",
		    "long desc",
		    true,
		    "int" ) );
    TEST( i == -123 );

    unsigned int ui = 0;
    TEST( t.argUInt( ui,
		     "UNSIGNED",
		     "argInt unsigned test args",
		     "long desc",
		     true,
		     "uint" ) );
    TEST( ui == 123 );

    short s = 0;
    TEST( t.argShort( s,
		      "SHORT",
		      "argShort test args",
		      "long desc",
		      true,
		      "short" ) );
    TEST( s == -456 );

    unsigned short us = 0;
    TEST( t.argUShort( us,
		       "UNSIGNED SHORT",
		       "argShort unsigned test args",
		       "long desc",
		       true,
		       "ushort" ) );
    TEST( us == 456 );

    long l = 0;
    TEST( t.argLong( l,
		     "LONG",
		     "argLong test args",
		     "long desc",
		     true,
		     "long" ) );
    TEST( l == -789 );

    unsigned long ul = 0;
    TEST( t.argULong( ul,
		      "UNSIGNED LONG",
		      "argLong unsigned test args",
		      "long desc",
		      true,
		      "ulong" ) );
    TEST( ul == 789 );

    double d = 0;
    TEST( t.argDouble( d,
		       "DOUBLE",
		       "argDouble test args",
		       "long desc",
		       false,
		       "double" ) );
    TEST( d == 10.10 );

    bool b = false;
    TEST( t.argBool( b,
		     "BOOL",
		     "argBool test args",
		     "long desc",
		     true,
		     "bool" ) );
    TEST( b == true );

    bool f = false;
    TEST( t.argFlag( f,
		     "argFlag test args",
		     "long desc",
		     "flag" ) );
    TEST( f == true );

    time_t tt = 0;
    DateTime tval( "7/15/95 08:15:15" );
    TEST( t.argDateTime( tt,
			 "DATETIME",
			 "argDateTime time_t test args",
			 "long desc",
			 true,
			 "timet" ) );
    TEST( tt == tval.timet() );

    DateTime dt( "9/1/95 06:00:10" );
    DateTime dtval( "8/1/95 06:00:10" );
    TEST( t.argDateTime( dt,
			 "DATETEIME",
			 "argDateTime DateTime test args",
			 "long desc",
			 true,
			 "datetime" ) );
    TEST( dt == dtval );

    ALog( LogLevel::Test ) << t;

    TEST( t.count() == 0 );

    TEST( ! t.help( false ) );
    TEST( t.good() );
  }

  return( true );
}

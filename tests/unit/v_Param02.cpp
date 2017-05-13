// 1996-11-17 (cc) Paul Houghton - (paul4hough@gmail.com)

#include "clue/Param.hpp"
#include "clue/Clue.hpp"
#include "clue/compare"

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#define TEST_DATA_DIR "data/Param"

static valid::verify verify("clue::Param");
using namespace clue;


static const char * argv01[] =
{
  "test/test",
  0
};

static const char * argv02[] =
{
  "test/test",
  "-log-file",	TEST_DATA_DIR "/param.log.01",
  "-help",
  "-log-level",	"TEST | INFO",
  "-log-max",	"10240",
  "-log-trim",	"1024",
  "-string",	"test string",
  "-str",	"test str",
  "-int",	"-123",
  "-uint",	"123",
  "-short",	"-456",
  "-ushort",	"456",
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
v_Param02( void )
{
  remove( TEST_DATA_DIR "/param.log.01" );

  {
    // Param( int &, char * [], const char * )
    // appName( void ) const
    // appFullName( void ) const
    // arg( size_t )
    // count( void ) const
    // env( const char * ) const
    // log( void )
    // log( LogLevel::Level )

    int argc = ArraySize( argv01 ) - 1;

    Param   t( argc, argv01, "ParamTest 01" );
    t.parseArgs();

    std::cout << t.appName() << ":" << t.appFullName() << std::endl;

    TEST( compare( t.appName(), "test" ) == 0 );
    TEST( compare( t.appFullName(), "test/test" ) == 0 );
    TEST( t.arg(0) == 0 );
    TEST( t.count() == 0 );
    TEST( compare( t.env( "USER" ), TEST_USER ) == 0 );

    t.log().setTimeStamp( false );
    t.log().setLevelStamp( false );

    TEST( t.log().getCurrent() == LogLevel::Error );
    TEST( t.log( LogLevel::Test ).getCurrent() == LogLevel::Test );
  }

  {
    // help( void ) const
    // ALog( LogLevel::Level )
    // argString( char * &, const char *, const char * )
    // argStr( Str &, const char *, const char * )
    // argInt( int &, const char *, const char * )
    // argInt( unsigned int &, const char *, const char * )
    // argShort( short &, const char *, const char * )
    // argShort( unsigned short &, const char *, const char * )
    // argLong( long &, const char *, const char * )
    // argLong( unsigned long &, const char *, const char * )
    // argDouble( double &, const char *, const char * )
    // argBool( bool &, const char *, const char * )
    // argFlag( flag &, const char *, const char * )
    // argDateTime( time_t &, const char *, const char * )
    // argDateTime( DateTime &, const char *, const char * )

    int argc = ArraySize( argv02 ) - 1;

    Param   t( argc, argv02, "ParamTest 02" );
    Param * App = &t;
    t.parseArgs();

    t.log().setTimeStamp( false );
    t.log().setLevelStamp( false );

    TEST( t.help(false) );
    TEST( t.log().getOutput() == ( LogLevel::Test | LogLevel::Info ) );

    // ALog( LogLevel::Test ) << t;

    if( false ) {
      for( int l = 0; l < 500; l++ )
	ALog( LogLevel::Info ) << "info message: " << l
			       << " to test log trimming\n";
    }

    char  * string = 0;
    TEST( t.argStr( string, "TVAL", "sdesc", "ldesc", false, "string" ) );
    TEST( compare( string, "test string" ) == 0 );

    Str str( "init" );
    TEST( t.argStr( str, "TVAL", "sdesc", "ldesc", false,  "str" ) );
    TEST( compare( str, "test str" ) == 0 );

    int i = 0;
    TEST( t.argInt( i, "TVAL", "sdesc", "ldesc", false,  "int" ) );
    TEST( i == -123 );

    unsigned int ui = 0;
    TEST( t.argUInt( ui, "TVAL", "sdesc", "ldesc", false,  "uint" ) );
    TEST( ui == 123 );

    short s = 0;
    TEST( t.argShort( s, "TVAL", "sdesc", "ldesc", false,  "short" ) );
    TEST( s == -456 );

    unsigned short us = 0;
    TEST( t.argUShort( us,  "TVAL", "sdesc", "ldesc", false,  "ushort" ) );
    TEST( us == 456 );

    long l = 0;
    TEST( t.argLong( l, "TVAL", "sdesc", "ldesc", false,  "long" ) );
    TEST( l == -789 );

    unsigned long ul = 0;
    TEST( t.argULong( ul, "TVAL", "sdesc", "ldesc", false,  "ulong" ) );
    TEST( ul == 789 );

    double d = 0;
    TEST( t.argDouble( d, "TVAL", "sdesc", "ldesc", false,  "double" ) );
    TEST( d == 10.10 );

    bool b = false;
    TEST( t.argBool( b, "TVAL", "sdesc", "ldesc", false,  "bool" ) );
    TEST( b == true );

    bool f = false;
    TEST( t.argFlag( f, "sdesc", "ldesc",  "flag" ) );
    TEST( f == true );

    time_t tt = 0;
    DateTime tval( "7/15/95 08:15:15" );
    TEST( t.argDateTime( tt, "TVAL", "sdesc", "ldesc", false, "timet" ) );
    TEST( tt == tval.timet() );

    DateTime dt( "9/1/95 06:00:10" );
    DateTime dtval( "8/1/95 06:00:10" );
    TEST( t.argDateTime( dt, "TVAL", "sdesc", "ldesc", false, "datetime" ) );
    TEST( dt == dtval );

    // ALog( LogLevel::Test ) << t;

    TEST( t.count() == 0 );
  }

  return( verify.is_valid() );
}

// 1996-11-17 (cc) Paul Houghton - (paul4hough@gmail.com)

#include "clue/Param.hpp"
#include "clue/Clue.hpp"
#include "clue/compare"

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::Param");
using namespace clue;

#define APP_VER		"Test Param Ver: 01.01.01"
#define APP_NAME_01	"TestParam_01"
#define APP_FULLNAME_01	"test/src/Base/" APP_NAME_01

static const char * Argv_01[] =
{
  APP_FULLNAME_01,
};

#define APP_NAME_02	"TestParam_01"
#define APP_FULLNAME_02	"test/src/Base/" APP_NAME_01

static const char * Argv_02[] =
{
  APP_FULLNAME_02,
  "arg  1",
  "arg  2",
  "arg  3",
  "1234",
  "10.10"
};

static const char * Argv_03[] =
{
  "test/src/Base/TestParam_03",
  "-help",
  "-log",   "../data/param_03.log", // TEST_DATA_DIR "/param_03.log",
  "-loglevel",	    "test | INFO | Warn",
  "-logfilter",	    "param",
  "-logtee",
  "-logtime",	    "false",
  "-logstamplevel", "false",
  "-logloc",	    "false",
  "-logmax",	    "4096",
  "-logtrim",	    "2048",
  "arg  1",
  "arg  2",
  "arg  3",
  "1234",
  "10.10"
};


bool
v_Param01( void )
{
  int	argc_01( ArraySize( Argv_01 ) );
  int	argc_02( ArraySize( Argv_02 ) );
  int	argc_03( ArraySize( Argv_03 ) );

  const char ** argv_01( new const char * [ argc_01 ] );
  const char ** argv_02( new const char * [ argc_02 ] );
  const char ** argv_03( new const char * [ argc_03 ] );


  {
    for( size_t a = 0; a < ArraySize( Argv_01 ); ++ a )
      argv_01[a] = strdup( Argv_01[a] );
  }

  {
    for( size_t a = 0; a < ArraySize( Argv_02 ); ++ a )
      argv_02[a] = strdup( Argv_02[a] );
  }

  {
    for( size_t a = 0; a < ArraySize( Argv_03 ); ++ a )
      argv_03[a] = strdup( Argv_03[a] );
  }

  {
    // Param( int, char * [] )
    // appName( void ) const;
    // appFullName( void ) const;

    Param t( argc_01, argv_01 );

    t.parseArgs();

    TEST( compare( t.appName(), APP_NAME_01 ) == 0 );
    TEST( compare( t.appFullName(), APP_FULLNAME_01 ) == 0 );
  }

  {
    // Param( int, char * [], const char * )
    // appVersion( void ) const;
    // count( void ) const;
    // begin( void ) const;
    // end( void ) const;
    // beginAll( void ) const
    // endAll( void ) const;

    Param t( argc_02, argv_02, APP_VER );

    t.parseArgs();

    TEST( compare( t.appVersion(), APP_VER ) == 0 );
    TEST( (int)t.count() == argc_02  -1  );

    size_t  count = 1;

    {
      for( Param::Args::const_iterator them = t.begin();
	   them != t.end();
	   ++them, ++count )
	{
	  TEST( (*them) == argv_02[count] );
	}

      TEST( (int)count == argc_02 );
    }

    count = 0;
    {
      for( Param::Args::const_iterator them = t.beginAll();
	   them != t.endAll();
	   ++them, ++count )
	{
	  TEST( (*them) == argv_02[count] );
	}

      TEST( (int)count == argc_02 );
    }
  }

  {
    // Param( int, char * [], const char * )
    // arg( void )
    // arg( size_t );
    // argLong( size_t );
    // argDouble( size_t );

    Param t( argc_02, argv_02, APP_VER );

    t.parseArgs();

    TEST( compare( t.arg(), argv_02[1] ) == 0 );
    TEST( compare( t.arg(1), argv_02[2] ) == 0 );

    TEST( t.argLong( 3 )   == 1234 );
    TEST( t.argDouble( 4 ) == 10.10 );
  }

  {
    Param t( argc_03, argv_03, APP_VER );

    t.parseArgs();
  }

  return( verify.is_valid() );
}

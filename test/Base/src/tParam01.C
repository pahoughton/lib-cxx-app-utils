#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Param.hh>
#include <Compare.hh>
#include <Clue.hh>
#include <cstdio>
#else
#include <TestCfg.hh>
#include <LibTest.hh>
#include <Param.hh>
#include <Compare.hh>
#include <Clue.hh>
#include <cstdio>
#endif



char * argv01[] =
{
  "test/test",
  0
};

char * argv02[] =
{
  "test/test",
  "-log",	"data/param.log.01",
  "-help",
  "-loglevel",	"TEST | INFO",
  "-logmax",	"10240",
  "-logtrim",	"1024",
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
tParam01( LibTest & tester )
{
  remove( "data/param.log.01" );
  
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

    TEST( compare( t.appName(), "test" ) == 0 );
    TEST( compare( t.appFullName(), "test/test" ) == 0 );
    TEST( compare( t.arg(0), "test/test" ) == 0 );
    TEST( t.arg(1) == 0 );
    TEST( t.count() == 1 );
    TEST( compare( t.env( "USER" ), "houghton" ) == 0 );
    
    t.log().setTimeStamp( false );
    t.log().setLevelStamp( false );
    
    TEST( t.log().getCurrent() == LogLevel::ERROR );
    TEST( t.log( LogLevel::TEST ).getCurrent() == LogLevel::TEST );
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
    
    t.log().setTimeStamp( false );
    t.log().setLevelStamp( false );

    TEST( t.help() );
    TEST( t.log().getOutput() == ( LogLevel::TEST | LogLevel::INFO ) );

    ALog( LogLevel::TEST ) << t;

    {
      for( int l = 0; l < 500; l++ )
	ALog( LogLevel::INFO ) << "info message: " << l
			       << " to test log trimming\n";
    }

    char * string = "init";
    TEST( t.argString( string, "argString test args", "string" ) );
    TEST( compare( string, "test string" ) == 0 );
    
    Str str( "init" );
    TEST( t.argStr( str, "argStr test args", "str" ) );
    TEST( compare( str, "test str" ) == 0 );

    int i = 0;
    TEST( t.argInt( i, "argInt test args", "int" ) );
    TEST( i == -123 );

    unsigned int ui = 0;
    TEST( t.argInt( ui, "argInt unsigned test args", "uint" ) );
    TEST( ui == 123 );

    short s = 0;
    TEST( t.argShort( s, "argShort test args", "short" ) );
    TEST( s == -456 );

    unsigned short us = 0;
    TEST( t.argShort( us, "argShort unsigned test args", "ushort" ) );
    TEST( us == 456 );

    long l = 0;
    TEST( t.argLong( l, "argLong test args", "long" ) );
    TEST( l == -789 );

    unsigned long ul = 0;
    TEST( t.argLong( ul, "argLong unsigned test args", "ulong" ) );
    TEST( ul == 789 );

    double d = 0;
    TEST( t.argDouble( d, "argDouble test args", "double" ) );
    TEST( d == 10.10 );

    bool b = false;
    TEST( t.argBool( b, "argBool test args", "bool" ) );
    TEST( b == true );

    bool f = false;
    TEST( t.argFlag( f, "argFlag test args", "flag" ) );
    TEST( f == true );

    time_t tt = 0;
    DateTime tval( "7/15/95 08:15:15" );
    TEST( t.argDateTime( tt, "argDateTime time_t test args", "timet" ) );
    TEST( tt == tval.getTimeT() );

    DateTime dt( "9/1/95 06:00:10" );
    DateTime dtval( "8/1/95 06:00:10" );
    TEST( t.argDateTime( dt, "argDateTime DateTime test args", "datetime" ) );
    TEST( dt == dtval );

    ALog( LogLevel::TEST ) << t;

    TEST( t.count() == 1 );
  }
  
      
  return( true );
}

    

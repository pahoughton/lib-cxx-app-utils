#include <LibTest.hh>
#include <Param.hh>

#include <Compare.hh>
#include <Clue.hh>

#include <cstdio>

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
tParam01( LibTest & test )
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

    test( compare( t.appName(), "test" ) == 0 );
    test( compare( t.appFullName(), "test/test" ) == 0 );
    test( compare( t.arg(0), "test/test" ) == 0 );
    test( t.arg(1) == 0 );
    test( t.count() == 1 );
    test( compare( t.env( "USER" ), "houghton" ) == 0 );
    
    t.log().setTimeStamp( false );
    t.log().setLevelStamp( false );
    
    test( t.log().getCurrent() == LogLevel::ERROR );
    test( t.log( LogLevel::TEST ).getCurrent() == LogLevel::TEST );
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

    test( t.help() );
    test( t.log().getOutput() == ( LogLevel::TEST | LogLevel::INFO ) );

    ALog( LogLevel::TEST ) << t;

    {
      for( int l = 0; l < 500; l++ )
	ALog( LogLevel::INFO ) << "info message: " << l
			       << " to test log trimming\n";
    }

    char * string = "init";
    test( t.argString( string, "argString test args", "string" ) );
    test( compare( string, "test string" ) == 0 );
    
    Str str( "init" );
    test( t.argStr( str, "argStr test args", "str" ) );
    test( compare( str, "test str" ) == 0 );

    int i = 0;
    test( t.argInt( i, "argInt test args", "int" ) );
    test( i == -123 );

    unsigned int ui = 0;
    test( t.argInt( ui, "argInt unsigned test args", "uint" ) );
    test( ui == 123 );

    short s = 0;
    test( t.argShort( s, "argShort test args", "short" ) );
    test( s == -456 );

    unsigned short us = 0;
    test( t.argShort( us, "argShort unsigned test args", "ushort" ) );
    test( us == 456 );

    long l = 0;
    test( t.argLong( l, "argLong test args", "long" ) );
    test( l == -789 );

    unsigned long ul = 0;
    test( t.argLong( ul, "argLong unsigned test args", "ulong" ) );
    test( ul == 789 );

    double d = 0;
    test( t.argDouble( d, "argDouble test args", "double" ) );
    test( d == 10.10 );

    bool b = false;
    test( t.argBool( b, "argBool test args", "bool" ) );
    test( b == true );

    bool f = false;
    test( t.argFlag( f, "argFlag test args", "flag" ) );
    test( f == true );

    time_t tt = 0;
    DateTime tval( "7/15/95 08:15:15" );
    test( t.argDateTime( tt, "argDateTime time_t test args", "timet" ) );
    test( tt == tval.getTimeT() );

    DateTime dt( "9/1/95 06:00:10" );
    DateTime dtval( "8/1/95 06:00:10" );
    test( t.argDateTime( dt, "argDateTime DateTime test args", "datetime" ) );
    test( dt == dtval );

    ALog( LogLevel::TEST ) << t;

    test( t.count() == 1 );
  }
  
      
  return( true );
}

    

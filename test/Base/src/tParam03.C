//
// File:        tParam03.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tParam03
//  
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     11/07/99 08:10
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include <TestConfig.hh>
#include <LibTest.hh>
#include <Param.hh>
#include <Compare.hh>
#include <StlUtilsMisc.hh>
#include <cstdio>


#define TEST_ARGFILE TEST_DATA_DIR "/param-03.args"
#define TEST_LOGFILE TEST_DATA_DIR "/param-03.log"
char * argv01[] =
{
  "test/test",
  "-argfile="	TEST_ARGFILE,	
  "-log-file",	TEST_LOGFILE,
  "-gen-argfile",
  "-log-level",	"TEST | INFO",
  "-log-mode",  "ios::in | ios::out",
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
tParam03( LibTest & tester )
{
  {
#if defined( STLUTILS_TEST )
    extern int Stlutils_Prama_Gen_NoDate;

    Stlutils_Prama_Gen_NoDate = 1;
#endif
    
    remove( TEST_ARGFILE );
    
    int argc = ArraySize( argv01 ) - 1;
    
    Param   t( argc, argv01, "ParamTest 03" );
    Param * App = &t;

    if( ! t.parseArgs() )
      {
	TESTR( "parseArgs", false );
	tester.getError() << '\n' << t << endl;
      }
    
    if( ! t.good() )
      {
	TESTR( "Param error", false );
	tester.getError() << '\n' << t << endl;
      }
    
    t.log().setTimeStamp( false );
    t.log().setLevelStamp( false );

    TESTR( LogLevel::getLevelNames( t.log().getOutput() ),
	   t.log().getOutput() == ( LogLevel::Test | LogLevel::Info ) );

    TEST( t.log().getMaxSize() == 10240 );
    TEST( t.log().getTrimSize() == 1024 );
    
    ALog( LogLevel::Test ) << t;

    {
      for( int l = 0; l < 500; l++ )
	ALog( LogLevel::Info ) << "info message: " << l
			       << " to test log trimming\n";
    }

    char * string = "init";
    TEST( t.argStr( string, "argString test args", "string" ) );
    TEST( compare( string, "test string" ) == 0 );

    Str str( "init" );
    TEST( t.argStr( str, "argStr test args", "str" ) );
    TEST( compare( str.c_str(), "test str" ) == 0 );

    int i = 0;
    TEST( t.argInt( i, "argInt test args", "int" ) );
    TEST( i == -123 );

    unsigned int ui = 0;
    TEST( t.argUInt( ui, "argInt unsigned test args", "uint" ) );
    TEST( ui == 123 );

    short s = 0;
    TEST( t.argShort( s, "argShort test args", "short" ) );
    TEST( s == -456 );

    unsigned short us = 0;
    TEST( t.argUShort( us, "argShort unsigned test args", "ushort" ) );
    TEST( us == 456 );

    long l = 0;
    TEST( t.argLong( l, "argLong test args", "long" ) );
    TEST( l == -789 );

    unsigned long ul = 0;
    TEST( t.argULong( ul, "argLong unsigned test args", "ulong" ) );
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
    TESTR( t.error(),
	   t.argDateTime( tt, "argDateTime time_t test args", "timet" ) );
    TESTR( ctime(&tt),
	   tt == tval.getTimeT() );

    DateTime dt( "9/1/95 06:00:10" );
    DateTime dtval( "8/1/95 06:00:10" );
    TEST( t.argDateTime( dt, "argDateTime DateTime test args", "datetime" ) );
    TEST( dt == dtval );

    ALog( LogLevel::Test ) << t;

    tester.getDump() << '\n' << t << endl;
    
    TEST( t.count() == 0 );

    TEST( ! t.help( false ) );
    
  }

  {
#if defined( STLUTILS_TEST )
    // This test doesn't work because when the exp file
    // is check in the Keywords get expanded.
    //
    // tester.file( __FILE__, __LINE__, TEST_ARGFILE );
#endif
    tester.file( __FILE__, __LINE__, TEST_LOGFILE );
  }
  
  return( true );
}

// Revision Log:
//
// $Log$
// Revision 4.2  1999/11/09 22:10:40  houghton
// Bug-Fix: can't test gen args file.
//
// Revision 4.1  1999/11/09 11:11:33  houghton
// Initial Version.
//
//

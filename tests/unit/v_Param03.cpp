//
// File:        tParam03.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tParam03
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
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

const char * argv01[] =
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
tParam03( LibTest & tester )
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

    if( ! t.parseArgs() )
      {
	tester.getError() << '\n' << t << endl;
	TESTR( "parseArgs", false );
      }

    // tester.getDump() << t;
    
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
    TESTR( t.error(),
	   t.argDateTime( tt,
			  "DATETIME",
			  "argDateTime time_t test args",
			  "long desc",
			  true,
			  "timet" ) );
    TESTR( ctime(&tt),
	   tt == tval.getTimeT() );

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

    tester.getDump() << '\n' << t << endl;
    
    TEST( t.count() == 0 );

    TEST( ! t.help( false ) );

    if( ! t.good() ) {
      tester.getDump() << '\n' << t.error() << endl;
      TEST( false );
    }
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
// Revision 6.2  2011/12/30 23:57:46  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:51  houghton
// Changed to version 6
//
// Revision 5.4  2001/07/26 19:28:56  houghton
// *** empty log message ***
//
// Revision 5.3  2000/05/30 15:12:49  houghton
// Changed: remove TEST_LOGFILE before running test.
//
// Revision 5.2  2000/05/25 17:11:50  houghton
// Port: Sun CC 5.0.
//
// Revision 5.1  2000/05/25 10:33:29  houghton
// Changed Version Num to 5
//
// Revision 4.2  1999/11/09 22:10:40  houghton
// Bug-Fix: can't test gen args file.
//
// Revision 4.1  1999/11/09 11:11:33  houghton
// Initial Version.
//
//

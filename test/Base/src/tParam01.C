//
// File:        tParam01.C
// Project:	Clue
// Desc:        
//
//  Test for the follwing Param methods.
//
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     11/17/96 06:52
//
// Revision History: (See end of file for Revision Log)
//
// $Id$


#include "TestConfig.hh"
#include "LibTest.hh"
#include "Param.hh"
#include "Compare.hh"
#include "ClueUtils.hh"

#define APP_VER		"Test Param Ver: 01.01.01"

#define APP_NAME_01	"TestParam_01"
#define APP_FULLNAME_01	"test/src/Base/" APP_NAME_01

static char * argv_01[] =
{
  APP_FULLNAME_01,
};

#define APP_NAME_02	"TestParam_01"
#define APP_FULLNAME_02	"test/src/Base/" APP_NAME_01

static char * argv_02[] =
{
  APP_FULLNAME_02,
  "arg  1",
  "arg  2",
  "arg  3",
  "1234",
  "10.10"
};

static char * argv_03[] =
{
  "test/src/Base/TestParam_03",
  "-help",
  "-log",   TEST_DATA_DIR "/param_03.log",
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
tParam01( LibTest & tester )
{
  {
    // Param( int, char * [] )
    // appName( void ) const;
    // appFullName( void ) const;
    
    const Param t( ArraySize( argv_01 ), argv_01 );

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
    
    const Param t( ArraySize( argv_02 ), argv_02, APP_VER );

    TEST( compare( t.appVersion(), APP_VER ) == 0 );
    TEST( t.count() == ArraySize( argv_02 ) );
    
    size_t  count = 0;
    
    for( Param::Args::const_iterator them = t.begin();
	 them != t.end();
	 ++them, ++count )
      {
	TEST( (*them) == argv_02[count] );
      }
    
    TEST( count == ArraySize( argv_02 ) );

    count = 0;
    
    for( Param::Args::const_iterator them = t.beginAll();
	 them != t.endAll();
	 ++them, ++count )
      {
	TEST( (*them) == argv_02[count] );
      }
    
    TEST( count == ArraySize( argv_02 ) );

  }

  {
    // Param( int, char * [], const char * )
    // arg( void )
    // arg( size_t );
    // argLong( size_t );
    // argDouble( size_t );
    
    Param t( ArraySize( argv_02 ), argv_02, APP_VER );

    TEST( compare( t.arg(), argv_02[1] ) == 0 );
    TEST( compare( t.arg(2), argv_02[2] ) == 0 );

    TEST( t.argLong( 4 )   == 1234 );
    TEST( t.argDouble( 5 ) == 10.10 );
  }

  return( true );
}
	 

    
    
//
// $Log$
// Revision 3.2  1996/11/19 12:36:10  houghton
// Major-rework.
//
//

//
// File:        tParam01.C
// Project:	StlUtils
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
#include "StlUtilsMisc.hh"

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
tParam01( LibTest & tester )
{
  int	argc_01( ArraySize( Argv_01 ) );
  int	argc_02( ArraySize( Argv_02 ) );
  int	argc_03( ArraySize( Argv_03 ) );
  
  char ** argv_01( new char * [ argc_01 ] );
  char ** argv_02( new char * [ argc_02 ] );
  char ** argv_03( new char * [ argc_03 ] );
  
  
  {
    for( size_t a = 0; a < ArraySize( Argv_01 ); ++ a )
      argv_01[a] = strdup( Argv_01[a] );
  }
	
  {
    for( size_t a = 0; a < ArraySize( Argv_02 ); ++ a )
      argv_01[a] = strdup( Argv_02[a] );
  }
	
  {
    for( size_t a = 0; a < ArraySize( Argv_03 ); ++ a )
      argv_01[a] = strdup( Argv_03[a] );
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
	  TESTR( (*them), (*them) == argv_02[count] );
	}
      
      TEST( (int)count == argc_02 );
    }
    
    count = 0;
    {
      for( Param::Args::const_iterator them = t.beginAll();
	   them != t.endAll();
	   ++them, ++count )
	{
	  TESTR( (*them), (*them) == argv_02[count] );
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
    
    TESTR( t.arg(), compare( t.arg(), argv_02[1] ) == 0 );
    TESTR( t.arg(2), compare( t.arg(1), argv_02[2] ) == 0 );

    TEST( t.argLong( 3 )   == 1234 );
    TEST( t.argDouble( 4 ) == 10.10 );
  }

  {
    Param t( argc_03, argv_03, APP_VER );

    t.parseArgs();
  }
    
    
  return( true );
}
	 

    
    
//
// $Log$
// Revision 4.3  1998/04/02 14:19:26  houghton
// Cleanup and eliminate warnings.
//
// Revision 4.2  1997/12/20 16:13:30  houghton
// Changed test to match lastest version.
//
// Revision 4.1  1997/09/17 15:14:28  houghton
// Changed to Version 4
//
// Revision 3.8  1997/09/17 15:11:08  houghton
// Renamed StlUtilsUtils.hh to StlUtilsMisc.hh
//
// Revision 3.7  1997/09/17 11:09:55  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.6  1997/07/18 21:49:33  houghton
// Port(Sun5): the linker had problems with this. FIXME (need a better
//     solution to the problem)
//
// Revision 3.5  1997/03/21 15:41:46  houghton
// Changed new style Param requires a call to parse.
//
// Revision 3.4  1997/03/03 19:10:52  houghton
// Changed for port to AIX41.
//
// Revision 3.3  1997/03/03 14:39:38  houghton
// Removed support for RW Tools++ & rpm.
// Bug had to add and ifdef for linux - gcc has a bug in const Class *
//     operator ++ handling.
//
// Revision 3.2  1996/11/19 12:36:10  houghton
// Major-rework.
//
//

//
// File:        tLog04.C
// Project:	StlUtils
// Desc:        
//
//  Test the following Log methods:
//
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     11/12/96 06:12
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#include "TestConfig.hh"
#include "LibTest.hh"
#include "Log.hh"
#include "FileStat.hh"
#include <fstream>
#include <cstdio>


bool
tLog04( LibTest & tester )
{
  
  {
    // level( const char * )

    const char * TestFn = TEST_DATA_DIR "/log.10";
    
    {
      Log	t( TestFn, LogLevel::All, ios::out, 0644,
		   true, false, false  );
      
      t.level( "Error" )   << "test Error" << '\n';
      t.level( "Err" )     << "test Err" << '\n';
      t.level( "Warning" ) << "test Warning" << '\n';
      t.level( "Warn" )    << "test Warn" << '\n';
      t.level( "App1" )    << "test App1" << '\n';
      t.level( "App2" )    << "test App2" << '\n';
      t.level( "App3" )    << "test App3" << '\n';
      t.level( "App4" )    << "test App4" << '\n';
      t.level( "App5" )    << "test App5" << '\n';
      t.level( "App6" )    << "test App6" << '\n';
      t.level( "Lib1" )    << "test Lib1" << '\n';
      t.level( "Lib2" )    << "test Lib2" << '\n';
      t.level( "Lib3" )    << "test Lib3" << '\n';
      t.level( "Lib4" )    << "test Lib4" << '\n';
      t.level( "Info" )    << "test Info" << '\n';
      t.level( "Test" )    << "test Test" << '\n';
      t.level( "Debug" )   << "test Debug" << '\n';
      t.level( "Funct" )   << "test Funct" << '\n';
    }
    
    tester.file( __FILE__, __LINE__, TestFn );
  }

  {
    // level( const char *, const char * )
    const char * TestFn = TEST_DATA_DIR "/log.11";
    remove( TestFn );
    
    {
      Log	t( TestFn,
		   LogLevel::Warn | LogLevel::Info | LogLevel::Debug,
		   (ios::open_mode)(ios::app|ios::out), 0644,
		   true, false, true  );
      
      t.level( "Error",   "Src" ) << "test Error (bad)" << '\n';
      t.level( "Err",     "Src" ) << "test Err (bad)" << '\n';
      t.level( "Warning", "Src" ) << "test Warning" << '\n';
      t.level( "Warn",    "Src" ) << "test Warn" << '\n';
      t.level( "App1",    "Src" ) << "test App1 (bad)" << '\n';
      t.level( "App2",    "Src" ) << "test App2 (bad)" << '\n';
      t.level( "App3",    "Src" ) << "test App3 (bad)" << '\n';
      t.level( "App4",    "Src" ) << "test App4 (bad)" << '\n';
      t.level( "App5",    "Src" ) << "test App5 (bad)" << '\n';
      t.level( "App6",    "Src" ) << "test App6 (bad)" << '\n';
      t.level( "Lib1",    "Src" ) << "test Lib1 (bad)" << '\n';
      t.level( "Lib2",    "Src" ) << "test Lib2 (bad)" << '\n';
      t.level( "Lib3",    "Src" ) << "test Lib3 (bad)" << '\n';
      t.level( "Lib4",    "Src" ) << "test Lib4 (bad)" << '\n';
      t.level( "Info",    "Src" ) << "test Info" << '\n';
      t.level( "Test",    "Src" ) << "test Test (bad)" << '\n';
      t.level( "Debug",   "Src" ) << "test Debug" << '\n';
      t.level( "Funct",   "Src" ) << "test Funct (bad)" << '\n';
    }
    
    tester.file( __FILE__, __LINE__, TestFn );
  }

  {
    // level( const char *, const char *, long )
    const char * TestFn = TEST_DATA_DIR "/log.12";
    remove( TestFn );
    
    {
      Log	t( TestFn,
		   "App1 | Warn | Error | Info | Debug",
		   (ios::open_mode)(ios::app|ios::out), 0644,
		   true, false, true  );
      
      t.level( "Error",   "Src",  1 ) << "test Error" << '\n';
      t.level( "Err",     "Src",  2 ) << "test Err" << '\n';
      t.level( "Warning", "Src",  3 ) << "test Warning" << '\n';
      t.level( "Warn",    "Src",  4 ) << "test Warn" << '\n';
      t.level( "App1",    "Src",  5 ) << "test App1" << '\n';
      t.level( "App2",    "Src",  6 ) << "test App2 (bad)" << '\n';
      t.level( "App3",    "Src",  7 ) << "test App3 (bad)" << '\n';
      t.level( "App4",    "Src",  8 ) << "test App4 (bad)" << '\n';
      t.level( "App5",    "Src",  9 ) << "test App5 (bad)" << '\n';
      t.level( "App6",    "Src", 10 ) << "test App6 (bad)" << '\n';
      t.level( "Lib1",    "Src", 11 ) << "test Lib1 (bad)" << '\n';
      t.level( "Lib2",    "Src", 12 ) << "test Lib2 (bad)" << '\n';
      t.level( "Lib3",    "Src", 13 ) << "test Lib3 (bad)" << '\n';
      t.level( "Lib4",    "Src", 14 ) << "test Lib4 (bad)" << '\n';
      t.level( "Info",    "Src", 15 ) << "test Info" << '\n';
      t.level( "Test",    "Src", 16 ) << "test Test (bad)" << '\n';
      t.level( "Debug",   "Src", 17 ) << "test Debug" << '\n';
      t.level( "Funct",   "Src", 18 ) << "test Funct (bad)" << '\n';
    }
    
    tester.file( __FILE__, __LINE__, TestFn );
  }

  {
    // operator () ( const char * )

    const char * TestFn = TEST_DATA_DIR "/log.13";
    remove( TestFn );
    
    {
      Log	t( TestFn, LogLevel::All, (ios::open_mode)(ios::app|ios::out), 0644,
		   true, false, false  );
      
      t( "Error" )   << "test Error" << '\n';
      t( "Err" )     << "test Err" << '\n';
      t( "Warning" ) << "test Warning" << '\n';
      t( "Warn" )    << "test Warn" << '\n';
      t( "App1" )    << "test App1" << '\n';
      t( "App2" )    << "test App2" << '\n';
      t( "App3" )    << "test App3" << '\n';
      t( "App4" )    << "test App4" << '\n';
      t( "App5" )    << "test App5" << '\n';
      t( "App6" )    << "test App6" << '\n';
      t( "Lib1" )    << "test Lib1" << '\n';
      t( "Lib2" )    << "test Lib2" << '\n';
      t( "Lib3" )    << "test Lib3" << '\n';
      t( "Lib4" )    << "test Lib4" << '\n';
      t( "Info" )    << "test Info" << '\n';
      t( "Test" )    << "test Test" << '\n';
      t( "Debug" )   << "test Debug" << '\n';
      t( "Funct" )   << "test Funct" << '\n';
    }
    
    tester.file( __FILE__, __LINE__, TestFn );
  }

  {
    // operator () ( const char *, const char *, long )
    const char * TestFn = TEST_DATA_DIR "/log.14";
    remove( TestFn );
    
    {
      Log	t( TestFn,
		   "App1 | Warn | Error | Info | Debug",
		   (ios::open_mode)(ios::app|ios::out), 0644,
		   true, false, true  );
      
      t( "Error",   "Src",  1 ) << "test Error" << '\n';
      t( "Err",     "Src",  2 ) << "test Err" << '\n';
      t( "Warning", "Src",  3 ) << "test Warning" << '\n';
      t( "Warn",    "Src",  4 ) << "test Warn" << '\n';
      t( "App1",    "Src",  5 ) << "test App1" << '\n';
      t( "App2",    "Src",  6 ) << "test App2 (bad)" << '\n';
      t( "App3",    "Src",  7 ) << "test App3 (bad)" << '\n';
      t( "App4",    "Src",  8 ) << "test App4 (bad)" << '\n';
      t( "App5",    "Src",  9 ) << "test App5 (bad)" << '\n';
      t( "App6",    "Src", 10 ) << "test App6 (bad)" << '\n';
      t( "Lib1",    "Src", 11 ) << "test Lib1 (bad)" << '\n';
      t( "Lib2",    "Src", 12 ) << "test Lib2 (bad)" << '\n';
      t( "Lib3",    "Src", 13 ) << "test Lib3 (bad)" << '\n';
      t( "Lib4",    "Src", 14 ) << "test Lib4 (bad)" << '\n';
      t( "Info",    "Src", 15 ) << "test Info" << '\n';
      t( "Test",    "Src", 16 ) << "test Test (bad)" << '\n';
      t( "Debug",   "Src", 17 ) << "test Debug" << '\n';
      t( "Funct",   "Src", 18 ) << "test Funct (bad)" << '\n';
    }
    
    tester.file( __FILE__, __LINE__, TestFn );
  }

  {
    // setLevelStamp( bool )
    // setTimeStamp( bool )
    // setLocStamp( bool )

    const char *    TestFn = TEST_DATA_DIR "/log.15";
    size_t	    LogSize = 0;
    {
      
      Log t( TestFn,
	     LogLevel::Error | LogLevel::Warn | LogLevel::Info,
	     ios::out );

      t( LogLevel::Error, "Src", 1 ) << "error good\n";
      LogSize += strlen( "mm/dd/yy hh:mm:ss ERROR Src:1 error good\n");

      t( LogLevel::Debug, "Src", 2 ) << "debug BAD\n";

      TEST( t.setLevelStamp( false ) == true );

      t( LogLevel::Warn, "Src", 3 ) << "warning good\n";
      LogSize += strlen( "mm/dd/yy hh:mm:ss Src:3 warning good\n" );

      TEST( t.setTimeStamp( false ) );

      t( LogLevel::Info, "Src", 4 ) << "info good\n";
      LogSize += strlen( "Src:3 info good\n" );

      TEST( t.setLocStamp( false ) );
      
      t( LogLevel::Error, "Src", 5 ) << "error good\n";
      LogSize += strlen( "error good\n");

      TEST( ! t.setTimeStamp( true ) );

      t( LogLevel::Warn, "Src", 6 ) << "warning good\n";
      LogSize += strlen( "mm/dd/yy hh:mm:ss warning good\n" );

      TEST( ! t.setLevelStamp( true ) );

      t( LogLevel::Warn, "Src", 7 ) << "warning good\n";
      LogSize += strlen( "mm/dd/yy hh:mm:ss WARNING warning good\n" );

      TEST( ! t.setLocStamp( true ) );

      t( LogLevel::Warn, "Src", 8 ) << "warning good\n";
      LogSize += strlen( "mm/dd/yy hh:mm:ss WARNING Src:8 warning good\n" );

    }
    {
      FileStat t( TestFn );

      TEST( t.getSize() == LogSize );
    }

  }

  {
    // setOutputLevel( LogLevel::Level )
    // setOutputLevel( const char * )
    // on( LogLevel::Level )
    // off( LogLevel::Level )
    
    const char *    TestFn = TEST_DATA_DIR "/log.16";
    {
      Log t( TestFn, LogLevel::All, ios::out, 0664, true, false, true );

      t( LogLevel::Error, "Test", 1 )   << "test Error (good)" << '\n';
      t( LogLevel::Err, "Test", 2 )     << "test Err (good)" << '\n';
      t( LogLevel::Warning, "Test", 3 ) << "test Warning (good)" << '\n';
      t( LogLevel::Warn, "Test", 4 )    << "test Warn (good)" << '\n';
      t( LogLevel::App1, "Test", 5 )    << "test App1 (good)" << '\n';
      t( LogLevel::App2, "Test", 6 )    << "test App2 (good)" << '\n';
      t( LogLevel::App3, "Test", 7 )    << "test App3 (good)" << '\n';
      t( LogLevel::App4, "Test", 8 )    << "test App4 (good)" << '\n';
      t( LogLevel::App5, "Test", 9 )    << "test App5 (good)" << '\n';
      t( LogLevel::App6, "Test", 10 )   << "test App6 (good)" << '\n';
      t( LogLevel::Lib1, "Test", 11 )   << "test Lib1 (good)" << '\n';
      t( LogLevel::Lib2, "Test", 12 )   << "test Lib2 (good)" << '\n';
      t( LogLevel::Lib3, "Test", 13 )   << "test Lib3 (good)" << '\n';
      t( LogLevel::Lib4, "Test", 14 )   << "test Lib4 (good)" << '\n';
      t( LogLevel::Info, "Test", 15 )   << "test Info (good)" << '\n';
      t( LogLevel::Test, "Test", 16 )   << "test Test (good)" << '\n';
      t( LogLevel::Debug, "Test", 17 )  << "test Debug (good)" << '\n';
      t( LogLevel::Funct, "Test", 18 )  << "test Funct (good)" << '\n';

      TEST( t.setOutputLevel( LogLevel::Warn | LogLevel::Test )
	    == LogLevel::All );

      t( LogLevel::Error, "Test", 0 )   << "test Error (BAD)" << '\n';
      t( LogLevel::Err, "Test", 0 )     << "test Err (BAD)" << '\n';
      t( LogLevel::Warning, "Test", 19 ) << "test Warning (good)" << '\n';
      t( LogLevel::Warn, "Test", 20 )   << "test Warn (good)" << '\n';
      t( LogLevel::App1, "Test", 0 )    << "test App1 (BAD)" << '\n';
      t( LogLevel::App2, "Test", 0 )    << "test App2 (BAD)" << '\n';
      t( LogLevel::App3, "Test", 0 )    << "test App3 (BAD)" << '\n';
      t( LogLevel::App4, "Test", 0 )    << "test App4 (BAD)" << '\n';
      t( LogLevel::App5, "Test", 0 )    << "test App5 (BAD)" << '\n';
      t( LogLevel::App6, "Test", 0 )    << "test App6 (BAD)" << '\n';
      t( LogLevel::Lib1, "Test", 0 )    << "test Lib1 (BAD)" << '\n';
      t( LogLevel::Lib2, "Test", 0 )    << "test Lib2 (BAD)" << '\n';
      t( LogLevel::Lib3, "Test", 0 )    << "test Lib3 (BAD)" << '\n';
      t( LogLevel::Lib4, "Test", 0 )    << "test Lib4 (BAD)" << '\n';
      t( LogLevel::Info, "Test", 0 )    << "test Info (BAD)" << '\n';
      t( LogLevel::Test, "Test", 21 )   << "test Test (good)" << '\n';
      t( LogLevel::Debug, "Test", 0 )   << "test Debug (BAD)" << '\n';
      t( LogLevel::Funct, "Test", 0 )   << "test Funct (BAD)" << '\n';

      TEST( t.setOutputLevel( LogLevel::None ) ==
	    (LogLevel::Warn | LogLevel::Test ) );

      t( LogLevel::Error, "Test", 0 )   << "test Error (BAD)" << '\n';
      t( LogLevel::Err, "Test", 0 )     << "test Err (BAD)" << '\n';
      t( LogLevel::Warning, "Test", 0 ) << "test Warning (BAD)" << '\n';
      t( LogLevel::Warn, "Test", 0 )    << "test Warn (BAD)" << '\n';
      t( LogLevel::App1, "Test", 0 )    << "test App1 (BAD)" << '\n';
      t( LogLevel::App2, "Test", 0 )    << "test App2 (BAD)" << '\n';
      t( LogLevel::App3, "Test", 0 )    << "test App3 (BAD)" << '\n';
      t( LogLevel::App4, "Test", 0 )    << "test App4 (BAD)" << '\n';
      t( LogLevel::App5, "Test", 0 )    << "test App5 (BAD)" << '\n';
      t( LogLevel::App6, "Test", 0 )    << "test App6 (BAD)" << '\n';
      t( LogLevel::Lib1, "Test", 0 )    << "test Lib1 (BAD)" << '\n';
      t( LogLevel::Lib2, "Test", 0 )    << "test Lib2 (BAD)" << '\n';
      t( LogLevel::Lib3, "Test", 0 )    << "test Lib3 (BAD)" << '\n';
      t( LogLevel::Lib4, "Test", 0 )    << "test Lib4 (BAD)" << '\n';
      t( LogLevel::Info, "Test", 0 )    << "test Info (BAD)" << '\n';
      t( LogLevel::Test, "Test", 0 )    << "test Test (BAD)" << '\n';
      t( LogLevel::Debug, "Test", 0 )   << "test Debug (BAD)" << '\n';
      t( LogLevel::Funct, "Test", 0 )   << "test Funct (BAD)" << '\n';

      TEST( t.setOutputLevel( "Funct | Lib1" ) == LogLevel::None );
      
      t( LogLevel::Error, "Test", 0 )   << "test Error (BAD)" << '\n';
      t( LogLevel::Err, "Test", 0 )     << "test Err (BAD)" << '\n';
      t( LogLevel::Warning, "Test", 0 ) << "test Warning (BAD)" << '\n';
      t( LogLevel::Warn, "Test", 0 )    << "test Warn (BAD)" << '\n';
      t( LogLevel::App1, "Test", 0 )    << "test App1 (BAD)" << '\n';
      t( LogLevel::App2, "Test", 0 )    << "test App2 (BAD)" << '\n';
      t( LogLevel::App3, "Test", 0 )    << "test App3 (BAD)" << '\n';
      t( LogLevel::App4, "Test", 0 )    << "test App4 (BAD)" << '\n';
      t( LogLevel::App5, "Test", 0 )    << "test App5 (BAD)" << '\n';
      t( LogLevel::App6, "Test", 0 )    << "test App6 (BAD)" << '\n';
      t( LogLevel::Lib1, "Test", 22 )   << "test Lib1 (good)" << '\n';
      t( LogLevel::Lib2, "Test", 0 )    << "test Lib2 (BAD)" << '\n';
      t( LogLevel::Lib3, "Test", 0 )    << "test Lib3 (BAD)" << '\n';
      t( LogLevel::Lib4, "Test", 0 )    << "test Lib4 (BAD)" << '\n';
      t( LogLevel::Info, "Test", 0 )    << "test Info (BAD)" << '\n';
      t( LogLevel::Test, "Test", 0 )    << "test Test (BAD)" << '\n';
      t( LogLevel::Debug, "Test", 0 )   << "test Debug (BAD)" << '\n';
      t( LogLevel::Funct, "Test", 23 )  << "test Funct (good)" << '\n';

      t.on( LogLevel::Test );
      
      t( LogLevel::Error, "Test", 0 )   << "test Error (BAD)" << '\n';
      t( LogLevel::Err, "Test", 0 )     << "test Err (BAD)" << '\n';
      t( LogLevel::Warning , "Test", 0) << "test Warning (BAD)" << '\n';
      t( LogLevel::Warn, "Test", 0 )    << "test Warn (BAD)" << '\n';
      t( LogLevel::App1, "Test", 0 )    << "test App1 (BAD)" << '\n';
      t( LogLevel::App2, "Test", 0 )    << "test App2 (BAD)" << '\n';
      t( LogLevel::App3, "Test", 0 )    << "test App3 (BAD)" << '\n';
      t( LogLevel::App4, "Test", 0 )    << "test App4 (BAD)" << '\n';
      t( LogLevel::App5, "Test", 0 )    << "test App5 (BAD)" << '\n';
      t( LogLevel::App6, "Test", 0 )    << "test App6 (BAD)" << '\n';
      t( LogLevel::Lib1, "Test", 24 )   << "test Lib1 (good)" << '\n';
      t( LogLevel::Lib2, "Test", 0 )    << "test Lib2 (BAD)" << '\n';
      t( LogLevel::Lib3, "Test", 0 )    << "test Lib3 (BAD)" << '\n';
      t( LogLevel::Lib4, "Test", 0 )    << "test Lib4 (BAD)" << '\n';
      t( LogLevel::Info, "Test", 0 )    << "test Info (BAD)" << '\n';
      t( LogLevel::Test, "Test", 25 )   << "test Test (good)" << '\n';
      t( LogLevel::Debug, "Test", 0 )   << "test Debug (BAD)" << '\n';
      t( LogLevel::Funct, "Test", 26 )  << "test Funct (good)" << '\n';

      t.on( LogLevel::Test | LogLevel::Err | LogLevel::App2 );
      
      t( LogLevel::Error, "Test", 27 )  << "test Error (good)" << '\n';
      t( LogLevel::Err, "Test", 28 )    << "test Err (good)" << '\n';
      t( LogLevel::Warning, "Test", 0 ) << "test Warning (BAD)" << '\n';
      t( LogLevel::Warn, "Test", 0 )    << "test Warn (BAD)" << '\n';
      t( LogLevel::App1, "Test", 0 )    << "test App1 (BAD)" << '\n';
      t( LogLevel::App2, "Test", 29 )   << "test App2 (good)" << '\n';
      t( LogLevel::App3, "Test", 0 )    << "test App3 (BAD)" << '\n';
      t( LogLevel::App4, "Test", 0 )    << "test App4 (BAD)" << '\n';
      t( LogLevel::App5, "Test", 0 )    << "test App5 (BAD)" << '\n';
      t( LogLevel::App6, "Test", 0 )    << "test App6 (BAD)" << '\n';
      t( LogLevel::Lib1, "Test", 30 )   << "test Lib1 (good)" << '\n';
      t( LogLevel::Lib2, "Test", 0 )    << "test Lib2 (BAD)" << '\n';
      t( LogLevel::Lib3, "Test", 0 )    << "test Lib3 (BAD)" << '\n';
      t( LogLevel::Lib4, "Test", 0 )    << "test Lib4 (BAD)" << '\n';
      t( LogLevel::Info, "Test", 0 )    << "test Info (BAD)" << '\n';
      t( LogLevel::Test, "Test", 31 )   << "test Test (good)" << '\n';
      t( LogLevel::Debug, "Test", 0 )   << "test Debug (BAD)" << '\n';
      t( LogLevel::Funct, "Test", 32 )  << "test Funct (good)" << '\n';

      t.off( LogLevel::Funct );
      
      t( LogLevel::Error, "Test", 33 )   << "test Error (good)" << '\n';
      t( LogLevel::Err, "Test", 34 )     << "test Err (good)" << '\n';
      t( LogLevel::Warning, "Test", 0 ) << "test Warning (BAD)" << '\n';
      t( LogLevel::Warn, "Test", 0 )    << "test Warn (BAD)" << '\n';
      t( LogLevel::App1, "Test", 0 )    << "test App1 (BAD)" << '\n';
      t( LogLevel::App2, "Test", 35 )   << "test App2 (good)" << '\n';
      t( LogLevel::App3, "Test", 0 )    << "test App3 (BAD)" << '\n';
      t( LogLevel::App4, "Test", 0 )    << "test App4 (BAD)" << '\n';
      t( LogLevel::App5, "Test", 0 )    << "test App5 (BAD)" << '\n';
      t( LogLevel::App6, "Test", 0 )    << "test App6 (BAD)" << '\n';
      t( LogLevel::Lib1, "Test", 36 )   << "test Lib1 (good)" << '\n';
      t( LogLevel::Lib2, "Test", 0 )    << "test Lib2 (BAD)" << '\n';
      t( LogLevel::Lib3, "Test", 0 )    << "test Lib3 (BAD)" << '\n';
      t( LogLevel::Lib4, "Test", 0 )    << "test Lib4 (BAD)" << '\n';
      t( LogLevel::Info, "Test", 0 )    << "test Info (BAD)" << '\n';
      t( LogLevel::Test, "Test", 37 )   << "test Test (good)" << '\n';
      t( LogLevel::Debug, "Test", 0 )   << "test Debug (BAD)" << '\n';
      t( LogLevel::Funct, "Test", 0 )   << "test Funct (BAD)" << '\n';

      t.off( LogLevel::Funct | LogLevel::Warn |
	     LogLevel::App2 | LogLevel::Test );
      
      t( LogLevel::Error, "Test", 38 )   << "test Error (good)" << '\n';
      t( LogLevel::Err, "Test", 39 )     << "test Err (good)" << '\n';
      t( LogLevel::Warning, "Test", 0 ) << "test Warning (BAD)" << '\n';
      t( LogLevel::Warn, "Test", 0 )    << "test Warn (BAD)" << '\n';
      t( LogLevel::App1, "Test", 0 )    << "test App1 (BAD)" << '\n';
      t( LogLevel::App2, "Test", 0 )    << "test App2 (BAD)" << '\n';
      t( LogLevel::App3, "Test", 0 )    << "test App3 (BAD)" << '\n';
      t( LogLevel::App4, "Test", 0 )    << "test App4 (BAD)" << '\n';
      t( LogLevel::App5, "Test", 0 )    << "test App5 (BAD)" << '\n';
      t( LogLevel::App6, "Test", 0 )    << "test App6 (BAD)" << '\n';
      t( LogLevel::Lib1, "Test", 40 )   << "test Lib1 (good)" << '\n';
      t( LogLevel::Lib2, "Test", 0 )    << "test Lib2 (BAD)" << '\n';
      t( LogLevel::Lib3, "Test", 0 )    << "test Lib3 (BAD)" << '\n';
      t( LogLevel::Lib4, "Test", 0 )    << "test Lib4 (BAD)" << '\n';
      t( LogLevel::Info, "Test", 0 )    << "test Info (BAD)" << '\n';
      t( LogLevel::Test, "Test", 0 )    << "test Test (BAD)" << '\n';
      t( LogLevel::Debug, "Test", 0 )   << "test Debug (BAD)" << '\n';
      t( LogLevel::Funct, "Test", 0 )   << "test Funct (BAD)" << '\n';
    }

    if( ! tester.file( __FILE__, __LINE__, TestFn ) )
      return( false );
      
  }
  return( true );
}


//
// $Log$
// Revision 4.1  1997/09/17 15:14:23  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:09:51  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1997/07/18 21:43:32  houghton
// Port(Sun5): Changed ios::app to (ios::open_mode)(ios::app|ios::out).
//
// Revision 3.1  1996/11/14 01:26:47  houghton
// Changed to Release 3
//
// Revision 2.5  1996/11/13 17:20:01  houghton
// Complete rework of all tests.
// Verified test against Log.hh header comments.
//
//

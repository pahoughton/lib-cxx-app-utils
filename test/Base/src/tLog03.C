//
// File:        tLog03.C
// Project:	Clue
// Desc:        
//
//  Test construtor args operate as expected. This test
//  was delayed to until after level(...) and operator ()
//  were tested because the verification of the constructor flags
//  heavily depends on the correct operator of these two methdos.
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     11/11/96 18:59
//
// Revision History: (See end of file for Revision Log)
//
// $Id$

#include "TestConfig.hh"
#include "LibTest.hh"
#include "Log.hh"
#include "FileStat.hh"
#include <cstdio>
#include <cstring>


bool
tLog03( LibTest & tester )
{
  {
    // This test verifies the stamp flags perform as expected for
    // Log( ostream &, LogLevel::Level )
    //
    // Note only the size will be check because the date/time
    // will change for the time stamps.
    
    const char * TestFn = TEST_DATA_DIR "/log.06";

    {
      // Log( ostream & )
      //  levelStamp = true;
      //  timeStamp = true;
      //  locStamp = true;

      ofstream	logOutput( TestFn );
      TEST( logOutput.good() );

      logOutput <<
	"Log::Log( ostream & ) - \n"
	"mm/dd/yy hh:mm:ss ERROR good\n";
    
      Log	    t( logOutput );

    
      t( LogLevel::Error ) << "good" << '\n';
      t << "good" << '\n';
    
      t( LogLevel::Err ) << "good" << '\n';
      t << "good" << '\n';
    
      t( LogLevel::Warning ) << "BAD" << '\n';
      t << "BAD" << '\n';
    
      t( LogLevel::Warn ) << "BAD" << '\n';
      t << "BAD" << '\n';
    
      t( LogLevel::App1 ) << "BAD" << '\n';
      t << "BAD" << '\n';
    
      t( LogLevel::App2 ) << "BAD" << '\n';
      t << "BAD" << '\n';
    
      t( LogLevel::App3 ) << "BAD" << '\n';
      t << "BAD" << '\n';
    
      t( LogLevel::App4 ) << "BAD" << '\n';
      t << "BAD" << '\n';
    
      t( LogLevel::Info ) << "BAD" << '\n';
      t << "BAD" << '\n';
    
      t( LogLevel::Test ) << "BAD" << '\n';
      t << "BAD" << '\n';
    
      t( LogLevel::Debug ) << "BAD" << '\n';
      t << "BAD" << '\n';
    
      t( LogLevel::Funct ) << "BAD" << '\n';
      t << "BAD" << '\n';

    }

    {    
      ofstream	logOutput( TestFn, ios::app );
      TEST( logOutput.good() );
    
      logOutput <<
	"Log::Log( ostream & ) - \n"
	"mm/dd/yy hh:mm:ss ERROR good\n";
      
      Log	    t( logOutput );
      
      t( LogLevel::Error ) << "good" << '\n';
      t << "good" << '\n';
    
      t( LogLevel::Warning ) << "BAD" << '\n';
      t << "BAD" << '\n';
    
    }
  
    {
      // Log( ostream &, LogLevel::Level )
      //  levelStamp = true;
      //  timeStamp = true;
      //  locStamp = true;
    
      ofstream	logOutput( TestFn, ios::app );
      TEST( logOutput.good() );
    
      logOutput <<
	"Log::Log( ostream &, LogLevel::Level ) - \n"
	"mm/dd/yy hh:mm:ss WARNING good\n";
    
      Log	    t( logOutput, LogLevel::Warning );

      t( LogLevel::Warning ) << "good" << '\n';
      t << "good" << '\n';
    
      t( LogLevel::Warn ) << "good" << '\n';
      t << "good" << '\n';
    
      t( LogLevel::Error ) << "BAD" << '\n';
      t << "BAD" << '\n';
    
    }
  
    {    
      // Log( ostream &, LogLevel::Level, bool )
    
      ofstream	logOutput( TestFn, ios::app );
      TEST( logOutput.good() );
    
      logOutput <<
	"Log::Log( ostream &, LogLevel::Level, bool ) - \n"
	"mm/dd/yy hh:mm:ss TEST good\n";
    
      Log	    t( logOutput, LogLevel::Test, true );

      t( LogLevel::Test ) << "good" << '\n';
    }
  
    {    
      ofstream	logOutput( TestFn, ios::app );
      TEST( logOutput.good() );
    
      logOutput <<
	"Log::Log( ostream &, LogLevel::Level, bool ) - \n"
	"mm/dd/yy hh:mm:ss good\n";
    
      Log	    t( logOutput, LogLevel::Test, false );
      
      t( LogLevel::Test ) << "good" << '\n';
    }
  
    {
      // Log( ostream &, LogLevel::Level, bool, bool )
    
      ofstream	logOutput( TestFn, ios::app );
      TEST( logOutput.good() );
    
      logOutput <<
	"Log::Log( ostream &, LogLevel::Level, bool, bool ) - \n"
	"mm/dd/yy hh:mm:ss TEST good\n";
    
      Log	    t( logOutput, LogLevel::Test, true, true );

      t( LogLevel::Test ) << "good" << '\n';
    }
  
    {    
      ofstream	logOutput( TestFn, ios::app );
      TEST( logOutput.good() );
    
      logOutput <<
	"Log::Log( ostream &, LogLevel::Level, bool, bool ) - \n"
	"TEST good\n";
    
      Log	    t( logOutput, LogLevel::Test, true, false );

      t( LogLevel::Test ) << "good" << '\n';
    }
  
    {    
      ofstream	logOutput( TestFn, ios::app );
      TEST( logOutput.good() );
    
      logOutput <<
	"Log::Log( ostream &, LogLevel::Level, bool, bool ) - \n"
	"mm/dd/yy hh:mm:ss good\n";
    
      Log	    t( logOutput, LogLevel::Test, false, true );

      t( LogLevel::Test ) << "good" << '\n';
    }
  
    {    
      ofstream	logOutput( TestFn, ios::app );
      TEST( logOutput.good() );
    
      logOutput <<
	"Log::Log( ostream &, LogLevel::Level, bool, bool ) - \n"
	"good\n";
    
      Log	    t( logOutput, LogLevel::Test, false, false );

      t( LogLevel::Test ) << "good" << '\n';
    }

    {
      ofstream	logOutput( TestFn, ios::app );
      TEST( logOutput.good() );
    
      logOutput <<
	"Log::Log( ostream &, LogLevel::Level, bool, bool, bool ) - \n"
	"mm/dd/yy hh:mm:ss TEST Src:1 good\n";
    
    
      Log	    t( logOutput, LogLevel::Test, true, true, true );

      t( LogLevel::Test, "Src", 1 ) << "good" << '\n';
      t( LogLevel::Test, "Src", 2 ) << "good" << '\n';
    }

    {
      ofstream	logOutput( TestFn, ios::app );
      TEST( logOutput.good() );
    
      logOutput <<
	"Log::Log( ostream &, LogLevel::Level, bool, bool, bool ) - \n"
	"good\n";
    
    
      Log	    t( logOutput, LogLevel::Test, false, false, false );

      t( LogLevel::Test, "Src", 1 ) << "good" << '\n';
    }

    {
    // We can't check the file by looking at the data
    // because the date strings will be different.
    // This will Just verify the size.
    //
    // Look through the file to double check it.
    //

      FileStat t( TestFn );

      TEST( t.good() );
      TEST( t.getSize() == 1133 );
    }
  }

  {
    const char *    TestFn = TEST_DATA_DIR "/log.07";
    const size_t    MaxSize = 10240;
    const size_t    LineLen = strlen(
	  "mm/dd/yy hh:mm:ss TEST good test with log trimming.\n" );

    
    remove( TestFn );
  
    {
      // Test for the size_t maxSize arg
      //
      // Log( const char *,
      //	    const char *,
      //	    ios::open_mode,
      //	    int,
      //	    bool,
      //	    bool,
      //	    bool,
      //	    size_t )

      Log t( TestFn,
	     LogLevel::Test | LogLevel::Info,
	     ios::app,
	     filebuf::openprot,
	     true,
	     true,
	     true,
	     MaxSize );

      for( size_t size = LineLen; size < MaxSize; size += LineLen )
	t( LogLevel::Test ) << "good test with log trimming.\n";
      
    }

    {
      FileStat t( TestFn );

      // the math works because of int rounding by the compiler.
      TEST( t.getSize() == ((MaxSize / LineLen) * LineLen) );
    }

    {
      Log t( TestFn,
	     LogLevel::Test | LogLevel::Info,
	     ios::app,
	     filebuf::openprot,
	     true,
	     true,
	     true,
	     MaxSize );
	     
      for( size_t size = 0; size < (MaxSize * 4); size += LineLen )
	t( LogLevel::Test ) << "good test with log trimming.\n";
    }

    {
      // the default trimmer (trimSize == 0) deletes the
      // first 'MaxSize / 4' and up to the next '\n' so the
      // log starts on the first character after a new line.
      
      FileStat t( TestFn );

      size_t minSize = ((MaxSize / 4) * 3) - LineLen;
      
      TEST( t.getSize() < MaxSize );
      TEST( t.getSize() > minSize );
    }
  }
  
  {
    const char *    TestFn = TEST_DATA_DIR "/log.08";
    const size_t    MaxSize = 10240;
    const size_t    TrimSize = 1024;
    const size_t    LineLen = strlen(
	  "mm/dd/yy hh:mm:ss TEST good test with log trimming.\n" );

    
    remove( TestFn );
  
    {
      // Test for the size_t trimSize arg
      //
      // Log( const char *,
      //	    const char *,
      //	    ios::open_mode,
      //	    int,
      //	    bool,
      //	    bool,
      //	    bool,
      //	    size_t,
      //	    size_t )

      Log t( TestFn,
	     LogLevel::Test | LogLevel::Info,
	     ios::app,
	     filebuf::openprot,
	     true,
	     true,
	     true,
	     MaxSize,
	     TrimSize );
	     
      for( size_t size = 0; size < (MaxSize * 3); size += LineLen )
	t( LogLevel::Test ) << "good test with log trimming.\n";
      
    }

    {
      FileStat t( TestFn );

      TEST( t.getSize() < MaxSize );
      TEST( t.getSize() > (MaxSize - (TrimSize + LineLen) ));
    }
  }

  {
    // Test last entry not sync'ed on close

    const char *    TestFn = TEST_DATA_DIR "/log.09";
    const char *    EntryText =
      "good test checking close sync.\n"
      "    Using multi line entry with no 'endl'.\n";
    const size_t    EntrySize =
      strlen( "mm/dd/yy hh:mm:ss TEST ") +
      strlen( EntryText );

    {
      Log t( TestFn, "Test", ios::out );

      t(LogLevel::Test) << EntryText;
      t(LogLevel::Test) << EntryText;
    }

    {
      FileStat t( TestFn );

      TEST( t.getSize() == (EntrySize * 2) );
    }

    {
      // now ad 1 char
      Log t( TestFn, "Test" );

      t(LogLevel::Test) << 't';
    }
    
    {
      FileStat t( TestFn );

      TEST( t.getSize() == ( (EntrySize * 2) +
			     strlen( "mm/dd/yy hh:mm:ss TEST ") + 1 ) );
    }      
  }
  return( true );
}

//
// $Log$
// Revision 3.1  1996/11/14 01:26:46  houghton
// Changed to Release 3
//
// Revision 2.6  1996/11/13 17:20:01  houghton
// Complete rework of all tests.
// Verified test against Log.hh header comments.
//
//






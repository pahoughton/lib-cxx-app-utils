//
// File:        tLog01.C
// Project:	StlUtils
// Desc:        
//
//  Test the following Log methods:
//	
//	  inline Log( ostream & 	outStream = cout,
//		      LogLevel::Level 	outLevel = LogLevel::Error,
//		      bool		stampLevel = true,
//		      bool		stampTime = true,
//		      bool		stampLoc = true );
//	
//	  inline Log( ostream & 	outStream,
//		      const char *      outLevel,
//		      bool		stampLevel = true,
//		      bool		stampTime = true,
//		      bool		stampLoc = true ); 
//	  
//	  inline Log( const char * 	fileName,
//		      LogLevel::Level 	outLevel = LogLevel::Error,
//		      ios::open_mode	mode = ios::app,
//		      int		prot = filebuf::openprot,
//		      bool		stampLevel = true,
//		      bool		stampTime = true,
//		      bool		stampLoc = true,
//		      size_t		maxSize = 0,
//		      size_t		trimSize = 0 );
//		      
//	  inline Log( const char * 	fileName,
//		      const char *	outLevel,
//		      ios::open_mode	mode = ios::app,
//		      int		prot = filebuf::openprot,
//		      bool		stampLevel = true,
//		      bool		stampTime = true,
//		      bool		stampLoc = true,
//		      size_t		maxSize = 0,
//		      size_t		trimSize = 0 );
//
//
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     11/11/96 16:31
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#include "TestConfig.hh"
#include "LibTest.hh"
#include "Log.hh"
#include "FileStat.hh"
#include <strstream.h>
#include <cstdlib>
#include <cstdio>
#include <cerrno>



static const char * LogFileName = TEST_DATA_DIR "/log.file.test";

bool
tLog01( LibTest & tester )
{

  {
    // Log();
    
    Log	    t;

    TEST( t.getOutput() == ( LogLevel::Error |
			     LogLevel::Warn |
			     LogLevel::Info ) );

    // these three should return true because that is the
    // default setting and they return the previous setting.
    TEST( t.setLevelStamp( false ) );
    TEST( t.setTimeStamp( false ) );
    TEST( t.setLocStamp( false ) );
    
  }

  {
    // Log( ostream & );
    strstream logDest;

    Log	t(logDest);

    TEST( t.getOutput() == ( LogLevel::Error |
			     LogLevel::Warn |
			     LogLevel::Info ) );

    TEST( t.setLevelStamp( false ) );
    TEST( t.setTimeStamp( false ) );
    TEST( t.setLocStamp( false ) );
  }

  {
    // Log( ostream &, LogLevel::Level )

    Log t( cerr, LogLevel::Error | LogLevel::Warn | LogLevel::Info );
    
    
    TEST( t.getOutput() == (LogLevel::Error |
			    LogLevel::Warn |
			    LogLevel::Info) );
    TEST( t.setLevelStamp( false ) );
    TEST( t.setTimeStamp( false ) );
    TEST( t.setLocStamp( false ) );
  }
  
  {
    // Log( ostream &, LogLevel::Level, bool )

    {
      Log t( cerr, LogLevel::Info, true );
    
    
      TEST( t.getOutput() == LogLevel::Info );
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }
    {
      Log t( cerr, LogLevel::Info, false );
    
    
      TEST( t.getOutput() == LogLevel::Info );
      TEST( ! t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }
  }
  
  {
    // Log( ostream &, LogLevel::Level, bool, bool )

    {
      Log t( cerr, LogLevel::Info, true, true );
    
    
      TEST( t.getOutput() == LogLevel::Info );
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }
    {
      Log t( cerr, LogLevel::Info, true, false );
    
    
      TEST( t.getOutput() == LogLevel::Info );
      TEST( t.setLevelStamp( false ) );
      TEST( ! t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }
  }
  
  {
    // Log( ostream &, LogLevel::Level, bool, bool, bool )

    {
      Log t( cerr, LogLevel::Info, true, true, true );
    
    
      TEST( t.getOutput() == LogLevel::Info );
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }
    {
      Log t( cerr, LogLevel::Info, true, true, false );
    
    
      TEST( t.getOutput() == LogLevel::Info );
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( ! t.setLocStamp( false ) );
    }
  }

  {
    // Log( ostream &, const char * )

    Log t( cerr, "Error | warn | INFO" );
    
    
    TEST( t.getOutput() == (LogLevel::Error |
			    LogLevel::Warn |
			    LogLevel::Info) );
    
    TEST( t.setLevelStamp( false ) );
    TEST( t.setTimeStamp( false ) );
    TEST( t.setLocStamp( false ) );
  }
  
  {
    // Log( ostream &, const char *, bool )

    {
      Log t( cerr, "info", true );
    
    
      TEST( t.getOutput() == LogLevel::Info );
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }
    {
      Log t( cerr, "test | debug", false );
    
    
      TEST( t.getOutput() == (LogLevel::Test |
			      LogLevel::Debug) );
      TEST( ! t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }
  }
  
  {
    // Log( ostream &, const char *, bool, bool )

    {
      Log t( cerr, "Info", true, true );
    
    
      TEST( t.getOutput() == LogLevel::Info );
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }
    {
      Log t( cerr, "Info", true, false );
    
    
      TEST( t.getOutput() == LogLevel::Info );
      TEST( t.setLevelStamp( false ) );
      TEST( ! t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }
  }
  
  {
    // Log( ostream &, const char *, bool, bool, bool )

    {
      Log t( cerr, "Info", true, true, true );
    
    
      TEST( t.getOutput() == LogLevel::Info );
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }
    {
      Log t( cerr, "Info", true, true, false );
    
    
      TEST( t.getOutput() == LogLevel::Info );
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( ! t.setLocStamp( false ) );
    }
  }

  {
    // Log( const char * fileName )

    remove( LogFileName );

    {
      Log t( LogFileName );

      TESTR( t.error(), t.good() );
      
      TEST( t.getOutput() == (LogLevel::Error |
			      LogLevel::Warn |
			      LogLevel::Info) );
    
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TESTR( logFileStat.error(), logFileStat.good() );
    TEST( logFileStat.getSize() == 0 );
    
  }

  {
    // Log( const char *, LogLevel::Level )

    remove( LogFileName );

    {
      Log t( LogFileName, LogLevel::Info );

      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );
    TEST( logFileStat.getSize() == 0 );
    
  }

  {
    // Log( const char *, LogLevel::Level, ios::open_mode )

    remove( LogFileName );

    {
      Log t( LogFileName, LogLevel::Info, ios::nocreate );

      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TEST( ! logFileStat.good() );
    
  }

  {
    // Log( const char *, LogLevel::Level, ios::open_mode, int )

    remove( LogFileName );

    {
      Log t( LogFileName,
	     LogLevel::Info,
	     (ios::open_mode)(ios::app|ios::out),
	     0711 );

      TESTR( t.error(), t.good() );
      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TESTR( logFileStat.error(), logFileStat.good() );
    TEST( (logFileStat.getMode() & 0777) == 0711 );
    
  }


  {
    // Log( const char *, LogLevel::Level, ios::open_mode, int, bool )

    remove( LogFileName );

    {
      Log t( LogFileName,
	     LogLevel::Info,
	     (ios::open_mode)(ios::app|ios::out),
	     0664,
	     true );

      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    {
      Log t( LogFileName,
	     LogLevel::Info,
	     (ios::open_mode)(ios::app|ios::out),
	     0664,
	     false );

      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( ! t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );
    TEST( (logFileStat.getMode() & 0777) == 0664 );
    
  }

  {
    // Log( const char *, LogLevel::Level, ios::open_mode, int, bool, bool )

    remove( LogFileName );

    {
      Log t( LogFileName,
	     LogLevel::Info,
	     (ios::open_mode)(ios::app|ios::out),
	     0664,
	     true,
	     true );

      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    {
      Log t( LogFileName,
	     LogLevel::Info,
	     (ios::open_mode)(ios::app|ios::out),
	     0664,
	     true,
	     false );

      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( t.setLevelStamp( false ) );
      TEST( ! t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );
    TEST( (logFileStat.getMode() & 0777) == 0664 );
    
  }

  {
    // Log( const char *,
    //	    LogLevel::Level,
    //	    ios::open_mode,
    //	    int,
    //	    bool,
    //	    bool,
    //	    bool )

    remove( LogFileName );

    {
      Log t( LogFileName, LogLevel::Info, (ios::open_mode)(ios::app|ios::out), 0664, true, true, true );

      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    {
      Log t( LogFileName, LogLevel::Info, (ios::open_mode)(ios::app|ios::out), 0664, true, true, false );

      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( ! t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );
    TEST( (logFileStat.getMode() & 0777) == 0664 );
    
  }

  {
    // Log( const char *,
    //	    LogLevel::Level,
    //	    ios::open_mode,
    //	    int,
    //	    bool,
    //	    bool,
    //	    bool,
    //	    size_t )

    remove( LogFileName );

    {
      Log t( LogFileName,
	     LogLevel::Info,
	     (ios::open_mode)(ios::app|ios::out),
	     0664,
	     true,
	     true,
	     true,
	     12345 );

      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
      TEST( t.setMaxSize( 0 ) == 12345 );
    }
    
    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );
    TEST( (logFileStat.getMode() & 0777) == 0664 );
    
  }
  {
    // Log( const char *,
    //	    LogLevel::Level,
    //	    ios::open_mode,
    //	    int,
    //	    bool,
    //	    bool,
    //	    bool,
    //	    size_t,
    //	    size_t )

    remove( LogFileName );

    {
      Log t( LogFileName,
	     LogLevel::Info,
	     (ios::open_mode)(ios::app|ios::out),
	     0664,
	     true,
	     true,
	     true,
	     12345,
	     678 );

      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
      TEST( t.setMaxSize( 0 ) == 12345 );
      TEST( t.setTrimSize( 0 ) == 678 );
    }
    
    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );
    TEST( (logFileStat.getMode() & 0777) == 0664 );
    
  }

  {
    // Log( const char *, const char * )

    remove( LogFileName );

    {
      Log t( LogFileName, "Info | Warn" );

      TEST( t.getOutput() == (LogLevel::Info | LogLevel::Warn ));
    
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );
    TEST( logFileStat.getSize() == 0 );
    
  }

  {
    // Log( const char *, const char *, ios::open_mode )

    remove( LogFileName );

    {
      Log t( LogFileName, "info", ios::nocreate );

      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TEST( ! logFileStat.good() );
    
  }

  {
    // Log( const char *, const char *, ios::open_mode, int )

    remove( LogFileName );

    {
      Log t( LogFileName, "info", (ios::open_mode)(ios::app|ios::out), 0711 );

      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );
    TEST( (logFileStat.getMode() & 0777) == 0711 );
    
  }

  {
    // Log( const char *, const char *, ios::open_mode, int, bool )

    remove( LogFileName );

    {
      Log t( LogFileName, "info", (ios::open_mode)(ios::app|ios::out), 0664, true );

      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    {
      Log t( LogFileName, "info", (ios::open_mode)(ios::app|ios::out), 0664, false );

      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( ! t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );
    TEST( (logFileStat.getMode() & 0777) == 0664 );
    
  }

  {
    // Log( const char *, const char *, ios::open_mode, int, bool, bool )

    remove( LogFileName );

    {
      Log t( LogFileName, "info", (ios::open_mode)(ios::app|ios::out), 0664, true, true );

      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    {
      Log t( LogFileName, "info", (ios::open_mode)(ios::app|ios::out), 0664, true, false );

      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( t.setLevelStamp( false ) );
      TEST( ! t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );
    TEST( (logFileStat.getMode() & 0777) == 0664 );
    
  }

  {
    // Log( const char *,
    //	    const char *,
    //	    ios::open_mode,
    //	    int,
    //	    bool,
    //	    bool,
    //	    bool )

    remove( LogFileName );

    {
      Log t( LogFileName, "info", (ios::open_mode)(ios::app|ios::out), 0664, true, true, true );

      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    {
      Log t( LogFileName, "info", (ios::open_mode)(ios::app|ios::out), 0664, true, true, false );

      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( ! t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );
    TEST( (logFileStat.getMode() & 0777) == 0664 );
    
  }

  {
    // Log( const char *,
    //	    const char *,
    //	    ios::open_mode,
    //	    int,
    //	    bool,
    //	    bool,
    //	    bool,
    //	    size_t )

    remove( LogFileName );

    {
      Log t( LogFileName,
	     "info",
	     (ios::open_mode)(ios::app|ios::out),
	     0664,
	     true,
	     true,
	     true,
	     12345 );

      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
      TEST( t.setMaxSize( 0 ) == 12345 );
    }
    
    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );
    TEST( (logFileStat.getMode() & 0777) == 0664 );
    
  }

  {
    // Log( const char *,
    //	    const char *,
    //	    ios::open_mode,
    //	    int,
    //	    bool,
    //	    bool,
    //	    bool,
    //	    size_t,
    //	    size_t )

    remove( LogFileName );

    {
      Log t( LogFileName,
	     "info",
	     (ios::open_mode)(ios::app|ios::out),
	     0664,
	     true,
	     true,
	     true,
	     12345,
	     678 );

      TEST( t.getOutput() == LogLevel::Info );
    
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
      TEST( t.setMaxSize( 0 ) == 12345 );
      TEST( t.setTrimSize( 0 ) == 678 );
    }
    
    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );
    TEST( (logFileStat.getMode() & 0777) == 0664 );
    
  }

  return( true );
}


//
// $Log$
// Revision 5.1  2000/05/25 10:33:28  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:21  houghton
// Changed to Version 4
//
// Revision 3.6  1997/09/17 11:09:48  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.5  1997/07/18 21:39:57  houghton
// Port(Sun5): Changed ios::app to (ios::open_mode)(ios::app|ios::out).
//
// Revision 3.4  1997/03/21 15:41:02  houghton
// Changed for new default output level.
//
// Revision 3.3  1996/11/20 12:16:23  houghton
// Cleanup.
//
// Revision 3.2  1996/11/19 12:35:15  houghton
// Changed include strstream to include strstream.h because strstream
//     is not part of the standard.
//
// Revision 3.1  1996/11/14 01:26:45  houghton
// Changed to Release 3
//
// Revision 2.4  1996/11/13 17:19:59  houghton
// Complete rework of all tests.
// Verified test against Log.hh header comments.
//
//

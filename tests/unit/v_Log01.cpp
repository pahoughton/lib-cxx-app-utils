// 1996-11-11 (cc) <paul4hough@gmail.com>

#include <clue/Log.hpp>
#include <clue/FileStat.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cerrno>

static valid::verify verify("clue::Log01");
using namespace clue;

#define TEST_DATA_DIR "data/Log"

static const char * LogFileName = TEST_DATA_DIR "/log.file.test";

bool
v_Log01( void )
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
    std::stringstream logDest;

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

    Log t( std::cerr, LogLevel::Error | LogLevel::Warn | LogLevel::Info );


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
      Log t( std::cerr, LogLevel::Info, true );


      TEST( t.getOutput() == LogLevel::Info );
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }
    {
      Log t( std::cerr, LogLevel::Info, false );


      TEST( t.getOutput() == LogLevel::Info );
      TEST( ! t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }
  }

  {
    // Log( ostream &, LogLevel::Level, bool, bool )

    {
      Log t( std::cerr, LogLevel::Info, true, true );


      TEST( t.getOutput() == LogLevel::Info );
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }
    {
      Log t( std::cerr, LogLevel::Info, true, false );


      TEST( t.getOutput() == LogLevel::Info );
      TEST( t.setLevelStamp( false ) );
      TEST( ! t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }
  }

  {
    // Log( ostream &, LogLevel::Level, bool, bool, bool )

    {
      Log t( std::cerr, LogLevel::Info, true, true, true );


      TEST( t.getOutput() == LogLevel::Info );
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }
    {
      Log t( std::cerr, LogLevel::Info, true, true, false );


      TEST( t.getOutput() == LogLevel::Info );
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( ! t.setLocStamp( false ) );
    }
  }

  {
    // Log( ostream &, const char * )

    Log t( std::cerr, "Error | warn | INFO" );


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
      Log t( std::cerr, "info", true );


      TEST( t.getOutput() == LogLevel::Info );
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }
    {
      Log t( std::cerr, "test | debug", false );


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
      Log t( std::cerr, "Info", true, true );


      TEST( t.getOutput() == LogLevel::Info );
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }
    {
      Log t( std::cerr, "Info", true, false );


      TEST( t.getOutput() == LogLevel::Info );
      TEST( t.setLevelStamp( false ) );
      TEST( ! t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }
  }

  {
    // Log( ostream &, const char *, bool, bool, bool )

    {
      Log t( std::cerr, "Info", true, true, true );


      TEST( t.getOutput() == LogLevel::Info );
      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }
    {
      Log t( std::cerr, "Info", true, true, false );


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

      TEST( t.good() );

      TEST( t.getOutput() == (LogLevel::Error |
			      LogLevel::Warn |
			      LogLevel::Info) );

      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );
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
    // Log( const char *, LogLevel::Level, ios::openmode, int )

    remove( LogFileName );

    {
      Log t( LogFileName,
	     LogLevel::Info,
	     (std::ios::openmode)(std::ios::app|std::ios::out) );

      TEST( t.good() );
      TEST( t.getOutput() == LogLevel::Info );

      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );
  }


  {
    // Log( const char *, LogLevel::Level, std::ios::openmode, int, bool )

    remove( LogFileName );

    {
      Log t( LogFileName,
	     LogLevel::Info,
	     (std::ios::openmode)(std::ios::app|std::ios::out),
	     true );

      TEST( t.getOutput() == LogLevel::Info );

      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    {
      Log t( LogFileName,
	     LogLevel::Info,
	     (std::ios::openmode)(std::ios::app|std::ios::out),
	     false );

      TEST( t.getOutput() == LogLevel::Info );

      TEST( ! t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );
  }

  {
    // Log( const char *, LogLevel::Level, std::ios::openmode, int, bool, bool )

    remove( LogFileName );

    {
      Log t( LogFileName,
	     LogLevel::Info,
	     (std::ios::openmode)(std::ios::app|std::ios::out),
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
	     (std::ios::openmode)(std::ios::app|std::ios::out),
	     true,
	     false );

      TEST( t.getOutput() == LogLevel::Info );

      TEST( t.setLevelStamp( false ) );
      TEST( ! t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );

  }

  {
    // Log( const char *,
    //	    LogLevel::Level,
    //	    std::ios::openmode,
    //	    int,
    //	    bool,
    //	    bool,
    //	    bool )

    remove( LogFileName );

    {
      Log t( LogFileName, LogLevel::Info, (std::ios::openmode)(std::ios::app|std::ios::out), true, true, true );

      TEST( t.getOutput() == LogLevel::Info );

      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    {
      Log t( LogFileName, LogLevel::Info, (std::ios::openmode)(std::ios::app|std::ios::out), true, true, false );

      TEST( t.getOutput() == LogLevel::Info );

      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( ! t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );

  }

  {
    // Log( const char *,
    //	    LogLevel::Level,
    //	    std::ios::openmode,
    //	    int,
    //	    bool,
    //	    bool,
    //	    bool,
    //	    size_t )

    remove( LogFileName );

    {
      Log t( LogFileName,
	     LogLevel::Info,
	     (std::ios::openmode)(std::ios::app|std::ios::out),
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

  }
  {
    // Log( const char *,
    //	    LogLevel::Level,
    //	    std::ios::openmode,
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
	     (std::ios::openmode)(std::ios::app|std::ios::out),
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
    // Log( const char *, const char *, std::ios::openmode, int )

    remove( LogFileName );

    {
      Log t( LogFileName, "info", (std::ios::openmode)(std::ios::app|std::ios::out) );

      TEST( t.getOutput() == LogLevel::Info );

      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );

  }

  {
    // Log( const char *, const char *, std::ios::openmode, int, bool )

    remove( LogFileName );

    {
      Log t( LogFileName, "info", (std::ios::openmode)(std::ios::app|std::ios::out), true );

      TEST( t.getOutput() == LogLevel::Info );

      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    {
      Log t( LogFileName, "info", (std::ios::openmode)(std::ios::app|std::ios::out), false );

      TEST( t.getOutput() == LogLevel::Info );

      TEST( ! t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );

  }

  {
    // Log( const char *, const char *, std::ios::openmode, int, bool, bool )

    remove( LogFileName );

    {
      Log t( LogFileName, "info", (std::ios::openmode)(std::ios::app|std::ios::out), true, true );

      TEST( t.getOutput() == LogLevel::Info );

      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    {
      Log t( LogFileName, "info", (std::ios::openmode)(std::ios::app|std::ios::out), true, false );

      TEST( t.getOutput() == LogLevel::Info );

      TEST( t.setLevelStamp( false ) );
      TEST( ! t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );

  }

  {
    // Log( const char *,
    //	    const char *,
    //	    std::ios::openmode,
    //	    int,
    //	    bool,
    //	    bool,
    //	    bool )

    remove( LogFileName );

    {
      Log t( LogFileName, "info", (std::ios::openmode)(std::ios::app|std::ios::out), true, true, true );

      TEST( t.getOutput() == LogLevel::Info );

      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( t.setLocStamp( false ) );
    }

    {
      Log t( LogFileName, "info", (std::ios::openmode)(std::ios::app|std::ios::out), true, true, false );

      TEST( t.getOutput() == LogLevel::Info );

      TEST( t.setLevelStamp( false ) );
      TEST( t.setTimeStamp( false ) );
      TEST( ! t.setLocStamp( false ) );
    }

    FileStat logFileStat( LogFileName );

    TEST( logFileStat.good() );

  }

  {
    // Log( const char *,
    //	    const char *,
    //	    std::ios::openmode,
    //	    int,
    //	    bool,
    //	    bool,
    //	    bool,
    //	    size_t )

    remove( LogFileName );

    {
      Log t( LogFileName,
	     "info",
	     (std::ios::openmode)(std::ios::app|std::ios::out),
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

  }

  {
    // Log( const char *,
    //	    const char *,
    //	    std::ios::openmode,
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
	     (std::ios::openmode)(std::ios::app|std::ios::out),
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

  }
  return( verify.is_valid() );
}

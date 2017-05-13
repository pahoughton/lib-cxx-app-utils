// 1996-11-11 (cc) <paul4hough@gmail.com>

#include <clue/Log.hpp>
#include <clue/FileStat.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <cstdio>
#include <cstring>

static valid::verify verify("clue::Log03");
using namespace clue;

#define TEST_DATA_DIR "data/Log"


bool
v_Log03( void )
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

      std::ofstream	logOutput( TestFn );
      TEST( logOutput.good() );

      logOutput <<
	"Log::Log( ostream & ) - \n"
	"mm/dd/yy hh:mm:ss ERROR good\n";

      Log	    t( logOutput );


      t( LogLevel::Error ) << "good" << '\n';
      t << "good" << '\n';

      t( LogLevel::Err ) << "good" << '\n';
      t << "good" << '\n';

      t( LogLevel::Warning ) << "good" << '\n';
      t << "good" << '\n';

      t( LogLevel::Warn ) << "good" << '\n';
      t << "good" << '\n';

      t( LogLevel::App1 ) << "BAD" << '\n';
      t << "BAD" << '\n';

      t( LogLevel::App2 ) << "BAD" << '\n';
      t << "BAD" << '\n';

      t( LogLevel::App3 ) << "BAD" << '\n';
      t << "BAD" << '\n';

      t( LogLevel::App4 ) << "BAD" << '\n';
      t << "BAD" << '\n';

      t( LogLevel::Info ) << "good" << '\n';
      t << "good" << '\n';

      t( LogLevel::Test ) << "BAD" << '\n';
      t << "BAD" << '\n';

      t( LogLevel::Debug ) << "BAD" << '\n';
      t << "BAD" << '\n';

      t( LogLevel::Funct ) << "BAD" << '\n';
      t << "BAD" << '\n';

    }

    {
      std::ofstream	logOutput( TestFn, (std::ios::openmode)(std::ios::app|std::ios::out) );
      TEST( logOutput.good() );

      logOutput <<
	"Log::Log( ostream & ) - \n"
	"mm/dd/yy hh:mm:ss ERROR good\n";

      Log	    t( logOutput );

      t( LogLevel::Error ) << "good" << '\n';
      t << "good" << '\n';

      t( LogLevel::Warning ) << "good" << '\n';
      t << "good" << '\n';

      t( LogLevel::Test ) << "BAD" << '\n';
      t << "BAD" << '\n';

    }

    {
      // Log( ostream &, LogLevel::Level )
      //  levelStamp = true;
      //  timeStamp = true;
      //  locStamp = true;

      std::ofstream	logOutput( TestFn, (std::ios::openmode)(std::ios::app|std::ios::out) );
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

      std::ofstream	logOutput( TestFn, (std::ios::openmode)(std::ios::app|std::ios::out) );
      TEST( logOutput.good() );

      logOutput <<
	"Log::Log( ostream &, LogLevel::Level, bool ) - \n"
	"mm/dd/yy hh:mm:ss TEST good\n";

      Log	    t( logOutput, LogLevel::Test, true );

      t( LogLevel::Test ) << "good" << '\n';
    }

    {
      std::ofstream	logOutput( TestFn, (std::ios::openmode)(std::ios::app|std::ios::out) );
      TEST( logOutput.good() );

      logOutput <<
	"Log::Log( ostream &, LogLevel::Level, bool ) - \n"
	"mm/dd/yy hh:mm:ss good\n";

      Log	    t( logOutput, LogLevel::Test, false );

      t( LogLevel::Test ) << "good" << '\n';
    }

    {
      // Log( ostream &, LogLevel::Level, bool, bool )

      std::ofstream	logOutput( TestFn, (std::ios::openmode)(std::ios::app|std::ios::out) );
      TEST( logOutput.good() );

      logOutput <<
	"Log::Log( ostream &, LogLevel::Level, bool, bool ) - \n"
	"mm/dd/yy hh:mm:ss TEST good\n";

      Log	    t( logOutput, LogLevel::Test, true, true );

      t( LogLevel::Test ) << "good" << '\n';
    }

    {
      std::ofstream	logOutput( TestFn, (std::ios::openmode)(std::ios::app|std::ios::out) );
      TEST( logOutput.good() );

      logOutput <<
	"Log::Log( ostream &, LogLevel::Level, bool, bool ) - \n"
	"TEST good\n";

      Log	    t( logOutput, LogLevel::Test, true, false );

      t( LogLevel::Test ) << "good" << '\n';
    }

    {
      std::ofstream	logOutput( TestFn, (std::ios::openmode)(std::ios::app|std::ios::out) );
      TEST( logOutput.good() );

      logOutput <<
	"Log::Log( ostream &, LogLevel::Level, bool, bool ) - \n"
	"mm/dd/yy hh:mm:ss good\n";

      Log	    t( logOutput, LogLevel::Test, false, true );

      t( LogLevel::Test ) << "good" << '\n';
    }

    {
      std::ofstream	logOutput( TestFn, (std::ios::openmode)(std::ios::app|std::ios::out) );
      TEST( logOutput.good() );

      logOutput <<
	"Log::Log( ostream &, LogLevel::Level, bool, bool ) - \n"
	"good\n";

      Log	    t( logOutput, LogLevel::Test, false, false );

      t( LogLevel::Test ) << "good" << '\n';
    }

    {
      std::ofstream	logOutput( TestFn, (std::ios::openmode)(std::ios::app|std::ios::out) );
      TEST( logOutput.good() );

      logOutput <<
	"Log::Log( ostream &, LogLevel::Level, bool, bool, bool ) - \n"
	"mm/dd/yy hh:mm:ss TEST Src:1 good\n";


      Log	    t( logOutput, LogLevel::Test, true, true, true );

      t( LogLevel::Test, "Src", 1 ) << "good" << '\n';
      t( LogLevel::Test, "Src", 2 ) << "good" << '\n';
    }

    {
      std::ofstream	logOutput( TestFn, (std::ios::openmode)(std::ios::app|std::ios::out) );
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
      TEST( t.getSize() == 1274 );
    }
  }

  {
    const char *		TestFn = TEST_DATA_DIR "/log.07";
    const FileStat::size_type   MaxSize = 10240;
    const size_t		LineLen = strlen(
	  "mm/dd/yy hh:mm:ss TEST good test with log trimming.\n" );


    remove( TestFn );

    {
      // Test for the size_t maxSize arg
      //
      // Log( const char *,
      //	    const char *,
      //	    std::ios::openmode,
      //	    int,
      //	    bool,
      //	    bool,
      //	    bool,
      //	    size_t )

      Log t( TestFn,
	     LogLevel::Test | LogLevel::Info,
	     (std::ios::openmode)(std::ios::app|std::ios::out),
	     true,
	     true,
	     true,
	     MaxSize );

      for( FileStat::size_type size = LineLen;
	   size < MaxSize;
	   size += LineLen )
	t( LogLevel::Test ) << "good test with log trimming.\n";

    }

    {
      FileStat t( TestFn );

      // the math works because of int rounding by the compiler.
      TEST( t.getSize() < MaxSize );
    }

    {
      Log t( TestFn,
	     LogLevel::Test | LogLevel::Info,
	     (std::ios::openmode)(std::ios::app|std::ios::out),
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

      FileStat::size_type minSize = ((MaxSize / 4) * 3) - LineLen;

      TEST( t.getSize() < MaxSize );
      TEST( t.getSize() > minSize );
    }
  }

  {
    const char *		TestFn = TEST_DATA_DIR "/log.08";
    const FileStat::size_type   MaxSize = 10240;
    const size_t		TrimSize = 1024;
    const size_t		LineLen = strlen(
	  "mm/dd/yy hh:mm:ss TEST good test with log trimming.\n" );


    remove( TestFn );

    {
      // Test for the size_t trimSize arg
      //
      // Log( const char *,
      //	    const char *,
      //	    std::ios::openmode,
      //	    int,
      //	    bool,
      //	    bool,
      //	    bool,
      //	    size_t,
      //	    size_t )

      Log t( TestFn,
	     LogLevel::Test | LogLevel::Info,
	     (std::ios::openmode)(std::ios::app|std::ios::out),
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
      TEST( t.getSize()
	    > (FileStat::size_type)(MaxSize - (TrimSize + LineLen) ));
    }
  }

  {
    // Test last entry not sync'ed on close

    const char *    TestFn = TEST_DATA_DIR "/log.09";
    const char *    EntryText =
      "good test checking close sync.\n"
      "    Using multi line entry with no 'endl'.\n";
    const FileStat::size_type    EntrySize =
      strlen( "mm/dd/yy hh:mm:ss TEST ") +
      strlen( EntryText );

    {
      Log t( TestFn, "Test", std::ios::out );

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

      TEST( t.getSize() ==
	    (FileStat::size_type)( (EntrySize * 2) +
				   strlen( "mm/dd/yy hh:mm:ss TEST ") + 1 ));
    }
  }
  {
    // level( const char * )

    const char * TestFn = TEST_DATA_DIR "/log.10";

    {
      Log	t( TestFn, LogLevel::All, std::ios::out,
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
    VVFILE( TestFn );
  }

  {
    // level( const char *, const char * )
    const char * TestFn = TEST_DATA_DIR "/log.11";
    remove( TestFn );

    {
      Log	t( TestFn,
		   LogLevel::Warn | LogLevel::Info | LogLevel::Debug,
		   (std::ios::openmode)(std::ios::app|std::ios::out),
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
    VVFILE( TestFn );
  }

  return( verify.is_valid() );
}

// 1996-11-11 (cc) <paul4hough@gmail.com>

#include <clue/Log.hpp>
#include <clue/FileStat.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <sstream>
#include <cstdio>
#include <cerrno>

static valid::verify verify("clue::Log02");
using namespace clue;

#define TEST_DATA_DIR "data/Log"

bool
v_Log02( void )
{
  {
    // getCurrent( void ) const;
    // getOutput( void ) const;

    const Log t( std::cout, LogLevel::Test | LogLevel::Warn );

    TEST( t.getCurrent() == LogLevel::Error );
    TEST( t.getOutput() == (LogLevel::Test | LogLevel::Warn ) );
  }

  {
    // willOutput( LogLevel::Level ) const;

    {
      const Log t( std::cerr, LogLevel::All );

      TEST( t.willOutput( LogLevel::Error ) );
      TEST( t.willOutput( LogLevel::Err ) );
      TEST( t.willOutput( LogLevel::Warning ) );
      TEST( t.willOutput( LogLevel::Warn ) );
      TEST( t.willOutput( LogLevel::App1 ) );
      TEST( t.willOutput( LogLevel::App2 ) );
      TEST( t.willOutput( LogLevel::App3 ) );
      TEST( t.willOutput( LogLevel::App4 ) );
      TEST( t.willOutput( LogLevel::App5 ) );
      TEST( t.willOutput( LogLevel::App6 ) );
      TEST( t.willOutput( LogLevel::Lib1 ) );
      TEST( t.willOutput( LogLevel::Lib2 ) );
      TEST( t.willOutput( LogLevel::Lib3 ) );
      TEST( t.willOutput( LogLevel::Lib4 ) );
      TEST( t.willOutput( LogLevel::Info ) );
      TEST( t.willOutput( LogLevel::Test ) );
      TEST( t.willOutput( LogLevel::Debug ) );
      TEST( t.willOutput( LogLevel::Funct ) );
    }

    {
      const Log t( std::cerr, LogLevel::Debug | LogLevel::Warn );

      TEST( ! t.willOutput( LogLevel::Error ) );
      TEST( ! t.willOutput( LogLevel::Err ) );
      TEST( t.willOutput( LogLevel::Warning ) );
      TEST( t.willOutput( LogLevel::Warn ) );
      TEST( ! t.willOutput( LogLevel::App1 ) );
      TEST( ! t.willOutput( LogLevel::App2 ) );
      TEST( ! t.willOutput( LogLevel::App3 ) );
      TEST( ! t.willOutput( LogLevel::App4 ) );
      TEST( ! t.willOutput( LogLevel::App5 ) );
      TEST( ! t.willOutput( LogLevel::App6 ) );
      TEST( ! t.willOutput( LogLevel::Lib1 ) );
      TEST( ! t.willOutput( LogLevel::Lib2 ) );
      TEST( ! t.willOutput( LogLevel::Lib3 ) );
      TEST( ! t.willOutput( LogLevel::Lib4 ) );
      TEST( ! t.willOutput( LogLevel::Info ) );
      TEST( ! t.willOutput( LogLevel::Test ) );
      TEST( t.willOutput( LogLevel::Debug ) );
      TEST( ! t.willOutput( LogLevel::Funct ) );
    }
  }

  {
    // level( LogLevel::Level )

    const char * TestFn = TEST_DATA_DIR "/log.01";
    remove( TestFn );

    {
      Log	t( TestFn, LogLevel::All, (std::ios::openmode)(std::ios::app|std::ios::out),
		   true, false, false  );

      t.level( LogLevel::Error )   << "test Error" << '\n';
      t.level( LogLevel::Err )     << "test Err" << '\n';
      t.level( LogLevel::Warning ) << "test Warning" << '\n';
      t.level( LogLevel::Warn )    << "test Warn" << '\n';
      t.level( LogLevel::App1 )    << "test App1" << '\n';
      t.level( LogLevel::App2 )    << "test App2" << '\n';
      t.level( LogLevel::App3 )    << "test App3" << '\n';
      t.level( LogLevel::App4 )    << "test App4" << '\n';
      t.level( LogLevel::App5 )    << "test App5" << '\n';
      t.level( LogLevel::App6 )    << "test App6" << '\n';
      t.level( LogLevel::Lib1 )    << "test Lib1" << '\n';
      t.level( LogLevel::Lib2 )    << "test Lib2" << '\n';
      t.level( LogLevel::Lib3 )    << "test Lib3" << '\n';
      t.level( LogLevel::Lib4 )    << "test Lib4" << '\n';
      t.level( LogLevel::Info )    << "test Info" << '\n';
      t.level( LogLevel::Test )    << "test Test" << '\n';
      t.level( LogLevel::Debug )   << "test Debug" << '\n';
      t.level( LogLevel::Funct )   << "test Funct" << '\n';
    }

    VVFILE( TestFn );
  }

  {
    // level( LogLevel::Level, const char * )
    const char * TestFn = TEST_DATA_DIR "/log.02";
    remove( TestFn );

    {
      Log	t( TestFn,
		   LogLevel::Warn | LogLevel::Info | LogLevel::Debug,
		   (std::ios::openmode)(std::ios::app|std::ios::out),
		   true, false, true  );

      t.level( LogLevel::Error,   "Src" ) << "test Error (bad)" << '\n';
      t.level( LogLevel::Err,     "Src" ) << "test Err (bad)" << '\n';
      t.level( LogLevel::Warning, "Src" ) << "test Warning" << '\n';
      t.level( LogLevel::Warn,    "Src" ) << "test Warn" << '\n';
      t.level( LogLevel::App1,    "Src" ) << "test App1 (bad)" << '\n';
      t.level( LogLevel::App2,    "Src" ) << "test App2 (bad)" << '\n';
      t.level( LogLevel::App3,    "Src" ) << "test App3 (bad)" << '\n';
      t.level( LogLevel::App4,    "Src" ) << "test App4 (bad)" << '\n';
      t.level( LogLevel::App5,    "Src" ) << "test App5 (bad)" << '\n';
      t.level( LogLevel::App6,    "Src" ) << "test App6 (bad)" << '\n';
      t.level( LogLevel::Lib1,    "Src" ) << "test Lib1 (bad)" << '\n';
      t.level( LogLevel::Lib2,    "Src" ) << "test Lib2 (bad)" << '\n';
      t.level( LogLevel::Lib3,    "Src" ) << "test Lib3 (bad)" << '\n';
      t.level( LogLevel::Lib4,    "Src" ) << "test Lib4 (bad)" << '\n';
      t.level( LogLevel::Info,    "Src" ) << "test Info" << '\n';
      t.level( LogLevel::Test,    "Src" ) << "test Test (bad)" << '\n';
      t.level( LogLevel::Debug,   "Src" ) << "test Debug" << '\n';
      t.level( LogLevel::Funct,   "Src" ) << "test Funct (bad)" << '\n';
    }

    VVFILE( TestFn );
  }

  {
    // level( LogLevel::Level, const char *, long )
    const char * TestFn = TEST_DATA_DIR "/log.03";
    remove( TestFn );

    {
      Log	t( TestFn,
		   "App1 | Warn | Error | Info | Debug",
		   (std::ios::openmode)(std::ios::app|std::ios::out),
		   true, false, true  );

      t.level( LogLevel::Error,   "Src",  1 ) << "test Error" << '\n';
      t.level( LogLevel::Err,     "Src",  2 ) << "test Err" << '\n';
      t.level( LogLevel::Warning, "Src",  3 ) << "test Warning" << '\n';
      t.level( LogLevel::Warn,    "Src",  4 ) << "test Warn" << '\n';
      t.level( LogLevel::App1,    "Src",  5 ) << "test App1" << '\n';
      t.level( LogLevel::App2,    "Src",  6 ) << "test App2 (bad)" << '\n';
      t.level( LogLevel::App3,    "Src",  7 ) << "test App3 (bad)" << '\n';
      t.level( LogLevel::App4,    "Src",  8 ) << "test App4 (bad)" << '\n';
      t.level( LogLevel::App5,    "Src",  9 ) << "test App5 (bad)" << '\n';
      t.level( LogLevel::App6,    "Src", 10 ) << "test App6 (bad)" << '\n';
      t.level( LogLevel::Lib1,    "Src", 11 ) << "test Lib1 (bad)" << '\n';
      t.level( LogLevel::Lib2,    "Src", 12 ) << "test Lib2 (bad)" << '\n';
      t.level( LogLevel::Lib3,    "Src", 13 ) << "test Lib3 (bad)" << '\n';
      t.level( LogLevel::Lib4,    "Src", 14 ) << "test Lib4 (bad)" << '\n';
      t.level( LogLevel::Info,    "Src", 15 ) << "test Info" << '\n';
      t.level( LogLevel::Test,    "Src", 16 ) << "test Test (bad)" << '\n';
      t.level( LogLevel::Debug,   "Src", 17 ) << "test Debug" << '\n';
      t.level( LogLevel::Funct,   "Src", 18 ) << "test Funct (bad)" << '\n';
    }

    VVFILE( TestFn );
  }

  {
    // operator () ( void );

    std::stringstream	logDest;
    {
      Log t( logDest, LogLevel::Error, true, false, false );

      t() << "test 1" << std::endl;
    }

    const char * expect = "ERROR test 1\n";

    logDest << std::ends;
    TEST( strcmp( expect, logDest.str().c_str() ) == 0 );
  }

  {
    // operator () ( LogLevel::Level )

    const char * TestFn = TEST_DATA_DIR "/log.04";
    remove( TestFn );

    {
      Log	t( TestFn, LogLevel::All,
		   (std::ios::openmode)(std::ios::app|std::ios::out),
		   true, false, false  );

      t( LogLevel::Error )   << "test Error" << '\n';
      t( LogLevel::Err )     << "test Err" << '\n';
      t( LogLevel::Warning ) << "test Warning" << '\n';
      t( LogLevel::Warn )    << "test Warn" << '\n';
      t( LogLevel::App1 )    << "test App1" << '\n';
      t( LogLevel::App2 )    << "test App2" << '\n';
      t( LogLevel::App3 )    << "test App3" << '\n';
      t( LogLevel::App4 )    << "test App4" << '\n';
      t( LogLevel::App5 )    << "test App5" << '\n';
      t( LogLevel::App6 )    << "test App6" << '\n';
      t( LogLevel::Lib1 )    << "test Lib1" << '\n';
      t( LogLevel::Lib2 )    << "test Lib2" << '\n';
      t( LogLevel::Lib3 )    << "test Lib3" << '\n';
      t( LogLevel::Lib4 )    << "test Lib4" << '\n';
      t( LogLevel::Info )    << "test Info" << '\n';
      t( LogLevel::Test )    << "test Test" << '\n';
      t( LogLevel::Debug )   << "test Debug" << '\n';
      t( LogLevel::Funct )   << "test Funct" << '\n';
    }
    VVFILE( TestFn );
  }

  {
    // operator () ( LogLevel::Level, const char *, long )
    const char * TestFn = TEST_DATA_DIR "/log.05";
    remove( TestFn );

    {
      Log	t( TestFn,
		   "App1 | Warn | Error | Info | Debug",
		   (std::ios::openmode)(std::ios::app|std::ios::out),
		   true, false, true  );

      t( LogLevel::Error,   "Src",  1 ) << "test Error" << '\n';
      t( LogLevel::Err,     "Src",  2 ) << "test Err" << '\n';
      t( LogLevel::Warning, "Src",  3 ) << "test Warning" << '\n';
      t( LogLevel::Warn,    "Src",  4 ) << "test Warn" << '\n';
      t( LogLevel::App1,    "Src",  5 ) << "test App1" << '\n';
      t( LogLevel::App2,    "Src",  6 ) << "test App2 (bad)" << '\n';
      t( LogLevel::App3,    "Src",  7 ) << "test App3 (bad)" << '\n';
      t( LogLevel::App4,    "Src",  8 ) << "test App4 (bad)" << '\n';
      t( LogLevel::App5,    "Src",  9 ) << "test App5 (bad)" << '\n';
      t( LogLevel::App6,    "Src", 10 ) << "test App6 (bad)" << '\n';
      t( LogLevel::Lib1,    "Src", 11 ) << "test Lib1 (bad)" << '\n';
      t( LogLevel::Lib2,    "Src", 12 ) << "test Lib2 (bad)" << '\n';
      t( LogLevel::Lib3,    "Src", 13 ) << "test Lib3 (bad)" << '\n';
      t( LogLevel::Lib4,    "Src", 14 ) << "test Lib4 (bad)" << '\n';
      t( LogLevel::Info,    "Src", 15 ) << "test Info" << '\n';
      t( LogLevel::Test,    "Src", 16 ) << "test Test (bad)" << '\n';
      t( LogLevel::Debug,   "Src", 17 ) << "test Debug" << '\n';
      t( LogLevel::Funct,   "Src", 18 ) << "test Funct (bad)" << '\n';
    }

    VVFILE( TestFn );

  }
  return( verify.is_valid() );
}

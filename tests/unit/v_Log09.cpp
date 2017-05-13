// 1996-11-13 (cc) <paul4hough@gmail.com>

#include <clue/Log.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE


static valid::verify verify("clue::Log09");
using namespace clue;

#define TEST_DATA_DIR "data/Log"


bool
v_Log09( void )
{
  {
    // LogIf( Log, LogLevel::Level )

    const char * TestFn = TEST_DATA_DIR "/log.39";

    {
      Log  t( TestFn,
	      LogLevel::Err | LogLevel::Test,
	      std::ios::out,
	      true, false, true );

      LogIf( t, LogLevel::Error ) << "LogIf test entry." << std::endl;
      LogIf( t, LogLevel::Err ) << "LogIf test entry." << std::endl;
      LogIf( t, LogLevel::Warning ) << "LogIf test entry." << std::endl;
      LogIf( t, LogLevel::Warn ) << "LogIf test entry." << std::endl;
      LogIf( t, LogLevel::App1 ) << "LogIf test entry." << std::endl;
      LogIf( t, LogLevel::App2 ) << "LogIf test entry." << std::endl;
      LogIf( t, LogLevel::App3 ) << "LogIf test entry." << std::endl;
      LogIf( t, LogLevel::App4 ) << "LogIf test entry." << std::endl;
      LogIf( t, LogLevel::App5 ) << "LogIf test entry." << std::endl;
      LogIf( t, LogLevel::Lib1 ) << "LogIf test entry." << std::endl;
      LogIf( t, LogLevel::Lib2 ) << "LogIf test entry." << std::endl;
      LogIf( t, LogLevel::Lib3 ) << "LogIf test entry." << std::endl;
      LogIf( t, LogLevel::Lib4 ) << "LogIf test entry." << std::endl;
      LogIf( t, LogLevel::Info ) << "LogIf test entry." << std::endl;
      LogIf( t, LogLevel::Test ) << "LogIf test entry." << std::endl;
      LogIf( t, LogLevel::Debug ) << "LogIf test entry." << std::endl;
      LogIf( t, LogLevel::Funct ) << "LogIf test entry." << std::endl;

      LogIf( t, LogLevel::Err ) << "Chunk Test: ";

      {
	const char * Entry =
	  " This is a large multi-line entry into the log that\n"
	  "    sould force an overflow becuse there are no sync\n"
	  "    calls.\n\n";

	size_t count = 0;
	for( size_t len = strlen( Entry );
	     len < 4096;
	     len += strlen( Entry ) )
	  {
	    t << "    " << ++count << ')' << Entry;
	  }
      }

      LogIf( t, LogLevel::Debug ) << "BAD" << std::endl;
      LogIf( t, LogLevel::Test ) << "End of Chnunk good!" << std::endl;

      LogIf( t, LogLevel::Debug ) << "BAD Chunk Test: ";

      {
	const char * Entry =
	  " This is a large multi-line entry into the log that\n"
	  "    sould force an overflow becuse there are no sync\n"
	  "    calls.\n\n";

	size_t count = 0;
	for( size_t len = strlen( Entry );
	     len < 4096;
	     len += strlen( Entry ) )
	  {
	    t << "    " << ++count << ')' << Entry;
	  }
      }

      LogIf( t, LogLevel::Test ) << "End of Test" << std::endl;
    }
    VVFILE( TestFn );

  }
  return( verify.is_valid() );
}

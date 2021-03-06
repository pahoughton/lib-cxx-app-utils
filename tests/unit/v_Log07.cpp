// 1996-11-12 (cc) <paul4hough@gmail.com>

#include <clue/Log.hpp>
#include <clue/FileStat.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <sstream>
#include <cstdio>

static valid::verify verify("clue::Log07");
using namespace clue;

#define TEST_DATA_DIR "data/Log"

bool
v_Log07( void )
{

#if __GNUC__ >= 6
  {
    // filter( const char * regex )
    const char *    TestFn = TEST_DATA_DIR "/log.27";
    const char *    Src = "Test.C";
    size_t	    Line = 0;

    {
      Log t( TestFn, LogLevel::All, std::ios::out, true, false, true );

      t( LogLevel::Test, Src, ++Line )
	<< "any old text before filter" << std::endl;

      TEST( t.filter( "good|pass" ) );

      t( LogLevel::Test, Src, ++Line )
	<< "any old text after filter" << std::endl;

      t( LogLevel::Test, Src, ++Line )
	<< "This line is good and should filter" << std::endl;

      t( LogLevel::Test, Src, ++Line )
	<< "This line is bad and should NOT filter" << std::endl;

      t( LogLevel::Test, Src, ++Line )
	<< "This line should pass through the filter" << std::endl;

      TEST( ! t.filter( 0 ) );

      t( LogLevel::Test, Src, ++Line )
	<< "any old text after filter removed" << std::endl;

    }

    VVFILE( TestFn );
  }
#endif // __GNUC__ >= 6

  {
    // addFilter( streambuf *, LogLevel::Level )
    // delFilter( LogBuf::FilterId )

    const char *    TestFn = TEST_DATA_DIR "/log.28";
    const char *    TestF1 = TEST_DATA_DIR "/log.29";
    const char *    TestF2 = TEST_DATA_DIR "/log.30";
    const char *    TestF3 = TEST_DATA_DIR "/log.31";

    // const char *    Src = "Test.C";
    size_t	    Line = 0;

    {
      std::ofstream	f1( TestF1 );
      std::ofstream	f2( TestF2 );
      std::ofstream	f3( TestF3 );

      Log t( TestFn, LogLevel::Err | LogLevel::Warn,
	     std::ios::out,
	     true, false, true );

      t( LogLevel::Error,   "Src", ++Line ) << "test Error" << '\n';
      t( LogLevel::Err,     "Src", ++Line ) << "test Err" << '\n';
      t( LogLevel::Warning, "Src", ++Line ) << "test Warning" << '\n';
      t( LogLevel::Warn,    "Src", ++Line ) << "test Warn" << '\n';
      t( LogLevel::App1,    "Src", ++Line ) << "test App1" << '\n';
      t( LogLevel::App2,    "Src", ++Line ) << "test App2" << '\n';
      t( LogLevel::App3,    "Src", ++Line ) << "test App3" << '\n';
      t( LogLevel::App4,    "Src", ++Line ) << "test App4" << '\n';
      t( LogLevel::App5,    "Src", ++Line ) << "test App5" << '\n';
      t( LogLevel::App6,    "Src", ++Line ) << "test App6" << '\n';
      t( LogLevel::Lib1,    "Src", ++Line ) << "test Lib1" << '\n';
      t( LogLevel::Lib2,    "Src", ++Line ) << "test Lib2" << '\n';
      t( LogLevel::Lib3,    "Src", ++Line ) << "test Lib3" << '\n';
      t( LogLevel::Lib4,    "Src", ++Line ) << "test Lib4" << '\n';
      t( LogLevel::Info,    "Src", ++Line ) << "test Info" << '\n';
      t( LogLevel::Test,    "Src", ++Line ) << "test Test" << '\n';
      t( LogLevel::Debug,   "Src", ++Line ) << "test Debug" << '\n';
      t( LogLevel::Funct,   "Src", ++Line ) << "test Funct" << '\n';

      LogBuf::FilterId fid1 = t.addFilter( f1.rdbuf(), LogLevel::Test );

      t( LogLevel::Error,   "Src", ++Line ) << "test Error" << '\n';
      t( LogLevel::Err,     "Src", ++Line ) << "test Err" << '\n';
      t( LogLevel::Warning, "Src", ++Line ) << "test Warning" << '\n';
      t( LogLevel::Warn,    "Src", ++Line ) << "test Warn" << '\n';
      t( LogLevel::App1,    "Src", ++Line ) << "test App1" << '\n';
      t( LogLevel::App2,    "Src", ++Line ) << "test App2" << '\n';
      t( LogLevel::App3,    "Src", ++Line ) << "test App3" << '\n';
      t( LogLevel::App4,    "Src", ++Line ) << "test App4" << '\n';
      t( LogLevel::App5,    "Src", ++Line ) << "test App5" << '\n';
      t( LogLevel::App6,    "Src", ++Line ) << "test App6" << '\n';
      t( LogLevel::Lib1,    "Src", ++Line ) << "test Lib1" << '\n';
      t( LogLevel::Lib2,    "Src", ++Line ) << "test Lib2" << '\n';
      t( LogLevel::Lib3,    "Src", ++Line ) << "test Lib3" << '\n';
      t( LogLevel::Lib4,    "Src", ++Line ) << "test Lib4" << '\n';
      t( LogLevel::Info,    "Src", ++Line ) << "test Info" << '\n';
      t( LogLevel::Test,    "Src", ++Line ) << "test Test" << '\n';
      t( LogLevel::Debug,   "Src", ++Line ) << "test Debug" << '\n';
      t( LogLevel::Funct,   "Src", ++Line ) << "test Funct" << '\n';

      LogBuf::FilterId fid2 = t.addFilter( f2.rdbuf(), LogLevel::All );

      t( LogLevel::Error,   "Src", ++Line ) << "test Error" << '\n';
      t( LogLevel::Err,     "Src", ++Line ) << "test Err" << '\n';
      t( LogLevel::Warning, "Src", ++Line ) << "test Warning" << '\n';
      t( LogLevel::Warn,    "Src", ++Line ) << "test Warn" << '\n';
      t( LogLevel::App1,    "Src", ++Line ) << "test App1" << '\n';
      t( LogLevel::App2,    "Src", ++Line ) << "test App2" << '\n';
      t( LogLevel::App3,    "Src", ++Line ) << "test App3" << '\n';
      t( LogLevel::App4,    "Src", ++Line ) << "test App4" << '\n';
      t( LogLevel::App5,    "Src", ++Line ) << "test App5" << '\n';
      t( LogLevel::App6,    "Src", ++Line ) << "test App6" << '\n';
      t( LogLevel::Lib1,    "Src", ++Line ) << "test Lib1" << '\n';
      t( LogLevel::Lib2,    "Src", ++Line ) << "test Lib2" << '\n';
      t( LogLevel::Lib3,    "Src", ++Line ) << "test Lib3" << '\n';
      t( LogLevel::Lib4,    "Src", ++Line ) << "test Lib4" << '\n';
      t( LogLevel::Info,    "Src", ++Line ) << "test Info" << '\n';
      t( LogLevel::Test,    "Src", ++Line ) << "test Test" << '\n';
      t( LogLevel::Debug,   "Src", ++Line ) << "test Debug" << '\n';
      t( LogLevel::Funct,   "Src", ++Line ) << "test Funct" << '\n';

      LogBuf::FilterId fid3 = t.addFilter( f3.rdbuf(),
					   LogLevel::Warn |
					   LogLevel::Info |
					   LogLevel::Debug |
					   LogLevel::Test  );

      t( LogLevel::Error,   "Src", ++Line ) << "test Error" << '\n';
      t( LogLevel::Err,     "Src", ++Line ) << "test Err" << '\n';
      t( LogLevel::Warning, "Src", ++Line ) << "test Warning" << '\n';
      t( LogLevel::Warn,    "Src", ++Line ) << "test Warn" << '\n';
      t( LogLevel::App1,    "Src", ++Line ) << "test App1" << '\n';
      t( LogLevel::App2,    "Src", ++Line ) << "test App2" << '\n';
      t( LogLevel::App3,    "Src", ++Line ) << "test App3" << '\n';
      t( LogLevel::App4,    "Src", ++Line ) << "test App4" << '\n';
      t( LogLevel::App5,    "Src", ++Line ) << "test App5" << '\n';
      t( LogLevel::App6,    "Src", ++Line ) << "test App6" << '\n';
      t( LogLevel::Lib1,    "Src", ++Line ) << "test Lib1" << '\n';
      t( LogLevel::Lib2,    "Src", ++Line ) << "test Lib2" << '\n';
      t( LogLevel::Lib3,    "Src", ++Line ) << "test Lib3" << '\n';
      t( LogLevel::Lib4,    "Src", ++Line ) << "test Lib4" << '\n';
      t( LogLevel::Info,    "Src", ++Line ) << "test Info" << '\n';
      t( LogLevel::Test,    "Src", ++Line ) << "test Test" << '\n';
      t( LogLevel::Debug,   "Src", ++Line ) << "test Debug" << '\n';
      t( LogLevel::Funct,   "Src", ++Line ) << "test Funct" << '\n';

      TEST( t.delFilter( fid2 ) == f2.rdbuf() );

      t( LogLevel::Error,   "Src", ++Line ) << "test Error" << '\n';
      t( LogLevel::Err,     "Src", ++Line ) << "test Err" << '\n';
      t( LogLevel::Warning, "Src", ++Line ) << "test Warning" << '\n';
      t( LogLevel::Warn,    "Src", ++Line ) << "test Warn" << '\n';
      t( LogLevel::App1,    "Src", ++Line ) << "test App1" << '\n';
      t( LogLevel::App2,    "Src", ++Line ) << "test App2" << '\n';
      t( LogLevel::App3,    "Src", ++Line ) << "test App3" << '\n';
      t( LogLevel::App4,    "Src", ++Line ) << "test App4" << '\n';
      t( LogLevel::App5,    "Src", ++Line ) << "test App5" << '\n';
      t( LogLevel::App6,    "Src", ++Line ) << "test App6" << '\n';
      t( LogLevel::Lib1,    "Src", ++Line ) << "test Lib1" << '\n';
      t( LogLevel::Lib2,    "Src", ++Line ) << "test Lib2" << '\n';
      t( LogLevel::Lib3,    "Src", ++Line ) << "test Lib3" << '\n';
      t( LogLevel::Lib4,    "Src", ++Line ) << "test Lib4" << '\n';
      t( LogLevel::Info,    "Src", ++Line ) << "test Info" << '\n';
      t( LogLevel::Test,    "Src", ++Line ) << "test Test" << '\n';
      t( LogLevel::Debug,   "Src", ++Line ) << "test Debug" << '\n';
      t( LogLevel::Funct,   "Src", ++Line ) << "test Funct" << '\n';

      TEST( t.delFilter( fid1 ) == f1.rdbuf() );

      t( LogLevel::Error,   "Src", ++Line ) << "test Error" << '\n';
      t( LogLevel::Err,     "Src", ++Line ) << "test Err" << '\n';
      t( LogLevel::Warning, "Src", ++Line ) << "test Warning" << '\n';
      t( LogLevel::Warn,    "Src", ++Line ) << "test Warn" << '\n';
      t( LogLevel::App1,    "Src", ++Line ) << "test App1" << '\n';
      t( LogLevel::App2,    "Src", ++Line ) << "test App2" << '\n';
      t( LogLevel::App3,    "Src", ++Line ) << "test App3" << '\n';
      t( LogLevel::App4,    "Src", ++Line ) << "test App4" << '\n';
      t( LogLevel::App5,    "Src", ++Line ) << "test App5" << '\n';
      t( LogLevel::App6,    "Src", ++Line ) << "test App6" << '\n';
      t( LogLevel::Lib1,    "Src", ++Line ) << "test Lib1" << '\n';
      t( LogLevel::Lib2,    "Src", ++Line ) << "test Lib2" << '\n';
      t( LogLevel::Lib3,    "Src", ++Line ) << "test Lib3" << '\n';
      t( LogLevel::Lib4,    "Src", ++Line ) << "test Lib4" << '\n';
      t( LogLevel::Info,    "Src", ++Line ) << "test Info" << '\n';
      t( LogLevel::Test,    "Src", ++Line ) << "test Test" << '\n';
      t( LogLevel::Debug,   "Src", ++Line ) << "test Debug" << '\n';
      t( LogLevel::Funct,   "Src", ++Line ) << "test Funct" << '\n';

      TEST( t.delFilter( fid3 ) == f3.rdbuf() );

    }

    VVFILE( TestFn );
    VVFILE( TestF1 );
    VVFILE( TestF2 );
    VVFILE( TestF3 );
  }

#if __GNUC__ >= 6
  {
    // addFilter( streambuf *, LogLevel::Level, const char * )
    // delFilter( LogBuf::FilterId )

    const char *    TestFn = TEST_DATA_DIR "/log.32";
    const char *    TestF1 = TEST_DATA_DIR "/log.33";
    const char *    TestF2 = TEST_DATA_DIR "/log.34";
    const char *    TestF3 = TEST_DATA_DIR "/log.35";
    {

      std::ofstream f1( TestF1 );
      std::ofstream f2( TestF2 );
      std::ofstream f3( TestF3 );

      Log t( TestFn, LogLevel::Test,
	     std::ios::out,
	     true, false, true );

      t( LogLevel::Test ) << "Chunk entry: \n";

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

      {
	// put a large quantity of text in the buf
	// before adding the filters. NOTE: the
	// log buf is 2048 so we want to get just under it;

	t( LogLevel::Debug ) << "Bunch of chars: ";

	for( size_t count = 0 ; count < 2000 ; count++ )
	  t << 't';
      }

      LogBuf::FilterId fid1 = t.addFilter( f1.rdbuf(),
					   LogLevel::Test,
					   "((filter)|(regex))" );

      LogBuf::FilterId fid2 = t.addFilter( f2.rdbuf(),
					   LogLevel::Debug,
					   "[tx]" );

      // the level is still set to DEBUG so put 5 'x'
      // that should make it into f2

      t << "xxxxx\n";

      {
	// this test serves two purposes. It will verify
	// both the filting and syncing / overflow of large
	// log entries.

	t( LogLevel::Test )
	  << "This should both overflow and go into the filter f1.\n";

	const char * Entry =
	  " This is a large multi-line entry into the log that\n"
	  "    sould force an overflow becuse there are no sync\n"
	  "    calls.\n\n";

	size_t count = 0;
	for( size_t len = strlen( Entry );
	     len < 8192;
	     len += strlen( Entry ) )
	  {
	    t << "    " << ++count << ')' << Entry;
	  }
      }

      TEST( t.delFilter( fid1 ) == f1.rdbuf() );

      LogBuf::FilterId fid3 = t.addFilter( f3.rdbuf(),
					   LogLevel::All,
					   "all" );

      // make sure filter slots are being re-used.
      TEST( fid3 == fid1 );

      t( LogLevel::Debug ) << "This is BAD\n";
      t( LogLevel::Test ) << "This will only be in the main log\n";
      t( LogLevel::Test )
	<< "This will be in both main and f3. all is well\n";
      t( LogLevel::Debug )
	<< "This should be in both f2 & f3 because of this 'x' and 'all'.\n";

      TEST( t.delFilter( fid2 ) == f2.rdbuf() );

    }

    VVFILE( TestFn );
    VVFILE( TestF1 );
    VVFILE( TestF2 );
    VVFILE( TestF3 );
  }
#endif //__GNUC__ >= 6

  return( verify.is_valid() );
}

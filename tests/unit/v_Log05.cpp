// 1996-11-12 (cc) <paul4hough@gmail.com>

#include <clue/Log.hpp>
#include <clue/FileStat.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <sstream>
#include <cstdio>

static valid::verify verify("clue::Log05");
using namespace clue;

#define TEST_DATA_DIR "data/Log"

bool
v_Log05( void )
{
  {
    // setOutputLevel( LogLevel::Level )
    // setOutputLevel( const char * )
    // on( LogLevel::Level )
    // off( LogLevel::Level )

    const char *    TestFn = TEST_DATA_DIR "/log.16";
    {
      Log t( TestFn, LogLevel::All, std::ios::out, true, false, true );

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
    VVFILE( TestFn );
  }

  {
    // tee( ostream & )

    const char *    TestFn = TEST_DATA_DIR "/log.17";
    const char *    TestTeeFn = TEST_DATA_DIR "/log.18";

    {
      std::ofstream teeDest( TestTeeFn );

      Log   t( TestFn, LogLevel::Err | LogLevel::Debug,
	       std::ios::out,
	       true, false, true );

      t( LogLevel::Error, "Test", 1 ) << "Log error output.\n";
      t( LogLevel::Error, "Test", 2 ) << "Log error output.\n";
      t( LogLevel::Error, "Test", 3 ) << "Log error output.\n";

      t.tee( teeDest );
      t( LogLevel::Debug, "Test", 4 ) << "Log debug output.\n";
      t( LogLevel::Debug, "Test", 5 ) << "Log debug output.\n";
      t( LogLevel::Debug, "Test", 6 ) << "Log debug output.\n";
      t( LogLevel::Debug, "Test", 7 ) << "Log debug output.\n";

    }
    VVFILE( TestFn );
    VVFILE( TestTeeFn );
  }

  {
    // setMaxSize( void )
    // setTrimSize( void )

    const char *    TestFn = TEST_DATA_DIR "/log.19";

    const FileStat::size_type	MaxSize = 40960;
    const FileStat::size_type	TrimSize = 1024;

    const char *    EntryText =
      "good test checking maxSize.\n";
    const FileStat::size_type    EntrySize =
      strlen( "mm/dd/yy hh:mm:ss INFO Test.C:n") +
      strlen( EntryText );

    size_t	    EntryNumber = 0;
    {

      Log t( TestFn, LogLevel::Info, std::ios::out );

      for( FileStat::size_type l = EntrySize;
	   l < (MaxSize * 2);
	   l += EntrySize )
	t( LogLevel::Info, "Test.C", ++EntryNumber ) << EntryText;

    }

    {
      FileStat t( TestFn );

      TEST( t.good() );
      TEST( t.getSize() > MaxSize );
    }

    {
      Log t( TestFn, LogLevel::Info, (std::ios::openmode)(std::ios::app|std::ios::out) );

      for( int l = 0; l < 50; ++l )
	t( LogLevel::Info, "Test.C", ++EntryNumber ) << EntryText;

      TEST( t.setMaxSize( MaxSize ) == 0 );

    }

    {
      FileStat t( TestFn );

      TEST( t.getSize() > ((MaxSize / 4 ) * 3) - EntrySize );
      TEST( t.getSize() < MaxSize );
    }

    {
       Log t( TestFn, LogLevel::Info, (std::ios::openmode)(std::ios::app|std::ios::out) );

      TEST( t.setMaxSize( MaxSize ) == 0 );

      for( int l = EntrySize; l < (MaxSize * 3); l += EntrySize )
	t( LogLevel::Info, "Test.C", ++EntryNumber ) << EntryText;

      TEST( (FileStat::size_type)t.setMaxSize( 0 ) == MaxSize );

      for( int e = EntrySize; e < (MaxSize * 2); e += EntrySize )
	t( LogLevel::Info, "Test.C", ++EntryNumber ) << EntryText;

    }

    {
      FileStat t( TestFn );

      TEST( t.good() );
      TEST( t.getSize() > MaxSize );
    }

    {

      Log t( TestFn, LogLevel::Info, (std::ios::openmode)(std::ios::app|std::ios::out) );

      TEST( t.setMaxSize( MaxSize ) == 0 );
      TEST( t.setTrimSize( TrimSize ) == 0 );

      for( int l = EntrySize; l < (MaxSize * 3); l += EntrySize )
	t( LogLevel::Info, "Test.C", ++EntryNumber ) << EntryText;
    }

    {
      FileStat t( TestFn );

      TEST( t.good() );
      TEST( t.getSize() < MaxSize );
      TEST( t.getSize() > (MaxSize - (TrimSize + EntrySize) ) );
    }
  }
  return( verify.is_valid() );
}

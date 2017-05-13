// 1996-11-12 (cc) <paul4hough@gmail.com>

#include <clue/Log.hpp>
#include <clue/FileStat.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <sstream>
#include <cstdio>

static valid::verify verify("clue::Log06");
using namespace clue;

#define TEST_DATA_DIR "data/Log"

bool
v_Log06( void )
{
  {
    // trim( void );
    // trim( size_t );

    const char *    TestFn = TEST_DATA_DIR "/log.20";

    const FileStat::size_type    MaxSize = 40960;
    const FileStat::size_type    TrimSize = 1024;

    const char *    EntryText =
      "good test checking trim( void ).\n";
    const FileStat::size_type    EntrySize =
      strlen( "mm/dd/yy hh:mm:ss INFO ") +
      strlen( EntryText );

    {
      Log t( TestFn,
	     LogLevel::Info,
	     std::ios::out );

      for( FileStat::size_type e = EntrySize;
	   e < (MaxSize - (EntrySize * 2));
	   e += EntrySize )
	t( LogLevel::Info ) << EntryText;

    }
    {
      // make sure we are between (MaxSize - TrimSize) and MaxSize
      FileStat t( TestFn );

      TEST( t.getSize() < MaxSize );
      TEST( t.getSize() > (MaxSize - TrimSize) );
    }
    {
      Log t( TestFn,
	     LogLevel::Info,
	     (std::ios::openmode)(std::ios::app|std::ios::out),
	     true,
	     true,
	     true,
	     MaxSize,
	     TrimSize );

      FileStat::size_type trimmed = t.trim();

      TEST( trimmed > 0 );
      TEST( trimmed < TrimSize );
    }

    {
      FileStat t( TestFn );

      TEST( t.getSize() < MaxSize );
      TEST( t.getSize() > (MaxSize - (TrimSize + EntrySize)) );
    }

    {
      Log t( TestFn,
	     LogLevel::Info,
	     (std::ios::openmode)(std::ios::app|std::ios::out),
	     true,
	     true,
	     true,
	     MaxSize );

      FileStat::size_type trimmed = t.trim( 10240 );

      TEST( trimmed < MaxSize );
      TEST( trimmed > 0 );
    }

    {
      FileStat t( TestFn );

      TEST( t.getSize() < 10240 );
      TEST( t.getSize() > (10240 - ((10240/4) + EntrySize)) );
    }
  }

  {
    // open( const char * )

    const char *    TestFn = TEST_DATA_DIR "/log.21";
    remove( TestFn );
    {

      std::stringstream tStream;

      Log t( tStream, LogLevel::Error | LogLevel::Info, true, false ) ;

      t() << "BAD\n";

      t.open( TestFn );

      t() << "error good\n";
      t( LogLevel::Info ) << "info good\n";

    }

    {
      std::stringstream tStream;

      Log t( tStream, LogLevel::Error | LogLevel::Info, true, false ) ;

      t() << "BAD\n";

      t.open( TestFn );

      t() << "error good\n";
      t( LogLevel::Info ) << "info good\n";
    }
    VVFILE( TestFn );
  }

  {
    // open( const char *, std::ios::openmode )

    const char * TestFn = TEST_DATA_DIR "/log.22";

    {
      // put some stuff in the file first
      std::ofstream t( TestFn );

      t << "Junk text BAD." << std::endl;
    }

    {

      std::stringstream tStream;

      Log t( tStream, LogLevel::Error | LogLevel::Info, true, false ) ;

      t() << "BAD\n";

      t.open( TestFn, std::ios::out );

      t() << "error Good\n";
      t( "info" ) << "Info good" << std::endl;
    }

    {
      std::stringstream tStream;

      Log t( tStream, LogLevel::Error | LogLevel::Info, true, false ) ;

      t() << "BAD\n";

      t.open( TestFn, (std::ios::openmode)(std::ios::app|std::ios::out) );

      t() << "error Good\n";
      t( "info" ) << "Info good" << std::endl;
    }
    VVFILE( TestFn );
  }

  {
    // setFileName( const char * )

    const char *    TestFn = TEST_DATA_DIR "/log.23";
    remove( TestFn );
    {

      std::stringstream tStream;

      Log t( tStream, LogLevel::Error | LogLevel::Info, true, false ) ;

      t() << "BAD\n";

      t.setFileName( TestFn );

      t() << "error good\n";
      t( LogLevel::Info ) << "info good\n";

    }

    {
      std::stringstream tStream;

      Log t( tStream, LogLevel::Error | LogLevel::Info, true, false ) ;

      t() << "BAD\n";

      t.setFileName( TestFn );

      t() << "error good\n";
      t( LogLevel::Info ) << "info good\n";
    }

    VVFILE( TestFn );
  }

  {
    // setFileName( const char *, std::ios::openmode )

    const char * TestFn = TEST_DATA_DIR "/log.24";

    {
      // put some stuff in the file first
      std::ofstream t( TestFn );

      t << "Junk text BAD." << std::endl;
    }

    {

      std::stringstream tStream;

      Log t( tStream, LogLevel::Error | LogLevel::Info, true, false ) ;

      t() << "BAD\n";

      t.setFileName( TestFn, std::ios::out );

      t() << "error Good\n";
      t( "info" ) << "Info good" << std::endl;
    }

    {
      std::stringstream tStream;

      Log t( tStream, LogLevel::Error | LogLevel::Info, true, false ) ;

      t() << "BAD\n";

      t.setFileName( TestFn, (std::ios::openmode)(std::ios::app|std::ios::out) );

      t() << "error Good\n";
      t( "info" ) << "Info good" << std::endl;
    }
    VVFILE( TestFn );
  }

  {
    // close( void )

    const char * TestFn = TEST_DATA_DIR "/log.25";
    const char * TestOpenFn = TEST_DATA_DIR "/log.26";

    {
      Log t( TestFn, LogLevel::Error | LogLevel::Debug,
	     std::ios::out,
	     true, false );

      t() << "error good\n";
      t( "DEBUG" ) << "debug good" << std::endl;

      {
	t.close();

	t() << "BAD" << std::endl;

	TEST( ! t.good() );

	for( size_t l = 0; l < 50; l++ )
	  t() << "BAD " << l << "\n";
	VVFILE( TestFn );
      }

      {
	t.open( TestOpenFn, std::ios::out );

	TEST( t.good() );

	t() << "error good\n";
	t( "DEBUG" ) << "debug good" << std::endl;

	TEST( t.good() );
      }

    }
    VVFILE( TestOpenFn );
  }
  return( verify.is_valid() );
}

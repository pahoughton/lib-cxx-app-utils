#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Log.hh>
#include <FileStat.hh>
#include <cstdio>
#include <cerrno>
#else
#include <TestCfg.hh>
#include <LibTest.hh>
#include <Log.hh>
#include <FileStat.hh>
#include <cstdio>
#include <cerrno>
#endif

bool
tLog02( LibTest & tester )
{
  static const char *   fn = "data/logfile.01";
  size_t		logSize = 0;
  
  remove( fn );
  {
    // Log( const char * )
        
    Log	t( fn );

    t( LogLevel::Error ) << "good\n";

    logSize += strlen( "mm/dd/yy hh:mm:ss ERROR good\n" );
    
  }

  {
    // Log( const char *, LogLevel::Level )

    Log	t( fn, LogLevel::Warning );

    t( LogLevel::Error ) << "BAD\n";
    t( LogLevel::Warning ) << "good\n";
    
    logSize += strlen( "mm/dd/yy hh:mm:ss WARNING good\n" );
  }

  {
    // Log( const char *, LogLevel::Level, bool )

    Log	t( fn, LogLevel::Test, true );

    t( LogLevel::Error ) << "BAD\n";
    t( LogLevel::Test ) << "good\n";
    
    logSize += strlen( "mm/dd/yy hh:mm:ss TEST good\n" );
  }

  {
    
    Log	t( fn, LogLevel::Test, false );

    t( LogLevel::Error ) << "BAD\n";
    t( LogLevel::Test ) << "good\n";
    
    logSize += strlen( "mm/dd/yy hh:mm:ss good\n" );
  }

  {
    // Log( const char *, LogLevel::Level, bool, bool )
    
    Log	t( fn, LogLevel::Test, false, true );

    t( LogLevel::Error ) << "BAD\n";
    t( LogLevel::Test ) << "good\n";
    
    logSize += strlen( "mm/dd/yy hh:mm:ss good\n" );
  }

  {
    Log	t( fn, LogLevel::Test, false, false );

    t( LogLevel::Error ) << "BAD\n";
    t( LogLevel::Test ) << "good\n";
    
    logSize += strlen( "good\n" );
  }

  {
    FileStat t( fn );

    TEST( (size_t)t.getSize() == logSize );
  }

  fn = "data/logfile.02";
    
  {  
    // Log( const char *, LogLevel::Level, bool, bool, ios::open_mode )

    Log t( fn, LogLevel::Test, false, false, ios::out );

    t( LogLevel::Test ) << "1 good\n";
    t( LogLevel::Error ) << "BAD\n";
    t( LogLevel::Test ) << "2 good\n";

  }
  
  {
    
    Log t( fn, LogLevel::Test | LogLevel::Warn, false, false, ios::app );

    t( LogLevel::Test ) << "3 good\n";
    t( LogLevel::Error ) << "BAD\n";
    t( LogLevel::Test ) << "4 good\n";
    t( LogLevel::Warn ) << "5 good\n";

  }

  {
    tester.file( __FILE__, __LINE__, fn );
  }

  fn = "data/logfile.03";

  remove( fn );
  
  {
    // Log( const char *, LogLevel::Level, bool, bool, ios::open_mode, int )

    Log t( fn, LogLevel::Test | LogLevel::Info, true, false, ios::app, 0666 );

    t( LogLevel::Debug ) << "BAD\n";
    t( LogLevel::Test ) << "1 good\n";
    t( LogLevel::Info ) << "2 good\n";
    t( LogLevel::Test ) << "3 good\n";
  }

  {
    FileStat t( fn );

    TEST( (t.getMode() & 0777 ) == 0666 );
    tester.file( __FILE__, __LINE__, fn );
  }
  
  fn = "data/logfile.04";

  remove( fn );
  
  {
    // Log( const char *, LogLevel::Level, bool, bool, ios::open_mode, int, size_t )

     Log t( fn, LogLevel::Test | LogLevel::Info, true, false,
	    ios::app, 0666, 4096 );

     size_t lineLen = strlen( "TEST good test with log trimming.\n" );

     size_t maxLines = (4096 / lineLen) - 1;
     
     for( size_t line = 0; line < maxLines; line++ )
       {
	 t( LogLevel::Test ) << "good test with log trimming.\n";
       }
  }

  {
    FileStat t( fn );

    size_t minSize = (4096 / 4) * 3;

    TEST( (size_t)t.getSize() > minSize && (size_t)t.getSize() < 4096 );
  }

  
  {

     Log t( fn, LogLevel::Test | LogLevel::Info, true, false,
	    ios::app, 0666, 4096 );

     for( size_t l = 0; l < 50; l++ )       
       t( LogLevel::Test ) << "good test with log trimming.\n";
  }
  
  {
    FileStat t( fn );

    size_t minSize = (4096 / 4) * 3;

    TEST( (size_t)t.getSize() > minSize && t.getSize() < 4096 );
  }

  {
     Log t( fn, LogLevel::Test | LogLevel::Info, true, false,
	    ios::app, 0666, 2048 );

  }
  
  {
    FileStat t( fn );

    size_t minSize = ((2048 / 4) * 3) -
      (strlen( "TEST good test with log trimming.\n" ));
 
    TEST( (size_t)t.getSize() > minSize && t.getSize() < 2048 );
  }

  remove( fn );

  
  {
    // Log( const char *, LogLevel::Level, bool, bool, ios::open_mode, int, size_t, size_t )

     Log t( fn, LogLevel::Test | LogLevel::Info, true, false,
	    ios::app, 0666, 4096, 2048 );

     size_t lineLen = strlen( "TEST good test with log trimming.\n" );

     size_t maxLines = (4096 / lineLen) - 1;
     
     for( size_t line = 0; line < maxLines; line++ )
       {
	 t( LogLevel::Test ) << "good test with log trimming.\n";
       }
  }

  {
    FileStat t( fn );

    size_t minSize = (4096 / 4) * 3;

    TEST( (size_t)t.getSize() > minSize && t.getSize() < 4096 );
  }

  
  {

     Log t( fn, LogLevel::Test | LogLevel::Info, true, false,
	    ios::app, 0666, 4096, 2048 );

     for( size_t l = 0; l < 50; l++ )       
       t( LogLevel::Test ) << "good test with log trimming.\n";
  }
  
  {
    FileStat t( fn );

    size_t minSize = (4096 / 4) * 3;

    TEST( (size_t)t.getSize() > minSize && t.getSize() < 4096 );
  }

  {
     Log t( fn, LogLevel::Test | LogLevel::Info, true, false,
	    ios::app, 0666, 2048, 128 );

  }
  
  {
    FileStat t( fn );

    size_t minSize = (2048 - 128 ) -
      (strlen( "TEST good test with log trimming.\n" ));

    TEST( (size_t)t.getSize() > minSize && t.getSize() < 2048 );
  }

  return( true );
}


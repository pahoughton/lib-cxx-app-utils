#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Log.hh>
#include <FileStat.hh>
#include <cstdio>
#include <cstring>
#else
#include <TestCfg.hh>
#include <LibTest.hh>
#include <Log.hh>
#include <FileStat.hh>
#include <cstdio>
#include <cstring>
#endif

bool
tLog03( LibTest & tester )
{
  static const char *   fn = "data/logfile.01";
  size_t		logSize = 0;

  remove( fn );
  
  {
    // Log( const char *, const char * )

    Log	t( fn, "WARNING" );

    t( LogLevel::ERROR ) << "BAD\n";
    t( LogLevel::WARNING ) << "good\n";
    
    logSize += strlen( "mm/dd/yy hh:mm:ss WARNING good\n" );
  }

  {
    // Log( const char *, const char *, bool )

    Log	t( fn, "TEST", true );

    t( LogLevel::ERROR ) << "BAD\n";
    t( LogLevel::TEST ) << "good\n";
    
    logSize += strlen( "mm/dd/yy hh:mm:ss TEST good\n" );
  }

  {
    
    Log	t( fn, "TEST", false );

    t( LogLevel::ERROR ) << "BAD\n";
    t( LogLevel::TEST ) << "good\n";
    
    logSize += strlen( "mm/dd/yy hh:mm:ss good\n" );
  }

  {
    // Log( const char *, const char *, bool, bool )
    
    Log	t( fn, "TEST", false, true );

    t( LogLevel::ERROR ) << "BAD\n";
    t( LogLevel::TEST ) << "good\n";
    
    logSize += strlen( "mm/dd/yy hh:mm:ss good\n" );
  }

  {
    Log	t( fn, "TEST", false, false );

    t( LogLevel::ERROR ) << "BAD\n";
    t( LogLevel::TEST ) << "good\n";
    
    logSize += strlen( "good\n" );
  }

  {
    FileStat t( fn );

    TEST( (size_t)t.getSize() == logSize );
  }

  fn = "data/logfile.02";
    
  {  
    // Log( const char *, const char *, bool, bool, ios::open_mode )

    Log t( fn, "TEST", false, false, ios::out );

    t( LogLevel::TEST ) << "1 good\n";
    t( LogLevel::ERROR ) << "BAD\n";
    t( LogLevel::TEST ) << "2 good\n";

  }
  
  {
    
    Log t( fn, "TEST | WARNING", false, false, ios::app );

    t( LogLevel::TEST ) << "3 good\n";
    t( LogLevel::ERROR ) << "BAD\n";
    t( LogLevel::TEST ) << "4 good\n";
    t( LogLevel::WARN ) << "5 good\n";

  }

  {
    tester.file( __FILE__, __LINE__, fn );
  }

  fn = "data/logfile.03";

  remove( fn );
  
  {
    // Log( const char *, const char *, bool, bool, ios::open_mode, int )

    Log t( fn, "TEST | INFO", true, false, ios::app, 0666 );

    t( LogLevel::DEBUG ) << "BAD\n";
    t( LogLevel::TEST ) << "1 good\n";
    t( LogLevel::INFO ) << "2 good\n";
    t( LogLevel::TEST ) << "3 good\n";
  }

  {
    FileStat t( fn );

    TEST( (t.getMode() & 0777 ) == 0666 );
    tester.file( __FILE__, __LINE__, fn );
  }
  
  fn = "data/logfile.04";

  remove( fn );
  
  {
    // Log( const char *, const char *, bool, bool, ios::open_mode, int, size_t )

     Log t( fn, "TEST | INFO", true, false,
	    ios::app, 0666, 4096 );

     size_t lineLen = strlen( "TEST good test with log trimming.\n" );

     size_t maxLines = (4096 / lineLen) - 1;
     
     for( size_t line = 0; line < maxLines; line++ )
       {
	 t( LogLevel::TEST ) << "good test with log trimming.\n";
       }
  }

  {
    FileStat t( fn );

    size_t minSize = (4096 / 4) * 3;

    TEST( (size_t)t.getSize() > minSize && (size_t)t.getSize() < 4096 );
  }

  
  {

     Log t( fn, "TEST | INFO", true, false,
	    ios::app, 0666, 4096 );

     for( size_t l = 0; l < 50; l++ )       
       t( LogLevel::TEST ) << "good test with log trimming.\n";
  }
  
  {
    FileStat t( fn );

    size_t minSize = (4096 / 4) * 3;

    TEST( (size_t)t.getSize() > minSize && t.getSize() < 4096 );
  }

  {
     Log t( fn, "TEST | INFO", true, false,
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
    // Log( const char *, const char *, bool, bool, ios::open_mode, int, size_t, size_t )

     Log t( fn, "TEST | INFO", true, false,
	    ios::app, 0666, 4096, 2048 );

     size_t lineLen = strlen( "TEST good test with log trimming.\n" );

     size_t maxLines = (4096 / lineLen) - 1;
     
     for( size_t line = 0; line < maxLines; line++ )
       {
	 t( LogLevel::TEST ) << "good test with log trimming.\n";
       }
  }

  {
    FileStat t( fn );

    size_t minSize = (4096 / 4) * 3;

    TEST( (size_t)t.getSize() > minSize && t.getSize() < 4096 );
  }

  
  {

     Log t( fn, "TEST | INFO", true, false,
	    ios::app, 0666, 4096, 2048 );

     for( size_t l = 0; l < 50; l++ )       
       t( LogLevel::TEST ) << "good test with log trimming.\n";
  }
  
  {
    FileStat t( fn );

    size_t minSize = (4096 / 4) * 3;

    TEST( (size_t)t.getSize() > minSize && t.getSize() < 4096 );
  }

  {
     Log t( fn, "TEST | INFO", true, false,
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


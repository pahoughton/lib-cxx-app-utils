#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Log.hh>
#include <FileStat.hh>
#include <cstdlib>
#include <cstdio>
#include <cerrno>
#else
#include <TestCfg.hh>
#include <LibTest.hh>
#include <Log.hh>
#include <FileStat.hh>
#include <cstdlib>
#include <cstdio>
#include <cerrno>
#endif




#if !defined( CLUE_SHORT_FN )
const char * LogStreamFn = TEST_DATA_DIR "/log.stream.test";
#else
const char * LogStreamFn = TEST_DATA_DIR "/logstrm.tst";
#endif

bool
tLog01( LibTest & tester )
{

  {
    // Log();
    
    Log	    t;    
  }

  {    
    // Log( ostream & );
    // operator () ( LogLevel::Level )

    ofstream	logOutput( LogStreamFn );
    TEST( logOutput.good() );

    logOutput << "Log::Log( ostream & ) - mm/dd/yy hh:mm:ss ERROR good\n";
    
    Log	    t( logOutput );

    
    t( LogLevel::Error ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::Err ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::Warning ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::App1 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::App2 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::App3 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::App4 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::Info ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::Test ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::Debug ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::Funct ) << "BAD" << '\n';
    t << "BAD" << '\n';

  }

  {    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream & ) - mm/dd/yy hh:mm:ss ERROR good\n";
    Log	    t( logOutput );

    t( LogLevel::Error ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::Warning ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
  }
  
  {
    // Log( ostream &, LogLevel::Level )
    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, LogLevel::Level ) - "
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
    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, LogLevel::Level, bool ) - "
      "mm/dd/yy hh:mm:ss TEST good\n";
    
    Log	    t( logOutput, LogLevel::Test, true );

    t( LogLevel::Test ) << "good" << '\n';
  }
  
  {    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, LogLevel::Level, bool ) - "
      "mm/dd/yy hh:mm:ss good\n";
    
    Log	    t( logOutput, LogLevel::Test, false );

    t( LogLevel::Test ) << "good" << '\n';
  }
  
  {
    // Log( ostream &, LogLevel::Level, bool, bool )
    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, LogLevel::Level, bool, bool ) - "
      "mm/dd/yy hh:mm:ss TEST good\n";
    
    Log	    t( logOutput, LogLevel::Test, true, true );

    t( LogLevel::Test ) << "good" << '\n';
  }
  
  {    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, LogLevel::Level, bool, bool ) - "
      "TEST good\n";
    
    Log	    t( logOutput, LogLevel::Test, true, false );

    t( LogLevel::Test ) << "good" << '\n';
  }
  
  {    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, LogLevel::Level, bool, bool ) - "
      "mm/dd/yy hh:mm:ss good\n";
    
    Log	    t( logOutput, LogLevel::Test, false, true );

    t( LogLevel::Test ) << "good" << '\n';
  }
  
  {    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, LogLevel::Level, bool, bool ) - "
      "good\n";
    
    Log	    t( logOutput, LogLevel::Test, false, false );

    t( LogLevel::Test ) << "good" << '\n';
  }

    
  {
    // Log( ostream &, const char *, bool )
    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, const char *, bool ) - "
      "mm/dd/yy hh:mm:ss TEST good\n";
    
    Log	    t( logOutput, "TEST", true );

    t( LogLevel::Test ) << "good" << '\n';
  }
  
  {    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, const char *, bool ) - "
      "mm/dd/yy hh:mm:ss good\n";
    
    Log	    t( logOutput, "TEST", false );

    t( LogLevel::Test ) << "good" << '\n';
  }
  
  {    
    // Log( ostream &, const char *, bool, bool )
    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, const char *, bool, bool ) - "
      "mm/dd/yy hh:mm:ss TEST good\n";
    
    Log	    t( logOutput, "TEST", true, true );

    t( LogLevel::Test ) << "good" << '\n';
  }
  
  {    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, const char *, bool, bool ) - "
      "TEST good\n";
    
    Log	    t( logOutput, "TEST", true, false );

    t( LogLevel::Test ) << "good" << '\n';
  }
  
  {    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, const char *, bool, bool ) - "
      "mm/dd/yy hh:mm:ss good\n";
    
    Log	    t( logOutput, "TEST", false, true );

    t( LogLevel::Test ) << "good" << '\n';
  }
  
  {    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, const char *, bool, bool ) - "
      "good\n";
    
    Log	    t( logOutput, "TEST", false, false );

    t( LogLevel::Test ) << "good" << '\n';
  }
  
  {    
    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, LogLevel::Level ) - "
      "mm/dd/yy hh:mm:ss TEST | ERROR good\n";
    
    Log	    t( logOutput, LogLevel::Error | LogLevel::Test );
    
    t( LogLevel::Error ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::Err ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::Test ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::Warning ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::App1 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::App2 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::App3 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::App4 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::Info ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::Debug ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::Funct ) << "BAD" << '\n';
    t << "BAD" << '\n';

  }

  {    
    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, const char * ) - "
      "mm/dd/yy hh:mm:ss ERROR | TEST good\n";
    
    Log	    t( logOutput, " ERROR | TEST "  );
    
    t( LogLevel::Error ) << "good str |" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::Err ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::Test ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::Warning ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::App1 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::App2 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::App3 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::App4 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::Info ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::Debug ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::Funct ) << "BAD" << '\n';
    t << "BAD" << '\n';

  }

  {    
    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, const char * ) - "
      "mm/dd/yy hh:mm:ss ERROR | TEST good\n";
    
    Log	    t( logOutput, "ERROR|TEST"  );
    
    t( LogLevel::Error ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::Err ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::Test ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::Warning ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::App1 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::App2 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::App3 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::App4 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::Info ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::Debug ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::Funct ) << "BAD" << '\n';
    t << "BAD" << '\n';

  }

  {    
    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, LogLevel::Level ) - "
      "mm/dd/yy hh:mm:ss ALL good\n";
    
    Log	    t( logOutput, LogLevel::All );
    
    t( LogLevel::Error ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::Err ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::Warning ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::Warn ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::App1 ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::App2 ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::App3 ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::App4 ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::Info ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::Test ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::Debug ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::Funct ) << "good" << '\n';
    t << "good" << '\n';
    
  }  

  {
    // We can't check the file by looking at the data
    // because the date strings will be different.
    // This will Just verify the size.
    //
    // Look through the file to double check it.
    //

    const FileStat t( LogStreamFn );

    TEST( t.getSize() == 2425 );
    
  }

  
      
  return( true );
}



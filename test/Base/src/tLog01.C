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
const char * LogStreamFn = TESTDATA_PATH "log.stream.test";
#else
const char * LogStreamFn = TESTDATA_PATH "logstrm.tst";
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

    
    t( LogLevel::ERROR ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::ERR ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::WARNING ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::USER_1 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::USER_2 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::USER_3 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::USER_4 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::INFO ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::TEST ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::DEBUG ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::FUNCT ) << "BAD" << '\n';
    t << "BAD" << '\n';

  }

  {    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream & ) - mm/dd/yy hh:mm:ss ERROR good\n";
    Log	    t( logOutput );

    t( LogLevel::ERROR ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::WARNING ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
  }
  
  {
    // Log( ostream &, LogLevel::Level )
    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, LogLevel::Level ) - "
      "mm/dd/yy hh:mm:ss WARNING good\n";
    
    Log	    t( logOutput, LogLevel::WARNING );

    t( LogLevel::WARNING ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::WARN ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::ERROR ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
  }
  
  {    
    // Log( ostream &, LogLevel::Level, bool )
    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, LogLevel::Level, bool ) - "
      "mm/dd/yy hh:mm:ss TEST good\n";
    
    Log	    t( logOutput, LogLevel::TEST, true );

    t( LogLevel::TEST ) << "good" << '\n';
  }
  
  {    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, LogLevel::Level, bool ) - "
      "mm/dd/yy hh:mm:ss good\n";
    
    Log	    t( logOutput, LogLevel::TEST, false );

    t( LogLevel::TEST ) << "good" << '\n';
  }
  
  {
    // Log( ostream &, LogLevel::Level, bool, bool )
    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, LogLevel::Level, bool, bool ) - "
      "mm/dd/yy hh:mm:ss TEST good\n";
    
    Log	    t( logOutput, LogLevel::TEST, true, true );

    t( LogLevel::TEST ) << "good" << '\n';
  }
  
  {    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, LogLevel::Level, bool, bool ) - "
      "TEST good\n";
    
    Log	    t( logOutput, LogLevel::TEST, true, false );

    t( LogLevel::TEST ) << "good" << '\n';
  }
  
  {    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, LogLevel::Level, bool, bool ) - "
      "mm/dd/yy hh:mm:ss good\n";
    
    Log	    t( logOutput, LogLevel::TEST, false, true );

    t( LogLevel::TEST ) << "good" << '\n';
  }
  
  {    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, LogLevel::Level, bool, bool ) - "
      "good\n";
    
    Log	    t( logOutput, LogLevel::TEST, false, false );

    t( LogLevel::TEST ) << "good" << '\n';
  }

    
  {
    // Log( ostream &, const char *, bool )
    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, const char *, bool ) - "
      "mm/dd/yy hh:mm:ss TEST good\n";
    
    Log	    t( logOutput, "TEST", true );

    t( LogLevel::TEST ) << "good" << '\n';
  }
  
  {    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, const char *, bool ) - "
      "mm/dd/yy hh:mm:ss good\n";
    
    Log	    t( logOutput, "TEST", false );

    t( LogLevel::TEST ) << "good" << '\n';
  }
  
  {    
    // Log( ostream &, const char *, bool, bool )
    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, const char *, bool, bool ) - "
      "mm/dd/yy hh:mm:ss TEST good\n";
    
    Log	    t( logOutput, "TEST", true, true );

    t( LogLevel::TEST ) << "good" << '\n';
  }
  
  {    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, const char *, bool, bool ) - "
      "TEST good\n";
    
    Log	    t( logOutput, "TEST", true, false );

    t( LogLevel::TEST ) << "good" << '\n';
  }
  
  {    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, const char *, bool, bool ) - "
      "mm/dd/yy hh:mm:ss good\n";
    
    Log	    t( logOutput, "TEST", false, true );

    t( LogLevel::TEST ) << "good" << '\n';
  }
  
  {    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, const char *, bool, bool ) - "
      "good\n";
    
    Log	    t( logOutput, "TEST", false, false );

    t( LogLevel::TEST ) << "good" << '\n';
  }
  
  {    
    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, LogLevel::Level ) - "
      "mm/dd/yy hh:mm:ss TEST | ERROR good\n";
    
    Log	    t( logOutput, LogLevel::ERROR | LogLevel::TEST );
    
    t( LogLevel::ERROR ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::ERR ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::TEST ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::WARNING ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::USER_1 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::USER_2 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::USER_3 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::USER_4 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::INFO ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::DEBUG ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::FUNCT ) << "BAD" << '\n';
    t << "BAD" << '\n';

  }

  {    
    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, const char * ) - "
      "mm/dd/yy hh:mm:ss ERROR | TEST good\n";
    
    Log	    t( logOutput, " ERROR | TEST "  );
    
    t( LogLevel::ERROR ) << "good str |" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::ERR ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::TEST ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::WARNING ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::USER_1 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::USER_2 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::USER_3 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::USER_4 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::INFO ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::DEBUG ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::FUNCT ) << "BAD" << '\n';
    t << "BAD" << '\n';

  }

  {    
    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, const char * ) - "
      "mm/dd/yy hh:mm:ss ERROR | TEST good\n";
    
    Log	    t( logOutput, "ERROR|TEST"  );
    
    t( LogLevel::ERROR ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::ERR ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::TEST ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::WARNING ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::USER_1 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::USER_2 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::USER_3 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::USER_4 ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::INFO ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::DEBUG ) << "BAD" << '\n';
    t << "BAD" << '\n';
    
    t( LogLevel::FUNCT ) << "BAD" << '\n';
    t << "BAD" << '\n';

  }

  {    
    
    ofstream	logOutput( LogStreamFn, ios::app );
    TEST( logOutput.good() );
    
    logOutput << "Log::Log( ostream &, LogLevel::Level ) - "
      "mm/dd/yy hh:mm:ss ALL good\n";
    
    Log	    t( logOutput, LogLevel::ALL );
    
    t( LogLevel::ERROR ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::ERR ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::WARNING ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::WARN ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::USER_1 ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::USER_2 ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::USER_3 ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::USER_4 ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::INFO ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::TEST ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::DEBUG ) << "good" << '\n';
    t << "good" << '\n';
    
    t( LogLevel::FUNCT ) << "good" << '\n';
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

    TEST( t.getSize() == 2431 );
    
  }

  
      
  return( true );
}



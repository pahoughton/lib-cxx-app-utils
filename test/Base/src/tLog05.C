#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Log.hh>
#include <FileStat.hh>
#include <cstdio>
#else
#include <TestCfg.hh>
#include <LibTest.hh>
#include <Log.hh>
#include <FileStat.hh>
#include <cstdio>
#endif

bool
tLog05( LibTest & tester )
{
  const char * fn = "data/logfile.07";

  remove( fn );
  
  {
    // level( void )
    // level( LogLevel::Level )
    // operator () ( void )
    // operator () ( LogLevel::Level )
    // level( const char * )
    // operator () ( const char * )

    Log t( fn, LogLevel::ERROR | LogLevel::INFO, true, false );

    t.level() << "error good\n";

    t.level( LogLevel::INFO ) << "info good\n";
    t.level( LogLevel::DEBUG ) << "debug BAD\n";

    t() << "error good\n";

    t( LogLevel::INFO ) << "info good\n";
    t( LogLevel::DEBUG ) << "debug BAD\n";
    t( LogLevel::ERROR ) << "error good\n";
    
    t.level( "ERROR" ) << "error good\n";
    t.level( "TEST" ) << "test BAD\n";
    t.level( "INFO" ) << "info good\n";

    t( "ERROR" ) << "error good\n";
    t( "TEST" ) << "test BAD\n";
    t( "INFO" ) << "info good\n";

  }

  {
    tester.file( __FILE__, __LINE__, fn );
  }

  fn = "data/logfile.08";
  
  {
    // on( LogLevel::Level )
    // off( LogLevel::Level )

    Log t( fn, LogLevel::ERROR | LogLevel::INFO, true, false, ios::out );

    t( LogLevel::ERROR ) << "error good\n";
    t( LogLevel::DEBUG ) << "debug BAD\n";
    t( LogLevel::INFO ) << "info good\n";

    t.on( LogLevel::DEBUG );
    
    t( LogLevel::DEBUG ) << "debug good\n";
    t( LogLevel::ERROR ) << "error good\n";
    t( LogLevel::INFO ) << "info good\n";

    t.off( LogLevel::INFO );
    
    t( LogLevel::DEBUG ) << "debug good\n";
    t( LogLevel::ERROR ) << "error good\n";
    t( LogLevel::INFO ) << "info BAD\n";

    t.on( LogLevel::TEST | LogLevel::WARNING );
    t.off( LogLevel::DEBUG | LogLevel::ERROR );
    
    t( LogLevel::DEBUG ) << "debug BAD\n";
    t( LogLevel::ERROR ) << "error BAD\n";
    t( LogLevel::INFO ) << "info BAD\n";

    t( LogLevel::TEST ) << "test good\n";
    t( LogLevel::ERROR ) << "error BAD\n";
    t( LogLevel::WARN ) << "warning good\n";

  }

  {
    tester.file( __FILE__, __LINE__, fn );
  }

  {
    // getCurrent( void ) const
    // getOutput( void ) const
    // willOutput( LogLevel::Level ) const


    Log t( fn, LogLevel::ERROR | LogLevel::INFO, true, false );

    TEST( t.getCurrent() == LogLevel::ERROR );
    TEST( t.getOutput() == LogLevel::ERROR | LogLevel::INFO );

    TEST( t.willOutput( LogLevel::ERROR ) );
    TEST( t.willOutput( LogLevel::INFO ) );
    TEST( ! t.willOutput( LogLevel::TEST ) );
  }

  {
    // setFileName( const char * )
    // open( const char * )
    // close( void )

    strstream tStream;
    
    Log t( tStream, LogLevel::ERROR | LogLevel::INFO, true, false ) ;

    t() << "BAD\n";
    
    t.setFileName( "data/logfile.09", ios::out );

    t() << "error good\n";
    t( LogLevel::INFO ) << "info good\n";

    t.close();

    {
      for( size_t l = 0; l < 500; l++ )
	t() << "BAD " << l << "\n";
    }
    
    TEST( ! t.good() );
    
    tester.file( __FILE__, __LINE__, "data/logfile.09" );

    t.open( "data/logfile.10", ios::out );

    TEST( t.good() );

    {
      for( size_t l = 0; l < 50; l++ )
	t( LogLevel::INFO ) << "info good " << l << "\n";
    }
  }

  {
    tester.file( __FILE__, __LINE__, "data/logfile.10" );
  }
  
  fn = "data/logfile.11";
  
  {
    // setOutputLevel( LogLevel::Level )
    // setOutputLevel( const char * )
    // setLevelStamp( bool )
    // setTimeStamp( bool )

    Log t( fn, LogLevel::ERROR | LogLevel::INFO, true, true, ios::out );

    t.setOutputLevel( LogLevel::DEBUG | LogLevel::TEST );

    t.setTimeStamp( false );

    t() << "error BAD\n";
    t( LogLevel::DEBUG ) << "debug good\n";
    t( LogLevel::INFO ) << "info BAD\n";
    t( LogLevel::TEST ) << "test good\n";

    t.setOutputLevel( "WARNING | FUNCT" );

    t() << "error BAD\n";
    t( LogLevel::DEBUG ) << "debug BAD\n";
    t( LogLevel::WARN ) << "warning good\n";
    t( LogLevel::INFO ) << "info BAD\n";
    t( LogLevel::TEST ) << "test BAD\n";
    t( LogLevel::FUNCT ) << "funct good\n";

    t.setLevelStamp( false );
    
    t() << "error BAD\n";
    t( LogLevel::DEBUG ) << "debug BAD\n";
    t( LogLevel::WARN ) << "good\n";
    t( LogLevel::INFO ) << "info BAD\n";
    t( LogLevel::TEST ) << "test BAD\n";
    t( LogLevel::FUNCT ) << "good\n";

  }

  {
    tester.file( __FILE__, __LINE__, fn );
  }

  fn = "data/logfile.12";
  remove( fn );
  
  {
    // getClassName( void ) const
    // getVersion( void ) const
    // getVersion( bool ) const

    Log t( fn, LogLevel::ERROR, true, false );

    TEST( t.getClassName() != 0 );
    TEST( t.getVersion() != 0 );
    TEST( t.getVersion( false ) != 0 );
    
  }

  {
    // dumpInfo( ostream & ) const
    // version

    Log t( fn, LogLevel::ERROR, true, false );

    tester.getDump() << '\n' << t.getClassName() << " dumpInfo:\n";
    t.dumpInfo( tester.getDump(), " -> ", true );
    tester.getDump() << '\n' << t.getClassName() << " version:\n";
    tester.getDump() << t.version;
    
    tester.getDump() << '\n' << tester.getCurrentTestName();
    
  }
  
  {
    // LogIf( Log &, LogLeve::Level )

    Log t( fn, LogLevel::ERROR | LogLevel::INFO | LogLevel::TEST,
	   true, false, ios::out );

    LogIf( t, LogLevel::WARN ) << "warn BAD\n";
    LogIf( t, LogLevel::ERR ) << "error good\n";
    LogIf( t, LogLevel::DEBUG ) << "debug BAD\n";
    LogIf( t, LogLevel::TEST ) << "test good\n";
    LogIf( t, LogLevel::FUNCT ) << "funct BAD\n";
    LogIf( t, LogLevel::INFO ) << "info good\n";
  }

  {
    tester.file( __FILE__, __LINE__, fn );
  }

  return( true );
}

    
  
      
      
    
    

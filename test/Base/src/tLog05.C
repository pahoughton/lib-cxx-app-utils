#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Log.hh>
#include <FileStat.hh>
#include <cstdio>
#include <strstream>
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
  const char * fn = TEST_DATA_DIR "/logfile.07";

  remove( fn );

#if defined( FIXME )
  {
    // level( void )
    // level( LogLevel::Level )
    // operator () ( void )
    // operator () ( LogLevel::Level )
    // level( const char * )
    // operator () ( const char * )

    Log t( fn, LogLevel::Error | LogLevel::Info, true, false );

    t.level() << "error good\n";

    t.level( LogLevel::Info ) << "info good\n";
    t.level( LogLevel::Debug ) << "debug BAD\n";

    t() << "error good\n";

    t( LogLevel::Info ) << "info good\n";
    t( LogLevel::Debug ) << "debug BAD\n";
    t( LogLevel::Error ) << "error good\n";
    
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

  fn = TEST_DATA_DIR "/logfile.08";
  
  {
    // on( LogLevel::Level )
    // off( LogLevel::Level )

    Log t( fn, LogLevel::Error | LogLevel::Info, true, false, ios::out );

    t( LogLevel::Error ) << "error good\n";
    t( LogLevel::Debug ) << "debug BAD\n";
    t( LogLevel::Info ) << "info good\n";

    t.on( LogLevel::Debug );
    
    t( LogLevel::Debug ) << "debug good\n";
    t( LogLevel::Error ) << "error good\n";
    t( LogLevel::Info ) << "info good\n";

    t.off( LogLevel::Info );
    
    t( LogLevel::Debug ) << "debug good\n";
    t( LogLevel::Error ) << "error good\n";
    t( LogLevel::Info ) << "info BAD\n";

    t.on( LogLevel::Test | LogLevel::Warning );
    t.off( LogLevel::Debug | LogLevel::Error );
    
    t( LogLevel::Debug ) << "debug BAD\n";
    t( LogLevel::Error ) << "error BAD\n";
    t( LogLevel::Info ) << "info BAD\n";

    t( LogLevel::Test ) << "test good\n";
    t( LogLevel::Error ) << "error BAD\n";
    t( LogLevel::Warn ) << "warning good\n";

  }

  {
    tester.file( __FILE__, __LINE__, fn );
  }

  {
    // getCurrent( void ) const
    // getOutput( void ) const
    // willOutput( LogLevel::Level ) const


    Log t( fn, LogLevel::Error | LogLevel::Info, true, false );

    TEST( t.getCurrent() == LogLevel::Error );
    TEST( t.getOutput() == LogLevel::Error | LogLevel::Info );

    TEST( t.willOutput( LogLevel::Error ) );
    TEST( t.willOutput( LogLevel::Info ) );
    TEST( ! t.willOutput( LogLevel::Test ) );
  }

  {
    // setFileName( const char * )
    // open( const char * )
    // close( void )

    strstream tStream;
    
    Log t( tStream, LogLevel::Error | LogLevel::Info, true, false ) ;

    t() << "BAD\n";
    
    t.setFileName( TEST_DATA_DIR "/logfile.09", ios::out );

    t() << "error good\n";
    t( LogLevel::Info ) << "info good\n";

    t.close();

    {
      for( size_t l = 0; l < 500; l++ )
	t() << "BAD " << l << "\n";
    }
    
    TEST( ! t.good() );
    
    tester.file( __FILE__, __LINE__, TEST_DATA_DIR "/logfile.09" );

    t.open( TEST_DATA_DIR "/logfile.10", ios::out );

    TEST( t.good() );

    {
      for( size_t l = 0; l < 50; l++ )
	t( LogLevel::Info ) << "info good " << l << "\n";
    }
  }

  {
    tester.file( __FILE__, __LINE__, TEST_DATA_DIR "/logfile.10" );
  }
  
  fn = TEST_DATA_DIR "/logfile.11";
  
  {
    // setOutputLevel( LogLevel::Level )
    // setOutputLevel( const char * )
    // setLevelStamp( bool )
    // setTimeStamp( bool )

    Log t( fn, LogLevel::Error | LogLevel::Info, true, true, ios::out );

    t.setOutputLevel( LogLevel::Debug | LogLevel::Test );

    t.setTimeStamp( false );

    t() << "error BAD\n";
    t( LogLevel::Debug ) << "debug good\n";
    t( LogLevel::Info ) << "info BAD\n";
    t( LogLevel::Test ) << "test good\n";

    t.setOutputLevel( "WARNING | FUNCT" );

    t() << "error BAD\n";
    t( LogLevel::Debug ) << "debug BAD\n";
    t( LogLevel::Warn ) << "warning good\n";
    t( LogLevel::Info ) << "info BAD\n";
    t( LogLevel::Test ) << "test BAD\n";
    t( LogLevel::Funct ) << "funct good\n";

    t.setLevelStamp( false );
    
    t() << "error BAD\n";
    t( LogLevel::Debug ) << "debug BAD\n";
    t( LogLevel::Warn ) << "good\n";
    t( LogLevel::Info ) << "info BAD\n";
    t( LogLevel::Test ) << "test BAD\n";
    t( LogLevel::Funct ) << "good\n";

  }

  {
    tester.file( __FILE__, __LINE__, fn );
  }

  fn = TEST_DATA_DIR "/logfile.12";
  remove( fn );
  
  {
    // getClassName( void ) const
    // getVersion( void ) const
    // getVersion( bool ) const

    Log t( fn, LogLevel::Error, true, false );

    TEST( t.getClassName() != 0 );
    TEST( t.getVersion() != 0 );
    TEST( t.getVersion( false ) != 0 );
    
  }

  {
    // dumpInfo( ostream & ) const
    // version

    Log t( fn, LogLevel::Error, true, false );

    tester.getDump() << '\n' << t.getClassName() << " dumpInfo:\n";
    t.dumpInfo( tester.getDump(), " -> ", true );
    tester.getDump() << '\n' << t.getClassName() << " version:\n";
    tester.getDump() << t.version;
    
    tester.getDump() << '\n' << tester.getCurrentTestName();
    
  }
  
  {
    // LogIf( Log &, LogLeve::Level )

    Log t( fn, LogLevel::Error | LogLevel::Info | LogLevel::Test,
	   true, false, ios::out );

    LogIf( t, LogLevel::Warn ) << "warn BAD\n";
    LogIf( t, LogLevel::Err ) << "error good\n";
    LogIf( t, LogLevel::Debug ) << "debug BAD\n";
    LogIf( t, LogLevel::Test ) << "test good\n";
    LogIf( t, LogLevel::Funct ) << "funct BAD\n";
    LogIf( t, LogLevel::Info ) << "info good\n";
  }

  {
    tester.file( __FILE__, __LINE__, fn );
  }
#endif
  return( true );
}

    
  
      
      
    
    

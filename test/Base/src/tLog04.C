#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Log.hh>
#include <FileStat.hh>
#include <fstream>
#include <cstdio>
#else
#include <TestCfg.hh>
#include <LibTest.hh>
#include <Log.hh>
#include <FileStat.hh>
#include <fstream>
#include <cstdio>
#endif


bool
tLog04( LibTest & tester )
{
  const char * fn = "data/logfile.05";

  remove( fn );
    
  {
    // tee( ostream & )

    ofstream tfile( "data/logfile.05.tee" );
    
    Log t( fn, LogLevel::Error, true, false );


    t.tee( tfile );

    t( LogLevel::Warn ) << "BAD\n";

    for( int l = 0; l < 50; l++ )
      t( LogLevel::Error ) << "good line: " << l << '\n';

  }

  {
    tester.file( __FILE__, __LINE__, fn );
    tester.file( __FILE__, __LINE__, "data/logfile.05.tee" );
  }

  fn = "data/logfile.06";
  remove( fn );
      
  {
    // trim( size_t );

    Log t( fn, LogLevel::Test, true, false );

    for( int l = 0; l < 1000; l++ )
      t( LogLevel::Test ) << "good line: " << l << '\n';


    t.trim( 10240 );

  }

  {
    
    FileStat t( fn );

    size_t lineLen = strlen( "TEST good line: 000\n" );
    
    TEST( (size_t) t.getSize() > ( (10240 / 4) - lineLen ) &&
	  (size_t) t.getSize() < ( ( 10240 - ( 10240 / 4 ) ) + lineLen ));
  }

  {
    // trim( void )

    Log t( fn, LogLevel::Test, true, false, ios::app, 0660, 10240 );

    for( int l = 0; l < 50; l++ )
      t( LogLevel::Test ) << "good line: " << l << '\n';

    t.trim();
  }

  {
    
    FileStat t( fn );

    size_t lineLen = strlen( "TEST good line: 000\n" );
    
    TEST( (size_t) t.getSize() > ( (10240 / 4) - lineLen ) &&
	  (size_t) t.getSize() < ( ( 10240 - ( 10240 / 4 ) ) + lineLen ));
  }


  {
    // setMaxSize( void )
    // setTrimSize( void )
    
    Log t( fn, LogLevel::Test, true, false );

    t.setTrimSize( 1024 );
    t.setMaxSize( 8192 );

    for( int l = 0; l < 50; l++ )
      t( LogLevel::Test ) << "good line: " << l << '\n';

  }

  {
    
    FileStat t( fn );

    size_t lineLen = strlen( "TEST good line: 000\n" );
    
    TEST( (size_t) t.getSize() > ( (8192 - 1024) - lineLen ) &&
	  t.getSize() <  8192 );
  }
 
  return( true );
}
  

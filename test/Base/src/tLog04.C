#include <LibTest.hh>
#include <Log.hh>

#include <FileStat.hh>

#include <fstream>
#include <cstdio>

bool
tLog04( LibTest & test )
{
  const char * fn = "data/logfile.05";

  remove( fn );
    
  {
    // tee( ostream & )

    ofstream tfile( "data/logfile.05.tee" );
    
    Log t( fn, LogLevel::ERROR, true, false );


    t.tee( tfile );

    t( LogLevel::WARN ) << "BAD\n";

    for( int l = 0; l < 50; l++ )
      t( LogLevel::ERROR ) << "good line: " << l << '\n';

  }

  {
    test.file( fn );
    test.file( "data/logfile.05.tee" );
  }

  fn = "data/logfile.06";
  remove( fn );
      
  {
    // trim( size_t );

    Log t( fn, LogLevel::TEST, true, false );

    for( int l = 0; l < 1000; l++ )
      t( LogLevel::TEST ) << "good line: " << l << '\n';


    t.trim( 10240 );

  }

  {
    
    FileStat t( fn );

    size_t lineLen = strlen( "TEST good line: 000\n" );
    
    test( (size_t) t.getSize() > ( (10240 / 4) - lineLen ) &&
	  (size_t) t.getSize() < ( ( 10240 - ( 10240 / 4 ) ) + lineLen ));
  }

  {
    // trim( void )

    Log t( fn, LogLevel::TEST, true, false, ios::app, 0660, 10240 );

    for( int l = 0; l < 50; l++ )
      t( LogLevel::TEST ) << "good line: " << l << '\n';

    t.trim();
  }

  {
    
    FileStat t( fn );

    size_t lineLen = strlen( "TEST good line: 000\n" );
    
    test( (size_t) t.getSize() > ( (10240 / 4) - lineLen ) &&
	  (size_t) t.getSize() < ( ( 10240 - ( 10240 / 4 ) ) + lineLen ));
  }


  {
    // setMaxSize( void )
    // setTrimSize( void )
    
    Log t( fn, LogLevel::TEST, true, false );

    t.setTrimSize( 1024 );
    t.setMaxSize( 8192 );

    for( int l = 0; l < 50; l++ )
      t( LogLevel::TEST ) << "good line: " << l << '\n';

  }

  {
    
    FileStat t( fn );

    size_t lineLen = strlen( "TEST good line: 000\n" );
    
    test( (size_t) t.getSize() > ( (8192 - 1024) - lineLen ) &&
	  t.getSize() <  8192 );
  }
 
  return( true );
}
  

#include <LibTest.hh>
#include <LogLevel.hh>
#include <Compare.hh>

#include <strstream>

bool
tLogLevel( LibTest & test )
{
  {
    // LogLevel( void )
    // getCurrent( void ) const
    // getOutput( void ) const
    
    LogLevel t;

    test( t.getCurrent() == LogLevel::ERROR );
    test( t.getOutput() == LogLevel::NONE );
    
  }

  {
    // LogLevel( const Level )

    LogLevel t( LogLevel::INFO );

    test( t.getCurrent() == LogLevel::ERROR );
    test( t.getOutput() == LogLevel::INFO );
  }

  {
    
    LogLevel t( LogLevel::INFO | LogLevel::TEST);

    test( t.getCurrent() == LogLevel::ERROR );
    test( t.getOutput() == ( LogLevel::INFO | LogLevel::TEST ) );
  }

  {
    // LogLevel( const char * )
    // willOutput( void );
    
    LogLevel t( "ERROR | WARNING " );
    
    test( t.getCurrent() == LogLevel::ERROR );
    test( t.getOutput() == ( LogLevel::ERROR | LogLevel::WARNING ) );
    test( t.willOutput( LogLevel::ERR ) );
    test( t.willOutput( LogLevel::WARN ) );
    test( ! (t.willOutput( LogLevel::INFO ) ) );
  }

  {
    // setOutput( const Level )

    LogLevel t( LogLevel::DEBUG );

    test( t.willOutput( LogLevel::DEBUG ) );
    test( ! t.willOutput( LogLevel::ERROR ) );

    t.setOutput( LogLevel::TEST | LogLevel::INFO );
    test( t.willOutput( LogLevel::TEST ) );
    test( t.willOutput( LogLevel::INFO ) );
    test( ! t.willOutput( LogLevel::DEBUG ) );
  }

  {
    // setOutput( const char * out )

    LogLevel t;

    t.setOutput( "TEST | INFO" );
    test( t.willOutput( LogLevel::TEST ) );
    test( t.willOutput( LogLevel::INFO ) );
    test( ! t.willOutput( LogLevel::DEBUG ) );
  }

  {
    // setCurrent( const Level );
    // shouldOutput( void ) const;
    
    LogLevel t( LogLevel::DEBUG | LogLevel::WARN );

    t.setCurrent( LogLevel::TEST );
    test( ! t.shouldOutput() );
    t.setCurrent( LogLevel::DEBUG );
    test( t.shouldOutput() );
    t.setCurrent( LogLevel::WARN );
    test( t.shouldOutput() );
    t.setCurrent( LogLevel::ERROR );
    test( ! t.shouldOutput() );
  }

  {
    // getCurrent( void ) const

    LogLevel t;

    t.setCurrent( LogLevel::DEBUG );
    test( t.getCurrent() == LogLevel::DEBUG );
    test( t.getCurrent() != LogLevel::ERROR );
  }

  {
    // getName( const Level )

    const LogLevel t;

    test( compare( t.getName( LogLevel::NONE ), "NONE" ) == 0 );
    test( compare( t.getName( LogLevel::WARN ), "WARNING" ) == 0 );
    test( compare( t.getName( LogLevel::TEST ), "TEST" ) == 0 );
    test( compare( t.getName( LogLevel::ALL ),  "ALL" ) == 0 );
  }

  {
    // getLevelNames( void ) const

    const LogLevel t;

    test( compare( t.getLevelNames( LogLevel::WARN |
				    LogLevel::DEBUG |
				    LogLevel::INFO ),
		   "WARNING | INFO | DEBUG" ) == 0 );
  }

  {
    // setName( Level )

    LogLevel t;

    t.setName( LogLevel::USER_2, "U2 Name" );
    test( compare( t.getName( LogLevel::USER_1 ), "USER 1" ) == 0 );
    test( compare( t.getName( LogLevel::USER_2 ), "U2 Name" ) == 0 );
  }

  {
    // getClassName( void ) const
    // dumpInfo( ostream & ) const
    // version
    
    const LogLevel t;

    strstream tStream;

    test( t.getClassName() != 0 );
    t.dumpInfo( tStream );
    test( t.version != 0 );
  }
  
  return( true );
}

  







#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <HeapBinStream.hh>
#include <LogLevel.hh>
#include <Compare.hh>
#include <strstream>
#else
#include <TestCfg.hh>
#include <LibTest.hh>
#include <HBinStrm.hh>
#include <LogLvl.hh>
#include <Compare.hh>
#include <strstream>
#endif


bool
tLogLevel( LibTest & tester )
{
  {
    // LogLevel( void )
    // getCurrent( void ) const
    // getOutput( void ) const
    
    LogLevel t;

    TEST( t.getCurrent() == LogLevel::ERROR );
    TEST( t.getOutput() == LogLevel::NONE );
    
  }

  {
    // LogLevel( const Level )

    LogLevel t( LogLevel::INFO );

    TEST( t.getCurrent() == LogLevel::ERROR );
    TEST( t.getOutput() == LogLevel::INFO );
  }

  {
    
    LogLevel t( LogLevel::INFO | LogLevel::TEST);

    TEST( t.getCurrent() == LogLevel::ERROR );
    TEST( t.getOutput() == ( LogLevel::INFO | LogLevel::TEST ) );
  }

  {
    // LogLevel( const char * )
    // willOutput( void );
    
    LogLevel t( "ERROR | WARNING " );
    
    TEST( t.getCurrent() == LogLevel::ERROR );
    TEST( t.getOutput() == ( LogLevel::ERROR | LogLevel::WARNING ) );
    TEST( t.willOutput( LogLevel::ERR ) );
    TEST( t.willOutput( LogLevel::WARN ) );
    TEST( ! (t.willOutput( LogLevel::INFO ) ) );
  }

  {
    // setOutput( const Level )

    LogLevel t( LogLevel::DEBUG );

    TEST( t.willOutput( LogLevel::DEBUG ) );
    TEST( ! t.willOutput( LogLevel::ERROR ) );

    t.setOutput( LogLevel::TEST | LogLevel::INFO );
    TEST( t.willOutput( LogLevel::TEST ) );
    TEST( t.willOutput( LogLevel::INFO ) );
    TEST( ! t.willOutput( LogLevel::DEBUG ) );
  }

  {
    // setOutput( const char * out )

    LogLevel t;

    t.setOutput( "TEST | INFO" );
    TEST( t.willOutput( LogLevel::TEST ) );
    TEST( t.willOutput( LogLevel::INFO ) );
    TEST( ! t.willOutput( LogLevel::DEBUG ) );
  }

  {
    // setCurrent( const Level );
    // shouldOutput( void ) const;
    
    LogLevel t( LogLevel::DEBUG | LogLevel::WARN );

    t.setCurrent( LogLevel::TEST );
    TEST( ! t.shouldOutput() );
    t.setCurrent( LogLevel::DEBUG );
    TEST( t.shouldOutput() );
    t.setCurrent( LogLevel::WARN );
    TEST( t.shouldOutput() );
    t.setCurrent( LogLevel::ERROR );
    TEST( ! t.shouldOutput() );
  }

  {
    // getCurrent( void ) const

    LogLevel t;

    t.setCurrent( LogLevel::DEBUG );
    TEST( t.getCurrent() == LogLevel::DEBUG );
    TEST( t.getCurrent() != LogLevel::ERROR );
  }

  {
    // getName( const Level )

    const LogLevel t;

    TEST( compare( t.getName( LogLevel::NONE ), "NONE" ) == 0 );
    TEST( compare( t.getName( LogLevel::WARN ), "WARNING" ) == 0 );
    TEST( compare( t.getName( LogLevel::TEST ), "TEST" ) == 0 );
    TEST( compare( t.getName( LogLevel::ALL ),  "ALL" ) == 0 );
  }

  {
    // getLevelNames( void ) const

    const LogLevel t;

    TEST( compare( t.getLevelNames( LogLevel::WARN |
				    LogLevel::DEBUG |
				    LogLevel::INFO ),
		   "WARNING | INFO | DEBUG" ) == 0 );
  }

  {
    // setName( Level )

    LogLevel t;

    t.setName( LogLevel::USER_2, "U2 Name" );
    TEST( compare( t.getName( LogLevel::USER_1 ), "USER 1" ) == 0 );
    TEST( compare( t.getName( LogLevel::USER_2 ), "U2 Name" ) == 0 );
  }

  {
    // getBinSize( void ) const
    // write( BinStream & dest ) const
    // read( BinStream & src )
    // BinStream::write( const BinObject & obj )
    // BinStream::read( BinObject & obj )

    HeapBinStream tStrm;

    const LogLevel  tw( LogLevel::DEBUG | LogLevel::WARN );
    LogLevel	    tr;

    TEST( tw.getBinSize() );

    tw.write( tStrm );
    tr.read( tStrm );

    TEST( tStrm.good() );
    TEST( (size_t)tStrm.tellp() == tw.getBinSize() );
    TEST( tStrm.tellg() == tStrm.tellp() );
    TEST( tr.getBinSize() == tw.getBinSize() );
    TEST( tw == tr );

    tr.setCurrent( LogLevel::INFO );
    tr.setOutput( LogLevel::INFO );
    
    TEST( tw != tr );
    
    tStrm.write( tw );
    tStrm.read( tr );

    TEST( tr == tw );
  }

  {
    // write( ostream & ) const
    // read( istream & )

    const LogLevel  tw( LogLevel::DEBUG | LogLevel::WARN );
    LogLevel	    tr;

    strstream tStrm;

    streampos gpos = tStrm.tellg();
    streampos ppos = tStrm.tellp();

#ifdef AIX
    ppos = 0;
    gpos = 0;
#endif
    
    TEST( ppos == 0 );
    TEST( gpos == 0 );
    
    tw.write( tStrm );
    ppos += tw.getBinSize();
    TEST( ppos == tStrm.tellp() );
      
    tr.read( tStrm );
    gpos += tr.getBinSize();
    TEST( gpos == tStrm.tellg() );
    TEST( tr == tw );
  }

  {
    // toStream( ostream & ) const
    // operator << ( ostream &, const FilePath & )

    const LogLevel  t( LogLevel::DEBUG | LogLevel::WARN );
    strstream tStrm;

    t.toStream( tStrm );
    tStrm << t;
  }
    
  {
    // getClassName( void ) const
    // getVersion( void ) const
    // getVersion( bool ) const

    const LogLevel  t( LogLevel::DEBUG | LogLevel::WARN );

    TEST( t.getClassName() != 0 );
    TEST( t.getVersion() != 0 );
    TEST( t.getVersion( false ) != 0 );
    
  }

  {
    // dumpInfo( ostream & ) const
    // version

    const LogLevel  t( LogLevel::DEBUG | LogLevel::WARN );

    tester.getDump() << '\n' << t.getClassName() << " toStream:\n";
    t.toStream( tester.getDump() );
    tester.getDump() << '\n' << t.getClassName() << " dumpInfo:\n";
    t.dumpInfo( tester.getDump(), " -> ", true );
    tester.getDump() << '\n' << t.getClassName() << " version:\n";
    tester.getDump() << t.version;
    
    tester.getDump() << '\n' << tester.getCurrentTestName();
    
  }
    
  return( true );
}

  







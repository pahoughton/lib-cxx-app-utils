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

    TEST( t.getCurrent() == LogLevel::Error );
    TEST( t.getOutput() == LogLevel::None );
    
  }

  {
    // LogLevel( const Level )

    LogLevel t( LogLevel::Info );

    TEST( t.getCurrent() == LogLevel::Error );
    TEST( t.getOutput() == LogLevel::Info );
  }

  {
    
    LogLevel t( LogLevel::Info | LogLevel::Test);

    TEST( t.getCurrent() == LogLevel::Error );
    TEST( t.getOutput() == ( LogLevel::Info | LogLevel::Test ) );
  }

  {
    // LogLevel( const char * ) - upper case
    // willOutput( void );
    
    LogLevel t( "ERROR | WARNING " );
    
    TEST( t.getCurrent() == LogLevel::Error );
    TEST( t.getOutput() == ( LogLevel::Error | LogLevel::Warning ) );
    TEST( t.willOutput( LogLevel::Err ) );
    TEST( t.willOutput( LogLevel::Warn ) );
    TEST( ! (t.willOutput( LogLevel::Info ) ) );
  }

  {
    // LogLevel( const char * ) - lower/Mixed case
    // willOutput( void );
    
    LogLevel t( "error | Warning " );
    
    TEST( t.getCurrent() == LogLevel::Error );
    TEST( t.getOutput() == ( LogLevel::Error | LogLevel::Warning ) );
    TEST( t.willOutput( LogLevel::Err ) );
    TEST( t.willOutput( LogLevel::Warn ) );
    TEST( ! (t.willOutput( LogLevel::Info ) ) );
  }

  {
    // setOutput( const Level )

    LogLevel t( LogLevel::Debug );

    TEST( t.willOutput( LogLevel::Debug ) );
    TEST( ! t.willOutput( LogLevel::Error ) );

    t.setOutput( LogLevel::Test | LogLevel::Info );
    TEST( t.willOutput( LogLevel::Test ) );
    TEST( t.willOutput( LogLevel::Info ) );
    TEST( ! t.willOutput( LogLevel::Debug ) );
    t.setOutput( LogLevel::All );
    TEST( t.willOutput( LogLevel::Error ) );
    TEST( t.willOutput( LogLevel::Err ) );
    TEST( t.willOutput( LogLevel::Warning ) );
    TEST( t.willOutput( LogLevel::Warn ) );
    TEST( t.willOutput( LogLevel::App1 ) );
    TEST( t.willOutput( LogLevel::App2 ) );
    TEST( t.willOutput( LogLevel::App3 ) );
    TEST( t.willOutput( LogLevel::App4 ) );
    TEST( t.willOutput( LogLevel::App5 ) );
    TEST( t.willOutput( LogLevel::App6 ) );
    TEST( t.willOutput( LogLevel::Lib1 ) );
    TEST( t.willOutput( LogLevel::Lib2 ) );
    TEST( t.willOutput( LogLevel::Lib3 ) );
    TEST( t.willOutput( LogLevel::Lib4 ) );
    TEST( t.willOutput( LogLevel::Info ) );
    TEST( t.willOutput( LogLevel::Test ) );
    TEST( t.willOutput( LogLevel::Debug ) );
    TEST( t.willOutput( LogLevel::Funct ) );
  }

  {
    // setOutput( const char * out )

    LogLevel t;

    t.setOutput( "TEST | INFO" );
    TEST( t.willOutput( LogLevel::Test ) );
    TEST( t.willOutput( LogLevel::Info ) );
    TEST( ! t.willOutput( LogLevel::Debug ) );
    t.setOutput( "ALL" );
    TEST( t.willOutput( LogLevel::Error ) );
    TEST( t.willOutput( LogLevel::Err ) );
    TEST( t.willOutput( LogLevel::Warning ) );
    TEST( t.willOutput( LogLevel::Warn ) );
    TEST( t.willOutput( LogLevel::App1 ) );
    TEST( t.willOutput( LogLevel::App2 ) );
    TEST( t.willOutput( LogLevel::App3 ) );
    TEST( t.willOutput( LogLevel::App4 ) );
    TEST( t.willOutput( LogLevel::App5 ) );
    TEST( t.willOutput( LogLevel::App6 ) );
    TEST( t.willOutput( LogLevel::Lib1 ) );
    TEST( t.willOutput( LogLevel::Lib2 ) );
    TEST( t.willOutput( LogLevel::Lib3 ) );
    TEST( t.willOutput( LogLevel::Lib4 ) );
    TEST( t.willOutput( LogLevel::Info ) );
    TEST( t.willOutput( LogLevel::Test ) );
    TEST( t.willOutput( LogLevel::Debug ) );
    TEST( t.willOutput( LogLevel::Funct ) );
  }

  {
    // setOutput( const char * out ) - lower/mixed case

    LogLevel t;

    t.setOutput( "Test | info" );
    TEST( t.willOutput( LogLevel::Test ) );
    TEST( t.willOutput( LogLevel::Info ) );
    TEST( ! t.willOutput( LogLevel::Debug ) );
    t.setOutput( "AlL" );
    TEST( t.willOutput( LogLevel::Error ) );
    TEST( t.willOutput( LogLevel::Err ) );
    TEST( t.willOutput( LogLevel::Warning ) );
    TEST( t.willOutput( LogLevel::Warn ) );
    TEST( t.willOutput( LogLevel::App1 ) );
    TEST( t.willOutput( LogLevel::App2 ) );
    TEST( t.willOutput( LogLevel::App3 ) );
    TEST( t.willOutput( LogLevel::App4 ) );
    TEST( t.willOutput( LogLevel::App5 ) );
    TEST( t.willOutput( LogLevel::App6 ) );
    TEST( t.willOutput( LogLevel::Lib1 ) );
    TEST( t.willOutput( LogLevel::Lib2 ) );
    TEST( t.willOutput( LogLevel::Lib3 ) );
    TEST( t.willOutput( LogLevel::Lib4 ) );
    TEST( t.willOutput( LogLevel::Info ) );
    TEST( t.willOutput( LogLevel::Test ) );
    TEST( t.willOutput( LogLevel::Debug ) );
    TEST( t.willOutput( LogLevel::Funct ) );
  }

  {
    // setCurrent( const Level );
    // shouldOutput( void ) const;
    
    LogLevel t( LogLevel::Debug | LogLevel::Warn );

    t.setCurrent( LogLevel::Test );
    TEST( ! t.shouldOutput() );
    t.setCurrent( LogLevel::Debug );
    TEST( t.shouldOutput() );
    t.setCurrent( LogLevel::Warn );
    TEST( t.shouldOutput() );
    t.setCurrent( LogLevel::Error );
    TEST( ! t.shouldOutput() );
  }

  {
    // getCurrent( void ) const

    LogLevel t;

    t.setCurrent( LogLevel::Debug );
    TEST( t.getCurrent() == LogLevel::Debug );
    TEST( t.getCurrent() != LogLevel::Error );
  }

  {
    // getName( const Level )

    const LogLevel t;

    TEST( compare( t.getName( LogLevel::None ), "NONE" ) == 0 );
    TEST( compare( t.getName( LogLevel::Warn ), "WARNING" ) == 0 );
    TEST( compare( t.getName( LogLevel::Test ), "TEST" ) == 0 );
    TEST( compare( t.getName( LogLevel::All ),  "ALL" ) == 0 );
  }

  {
    // getLevelNames( void ) const

    const LogLevel t;

    TEST( compare( t.getLevelNames( LogLevel::Warn |
				    LogLevel::Debug |
				    LogLevel::Info ),
		   "WARNING | INFO | DEBUG" ) == 0 );
  }

  {
    // setName( Level )

    LogLevel t;

    t.setName( LogLevel::App2, "U2 Name" );
    TEST( compare( t.getName( LogLevel::App1 ), "APP1" ) == 0 );
    TEST( compare( t.getName( LogLevel::App2 ), "U2 Name" ) == 0 );
  }

  {
    // getBinSize( void ) const
    // write( BinStream & dest ) const
    // read( BinStream & src )
    // BinStream::write( const BinObject & obj )
    // BinStream::read( BinObject & obj )

    HeapBinStream tStrm;

    const LogLevel  tw( LogLevel::Debug | LogLevel::Warn );
    LogLevel	    tr;

    TEST( tw.getBinSize() );

    tw.write( tStrm );
    tr.read( tStrm );

    TEST( tStrm.good() );
    TEST( (size_t)tStrm.tellp() == tw.getBinSize() );
    TEST( tStrm.tellg() == tStrm.tellp() );
    TEST( tr.getBinSize() == tw.getBinSize() );
    TEST( tw == tr );

    tr.setCurrent( LogLevel::Info );
    tr.setOutput( LogLevel::Info );
    
    TEST( tw != tr );
    
    tStrm.write( tw );
    tStrm.read( tr );

    TEST( tr == tw );
  }

  {
    // write( ostream & ) const
    // read( istream & )

    const LogLevel  tw( LogLevel::Debug | LogLevel::Warn );
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

    const LogLevel  t( LogLevel::Debug | LogLevel::Warn );
    strstream tStrm;

    t.toStream( tStrm );
    tStrm << t;
  }
    
  {
    // getClassName( void ) const
    // getVersion( void ) const
    // getVersion( bool ) const

    const LogLevel  t( LogLevel::Debug | LogLevel::Warn );

    TEST( t.getClassName() != 0 );
    TEST( t.getVersion() != 0 );
    TEST( t.getVersion( false ) != 0 );
    
  }

  {
    // dumpInfo( ostream & ) const
    // version

    const LogLevel  t( LogLevel::Debug | LogLevel::Warn );

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

  







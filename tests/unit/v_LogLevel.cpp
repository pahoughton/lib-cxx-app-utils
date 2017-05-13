// 1996-10-31 (cc) <paul4hough@gmail.com>

#include <clue/LogLevel.hpp>
#include <sstream>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::LogLevel");
using namespace clue;

bool
v_LogLevel( void )
{
  {
    // static const Level	None;
    // static const Level	Error;
    // static const Level	Err;
    // static const Level	Warning;
    // static const Level	Warn;
    // static const Level	App1;
    // static const Level	App2;
    // static const Level	App3;
    // static const Level	App4;
    // static const Level	App5;
    // static const Level	App6;
    // static const Level	Lib1;
    // static const Level	Lib2;
    // static const Level	Lib3;
    // static const Level	Lib4;
    // static const Level	Info;
    // static const Level	Test;
    // static const Level	Debug;
    // static const Level	Funct;
    // static const Level	All;

    TEST( LogLevel::None.none() );
    TEST( LogLevel::Error.any() );
    TEST( LogLevel::Error ==  LogLevel::Err );
    TEST( LogLevel::Warning.any() );
    TEST( LogLevel::Warning ==  LogLevel::Warn );
    TEST( LogLevel::App1.any() );
    TEST( LogLevel::App2.any() );
    TEST( LogLevel::App3.any() );
    TEST( LogLevel::App4.any() );
    TEST( LogLevel::App5.any() );
    TEST( LogLevel::App6.any() );
    TEST( LogLevel::Lib1.any() );
    TEST( LogLevel::Lib2.any() );
    TEST( LogLevel::Lib3.any() );
    TEST( LogLevel::Lib4.any() );
    TEST( LogLevel::Info.any() );
    TEST( LogLevel::Test.any() );
    TEST( LogLevel::Debug.any() );
    TEST( LogLevel::Funct.any() );
    TEST( LogLevel::All.any() );

  }

  {
    // LogLevel( void )
    // getOutput( void ) const
    // getCurrent( void ) const

    LogLevel	t;

    TEST( t.getOutput() == LogLevel::None );
    TEST( t.getCurrent() == LogLevel::Error );
  }

  {
    // LogLevel( const Level )

    {
      LogLevel	t( LogLevel::Error );

      TEST( t.getOutput() == LogLevel::Error );
    }


    {
      LogLevel t( LogLevel::Info | LogLevel::Test);

      TEST( t.getCurrent() == LogLevel::Error );
      TEST( t.getOutput() == ( LogLevel::Info | LogLevel::Test ) );
    }
  }

  {
    // LogLevel( const Level, const Level )

    LogLevel t( LogLevel::All, LogLevel::Debug );

    TEST( t.getOutput() == LogLevel::All );
    TEST( t.getCurrent() == LogLevel::Debug );
  }

  {
    // LogLevel( const char * )
    {
      // upper case

      LogLevel t( "ERROR | WARNING " );

      TEST( t.getCurrent() == LogLevel::Error );
      TEST( t.getOutput() == ( LogLevel::Error | LogLevel::Warning ) );

    }

    {
      // lower/Mixed case

      LogLevel t( "error | Warning " );

      TEST( t.getCurrent() == LogLevel::Error );
      TEST( t.getOutput() == ( LogLevel::Error | LogLevel::Warning ) );
    }

    {
      // err, warn abbrev

      LogLevel t( "err|WARN " );

      TEST( t.getCurrent() == LogLevel::Error );
      TEST( t.getOutput() == ( LogLevel::Error | LogLevel::Warning ) );
    }
  }

  {
    // LogLevel( const LogLevel & )

    const LogLevel s( LogLevel::Info, LogLevel::Info );
    LogLevel t( s );

    TEST( t.getCurrent() == LogLevel::Info );
    TEST( t.getOutput() == LogLevel::Info );
  }

  {
    // setOutput( const Level )

    LogLevel t( LogLevel::Debug );

    t.setOutput( LogLevel::Test | LogLevel::Info );
    TEST( t.getOutput() == (LogLevel::Test | LogLevel::Info ) );

    t.setOutput( LogLevel::All );
    TEST( t.getOutput() == LogLevel::All );
  }

  {
    // setOutput( const char * out )

    {
      LogLevel t;

      t.setOutput( "TEST | INFO" );
      TEST( t.getOutput() == (LogLevel::Test | LogLevel::Info ) );

      t.setOutput( "ALL" );
      TEST( t.getOutput() == LogLevel::All );

      t.setOutput( "err" );
      TEST( t.getOutput() == LogLevel::Error );

      t.setOutput( "warn" );
      TEST( t.getOutput() == LogLevel::Warning );

      t.setOutput( "err| Info | Debug|test|Warning" );
      TEST( t.getOutput() == (LogLevel::Error |
			      LogLevel::Info |
			      LogLevel::Debug |
			      LogLevel::Test |
			      LogLevel::Warning ) );
    }

    {
      LogLevel	t;

      t.setOutput( "TEST | INFO" );
      TEST( t.getOutput() == (LogLevel::Test | LogLevel::Info ) );

      t.setOutput( "+debug | err | -INFO" );
      TEST( t.getOutput() == (LogLevel::Test |
			       LogLevel::Err |
			       LogLevel::Debug ) );

      t.setOutput( "+info" );
      TEST( t.getOutput() == (LogLevel::Test |
			      LogLevel::Err |
			      LogLevel::Debug |
			      LogLevel::Info ) );

      t.setOutput( "-debug" );
      TEST( t.getOutput() == (LogLevel::Test |
			      LogLevel::Err |
			      LogLevel::Info ) );

      t.setOutput( "funct" );
      TEST( t.getOutput() == (LogLevel::Funct ) );
    }

  }


  {
    // setCurrent( const Level );

    LogLevel t( LogLevel::Debug );

    t.setCurrent( LogLevel::Test | LogLevel::Info );
    TEST( t.getCurrent() == (LogLevel::Test | LogLevel::Info ) );

    t.setCurrent( LogLevel::All );
    TEST( t.getCurrent() == LogLevel::All );
  }

  {
    // setCurrent( const char * out )

    LogLevel t;

    t.setCurrent( "TEST | INFO" );
    TEST( t.getCurrent() == (LogLevel::Test | LogLevel::Info ) );

    t.setCurrent( "ALL" );
    TEST( t.getCurrent() == LogLevel::All );

    t.setCurrent( "err" );
    TEST( t.getCurrent() == LogLevel::Error );

    t.setCurrent( "warn" );
    TEST( t.getCurrent() == LogLevel::Warning );

    t.setCurrent( "err| App1 | Lib1|test|Warning" );
    TEST( t.getCurrent() == (LogLevel::Error |
			     LogLevel::App1 |
			     LogLevel::Lib1 |
			     LogLevel::Test |
			     LogLevel::Warning ) );
  }

  {
    // getOuptut( void ) const
    // getCurrent( void ) const

    const LogLevel	t;

    TEST( t.getOutput() == LogLevel::None );
    TEST( t.getCurrent() == LogLevel::Error );
  }

  {
    // getName( const Level )

    TEST( compare( LogLevel::getName( LogLevel::None ), "NONE" ) == 0 );
    TEST( compare( LogLevel::getName( LogLevel::Warn ), "WARNING" ) == 0 );
    TEST( compare( LogLevel::getName( LogLevel::Test ), "TEST" ) == 0 );
    TEST( compare( LogLevel::getName( LogLevel::All ),  "ALL" ) == 0 );
    TEST( compare( LogLevel::getName( LogLevel::Debug | LogLevel::Warn ),
		   "WARNING" ) == 0 );
  }

  {
    // getLevelNames( void ) const

    TEST( compare( LogLevel::getLevelNames( LogLevel::App1 ), "APP1" ) == 0 );
    TEST( compare( LogLevel::getLevelNames( LogLevel::Warn |
				    LogLevel::Debug |
				    LogLevel::Info ),
		   "WARNING | INFO | DEBUG" ) == 0 );
  }

  {
    // setName( Level )

    LogLevel::setName( LogLevel::App2, "U2 Name" );
    {
      LogLevel t;

      TEST( compare( t.getName( LogLevel::App1 ), "APP1" ) == 0 );
      TEST( compare( t.getName( LogLevel::App2 ), "U2 Name" ) == 0 );
      TEST( compare( t.getName( LogLevel::App3 ), "APP3" ) == 0 );

      t.setOutput( "Warn | U2 Name | Debug" );
      TEST( t.getOutput() ==
	    ( LogLevel::Warn | LogLevel::App2 | LogLevel::Debug ) );

      t.setCurrent( "U2 Name" );
      TEST( t.getCurrent() == LogLevel::App2 );
    }

    {
      LogLevel t("u2 name | Debug");

      TEST( t.getOutput() == (LogLevel::App2 | LogLevel::Debug) );
    }
    {
      TEST( compare( LogLevel::getLevelNames( LogLevel::App2 |
					      LogLevel::Debug ),
		     "U2 Name | DEBUG" ) == 0 );
    }

    {
      // ok now change it back
      LogLevel t;

      t.setName( LogLevel::App2, "APP2" );
      TEST( compare( t.getName( LogLevel::App2 ), "APP2" ) == 0 );
    }
  }

  {
    // shouldOutput( void ) const;

    LogLevel t( LogLevel::Debug | LogLevel::Warn );

    t.setCurrent( LogLevel::Error );
    TEST( ! t.shouldOutput() );

    t.setCurrent( LogLevel::Err );
    TEST( ! t.shouldOutput() );

    t.setCurrent( LogLevel::Warning );
    TEST( t.shouldOutput() );

    t.setCurrent( LogLevel::Warn );
    TEST( t.shouldOutput() );

    t.setCurrent( LogLevel::App1 );
    TEST( ! t.shouldOutput() );

    t.setCurrent( LogLevel::App2 );
    TEST( ! t.shouldOutput() );

    t.setCurrent( LogLevel::App3 );
    TEST( ! t.shouldOutput() );

    t.setCurrent( LogLevel::App4 );
    TEST( ! t.shouldOutput() );

    t.setCurrent( LogLevel::App5 );
    TEST( ! t.shouldOutput() );

    t.setCurrent( LogLevel::App6 );
    TEST( ! t.shouldOutput() );

    t.setCurrent( LogLevel::Lib1 );
    TEST( ! t.shouldOutput() );

    t.setCurrent( LogLevel::Lib2 );
    TEST( ! t.shouldOutput() );

    t.setCurrent( LogLevel::Lib3 );
    TEST( ! t.shouldOutput() );

    t.setCurrent( LogLevel::Lib4 );
    TEST( ! t.shouldOutput() );

    t.setCurrent( LogLevel::Info );
    TEST( ! t.shouldOutput() );

    t.setCurrent( LogLevel::Test );
    TEST( ! t.shouldOutput() );

    t.setCurrent( LogLevel::Debug );
    TEST( t.shouldOutput() );

    t.setCurrent( LogLevel::Funct );
    TEST( ! t.shouldOutput() );
  }

  {
    // willOutput( const Level curLevel ) const

    LogLevel t( LogLevel::None );

    TEST( ! t.willOutput( LogLevel::Error ) );
    TEST( ! t.willOutput( LogLevel::Err ) );
    TEST( ! t.willOutput( LogLevel::Warning ) );
    TEST( ! t.willOutput( LogLevel::Warn ) );
    TEST( ! t.willOutput( LogLevel::App1 ) );
    TEST( ! t.willOutput( LogLevel::App2 ) );
    TEST( ! t.willOutput( LogLevel::App3 ) );
    TEST( ! t.willOutput( LogLevel::App4 ) );
    TEST( ! t.willOutput( LogLevel::App5 ) );
    TEST( ! t.willOutput( LogLevel::App6 ) );
    TEST( ! t.willOutput( LogLevel::Lib1 ) );
    TEST( ! t.willOutput( LogLevel::Lib2 ) );
    TEST( ! t.willOutput( LogLevel::Lib3 ) );
    TEST( ! t.willOutput( LogLevel::Lib4 ) );
    TEST( ! t.willOutput( LogLevel::Info ) );
    TEST( ! t.willOutput( LogLevel::Test ) );
    TEST( ! t.willOutput( LogLevel::Debug ) );
    TEST( ! t.willOutput( LogLevel::Funct ) );

    t.setOutput( LogLevel::Warn | LogLevel::Lib1 | LogLevel::Test );

    TEST( ! t.willOutput( LogLevel::Error ) );
    TEST( ! t.willOutput( LogLevel::Err ) );
    TEST( t.willOutput( LogLevel::Warning ) );
    TEST( t.willOutput( LogLevel::Warn ) );
    TEST( ! t.willOutput( LogLevel::App1 ) );
    TEST( ! t.willOutput( LogLevel::App2 ) );
    TEST( ! t.willOutput( LogLevel::App3 ) );
    TEST( ! t.willOutput( LogLevel::App4 ) );
    TEST( ! t.willOutput( LogLevel::App5 ) );
    TEST( ! t.willOutput( LogLevel::App6 ) );
    TEST( t.willOutput( LogLevel::Lib1 ) );
    TEST( ! t.willOutput( LogLevel::Lib2 ) );
    TEST( ! t.willOutput( LogLevel::Lib3 ) );
    TEST( ! t.willOutput( LogLevel::Lib4 ) );
    TEST( ! t.willOutput( LogLevel::Info ) );
    TEST( t.willOutput( LogLevel::Test ) );
    TEST( ! t.willOutput( LogLevel::Debug ) );
    TEST( ! t.willOutput( LogLevel::Funct ) );

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
    // compare( const LogLevel & two ) const

    const LogLevel  t( LogLevel::Warn | LogLevel::Test,
		       LogLevel::Lib1 );

    {
      const LogLevel te( t );
      const LogLevel tl( LogLevel::Warn | LogLevel::Test,
			 LogLevel::App6 );
      const LogLevel tm( LogLevel::Warn | LogLevel::Test,
			 LogLevel::Lib2 );

      TEST( t.compare( te ) == 0 );
      TEST( t.compare( tl ) >  0 );
      TEST( t.compare( tm ) <  0 );
    }

    {
      const LogLevel tl( LogLevel::Test,
			 LogLevel::Lib1 );
      const LogLevel tm( LogLevel::Warn | LogLevel::Test | LogLevel::Err,
			 LogLevel::Lib1 );

      TEST( t.compare( tl ) >  0 );
      TEST( t.compare( tm ) <  0 );
    }
  }

  {
    // operator = ( const LogLevel & )

    const LogLevel  s( LogLevel::Warn | LogLevel::Test,
		       LogLevel::Lib1 );

    LogLevel t;

    TEST( t.compare( s ) != 0 );
    t = s;
    TEST( t.compare( s ) == 0 );
  }

  {
    // operator == ( const LogLevel & ) const
    // operator != ( const LogLevel & ) const
    // operator <  ( const LogLevel & ) const
    // operator <= ( const LogLevel & ) const
    // operator >  ( const LogLevel & ) const
    // operator >= ( const LogLevel & ) const

    const LogLevel  t( LogLevel::Warn | LogLevel::Test,
		       LogLevel::Lib1 );

    const LogLevel te( t );
    const LogLevel tl( LogLevel::Warn | LogLevel::Test,
		       LogLevel::App6 );
    const LogLevel tm( LogLevel::Warn | LogLevel::Test,
		       LogLevel::Lib2 );

    TEST( t == te );
    TEST( t != tl );
    TEST( t <  tm );
    TEST( t <= tm );
    TEST( t <= te );
    TEST( t >  tl );
    TEST( t >= tl );
    TEST( t >= te );
  }



  {
    // toStream( ostream & ) const

    const LogLevel  t( LogLevel::Debug | LogLevel::Warn,
		       LogLevel::Test );
    std::stringstream tStrm;

    t.toStream( tStrm ) << std::ends;

    TEST( compare( tStrm.str().c_str(), "TEST" ) == 0 );
  }

  {
    // ::operator << ( ostream & dest, const LogLevel obj )

    const LogLevel  t( LogLevel::Error | LogLevel::Warn,
		       LogLevel::Warn );
    std::stringstream tStrm;

    tStrm << t << std::ends;

    TEST( compare( tStrm.str().c_str(), "WARNING" ) == 0 );

  }

  return( verify.is_valid() );
}

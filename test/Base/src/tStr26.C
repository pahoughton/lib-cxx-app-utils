#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#else
#include <TestCfg.hh>
#include <LibTest.hh>
#include <Str.hh>
#endif

bool
tStr26( LibTest & tester )
{
  {
    // StringToBool( const Str & )

    Str     t;

    t << "0";
    TEST( ! StringToBool( t ) );
    
    t.assign( "01" );
    TEST( StringToBool( t ) );

    t.assign( "500" );
    TEST( StringToBool( t ) );

    t.assign( "T" );
    TEST( StringToBool( t ) );

    t.assign( "t" );
    TEST( StringToBool( t ) );

    t.assign( "F" );
    TEST( ! StringToBool( t ) );

    t.assign( "f" );
    TEST( ! StringToBool( t ) );

    t.assign( "true" );
    TEST( StringToBool( t ) );

    t.assign( "TRUE" );
    TEST( StringToBool( t ) );

    t.assign( "TrUe" );
    TEST( StringToBool( t ) );

    t.assign( "false" );
    TEST( ! StringToBool( t ) );

    t.assign( "FALSE" );
    TEST( ! StringToBool( t ) );

    t.assign( "FaLse" );
    TEST( ! StringToBool( t ) );

    t.assign( "y" );
    TEST( StringToBool( t ) );

    t.assign( "Y" );
    TEST( StringToBool( t ) );

    t.assign( "n" );
    TEST( ! StringToBool( t ) );

    t.assign( "N" );
    TEST( ! StringToBool( t ) );

    t.assign( "yes" );
    TEST( StringToBool( t ) );

    t.assign( "no" );
    TEST( ! StringToBool( t ) );

    t.assign( "on" );
    TEST( StringToBool( t ) );

    t.assign( "off" );
    TEST( ! StringToBool( t ) );

    t.assign( "ON" );
    TEST( StringToBool( t ) );

    t.assign( "OFF" );
    TEST( ! StringToBool( t ) );
  }

  {
    // StringToInt( const Str & )
    // StringToInt( const Str &, unsigned short )

    Str t;

    t.assign( "1150" );
    TEST( StringToInt( t ) == 1150 );

    t.assign( "0xfff" );
    TEST( StringToInt( t ) == 0xfff );

    t.assign( "-30" );
    TEST( StringToInt( t ) == -30 );

    t = "123";
    TEST( StringToInt( t, 16 ) == 0x123 );
  }
  
  {
    // StringToLong( const Str & )
    // StringToLong( const Str &, unsigned short )

    Str t;

    t.assign( "1123456" );
    TEST( StringToLong( t ) == 1123456L );

    t.assign( "-1123456" );
    TEST( StringToLong( t ) == -1123456L );

    t = "123";
    TEST( StringToLong( t, 16 ) == 0x123 );
  }

  {
    // StringToDouble( cosnt Str & )
    // StringToDouble( const Str &, unsigned short )

    Str t;

    t.assign( "15.15" );
    TEST( StringToDouble( t ) ==  15.15 );

    t = "10.1";
    TEST( StringToDouble( t, 8 ) == 8.125 );

  }

  {
    // StringToUInt( const Str & )
    // StringToUInt( const Str &, unsigned short )

    Str t;

    t.assign( "0xff0f" );
    TEST( StringToUInt( t ) == 0xff0f);

    t = "123";
    TEST( StringToUInt( t, 16 ) == 0x123 );
  }

  {
    // StringToULong( const Str & )
    // StringToULong( const Str &,  unsigned short )

    Str t;

    t.assign( "0xffff0000" );
    TEST( StringToULong( t ) == 0xffff0000L );

    t = "123";
    TEST( StringToULong( t, 16 ) == 0x123 );
  }

  return( true );
}
    

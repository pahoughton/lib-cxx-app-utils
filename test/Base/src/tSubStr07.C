#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#endif

bool
tSubStr07( LibTest & tester )
{
  {
    // StringToBool( const SubStr & )

    Str		ts( "A string for t to be a sub of" );
    SubStr      t( ts, 3, 5);

    t = "0";
    TEST( ! StringToBool( t ) );
    
    t = "01" ;
    TEST( StringToBool( t ) );

    t = "500" ;
    TEST( StringToBool( t ) );

    t = "T" ;
    TEST( StringToBool( t ) );

    t = "t" ;
    TEST( StringToBool( t ) );

    t = "F" ;
    TEST( ! StringToBool( t ) );

    t = "f" ;
    TEST( ! StringToBool( t ) );

    t = "true" ;
    TEST( StringToBool( t ) );

    t = "TRUE" ;
    TEST( StringToBool( t ) );

    t = "TrUe" ;
    TEST( StringToBool( t ) );

    t = "false" ;
    TEST( ! StringToBool( t ) );

    t = "FALSE" ;
    TEST( ! StringToBool( t ) );

    t = "FaLse" ;
    TEST( ! StringToBool( t ) );

    t = "y" ;
    TEST( StringToBool( t ) );

    t = "Y" ;
    TEST( StringToBool( t ) );

    t = "n" ;
    TEST( ! StringToBool( t ) );

    t = "N" ;
    TEST( ! StringToBool( t ) );

    t = "yes" ;
    TEST( StringToBool( t ) );

    t = "no" ;
    TEST( ! StringToBool( t ) );

    t = "on" ;
    TEST( StringToBool( t ) );

    t = "off" ;
    TEST( ! StringToBool( t ) );

    t = "ON" ;
    TEST( StringToBool( t ) );

    t = "OFF" ;
    TEST( ! StringToBool( t ) );
  }

  {
    // StringToInt( const SubStr & )
    // StringToInt( const SubStr &, unsigned short )

    Str		ts( "A string for t to be a sub of" );
    SubStr      t( ts, 3, 5);

    t = "1150" ;
    TEST( StringToInt( t ) == 1150 );

    t = "0xfff" ;
    TEST( StringToInt( t ) == 0xfff );

    t = "-30" ;
    TEST( StringToInt( t ) == -30 );

    t = "123";
    TEST( StringToInt( t, 16 ) == 0x123 );
  }
  
  {
    // StringToLong( const SubStr & )
    // StringToLong( const SubStr &, unsigned short )

    Str		ts( "A string for t to be a sub of" );
    SubStr      t( ts, 3, 5);

    t = "1123456" ;
    TEST( StringToLong( t ) == 1123456L );

    t = "-1123456" ;
    TEST( StringToLong( t ) == -1123456L );

    t = "123";
    TEST( StringToLong( t, 16 ) == 0x123L );
  }

  {
    // StringToDouble( cosnt Str & )
    // StringToDouble( const SubStr &, unsigned short )

    Str		ts( "A string for t to be a sub of" );
    SubStr      t( ts, 3, 5);

    t = "15.15" ;
    TEST( StringToDouble( t ) ==  15.15 );

    t = "10.1";
    TEST( StringToDouble( t, 8 ) == 8.125 );

  }

  {
    // StringToUInt( const SubStr & )
    // StringToUInt( const SubStr &, unsigned short )

    Str		ts( "A string for t to be a sub of" );
    SubStr      t( ts, 3, 5);

    t = "0xff0f" ;
    TEST( StringToUInt( t ) == 0xff0f);

    t = "123";
    TEST( StringToUInt( t, 16 ) == 0x123 );
  }

  {
    // StringToULong( const SubStr & )
    // StringToULong( const SubStr &,  unsigned short )

    Str		ts( "A string for t to be a sub of" );
    SubStr      t( ts, 3, 5);

    t = "0xffff0000" ;
    TEST( StringToULong( t ) == 0xffff0000L );

    t = "123";
    TEST( StringToULong( t, 16 ) == 0x123 );
  }

  return( true );
}
    

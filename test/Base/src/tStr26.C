#include <LibTest.hh>
#include <Str.hh>

bool
tStr26( LibTest & test )
{
  {
    // StringToBool( const Str & )

    Str     t;

    t << "0";
    test( ! StringToBool( t ) );
    
    t.assign( "01" );
    test( StringToBool( t ) );

    t.assign( "500" );
    test( StringToBool( t ) );

    t.assign( "T" );
    test( StringToBool( t ) );

    t.assign( "t" );
    test( StringToBool( t ) );

    t.assign( "F" );
    test( ! StringToBool( t ) );

    t.assign( "f" );
    test( ! StringToBool( t ) );

    t.assign( "true" );
    test( StringToBool( t ) );

    t.assign( "TRUE" );
    test( StringToBool( t ) );

    t.assign( "TrUe" );
    test( StringToBool( t ) );

    t.assign( "false" );
    test( ! StringToBool( t ) );

    t.assign( "FALSE" );
    test( ! StringToBool( t ) );

    t.assign( "FaLse" );
    test( ! StringToBool( t ) );

    t.assign( "y" );
    test( StringToBool( t ) );

    t.assign( "Y" );
    test( StringToBool( t ) );

    t.assign( "n" );
    test( ! StringToBool( t ) );

    t.assign( "N" );
    test( ! StringToBool( t ) );

    t.assign( "yes" );
    test( StringToBool( t ) );

    t.assign( "no" );
    test( ! StringToBool( t ) );

    t.assign( "on" );
    test( StringToBool( t ) );

    t.assign( "off" );
    test( ! StringToBool( t ) );

    t.assign( "ON" );
    test( StringToBool( t ) );

    t.assign( "OFF" );
    test( ! StringToBool( t ) );
  }

  {
    // StringToInt( const Str & )
    // StringToInt( const Str &, unsigned short )

    Str t;

    t.assign( "1150" );
    test( StringToInt( t ) == 1150 );

    t.assign( "0xfff" );
    test( StringToInt( t ) == 0xfff );

    t.assign( "-30" );
    test( StringToInt( t ) == -30 );

    t = "123";
    test( StringToInt( t, 16 ) == 0x123 );
  }
  
  {
    // StringToLong( const Str & )
    // StringToLong( const Str &, unsigned short )

    Str t;

    t.assign( "1123456" );
    test( StringToLong( t ) == 1123456 );

    t.assign( "-1123456" );
    test( StringToLong( t ) == -1123456 );

    t = "123";
    test( StringToLong( t, 16 ) == 0x123 );
  }

  {
    // StringToDouble( cosnt Str & )
    // StringToDouble( const Str &, unsigned short )

    Str t;

    t.assign( "15.15" );
    test( StringToDouble( t ) ==  15.15 );

    t = "10.1";
    test( StringToDouble( t, 8 ) == 8.125 );

  }

  {
    // StringToUInt( const Str & )
    // StringToUInt( const Str &, unsigned short )

    Str t;

    t.assign( "0xff0f" );
    test( StringToUInt( t ) == 0xff0f);

    t = "123";
    test( StringToUInt( t, 16 ) == 0x123 );
  }

  {
    // StringToULong( const Str & )
    // StringToULong( const Str &,  unsigned short )

    Str t;

    t.assign( "0xffff0000" );
    test( StringToULong( t ) == 0xffff0000 );

    t = "123";
    test( StringToULong( t, 16 ) == 0x123 );
  }

  return( true );
}
    

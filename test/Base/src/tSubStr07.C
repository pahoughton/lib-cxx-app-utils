#include <LibTest.hh>
#include <Str.hh>

bool
tSubStr07( LibTest & test )
{
  {
    // StringToBool( const SubStr & )

    Str		ts( "A string for t to be a sub of" );
    SubStr      t( ts, 3, 5);

    t = "0";
    test( ! StringToBool( t ) );
    
    t = "01" ;
    test( StringToBool( t ) );

    t = "500" ;
    test( StringToBool( t ) );

    t = "T" ;
    test( StringToBool( t ) );

    t = "t" ;
    test( StringToBool( t ) );

    t = "F" ;
    test( ! StringToBool( t ) );

    t = "f" ;
    test( ! StringToBool( t ) );

    t = "true" ;
    test( StringToBool( t ) );

    t = "TRUE" ;
    test( StringToBool( t ) );

    t = "TrUe" ;
    test( StringToBool( t ) );

    t = "false" ;
    test( ! StringToBool( t ) );

    t = "FALSE" ;
    test( ! StringToBool( t ) );

    t = "FaLse" ;
    test( ! StringToBool( t ) );

    t = "y" ;
    test( StringToBool( t ) );

    t = "Y" ;
    test( StringToBool( t ) );

    t = "n" ;
    test( ! StringToBool( t ) );

    t = "N" ;
    test( ! StringToBool( t ) );

    t = "yes" ;
    test( StringToBool( t ) );

    t = "no" ;
    test( ! StringToBool( t ) );

    t = "on" ;
    test( StringToBool( t ) );

    t = "off" ;
    test( ! StringToBool( t ) );

    t = "ON" ;
    test( StringToBool( t ) );

    t = "OFF" ;
    test( ! StringToBool( t ) );
  }

  {
    // StringToInt( const SubStr & )
    // StringToInt( const SubStr &, unsigned short )

    Str		ts( "A string for t to be a sub of" );
    SubStr      t( ts, 3, 5);

    t = "1150" ;
    test( StringToInt( t ) == 1150 );

    t = "0xfff" ;
    test( StringToInt( t ) == 0xfff );

    t = "-30" ;
    test( StringToInt( t ) == -30 );

    t = "123";
    test( StringToInt( t, 16 ) == 0x123 );
  }
  
  {
    // StringToLong( const SubStr & )
    // StringToLong( const SubStr &, unsigned short )

    Str		ts( "A string for t to be a sub of" );
    SubStr      t( ts, 3, 5);

    t = "1123456" ;
    test( StringToLong( t ) == 1123456 );

    t = "-1123456" ;
    test( StringToLong( t ) == -1123456 );

    t = "123";
    test( StringToLong( t, 16 ) == 0x123 );
  }

  {
    // StringToDouble( cosnt Str & )
    // StringToDouble( const SubStr &, unsigned short )

    Str		ts( "A string for t to be a sub of" );
    SubStr      t( ts, 3, 5);

    t = "15.15" ;
    test( StringToDouble( t ) ==  15.15 );

    t = "10.1";
    test( StringToDouble( t, 8 ) == 8.125 );

  }

  {
    // StringToUInt( const SubStr & )
    // StringToUInt( const SubStr &, unsigned short )

    Str		ts( "A string for t to be a sub of" );
    SubStr      t( ts, 3, 5);

    t = "0xff0f" ;
    test( StringToUInt( t ) == 0xff0f);

    t = "123";
    test( StringToUInt( t, 16 ) == 0x123 );
  }

  {
    // StringToULong( const SubStr & )
    // StringToULong( const SubStr &,  unsigned short )

    Str		ts( "A string for t to be a sub of" );
    SubStr      t( ts, 3, 5);

    t = "0xffff0000" ;
    test( StringToULong( t ) == 0xffff0000 );

    t = "123";
    test( StringToULong( t, 16 ) == 0x123 );
  }

  return( true );
}
    

#include <LibTest.hh>
#include <Str.hh>

static const char * BaseStrings[] =
{
  "111111111111",
  "12121200",
  "333333",
  "112340",
  "30543",
  "14640",
  "7777",
  "5550",
  "4095",
  "3093",
  "2453",
  "1b30",
  "16c7",
  "1330",
  "fff"
};

bool
tSubStr02( LibTest & test )
{    
  {
    // to( int &, unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );
    int n;
    
    t = "100";

    test( t.to( n ) && n == 100 );

    t = "  0xabcd  ";

    test( t.to( n ) && n == 0xabcd );

    t = "  077 ";

    test( t.to( n ) && n == 077 );

    for( int b = 2; b < 17; b++ )
      {
	t = BaseStrings[b-2];
	
	test( t.to( n, b ) && n == 0xfff );
      }

    t = "-1050";
    test( t.to(n) && n == -1050 );

    t = "+1050";
    test( t.to(n) && n == 1050 );

    t = "0xtest";
    test( ! t.to(n) );

    t = "0";
    test( t.to(n) && n == 0 );
  }
    
  {
    // to( short & ) const
    // to( short &, unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );
    short n;

    t = "0xfff";
    test( t.to( n ) && n == 0xfff );
    t = "10";
    test( t.to( n, 8 ) && n == 010 );
  }
  
  {
    // to( long & ) const
    // to( long &, unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );
    long n;

    t = "0xffffff";
    test( t.to( n ) && n == 0xffffff );

    t = "123";
    test( t.to( n, 16 ) && n == 0x123 );
  }
  
  {
    // to( double & ) const
    // to( double &, unsinged short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );
    double n;

    t = "0xf.8";
    test( t.to( n ) && n == 15.5 );

    t = "-1010.15";

    test( t.to( n ) && n == -1010.15 );

    t = ".120";

    test( t.to( n ) && n == .120 );

    t = "25.1";
    test( t.to( n, 8 ) && n == 21.125 );
  }
  
  {
    // to( unsigned int & ) const
    // to( unsigned int &, unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );
    unsigned int n;

    t = "0xfff0";
    test( t.to( n ) && n == 0xfff0 );

    t = "132";
    test( t.to( n, 16 ) && n == 0x132 );
  }

  {
    // to( unsigned short & ) const
    // to( unsigned short &, unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );
    unsigned short n;

    t = "0xfff0";
    test( t.to( n ) && n == 0xfff0 );

    t = "132";
    test( t.to( n, 8 ) && n == 0132 );
  }

  {
    // to( unsigned long & ) const
    // to( unsigned long &, unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );
    unsigned long n;

    t = "0xfffff00f";
    test( t.to( n ) && n == 0xfffff00f );

    t = "132";
    test( t.to( n, 8 ) && n == 0132 );
  }

  {
    // toBool( void ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );

    t = "0";
    test( ! t.toBool() );
    
    t =  "01" ;
    test( t.toBool() );

    t =  "500" ;
    test( t.toBool() );

    t =  "T" ;
    test( t.toBool() );

    t =  "t" ;
    test( t.toBool() );

    t =  "F" ;
    test( ! t.toBool() );

    t =  "f" ;
    test( ! t.toBool() );

    t =  "true" ;
    test( t.toBool() );

    t =  "TRUE" ;
    test( t.toBool() );

    t =  "TrUe" ;
    test( t.toBool() );

    t =  "false" ;
    test( ! t.toBool() );

    t =  "FALSE" ;
    test( ! t.toBool() );

    t =  "FaLse" ;
    test( ! t.toBool() );

    t =  "y" ;
    test( t.toBool() );

    t =  "Y" ;
    test( t.toBool() );

    t =  "n" ;
    test( ! t.toBool() );

    t =  "N" ;
    test( ! t.toBool() );

    t =  "yes" ;
    test( t.toBool() );

    t =  "no" ;
    test( ! t.toBool() );

    t =  "on" ;
    test( t.toBool() );

    t =  "off" ;
    test( ! t.toBool() );

    t =  "ON" ;
    test( t.toBool() );

    t =  "OFF" ;
    test( ! t.toBool() );
  }

  {
    // toInt( void ) const
    // toInt( unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );

    t =  "1150" ;
    test( t.toInt() == 1150 );

    t =  "0xfff" ;
    test( t.toInt() == 0xfff );

    t =  "-30" ;
    test( t.toInt() == -30 );

    t = "123";
    test( t.toInt( 16 ) == 0x123 );
  }
  
  {
    // toLong( void ) const
    // toLong( unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );

    t =  "1123456" ;
    test( t.toLong() == 1123456 );

    t =  "-1123456" ;
    test( t.toLong() == -1123456 );

    t = "123";
    test( t.toLong( 16 ) == 0x123 );
  }

  {
    // toDouble( void ) const
    // toDouble( unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );

    t =  "15.15" ;
    test( t.toDouble() ==  15.15 );

    t = "10.1";
    test( t.toDouble( 8 ) == 8.125 );

  }

  {
    // toUInt( void ) const
    // toUInt( unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );

    t =  "0xff0f" ;
    test( t.toUInt() == 0xff0f);

    t = "123";
    test( t.toUInt( 16 ) == 0x123 );
  }

  {
    // toULong( void ) const
    // toULong( unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );

    t =  "0xffff0000" ;
    test( t.toULong() == 0xffff0000 );

    t = "123";
    test( t.toULong( 16 ) == 0x123 );
  }

  return( true );
}

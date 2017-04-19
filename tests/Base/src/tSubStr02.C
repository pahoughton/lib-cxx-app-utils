#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#endif

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
tSubStr02( LibTest & tester )
{    
  {
    // to( int &, unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );
    int n;
    
    t = "100";

    TEST( t.to( n ) && n == 100 );

    t = "  0xbcd";

    TEST( t.to( n ) && n == 0xbcd );

    t = "  077";

    TEST( t.to( n ) && n == 077 );

    for( int b = 2; b < 17; b++ )
      {
	t = BaseStrings[b-2];
	
	TEST( t.to( n, b ) && n == 0xfff );
      }

    t = "-1050";
    TEST( t.to(n) && n == -1050 );

    t = "+1050";
    TEST( t.to(n) && n == 1050 );

    t = "0xtest";
    TEST( ! t.to(n) );

    t = "0";
    TEST( t.to(n) && n == 0 );
  }
    
  {
    // to( short & ) const
    // to( short &, unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );
    short n;

    t = "0xfff";
    TEST( t.to( n ) && n == 0xfff );
    t = "10";
    TEST( t.to( n, 8 ) && n == 010 );
  }
  
  {
    // to( long & ) const
    // to( long &, unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );
    long n;

    t = "0xffffff";
    TEST( t.to( n ) && n == 0xffffffL );

    t = "123";
    TEST( t.to( n, 16 ) && n == 0x123 );
  }
  
  {
    // to( double & ) const
    // to( double &, unsinged short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );
    double n;

    t = "0xf.8";
    TEST( t.to( n ) && n == 15.5 );

    t = "-1010.15";

    TEST( t.to( n ) && n == -1010.15 );

    t = ".120";

    TEST( t.to( n ) && n == .120 );

    t = "25.1";
    TEST( t.to( n, 8 ) && n == 21.125 );
  }
  
  {
    // to( unsigned int & ) const
    // to( unsigned int &, unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );
    unsigned int n;

    t = "0xfff0";
    TEST( t.to( n ) && n == 0xfff0 );

    t = "132";
    TEST( t.to( n, 16 ) && n == 0x132 );
  }

  {
    // to( unsigned short & ) const
    // to( unsigned short &, unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );
    unsigned short n;

    t = "0xfff0";
    TEST( t.to( n ) && n == 0xfff0 );

    t = "132";
    TEST( t.to( n, 8 ) && n == 0132 );
  }

  {
    // to( unsigned long & ) const
    // to( unsigned long &, unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );
    unsigned long n;

    t = "0xfffff00f";
    TEST( t.to( n ) && n == 0xfffff00fL );

    t = "132";
    TEST( t.to( n, 8 ) && n == 0132 );
  }

  {
    // toBool( void ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );

    t = "0";
    TEST( ! t.toBool() );
    
    t =  "01" ;
    TEST( t.toBool() );

    t =  "500" ;
    TEST( t.toBool() );

    t =  "T" ;
    TEST( t.toBool() );

    t =  "t" ;
    TEST( t.toBool() );

    t =  "F" ;
    TEST( ! t.toBool() );

    t =  "f" ;
    TEST( ! t.toBool() );

    t =  "true" ;
    TEST( t.toBool() );

    t =  "TRUE" ;
    TEST( t.toBool() );

    t =  "TrUe" ;
    TEST( t.toBool() );

    t =  "false" ;
    TEST( ! t.toBool() );

    t =  "FALSE" ;
    TEST( ! t.toBool() );

    t =  "FaLse" ;
    TEST( ! t.toBool() );

    t =  "y" ;
    TEST( t.toBool() );

    t =  "Y" ;
    TEST( t.toBool() );

    t =  "n" ;
    TEST( ! t.toBool() );

    t =  "N" ;
    TEST( ! t.toBool() );

    t =  "yes" ;
    TEST( t.toBool() );

    t =  "no" ;
    TEST( ! t.toBool() );

    t =  "on" ;
    TEST( t.toBool() );

    t =  "off" ;
    TEST( ! t.toBool() );

    t =  "ON" ;
    TEST( t.toBool() );

    t =  "OFF" ;
    TEST( ! t.toBool() );
  }

  {
    // toInt( void ) const
    // toInt( unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );

    t =  "1150" ;
    TEST( t.toInt() == 1150 );

    t =  "0xfff" ;
    TEST( t.toInt() == 0xfff );

    t =  "-30" ;
    TEST( t.toInt() == -30 );

    t = "123";
    TEST( t.toInt( 16 ) == 0x123 );
  }
  
  {
    // toLong( void ) const
    // toLong( unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );

    t =  "1123456" ;
    TEST( t.toLong() == 1123456L );

    t =  "-1123456" ;
    TEST( t.toLong() == -1123456L );

    t = "123";
    TEST( t.toLong( 16 ) == 0x123 );
  }

  {
    // toDouble( void ) const
    // toDouble( unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );

    t =  "15.15" ;
    TEST( t.toDouble() ==  15.15 );

    t = "10.1";
    TEST( t.toDouble( 8 ) == 8.125 );

  }

  {
    // toUInt( void ) const
    // toUInt( unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );

    t =  "0xff0f" ;
    TEST( t.toUInt() == 0xff0f);

    t = "123";
    TEST( t.toUInt( 16 ) == 0x123 );
  }

  {
    // toULong( void ) const
    // toULong( unsigned short ) const

    Str	s( "Just a string to get a SubStr of" );
    SubStr t( s, 5, 3 );

    t =  "0xffff0000" ;
    TEST( t.toULong() == 0xffff0000UL );

    t = "123";
    TEST( t.toULong( 16 ) == 0x123 );
  }

  return( true );
}

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
tStr17( LibTest & test )
{
  {
    // to( int & ) const
    // to( int &, unsigned short ) const

    Str	t;
    int n;
    
    t << "100";

    test( t.to( n ) && n == 100 );

    t.reset();
    t << "  0xabcd  ";

    test( t.to( n ) && n == 0xabcd );

    t.reset();
    t << "  077 ";

    test( t.to( n ) && n == 077 );

    for( int b = 2; b < 17; b++ )
      {
	t.reset();
	t << BaseStrings[b-2];
	
	test( t.to( n, b ) && n == 0xfff );
      }

    t.reset();
    t << "-1050";
    test( t.to(n) && n == -1050 );

    t.reset();
    t << "+1050";
    test( t.to(n) && n == 1050 );

    t.reset();
    test( ! t.to(n) );

    t << "0xtest";
    test( ! t.to(n) );

    t.reset();
    t << "0";
    test( t.to(n) && n == 0 );
    
  }

  {
    // to( short & ) const
    // to( short &, unsigned short ) const

    Str t;
    short n;

    t = "0xfff";
    test( t.to( n ) && n == 0xfff );
    t = "10";
    test( t.to( n, 8 ) && n == 010 );
  }

  {
    // to( long & ) const
    // to( long &, unsigned short ) const

    Str t;
    long n;

    t << "0xffffff";
    test( t.to( n ) && n == 0xffffff );

    t = "123";
    test( t.to( n, 16 ) && n == 0x123 );
  }
  
  {
    // to( double & ) const
    // to( double &, unsinged short ) const

    Str t;
    double n;

    t << "0xf.8";
    test( t.to( n ) && n == 15.5 );

    t.reset();
    t << "-1010.15";

    test( t.to( n ) && n == -1010.15 );

    t.reset();
    t << ".120";

    test( t.to( n ) && n == .120 );

    t = "25.1";
    test( t.to( n, 8 ) && n == 21.125 );
  }
  
  {
    // to( unsigned int & ) const
    // to( unsigned int &, unsigned short ) const

    Str t;
    unsigned int n;

    t << "0xfff0";
    test( t.to( n ) && n == 0xfff0 );

    t = "132";
    test( t.to( n, 16 ) && n == 0x132 );
  }

  {
    // to( unsigned short & ) const
    // to( unsigned short &, unsigned short ) const

    Str t;
    unsigned short n;

    t << "0xfff0";
    test( t.to( n ) && n == 0xfff0 );

    t = "132";
    test( t.to( n, 8 ) && n == 0132 );
  }

  {
    // to( unsigned long & ) const
    // to( unsigned long &, unsigned short ) const

    Str t;
    unsigned long n;

    t << "0xfffff00f";
    test( t.to( n ) && n == 0xfffff00f );

    t = "132";
    test( t.to( n, 8 ) && n == 0132 );
  }

  {
    // toBool( void ) const

    Str     t;

    t << "0";
    test( ! t.toBool() );
    
    t.assign( "01" );
    test( t.toBool() );

    t.assign( "500" );
    test( t.toBool() );

    t.assign( "T" );
    test( t.toBool() );

    t.assign( "t" );
    test( t.toBool() );

    t.assign( "F" );
    test( ! t.toBool() );

    t.assign( "f" );
    test( ! t.toBool() );

    t.assign( "true" );
    test( t.toBool() );

    t.assign( "TRUE" );
    test( t.toBool() );

    t.assign( "TrUe" );
    test( t.toBool() );

    t.assign( "false" );
    test( ! t.toBool() );

    t.assign( "FALSE" );
    test( ! t.toBool() );

    t.assign( "FaLse" );
    test( ! t.toBool() );

    t.assign( "y" );
    test( t.toBool() );

    t.assign( "Y" );
    test( t.toBool() );

    t.assign( "n" );
    test( ! t.toBool() );

    t.assign( "N" );
    test( ! t.toBool() );

    t.assign( "yes" );
    test( t.toBool() );

    t.assign( "no" );
    test( ! t.toBool() );

    t.assign( "on" );
    test( t.toBool() );

    t.assign( "off" );
    test( ! t.toBool() );

    t.assign( "ON" );
    test( t.toBool() );

    t.assign( "OFF" );
    test( ! t.toBool() );
  }

  {
    // toInt( void ) const
    // toInt( unsigned short ) const

    Str t;

    t.assign( "1150" );
    test( t.toInt() == 1150 );

    t.assign( "0xfff" );
    test( t.toInt() == 0xfff );

    t.assign( "-30" );
    test( t.toInt() == -30 );

    t = "123";
    test( t.toInt( 16 ) == 0x123 );
  }
  
  {
    // toLong( void ) const
    // toLong( unsigned short ) const

    Str t;

    t.assign( "1123456" );
    test( t.toLong() == 1123456 );

    t.assign( "-1123456" );
    test( t.toLong() == -1123456 );

    t = "123";
    test( t.toLong( 16 ) == 0x123 );
  }

  {
    // toDouble( void ) const
    // toDouble( unsigned short ) const

    Str t;

    t.assign( "15.15" );
    test( t.toDouble() ==  15.15 );

    t = "10.1";
    test( t.toDouble( 8 ) == 8.125 );

  }

  {
    // toUInt( void ) const
    // toUInt( unsigned short ) const

    Str t;

    t.assign( "0xff0f" );
    test( t.toUInt() == 0xff0f);

    t = "123";
    test( t.toUInt( 16 ) == 0x123 );
  }

  {
    // toULong( void ) const
    // toULong( unsigned short ) const

    Str t;

    t.assign( "0xffff0000" );
    test( t.toULong() == 0xffff0000 );

    t = "123";
    test( t.toULong( 16 ) == 0x123 );
  }

  return( true );
}

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
tStr17( LibTest & tester )
{
  {
    // to( int & ) const
    // to( int &, unsigned short ) const

    Str	t;
    int n;
    
    t << "100";

    TEST( t.to( n ) && n == 100 );

    t.reset();
    t << "  0xbcd";

    TEST( t.to( n ) && n == 0xbcd );

    t.reset();
    t << "  077";

    TEST( t.to( n ) && n == 077 );

    for( int b = 2; b < 17; b++ )
      {
	t.reset();
	t << BaseStrings[b-2];
	
	TEST( t.to( n, b ) && n == 0xfff );
      }

    t.reset();
    t << "-1050";
    TEST( t.to(n) && n == -1050 );

    t.reset();
    t << "+1050";
    TEST( t.to(n) && n == 1050 );

    t.reset();
    TEST( ! t.to(n) );

    t << "0xtest";
    TEST( ! t.to(n) );

    t.reset();
    t << "0";
    TEST( t.to(n) && n == 0 );
    
  }

  {
    // to( short & ) const
    // to( short &, unsigned short ) const

    Str t;
    short n;

    t = "0xfff";
    TEST( t.to( n ) && n == 0xfff );
    t = "10";
    TEST( t.to( n, 8 ) && n == 010 );
  }

  {
    // to( long & ) const
    // to( long &, unsigned short ) const

    Str t;
    long n;

    t << "0xffffff";
    TEST( t.to( n ) && n == 0xffffffL );

    t = "123";
    TEST( t.to( n, 16 ) && n == 0x123 );
  }
  
  {
    // to( double & ) const
    // to( double &, unsinged short ) const

    Str t;
    double n;

    t << "0xf.8";
    TEST( t.to( n ) && n == 15.5 );

    t.reset();
    t << "-1010.15";

    TEST( t.to( n ) && n == -1010.15 );

    t.reset();
    t << ".120";

    TEST( t.to( n ) && n == .120 );

    t = "25.1";
    TEST( t.to( n, 8 ) && n == 21.125 );
  }
  
  {
    // to( unsigned int & ) const
    // to( unsigned int &, unsigned short ) const

    Str t;
    unsigned int n;

    t << "0xfff0";
    TEST( t.to( n ) && n == 0xfff0 );

    t = "132";
    TEST( t.to( n, 16 ) && n == 0x132 );
  }

  {
    // to( unsigned short & ) const
    // to( unsigned short &, unsigned short ) const

    Str t;
    unsigned short n;

    t << "0xfff0";
    TEST( t.to( n ) && n == 0xfff0 );

    t = "132";
    TEST( t.to( n, 8 ) && n == 0132 );
  }

  {
    // to( unsigned long & ) const
    // to( unsigned long &, unsigned short ) const

    Str t;
    unsigned long n;

    t << "0xfffff00f";
    TEST( t.to( n ) && n == 0xfffff00fUL );

    t = "132";
    TEST( t.to( n, 8 ) && n == 0132 );
  }

  {
    // toBool( void ) const

    Str     t;

    t << "0";
    TEST( ! t.toBool() );
    
    t.assign( "01" );
    TEST( t.toBool() );

    t.assign( "500" );
    TEST( t.toBool() );

    t.assign( "T" );
    TEST( t.toBool() );

    t.assign( "t" );
    TEST( t.toBool() );

    t.assign( "F" );
    TEST( ! t.toBool() );

    t.assign( "f" );
    TEST( ! t.toBool() );

    t.assign( "true" );
    TEST( t.toBool() );

    t.assign( "TRUE" );
    TEST( t.toBool() );

    t.assign( "TrUe" );
    TEST( t.toBool() );

    t.assign( "false" );
    TEST( ! t.toBool() );

    t.assign( "FALSE" );
    TEST( ! t.toBool() );

    t.assign( "FaLse" );
    TEST( ! t.toBool() );

    t.assign( "y" );
    TEST( t.toBool() );

    t.assign( "Y" );
    TEST( t.toBool() );

    t.assign( "n" );
    TEST( ! t.toBool() );

    t.assign( "N" );
    TEST( ! t.toBool() );

    t.assign( "yes" );
    TEST( t.toBool() );

    t.assign( "no" );
    TEST( ! t.toBool() );

    t.assign( "on" );
    TEST( t.toBool() );

    t.assign( "off" );
    TEST( ! t.toBool() );

    t.assign( "ON" );
    TEST( t.toBool() );

    t.assign( "OFF" );
    TEST( ! t.toBool() );
  }

  {
    // toInt( void ) const
    // toInt( unsigned short ) const

    Str t;

    t.assign( "1150" );
    TEST( t.toInt() == 1150 );

    t.assign( "0xfff" );
    TEST( t.toInt() == 0xfff );

    t.assign( "-30" );
    TEST( t.toInt() == -30 );

    t = "123";
    TEST( t.toInt( 16 ) == 0x123 );
  }
  
  {
    // toLong( void ) const
    // toLong( unsigned short ) const

    Str t;

    t.assign( "1123456" );
    TEST( t.toLong() == 1123456L );

    t.assign( "-1123456" );
    TEST( t.toLong() == -1123456L );

    t = "123";
    TEST( t.toLong( 16 ) == 0x123 );

    t = "001234";
    TEST( t.toLong( 10 ) == 1234 );

    t = "012";
    TEST( t.toLong() == 012 );

    t = "00321";
    TEST( t.toLong() == 00321 );
  }

  {
    // toDouble( void ) const
    // toDouble( unsigned short ) const

    Str t;

    t.assign( "15.15" );
    TEST( t.toDouble() ==  15.15 );

    t = "10.1";
    TEST( t.toDouble( 8 ) == 8.125 );

  }

  {
    // toUInt( void ) const
    // toUInt( unsigned short ) const

    Str t;

    t.assign( "0xff0f" );
    TEST( t.toUInt() == 0xff0f);

    t = "123";
    TEST( t.toUInt( 16 ) == 0x123 );
  }

  {
    // toULong( void ) const
    // toULong( unsigned short ) const

    Str t;

    t.assign( "0xffff0000" );
    TEST( t.toULong() == 0xffff0000UL );

    t = "123";
    TEST( t.toULong( 16 ) == 0x123 );
  }

  {
    // to( RangeList & range, unsigned short base )
    Str		    r;
    Str::RangeList  t;

    r = "57";
    TEST( r.to( t ) == 1 );

    {
      TEST( t.size() == 1 );
      
      Str::RangeList::iterator them = t.begin();

      TEST( them != t.end() );
      TEST( (*them).first == 57 );
      TEST( (*them).second == 0 );
    }

    r = "4,8";
    TEST( r.to( t ) == 2 );
    
    {
      TEST( t.size() == 2 );
      
      Str::RangeList::iterator them = t.begin();

      TEST( them != t.end() );
      TEST( (*them).first == 4 );
      TEST( (*them).second == 0 );
      
      ++ them;
      TEST( them != t.end() );
      TEST( (*them).first == 8);
      TEST( (*them).second == 0 );
    }

    r = "3-200";
    TEST( r.to( t ) == 1 );
    
    {
      TEST( t.size() == 1 );
      
      Str::RangeList::iterator them = t.begin();

      TEST( them != t.end() );
      TEST( (*them).first == 3 );
      TEST( (*them).second == 200 );
      
    }

    r = "4-8,10:20.23  30..35\t50;1025-";
    TEST( r.to( t ) == 6 );
    
    {
      TEST( t.size() == 6 );
      
      Str::RangeList::iterator them = t.begin();

      TEST( them != t.end() );
      TEST( (*them).first == 4 );
      TEST( (*them).second == 8 );
      
      ++ them;
      TEST( them != t.end() );
      TEST( (*them).first == 10 );
      TEST( (*them).second == 0 );
      
      ++ them;
      TEST( them != t.end() );
      TEST( (*them).first == 20 );
      TEST( (*them).second == 23 );
      
      ++ them;
      TEST( them != t.end() );
      TEST( (*them).first == 30 );
      TEST( (*them).second == 35  );
      
      ++ them;
      TEST( them != t.end() );
      TEST( (*them).first == 50 );
      TEST( (*them).second == 0 );
      
      ++ them;
      TEST( them != t.end() );
      TEST( (*them).first == 1025 );
      TEST( (*them).second == ULONG_MAX );
    }

  }
	
      
  return( true );
}

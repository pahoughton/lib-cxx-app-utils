#include <LibTest.hh>
#include <Str.hh>

// Str::from( number)

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
tStr16( LibTest & test )
{
  {
    // from( int )
    
    Str t;

    int num = 0;
    t.from( num );

    test(  t == "0" );

    t = "number: ";

    num = 10;
    t.from( num );

    test( t == "number: 10" );

    t.reset();
    num = 4096;
    t.from( num );

    t << " - 4096";

    test( t == "4096 - 4096" );

    t.reset();
    t.width( 5 );
    num = -21;
    t.from( num );

    test( t == "  -21" );

    t.reset();
    t.width( 3 );
    num = 19999;
    t.from( num ).append( " number" );

    test( t == "19999 number" );

    t.reset();
    num = 50;
    long was = t.setf( ios::showpos );
    t.from( num );

    test( t == "+50" );
    
    t.reset();
    t.width( 5 );
    num = 15;
    t.from( num );

    test( t == "  +15" );

    t.reset();
    t.flags( was );
    was = t.setf( ios::left );
    num = 15;
    t.width( 5 );
    t.from( num );

    test( t == "15   " );

    t.reset();
    t.flags( was );
    was = t.setf( ios::showpos );
    t.setf( ios::left );
    num = 100;
    t.width( 8 );
    t.from( num );

    test( t == "+100    " );

  }

  {
    // from( int, unsigned short )
    Str t;
    int num = 0;

    num = 077;
    t.from( num );

    test( t == "63" );

    num = 0xff00;
    t.reset();
    t.from( num );
    
    test( t == "65280" );

    num = 0xfff;

    for( int b = 2; b < 17; b++ )
      {
	t.reset();
	t.from( num, b );
	test( t == BaseStrings[b-2] );
      }
    
    num = -43981;

    t.reset();
    t.setf( ios::showbase );
    t.setf( ios::showpos );
    t.width( 10 );
    t.from( num, 8 );
    
    test( t == "  -0125715" );

    t.reset();
    t.from( num, 16 );
    
    test( t == "-0xabcd" );

    t.reset();
    t.setf( ios::uppercase );
    t.from( num, 16 );
    
    test( t == "-0XABCD" );

    t.reset();
    num = -num;
    t.width( 10 );
    t.from( num, 8 );
    
    test( t == "  +0125715" );

    t.reset();
    t.width( 10 );
    t.from( num, 16 );
    
    test( t == "   +0XABCD" );


    t.reset();
    t.setf( ios::left );
    t.width( 10 );
    t.from( num, 16 );
    
    test( t == "+0XABCD   " );

  }

  {
    // from( short )
    Str t;
    
    short num = -550;
    t.from( num );

    test( t == "-550" );
  }
    
  {
    // from( short, unsigned short )
    Str t;
    
    short num = 0xfff;
    
    for( int b = 2; b < 17; b++ )
      {
	t.reset();
	t.from( num, b );
	test( t == BaseStrings[b-2] );
      }    
  }

  {
    // from( long )
    
    Str t;
    
    long num = -550;
    t.from( num );

    test( t == "-550" );

    t.reset();
    num = 999999999;
    t.from( num );
    test( t == "999999999" );
    
    t.reset();
    num = 111111111;
    t.from( num );
    test( t == "111111111" );
    
  }

  {
    // from( long, unsigned short )
    Str t;
    
    long num = 0xfff;
    
    for( int b = 2; b < 17; b++ )
      {
	t.reset();
	t.from( num, b );
	test( t == BaseStrings[b-2] );
      }    
  }

  {
    // from( unsigned int )
    Str t;

    unsigned int num = UINT_MAX;

    t.from( num, 16 );
    
    if( sizeof( int ) == sizeof( long ) )
      {
	test( t == "ffffffff" );
      }
    else
      {
	test( t == "ffff" );
      }
  }
    
  {
    // from( unsigned int, unsigned short )
    Str t;
    
    unsigned int num = 0xfff;
    
    for( int b = 2; b < 17; b++ )
      {
	t.reset();
	t.from( num, b );
	test( t == BaseStrings[b-2] );
      }    
  }

  {
    // from( unsigned short )
    // from( unsigned short, unsigned short )
    Str t;

    unsigned short num = 1234;

    t.from( num );
    test( t == "1234" );
    
    t.reset();
    num = USHRT_MAX;
    
    t.from( num, 16 );
    
    test( t == "ffff" );    
  }
    
  {
    // from( unsigned long )
    // from( unsigned long, unsigned short )
    
    Str t;

    unsigned long num = 1234;

    t.from( num );
    test( t == "1234" );
    
    num = ULONG_MAX;
    t.reset();
    t.from( num, 16 );
    
    test( t == "ffffffff" );    
  }
    
  return( true );
}

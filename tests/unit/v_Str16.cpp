// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/Str.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <climits>

static valid::verify verify("clue::Str16");
using namespace clue;

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
v_Str16( void )
{
  {
    // from( int )

    Str t;

    int num = 0;
    t.from( num );

    TEST(  t == "0" );

    t = "number: ";

    num = 10;
    t.from( num );

    TEST( t == "number: 10" );

    t.reset();
    num = 4096;
    t.from( num );

    t << " - 4096";

    TEST( t == "4096 - 4096" );

    t.reset();
    t.width( 5 );
    num = -21;
    t.from( num );

    TEST( t == "  -21" );

    t.reset();
    t.width( 3 );
    num = 19999;
    t.from( num ).append( " number" );

    TEST( t == "19999 number" );

    t.reset();
    num = 50;
    std::ios::fmtflags was = t.setf( std::ios::showpos );
    t.from( num );

    TEST( t == "+50" );

    t.reset();
    t.width( 5 );
    num = 15;
    t.from( num );

    TEST( t == "  +15" );

    t.reset();
    t.flags( was );
    was = t.setf( std::ios::left );
    num = 15;
    t.width( 5 );
    t.from( num );

    TEST( t == "15   " );

    t.reset();
    t.flags( was );
    was = t.setf( std::ios::showpos );
    t.setf( std::ios::left );
    num = 100;
    t.width( 8 );
    t.from( num );

    TEST( t == "+100    " );

  }

  {
    // from( int, unsigned short )
    Str t;
    int num = 0;

    num = 077;
    t.from( num );

    TEST( t == "63" );

    num = 0x0ff0;
    t.reset();
    t.from( num );

    TEST( t == "4080" );

    num = 0xfff;

    for( int b = 2; b < 17; b++ )
      {
	t.reset();
	t.from( num, b );
	TEST( t == BaseStrings[b-2] );
      }

    num = -3981;

    t.reset();
    t.setf( std::ios::showbase );
    t.setf( std::ios::showpos );
    t.width( 10 );
    t.from( num, 8 );

    TEST( t == "    -07615" );

    t.reset();
    t.from( num, 16 );

    TEST( t == "-0xf8d" );

    t.reset();
    t.setf( std::ios::uppercase );
    t.from( num, 16 );

    TEST( t == "-0XF8D" );

    t.reset();
    num = -num;
    t.width( 10 );
    t.from( num, 8 );

    TEST( t == "    +07615" );

    t.reset();
    t.width( 10 );
    t.from( num, 16 );

    TEST( t == "    +0XF8D" );


    t.reset();
    t.setf( std::ios::left );
    t.width( 10 );
    t.from( num, 16 );

    TEST( t == "+0XF8D    " );

  }

  {
    // from( short )
    Str t;

    short num = -550;
    t.from( num );

    TEST( t == "-550" );
  }

  {
    // from( short, unsigned short )
    Str t;

    short num = 0xfff;

    for( int b = 2; b < 17; b++ )
      {
	t.reset();
	t.from( num, b );
	TEST( t == BaseStrings[b-2] );
      }
  }

  {
    // from( long )

    Str t;

    long num = -550;
    t.from( num );

    TEST( t == "-550" );

    t.reset();
    num = 999999999L;
    t.from( num );
    TEST( t == "999999999" );

    t.reset();
    num = 111111111L;
    t.from( num );
    TEST( t == "111111111" );

  }

  {
    // from( long, unsigned short )
    Str t;

    long num = 0xfff;

    for( int b = 2; b < 17; b++ )
      {
	t.reset();
	t.from( num, b );
	TEST( t == BaseStrings[b-2] );
      }
  }

  {
    // from( unsigned int )
    Str t;

    unsigned int num = UINT_MAX;

    t.from( num, 16 );

    if( sizeof( int ) == 4 ) {
      TEST( t == "ffffffff" );
    } else if( sizeof( int ) == 2 ) {
      TEST( t == "ffff" );
    } else {
      TEST( false );
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
	TEST( t == BaseStrings[b-2] );
      }
  }

  {
    // from( unsigned short )
    // from( unsigned short, unsigned short )
    Str t;

    unsigned short num = 1234;

    t.from( num );
    TEST( t == "1234" );

    t.reset();
    num = USHRT_MAX;

    t.from( num, 16 );

    TEST( t == "ffff" );
  }

  {
    // from( unsigned long )
    // from( unsigned long, unsigned short )

    Str t;

    unsigned long num = 1234;

    t.from( num );
    TEST( t == "1234" );

    num = ULONG_MAX;
    t.reset();
    t.from( num, 16 );

    if( sizeof( num ) == 8 ) {
      TEST( t == "ffffffffffffffff" );
    } else if( sizeof( num ) == 4 ) {
      TEST( t == "ffffffff" );
    } else {
      TEST( false );
    }
  }

  return( verify.is_valid() );
}

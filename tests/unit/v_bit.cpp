// 1996-10-28 (cc) <paul4hough@gmail.com>

#include <clue/bit>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>

static valid::verify verify("clue::bit");

using namespace clue;

bool
v_bit( void )
{
  {
    // CHAR_BITS
    // SHORT_BITS
    // INT_BITS
    // LONG_BITS

    VVTRUE( CHAR_BITS == CHAR_BIT );
    VVTRUE( SHORT_BITS == ( sizeof(short) * CHAR_BITS ) );
    VVTRUE( INT_BITS == ( sizeof(int) * CHAR_BITS ) );
    VVTRUE( LONG_BITS == ( sizeof(long) * CHAR_BITS ) );
  }

  {
    // CHAR_ALL_BITS
    // SHORT_ALL_BITS
    // LONG_ALL_BITS
    // INT_ALL_BITS

    VVTRUE( CHAR_ALL_BITS == (unsigned char)(~0L ) );
    VVTRUE( SHORT_ALL_BITS == (unsigned short)(~0L ) );
    VVTRUE( LONG_ALL_BITS == (unsigned long)(~0L ) );
    VVTRUE( INT_ALL_BITS == (unsigned int)(~0 ) );
  }

  {
    // Bit( number )
    for( int i = 0; i < 32; i++ )
      {
	VVTRUE( Bit( i ) == (1 << i) );
      }

    VVTRUE( Bit( 0 ) == 0x01 );
    VVTRUE( Bit( 2 ) == 0x04 );
    VVTRUE( Bit( 4 ) == 0x10 );
  }

  {
    // BitSizeof( char )
    // BitSizeof( short )
    // BitSizeof( int )
    // BitSizeof( long )

    char    tChar = 0;
    short   tShort = 0;
    int	    tInt = 0;
    long    tLong = 0;

    VVTRUE( BitSizeof( tChar ) == CHAR_BIT );
    VVTRUE( BitSizeof( tShort ) == ( CHAR_BIT * sizeof( tShort ) ) );
    VVTRUE( BitSizeof( tLong ) == ( CHAR_BIT * sizeof( tLong ) ) );
    VVTRUE( BitSizeof( tInt ) == ( CHAR_BIT * sizeof( tInt ) ) );
  }

  {
    // StripHigh( char, number )

    char t = 0xf5;

    VVTRUE( StripHigh( t, 6 ) == 0x35 );
    t = 0x80;
    VVTRUE( StripHigh( t, 7 ) == 0x00 );
    t = 0x45;
    VVTRUE( StripHigh( t, 7 ) == 0x45 );
    t = 0x1f;
    VVTRUE( StripHigh( t, 6 ) == 0x1f );
    t = 0x1f;
    VVTRUE( StripHigh( t, 4 ) == 0x0f );
    t = 0xff;
    VVTRUE( StripHigh( t, 1 ) == 0x01 );
    t = 0xff;
    VVTRUE( StripHigh( t, 3 ) == 0x07 ); // doc example
  }

  {
    // StripHigh( short, number )

    short t = 0x3fff;

    VVTRUE( StripHigh( t, 11 ) == 0x07ff );
  }

  {
    // StripHigh( unsigned short, number )

    unsigned short t = 0xffff;

    VVTRUE( StripHigh( t, 10 ) == 0x03ff );
  }

  {
    // StripHigh( int, number )

    if( sizeof( int ) == 4 )
      {
	int t = 0x1fffffff;
	VVTRUE( INT_ALL_BITS == 0xffffffff );
	VVTRUE( StripHigh( t, 16 ) == 0x0000ffff );
      }
    else
      {
	int t = 0x1fff;

	VVTRUE( INT_ALL_BITS == 0xffff );
	VVTRUE( StripHigh( t, 8 ) == 0x00ff );
      }
  }

  {
    // StripHigh( unsigned int, number )

    if( sizeof( int ) == 4 )
      {
	unsigned int t = 0xffffffff;

	VVTRUE( StripHigh( t, 16 ) == 0xffff );
      }
    else
      {
	unsigned int t = 0xffff;

	VVTRUE( StripHigh( t, 8 ) == 0x00ff );
      }
  }

  {
    // StripHigh( long value, number )

    long t = 0x0fffffff;

    VVTRUE( StripHigh( t, 4 ) == 0x0000000f );
  }

  {
    // StripHigh( unsigned long, number )
    unsigned long t = 0xffffffff;

    VVTRUE( StripHigh( t, 1 ) == 0x00000001 );
  }

  {
    // StripLow( unsigned char, number )

    unsigned char t = 0xff;

    VVTRUE( StripLow( t, 4 ) == 0xf0 );
    VVTRUE( StripLow( t, 7 ) == 0x80 );
    VVTRUE( StripLow( t, 1 ) == 0xfe );
    VVTRUE( StripLow( t, 3 ) == 0xf8 );	// doc example
  }

  {
    // StripLow( long, number )

    long t = 0x1fffffff;

    VVTRUE( StripLow( t, 4 ) == 0x1ffffff0 );
    VVTRUE( StripLow( t, 28 ) == 0x10000000 );
  }

  {
    // ShiftRight( char, number )

    char t = 0x5f;

    VVTRUE( ShiftRight( t, 3 ) == 0x0b );
    VVTRUE( ShiftRight( t, 6 ) == 0x01 );
  }

  {
    // ShiftRight( long, number )
    long t = 0x03000000;

    VVTRUE( ShiftRight( t, 8  ) == 0x030000 );
    VVTRUE( ShiftRight( t, 28 ) == 0x0 );
    VVTRUE( ShiftRight( t, 24 ) == 0x03 );
  }

  {
    // ShiftLeft( unsigned char, number )

    unsigned char t = 0x35;
    VVTRUE( ShiftLeft( t, 4 ) == 0xA8 ); // doc example
  }


  {
    // ShiftLeft( unsigned char, number, number )

    unsigned char t = 0x06;

    VVTRUE( ShiftLeft( t, 1, 2 ) == 0xc0 );
    t = 0x34;
    VVTRUE( ShiftLeft( t, 4, 3 ) == 0x68 ); // doc example
    VVTRUE( ShiftLeft( t, 3, 3 ) == 0xd0 ); // doc example
    t = 3;
    VVTRUE( ShiftLeft( t, 0, 3 ) == 0x60 ); // doc example
    VVTRUE( ShiftLeft( t, 3, 0 ) == 0x60 ); // doc example
  }

  {
    // ShiftLeft( unsigned long, number, number )

    unsigned int t = 0xff0dffff;

    VVTRUE( ShiftLeft( t, 16, 3 ) == 0xbfffe000 );
  }

  {
    // ExtractBits( char, number, number )

    char t = 0x14;

    VVTRUE( ExtractBits( t, 2, 3 ) == 5 );
    t = 0xc0;
    VVTRUE( ExtractBits( t, 6, 2 ) == 3 );
    t = 0x34;
    VVTRUE( ExtractBits( t, 4, 3 ) == 0x03 ); // doc example
    VVTRUE( ExtractBits( t, 3, 3 ) == 0x06 ); // doc example
  }

  {
    // ExtractBits( short, number, number )

    short t = 0x0080;

    VVTRUE( ExtractBits( t, 7, 1 ) == 1 );
    t = 0x0300;
    VVTRUE( ExtractBits( t, 7, 3 ) == 6 );
  }

  {
    // ExtractBits( unsigned short, number, number )

    unsigned short t = 0xf000;

    VVTRUE( ExtractBits( t, 12, 4 ) == 0x000f );
  }

  {
    // ExtractBits( int, number, number )

    int t = 0xff00;

    VVTRUE( ExtractBits( t, 6, 4 ) == 12 );
  }

  {
    // ExtractBits( unsigned int, number, number )

    unsigned int t = 0xffff;

    VVTRUE( ExtractBits( t, 12, 2 ) == 3 );
  }

  {
    // ExtractBits( long, number, number )

    long t = 0x03000000;

    VVTRUE( ExtractBits( t, 22, 5 ) == 12 );
  }

  {
    // ExtractBits( unsigned long, number, number )

    unsigned long t = 0xfb000000;

    VVTRUE( ExtractBits( t, 22, 5 ) == 12 );
  }

  {
    // SetBits( unsigned char, int, number, number );

    unsigned char dest = CHAR_ALL_BITS;

    SetBits( dest, 0x0a, 1, 5 );
    VVTRUE( dest == 0xD5 );	// doc example

    dest = CHAR_ALL_BITS;
    SetBits( dest, 3, 4, 3 );
    VVTRUE( dest == 0xbf );	// doc example

    dest = CHAR_ALL_BITS;
    SetBits( dest, 6, 3, 3 );
    VVTRUE( dest == 0xf7 );	// doc example

    dest = 0;
    SetBits( dest, 3, 4, 3 );
    VVTRUE( dest == 0x30 );	// doc example

    dest = 0;
    SetBits( dest, 6, 3, 3 );
    VVTRUE( dest == 0x30 );	// doc example
  }

// 0110 0000 1000 0000   0000 0000 0000 0000
// 0110 0000 1000 0000   0000 0000 0000 0000
  {
    // SetBits( unsigned long, char, number, number )
    // SetBits( unsigned long, int, number, number )
    // SetBits( unsigned long, short, number, number )

    unsigned long d = 0x00000000;
    char    	  v = 0xfb;

    SetBits( d, v, 4, 3 );
    VVTRUE( d == 0x30 );

    int iv = 0xfffff;

    SetBits( d, iv, 16, 5 );
    VVTRUE( d == 0x001f0030 );

    short sv = 0x0c1;
    SetBits( d, sv, 23, 9 );
    VVTRUE( d == 0x609f0030 );
  }

  return( verify.is_valid() );
}

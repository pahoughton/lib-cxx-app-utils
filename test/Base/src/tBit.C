
#include <LibTest.hh>
#include <Bit.hh>

bool
tBit( LibTest & test )
{
  {
    // Bit( number )
    for( int i = 0; i < 32; i++ )
      {
	test( Bit( i ) == (1 << i) );
      }

    test( Bit( 0 ) == 0x01 );
    test( Bit( 2 ) == 0x04 );
    test( Bit( 4 ) == 0x10 );
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

    test( BitSizeof( tChar ) == CHAR_BIT );
    test( BitSizeof( tShort ) == ( CHAR_BIT * sizeof( tShort ) ) );
    test( BitSizeof( tLong ) == ( CHAR_BIT * sizeof( tLong ) ) );
    test( BitSizeof( tInt ) == ( CHAR_BIT * sizeof( tInt ) ) );
  }

  {
    // StripHigh( char, number )

    char t = 0xf5;
    
    test( StripHigh( t, 6 ) == 0x35 );
    t = 0x80;
    test( StripHigh( t, 7 ) == 0x00 );
    t = 0x45;
    test( StripHigh( t, 7 ) == 0x45 );
    t = 0x1f;
    test( StripHigh( t, 6 ) == 0x1f );
    t = 0x1f;
    test( StripHigh( t, 4 ) == 0x0f );
    t = 0xff;
    test( StripHigh( t, 1 ) == 0x01 );
  }

  {
    // StripHigh( short, number )

    short t = 0x3fff;

    test( StripHigh( t, 11 ) == 0x07ff );
  }

  {
    // StripHigh( unsigned short, number )
    
    unsigned short t = 0xffff;

    test( StripHigh( t, 10 ) == 0x03ff );
  }

  {
    // StripHigh( int, number )
    
    if( sizeof( int ) == 4 )
      {
	int t = 0x1fffffff;
	test( INT_ALL_BITS == 0xffffffff );
	test( StripHigh( t, 16 ) == 0x0000ffff );
      }
    else
      {
	int t = 0x1fff;

	test( INT_ALL_BITS == 0xffff );
	test( StripHigh( t, 8 ) == 0x00ff );
      }
  }

  {
    // StripHigh( unsigned int, number )
    
    if( sizeof( int ) == 4 )
      {
	unsigned int t = 0xffffffff;

	test( StripHigh( t, 16 ) == 0xffff );
      }
    else
      {
	unsigned int t = 0xffff;

	test( StripHigh( t, 8 ) == 0x00ff );
      }
  }

  {
    // StripHigh( long value, number )
    
    long t = 0x0fffffff;

    test( StripHigh( t, 4 ) == 0x0000000f );
  }
  
  {
    // StripHigh( unsigned long, number )
    unsigned long t = 0xffffffff;

    test( StripHigh( t, 1 ) == 0x00000001 );
  }

  {
    // StripLow( unsigned char, number )
    
    unsigned char t = 0xff;

    test( StripLow( t, 4 ) == 0xf0 );
    test( StripLow( t, 7 ) == 0x80 );
    test( StripLow( t, 1 ) == 0xfe );
  }

  {
    // StripLow( long, number )
    
    long t = 0x1fffffff;

    test( StripLow( t, 4 ) == 0x1ffffff0 );
    test( StripLow( t, 28 ) == 0x10000000 );
  }

  {
    // ShiftRight( char, number )
    
    char t = 0x5f;

    test( ShiftRight( t, 3 ) == 0x0b );
    test( ShiftRight( t, 6 ) == 0x01 );
  }

  {
    // ShiftRight( long, number )
    long t = 0x03000000;

    test( ShiftRight( t, 8  ) == 0x030000 );
    test( ShiftRight( t, 28 ) == 0x0 );
    test( ShiftRight( t, 24 ) == 0x03 );
  }
  
  {
    // ShiftLeft( unsigned char, number, number )
    
    unsigned char t = 0x06;

    test( ShiftLeft( t, 1, 2 ) == 0xc0 );
  }

  {
    // ShiftLeft( unsigned long, number, number )
    
    unsigned long t = 0xff0dffff;
    
    test( ShiftLeft( t, 16, 3 ) == 0xbfffe000 );
  }
  
  {
    // ExtractBits( char, number, number )
    
    char t = 0x14;

    test( ExtractBits( t, 2, 3 ) == 5 );
    t = 0xc0;
    test( ExtractBits( t, 6, 2 ) == 3 );
  }

  {
    // ExtractBits( short, number, number )
    
    short t = 0x0080;

    test( ExtractBits( t, 7, 1 ) == 1 );
    t = 0x0300;
    test( ExtractBits( t, 7, 3 ) == 6 );
  }

  {
    // ExtractBits( unsigned short, number, number )
    
    unsigned short t = 0xf000;

    test( ExtractBits( t, 12, 4 ) == 0x000f );
  }
  
  {
    // ExtractBits( int, number, number )
    
    int t = 0xff00;

    test( ExtractBits( t, 6, 4 ) == 12 );
  }

  {
    // ExtractBits( unsigned int, number, number )
    
    unsigned int t = 0xffff;

    test( ExtractBits( t, 12, 2 ) == 3 );
  }

  {
    // ExtractBits( long, number, number )
    
    long t = 0x03000000;

    test( ExtractBits( t, 22, 5 ) == 12 );
  }
      
  {
    // ExtractBits( unsigned long, number, number )
    
    unsigned long t = 0xfb000000;

    test( ExtractBits( t, 22, 5 ) == 12 );
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
    test( d == 0x30 );

    int iv = 0xfffff;
    
    SetBits( d, iv, 16, 5 );
    test( d == 0x001f0030 );

    short sv = 0x0c1;
    SetBits( d, sv, 23, 9 );
    test( d == 0x609f0030 );
  }
  
  return( true );
  
}

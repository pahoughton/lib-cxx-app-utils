//
// File:        tBit.C
// Project:	Clue
// Desc:        
//
//  Tests for Bit Constants, Macros, and functions found
//  in Bit.hh & Bit.ii
//  
// Source Header Version: 2.3
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/28/96 07:02
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Bit.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Bit.hh>
#endif

bool
tBit( LibTest & tester )
{
  {
    // CHAR_BITS
    // SHORT_BITS
    // INT_BITS
    // LONG_BITS
    
    TEST( CHAR_BITS == CHAR_BIT );
    TEST( SHORT_BITS == ( sizeof(short) * CHAR_BITS ) );
    TEST( INT_BITS == ( sizeof(int) * CHAR_BITS ) );
    TEST( LONG_BITS == ( sizeof(long) * CHAR_BITS ) );
  }

  {
    // CHAR_ALL_BITS
    // SHORT_ALL_BITS
    // LONG_ALL_BITS
    // INT_ALL_BITS

    TEST( CHAR_ALL_BITS == (unsigned char)(~0L ) );
    TEST( SHORT_ALL_BITS == (unsigned short)(~0L ) );
    TEST( LONG_ALL_BITS == (unsigned long)(~0L ) );
    TEST( INT_ALL_BITS == (unsigned int)(~0 ) );
  }
      
  {
    // Bit( number )
    for( int i = 0; i < 32; i++ )
      {
	TEST( Bit( i ) == (1 << i) );
      }

    TEST( Bit( 0 ) == 0x01 );
    TEST( Bit( 2 ) == 0x04 );
    TEST( Bit( 4 ) == 0x10 );
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

    TEST( BitSizeof( tChar ) == CHAR_BIT );
    TEST( BitSizeof( tShort ) == ( CHAR_BIT * sizeof( tShort ) ) );
    TEST( BitSizeof( tLong ) == ( CHAR_BIT * sizeof( tLong ) ) );
    TEST( BitSizeof( tInt ) == ( CHAR_BIT * sizeof( tInt ) ) );
  }

  {
    // StripHigh( char, number )

    char t = 0xf5;

    TEST( StripHigh( t, 6 ) == 0x35 );
    t = 0x80;
    TEST( StripHigh( t, 7 ) == 0x00 );
    t = 0x45;
    TEST( StripHigh( t, 7 ) == 0x45 );
    t = 0x1f;
    TEST( StripHigh( t, 6 ) == 0x1f );
    t = 0x1f;
    TEST( StripHigh( t, 4 ) == 0x0f );
    t = 0xff;
    TEST( StripHigh( t, 1 ) == 0x01 );
    t = 0xff;
    TEST( StripHigh( t, 3 ) == 0x07 ); // doc example
  }

  {
    // StripHigh( short, number )

    short t = 0x3fff;

    TEST( StripHigh( t, 11 ) == 0x07ff );
  }

  {
    // StripHigh( unsigned short, number )
    
    unsigned short t = 0xffff;

    TEST( StripHigh( t, 10 ) == 0x03ff );
  }

  {
    // StripHigh( int, number )
    
    if( sizeof( int ) == 4 )
      {
	int t = 0x1fffffff;
	TEST( INT_ALL_BITS == 0xffffffff );
	TEST( StripHigh( t, 16 ) == 0x0000ffff );
      }
    else
      {
	int t = 0x1fff;

	TEST( INT_ALL_BITS == 0xffff );
	TEST( StripHigh( t, 8 ) == 0x00ff );
      }
  }

  {
    // StripHigh( unsigned int, number )
    
    if( sizeof( int ) == 4 )
      {
	unsigned int t = 0xffffffff;

	TEST( StripHigh( t, 16 ) == 0xffff );
      }
    else
      {
	unsigned int t = 0xffff;

	TEST( StripHigh( t, 8 ) == 0x00ff );
      }
  }

  {
    // StripHigh( long value, number )
    
    long t = 0x0fffffff;

    TEST( StripHigh( t, 4 ) == 0x0000000f );
  }
  
  {
    // StripHigh( unsigned long, number )
    unsigned long t = 0xffffffff;

    TEST( StripHigh( t, 1 ) == 0x00000001 );
  }

  {
    // StripLow( unsigned char, number )
    
    unsigned char t = 0xff;

    TEST( StripLow( t, 4 ) == 0xf0 );
    TEST( StripLow( t, 7 ) == 0x80 );
    TEST( StripLow( t, 1 ) == 0xfe );
    TEST( StripLow( t, 3 ) == 0xf8 );	// doc example
  }

  {
    // StripLow( long, number )
    
    long t = 0x1fffffff;

    TEST( StripLow( t, 4 ) == 0x1ffffff0 );
    TEST( StripLow( t, 28 ) == 0x10000000 );
  }

  {
    // ShiftRight( char, number )
    
    char t = 0x5f;

    TEST( ShiftRight( t, 3 ) == 0x0b );
    TEST( ShiftRight( t, 6 ) == 0x01 );
  }

  {
    // ShiftRight( long, number )
    long t = 0x03000000;

    TEST( ShiftRight( t, 8  ) == 0x030000 );
    TEST( ShiftRight( t, 28 ) == 0x0 );
    TEST( ShiftRight( t, 24 ) == 0x03 );
  }

  {
    // ShiftLeft( unsigned char, number )

    unsigned char t = 0x35;
    TEST( ShiftLeft( t, 4 ) == 0xA8 ); // doc example
  }
  
    
  {
    // ShiftLeft( unsigned char, number, number )
    
    unsigned char t = 0x06;

    TEST( ShiftLeft( t, 1, 2 ) == 0xc0 );
    t = 0x34;
    TEST( ShiftLeft( t, 4, 3 ) == 0x68 ); // doc example
    TEST( ShiftLeft( t, 3, 3 ) == 0xd0 ); // doc example
    t = 3;
    TEST( ShiftLeft( t, 0, 3 ) == 0x60 ); // doc example
    TEST( ShiftLeft( t, 3, 0 ) == 0x60 ); // doc example 
  }

  {
    // ShiftLeft( unsigned long, number, number )
    
    unsigned long t = 0xff0dffff;
    
    TEST( ShiftLeft( t, 16, 3 ) == 0xbfffe000 );
  }
  
  {
    // ExtractBits( char, number, number )
    
    char t = 0x14;

    TEST( ExtractBits( t, 2, 3 ) == 5 );
    t = 0xc0;
    TEST( ExtractBits( t, 6, 2 ) == 3 );
    t = 0x34;
    TEST( ExtractBits( t, 4, 3 ) == 0x03 ); // doc example
    TEST( ExtractBits( t, 3, 3 ) == 0x06 ); // doc example
  }

  {
    // ExtractBits( short, number, number )
    
    short t = 0x0080;

    TEST( ExtractBits( t, 7, 1 ) == 1 );
    t = 0x0300;
    TEST( ExtractBits( t, 7, 3 ) == 6 );
  }

  {
    // ExtractBits( unsigned short, number, number )
    
    unsigned short t = 0xf000;

    TEST( ExtractBits( t, 12, 4 ) == 0x000f );
  }
  
  {
    // ExtractBits( int, number, number )
    
    int t = 0xff00;

    TEST( ExtractBits( t, 6, 4 ) == 12 );
  }

  {
    // ExtractBits( unsigned int, number, number )
    
    unsigned int t = 0xffff;

    TEST( ExtractBits( t, 12, 2 ) == 3 );
  }

  {
    // ExtractBits( long, number, number )
    
    long t = 0x03000000;

    TEST( ExtractBits( t, 22, 5 ) == 12 );
  }
      
  {
    // ExtractBits( unsigned long, number, number )
    
    unsigned long t = 0xfb000000;

    TEST( ExtractBits( t, 22, 5 ) == 12 );
  }

  {
    // SetBits( unsigned char, int, number, number );

    unsigned char dest = CHAR_ALL_BITS;

    SetBits( dest, 0x0a, 1, 5 );
    TEST( dest == 0xD5 );	// doc example
    
    dest = CHAR_ALL_BITS;
    SetBits( dest, 3, 4, 3 );
    TEST( dest == 0xbf );	// doc example
    
    dest = CHAR_ALL_BITS;
    SetBits( dest, 6, 3, 3 );
    TEST( dest == 0xf7 );	// doc example

    dest = 0;
    SetBits( dest, 3, 4, 3 );
    TEST( dest == 0x30 );	// doc example

    dest = 0;
    SetBits( dest, 6, 3, 3 );
    TEST( dest == 0x30 );	// doc example
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
    TEST( d == 0x30 );

    int iv = 0xfffff;
    
    SetBits( d, iv, 16, 5 );
    TEST( d == 0x001f0030 );

    short sv = 0x0c1;
    SetBits( d, sv, 23, 9 );
    TEST( d == 0x609f0030 );
  }
  
  return( true );
  
}

//
// $Log$
// Revision 2.2  1996/11/04 14:45:21  houghton
// Added header comments.
// Changed so that everything in Bit.hh is tested.
//
//

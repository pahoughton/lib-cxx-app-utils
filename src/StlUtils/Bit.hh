#ifndef _Bit_hh_
#define _Bit_hh_
//
// File:        Bit.hh
// Desc:        
//
//
// NOTES: This is my understanding of the C++ standard
//
// CHAR_BIT comes from climits
//
// 1 = sizeof( char ) <= sizeof( short ) <= sizeof( int ) <= sizeof( long )
// 
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     02/22/95 09:46
//
// Revision History:
//
// $Log$
// Revision 1.3  1995/11/05 15:28:30  houghton
// Revised
//
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <cstddef>
#include <climits>
#else
#include <ClueCfg.hh>
#include <cstddef>
#include <climits>
#endif

#define Bit( _b_ ) ( 1 << _b_ )


#define CHAR_BITS   CHAR_BIT
#define SHORT_BITS  ( sizeof(short) * CHAR_BITS)
#define INT_BITS    ( sizeof(int) * CHAR_BITS)
#define LONG_BITS   ( sizeof(long) * CHAR_BITS)


#define CHAR_ALL_BITS	((unsigned char)(~0))  // 0xff
#define SHORT_ALL_BITS	((unsigned short)(~0)) // 0xffff
#define LONG_ALL_BITS	((unsigned long)(~0L)) // 0xffffffff
#define INT_ALL_BITS	((unsigned int)(~0))   // 0xffff | 0xffffffff

//
// Functions in Bit.ii
//
// template<T>
//
// T StripHigh( T value, int keepCount )
// T StripLow( T value, int count )
// T ShiftRight( T value, int count )
// T ShiftLeft( T value, int start, int len )
// T ExtractBits( T value, int start, int len )
// T SetBits( T value, int start, int len )
//
// start is right to left begining with bit 0
// len is right to left begining with bit 'start'
//
// ShiftLeft( 00110100, 4, 3 ) == 01101000
// ShiftLeft( 00110100, 3, 3 ) == 11010000
// ShiftLeft( 011, 0, 3 ) == 00011000
// ShiftLeft( 011, 3, 0 ) == 00011000
//
// ExtractBits( 00110100, 4, 3 ) == 00000011
// ExtractBits( 00110100, 3, 3 ) == 00000110
//
// SetBits( dest, 3, 4, 3 ) == x011xxxx  (x means not modified)
// SetBits( dest, 6, 3, 3 ) == xx110xxx  (x means not modified)
//

#include <Bit.ii>

#endif // ! def _Bit_hh_ 

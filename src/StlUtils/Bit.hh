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
// Revision 2.2  1995/11/10 14:08:33  houghton
// Updated documentation comments
//
// Revision 2.1  1995/11/10  12:40:15  houghton
// Change to Version 2
//
// Revision 1.4  1995/11/06  11:59:47  houghton
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

#if !defined( CHAR_ALL_BITS )

#define Bit( _b_ ) ( 1 << _b_ )

#define CHAR_BITS   CHAR_BIT
#define SHORT_BITS  ( sizeof(short) * CHAR_BITS)
#define INT_BITS    ( sizeof(int) * CHAR_BITS)
#define LONG_BITS   ( sizeof(long) * CHAR_BITS)


#define CHAR_ALL_BITS	((unsigned char)(~0))  // 0xff
#define SHORT_ALL_BITS	((unsigned short)(~0)) // 0xffff
#define LONG_ALL_BITS	((unsigned long)(~0L)) // 0xffffffff
#define INT_ALL_BITS	((unsigned int)(~0))   // 0xffff | 0xffffffff

#endif

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
// T SetBits( Dest dest, T setValue, int start, int len )
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

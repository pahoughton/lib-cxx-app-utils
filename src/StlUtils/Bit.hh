#ifndef _Bit_hh_
#define _Bit_hh_
/**
   File:        Bit.hh
   Project:	StlUtils ()
   Desc:        
  
    This is a collection of defines and macros and inline functions
    to help with bit manipulations.
  
   Notes:
  
    This is my understanding of the C++ standard
  
    CHAR_BIT comes from climits
  
    1 == sizeof( char ) <= sizeof( short ) <= sizeof( int ) <= sizeof( long )
  
   Author:      Paul Houghton - (paul4hough@gmail.com)
   Created:     02/22/95 09:46
  
   Revision History: (See end of file for Revision Log)
  
   $Id$ 
   
**/


#include "StlUtilsConfig.hh"
#include <cstddef>
#include <climits>

#if !defined( CHAR_ALL_BITS )

#define CHAR_BITS   CHAR_BIT
#define SHORT_BITS  ( sizeof(short) * CHAR_BITS)
#define INT_BITS    ( sizeof(int) * CHAR_BITS)
#define LONG_BITS   ( sizeof(long) * CHAR_BITS)


#define CHAR_ALL_BITS	((unsigned char)(~0))  // 0xff
#define SHORT_ALL_BITS	((unsigned short)(~0)) // 0xffff
#define LONG_ALL_BITS	((unsigned long)(~0L)) // 0xffffffff
#define INT_ALL_BITS	((unsigned int)(~0))   // 0xffff | 0xffffffff

#define Bit( _b_ ) ( 1 << _b_ )

#endif // ! def( CHAR_ALL_BITS )

#include "Bit.ii"

/**
   Detail Documentation:
  
    Defines:
  
  	CHAR_BITS
  	    The number of bits in a 'char' (normally 8).
  
  	SHORT_BITS
  	    The number of bits in a 'short'.
  
  	INT_BITS
  	    The number of bits in a 'int'.
  
  	LONG_BITS
  	    The number of bits in a 'long'.
  
  	CHAR_ALL_BITS
  	    A 'char' with all bits set to 1.
  
  	SHORT_ALL_BITS
  	    A 'short' with all bits set to 1.
  
  	INT_ALL_BITS
  	    An 'int' with all bits set to 1.
  
  	LONG_ALL_BITS
  	    A 'long' with all bits set to 1.
  
    Macros:
  
  	Bit( n )
  	    A number with it's 'n' bit turned on. (i.e. Bit(0) == 00000001,
  	    Bit(3) == '000001000' ).
  
    Functions:
  
  	template< class T > inline
  	size_t
  	BitSizeof( T value )
  	    Return the number of bits in 'value'.
  
  	template< class T, class NumberType > inline
  	T
  	StripHigh( T value, NumberType keepCount )
  	    Returns value with it's high bits set to 0 without
  	    changing the first 'keepCount' bits.
  	    (i.e. StripHigh( '11111111', 3 ) == '00000111' ).
  
  	template< class T, class NumberType > inline
  	T
  	StripLow( T value, NumberType stripCount )
  	    Returns value with it's low 'stripCount' bits set to 0.
  	    (i.e. StripLow( '11111111', 3 ) == '11111000' ).
  
  	template< class T, class NumberType > inline
  	T
  	ShiftRight( T value, NumberType count )
  	    Returns value shifted right by count bits. This function
  	    is just like the '>>' operator except it does a modulo (%)
  	    on count using BitSizeof(T).
  	    (i.e. ShiftRight( char, 4 ) == ShiftRight( char, 20 ) ).
  
  	template< class T, class NumberType > inline
  	T
  	ShiftLeft( T value, NumberType start )
  	    Returns value shifted left so that bit 'start' is the leftmost
  	    bit. 'start' is right to left begining with 0 and
  	    is modulod with BitSize(T) to prevent overflow.
  	    (i.e. ShiftLeft( (char)(00110101), 4 ) == 10101000 ).
  
  	template< class T, class NumberType > inline
  	T
  	ShiftLeft( T value, NumberType start, NumberType len )
  	    Returns value shifted left so the bit at 'start' + 'len' is
  	    the leftmost bit. 'start' is right to left begining with 0 and
  	    is modulod with BitSize(T) to prevent overflow. 'len' is right to
  	    left begining with bit 'start'. 
  	    (i.e. ShiftLeft( (char)'00101000', 3, 3 ) == '10100000').
  
  	template< class T, class NumberType > inline
  	T
  	ExtractBits( T value, NumberType start, NumberType len )
  	    Returns the value of the bits in 'value' from 'start' to 'len'.
  	    Where 'start' is right to left begining with a 0 and 'len'
  	    is right to left begining with start'.
  	    (i.e. ExtractBits( 00110100, 4, 3 ) == 00000011 and
  	    ExtractBits( 00110100, 3, 3 ) == 00000110 ).
  
  	template< class Dest, class T, class NumberType > inline
  	void
  	SetBits( Dest & dest, Value value, NubmerType start, NumberType len )
  	    Sets the bits in dest from start to len to the value specified
  	    by 'value'. Where 'start' is right to left begining with a 0
  	    and 'len' is right to left begining with start'.
  	    (i.e. dest = '11111111'; SetBits( dest, '01010', 1, 5 );
  	    dest == '11010101').
  
  
    Example:
  
  	StripHigh( 11111111, 3 ) == 00000111
  
  	StripLow( 11111111, 3 ) == 11111000
  
  	ShiftLeft( 00110101, 4 ) == 10101000
  
  	ShiftLeft( 00110100, 4, 3 ) == 01101000
  	ShiftLeft( 00110100, 3, 3 ) == 11010000
  	ShiftLeft( 011, 0, 3 ) == 01100000
  	ShiftLeft( 011, 3, 0 ) == 01100000
  
  	ExtractBits( 00110100, 4, 3 ) == 00000011
  	ExtractBits( 00110100, 3, 3 ) == 00000110
  
  	SetBits( dest, 3, 4, 3 ) == x011xxxx  (x means not modified)
  	SetBits( dest, 6, 3, 3 ) == xx110xxx  (x means not modified)
  
   See Also:
  
    Bitmask(3)
  
   Files:
  
    Bit.hh, Bit.ii
  
   
   Documented Ver: 2.3
   Tested Ver: 2.3
**/

// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.2  2011/12/30 23:57:10  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:40  houghton
// Changed to version 6
//
// Revision 5.4  2003/08/09 11:20:57  houghton
// Changed ver strings.
//
// Revision 5.3  2001/07/29 19:56:38  houghton
// *** empty log message ***
//
// Revision 5.2  2001/07/26 19:29:01  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:14  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:12:09  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:08:08  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1996/11/19 12:18:37  houghton
// Changed include lines to use " " instead of < > to accomidate rpm.
// Removed support for short file names to accomidate rpm.
//
// Revision 3.1  1996/11/14 01:23:25  houghton
// Changed to Release 3
//
// Revision 2.3  1996/11/04 13:15:33  houghton
// Restructure header comments layout.
// Updated and verified header comment documentation.
//
// Revision 2.2  1995/11/10 14:08:33  houghton
// Updated documentation comments
//
// Revision 2.1  1995/11/10  12:40:15  houghton
// Change to Version 2
//
// Revision 1.4  1995/11/06  11:59:47  houghton
// Revised
//


#endif // ! def _Bit_hh_ 

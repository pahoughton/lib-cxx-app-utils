#ifndef _Bit_hh_
#define _Bit_hh_
//
// File:        Bit.hh
// Desc:        
//
//
//  Quick Start: - short example of class usage
//
//  Data Types: - data types defined by this header
//
//  	Bit	class
//
//  Constructors:
//
//  	Bit( );
//
//  Destructors:
//
//  Public Interface:
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. Bit )
//
//  	virtual Bool
//  	good( void ) const;
//  	    Returns true if there are no detected errors associated
//  	    with this class, otherwise FALSE.
//
//  	virtual const char *
//  	error( void ) const
//  	    Returns as string description of the state of the class.
//
//  Protected Interface:
//
//  Private Methods:
//
//  Other Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const Bit & obj );
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     02/22/95 09:46
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/03/02 16:35:30  houghton
// Linux ports & new Classes
//
//

#include <Bit.h>

inline
char
StripHigh( char value, int count )
{
  return( (CHAR_ALL_BITS >> count) & value );
}

inline
short
StripHigh( short value, int count )
{
  return( (SHORT_ALL_BITS >> count) & value );
}

inline
unsigned short
StripHigh( unsigned short value, int count )
{
  return( (SHORT_ALL_BITS >> count) & value );
}

inline
int
StripHigh( int value, int count )
{
  return( (INT_ALL_BITS >> count) & value );
}

inline
unsigned int
StripHigh( unsigned int value, int count )
{
  return( (INT_ALL_BITS >> count) & value );
}


inline
long
StripHigh( long value, int count )
{
  return( (LONG_ALL_BITS >> count) & value );
}

inline
unsigned long
StripHigh( unsigned long value, int count )
{
  return( (LONG_ALL_BITS >> count) & value );
}

inline
char
ShiftRight( char value, unsigned long start, unsigned long len )
{
  return( value >> (CHAR_BITS - ((start % CHAR_BITS) + len )) );
}

inline
short
ShiftRight( short value, unsigned long start, unsigned long len )
{
  return( value >> (SHORT_BITS - ((start % SHORT_BITS) + len )) );
}

inline
unsigned short
ShiftRight( unsigned short value, unsigned long start, unsigned long len )
{
  return( value >> (SHORT_BITS - ((start % SHORT_BITS) + len )) );
}

inline
int
ShiftRight( int value, unsigned long start, unsigned long len )
{
  return( value >> (INT_BITS - ((start % INT_BITS) + len )) );
}

inline
unsigned int
ShiftRight( unsigned int value, unsigned long start, unsigned long len )
{
  return( value >> (INT_BITS - ((start % INT_BITS) + len )) );
}

inline
long
ShiftRight( long value, unsigned long start, unsigned long len )
{
  return( value >> (LONG_BITS - ((start % LONG_BITS) + len )) );
}

inline
unsigned long
ShiftRight( unsigned long value, unsigned long start, unsigned long len )
{
  return( value >> (LONG_BITS - ((start % LONG_BITS) + len )) );
}



#endif // ! def _Bit_hh_ 
//
//              This software is the sole property of
// 
//                 The Williams Companies, Inc.
//                        1 Williams Center
//                          P.O. Box 2400
//        Copyright (c) 1995 by The Williams Companies, Inc.
// 
//                      All Rights Reserved.  
// 
//

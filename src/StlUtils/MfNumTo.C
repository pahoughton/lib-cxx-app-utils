//
// File:        MfNumTo.C
// Project:	StlUtils
// Desc:        
//
//  The mainframe uses the high nibble (4 bits) of the last char
//  to indicate + or - sign.
//
//  This table show the conversion
//
//	Last Char   Value	pos/neg
//
//	{	    0		pos
//	A	    1		pos
//	B	    2		pos
//	C	    3		pos
//	D	    4		pos
//	E	    5		pos
//	F	    6		pos
//	G	    7		pos
//	H	    8		pos
//	I	    9		pos
//
//	}	    0		neg
//	J	    1		neg
//	K	    2		neg
//	L	    3		neg
//	M	    4		neg
//	N	    5		neg
//	O	    6		neg
//	P	    7		neg
//	Q	    8		neg
//	R	    9		neg
//
// Author:      Paul Houghton - (houghton@cworld.wcom.com)
// Created:     11/18/97 06:25
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include "StringUtils.hh"
#include <cctype>
#define MF_NUM_TO_TYPE( type )							\
bool										\
MfNumTo(									\
  type	&	dest,								\
  const char *	src,								\
  size_t	len								\
  )										\
{										\
  size_t srcLen = (len == NPOS ? strlen( src ) : len);				\
										\
  char	lastDigit = src[ srcLen - 1 ];						\
										\
  if( ! StringTo( dest, src, 10, srcLen ) )					\
    return( false );								\
										\
  dest *= 10;									\
  										\
  if( ! isdigit( lastDigit ) )							\
    {										\
      if( lastDigit == '{' )							\
	return( true );								\
										\
      if( lastDigit == '}' )							\
	{									\
	  dest *= -1;								\
	  return( true );							\
	}									\
										\
      if( lastDigit >= 'A' && lastDigit <= 'I' )				\
	{									\
	  dest += lastDigit - 'A';						\
	  return( true );							\
	}									\
										\
      if( lastDigit >= 'J' && lastDigit <= 'R' )				\
	{									\
	  dest += lastDigit - 'J';						\
	  dest *= -1;								\
	  return( true );							\
	}									\
										\
      return( false );								\
    }										\
  else										\
    {										\
      dest += lastDigit - '0';							\
      return( true );								\
    }										\
}

#define MF_NUM_TO_TYPE_RET( type, typeName )					\
type										\
MfNumTo##typeName(								\
  const char *	src,								\
  size_t	len								\
  )										\
{										\
  type	val = 0;								\
  MfNumTo( val, src, len );							\
  return( val );								\
}
  
MF_NUM_TO_TYPE( short );
MF_NUM_TO_TYPE( int );
MF_NUM_TO_TYPE( long );

MF_NUM_TO_TYPE_RET( short, Short );
MF_NUM_TO_TYPE_RET( int, Int );
MF_NUM_TO_TYPE_RET( long, Long );


// Revision Log:
//
// $Log$
// Revision 4.1  1997/11/18 15:07:42  houghton
// Initial Version.
//
//

/* 1997-11-18 (cc) <paul4hough@gmail.com>

   The mainframe uses the high nibble (4 bits) of the last char
   to indicate + or - sign.

   This table show the conversion

  	Last Char   Value	pos/neg

  	{	    0		pos
  	A	    1		pos
  	B	    2		pos
  	C	    3		pos
  	D	    4		pos
  	E	    5		pos
  	F	    6		pos
  	G	    7		pos
  	H	    8		pos
  	I	    9		pos

  	}	    0		neg
  	J	    1		neg
  	K	    2		neg
  	L	    3		neg
  	M	    4		neg
  	N	    5		neg
  	O	    6		neg
  	P	    7		neg
  	Q	    8		neg
  	R	    9		neg

*/

#include "StringUtils.hpp"
#include <cctype>

namespace clue {

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
  if( src[0] == ' ' && lastDigit == ' ' )					\
    {										\
      dest = 0;									\
      return( true );								\
    }										\
  										\
  if( ! StringTo( dest, src, 10, srcLen - 1 ) )					\
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
	  dest += lastDigit - 'A' + 1;						\
	  return( true );							\
	}									\
										\
      if( lastDigit >= 'J' && lastDigit <= 'R' )				\
	{									\
	  dest += lastDigit - 'J' + 1;						\
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

bool
MfNumTo(
  char *	dest,
  size_t	destSize,
  size_t	decimalPlaces,
  const char *	src,
  size_t	srcSize
  )
{
  size_t srcLen = (srcSize == NPOS ? strlen( src ) : srcSize );

  const char *  srcEnd = src + srcLen - 1;

  if( destSize == NPOS || destSize < srcSize + 1 || destSize < decimalPlaces + 2 )
    return( false );

  bool isNeg = false;

  if( StringFirstNotOf( src, srcLen - 1, " 0123456789", NPOS ) != NPOS )
    {
      return( false );
    }

  if( *src == ' ' && *srcEnd == ' ' )
    {
      memset( dest, '0', destSize );
      if( decimalPlaces )
	dest[ destSize - decimalPlaces - 1 ] = '.';
      return( true );
    }
  else
    {
      if( *srcEnd == '{' )
	{
	  dest[ destSize - 1 ] = '0';
	}
      else
	{
	  if( *srcEnd == '}' )
	    {
	      dest[ destSize - 1 ] = '0';
	      isNeg = true;
	    }
	  else
	    {
	      if( *srcEnd >= 'A' && *srcEnd <= 'I' )
		{
		  dest[ destSize - 1 ] = *srcEnd - 'A' + '1';
		}
	      else
		{
		  if( *srcEnd >= 'J' && *srcEnd <= 'R' )
		    {
		      dest[ destSize - 1 ] = *srcEnd - 'J' + '1';
		      isNeg = true;
		    }
		  else
		    {
		      if( isdigit( *srcEnd ) )
			{
			  dest[ destSize - 1 ] = *srcEnd;
			}
		      else
			{
			  return( false );
			}
		    }
		}
	    }
	}

      // now for the rest of the digits
      if( decimalPlaces )
	{
	  if( decimalPlaces > 1 )
	    memcpy( dest + destSize - decimalPlaces,
		    src + srcSize - decimalPlaces,
		    decimalPlaces - 1 );

	  dest[ destSize - decimalPlaces - 1 ] = '.';

	  if( decimalPlaces < srcSize )
	    {
	      size_t destStartPos = destSize - srcSize - 1;

	      memcpy( dest + destStartPos,
		      src,
		      srcSize - decimalPlaces );

	    }

	  memset( dest, '0', destSize - srcSize - 1 );

	  if( isNeg )
	    dest[0] = '-';
	}
      else
	{
	  memcpy( dest + destSize - srcSize,
		  src,
		  srcSize - 1 );

	  memset( dest, '0', destSize - srcSize );

	  if( isNeg )
	    dest[0] = '-';
	}
    }
  return( true );
}


}; // namespace clue

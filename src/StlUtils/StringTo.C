//
// File:        StringTo.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/06/95 09:31 
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 13:23:38  houghton
// Initaial implementation
//
//

#include "StringUtils.hh"
#include "_Clue.hh"

#include <cstring>
#include <cctype>


static const char * RcsId =
LIB_CLUE_VERSION
"$Id$";


const int _CharToNumber[] =
{
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23, 24,
  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  -1,  -1,  -1,  -1, -1,
  -1,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23, 24,
  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
};

#define WHITE " \t\r\n\f"

static const char *
_StringToNumPrep(
  const char *      string,
  const char *      end,
  unsigned short &  base,
  bool &    	    neg
  )
{
  const char * conv = string;
  
  // skip past white space

  for( ; conv < end && strchr( WHITE, *conv ); conv++ );

  if( conv >= end ) return( 0 );
  
  // look for +/-

  if( *conv == '-' )
    {
      neg = true;
      conv++;
    }
  else
    {
      if( *conv == '+' ) conv++;
    }

  if( conv >= end ) return( 0 );
  
  // determin base
  
  if( base == 0 )
    {
      base = 10;
      if( *conv == '0' )
	{
	  conv++;
	  if( conv < end && tolower( *conv ) == 'x' )
	    {
	      conv++;
	      base = 16;
	    }
	  else
	    {
	      base = 8;
	    }
	}
      else
	{
	  if( tolower( *conv ) == 'x' )
	    {
	      conv++;
	      base = 16;
	    }
	}
    }
  else
    {
      if( base == 16 )
	{
	  if( *conv == '0' )
	    {
	      conv++;
	      if( conv < end && tolower( *conv ) == 'x' )
		{
		  conv++;
		}
	    }
	}
    }
  return( conv );
}

  
#define STRING_TO_TYPE( _type_ )					      \
bool									      \
StringTo(								      \
  _type_ &	    dest,						      \
  const char * 	    src,						      \
  unsigned short    baseToUse,						      \
  size_t    	    len							      \
  )									      \
{									      \
  _type_  value = 0;							      \
									      \
  const char * 	    end = src + ( len ? len : strlen( src ) );		      \
  unsigned short    base = baseToUse;					      \
  bool	    	    neg = false;					      \
									      \
  const char * conv = _StringToNumPrep( src, end, base, neg );		      \
									      \
  if( ! conv || conv >= end )						      \
    {									      \
      if( base == 8 )							      \
	{								      \
	  dest = 0;							      \
	  return( true );						      \
	}								      \
      else								      \
	{								      \
	  return( false );						      \
	}								      \
    }									      \
									      \
  const char * first = conv;						      \
									      \
  for( ; conv < end; conv++ )						      \
    {									      \
      if( IsBaseDigit( *conv, base ) )					      \
	{								      \
	  value *= base;						      \
	  value += CharToInt( *conv );					      \
	}								      \
      else								      \
	{								      \
	  if( conv == first || isdigit( *conv ) ) return( false );	      \
									      \
	  dest = (neg) ? value * -1 : value;				      \
	  return( true );						      \
	}								      \
    }									      \
  dest = (neg) ? value * -1 : value;					      \
  return( true );							      \
}

STRING_TO_TYPE( int )
STRING_TO_TYPE( short )
STRING_TO_TYPE( long )

#define STRING_TO_UTYPE( _type_ )					   \
bool									   \
StringTo(								   \
  _type_ &	    dest,						   \
  const char * 	    src,						   \
  unsigned short    baseToUse,						   \
  size_t    	    len							   \
  )									   \
{									   \
  _type_  value = 0;							   \
									   \
  const char * 	    end = src + ( len ? len : strlen( src ) );		   \
  unsigned short    base = baseToUse;					   \
  bool	    	    neg = false;					   \
									   \
  const char * conv = _StringToNumPrep( src, end, base, neg );		   \
									   \
  if( ! conv || conv >= end ) return( false );				   \
									   \
  const char * first = conv;						   \
  for( ; conv < end; conv++ )						   \
    {									   \
      if( IsBaseDigit( *conv, base ) )					   \
	{								   \
	  value *= base;						   \
	  value += CharToInt( *conv );					   \
	}								   \
      else								   \
	{								   \
	  if( conv == first || isdigit( *conv ) ) return( false );	   \
	  dest = value;							   \
	  return( true );						   \
	}								   \
    }									   \
  dest = value;								   \
  return( true );							   \
}


STRING_TO_UTYPE( unsigned int )
STRING_TO_UTYPE( unsigned short )
STRING_TO_UTYPE( unsigned long )


#include <cmath>

bool
StringTo(
  double &  	    dest,
  const char * 	    src,
  unsigned short    baseToUse,
  size_t    	    len )
{

  double  value = 0;
  
  const char *      end = src + ((len) ? len : strlen( src ) );
  unsigned short    base = baseToUse;
  bool	    	    neg = false;
  
  const char * conv = _StringToNumPrep( src, end, base, neg );

  int	fract = 0;

  if( ! conv || conv >= end ) return( false );

  const char * first = conv;
  
  for( ; conv < end; conv++ )
    {
      if( ! fract && *conv == '.' )
	{
	  fract = 1;
	  continue;
	}
      
      if( IsBaseDigit( *conv, base ) )
	{
	  value *= base;
	  value += CharToInt( *conv );
	  if( fract ) fract++;
	}
      else
	{
	  if( conv == first || isdigit( *conv ) ) return( false );

	  if( fract )
	    {
	      fract--;
	      value *= pow( base, -1 * fract );
	    }
	  dest =  (neg) ? value * -1 : value;
	  return( true );
	}
    }
        
  if( fract )
    {
      fract--;
      value *= pow( base, -1 * fract );
    }
  
  dest =  (neg) ? value * -1 : value;
  return( true );
}

bool
StringTo(
  float &  	    dest,
  const char * 	    src,
  unsigned short    baseToUse,
  size_t    	    len )
{
  double value;

  if( ! StringTo( value, src, baseToUse, len ) )
    return( false );
  
  dest = value;
  return( true );
}
  
  
#define STRING_TO_RET_TYPE( _type_, _name_ )				      \
_type_									      \
StringTo##_name_( const char * src, unsigned short base, size_t  len )	      \
{									      \
  _type_  value = -1;							      \
  StringTo( value, src, base, len );					      \
  return( value );							      \
}									      \

#define STRING_TO_U_RET_TYPE( _type_, _name_ )				      \
_type_									      \
StringTo##_name_( const char * src, unsigned short base, size_t  len )	      \
{									      \
  _type_  value = 0;							      \
  StringTo( value, src, base, len );					      \
  return( value );							      \
}

STRING_TO_RET_TYPE( int, Int )
STRING_TO_RET_TYPE( short, Short )
STRING_TO_RET_TYPE( long, Long )
STRING_TO_RET_TYPE( float, Float )
STRING_TO_RET_TYPE( double, Double )
STRING_TO_U_RET_TYPE( unsigned int, UInt )
STRING_TO_U_RET_TYPE( unsigned short, UShort )
STRING_TO_U_RET_TYPE( unsigned long, ULong )


//
// Bools are special
//

bool
StringToBool(
  bool &    	dest,
  const char *  src,
  size_t    	len
  )
{
  if( isdigit( src[0] ) )
    {
      int num = 0;
      StringTo( num, src, 0, len );
      dest = (num) ? true : false;
      return( true );
    }

  char boolStr[10];
  strncpy( boolStr, src, (len) ? len : sizeof( boolStr ) );
  boolStr[ (len) ? len : (sizeof( boolStr ) - 1) ] = 0;
  StringLower( boolStr );

  if( ! strncmp( boolStr, "true", 4 ) ||
      ! strncmp( boolStr, "yes", 3 ) ||
      ! strcmp( boolStr, "t" ) ||
      ! strcmp( boolStr, "y" ) ||
      ! strncmp( boolStr, "on", 2 ) )
    {
      dest = true;
      return( true );
    }
  
  if( ! strncmp( boolStr, "false", 5 ) ||
      ! strncmp( boolStr, "no", 3 ) ||
      ! strcmp( boolStr, "f" ) ||
      ! strcmp( boolStr, "n" ) ||
      ! strncmp( boolStr, "off", 3 ) )
    {
      dest = false;
      return( true );
    }
  return( false );
}

      
bool
StringToBool(
  const char *  src,
  size_t    	len
  )
{
  bool dest = false;
  StringToBool( dest, src, len );
  return( dest );
}
      

  

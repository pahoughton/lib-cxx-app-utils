//
// File:        StringTo.C
// Project:	StlUtils ()
// Desc:        
//
//  Convert string to a number (See Description at end of file).
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     05/06/95 09:31 
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//


#include "StringUtils.hh"
#include <cstring>
#include <cctype>

STLUTILS_FUNCT_VERSION(
  StringTo,
  "$Id$ " );


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
  size_t    	    len,						      \
  bool		    stopAtNonDigit					      \
  )									      \
{									      \
  _type_  value = 0;							      \
									      \
  const char * 	    end = src + ( len != NPOS ? len : strlen( src ) );	      \
  unsigned short    base = baseToUse;					      \
  bool	    	    neg = false;					      \
									      \
  const char * conv = _StringToNumPrep( src, end, base, neg );		      \
									      \
  if( ! conv || conv >= end )						      \
    {									      \
      dest = 0;								      \
      return( true );							      \
    }									      \
									      \
  for( ; conv < end; conv++ )						      \
    {									      \
      if( CharIsBaseDigit( *conv, base ) )				      \
	{								      \
	  value *= base;						      \
	  value += CharToInt( *conv );					      \
	}								      \
      else								      \
	{								      \
	  if( ! stopAtNonDigit )					      \
	    {								      \
	      return( false );						      \
	    }								      \
	  else								      \
	    {								      \
	      dest = (neg) ? value * -1 : value;			      \
	      return( true );						      \
	    }								      \
	}								      \
    }									      \
									      \
  dest = (neg) ? value * -1 : value;					      \
  return( true );							      \
}									      \

#if defined( DO_NOT_USE_MACRO )
bool
StringTo(
  int &	    dest,
  const char * 	    src,
  unsigned short    baseToUse,
  size_t    	    len
  )
{
  int  value = 0;

  const char * 	    end = src + ( len != NPOS ? len : strlen( src ) );
  unsigned short    base = baseToUse;
  bool	    	    neg = false;

  const char * conv = _StringToNumPrep( src, end, base, neg );

  if( ! conv || conv >= end )
    {
      dest = 0;
      return( true );
    }

  const char * first = conv;

  for( ; conv < end; conv++ )
    {
      if( CharIsBaseDigit( *conv, base ) )
	{
	  value *= base;
	  value += CharToInt( *conv );
	}
      else
	{
	  if( conv == first || isdigit( *conv ) )
	    return( false );

	  dest = (neg) ? value * -1 : value;
	  return( true );
	}
    }
  dest = (neg) ? value * -1 : value;
  return( true );
}

#else
STRING_TO_TYPE( int )
#endif
  
STRING_TO_TYPE( short )
STRING_TO_TYPE( long )
#if defined( STLUTILS_HAVE_LONG_LONG )
STRING_TO_TYPE( long long )
#endif
  
#define STRING_TO_UTYPE( _type_ )					      \
bool									      \
StringTo(								      \
  _type_ &	    dest,						      \
  const char * 	    src,						      \
  unsigned short    baseToUse,						      \
  size_t    	    len,						      \
  bool		    stopAtNonDigit					      \
  )									      \
{									      \
  _type_  value = 0;							      \
									      \
  const char * 	    end = src + ( len != NPOS ? len : strlen( src ) );	      \
  unsigned short    base = baseToUse;					      \
  bool	    	    neg = false;					      \
									      \
  const char * conv = _StringToNumPrep( src, end, base, neg );		      \
									      \
  if( ! conv || conv >= end )						      \
    {									      \
      dest = 0;								      \
      return( true );							      \
    }									      \
									      \
  for( ; conv < end; conv++ )						      \
    {									      \
      if( CharIsBaseDigit( *conv, base ) )				      \
	{								      \
	  value *= base;						      \
	  value += CharToInt( *conv );					      \
	}								      \
      else								      \
	{								      \
	  if( ! stopAtNonDigit )					      \
	    {								      \
	      return( false );						      \
	    }								      \
	  else								      \
	    {								      \
	      dest = value;						      \
	      return( true );						      \
	    }								      \
	}								      \
    }									      \
  dest = value;								      \
  return( true );							      \
}


STRING_TO_UTYPE( unsigned int )
STRING_TO_UTYPE( unsigned short )
STRING_TO_UTYPE( unsigned long )
#if defined( STLUTILS_HAVE_LONG_LONG )
STRING_TO_UTYPE( unsigned long long )
#endif
  
#include <cmath>

bool
StringTo(
  double &  	    dest,
  const char * 	    src,
  unsigned short    baseToUse,
  size_t    	    len,
  bool		    stopAtNonDigit
  )
{

  double  value = 0;
  
  const char *      end = src + ((len != NPOS) ? len : strlen( src ) );
  unsigned short    base = baseToUse;
  bool	    	    neg = false;
  
  const char * conv = _StringToNumPrep( src, end, base, neg );

  int	fract = 0;

  if( ! conv || conv >= end )
    {
      dest = 0;
      return( true );
    }

  for( ; conv < end; conv++ )
    {
      if( ! fract && *conv == '.' )
	{
	  fract = 1;
	  continue;
	}
      
      if( CharIsBaseDigit( *conv, base ) )
	{
	  value *= base;
	  value += CharToInt( *conv );
	  if( fract ) fract++;
	}
      else
	{
	  if( ! stopAtNonDigit )
	    {
	      return( false );
	    }
	  else
	    {
	      
	      if( fract )
		{
		  fract--;
		  value *= pow( (double)base, -1 * fract );
		}
	      dest =  (neg) ? value * -1 : value;
	      return( true );
	    }
	}
    }
        
  if( fract )
    {
      fract--;
      value *= pow( (double)base, -1 * fract );
    }
  
  dest =  (neg) ? value * -1 : value;
  return( true );
}

bool
StringTo(
  float &  	    dest,
  const char * 	    src,
  unsigned short    baseToUse,
  size_t    	    len,
  bool		    stopAtNonDigit
  )
{
  double value;

  if( ! StringTo( value, src, baseToUse, len, stopAtNonDigit ) )
    return( false );
  
  dest = value;
  return( true );
}
  
bool
StringTo(
  struct tm &	dest,
  const char *	src,
  const char *	fmt )
{
  strptime( src, fmt, &dest );
  return( true );
}

#define STRING_TO_RET_TYPE( _type_, _name_ )				      \
_type_									      \
StringTo##_name_(							      \
  const char *	    src,						      \
  unsigned short    base,						      \
  size_t	    len,						      \
  bool		    stopAtNonDigit					      \
  )									      \
{									      \
  _type_  value = 0;							      \
  StringTo( value, src, base, len, stopAtNonDigit );			      \
  return( value );							      \
}

#define STRING_TO_U_RET_TYPE( _type_, _name_ )				      \
_type_									      \
StringTo##_name_(							      \
  const char *	    src,						      \
  unsigned short    base,						      \
  size_t	    len,						      \
  bool		    stopAtNonDigit					      \
  )									      \
{									      \
  _type_  value = 0;							      \
  StringTo( value, src, base, len, stopAtNonDigit );			      \
  return( value );							      \
}

STRING_TO_RET_TYPE( int, Int )
STRING_TO_RET_TYPE( short, Short )
STRING_TO_RET_TYPE( long, Long )
  
#if defined( STLUTILS_HAVE_LONG_LONG )
STRING_TO_RET_TYPE( long long, LongLong )
#endif
  
STRING_TO_RET_TYPE( float, Float )
STRING_TO_RET_TYPE( double, Double )
STRING_TO_U_RET_TYPE( unsigned int, UInt )
STRING_TO_U_RET_TYPE( unsigned short, UShort )
STRING_TO_U_RET_TYPE( unsigned long, ULong )
  
#if defined( STLUTILS_HAVE_LONG_LONG )
STRING_TO_U_RET_TYPE( unsigned long long, ULongLong )
#endif

//
// Bools are special
//

bool
StringTo(
  bool &    	dest,
  const char *  src,
  size_t    	len
  )
{
  if( ! src )
    return( false );

  if( src[0] == 0 )
    {
      dest = false;
      return( true );
    }
  
  if( isdigit( src[0] ) )
    {
      int num = 0;
      StringTo( num, src, 0, len );
      dest = (num) ? true : false;
      return( true );
    }

  if( ( (len == 1 || (len == NPOS && src[1] == 0 ) ) &&
	( tolower( src[0] ) == 't' || tolower( src[0] ) == 'y' ) ) ||
	
      ! StringCaseCompare( src, "true", (len && len < 4) ? len : 4 ) ||
      ! StringCaseCompare( src, "yes", (len && len < 3) ? len : 3 ) ||
      ! StringCaseCompare( src, "on", (len && len < 2) ? len : 2 ) )
    {
      dest = true;
      return( true );
    }

  if( ( (len == 1 || (len == NPOS && src[1] == 0 ) ) &&
	( tolower( src[0] ) == 'f' ||
	  tolower( src[0] ) == 'n' ||
	  tolower( src[0] ) == ' ' ) ) ||
      ! StringCaseCompare( src, "false", ( (len != NPOS && len < 4) ?
					   len : 4 ) ) ||
      ! StringCaseCompare( src, "no", (len != NPOS && len < 2) ? len : 2 ) ||
      ! StringCaseCompare( src, "off", (len != NPOS && len < 3) ? len : 3 ) )
    {
      dest = false;
      return( true );
    }

  const char * c = src;
  
  for( ; ((len != NPOS && ((size_t)(c - src)) < len) || *c != 0) &&
	 *c == ' '; c++ );

  if( (len != NPOS &&  ((size_t)(c - src)) == len ) || *c == 0 )
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
  StringTo( dest, src, len );
  return( dest );
}

struct tm
StringToTm( const char * src, const char * fmt )
{
  struct tm dest;
  strptime( src, fmt, &dest );
  return( dest );
}

//
// Description:
//
//	bool
//	StringTo( bool & 	    	dest,
//		  const char *  	str,
//		  size_t 	    	len = NPOS );
//	    Set dest by converting str to a bool value. If str is
//	    'yes', 'true', 'on', 't', 'y' or a non zero number, dest
//	    will be set to true (case is ignored). If str is 'no',
//	    'false', 'off', 'f', 'n', ' ' or '0', dest will be
//	    set to true. Returns true if dest was set or false if
//	    str could not be converted.
//
//	bool
//	StringTo( int &     	    dest,
//		  const char * 	    str,
//		  unsigned short    base = 0,
//		  size_t    	    len = NPOS );
//	    Set dest by converting str to a numeric value. base is
//	    the base to use for the conversion (i.e. 8 = for oct,
//	    10 for dec, 16 for hex), it can be any value between
//	    2 and 36 or 0. If base is zero the beginning of str is
//	    used to determine base. If it is 0x or 0X the base is 16.
//	    If it is 0 the base is 8. Otherwise the base is 10.
//	    Returns true if dest was set or false if str could
//	    not be converted.
//	
//	bool
//	StringTo( short &     	    dest,
//		  const char * 	    str,
//		  unsigned short    base = 0,
//		  size_t    	    len = NPOS );
//	    Set dest by converting str to a numeric value. base is
//	    the base to use for the conversion (i.e. 8 = for oct,
//	    10 for dec, 16 for hex), it can be any value between
//	    2 and 36 or 0. If base is zero the beginning of str is
//	    used to determine base. If it is 0x or 0X the base is 16.
//	    If it is 0 the base is 8. Otherwise the base is 10.
//	    Returns true if dest was set or false if str could
//	    not be converted.
//	
//	bool
//	StringTo( long &     	    dest,
//		  const char * 	    str,
//		  unsigned short    base = 0,
//		  size_t    	    len = NPOS );
//	    Set dest by converting str to a numeric value. base is
//	    the base to use for the conversion (i.e. 8 = for oct,
//	    10 for dec, 16 for hex), it can be any value between
//	    2 and 36 or 0. If base is zero the beginning of str is
//	    used to determine base. If it is 0x or 0X the base is 16.
//	    If it is 0 the base is 8. Otherwise the base is 10.
//	    Returns true if dest was set or false if str could
//	    not be converted.
//	
//	bool
//	StringTo( float &     	    dest,
//		  const char * 	    str,
//		  unsigned short    base = 0,
//		  size_t    	    len = NPOS );
//	    Set dest by converting str to a numeric value. base is
//	    the base to use for the conversion (i.e. 8 = for oct,
//	    10 for dec, 16 for hex), it can be any value between
//	    2 and 36 or 0. If base is zero the beginning of str is
//	    used to determine base. If it is 0x or 0X the base is 16.
//	    If it is 0 the base is 8. Otherwise the base is 10.
//	    Returns true if dest was set or false if str could
//	    not be converted.
//	
//	bool
//	StringTo( double &     	    dest,
//		  const char * 	    str,
//		  unsigned short    base = 0,
//		  size_t    	    len = NPOS );
//	    Set dest by converting str to a numeric value. base is
//	    the base to use for the conversion (i.e. 8 = for oct,
//	    10 for dec, 16 for hex), it can be any value between
//	    2 and 36 or 0. If base is zero the beginning of str is
//	    used to determine base. If it is 0x or 0X the base is 16.
//	    If it is 0 the base is 8. Otherwise the base is 10.
//	    Returns true if dest was set or false if str could
//	    not be converted.
//	
//	bool
//	StringTo( unsigned int &    dest,
//		  const char * 	    str,
//		  unsigned short    base = 0,
//		  size_t    	    len = NPOS );
//	    Set dest by converting str to a numeric value. base is
//	    the base to use for the conversion (i.e. 8 = for oct,
//	    10 for dec, 16 for hex), it can be any value between
//	    2 and 36 or 0. If base is zero the beginning of str is
//	    used to determine base. If it is 0x or 0X the base is 16.
//	    If it is 0 the base is 8. Otherwise the base is 10.
//	    Returns true if dest was set or false if str could
//	    not be converted.
//	
//	bool
//	StringTo( unsigned short &  dest,
//		  const char * 	    str,
//		  unsigned short    base = 0,
//		  size_t    	    len = NPOS );
//	    Set dest by converting str to a numeric value. base is
//	    the base to use for the conversion (i.e. 8 = for oct,
//	    10 for dec, 16 for hex), it can be any value between
//	    2 and 36 or 0. If base is zero the beginning of str is
//	    used to determine base. If it is 0x or 0X the base is 16.
//	    If it is 0 the base is 8. Otherwise the base is 10.
//	    Returns true if dest was set or false if str could
//	    not be converted.
//	
//	bool
//	StringTo( unsigned long &   dest,
//		  const char * 	    str,
//		  unsigned short    base = 0,
//		  size_t    	    len = NPOS );
//	    Set dest by converting str to a numeric value. base is
//	    the base to use for the conversion (i.e. 8 = for oct,
//	    10 for dec, 16 for hex), it can be any value between
//	    2 and 36 or 0. If base is zero the beginning of str is
//	    used to determine base. If it is 0x or 0X the base is 16.
//	    If it is 0 the base is 8. Otherwise the base is 10.
//	    Returns true if dest was set or false if str could
//	    not be converted.
//	
//	bool
//	StringToBool( const char * str, size_t len = NPOS );
//	    Uses StringTo to convert the str and returns
//	    the value. If StringTo returned false, 'false' is returned.
//	
//	int
//	StringToInt( const char *   str,
//		     unsigned short base = 0,
//		     size_t	    len = NPOS );
//	    Uses StringTo to convert the str and returns the
//	    value. If StringTo returned false, 0 is returned.
//	
//	short
//	StringToShort( const char *	str,
//		       unsigned short	base = 0,
//		       size_t		len = NPOS );
//	    Uses StringTo to convert the str and returns the
//	    value. If StringTo returned false, 0 is returned.
//	
//	long
//	StringToLong( const char *	str,
//		      unsigned short	base = 0,
//		      size_t		len = NPOS );
//	    Uses StringTo to convert the str and returns the
//	    value. If StringTo returned false, 0 is returned.
//	
//	float
//	StringToFloat( const char *	str,
//		       unsigned short	base = 0,
//		       size_t		len = NPOS );
//	    Uses StringTo to convert the str and returns the
//	    value. If StringTo returned false, 0 is returned.
//	
//	double
//	StringToDouble( const char *	str,
//			unsigned short  base = 0,
//			size_t          len = NPOS );
//	    Uses StringTo to convert the str and returns the
//	    value. If StringTo returned false, 0 is returned.
//	
//	unsigned int
//	StringToUInt( const char *	str,
//		      unsigned short	base = 0,
//		      size_t		len = NPOS );
//	    Uses StringTo to convert the str and returns the
//	    value. If StringTo returned false, 0 is returned.
//	
//	unsigned short
//	StringToUShort( const char *	str,
//			unsigned short  base = 0,
//			size_t		len = NPOS );
//	    Uses StringTo to convert the str and returns the
//	    value. If StringTo returned false, 0 is returned.
//	
//	unsigned long
//	StringToULong( const char *	str,
//		       unsigned short	base = 0,
//		       size_t		len = NPOS );
//	    Uses StringTo to convert the str and returns the
//	    value. If StringTo returned false, 0 is returned.
//	
//
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.2  2011/12/30 23:57:21  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:43  houghton
// Changed to version 6
//
// Revision 5.3  2003/08/09 11:21:00  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:28:58  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:18  houghton
// Changed Version Num to 5
//
// Revision 4.6  1999/05/09 13:06:41  houghton
// Added long long support.
//
// Revision 4.5  1999/05/09 11:32:42  houghton
// Cleanup.
//
// Revision 4.4  1998/08/13 10:53:21  houghton
// Port(Hpux10): had to cast args to 'pow()'.
//
// Revision 4.3  1998/02/13 23:32:53  houghton
// Cleanup.
//
// Revision 4.2  1998/01/22 18:33:42  houghton
// Changed - added stopAtNonDigit arg to all StringTo functions.
// Cleanup - moved descriptions to end of file.
//
// Revision 4.1  1997/09/17 15:13:02  houghton
// Changed to Version 4
//
// Revision 3.4  1997/09/17 11:08:53  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1996/11/25 10:14:01  houghton
// Added StringTo( struct & tm dest, const char * src, const char * fmt )
// Added StringToTm( const char * src, const char * fmt
//
// Revision 3.2  1996/11/19 12:26:05  houghton
// Changed include lines to use " " instead of < > to accomidate rpm.
// Removed support for short file names to accomidate rpm.
//
// Revision 3.1  1996/11/14 01:24:19  houghton
// Changed to Release 3
//
// Revision 2.4  1996/11/04 14:32:20  houghton
// Restructure header comments layout.
// Changed default len to be NPOS instead of 0.
// Changed to call CharIsBaseDigit instead of IsBaseDigit.
//
// Revision 2.3  1996/07/09 11:34:13  houghton
// Bug-Fix: Change to StringToBool to StringTo.
//
// Revision 2.2  1996/05/25 12:36:04  houghton
// Bug-Fix: convert '   ' to 0.
//
// Revision 2.1  1995/11/10 12:41:13  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:50  houghton
// Ports and Version ID changes
//
//

  

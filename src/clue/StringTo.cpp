// 1995-05-06 (cc) <paul4hough@gmail.com>

#include "StringUtils.hpp"
#include <cstring>
#include <cctype>
#include <cmath>

namespace clue {
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

const char *
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



} // namespace clue

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

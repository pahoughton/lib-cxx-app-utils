#ifndef _StringUtils_hpp_
// 1995-05-02 (cc) paul4hough@gmail.com
#define _StringUtils_hpp_
#include <cstring>
#include <ctime>
#include <cctype>

#define STLUTILS_DIGITS_SPACE	"0123456789 "
#if !defined( NPOS )
#define NPOS (static_cast<size_t>(-1))
#endif

namespace clue {

inline
char *
SafeStrcpy( char * dest, const char * src, size_t size )
{
  if( src )
    strncpy( dest, src, size );
  else
    dest[0] = 0;

  dest[size-1] = 0;
  return( dest );
}

extern const int _CharToNumber[];

inline
int
CharToInt( char c )
{
  return( _CharToNumber[ (short)c ] );
}


inline
bool
CharIsBaseDigit( char c, unsigned short base )
{
  return( CharToInt(c) >= 0 && CharToInt(c) < base );
}

char *
StripWhite( char *  	    buffer,
	    const char *    white = " \n\t\r\v\f",
	    size_t          bufSize = NPOS );

char *
StripTrailing( char *		buffer,
	       const char *	white = " \n\t\r\v\f",
	       size_t		bufferSize = NPOS );


const char *
StringSearch( const char *  haystack,
	      size_t        hayLen,
	      const char *  needle,
	      size_t        needleLen );

const char *
StringReverseSearch( const char *  haystack,
		     size_t        hayLen,
		     const char *  needle,
		     size_t        needleLen );

const char *
StringCaseSearch( const char *  haystack,
		  size_t        hayLen,
		  const char *  needle,
		  size_t        needleLen );

const char *
StringCaseReverseSearch( const char *  haystack,
			 size_t        hayLen,
			 const char *  needle,
			 size_t        needleLen );

size_t
StringFirstNotOf( const char *	haystack,
		  size_t	hayLen,
		  const char *	needles,
		  size_t	needleLen );

int
StringCaseCompare( const char * one, const char * two );

int
StringCaseCompare( const char * one, const char * two, size_t len );

int
StringCaseCompare( const char * one, size_t lenOne,
		   const char * two, size_t lenTwo );


char *
StringLower( char * str, size_t len = NPOS );

char *
StringUpper( char * str, size_t len = NPOS );

char *
StringCapitalize( char * str, size_t len = NPOS );

// internal - set base, neg and return next digit
const char *
_StringToNumPrep(
  const char *      string,
  const char *      end,
  unsigned short &  base,
  bool &    	    neg );

template<typename TYPE>
inline bool
StringToSigned(
  TYPE &	    dest,
  const char * 	    src,
  unsigned short    baseToUse,
  size_t    	    len,
  bool		    stopAtNonDigit
  )
{
  TYPE  value = 0;

  const char * 	    end  = src + ( len != NPOS ? len : strlen( src ) );
  unsigned short    base = baseToUse;
  bool	    	    neg  = false;

  const char *      conv = _StringToNumPrep( src, end, base, neg );

  if( ! conv || conv >= end ) {
    dest = 0;
    return( true );
  }

  for( ; conv < end; conv++ ) {
    if( CharIsBaseDigit( *conv, base ) ) {
      value *= base;
      value += CharToInt( *conv );

    } else {
      if( stopAtNonDigit ) {
	break;
      } else {
	return( false );
      }
    }
  }

  dest = (neg) ? value * -1 : value;
  return( true );
}

template<typename TYPE>
inline bool
StringToUnsigned(
  TYPE &	    dest,
  const char * 	    src,
  unsigned short    baseToUse,
  size_t    	    len,
  bool		    stopAtNonDigit
  )
{
  TYPE  value = 0;

  const char * 	    end  = src + ( len != NPOS ? len : strlen( src ) );
  unsigned short    base = baseToUse;
  bool	    	    neg  = false;

  const char *      conv = _StringToNumPrep( src, end, base, neg );

  if( ! conv || conv >= end ) {
    dest = 0;
    return( true );
  }

  for( ; conv < end; conv++ ) {
    if( CharIsBaseDigit( *conv, base ) ) {
      value *= base;
      value += CharToInt( *conv );

    } else {
      if( stopAtNonDigit ) {
	break;
      } else {
	return( false );
      }
    }
  }

  dest = value;
  return( true );
}

#define CLUE_STRING_TO_STYPE( _type_ )		\
inline bool					\
StringTo(					\
  _type_ &	    dest,			\
  const char * 	    src,			\
  unsigned short    baseToUse = 0,		\
  size_t    	    len = NPOS,			\
  bool		    stopAtNonDigit = false	\
  )						\
{						\
  return( StringToSigned( dest,			\
			  src,			\
			  baseToUse,		\
			  len,			\
			  stopAtNonDigit) );	\
}

#define CLUE_STRING_TO_UTYPE( _type_ )		\
inline bool					\
StringTo(					\
  _type_ &	    dest,			\
  const char * 	    src,			\
  unsigned short    baseToUse = 0,		\
  size_t    	    len = NPOS,			\
  bool		    stopAtNonDigit = false	\
  )						\
{						\
  return( StringToUnsigned( dest,		\
			    src,		\
			    baseToUse,		\
			    len,		\
			    stopAtNonDigit) );	\
}

CLUE_STRING_TO_STYPE( int )
CLUE_STRING_TO_STYPE( short )
CLUE_STRING_TO_STYPE( long )
CLUE_STRING_TO_STYPE( long long )

CLUE_STRING_TO_UTYPE( unsigned int )
CLUE_STRING_TO_UTYPE( unsigned short )
CLUE_STRING_TO_UTYPE( unsigned long )
CLUE_STRING_TO_UTYPE( unsigned long long )

bool
StringTo( bool & 	    dest,
	  const char *      str,
	  size_t 	    len = NPOS );

bool
StringTo( double &     	    dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = NPOS,
	  bool		    stopAtNonDigit = false );

inline
bool
StringTo(
  float &  	    dest,
  const char * 	    src,
  unsigned short    base = 0,
  size_t    	    len = NPOS,
  bool		    stopAtNonDigit = false )
{
  double value;

  if( ! StringTo( value, src, base, len, stopAtNonDigit ) )
    return( false );

  dest = value;
  return( true );
}

inline
bool
StringTo(
  struct tm &	dest,
  const char *	src,
  const char *  fmt = "%m/%d/%y %H:%M:%S" )
{
  strptime( src, fmt, &dest );
  return( true );
}


#define CLUE_STRING_TO_RET_TYPE( _type_, _name_ )	\
inline _type_						\
StringTo##_name_(					\
  const char *	    src,				\
  unsigned short    base = 0,				\
  size_t	    len = NPOS,				\
  bool		    stopAtNonDigit = false		\
  )							\
{							\
  _type_  value = 0;					\
  StringTo( value, src, base, len, stopAtNonDigit );	\
  return( value );					\
}
CLUE_STRING_TO_RET_TYPE( int, Int )
CLUE_STRING_TO_RET_TYPE( short, Short )
CLUE_STRING_TO_RET_TYPE( long, Long )
CLUE_STRING_TO_RET_TYPE( long long, LongLong )
CLUE_STRING_TO_RET_TYPE( float, Float )
CLUE_STRING_TO_RET_TYPE( double, Double )
CLUE_STRING_TO_RET_TYPE( unsigned int, UInt )
CLUE_STRING_TO_RET_TYPE( unsigned short, UShort )
CLUE_STRING_TO_RET_TYPE( unsigned long, ULong )
CLUE_STRING_TO_RET_TYPE( unsigned long long, ULongLong )


inline
bool
StringToBool(
  const char *  src,
  size_t    	len = NPOS
  )
{
  bool dest = false;
  StringTo( dest, src, len );
  return( dest );
}

inline
struct tm
StringToTm( const char * src, const char * fmt )
{
  struct tm dest;
  strptime( src, fmt, &dest );
  return( dest );
}


bool
MfNumTo( short & dest, const char * src, size_t len = NPOS );

bool
MfNumTo( int & dest, const char * src, size_t len = NPOS );

bool
MfNumTo( long & dest, const char * src, size_t len = NPOS );

short
MfNumToShort( const char * src, size_t len = NPOS );

int
MfNumToInt( const char * src, size_t len = NPOS );

long
MfNumToLong( const char * src, size_t len = NPOS );

bool
MfNumTo( char *		dest,
	 size_t		destSize,
	 size_t		decimalPlaces,
	 const char *	src,
	 size_t		srcSize );

const char *
StringFrom( int num, short base = 10, bool prefix = false );

const char *
StringFrom( short num, short base = 10, bool prefix = false );

const char *
StringFrom( long num, short base = 10, bool prefix = false );

const char *
StringFrom( unsigned int num, short base = 10, bool prefix = false );

const char *
StringFrom( unsigned short num, short base = 10, bool prefix = false );

const char *
StringFrom( unsigned long num, short base = 10, bool prefix = false );

const char *
StringFrom( double num, short precision = 2 );

const char *
StringFrom( const struct tm & src, const char * fmt = "%m/%d/%y %H:%M:%S" );

const char *
StringFrom( long long num, short base = 10, bool prefix = false );

const char *
StringFrom( unsigned long long num, short base = 10, bool prefix = false );

char *
StringFrom( char *	dest,
	    size_t	destSize,
	    short	num,
	    char	fill = '0',
	    short	base = 10,
	    bool	prefix = false );

char *
StringFrom( char *	dest,
	    size_t	destSize,
	    int		num,
	    char	fill = '0',
	    short	base = 10,
	    bool	prefix = false );

char *
StringFrom( char *	dest,
	    size_t	destSize,
	    long	num,
	    char	fill = '0',
	    short	base = 10,
	    bool	prefix = false );

char *
StringFrom( char *	    dest,
	    size_t	    destSize,
	    unsigned short  num,
	    char	    fill = '0',
	    short	    base = 10,
	    bool	    prefix = false );

char *
StringFrom( char *	    dest,
	    size_t	    destSize,
	    unsigned int    num,
	    char	    fill = '0',
	    short	    base = 10,
	    bool	    prefix = false );

char *
StringFrom( char *	    dest,
	    size_t	    destSize,
	    unsigned long   num,
	    char	    fill = '0',
	    short	    base = 10,
	    bool	    prefix = false );

char *
StringFrom( char *	    dest,
	    size_t	    destSize,
	    long long	    num,
	    char	    fill = '0',
	    short	    base = 10,
	    bool	    prefix = false );
char *
StringFrom( char *		dest,
	    size_t		destSize,
	    unsigned long long  num,
	    char		fill = '0',
	    short		base = 10,
	    bool		prefix = false );

char *
basename( char * fn );

const char *
basename( const char * fn );

}; // namespace clue

/**
  char *
  StripWhite( char *  	    buffer,
  	    const char *    white = " \n\t\r\v\f",
  	    size_t          bufSize = NPOS );
      Remove leading and trailing 'white' characters from
      'buffer' and return buffer. If bufSize == 0, the string
      is NOT modified.

  const char *
  StringSearch( const char *  haystack,
  	      size_t        hayLen,
  	      const char *  needle,
  	      size_t        needleLen );
      Search the string 'haystack' for the string 'needle'. If
      'needle' is found in 'haystack' a pointer to the first char
      of 'needle' in 'haystack' is returned. If 'needle' is not found,
      a 0 is returned. Use NPOS for the len parameters if the
      corresponding string is null (0) terminated.

  const char *
  StringReverseSearch( const char *  haystack,
  		     size_t        hayLen,
  		     const char *  needle,
  		     size_t        needleLen );
      Search the string 'haystack' for the string 'needle' starting
      from the end of 'haystack'. If 'needle' is found in 'haystack'
      a pointer to the first char of 'needle' in 'haystack' is
      returned. If 'needle' is not found, a 0 is returned.
      Use NPOS for the len parameters if the corresponding string
      is null (0) terminated.


  const char *
  StringCaseSearch( const char *  haystack,
  		  size_t        hayLen,
  		  const char *  needle,
  		  size_t        needleLen );
      Search the string 'haystack' for the string 'needle' ignoring
      case. If 'needle' is found in 'haystack' a pointer to the first
      char of 'needle' in 'haystack' is returned. If 'needle' is not
      found, a 0 is returned. Use NPOS for the len parameters if the
      corresponding string is null (0) terminated.


  const char *
  StringCaseReverseSearch( const char *  haystack,
  			 size_t        hayLen,
  			 const char *  needle,
  			 size_t        needleLen );
      Search the string 'haystack' for the string 'needle' starting
      from the end of 'haystack' and ignoring case. If 'needle' is
      found in 'haystack' a pointer to the first char of 'needle'
      in 'haystack' is returned. If 'needle' is not found, a 0 is
      returned. Use NPOS for the len parameters if the corresponding
      string is null (0) terminated.

  size_t
  StringFirstNotOf( const char *	haystack,
  		  size_t	hayLen,
  		  const char *	needles,
  		  size_t	needleLen );
      Search the string 'haystack' for an character not in the string
      needle. Return the position of the first character in
      'haystack' that is not in needle or NPOS if all the characters
      in 'haystack' consist of characters in 'needle. Use NPOS for
      the len parameters if the corresponding string is null (0)
      terminated.

  int
  StringCaseCompare( const char * one, const char * two );
      Compare two strings ignoring case. return 0 if one == two,
      return < 0 if one < two, and return > 0 if one > two.

  int
  StringCaseCompare( const char * one, const char * two, size_t len );
      Compare the first 'len' chars of two strings ignoring case.
      return 0 if one == two, return < 0 if one < two, and
return > 0 if one > two.

  int
  StringCaseCompare( const char * one, size_t lenOne,
  		   const char * two, size_t lenTwo );
      Compare the two strings ignoring case. The first
      min( lenOne, lenTwo) char are check first if they are
      not the same, the difference is return. If they are the
      same, the differance of lenOne and lenTwo is returnd.

  char *
  StringLower( char * str, size_t len = NPOS );
      Convert all upper case characters (A-Z) to lower case (a-z).
      Returns str.


  char *
  StringUpper( char * str, size_t len = NPOS );
      Convert all lower case characters (a-z) to upper case (A-Z).
      Returns str.

  char *
  StringCapitalize( char * str, size_t len = NPOS );
      Convert the first lower case alpha (a-z) char of
      every word to upper case and convert every other
      character in every word to lower case. Returns str.

  bool
  StringTo( bool & 	    	dest,
  	  const char *  	str,
  	  size_t 	    	len = NPOS );
      Set dest by converting str to a bool value. If str is
      'yes', 'true', 'on', 't', 'y' or a non zero number, dest
      will be set to true (case is ignored). Else if str is 'no',
      'false', 'off', 'f', 'n', ' ' or '0', dest will be
      set to false. Returns true if dest was set or false if
      str could not be converted.

  bool
  StringTo( int &     	    dest,
  	  const char * 	    str,
  	  unsigned short    base = 0,
  	  size_t    	    len = NPOS );
      Set dest by converting str to a numeric value. base is
      the base to use for the conversion (i.e. 8 = for oct,
      10 for dec, 16 for hex), it can be any value between
      2 and 36 or 0. If base is zero the beginning of str is
      used to determine base. If it is 0x or 0X the base is 16.
      If it is 0 the base is 8. Otherwise the base is 10.
      Returns true if dest was set or false if str could
      not be converted.

  bool
  StringTo( short &     	    dest,
  	  const char * 	    str,
  	  unsigned short    base = 0,
  	  size_t    	    len = NPOS );
      Set dest by converting str to a numeric value. base is
      the base to use for the conversion (i.e. 8 = for oct,
      10 for dec, 16 for hex), it can be any value between
      2 and 36 or 0. If base is zero the beginning of str is
      used to determine base. If it is 0x or 0X the base is 16.
      If it is 0 the base is 8. Otherwise the base is 10.
      Returns true if dest was set or false if str could
      not be converted.

  bool
  StringTo( long &     	    dest,
  	  const char * 	    str,
  	  unsigned short    base = 0,
  	  size_t    	    len = NPOS );
      Set dest by converting str to a numeric value. base is
      the base to use for the conversion (i.e. 8 = for oct,
      10 for dec, 16 for hex), it can be any value between
      2 and 36 or 0. If base is zero the beginning of str is
      used to determine base. If it is 0x or 0X the base is 16.
      If it is 0 the base is 8. Otherwise the base is 10.
      Returns true if dest was set or false if str could
      not be converted.

  bool
  StringTo( float &     	    dest,
  	  const char * 	    str,
  	  unsigned short    base = 0,
  	  size_t    	    len = NPOS );
      Set dest by converting str to a numeric value. base is
      the base to use for the conversion (i.e. 8 = for oct,
      10 for dec, 16 for hex), it can be any value between
      2 and 36 or 0. If base is zero the beginning of str is
      used to determine base. If it is 0x or 0X the base is 16.
      If it is 0 the base is 8. Otherwise the base is 10.
      Returns true if dest was set or false if str could
      not be converted.

  bool
  StringTo( double &     	    dest,
  	  const char * 	    str,
  	  unsigned short    base = 0,
  	  size_t    	    len = NPOS );
      Set dest by converting str to a numeric value. base is
      the base to use for the conversion (i.e. 8 = for oct,
      10 for dec, 16 for hex), it can be any value between
      2 and 36 or 0. If base is zero the beginning of str is
      used to determine base. If it is 0x or 0X the base is 16.
      If it is 0 the base is 8. Otherwise the base is 10.
      Returns true if dest was set or false if str could
      not be converted.

  bool
  StringTo( unsigned int &    dest,
  	  const char * 	    str,
  	  unsigned short    base = 0,
  	  size_t    	    len = NPOS );
      Set dest by converting str to a numeric value. base is
      the base to use for the conversion (i.e. 8 = for oct,
      10 for dec, 16 for hex), it can be any value between
      2 and 36 or 0. If base is zero the beginning of str is
      used to determine base. If it is 0x or 0X the base is 16.
      If it is 0 the base is 8. Otherwise the base is 10.
      Returns true if dest was set or false if str could
      not be converted.

  bool
  StringTo( unsigned short &  dest,
  	  const char * 	    str,
  	  unsigned short    base = 0,
  	  size_t    	    len = NPOS );
      Set dest by converting str to a numeric value. base is
      the base to use for the conversion (i.e. 8 = for oct,
      10 for dec, 16 for hex), it can be any value between
      2 and 36 or 0. If base is zero the beginning of str is
      used to determine base. If it is 0x or 0X the base is 16.
      If it is 0 the base is 8. Otherwise the base is 10.
      Returns true if dest was set or false if str could
      not be converted.

  bool
  StringTo( unsigned long &   dest,
  	  const char * 	    str,
  	  unsigned short    base = 0,
  	  size_t    	    len = NPOS );
      Set dest by converting str to a numeric value. base is
      the base to use for the conversion (i.e. 8 = for oct,
      10 for dec, 16 for hex), it can be any value between
      2 and 36 or 0. If base is zero the beginning of str is
      used to determine base. If it is 0x or 0X the base is 16.
      If it is 0 the base is 8. Otherwise the base is 10.
      Returns true if dest was set or false if str could
      not be converted.

  bool
  StringToBool( const char * str, size_t len = NPOS );
      Uses StringTo to convert the str and returns
      the value. If StringTo returned false, 'false' is returned.

  int
  StringToInt( const char *   str,
  	     unsigned short base = 0,
  	     size_t	    len = NPOS );
      Uses StringTo to convert the str and returns the
      value. If StringTo returned false, 0 is returned.

  short
  StringToShort( const char *	str,
  	       unsigned short	base = 0,
  	       size_t		len = NPOS );
      Uses StringTo to convert the str and returns the
      value. If StringTo returned false, 0 is returned.

  long
  StringToLong( const char *	str,
  	      unsigned short	base = 0,
  	      size_t		len = NPOS );
      Uses StringTo to convert the str and returns the
      value. If StringTo returned false, 0 is returned.

  float
  StringToFloat( const char *	str,
  	       unsigned short	base = 0,
  	       size_t		len = NPOS );
      Uses StringTo to convert the str and returns the
      value. If StringTo returned false, 0 is returned.

  double
  StringToDouble( const char *	str,
  		unsigned short  base = 0,
  		size_t          len = NPOS );
      Uses StringTo to convert the str and returns the
      value. If StringTo returned false, 0 is returned.

  unsigned int
  StringToUInt( const char *	str,
  	      unsigned short	base = 0,
  	      size_t		len = NPOS );
      Uses StringTo to convert the str and returns the
      value. If StringTo returned false, 0 is returned.

  unsigned short
  StringToUShort( const char *	str,
  		unsigned short  base = 0,
  		size_t		len = NPOS );
      Uses StringTo to convert the str and returns the
      value. If StringTo returned false, 0 is returned.

  unsigned long
  StringToULong( const char *	str,
  	       unsigned short	base = 0,
  	       size_t		len = NPOS );
      Uses StringTo to convert the str and returns the
      value. If StringTo returned false, 0 is returned.

  const char *
  StringFrom( int	    num,
  	    short   base = 10,
  	    bool    prefix = false );
      This function converts num into a null terminated
      string. 'num' is the value to convert. 'base' is the
      base to use in the string. if 'prefix' is true a
      '0' will be prepended for 'base' 8 and a 0x will be
      prepended for base 16. The Return value is an interal
      static buffer used by all the StringFrom functions.

  const char *
  StringFrom( short   num,
  	    short   base = 10,
  	    bool    prefix = false );
      This function converts num into a null terminated
      string. 'num' is the value to convert. 'base' is the
      base to use in the string. if 'prefix' is true a
      '0' will be prepended for 'base' 8 and a 0x will be
      prepended for base 16. The Return value is an interal
      static buffer used by all the StringFrom functions.

  const char *
  StringFrom( long    num,
  	    short   base = 10,
  	    bool    prefix = false );
      This function converts num into a null terminated
      string. 'num' is the value to convert. 'base' is the
      base to use in the string. if 'prefix' is true a
      '0' will be prepended for 'base' 8 and a 0x will be
      prepended for base 16. The Return value is an interal
      static buffer used by all the StringFrom functions.

  const char *
  StringFrom( unsigned int    num,
  	    short	    base = 10,
  	    bool	    prefix = false );
      This function converts num into a null terminated
      string. 'num' is the value to convert. 'base' is the
      base to use in the string. if 'prefix' is true a
      '0' will be prepended for 'base' 8 and a 0x will be
      prepended for base 16. The Return value is an interal
      static buffer used by all the StringFrom functions.

  const char *
  StringFrom( unsigned short    num,
  	    short	    base = 10,
  	    bool	    prefix = false );
      This function converts num into a null terminated
      string. 'num' is the value to convert. 'base' is the
      base to use in the string. if 'prefix' is true a
      '0' will be prepended for 'base' 8 and a 0x will be
      prepended for base 16. The Return value is an interal
      static buffer used by all the StringFrom functions.

  const char *
  StringFrom( unsigned long    num,
  	    short	    base = 10,
  	    bool	    prefix = false );
      This function converts num into a null terminated
      string. 'num' is the value to convert. 'base' is the
      base to use in the string. if 'prefix' is true a
      '0' will be prepended for 'base' 8 and a 0x will be
      prepended for base 16. The Return value is an interal
      static buffer used by all the StringFrom functions.

  const char *
  StringFrom( double num, short precision = 2 )
      This function converts num into a null terminated
      string. 'num' is the value to convert. 'precision'
      is the number of decimal places to use. The string
      will be a fixed floating point representation.
      The Return value is an internal static buffer
      used by all the StringFrom functions.

  const char *
  basename( const char * fn );
      Returns a pointer to the filename from part of 'fn'
      without the directory part.

  char *
  basename( char * fn );
      Returns a pointer to the filename from part of 'fn'
      without the directory part.

  inline
  char *
  SafeStrcpy( char * dest, const char * src, size_t size )
      Copy 'size' chars of 'src' into dest and
      set dest[size-1] to 0. Returns dest.

  inline
  int
  CharToInt( char c )
      Return 'c' as a numeric value. If 'c' is not 0-9,
      Return -1.

  inline
  bool
  CharIsBaseDigit( char c, unsigned short base )
      Return true if 'c' is a valid digit of 'base'. Otherwise
      return false.

**/

#endif // ! def _StringUtils_hpp_

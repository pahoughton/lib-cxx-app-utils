//
// File:        StringFrom.C
// Project:	StlUtils (%PP%)
// Item:   	%PI% (%PF%)
// Desc:        
//
//  The StringFrom functions were developed out of my
//  frustration in trying to find a good way to convert
//  number into character strings and append them to
//  a 'class string'.
//
//  The only standard text conversion for numbers are the
//  '<<' operators for ostream. The number of code lines and
//  perfomance expence in using a strstream (or the new sstream)
//  just to get a number converted to text is WAY to high.
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     11/15/96 14:56
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    %PO%
//  Last Mod:	    %PRT%
//  Version:	    %PIV%
//  Status: 	    %PS%
//
// %PID%

#if defined( STLUTILS_THREADS )
#error Mutex needed
#endif

#include "StringUtils.hh"
// #include "Mutex.hh"
#include <strstream.h>
#include <cstring>
#include <cctype>

STLUTILS_FUNCT_VERSION(
  StringAppend,
  "%PID%" );

static char	NumBuf[ 129 ];
//static Mutex	NumBufMutex;


template< class NumT >
inline
char * 
_StlUtilsStringUnsignedFrom(
  char *    end,
  size_t    size,
  NumT	    num,
  bool	    neg,
  char	    fill,
  short	    base,
  bool	    prefix,
  bool	    nullTerm )
{
  // We work from back to front!
  // and return front. So start by null terminating the string.

  //  NumBufMutex.lock();

  if( nullTerm )
    {
      *end = 0;
      -- end;
      -- size;
    }

  if( num )
    {
      if( base == 10 )
	{
	  for( ; num != 0 && size ; -- end, -- size, num /= 10 )
	    *end = (num % 10) + '0';
	}
      else
	{
	  static const char * digits = "0123456789abcdefghijklmnopqrstuvwxyz";
	  
	  for( ; num != 0 && size; --end, --size, num /= base )
	    *end = digits[ (num % base) ];
	}
    }
  else
    {
      *end = '0';
      -- end;
      -- size;
    }
  
  if( fill )
    {
      size_t prefixCount = 0;
      
      if( size )
	{
	  if( prefix )
	    {
	      if( base == 8 )
		{
		  if( fill != '0' )
		    {
		      *end = '0';
		      -- end;
		      -- size;
		      if( neg )
			{
			  *end = '-';
			  -- end;
			  -- size;
			}
		    }
		  else
		    {
		      if( neg )
			{
			  *( end - size + 1) = '-';
			  -- size;
			  ++ prefixCount;
			}
		      *(end - size + 1) = '0';
		      -- size;
		      ++ prefixCount;
		    }
		  memset( end - size + 1, fill, size );
		}
	      else
		{
		  if( base == 16 )
		    {
		      if( fill != '0' )
			{
			  *end = '0';
			  -- end;
			  -- size;
			  *end = 'x';
			  -- end;
			  -- size;
			  if( neg )
			    {
			      *end = '-';
			      -- end;
			      -- size;
			    }
			}
		      else
			{
			  if( neg )
			    {
			      *( end - size + 1) = '-';
			      -- size;
			      ++ prefixCount;
			    }
			  *(end - size + 1) = '0';
			  -- size;
			  ++ prefixCount;
			  *(end - size + 1) = 'x';
			  -- size;
			  ++ prefixCount;
			}
		      memset( end - size + 1, fill, size );
		    }
		  else
		    {
		      return( 0 );
		    }
		}
	    }
	  else
	    {
	      // no prefix
	      if( fill != '0' )
		{
		  if( neg )
		    {
		      *end = '-';
		      -- end;
		      -- size;
		    }
		}
	      else
		{
		  if( neg )
		    {
		      *(end - size + 1) = '-';
		      -- size;
		      ++ prefixCount;
		    }
		}
	      memset( end - size + 1, fill, size );
	    }
	}
      else
	{
	  // no room for '-' 
	  if( neg )
	    return( NULL );
	}
      
      end -= size + prefixCount;
      ++ end;
    }
  else
    {
      // ! fill
      
      if( prefix )
	{
	  if( base == 8 )
	    {
	      *end = '0';
	      --end;
	    }
	  else
	    {
	      if( base == 16 )
		{
		  *end = 'x';
		  --end;
		  *end = '0';
		  --end;
		}
	      else
		{
		  return( NULL );
		}
	    }
	}
      
      if( neg )
	*end = '-';
      else
	++end; // one to far;
    }
  
  // NumBufMutex.unlock();
  
  return( end ); // which is now the front.
}

template< class NumT >
inline
char * 
_StlUtilsStringSignedFrom(
  char *    end,
  size_t    size,
  NumT	    num,
  char	    fill,
  short	    base,
  bool	    prefix,
  bool	    nullTerm
  )
{
  return( _StlUtilsStringUnsignedFrom( end,
				       size,
				       ( num < 0 ? -num : num ),
				       ( num < 0 ? true : false ),
				       fill,
				       base,
				       prefix,
				       nullTerm ) );
}


#define SIGNED_STR_FRM_FIXED_TYPE( NumType )				      \
char *									      \
StringFrom(								      \
  char *    dest,							      \
  size_t    destSize,							      \
  NumType   num,							      \
  char	    fill,							      \
  short	    base,							      \
  bool	    prefix							      \
  )									      \
{									      \
  return( _StlUtilsStringSignedFrom( dest + destSize - 1,		      \
				     destSize,				      \
				     num,				      \
				     fill,				      \
				     base,				      \
				     prefix,				      \
				     false ) );				      \
}


#define UNSIGNED_STR_FRM_FIXED_TYPE( NumType )				      \
char *									      \
StringFrom(								      \
  char *    dest,							      \
  size_t    destSize,							      \
  NumType   num,							      \
  char	    fill,							      \
  short	    base,							      \
  bool	    prefix							      \
  )									      \
{									      \
  return( _StlUtilsStringUnsignedFrom( dest + destSize - 1,		      \
				       destSize,			      \
				       num,				      \
				       false,				      \
				       fill,				      \
				       base,				      \
				       prefix,				      \
				       false ) );			      \
}

#define SIGNED_STR_FRM_TYPE( NumType )					      \
const char *								      \
StringFrom( NumType num, short base, bool prefix )			      \
{									      \
  return( _StlUtilsStringSignedFrom( NumBuf + sizeof( NumBuf ) - 1,	      \
				     sizeof( NumBuf ),			      \
				     num,				      \
				     (char)0,				      \
				     base,				      \
				     prefix,				      \
				     true ) );				      \
}

#define UNSIGNED_STR_FRM_TYPE( NumType )				      \
const char *								      \
StringFrom( NumType num, short base, bool prefix )			      \
{									      \
  return( _StlUtilsStringUnsignedFrom( NumBuf + sizeof( NumBuf ) - 1,	      \
				       sizeof( NumBuf ),		      \
				       num,				      \
				       false,				      \
				       (char)0,				      \
				       base,				      \
				       prefix,				      \
				       true ) );			      \
}

				     
SIGNED_STR_FRM_FIXED_TYPE( short );
SIGNED_STR_FRM_FIXED_TYPE( int );
SIGNED_STR_FRM_FIXED_TYPE( long );

UNSIGNED_STR_FRM_FIXED_TYPE( unsigned short );
UNSIGNED_STR_FRM_FIXED_TYPE( unsigned int );
UNSIGNED_STR_FRM_FIXED_TYPE( unsigned long );

SIGNED_STR_FRM_TYPE( short );
SIGNED_STR_FRM_TYPE( int );
SIGNED_STR_FRM_TYPE( long );

UNSIGNED_STR_FRM_TYPE( unsigned short );
UNSIGNED_STR_FRM_TYPE( unsigned int );
UNSIGNED_STR_FRM_TYPE( unsigned long );

#if defined( STLUTILS_HAVE_LONG_LONG )
SIGNED_STR_FRM_FIXED_TYPE( long long );
UNSIGNED_STR_FRM_FIXED_TYPE( unsigned long long );
SIGNED_STR_FRM_TYPE( long long );
UNSIGNED_STR_FRM_TYPE( unsigned long long );
#endif


const char *
StringFrom( double num, short prec )
{
  strstream tmp;
  tmp.setf( ios::fixed, ios::floatfield );
  tmp.precision( prec );

  tmp << num << ends;
  //  NumBufMutex.lock();
  strcpy( NumBuf, tmp.str() );
  //  NumBufMutex.unlock();
  tmp.rdbuf()->freeze(0);
  return( NumBuf );
}

const char *
StringFrom( const struct tm & src, const char * fmt )
{
  // NumBufMutex.lock();
  NumBuf[0] = 0;
  strftime( NumBuf, sizeof( NumBuf ), fmt, &src );
  // NumBufMutex.unlock();
  return( NumBuf );
}

//
// 
// %PL%
// 
// $Log$
// Revision 5.2  2001/07/26 19:28:58  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:18  houghton
// Changed Version Num to 5
//
// Revision 4.5  1999/05/09 13:06:34  houghton
// Added long long support.
//
// Revision 4.4  1999/05/09 11:32:27  houghton
// Cleanup.
//
// Revision 4.3  1998/01/05 13:07:51  houghton
// Port(Aix): had to cast fill 0 to a char.
//
// Revision 4.2  1997/12/23 12:06:30  houghton
// Added StringFrom( char * dest ).
//
// Revision 4.1  1997/09/17 15:13:01  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:08:52  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1997/07/28 16:46:48  houghton
// Bug-Fix: if num was 0, an empty string would be returned.
//
// Revision 3.1  1997/03/21 15:43:36  houghton
// Changed base version to 3
//
// Revision 1.3  1996/11/25 10:12:48  houghton
// Added StringFrom( const struct & tm, const char * fmt );
//
// Revision 1.2  1996/11/24 19:06:58  houghton
// Commented out mutex support for rpm (temporary).
//
// Revision 1.1  1996/11/19 12:26:58  houghton
// Initial Version.
//
//

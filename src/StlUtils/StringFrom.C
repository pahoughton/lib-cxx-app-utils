//
// File:        StringFrom.C
// Project:	Clue
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

#if defined( CLUE_THREADS )
#error Mutex needed
#endif

#include "StringUtils.hh"
// #include "Mutex.hh"
#include <strstream.h>
#include <cstring>
#include <cctype>

CLUE_FUNCT_VERSION(
  StringAppend,
  "$Id$" );

static char	NumBuf[ 129 ];
//static Mutex	NumBufMutex;


template< class NumT >
inline
char * 
_ClueStringUnsignedFrom(
  char *    end,
  NumT	    num,
  bool	    neg,
  short	    base,
  bool	    prefix )
{
  // We work from back to front!
  // and return front. So start by null terminating the string.

  //  NumBufMutex.lock();
  
  *end = 0;
  
  if( base == 10 )
    {
      for(--end; num != 0; --end, num /= 10 )
	*end = (num % 10) + '0';
    }
  else
    {
      static const char * digits = "0123456789abcdefghijklmnopqrstuvwxyz";
      for( --end; num != 0 ; --end, num /= base )
	*end = digits[ (num % base) ];
    }
  
  if( prefix )
    {
      if( base == 8 )
	{
	  *end = '0';
	  --end;
	}
      if( base == 16 )
	{
	  *end = 'x';
	  --end;
	  *end = '0';
	  --end;
	}
    }

  if( neg )
    *end = '-';
  else
    ++end; // one to far;

  // NumBufMutex.unlock();
  
  return( end ); // which is now the front.
}

template< class NumT >
inline
char * 
_ClueStringSignedFrom( char * end, NumT num, short base, bool prefix )
{
  if( num < 0 )
    {
      return( _ClueStringUnsignedFrom( end, -num, true, base, prefix  ) );
    }
  else
    {
      return( _ClueStringUnsignedFrom( end, num, false, base, prefix  ) );
    }
}

const char *
StringFrom( int num, short base, bool prefix )
{
  return( _ClueStringSignedFrom( NumBuf + sizeof( NumBuf ) - 1,
				 num, base, prefix ) );
}

const char *
StringFrom( short num, short base, bool prefix )
{
  return( _ClueStringSignedFrom( NumBuf + sizeof( NumBuf ) - 1,
				 num, base, prefix ) );
}

const char *
StringFrom( long num, short base, bool prefix )
{
  return( _ClueStringSignedFrom( NumBuf + sizeof( NumBuf ) - 1,
				 num, base, prefix ) );
}

const char *
StringFrom( unsigned int num, short base, bool prefix )
{
  return( _ClueStringUnsignedFrom( NumBuf + sizeof( NumBuf ) - 1,
				   num, false, base, prefix ) );
}

const char *
StringFrom( unsigned short num, short base, bool prefix )
{
  return( _ClueStringUnsignedFrom( NumBuf + sizeof( NumBuf ) - 1,
				   num, false, base, prefix ) );
}

const char *
StringFrom( unsigned long num, short base, bool prefix )
{
  return( _ClueStringUnsignedFrom( NumBuf + sizeof( NumBuf ) - 1,
				   num, false, base, prefix ) );
}

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
// $Log$
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

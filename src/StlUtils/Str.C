//
// File:        Str.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/30/95 15:08 
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 13:23:32  houghton
// Initaial implementation
//
//

#include "ClueConfig.hh"
#include "ClueExceptions.hh"

#include "Str.hh"
#include "Clue.hh"
#include "RegexScan.hh"
#include "Compare.hh"
#include "File.hh"

#include <algorithm>
#include <new>

#include <cstring>

const char Str::version[] =
LIB_CLUE_VERSION
"$Id$";

const size_t Str::npos = NPOS;

inline
size_t
Str::length( const char * from )
{
  return( length() - (from - strbase()) );
}

inline
size_t
Str::pos( const char * at )
{
  return( at - strbase() );
}
  

#ifdef   CLUE_DEBUG
#define  inline
#include <Str.ii>
#endif


// append  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Str &
Str::append( const char * src, size_t srcLen )
{
  // there is a real danger of overlap so check for it

  if( ! src )
    return( *this );
      
  size_t  appLen = ( srcLen == npos ) ? strlen( src ) : srcLen;

  if( ! appLen )
    return( *this );
      
  if( MemOverlap( src, appLen, strbase(), size() ) )
    {
      char * tmp = new char[ appLen + 1 ];
      BAD_ALLOC( tmp == 0, *this );
      memcpy( tmp, src, appLen );
      rdbuf()->sputn( tmp, appLen );
      delete tmp;
    }
  else
    {
      rdbuf()->sputn( src, appLen );
    }

  return( *this );
}

// replace * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Str &
Str::replace(
  size_t    	start,
  size_t    	len,
  const char * 	src,
  size_t    	srcLen
  )
{
  OUT_OF_RANGE( start > size(), *this );

  size_t    replaceLen = min( len, size() - start );
  
  size_t    keepSize = size() - ( start + replaceLen );
  char *    keepString = 0;

  if( keepSize )
    {
      keepString = new char[ keepSize + 1];
      BAD_ALLOC( keepString == 0, *this );
      memcpy( keepString, strbase() + ( start + replaceLen ), keepSize );
    }

  seekp( start, ios::beg );

  if( src )
    append( src, srcLen );

  if( keepString )
    {
      append( keepString, keepSize );
      delete keepString;
    }

  return( *this );
}

  
Str &
Str::replace(
  size_t    start,
  size_t    len,
  size_t    count,
  char 	    src
  )
{
  OUT_OF_RANGE( start > size(), *this );

  size_t    replaceLen = min( len, size() - start );
  
  size_t    keepSize = size() - ( start + replaceLen );
  char *    keepString = 0;

  if( keepSize )
    {
      keepString = new char[ keepSize + 1];
      BAD_ALLOC( keepString == 0, *this );
      memcpy( keepString, strbase() + ( start + replaceLen ), keepSize );
    }

  seekp( start, ios::beg );

  if( count )
    append( count, src );

  if( keepString )
    {
      append( keepString, keepSize );
      delete keepString;
    }

  return( *this );
}

Str &
Str::replace(
  iterator  	first,
  iterator  	last,
  InputIterator	srcFirst,
  InputIterator	srcLast
  )
{
  size_t    start = (size_t)(min( 0, first - begin()));
  size_t    replaceLen = last - first;
  
  size_t    keepSize = size() - ( start + replaceLen );
  char *    keepString = 0;

  if( keepSize )
    {
      keepString = new char[ keepSize + 1];
      BAD_ALLOC( keepString == 0, *this );
      memcpy( keepString, strbase() + ( start + replaceLen ), keepSize );
    }

  seekp( start, ios::beg );

  append( srcFirst, srcLast  );

  if( keepString )
    {
      append( keepString, keepSize );
      delete keepString;
    }

  return( *this );
}
  


// compare * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


int
Str::compare( const Str & two, size_t start, size_t len ) const
{
  OUT_OF_RANGE( start > size(), false );
  
  size_t oneLen = min( size() - start, len );
  size_t twoLen = min( two.size(), len );

  int diff = strncmp( strbase() + start, two.strbase(), min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
Str::compare( const SubStr & two, size_t start, size_t len ) const
{
  OUT_OF_RANGE( start > size(), false );
  
  size_t oneLen = min( size() - start, len );
  size_t twoLen = min( two.size(), len );

  int diff = strncmp( strbase() + start, two.strbase(), min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}  

int
Str::compare( const char * two, size_t start, size_t len ) const
{
  OUT_OF_RANGE( start > size(), false );
  
  size_t oneLen = min( size() - start, len );
  size_t twoLen = min( strlen( two ), len );

  int diff = strncmp( strbase() + start, two, min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
compare( const SubStr & one, const Str & two, size_t len )
{
  return( one.compare( two, 0, len ) );
}

int
compare( const char * one, const Str & two, size_t len )
{
  size_t oneLen = min( strlen( one ), len );
  size_t twoLen = min( two.size(), len );

  int diff = strncmp( one, two.strbase(), min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}


	 
int
Str::fcompare( const Str & two, size_t start, size_t len ) const
{
  OUT_OF_RANGE( start > size(), false );
  
  size_t oneLen = min( size() - start, len );
  size_t twoLen = min( two.size(), len );

  int diff = StringCaseCompare( strbase() + start, two.strbase(),
				min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
Str::fcompare( const SubStr & two, size_t start, size_t len ) const
{
  OUT_OF_RANGE( start > size(), false );
  
  size_t oneLen = min( size() - start, len );
  size_t twoLen = min( two.size(), len );

  int diff = StringCaseCompare( strbase() + start, two.strbase(),
				min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}  

int
Str::fcompare( const char * two, size_t start, size_t len ) const
{
  size_t oneLen = min( size() - start, len );
  size_t twoLen = min( strlen( two ), len );

  int diff = StringCaseCompare( strbase() + start, two,
				min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
fcompare( const SubStr & one, const Str & two, size_t len )
{
  return( one.fcompare( two, 0, len ) );
}

int
fcompare( const char * one, const Str & two, size_t len )
{
  size_t oneLen = min( strlen( one ), len );
  size_t twoLen = min( two.size(), len );

  int diff = StringCaseCompare( one, two.strbase(),
				min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}  

// modifications * * * * * * * * * * * * * * * * * * * * * * * * * * *


size_t
Str::strip( const char * stripChars )
{
  const char * bufStart = cstr();
  char * destStart = rdbuf()->pbase();
  char * srcStart =  destStart + find_first_not_of( stripChars );
  char * srcEnd = strpbrk( srcStart, stripChars );

  if( destStart != srcEnd )
    {
      if( destStart != srcStart )
	memmove( destStart, srcStart, (srcEnd - srcStart) );
      destStart += (srcEnd - srcStart);
      srcEnd += strspn( srcEnd, stripChars );
      srcStart = srcEnd;
    }
  
  for( srcEnd = strpbrk( srcStart, stripChars );
      srcEnd;
      srcEnd = strpbrk( srcStart, stripChars ) )
    {
      memmove( destStart, srcStart, (srcEnd - srcStart) );
      destStart += (srcEnd - srcStart);
      srcEnd += strspn( srcEnd, stripChars );
      srcStart = srcEnd;
    }

  size_t count = length() - (srcStart - bufStart);
  
  memmove( destStart, srcStart, count );
  seekp( (destStart + count) - bufStart );
  return( length() );
}


// substitute

Str &
Str::substitute( char from, char to, size_t start, bool global )
{
  OUT_OF_RANGE( start > size(), *this );
  
  if( ! global )
    {
      char * chg = (char *)memchr( (void *)(rdbuf()->pbase() + start),
				   from, size() - start );

      if( chg )
	*chg = to;
    }
  else
    {
      for( char * chg = (char *)memchr( (void *)(rdbuf()->pbase() + start),
					from, size() - start );
	  chg;
	  chg = (char *)memchr( (void *)(chg+1), from, length( chg+1 ) ) )
	{
	  *chg = to;
	}
    }
  
  return( *this );
}


Str &
Str::substitute( const char * from, const char * to, size_t start, bool global )
{
  OUT_OF_RANGE( start > size(), *this );
  
  size_t fromLen = strlen( from );
  
  if( ! global )
    {
      size_t beg = find( from, start, fromLen );

      if( beg != npos )
	{
	  replace( beg, fromLen, to );
	}
    }
  else
    {
      size_t toLen = strlen( to );
      
      for( size_t beg = find( from, start, fromLen );
	  beg != npos;
	  beg = find( from, beg + fromLen, fromLen ) )
	{
	  replace( beg, fromLen, to, toLen );
	}
    }

  return( *this );
}

Str &
Str::substitute(
  const RegexScan & exp,
  const char *	    to,
  size_t    	    start,
  bool	    	    global
  )
{
  const char * base = strbase() + start;
  size_t       bLen = size() - start;
  
  Str repl;
  
  for( size_t beg = 0;
      exp.search( base, beg, bLen );
      beg = exp.matchStart() + repl.size(), bLen = size() - start )
    {
      repl.reset();
      for( const char * t = to; *t; t++ )
	{
	  if( *t == '\\' )
	    {
	      t++;
	      if( isdigit( *t ) )
		{
		  if( (size_t)(CharToInt( *t )) <= exp.matchCount() )
		    {
		      repl += at( start + exp.matchStart( CharToInt( *t ) ),
				  exp.matchLength( CharToInt( *t ) ) );
		    }
		}
	      if( *t == '&' )
		{
		  repl += at( start + exp.matchStart( 0 ),
			      exp.matchLength( 0 ) );
		}
	    }
	  else
	    {
	      repl += *t;
	    }
	  
	}
      
      replace( start + exp.matchStart(0),
	       exp.matchLength(0),
	       repl );

      if( ! global ) break;
    }
  return( *this );
}

size_t
Str::wrap( size_t w, long pad, long firstPad )
{

  stripLeading( " \t\n\r\f" );
  
  Str tmp;

  int fp = 0;
  
  if( firstPad > 0 || (firstPad == -1 && pad > 0) )
    {
      fp = ( firstPad > 0 ) ? firstPad : pad;

      for( int fCnt = 0; fCnt < fp; fCnt++ )
	tmp += ' ';
    }

  substitute( '\n', ' ' );
  substitute( '\t', ' ' );
  substitute( '\f', ' ' );
  
  if( ! scan( ' ' ) > 0 )
    return( 1 );

  size_t col = fp;
  size_t lines = 0;

  tmp += scanMatch(1);
  col += scanMatchLength(1);
  
  for( size_t m = 2;
      m < scanMatchCount();
      m++ )
    {
      if( (col + 1 + scanMatchLength(m) ) > w )
	{
	  tmp += '\n';
	  lines++;
	  col = 0;
	  if( pad > 0 )
	    {
	      for( int pCnt = 0; pCnt < pad; pCnt++ )
		{
		  tmp += ' ';
		  col++;
		}
	    }
	}
      else
	{
	  tmp += ' ';
	  col++;
	}

      tmp += scanMatch( m );
      col += scanMatchLength(m);      
    }

  tmp += '\n';
  
  assign( tmp );
  
  return( lines + 1 );
}
  

// scan  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


size_t
Str::scan( const RegexScan & exp, size_t start )
{
  OUT_OF_RANGE( start > size(), 0 );
  
  matches.erase( matches.begin(), matches.end() );

  if( exp.search( strbase(), start, length() ) )
    {
      for( size_t r = 0; r <= exp.matchCount(); r++ )
	{
	  int mBeg = 0;
	  int mLen = 0;

	  exp.matchInfo( mBeg, mLen, r );

	  matches.push_back( ScanMatch( mBeg, mLen ) );
	}
    }
  return( matches.size() );
}
      

size_t
Str::scan( const char * delim, size_t start, size_t dLen )
{
  matches.erase( matches.begin(), matches.end() );

  matches.push_back( ScanMatch( start, size() - start ) );
  
  size_t delimLen = (dLen == npos) ? strlen( delim ) : dLen;
  
  size_t beg = find_first_not_of( delim, start, delimLen );

  if( beg == npos )
    return( 0 );

  for( size_t end = find_first_of( delim, beg, delimLen );
      end != npos;
      end = find_first_of( delim, beg, delimLen ) )
    {
      matches.push_back( ScanMatch( beg , end - beg) );

      beg = find_first_not_of( delim, end, delimLen );
      if( beg == npos )
	break;
    }

  if( beg != start )
    {
      matches.push_back( ScanMatch( beg , size() - beg) );
    }

  return( matches.size() );
}
	  
size_t
Str::scan( char delim, size_t start )
{
  matches.erase( matches.begin(), matches.end() );

  size_t beg = start;
  
  for( ; at( beg ) == delim && beg < size(); beg++ );

  if( beg >= size() )
    return( 0 );
  
  matches.push_back( ScanMatch( start, size() - start ) );

  for( size_t end = find( delim, beg ); end < size(); end = find( delim, beg ) )
    {
      matches.push_back( ScanMatch( beg , end - beg) );

      for( beg = end + 1; at( beg ) == delim && beg < size();  beg++ );

      if( beg >= size() )
	break;
    }
  
  if( beg != start )
    {
      matches.push_back( ScanMatch( beg , size() - beg) );
    }

  return( matches.size() );
}

size_t
Str::scanPattern( const RegexScan & exp, size_t start )
{
  matches.erase( matches.begin(), matches.end() );

  const char *  str = strbase() + start;
  size_t    	len = size() - start;

  matches.push_back( ScanMatch( start, length( str ) ) );
  
  for( ; exp.search( str, 0, len );
      str += (exp.matchStart(0) + exp.matchLength(0) ),
      len -= (exp.matchStart(0) + exp.matchLength(0) ) )
	 
    {
      matches.push_back( ScanMatch( pos( str ), exp.matchStart(0) ) );
    }
  
  
  if( matches.size() == 1 )
    {
      matches.erase( matches.begin(), matches.end() );
      return( 0 );
    }
  else
    {
      matches.push_back( ScanMatch( pos( str ), length(str) ) );
      return( matches.size() );
    }
}

size_t
Str::scanString(
  const char *	delimStr,
  size_t    	scanStart,
  size_t    	delimLength
  )
{
  if( ! delimStr || delimStr[0] == 0 ) return( 0 );
  
  const char * 	str = strbase() + scanStart;
  size_t    	dLen = (delimLength == npos) ? strlen( delimStr ) : delimLength;

  matches.push_back( ScanMatch( pos( str ), length( str )) );

  const char * found = StringSearch( str, length( str ), delimStr, dLen );

  for( ; found ;
	 str = found+dLen,
	 found = StringSearch( str, length( str ), delimStr, dLen ) )
    {
      matches.push_back( ScanMatch( pos(str), found - str ) );
    }

  if( matches.size() == 1 )
    {
      matches.erase( matches.begin(), matches.end() );
      return( 0 );
    }
  else
    {
      matches.push_back( ScanMatch( pos(str), length( str ) ) );
      return( matches.size() );
    }
}


// io helpers  * * * * * * * * * * * * * * * * * * * * * * * * * * * *


istream &
Str::getDelim( istream & src, char delim, bool discard  )
{
  // get the first char before modifing this
  // if it is an EOF. dont modify
  
  char ch;
  
  if( ! src.get( ch ).good() ) return( src );

  seekp(0);
  
  for( ; src.good(); src.get( ch ) )
    {
      if( ch == delim )
	{
	  if( ! discard )
	    append( ch );
	  return( src );
	}
      
      append( ch );
    }

  return( src );
}

istream &
Str::getDelim( istream & src, const char * delimChars, bool discard  )
{
  // get the first char before modifing this
  // if it is an EOF. dont modify
  
  char ch;
  
  if( ! src.get( ch ).good() ) return( src );

  seekp(0);
  
  for( ; src.good(); src.get( ch ) )
    {
      
      if( strchr( delimChars, ch ) )
	{
	  if( ! discard )
	    append( ch );
	  return( src );
	}

      append( ch );
    }

  return( src );
}

istream &
Str::get( istream & src, size_t size )
{
  size_t len = size;
  reset();
  
  // if the put buffer is not big enough read
  // the string the hard way

  if( rdbuf()->psize() < len )
    {
      char buf[1024];
      while( len )
	{
	  src.read( buf, min( len, sizeof(buf) ) );
	  if( ! src.gcount() )
	    break;
	  rdbuf()->sputn( buf, src.gcount() );
	  len -= src.gcount();
	}
    }
  else
    {
      while( len )
	{
	  src.read( rdbuf()->pptr(), len );
	  if( ! src.gcount() )
	    break;
#ifdef __linux__
	  // This is a major hack to get around a problem with
	  // GNU's libg++ strstream implementation.

	  rdbuf()->_IO_write_ptr += src.gcount();
#else
	  rdbuf()->seekoff( src.gcount(), ios::cur, ios::out );
#endif
	  len -= src.gcount();
	}
    }
  return( src );
}
  
istream &
Str::read( istream & src )
{
  size_t    len;

  src.read( (char *)&len, sizeof( len ) );

  return( get( src, len ) );
}
  
ostream &
Str::write( ostream & dest ) const
{
  size_t len = length();
  dest.write( (const char *)&len, sizeof( len ) );
  dest.write( strbase(), length() );
  return( dest );
}
  

File &
Str::read( File & src )
{
  size_t len = size();
  reset();
  
  // if the put buffer is not big enough read
  // the string the hard way

  if( rdbuf()->psize() < len )
    {
      char buf[1024];
      while( len )
	{
	  src.read( buf, min( len, sizeof(buf) ) );
	  if( ! src.gcount() )
	    break;
	  rdbuf()->sputn( buf, src.gcount() );
	  len -= src.gcount();
	}
    }
  else
    {
      while( len )
	{
	  src.read( rdbuf()->pptr(), len );
	  if( ! src.gcount() )
	    break;
#ifdef __linux__
	  // This is a major hack to get around a problem with
	  // GNU's libg++ strstream implementation.

	  rdbuf()->_IO_write_ptr += src.gcount();
#else
	  rdbuf()->seekoff( src.gcount(), ios::cur, ios::out );
#endif
	  len -= src.gcount();
	}
    }
  return( src );
}

File &
Str::write( File & dest ) const
{
  size_t len = length();
  dest.write( &len, sizeof( len ) );
  dest.write( strbase(), length() );
  return( dest );
}
  
  
    
bool
Str::writeNum( unsigned long num, unsigned short base, bool neg )
{
  static const char lDigits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
  static const char uDigits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  const char * digits = ((flags() & ios::uppercase) ? uDigits : lDigits );
  
  char buf[ ( 2 * ( sizeof( unsigned long ) * CHAR_BIT ) + 5 ) ];
  int  len = sizeof( buf ) - 2;
  int  pos = len;

  buf[ len + 1 ] = 0;

  unsigned long value;
  for( value = num; value >= base; value /= base )
    {
      buf[ pos ] = digits[ (value % base) ];
      pos--;
    }
  
  if( value || pos == len )
    {
      buf[ pos ] = digits[ value ];
      pos --;
    }

  if( flags() & ios::showbase )
    {
      if( base == 16 )
	{
	  if( flags() & ios::uppercase )
	    buf[ pos ] = 'X';
	  else
	    buf[ pos ] = 'x';

	  pos--;
	  buf[ pos ] = '0';
	  pos--;
	}
      if( base == 8 )
	{
	  buf[ pos ] = '0';
	  pos--;
	}
    }

  if( neg )
    {
      buf[ pos ] = '-';
      pos--;
    }
  else
    {
      if( flags() & ios::showpos )
	{
	  buf[ pos ] = '+';
	  pos--;
	}
    }

  if( width() )
    {
      if( (flags() & ios::left) )
	{
 	  rdbuf()->sputn( &(buf[pos+1]), len - pos );
	  for( int w = 0; w < width() - ( len - pos ); w++ )
	    put( fill() );
	}
      else
	{
	  for( int w = 0; w < width() - ( len - pos ); w++ )
	    put( fill() );
	  rdbuf()->sputn( &(buf[pos+1]), len - pos );
	}
      width(0);
    }
  else
    {
      rdbuf()->sputn( &(buf[pos+1]), len - pos );
    }
  return( true );
}

  


// getClassName - return the name of this class
const char *
Str::getClassName( void ) const
{
  return( "Str" );
}

// good - return TRUE if no detected errors
bool
Str::good( void ) const
{
  return( ios::good() );
}

// error - return a string describing the current state
const char *
Str::error( void ) const
{
  static Str errStr;
  errStr.reset();

  errStr << getClassName();

  if( good() )
    {
       errStr << ": Ok";
    }
  else
    {
      errStr << ": unknown error";
    }

  return( errStr.cstr() );
}

ostream &
Str::dumpInfo( 
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  ) const
{
  if( showVer )
    {
      dest << getClassName() << ":\n";
      dest << getVersion() << '\n';
    }

  
  if( ! good() )
    dest << prefix << "Error:    " << error() << '\n';
  else
    dest << prefix << "good" << '\n';

  if( matches.size() )
    {
      int m = 0;
      for( vector<ScanMatch>::const_iterator them = matches.begin();
	   them;
	   them++ )
	{
	  dest << prefix << "matches[" << m << "].pos:   "
	       << (*them).pos << '\n';
	  dest << prefix << "matches[" << m << "].len:   "
	       << (*them).len << '\n';
	}
    }

  if( rdbuf() )
    {
      Str pre;
      pre = prefix;
      pre << "rdbuf:" << rdbuf()->getClassName() << "::";

      rdbuf()->dumpInfo( dest, pre, false );
    }
  

  return( dest  );
}  


const char *
Str::getVersion( void ) const
{
  static Str ver;
  ver = version;
  if( rdbuf() )
    ver << '\n' << rdbuf()->getVersion();
  return( ver );
}

#ifdef STD_STRING
int
Str::compare( const string & two, size_t start, size_t len ) const
{
  OUT_OF_RANGE( start > size(), false );
  
  size_t oneLen = min( size() - start, len );
  size_t twoLen = min( two.size(), len );

  int diff = strncmp( strbase() + start, two.c_str(), min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}
#endif

#ifdef STD_STRING
int
Str::fcompare( const string & two, size_t start, size_t len ) const
{
  OUT_OF_RANGE( start > size(), false );
  
  size_t oneLen = min( size() - start, len );
  size_t twoLen = min( two.size(), len );

  int diff = StringCaseCompare( strbase() + start, two.c_str(),
				min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}  
#endif


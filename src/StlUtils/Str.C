//
// File:        Str.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/30/95 15:08 
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//

#include "Str.hh"
#include "StlUtilsMisc.hh"
#include "Compare.hh"


#if defined( STLUTILS_DEBUG )
#include <Str.ii>
#else

#endif

STLUTILS_VERSION(
  Str,
  "$Id$" );

const Str::size_type Str::npos = NPOS;

#if defined( Sun5 ) 
// This is UNBELIEVABLE but ...
void
unsafe_ios::operator = ( unsafe_ios & )
{
}

void
ios::operator = ( ios & )
{
}
#endif


Str::Str( void )
  : iostream( new StrStreambuf )
{
}


inline
Str::size_type
Str::length( const char * from )
{
  return( length() - (from - strbase()) );
}

inline
Str::size_type
Str::pos( const char * at )
{
  return( at - strbase() );
}
  



Str::~Str( void )
{
  delete rdbuf();
}


// append  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Str &
Str::append( const char * src, size_type srcLen )
{
  // there is a real danger of overlap so check for it

  if( ! src )
    return( *this );
      
  size_type  appLen;

  if( srcLen != npos )
    {
      const char * nullpos = (const char *)memchr( src, 0, srcLen );

      if( nullpos )
	appLen = nullpos - src;
      else
	appLen = srcLen;
    }
  else
    {
      appLen = strlen( src );
    }
  
  if( ! appLen )
    return( *this );
      
  if( MemOverlap( src, appLen, strbase(), size() ) )
    {
      char * tmp = new char[ appLen + 1 ];
      STLUTILS_EXCPT_BAD_ALLOC( tmp == 0, *this );
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
  size_type    	start,
  size_type    	len,
  const char * 	src,
  size_type    	srcLen
  )
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), *this );

  size_type    replaceLen = min( len, size() - start );
  
  size_type    keepSize = size() - ( start + replaceLen );
  char *    keepString = 0;

  if( keepSize )
    {
      keepString = new char[ keepSize + 1];
      STLUTILS_EXCPT_BAD_ALLOC( keepString == 0, *this );
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
  size_type    start,
  size_type    len,
  size_type    count,
  char 	    src
  )
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), *this );

  size_type    replaceLen = min( len, size() - start );
  
  size_type    keepSize = size() - ( start + replaceLen );
  char *    keepString = 0;

  if( keepSize )
    {
      keepString = new char[ keepSize + 1];
      STLUTILS_EXCPT_BAD_ALLOC( keepString == 0, *this );
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
  size_type    start = (size_type)(min( 0L, (long)(first - begin())));
  size_type    replaceLen = last - first;
  
  size_type    keepSize = size() - ( start + replaceLen );
  char *    keepString = 0;

  if( keepSize )
    {
      keepString = new char[ keepSize + 1];
      STLUTILS_EXCPT_BAD_ALLOC( keepString == 0, *this );
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
Str::compare( const Str & two, size_type start, size_type len ) const
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_type oneLen = min( size() - start, len );
  size_type twoLen = min( two.size(), len );

  int diff = strncmp( strbase() + start, two.strbase(), min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
Str::compare( const SubStr & two, size_type start, size_type len ) const
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_type oneLen = min( size() - start, len );
  size_type twoLen = min( two.size(), len );

  int diff = strncmp( strbase() + start, two.strbase(), min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}  

int
Str::compare( const char * two, size_type start, size_type len ) const
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), false );

  // no string I have 1 or more chars from start, return 1 (I'm bigger)
  //  I have no chars (we are both empty, return 0
  if( ! two )
    return( size() - start ? 1 : 0  );
  
  size_type oneLen = min( size() - start, len );
  size_type twoLen = min( (size_type)strlen( two ), len );

  int diff = strncmp( strbase() + start, two, min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
compare( const SubStr & one, const Str & two, Str::size_type len )
{
  return( one.compare( two, 0, len ) );
}

int
compare( const char * one, const Str & two, Str::size_type len )
{
  Str::size_type oneLen = min( (Str::size_type)strlen( one ), len );
  Str::size_type twoLen = min( two.size(), len );

  int diff = strncmp( one, two.strbase(), min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}


	 
int
Str::fcompare( const Str & two, size_type start, size_type len ) const
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_type oneLen = min( size() - start, len );
  size_type twoLen = min( two.size(), len );

  int diff = StringCaseCompare( strbase() + start, two.strbase(),
				min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
Str::fcompare( const SubStr & two, size_type start, size_type len ) const
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_type oneLen = min( size() - start, len );
  size_type twoLen = min( two.size(), len );

  int diff = StringCaseCompare( strbase() + start, two.strbase(),
				min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}  

int
Str::fcompare( const char * two, size_type start, size_type len ) const
{
  size_type oneLen = min( size() - start, len );
  size_type twoLen = min( (size_type)strlen( two ), len );

  int diff = StringCaseCompare( strbase() + start, two,
				min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
fcompare( const SubStr & one, const Str & two, Str::size_type len )
{
  return( one.fcompare( two, 0, len ) );
}

int
fcompare( const char * one, const Str & two, Str::size_type len )
{
  Str::size_type oneLen = min( (Str::size_type)strlen( one ), len );
  Str::size_type twoLen = min( two.size(), len );

  int diff = StringCaseCompare( one, two.strbase(),
				min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}  

bool
Str::to( Range & r, unsigned short base ) const
{
  size_type rangeInd = find_first_of( "-." );
  
  if( rangeInd != npos )
    {
      size_type lastPos = rangeInd + 1;
      
      if( at( lastPos ) == '.' )
	++ lastPos;
      
      if( lastPos < size() )
	{
	  if( ! substr( lastPos, Str::npos).to( r.second, base ) ) 
	    return( false );
	}
      else
	{
	  r.second = ULONG_MAX;
	}
		  
      if( ! substr(0, rangeInd).to( r.first, base ) )
	return( false );
    }
  else
    {
	      
      if( ! to( r.first, base ) )
	return( false );
      
      r.second = 0;
    }
  
  return( true );
}
  
Str::RangeList::size_type
Str::to( RangeList & range, unsigned short base ) const
{
  if( ! size() )
    return( 0 );
  
  range.erase( range.begin(), range.end() );
  
  // scan is non const, so we need a temp
  Str	tmp( *this );

  size_type matcheCount = tmp.scan( " \t,;:" );

  Range r;
  
  if( matcheCount > 1 )
    {
      
      for( size_type m = 1; m < matcheCount; ++ m )
	{
	  Str   numseq =  tmp.scanMatch( m );
	  
	  if( numseq.to( r, base ) )
	    {
	      range.push_back( r );
	    }
	  else
	    {
	      range.erase( range.begin(), range.end() );
	      return( 0 );
	    }
	}
    }
  else
    {
      if( tmp.to( r ) )
	range.push_back( r );
    }
  
  return( range.size() );
}
      
        
	
// modifications * * * * * * * * * * * * * * * * * * * * * * * * * * *


Str::size_type
Str::strip( const char * stripChars )
{
  const char * bufStart = cstr();
  char * destStart = rdbuf()->pbase();

  size_type firstNonStrip = find_first_not_of( stripChars );

  if( firstNonStrip == NPOS )
    {
      // strip all
      reset();
      return( size() );
    }
  
  char * srcStart =  destStart + firstNonStrip;
  char * srcEnd   = strpbrk( srcStart, stripChars );

  if( ! srcEnd )
    {
      if( destStart != srcStart )
	{
	  memmove( destStart, srcStart, size() - firstNonStrip );
	  seekp( size() - firstNonStrip );
	  return( size() );
	}
      else
	{
	  // do NOT strip any
	  return( size() );
	}
    }
  
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

  size_type count = length() - (srcStart - bufStart);
  
  memmove( destStart, srcStart, count );
  seekp( (destStart + count) - bufStart );
  return( length() );
}


// substitute

Str &
Str::substitute( char from, char to, size_type start, bool global )
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), *this );
  
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
Str::substitute( const char * from, const char * to, size_type start, bool global )
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), *this );
  
  size_type fromLen = strlen( from );
  
  if( ! global )
    {
      size_type fromBeg = find( from, start, fromLen );

      if( fromBeg != npos )
	{
	  replace( fromBeg, fromLen, to );
	}
    }
  else
    {
      size_type toLen = strlen( to );
      
      for( size_type fromBeg = find( from, start, fromLen );
	  fromBeg != npos;
	  fromBeg = find( from, fromBeg + toLen, fromLen ) )
	{
	  replace( fromBeg, fromLen, to, toLen );
	}
    }

  return( *this );
}

Str &
Str::substitute(
  const RegexScan & exp,
  const char *	    to,
  size_type    	    start,
  bool	    	    global
  )
{
  const char * base = strbase() + start;
  size_type       bLen = size() - start;
  
  Str repl;
  
  for( size_type expBeg = 0;
      exp.search( base, expBeg, bLen );
      expBeg = exp.matchStart() + repl.size(),
	base = strbase() + start,
	bLen = size() - start )
    {
      repl.reset();
      for( const char * t = to; *t; t++ )
	{
	  if( *t == '\\' )
	    {
	      t++;
	      if( isdigit( *t ) )
		{
		  if( (size_type)(CharToInt( *t )) <= exp.matchCount() )
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

Str::size_type
Str::wrap( size_type w, long pad, long firstPad )
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

  size_type col = fp;
  size_type lines = 0;

  tmp += scanMatch(1);
  col += scanMatchLength(1);
  
  for( size_type m = 2;
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


Str::size_type
Str::scan( const RegexScan & exp, size_type start )
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), 0 );
  
  matches.erase( matches.begin(), matches.end() );

  if( exp.search( strbase(), start, length() ) )
    {
      for( size_type r = 0; r <= exp.matchCount(); r++ )
	{
	  int mBeg = 0;
	  int mLen = 0;

	  exp.matchInfo( mBeg, mLen, r );

	  matches.push_back( ScanMatch( mBeg, mLen ) );
	}
    }
  return( matches.size() );
}
      

Str::size_type
Str::scan(
  const char *	delim,
  bool		multiDelim,
  size_type	start,
  size_type	dLen
  )
{
  matches.erase( matches.begin(), matches.end() );

  matches.push_back( ScanMatch( start, size() - start ) );
  
  size_type delimLen = (dLen == npos) ? strlen( delim ) : dLen;
  
  size_type matchBeg = find_first_not_of( delim, start, delimLen );

  if( matchBeg == npos )
    return( 0 );

  for( size_type matchEnd = find_first_of( delim, matchBeg, delimLen );
      matchEnd != npos;
      matchEnd = find_first_of( delim, matchBeg, delimLen ) )
    {
      matches.push_back( ScanMatch( matchBeg , matchEnd - matchBeg) );

      if( multiDelim )
	{
	  matchBeg = find_first_not_of( delim, matchEnd, delimLen );
	  if( matchBeg == npos )
	    break;
	}	  
      else
	{
	  matchBeg = matchEnd + 1;
	  if( matchBeg >= size() )
	    break;
	}
    }

  if( matchBeg != start )
    {
      matches.push_back( ScanMatch( matchBeg , size() - matchBeg) );
    }

  return( matches.size() );
}
	  
Str::size_type
Str::scan( char delim, bool multiDelim, size_type start )
{
  matches.erase( matches.begin(), matches.end() );

  size_type matchBeg = start;
  
  for( ; at( matchBeg ) == delim && matchBeg < size(); matchBeg ++ );

  if( matchBeg >= size() )
    return( 0 );
  
  matches.push_back( ScanMatch( start, size() - start ) );

  for( size_type matchEnd = find( delim, matchBeg );
       matchEnd < size();
       matchEnd = find( delim, matchBeg ) )
    {
      matches.push_back( ScanMatch( matchBeg , matchEnd - matchBeg) );

      if( multiDelim )
	{
	  for( matchBeg = matchEnd + 1;
	       at( matchBeg ) == delim && matchBeg < size();
	       matchBeg++ );
	}
      else
	{
	  matchBeg = matchEnd + 1;
	}
      
      if( matchBeg >= size() )
	break;
    }
  
  if( matchBeg != start )
    {
      matches.push_back( ScanMatch( matchBeg , size() - matchBeg) );
    }

  return( matches.size() );
}

Str::size_type
Str::scanPattern( const RegexScan & exp, size_type start )
{
  matches.erase( matches.begin(), matches.end() );

  const char *  str = strbase() + start;
  size_type    	len = size() - start;

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

Str::size_type
Str::scanString(
  const char *	delimStr,
  size_type    	scanStart,
  size_type    	delimLength
  )
{
  if( ! delimStr || delimStr[0] == 0 ) return( 0 );
  
  const char * 	str = strbase() + scanStart;
  size_type    	dLen = (delimLength == npos) ? strlen( delimStr ) : delimLength;

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
Str::get( istream & src, size_type size )
{
  size_type len = size;
  reset();
  
  // if the put buffer is not big enough read
  // the string the hard way

  if( rdbuf()->psize() < len )
    {
      char buf[1024];
      while( len )
	{
	  src.read( buf, min( len, (size_type)sizeof(buf) ) );
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
  
Str::size_type
Str::getBinSize( void ) const
{
  return( sizeof( size_type ) + size() );
}

istream &
Str::read( istream & src )
{
  size_type len;

  src.read( (char *)&len, sizeof( len ) );

  return( get( src, len ) );
}

istream &
Str::read( char * dest, int size )
{
  return( istream::read( dest, size ) );
}

istream &
Str::read( unsigned char * dest, int size )
{
  return( istream::read( dest, size ) );
}


ostream &
Str::write( ostream & dest ) const
{
  size_type len = length();
  dest.write( (const char *)&len, sizeof( len ) );
  dest.write( strbase(), length() );
  return( dest );
}

ostream &
Str::write( const char * src, int size )
{
  return( ostream::write( src, size ) );
}

ostream &
Str::write( const unsigned char * src, int size )
{
  return( ostream::write( src, size ) );
}

ostream &
Str::write( const wchar_t * src, int size )
{
  return( ostream::write( src, size ) );
}

ostream &
Str::write( const void * src, size_type size )
{
  return( ostream::write( (const char *)src, size ) );
}

  

ostream &
Str::toStream( ostream & dest ) const
{
  dest << cstr();
  return( dest );
}

istream &
Str::fromStream( istream & src )
{
  return( getDelim( src, " \t\n\r\f" ) );
}


// good - return TRUE if no detected errors
bool
Str::good( void ) const
{
  return( rdbuf() != 0 &&
#if defined( STLUTILS_HAS_CONST_IOSGOOD )
	  ios::good()
#else
	  ios::state == 0
#endif
	  );
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
      size_type eSize = errStr.size();

      if( rdbuf() == 0 )
	errStr << ": no 'streambuf'";
      
#if defined( STLUTILS_HAS_CONST_IOSRDSTATE )
      if( ! ios::good() )
	{
	  if( ios::rdstate() & ios::eofbit )
	    errStr += ": EOF bit set";
	  if( ios::rdstate() & ios::failbit )
	    errStr += ": FAIL bit set";
	  if( ios::rdstate() & ios::badbit )
	    errStr += ": BAD bit set";
	}
#else
      if( state != 0 )
	{
	  if( ios::state & ios::eofbit )
	    errStr += ": EOF bit set";
	  if( ios::state & ios::failbit )
	    errStr += ": FAIL bit set";
	  if( ios::state & ios::badbit )
	    errStr += ": BAD bit set";
	}
#endif
      
      if( eSize == errStr.size() )
	errStr << ": unknown error";
      
    }

  return( errStr.cstr() );
}

// getClassName - return the name of this class
const char *
Str::getClassName( void ) const
{
  return( "Str" );
}

const char *
Str::getVersion( bool withPrjVer ) const
{
  if( rdbuf() )
    return( version.getVer( withPrjVer, rdbuf()->getVersion( false ) ) );
  else
    return( version.getVer( withPrjVer ) );  
}

ostream &
Str::dumpInfo( 
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << Str::getClassName() << ":\n"
	 << Str::getVersion() << '\n';

  
  if( ! Str::good() )
    dest << prefix << "Error: " << Str::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  if( matches.size() )
    {
      Str matchStr;
      
      dest << prefix << "matches.size(): " << matches.size() << '\n';

      for( size_type m = 0; m < matches.size(); m++ )
	{
	  scanMatch( matchStr, m );
	  dest << prefix << "matches[" << m << "].pos:   "
	       << matches[m].pos << '\n';
	  dest << prefix << "matches[" << m << "].len:   "
	       << matches[m].len << '\n';
	  dest << prefix << "matches[" << m << "].SubStr: '"
	       << matchStr << "'\n" ;
	}
    }

  if( rdbuf() )
    {
      Str pre;
      pre = prefix;
      pre << "rdbuf: " << rdbuf()->getClassName() << "::";

      rdbuf()->dumpInfo( dest, pre, false );
    }
  
  return( dest  );
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


#ifdef STD_STRING
int
Str::compare( const string & two, size_type start, size_type len ) const
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_type oneLen = min( size() - start, len );
  size_type twoLen = min( two.size(), len );

  int diff = strncmp( strbase() + start, two.c_str(), min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}
#endif

#ifdef STD_STRING
int
Str::fcompare( const string & two, size_type start, size_type len ) const
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_type oneLen = min( size() - start, len );
  size_type twoLen = min( two.size(), len );

  int diff = StringCaseCompare( strbase() + start, two.c_str(),
				min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}  
#endif

// Revision Log:
//
// $Log$
// Revision 4.6  1998/03/23 10:45:23  houghton
// Changed to eliminate Sun5 compiler warnings.
//
// Revision 4.5  1998/01/22 18:32:18  houghton
// Bug-Fix: substitute() was using wrong value to starts looking for next
//     'from' string.
//
// Revision 4.4  1997/12/29 14:00:32  houghton
// Bug-Fix: strip() was not handling all cases correctly.
//
// Revision 4.3  1997/12/19 14:00:42  houghton
// Port(Sun5): fixed for warning about hiding 'matches'.
//
// Revision 4.2  1997/09/19 11:22:21  houghton
// Changed to use size_type.
//
// Revision 4.1  1997/09/17 15:12:51  houghton
// Changed to Version 4
//
// Revision 3.8  1997/09/17 14:10:20  houghton
// Renamed StlUtilsUtils.hh to StlUtilsMisc.hh
//
// Revision 3.7  1997/09/17 11:08:44  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.6  1997/09/02 13:07:45  houghton
// Added to( Range )
// Added to( RangeList )
//
// Revision 3.5  1997/07/18 19:15:52  houghton
// Port(Sun5): had to define ios::operator = (). I was getting link
//     errors on this. This is a significant bug in Sun's compiler
//     since it is declared as a 'private' member.
// Port(Sun5): changed all locale variables named beg and end to
//     eliminate compiler warnings.
//
// Revision 3.4  1997/03/15 18:05:04  houghton
// Changed append - to prevent inserting nulls (0 char) into the Str even
//     if the src len is specified.
//
// Revision 3.3  1997/03/02 13:20:17  houghton
// Changed to use 'size_type'
//
// Revision 3.2  1996/11/20 12:12:05  houghton
// Removed support for BinStream.
//
// Revision 3.1  1996/11/14 01:24:08  houghton
// Changed to Release 3
//
// Revision 2.6  1996/11/06 18:06:16  houghton
// StlUtils.hh renamed to StlUtilsUtils.hh.
//
// Revision 2.5  1996/10/11 17:42:59  houghton
// Changed: Added new 'multiDelim' arg to scan methods. This arg
//   specifies if multiple consecutive instances of the delimiter are
//   ignored or create separate matches.
//      Example: 'this,is,,a,test'
//               mutliDelim == true:  4 fields
//               multiDelim == false: 5 fields (the third has a 0 length).
//
// Revision 2.4  1996/06/09 09:44:49  houghton
// Bug-Fix: compare( const char * ) if both strings are empty, return 0.
// Bug-Fix: read( BinStream & ) if len was 0, was not reseting string.
//
// Revision 2.3  1996/04/27 13:08:39  houghton
// Cleanup.
//
// Revision 2.2  1995/12/04 11:18:26  houghton
// Bug Fix - Can now compile with out '-DSTLUTILS_DEBUG'.
//
// Revision 2.1  1995/11/10  12:41:03  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  15:28:46  houghton
// Revised
//
//

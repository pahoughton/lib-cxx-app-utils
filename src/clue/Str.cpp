//
// File:        Str.C
// Project:	StlUtils ()
// Desc:        
//
//  Compiled sources for Str
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     05/30/95 15:08 
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
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
  "$Id$ " );

const Str::size_type Str::npos = NPOS;

#if defined( Sun5 ) && defined( WS_42 ) && defined( BROKEN )
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
  : std::iostream( new StrStreambuf )
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

  size_type    replaceLen = std::min( len, size() - start );
  
  size_type    keepSize = size() - ( start + replaceLen );
  char *    keepString = 0;

  if( keepSize )
    {
      keepString = new char[ keepSize + 1];
      STLUTILS_EXCPT_BAD_ALLOC( keepString == 0, *this );
      memcpy( keepString, strbase() + ( start + replaceLen ), keepSize );
    }

  seekp( start, std::ios::beg );

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

  size_type    replaceLen = std::min( len, size() - start );
  
  size_type    keepSize = size() - ( start + replaceLen );
  char *    keepString = 0;

  if( keepSize )
    {
      keepString = new char[ keepSize + 1];
      STLUTILS_EXCPT_BAD_ALLOC( keepString == 0, *this );
      memcpy( keepString, strbase() + ( start + replaceLen ), keepSize );
    }

  seekp( start, std::ios::beg );

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
  size_type    start = (size_type)(std::min( 0L, (long)(first - begin())));
  size_type    replaceLen = last - first;
  
  size_type    keepSize = size() - ( start + replaceLen );
  char *    keepString = 0;

  if( keepSize )
    {
      keepString = new char[ keepSize + 1];
      STLUTILS_EXCPT_BAD_ALLOC( keepString == 0, *this );
      memcpy( keepString, strbase() + ( start + replaceLen ), keepSize );
    }

  seekp( start, std::ios::beg );

  append( srcFirst, srcLast  );

  if( keepString )
    {
      append( keepString, keepSize );
      delete keepString;
    }

  return( *this );
}
  
Str &
Str::replaceAny( const char * chars, char val )
{
  for( iterator them = begin();
      them != end();
      ++ them ) {
    for( const char * rval = chars; *rval; ++ rval ) {
      if( *them == *rval ) {
        *them = '_';
      }
    }
  }
  return(*this);
}

// compare * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


int
Str::compare( const Str & two, size_type start, size_type len ) const
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_type oneLen = std::min( size() - start, len );
  size_type twoLen = std::min( two.size(), len );

  int diff = strncmp( strbase() + start, two.strbase(), std::min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
Str::compare( const SubStr & two, size_type start, size_type len ) const
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_type oneLen = std::min( size() - start, len );
  size_type twoLen = std::min( two.size(), len );

  int diff = strncmp( strbase() + start, two.strbase(), std::min( oneLen, twoLen ) );

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
  
  size_type oneLen = std::min( size() - start, len );
  size_type twoLen = std::min( (size_type)strlen( two ), len );

  int diff = strncmp( strbase() + start, two, std::min( oneLen, twoLen ) );

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
  Str::size_type oneLen = std::min( (Str::size_type)strlen( one ), len );
  Str::size_type twoLen = std::min( two.size(), len );

  int diff = strncmp( one, two.strbase(), std::min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}


	 
int
Str::fcompare( const Str & two, size_type start, size_type len ) const
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_type oneLen = std::min( size() - start, len );
  size_type twoLen = std::min( two.size(), len );

  int diff = StringCaseCompare( strbase() + start, two.strbase(),
				std::min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}

int
Str::fcompare( const SubStr & two, size_type start, size_type len ) const
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_type oneLen = std::min( size() - start, len );
  size_type twoLen = std::min( two.size(), len );

  int diff = StringCaseCompare( strbase() + start, two.strbase(),
				std::min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}  

int
Str::fcompare( const char * two, size_type start, size_type len ) const
{
  size_type oneLen = std::min( size() - start, len );
  size_type twoLen = std::min( (size_type)strlen( two ), len );

  int diff = StringCaseCompare( strbase() + start, two,
				std::min( oneLen, twoLen ) );

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
  Str::size_type oneLen = std::min( (Str::size_type)strlen( one ), len );
  Str::size_type twoLen = std::min( two.size(), len );

  int diff = StringCaseCompare( one, two.strbase(),
				std::min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}  

bool
Str::to( Range & r, unsigned short base ) const
{
  size_type rangeInd = find_first_of( ":." );
  
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
#if defined( STLUTILS_HAVE_LONG_LONG )
	  r.second = LLONG_MAX;
#else
	  r.second = LONG_MAX;
#endif
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

  size_type matcheCount = tmp.scan( " \t,;" );

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
	  ssize_t mBeg = 0;
	  ssize_t mLen = 0;

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
Str::scan(
  const char *	quoteChars,
  char		escChar,
  const char *	delimChars,
  bool		multiDelim,
  size_type	start
  )
{
  matches.erase( matches.begin(), matches.end() );

  if( start >= size() )
    return( 0 );
  
  matches.push_back( ScanMatch( start, size() - start ) );

  size_type	pos( start );
  
  size_type	matchBeg( start );

  for( ; pos < size(); )
    {
      if( strchr( quoteChars, at( pos ) ) )
	{
	  ++ pos;
	  matchBeg = pos;
	      
	  for( ; pos < size(); ++ pos )
	    {
	      if( at( pos ) == escChar )
		{
		  remove( pos, 1 );
		}
	      else
		{
		  if( strchr( quoteChars, at( pos ) ) )
		    {
		      matches.push_back( ScanMatch( matchBeg,
						    pos - matchBeg ) );
		      ++ pos;
		      if( pos >= size() )
			{
			  break;
			}
		      else
			{
			  if( strchr( delimChars, at( pos ) ) )
			    {
			      ++ pos;
			      break;
			    }
			  else
			    {
			      // invalid format - non escaped
			      // quote in the middle of a field
			      return( 0 );
			    }
			}
		    }
		}
	    }
	}
      else
	{
      
	  if( at( pos ) == escChar )
	    {
	      remove( pos, 1 );
	    }
      
	  matchBeg = pos;
	  
	  for( ; pos < size(); ++ pos )
	    {
	      if( at( pos ) == escChar )
		{
		  remove( pos, 1 );
		}
	      else
		{
		  if( strchr( delimChars, at( pos ) ) )
		    {
		      matches.push_back( ScanMatch (matchBeg,
						    pos - matchBeg ) );
		      ++ pos;
		      break;
		    }
		}
	    }
	  
	  if( pos >= size() )
	    {
	      // did not find another delim;
	      matches.push_back( ScanMatch( matchBeg,
					    size() - matchBeg ) );
	      break;
	    }
	}
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


std::istream &
Str::getDelim( std::istream & src, char delim, bool discard  )
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

std::istream &
Str::getDelim( std::istream & src, const char * delimChars, bool discard  )
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

std::istream &
Str::get( std::istream & src, size_type size )
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
	  src.read( buf, std::min( len, (size_type)sizeof(buf) ) );
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
#if defined( STLUTILS_STRSTREAM_HACK )
	  // This is a major hack to get around a problem with
	  // GNU's libg++ strstream implementation.

	  rdbuf()->_IO_write_ptr += src.gcount();
#else
	  rdbuf()->seekoff( src.gcount(), std::ios::cur, std::ios::out );
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

std::istream &
Str::read( std::istream & src )
{
  size_type len;

  src.read( (char *)&len, sizeof( len ) );

  return( get( src, len ) );
}

std::istream &
Str::read( char * dest, int size )
{
  rdbuf()->readPrep();
  
  return( std::istream::read( dest, size ) );
}

#if defined( STLUTILS_STR_UNSIGNED )
std::istream &
Str::read( unsigned char * dest, int size )
{
  return( std::istream::read( dest, size ) );
}
#endif

std::ostream &
Str::write( std::ostream & dest ) const
{
  size_type len = length();
  dest.write( (const char *)&len, sizeof( len ) );
  dest.write( strbase(), length() );
  return( dest );
}

std::ostream &
Str::write( const char * src, int size )
{
  return( std::ostream::write( src, size ) );
}

#if defined( STLUTILS_STR_UNSIGNED )
std::ostream &
Str::write( const unsigned char * src, int size )
{
  return( std::ostream::write( src, size ) );
}
#endif

#if defined( STLUTILS_STR_WCHAR )
std::ostream &
Str::write( const wchar_t * src, int size )
{
  return( std::ostream::write( src, size ) );
}
#endif

std::ostream &
Str::write( const void * src, size_type size )
{
  return( std::ostream::write( (const char *)src, size ) );
}

  

std::ostream &
Str::toStream( std::ostream & dest ) const
{
  dest << cstr();
  return( dest );
}

std::istream &
Str::fromStream( std::istream & src )
{
  return( getDelim( src, " \t\n\r\f" ) );
}


// good - return TRUE if no detected errors
bool
Str::good( void ) const
{
  return( rdbuf() != 0 &&
#if defined( STLUTILS_HAS_CONST_IOSGOOD )
	  std::ios::good()
#else
	  std::ios::state == 0
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
      if( ! std::ios::good() )
	{
	  if( std::ios::rdstate() & std::ios::eofbit )
	    errStr += ": EOF bit set";
	  if( std::ios::rdstate() & std::ios::failbit )
	    errStr += ": FAIL bit set";
	  if( std::ios::rdstate() & std::ios::badbit )
	    errStr += ": BAD bit set";
	}
#else
      if( state != 0 )
	{
	  if( std::ios::state & std::ios::eofbit )
	    errStr += ": EOF bit set";
	  if( std::ios::state & std::ios::failbit )
	    errStr += ": FAIL bit set";
	  if( std::ios::state & std::ios::badbit )
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

std::ostream &
Str::dumpInfo( 
  std::ostream &	dest,
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

#if defined( STLUTILS_HAVE_LONG_LONG )
#define NumType unsigned long long
#else
#define NumType unsigned long
#endif

bool
Str::writeNum( NumType num, unsigned short base, bool neg )
{
  static const char lDigits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
  static const char uDigits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  const char * digits = ((flags() & std::ios::uppercase) ? uDigits : lDigits );
  
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

  if( flags() & std::ios::showbase )
    {
      if( base == 16 )
	{
	  if( flags() & std::ios::uppercase )
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
      if( flags() & std::ios::showpos )
	{
	  buf[ pos ] = '+';
	  pos--;
	}
    }

  if( width() )
    {
      if( (flags() & std::ios::left) )
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
  
  size_type oneLen = std::min( size() - start, len );
  size_type twoLen = std::min( two.size(), len );

  int diff = strncmp( strbase() + start, two.c_str(), std::min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}
#endif

#ifdef STD_STRING
int
Str::fcompare( const string & two, size_type start, size_type len ) const
{
  STLUTILS_EXCPT_OUT_OF_RANGE( start > size(), false );
  
  size_type oneLen = std::min( size() - start, len );
  size_type twoLen = std::min( two.size(), len );

  int diff = StringCaseCompare( strbase() + start, two.c_str(),
				min( oneLen, twoLen ) );

  return( (diff == 0) ? ::compare( oneLen, twoLen ) : diff );
}  
#endif


// 1995-06-04 (cc) Paul Houghton - (paul4hough@gmail.com)

#include "SubStr.hpp"
#include "Str.hpp"
#include "clue/compare"

#include <algorithm>
namespace clue {

const SubStr::size_type SubStr::npos = NPOS;

Str SubStr::dummyStr("dummy");

// compare * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


int
SubStr::compare( const Str & two, size_type start, size_type compLen ) const
{
  size_t oneLen = std::min( size() - start, compLen );
  size_t twoLen = std::min( two.size(), compLen );

  int diff = strncmp( strbase() + start, two.strbase(), std::min( oneLen, twoLen ) );

  return( (diff == 0) ? clue::compare( oneLen, twoLen ) : diff );
}

int
SubStr::compare( const SubStr & two, size_type start, size_type compLen ) const
{
  size_type oneLen = std::min( size() - start, compLen );
  size_type twoLen = std::min( two.size(), compLen );

  int diff = strncmp( strbase() + start, two.strbase(), std::min( oneLen, twoLen ) );

  return( (diff == 0) ? clue::compare( oneLen, twoLen ) : diff );
}


int
SubStr::compare( const char * two, size_type start, size_type compLen ) const
{
  size_type oneLen = std::min( size() - start, compLen );
  size_type twoLen = std::min( (size_type)strlen( two ), compLen );

  int diff = strncmp( strbase() + start, two, std::min( oneLen, twoLen ) );

  return( (diff == 0) ? clue::compare( oneLen, twoLen ) : diff );
}

int
SubStr::fcompare( const Str & two, size_type start, size_type compLen ) const
{
  size_type oneLen = std::min( size() - start, compLen );
  size_type twoLen = std::min( two.size(), compLen );

  int diff = StringCaseCompare( strbase() + start, two.strbase(),
				std::min( oneLen, twoLen ) );

  return( (diff == 0) ? clue::compare( oneLen, twoLen ) : diff );
}

int
SubStr::fcompare( const SubStr & two, size_type start, size_type compLen ) const
{
  size_type oneLen = std::min( size() - start, compLen );
  size_type twoLen = std::min( two.size(), compLen );

  int diff = StringCaseCompare( strbase() + start, two.strbase(),
				std::min( oneLen, twoLen ) );

  return( (diff == 0) ? clue::compare( oneLen, twoLen ) : diff );
}

int
SubStr::fcompare( const char * two, size_type start, size_type compLen ) const
{
  size_type oneLen = std::min( size() - start, compLen );
  size_type twoLen = std::min( (size_type)strlen( two ), compLen );

  int diff = StringCaseCompare( strbase() + start, two,
				std::min( oneLen, twoLen ) );

  return( (diff == 0) ? clue::compare( oneLen, twoLen ) : diff );
}


int
compare( const char * one, const SubStr & two, SubStr::size_type len )
{
  SubStr::size_type oneLen = std::min( (SubStr::size_type)strlen( one ), len );
  SubStr::size_type twoLen = std::min( two.size(), len );

  int diff = strncmp( one, two.strbase(), std::min( oneLen, twoLen ) );

  return( (diff == 0) ? clue::compare( oneLen, twoLen ) : diff );
}

int
fcompare( const char * one, const SubStr & two, SubStr::size_type len )
{
  SubStr::size_type oneLen = std::min( (SubStr::size_type)strlen( one ), len );
  SubStr::size_type twoLen = std::min( two.size(), len );

  int diff = StringCaseCompare( one, two.strbase(), std::min( oneLen, twoLen ) );

  return( (diff == 0) ? clue::compare( oneLen, twoLen ) : diff );
}

SubStr::size_type
SubStr::getBinSize( void ) const
{
  return( sizeof( size_type ) + len );
}

std::ostream &
SubStr::write( std::ostream & dest ) const
{
  size_type sLen = len;
  dest.write( (const char *)&sLen, sizeof( sLen ) );
  dest.write( strbase(), len );
  return( dest );
}

std::istream &
SubStr::read( std::istream & src )
{
  Str tmp;
  tmp.read( src );
  if( src.good() )
    str.replace( pos, len, tmp );
  len = tmp.size();
  return( src );
}

std::ostream &
SubStr::toStream( std::ostream & dest ) const
{
  std::ostream::sentry   opfx( dest );
  if( ! opfx )
    return( dest );

  if( dest.width()
      && (dest.flags() & (std::ios::right | std::ios::internal ))
      || ! (dest.flags() & std::ios::adjustfield) )
    {
      for( int fcnt = size(); fcnt < dest.width(); ++ fcnt )
	{
	  if( ! dest.put( dest.fill() ).good() )
	      return( dest );
	}
    }

  if( dest.write( strbase(), size() ).good() )
    {
      if( dest.width() && ( dest.flags() & std::ios::left) )
	{
	  for( int fcnt = size(); fcnt < dest.width(); ++ fcnt )
	    {
	      if( ! dest.put( dest.fill() ).good() )
		return( dest );
	    }
	}
    }
  dest.width(0);

  return( dest );
}

const char *
SubStr::error( void ) const
{
  static Str errStr;
  errStr.reset();

  errStr << "SubStr";

  if( good() )
    {
       errStr << ": Ok";
    }
  else
    {
      errStr << ": " << constStr.error();
    }

  return( errStr.cstr() );
}

std::ostream &
SubStr::dumpInfo(
  std::ostream & dest,
  const char *   prefix
  ) const
{
  if( ! SubStr::good() )
    dest << prefix << "Error: " << SubStr::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  Str pre;
  pre << prefix << "str:";

  constStr.dumpInfo( dest, pre );

  dest << prefix << "pos:        " << pos << "'\n";
  dest << prefix << "len:        " << len << "\n";
  dest << prefix << "SubString:  '" << *this << "'\n";

  dest << '\n';

  return( dest  );
}

int
SubStr::fcompare( const std::string & two, size_t start, size_t len ) const
{
  size_t oneLen = std::min( size() - start, len );
  size_t twoLen = std::min( two.length(), len );

  int diff = StringCaseCompare( strbase() + start, two.c_str(),
				std::min( oneLen, twoLen ) );

  return( (diff == 0) ? clue::compare( oneLen, twoLen ) : diff );
}

int
compare( const std::string & one, const SubStr & two, size_t len )
{
  size_t oneLen = std::min( one.length(), len );
  size_t twoLen = std::min( two.size(), len );

  int diff = strncmp( one.c_str(), two.strbase(), std::min( oneLen, twoLen ) );

  return( (diff == 0) ? clue::compare( oneLen, twoLen ) : diff );
}

int
fcompare( const std::string & one, const SubStr & two, size_t len )
{
  size_t oneLen = std::min( one.length(), len );
  size_t twoLen = std::min( two.size(), len );

  int diff = StringCaseCompare( one.c_str(), two.strbase(), std::min( oneLen, twoLen ) );

  return( (diff == 0) ? clue::compare( oneLen, twoLen ) : diff );
}

int
SubStr::compare( const std::string & two, size_t start, size_t len ) const
{
  size_t oneLen = std::min( size() - start, len );
  size_t twoLen = std::min( two.length(), len );

  int diff = strncmp( strbase() + start, two.c_str(), std::min( oneLen, twoLen ) );

  return( (diff == 0) ? clue::compare( oneLen, twoLen ) : diff );
}

}; // namespace clue

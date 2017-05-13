// 1995-06-15 (cc) Paul Houghton <paul4hough@gmail.com>

#include "FilePath.hpp"

#include "User.hpp"

#include <fnmatch.h>

#include <cstdio>
#include <cstring>

namespace clue {

const char FilePath::DirDelim = '/';

Str
FilePath::getName( void ) const
{
  Str name;

  size_type nameBeg = rfind( dirDelim );
  size_type nameEnd = rfind( extDelim );

  if( nameBeg == npos )
    {
      if( nameEnd == npos )
	{
	  return( *this );
	}
      else
	{
	  name = substr( 0, nameEnd );
	  return( name );
	}
    }

  if( nameEnd == npos )
    name = substr( nameBeg + 1 );
  else
    name = substr( nameBeg + 1, nameEnd  - (nameBeg + 1) );

  return( name );
}

bool
FilePath::match( const char * pattern ) const
{
  return( fnmatch( pattern, c_str(), 0 ) == 0 );
}

bool
FilePath::expand( void )
{
  bool changed = false;

  for( Str::size_type pos = find( '$' );
       pos != npos;
       pos = find( '$', pos ) ) {

    Str            evar;
    Str::size_type epos = npos;

    if( at( pos + 1 ) == '{' ) {

      epos = find( '}', pos + 2 );
      if( epos == npos )
	return( false );

      evar.assign( *this, pos + 2, epos - (pos + 2) );
      ++ epos;
    } else {
      for( epos = pos + 1;
	   epos < size()
	     && ( ( 'A' <= at( epos ) && at( epos ) <= 'Z')
		  || ( 'a' <= at( epos ) && at( epos ) <= 'z')
		  || ( '0' <= at( epos ) && at( epos ) <= '9')
		  || '_' == at( epos ));
	   ++ epos );
      evar.assign( *this, pos + 1, epos - (pos + 1));
    }
    const char * eval    = getenv( evar );
    size_t       elen = eval ? strlen( eval ) : 0;

    if( elen ) {
      replace( pos, epos - pos, eval );
      pos += elen;

    } else {
      remove( pos, epos - pos );
    }
    changed = true;
  }

  if( size() && at((size_type)0) == '~' )
    {
      if( size() == 1 || at(1) == '/' )
	{
	  const char * home = getenv("HOME");
	  if( home && strlen( home ) )
	    {
	      replace( 0, 1, home );
	      changed = true;
	    }
	  else
	    {
	      User user;
	      if( user.good() && user.getHome() && strlen( user.getHome() ) )
		{
		  replace( 0, 1, user.getHome() );
		  changed = true;
		}
	    }
	}
      else
	{
	  Str userName( *this, (Str::size_type) 1, find( '/' ) - 1 );
	  User user( userName.c_str() );
	  if( user.good() && user.getHome() && strlen( user.getHome() ) )
	    {
	      replace( 0, userName.size() + 1, user.getHome() );
	      changed = true;
	    }
	}
    }

  return( changed );
}



bool
FilePath::setPrefix( const char * prefix )
{
  if( prefix[0] == 0 )
    return( true );

  if( at((size_type)0) == dirDelim )
    {
      if( prefix[ strlen( prefix ) - 1 ] == dirDelim )
	{
	  insert( 0, prefix, strlen( prefix ) - 2 );
	}
      else
	{
	  insert( 0, prefix );
	}
    }
  else
    {
      if( prefix[ strlen( prefix ) - 1 ] == dirDelim )
	{
	  insert( 0, prefix );
	}
      else
	{
	  insert( (size_type)0, 1, dirDelim );
	  insert( 0, prefix );
	}
    }
  return( true );
}

bool
FilePath::setPath( const char * path )
{
  size_t end = rfind( dirDelim );

  if( end == npos )
    {
      if( path[ strlen( path ) - 1 ] == dirDelim )
	{
	  insert( 0, path );
	}
      else
	{
	  insert( (size_type)0, 1, dirDelim );
	  insert( 0, path );
	}
    }
  else
    {
      if( path[ strlen( path ) - 1 ] == dirDelim )
	{
	  replace( 0, end + 1, path );
	}
      else
	{
	  replace( 0, end, path );
	}
    }
  return( true );
}

bool
FilePath::changePath( const char * oldDirs, const char * newDirs )
{
  size_type pathBeg = find( oldDirs );

  if( pathBeg == npos )
    return( false );

  replace( pathBeg, strlen( oldDirs ), newDirs );

  return( true );
}

void
FilePath::cleanFn( void )
{
  if( length() ) {
    if( *begin() == '.' ) {
      *begin() = '_';
    }
    replaceAny( CLUE_CLEANFN_CHARS, '_' );
  }
}
bool
FilePath::setFileName( const char * name )
{
  size_t fnBeg = rfind( dirDelim );

  if( fnBeg == npos )
    {
      assign( name );
    }
  else
    {
      replace( fnBeg + 1, npos, name );
    }
  return( true );
}

bool
FilePath::setName( const char * name )
{
  return( setName( name, extDelim ) );
}

bool
FilePath::setName( const char * name, char ext )
{
  size_t nameBeg = rfind( dirDelim );
  size_t nameEnd = rfind( ext );

  if( nameBeg == npos )
    nameBeg = 0;
  else
    nameBeg++;

  if( nameEnd == npos )
    nameEnd = size();

  replace( nameBeg, nameEnd - nameBeg, name );

  return( true );
}

bool
FilePath::setName( const char * name, const char * ext )
{
  size_t nameBeg = rfind( dirDelim );
  size_t nameEnd = find( ext);

  if( nameBeg == npos )
    nameBeg = 0;
  else
    nameBeg++;

  if( nameEnd == npos )
    nameEnd = size();

  replace( nameBeg, nameEnd - nameBeg, name );

  return( true );
}

bool
FilePath::setExt( const char * ext )
{
  return( setExt( ext, extDelim ) );
}

bool
FilePath::setExt( const char * ext, char delim )
{
  size_t extBeg = rfind( delim );

  if( extBeg == npos )
    {
      append( 1, extDelim );
      append( ext );
    }
  else
    {
      replace( extBeg + 1, npos, ext );
    }
  return( true );
}

bool
FilePath::setExt( const char * oldExt, const char * newExt )
{
  size_t extBeg = rfind( oldExt );

  if( extBeg == npos || (extBeg + strlen( oldExt )) != size() )
    return( false );

  replace( extBeg, size() - extBeg, newExt );
  return( true );
}

bool
FilePath::setTempName( const char * prefix )
{
  return( setTempName( getPath().c_str(), prefix ) );
}

bool
FilePath::setTempName( const char * path, const char * prefix )
{
  Str fnPrefix;

  if( prefix != 0 )
    fnPrefix = prefix;
  else
    fnPrefix = getName();

  if( fnPrefix.size() )
    fnPrefix = fnPrefix.substr(0,5);
  else
    fnPrefix = "tmp";

  {
    // tempnam returns a malloc'ed string
    char * tempFileName = tempnam( path, fnPrefix.c_str() );
    assign( tempFileName );
    free( tempFileName );
  }

  return( size() != 0 );
}

std::ostream &
FilePath::toStream( std::ostream & dest ) const
{
  return( Str::toStream( dest ) );
}

FilePath::size_type
FilePath::getBinSize( void ) const
{
  return( sizeof( size_type ) +
	  size() +
	  sizeof( dirDelim ) +
	  sizeof( extDelim ) );
}


std::ostream &
FilePath::write( std::ostream & dest ) const
{
  size_type  len = size();
  dest.write( (const char *)&len, sizeof( len ) );
  dest.write( c_str(), size() );
  dest.write( &dirDelim, sizeof( dirDelim ) );
  dest.write( &extDelim, sizeof( extDelim ) );
  return( dest );
}

std::ostream &
FilePath::write( const char * src, int size )
{
  return( Str::write( src, size ) );
}

std::ostream &
FilePath::write( const unsigned char * src, int size )
{
  return( Str::write( src, size ) );
}

std::ostream &
FilePath::write( const wchar_t * src, int size )
{
  return( Str::write( src, size ) );
}

std::ostream &
FilePath::write( const void * src, size_type size )
{
  return( Str::write( src, size ) );
}



std::istream &
FilePath::read( std::istream & src )
{
  size_type  len = 0;
  src.read( (char *)&len, sizeof( len ) );

  if( ! len )
    return( src );

  char * buf = new char[ len + 5];
  src.read( buf, len );
  buf[len] = 0;
  assign( buf );
  delete buf;

  src.read( &dirDelim, sizeof( dirDelim ) );
  src.read( &extDelim, sizeof( extDelim ) );
  return( src );
}

std::istream &
FilePath::read( char * dest, int size )
{
  return( Str::read( dest, size ) );
}

std::istream &
FilePath::read( unsigned char * dest, int size )
{
  return( Str::read( dest, size ) );
}


bool
FilePath::good( void ) const
{
  return( Str::good() );
}

// error - return a Str describing the current state
const char *
FilePath::error( void ) const
{
  static Str errStr;

  errStr = "FilePath";

  if( good() )
    {
       errStr += ": ok.";
    }
  else
    {
      size_type eSize = errStr.size();

      if( ! Str::good() )
	errStr << Str::error();

      if( eSize == errStr.size() )
	errStr += ": unknown error.";
    }

  return( errStr.c_str() );
}

std::ostream &
FilePath::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

  if( ! FilePath::good() )
    dest << prefix << "Error: " << FilePath::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  dest << prefix << "file path:  " << *this << '\n'
       << prefix << "dirDelim:   " << dirDelim << '\n'
       << prefix << "extDelim:   " << extDelim << '\n'
    ;

  dest << '\n';

  return( dest  );
}

}; // namespace clue;

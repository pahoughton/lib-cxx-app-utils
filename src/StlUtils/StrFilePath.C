#include "FilePath.hh"

//
// File:        FilePath.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     06/15/95 07:48 
//
// Revision History:
//
// $Log$
// Revision 1.2  1995/11/05 14:44:33  houghton
// Ports and Version ID changes
//
//

#include "FilePath.hh"

#include <fnmatch.h>

#include <cstdio>
#include <cstring>

#if defined( CLUE_DEBUG )
#define  inline
#include <FilePath.ii>
#endif

CLUE_VERSION(
  FilePath,
  "$Id$" );

const char FilePath::DirDelim = CLUE_DIR_DELIM;

Str
FilePath::getName( void ) const
{
  Str name;
  
  size_t beg = rfind( dirDelim );
  size_t end = rfind( extDelim );

  if( beg == Str::npos )
    {
      if( end == Str::npos )
	{
	  return( *this );
	}
      else
	{
	  name = before( end );
	  return( name );
	}
    }
      
  if( end == Str::npos )
    name = after( beg + 1 );
  else
    name = substr( beg + 1, end  - (beg + 1) );

  return( name );  
}

bool
FilePath::match( const char * pattern )
{
  return( fnmatch( pattern, cstr(), 0 ) == 0 );
}

bool
FilePath::setPrefix( const char * prefix )
{
  if( prefix[0] == 0 )
    return( true );
  
  if( at((size_t)0) == dirDelim )
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
	  insert( 0, dirDelim );
	  insert( 0, prefix );
	}
    }
  return( true );
}

bool
FilePath::setPath( const char * path )
{
  size_t end = rfind( dirDelim );

  if( end == Str::npos )
    {
      if( path[ strlen( path ) - 1 ] == dirDelim )
	{
	  insert( 0, path );
	}
      else
	{
	  insert( 0, dirDelim );
	  insert( 0, path );
	}
    }
  else
    {
      if( path[ strlen( path ) - 1 ] == dirDelim )
	{
	  before( end + 1 ) = path;
	}
      else
	{
	  before( end ) = path;
	}
    }
  return( true );
}

bool
FilePath::changePath( const char * oldDirs, const char * newDirs )
{
  at( oldDirs ) = newDirs;
  return( true );
}

bool
FilePath::setFileName( const char * name )
{
  size_t beg = rfind( dirDelim );

  if( beg == Str::npos )
    {
      assign( name );
    }
  else
    {
      after( beg + 1 ) = name;
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
  size_t beg = rfind( dirDelim );
  size_t end = rfind( ext );

  if( beg == Str::npos )
    beg = 0;
  else
    beg++;
  
  if( end == Str::npos )
    end = size();
  
  at( beg, end - beg ) = name;

  return( true );
}

bool
FilePath::setName( const char * name, const char * ext )
{
  size_t beg = rfind( dirDelim );
  size_t end = find( ext);

  if( beg == Str::npos )
    beg = 0;
  else
    beg++;
  
  if( end == Str::npos )
    end = size();

  at( beg, end - beg ) = name;
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
  size_t beg = rfind( delim );

  if( beg == Str::npos )
    {
      append( extDelim );
      append( ext );
    }
  else
    {
      after( beg + 1 ) = ext;
    }
  return( true );
}

bool
FilePath::setExt( const char * oldExt, const char * newExt )
{
  size_t beg = rfind( oldExt );

  if( beg == Str::npos || (beg + strlen( oldExt )) != size() )
    return( false );

  at( beg, size() - beg ) = newExt;
  return( true );
}

bool
FilePath::setTempName( const char * prefix )
{
  Str fnPrefix;

  if( prefix != 0 )
    fnPrefix = prefix;
  else
    fnPrefix = getName().cstr();

  if( fnPrefix.size() )
    fnPrefix = fnPrefix.before(5);
  else
    fnPrefix = "tmp";

  
  assign( tempnam( (char *)getPath().cstr(), (char *)fnPrefix.cstr() ) );
  return( size() != 0 );
}

bool
FilePath::setTempName( const char * path, const char * prefix )
{
  Str fnPrefix = prefix;
  if( fnPrefix.size() > 5 )
    fnPrefix = fnPrefix.before( 5 );

  assign( tempnam( (char *)path, (char *)fnPrefix.cstr() ) );
  return( size() != 0 );
}

size_t
FilePath::getBinSize( void ) const
{
  return( Str::getBinSize() +
	  sizeof( dirDelim ) +
	  sizeof( extDelim ) );
}

BinStream & 
FilePath::write( BinStream & dest ) const
{
  Str::write( dest );
  dest.write( dirDelim );
  dest.write( extDelim );
  return( dest );
}

BinStream &
FilePath::read( BinStream & src )
{
  Str::read( src );
  src.read( dirDelim );
  src.read( extDelim );
  return( src );
}
	    
ostream & 
FilePath::write( ostream & dest ) const
{
  Str::write( dest );
  dest.write( &dirDelim, sizeof( dirDelim ) );
  dest.write( &extDelim, sizeof( extDelim ) );
  return( dest );
}

istream &
FilePath::read( istream & src )
{
  Str::read( src );
  src.read( &dirDelim, sizeof( dirDelim ) );
  src.read( &extDelim, sizeof( extDelim ) );
  return( src );
}
	    
// good - return TRUE if no detected errors
bool
FilePath::good( void ) const
{
  return( Str::good() && ! empty() );
}

// error - return a string describing the current state
const char *
FilePath::error( void ) const
{
  static Str errStr;
  errStr.reset();

  errStr << getClassName() << ':' ;

  if( good() )
    {
       errStr << " Ok";
    }
  else
    {
      if( ! Str::good() )
	{
	  errStr << ' ' << Str::error();
	}
      else
	{
	  errStr << " empty";
	}
    }

  return( errStr.cstr() );
}

// getClassName - return the name of this class
const char *
FilePath::getClassName( void ) const
{
  return( "FilePath" );
}

const char *
FilePath::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer, Str::getVersion( false ) ) );
}

ostream &
FilePath::dumpInfo( 
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << FilePath::getClassName() << ":\n"
	 << FilePath::getVersion() << '\n';
  
  if( ! FilePath::good() )
    dest << prefix << "Error: " << FilePath::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  dest << prefix << "path: ";
  FilePath::toStream( dest );
  dest << '\n';
  
  Str pre;
  pre << prefix << Str::getClassName() << "::";

  Str::dumpInfo( dest, pre, false );

  dest << prefix << "dirDelim:   " << dirDelim << '\n'
       << prefix << "extDelim:   " << extDelim << '\n'
    ;
  
  dest << '\n';
  
  return( dest  );
}  


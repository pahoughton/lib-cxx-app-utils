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
// Revision 1.1  1995/11/05 13:23:23  houghton
// Initaial implementation
//
//

#include "FilePath.hh"

#include <cstdio>

const char FilePath::version[] =
LIB_CLUE_VERSION
"$Id$";

#ifdef   CLUE_DEBUG
#define  inline
#include <FilePath.ii>
#endif


Str
FilePath::getName( void ) const
{
  Str name;
  
  size_t beg = fileName.rfind( dirDelim );
  size_t end = fileName.rfind( extDelim );

  if( beg == Str::npos )
    {
      if( end == Str::npos )
	{
	  return( fileName );
	}
      else
	{
	  name = fileName.before( end );
	  return( name );
	}
    }
      
  if( end == Str::npos )
    name = fileName.after( beg + 1 );
  else
    name = fileName.substr( beg + 1, end  - (beg + 1) );

  return( name );  
}

bool
FilePath::setPrefix( const char * prefix )
{
  if( fileName[0] == dirDelim )
    {
      if( prefix[ strlen( prefix ) - 1 ] == dirDelim )
	{
	  fileName.insert( 0, prefix, strlen( prefix ) - 2 );
	}
      else
	{
	  fileName.insert( 0, prefix );
	}
    }
  else
    {
      if( prefix[ strlen( prefix ) - 1 ] == dirDelim )
	{
	  fileName.insert( 0, prefix );
	}
      else
	{
	  fileName.insert( 0, dirDelim );
	  fileName.insert( 0, prefix );
	}
    }
  return( true );
}

bool
FilePath::setPath( const char * path )
{
  size_t end = fileName.rfind( dirDelim );

  if( end == Str::npos )
    {
      if( path[ strlen( path ) - 1 ] == dirDelim )
	{
	  fileName.insert( 0, path );
	}
      else
	{
	  fileName.insert( 0, dirDelim );
	  fileName.insert( 0, path );
	}
    }
  else
    {
      if( path[ strlen( path ) - 1 ] == dirDelim )
	{
	  fileName.before( end + 1 ) = path;
	}
      else
	{
	  fileName.before( end ) = path;
	}
    }
  return( true );
}

bool
FilePath::changePath( const char * oldDirs, const char * newDirs )
{
  fileName.at( oldDirs ) = newDirs;
  return( true );
}

bool
FilePath::setFileName( const char * name )
{
  size_t beg = fileName.rfind( dirDelim );

  if( beg == Str::npos )
    {
      fileName = name;
    }
  else
    {
      fileName.after( beg + 1 ) = name;
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
  size_t beg = fileName.rfind( dirDelim );
  size_t end = fileName.rfind( ext );

  if( beg == Str::npos )
    beg = 0;
  else
    beg++;
  
  if( end == Str::npos )
    end = fileName.size();
  
  fileName.at( beg, end - beg ) = name;

  return( true );
}

bool
FilePath::setName( const char * name, const char * ext )
{
  size_t beg = fileName.rfind( dirDelim );
  size_t end = fileName.find( ext);

  if( beg == Str::npos )
    beg = 0;
  else
    beg++;
  
  if( end == Str::npos )
    end = fileName.size();

  fileName.at( beg, end - beg ) = name;
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
  size_t beg = fileName.rfind( delim );

  if( beg == Str::npos )
    {
      fileName += extDelim;
      fileName += ext;
    }
  else
    {
      fileName.after( beg + 1 ) = ext;
    }
  return( true );
}

bool
FilePath::setExt( const char * oldExt, const char * newExt )
{
  size_t beg = fileName.rfind( oldExt );

  if( beg == Str::npos || (beg + strlen( oldExt )) != fileName.size() )
    return( false );

  fileName( beg, fileName.size() - beg ) = newExt;
  return( true );
}

bool
FilePath::setTempName( const char * prefix )
{
  Str fnPrefix = (prefix ? prefix : getName().cstr() );

  if( fnPrefix.size() )
    fnPrefix = fnPrefix.before(5);
  else
    fnPrefix = "tmp";

  
  fileName = tempnam( (char *)getPath().cstr(), (char *)fnPrefix.cstr() );
  return( fileName.size() != 0 );
}

bool
FilePath::setTempName( const char * path, const char * prefix )
{
  Str fnPrefix = prefix;
  if( fnPrefix.size() > 5 )
    fnPrefix = fnPrefix.before( 5 );

  fileName = tempnam( (char *)path, (char *)fnPrefix.cstr() );
  return( fileName.size() != 0 );
}

// getClassName - return the name of this class
const char *
FilePath::getClassName( void ) const
{
  return( "FilePath" );
}

// good - return TRUE if no detected errors
bool
FilePath::good( void ) const
{
  return( fileName.good() && ! fileName.empty() );
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
      if( ! fileName.good() )
	{
	  errStr << ' ' << fileName.error();
	}
      else
	{
	  errStr << " empty";
	}
    }

  return( errStr.cstr() );
}

ostream &
FilePath::toStream( ostream & dest ) const
{
  dest << fileName;
  return( dest );
}

ostream &
FilePath::dumpInfo( ostream & dest ) const
{
  dest << getClassName() << ":\n";

  dest << "    " << version << '\n';

  if( ! good() )
    dest << "    Error: " << error() << '\n';
  else
    dest << "    " << "Good!" << '\n';

  dest << "    " ;
  toStream( dest );
  dest << '\n';

  dest << getClassName() << "::" ;
  fileName.dumpInfo( dest );

  dest << '\n';

  return( dest  );
}  


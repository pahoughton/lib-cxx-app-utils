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
// Revision 4.1  1997/09/17 15:12:25  houghton
// Changed to Version 4
//
// Revision 3.8  1997/09/17 11:08:21  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.7  1997/08/08 12:37:29  houghton
// Added expand() method.
//
// Revision 3.6  1997/07/18 19:13:04  houghton
// Port(Sun5): changed all locale variables named beg and end to
//     eliminate compiler warnings.
//
// Revision 3.5  1997/06/09 12:01:18  houghton
// Changed 'match' to be a const method.
//
// Revision 3.4  1997/03/03 18:58:47  houghton
// Changed arg to write calls to const char * (AIX workaround)
// Changed arg to write class to char * (AIX workaround)
//
// Revision 3.3  1997/03/03 14:35:53  houghton
// Changed base class from string back to Str (Massive improvement of
//     functionallity )
//
// Revision 3.2  1996/11/20 12:06:10  houghton
// Changed: Major rework to change base class from Str to string.
//
// Revision 3.1  1996/11/14 01:23:41  houghton
// Changed to Release 3
//
// Revision 2.3  1996/11/04 13:35:19  houghton
// Bug-Fix: changeDirs - if oldDirs not found in path, return false.
//
// Revision 2.2  1995/12/04 11:17:22  houghton
// Bug Fix - Can now compile with out '-DSTLUTILS_DEBUG'.
//
// Revision 2.1  1995/11/10  12:40:34  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  15:28:33  houghton
// Revised
//
//

#include "FilePath.hh"

#if defined( UNIX )
#include <User.hh>
#endif

#include <RegexScan.hh>

#include <fnmatch.h>

#include <cstdio>
#include <cstring>

#if defined( STLUTILS_DEBUG )
#include <FilePath.ii>
#endif

STLUTILS_VERSION(
  FilePath,
  "$Id$" );

const char FilePath::DirDelim = STLUTILS_DIR_DELIM;

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
  
  Str::size_type pos = find( '$' );

  if( pos != npos )
    {
      // expand env vars
      static const RegexScan  EnvVarChars( "[A-Za-z0-9_]+" );
      Str   eVar;
      
      Str::size_type endpos;
      for( ; pos != Str::npos ; pos = find( '$', endpos  ) )
	{
	  if( at( pos + 1 ) == '{' )
	    {
	      endpos = find( '}', pos + 2 );
	      if( endpos == npos )
		return( false );

	      eVar.assign( *this, pos + 2, endpos - pos - 2 );
	    }
	  else
	    {
	      if( EnvVarChars.match( c_str(), pos + 1) )
		{		  
		  endpos = pos + EnvVarChars.matchLength();
		}
	      else
		{
		  // not a valid env var, try again staring with
		  // the next char
		  endpos = pos + 1;
		  continue;
		}
	      eVar.assign( *this, pos + 1, endpos - pos );
	      
	    }
	  
	  const char * eValue = getenv( eVar );
	  
	  if( eValue && strlen( eValue ) )
	    {
	      long oldSize = size();
	      replace( pos, endpos + 1 - pos, eValue );
	      long newSize = size();
	      endpos = pos + (endpos + 1 - pos ) + newSize - oldSize;
	    }
	  else
	    {
	      remove( pos, endpos + 1 - pos );
	      endpos = pos;
	    }
	  
	  changed = true;
	}
    }

#if defined( UNIX )
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
	  Str userName( *this, 1, find( '/' ) - 1 );
	  User user( userName.c_str() );
	  if( user.good() && user.getHome() && strlen( user.getHome() ) )
	    {
	      replace( 0, userName.size() + 1, user.getHome() );
	      changed = true;
	    }
	}
    }
#endif // def UNIX
  
  return( changed );
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

  assign( tempnam( (char *)path, (char *)fnPrefix.c_str() ) );
  return( size() != 0 );
}

ostream &
FilePath::toStream( ostream & dest ) const
{
  return( Str::toStream( dest ) );
}

size_t
FilePath::getBinSize( void ) const
{
  return( sizeof( STLUTILS_U32 ) +
	  size() +
	  sizeof( dirDelim ) +
	  sizeof( extDelim ) );
}

	    
ostream & 
FilePath::write( ostream & dest ) const
{
  STLUTILS_U32  len = size();
  dest.write( (const char *)&len, sizeof( len ) );
  dest.write( c_str(), size() );
  dest.write( &dirDelim, sizeof( dirDelim ) );
  dest.write( &extDelim, sizeof( extDelim ) );
  return( dest );
}

istream &
FilePath::read( istream & src )
{
  STLUTILS_U32  len = 0;
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
	    
// good - return TRUE if no detected errors
bool
FilePath::good( void ) const
{
  return( true );
}

// error - return a Str describing the current state
const char *
FilePath::error( void ) const
{
  static Str errStr;
  
  errStr = getClassName();

  if( good() )
    {
       errStr += ": ok.";
    }
  else
    {
      size_type eSize = errStr.size();

      if( eSize == errStr.size() )
	errStr += ": unknown error.";
    }

  return( errStr.c_str() );
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
  return( version.getVer( withPrjVer ) );
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

  dest << prefix << "file path:  " << *this << '\n'
       << prefix << "dirDelim:   " << dirDelim << '\n'
       << prefix << "extDelim:   " << extDelim << '\n'
    ;
  
  dest << '\n';
  
  return( dest  );
}  


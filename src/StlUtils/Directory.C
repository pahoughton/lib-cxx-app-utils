//
// File:        Directory.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld1.wiltel.com)
// Created:     09/19/95 08:18
//
// Revision History:
//
// $Log$
// Revision 1.3  1995/11/05 13:48:11  houghton
// New implementation
//
//

#include "Directory.hh"
#include "User.hh"
#include "UserGroup.hh"
#include "Compare.hh"
#include <unistd.h>
#include <dirent.h>
#include <cstring>

#if defined( CLUE_DEBUG )
#define inline
#include <Directory.ii>
#endif

const char Directory::version[] =
LIB_CLUE_VERSION
"$Id$";


class DirSortName : public SortCompareBase< FileStat >
{
public:
  int operator () ( const FileStat & one, const FileStat & two ) const;
};

int
DirSortName::operator () ( const FileStat & one, const FileStat & two ) const
{
  return( ::compare( (const char *)one.getName(),
		     (const char *)two.getName() ) );
}

class DirSortExt : public SortCompareBase< FileStat >
{
public:
  int operator () ( const FileStat & one, const FileStat & two ) const;
};

int
DirSortExt::operator () ( const FileStat & one, const FileStat & two ) const
{
  return( ::compare( one.getName().getExt(), two.getName().getExt() ) );
}

class DirSortSize : public SortCompareBase< FileStat >
{
public:
  int operator () ( const FileStat & one, const FileStat & two ) const;
};

int
DirSortSize::operator () ( const FileStat & one, const FileStat & two ) const
{
  return( ::compare( one.getSize(), two.getSize() ) );
}

class DirSortTime : public SortCompareBase< FileStat >
{
public:
  int operator () ( const FileStat & one, const FileStat & two ) const;
};

int
DirSortTime::operator () ( const FileStat & one, const FileStat & two ) const
{
  return( ::compare( one.getModificationTime(), two.getModificationTime() ) );
}

class DirSortUser : public SortCompareBase< FileStat >
{
public:
  int operator () ( const FileStat & one, const FileStat & two ) const;
};

int
DirSortUser::operator () ( const FileStat & one, const FileStat & two ) const
{
  User uOne( one.getUID() );
  User uTwo( two.getUID() );
  
  return( uOne.compare( uTwo ) );
}

class DirSortUserGroup : public SortCompareBase< FileStat >
{
public:
  int operator () ( const FileStat & one, const FileStat & two ) const;
};

int
DirSortUserGroup::operator () ( const FileStat & one, const FileStat & two ) const
{
  UserGroup gOne( one.getGID() );
  UserGroup gTwo( two.getGID() );
  
  return( one.compare( two ) );
}


const Directory::DirOrder SortName( DirSortName() );
const Directory::DirOrder SortExt( DirSortExt() );
const Directory::DirOrder SortSize( DirSortSize() );
const Directory::DirOrder SortTime( DirSortTime() );
const Directory::DirOrder SortUser( DirSortUser() );
const Directory::DirOrder SortUserGroup( DirSortUserGroup() );

Directory::~DirField( void )
{
}

Directory::
  
  
Directory::~Directory( void )
{
}

bool
Directory::set( const char * path, Options options )
{
  Str	    dirName( path );
  FilePath  dirPath;
  FilePath  matchPath;
  
  size_t wild = dirName.find_first_of( "*?" );

  size_t pathEnd = dirName.rfind( FilePath::DirDelim, wild );

  if( pathEnd == Str::npos )
    {
      matchPath = dirName;
      dirName = ".";
    }
  else
    {
      matchPath = dirName.after( pathEnd );
      dirPath = dirName.before( pathEnd );
      
      dirName.remove( pathEnd );
    }

  DIR * dir = opendir( dirName );

  if( ! dir )
    return( false );
  else
    return( readDir( dir, dirPath, matchPath, options ) );
}

bool
Directory::readDir(
  DIR *		    dir,
  const FilePath &  dirPath,
  const FilePath &  matchPath,
  Options	    options
  )
{
  Str match;
  match = matchPath.getFullName().at( (size_t)0, matchPath.getFullName().find( FilePath::DirDelim ) );

  for( struct dirent * dEnt = readdir( dir );
       dEnt != 0;
       dEnt = readdir( dir ) )
    {
      if( ! all && dEnt->d_name[0] == "." )
	continue;
      
      FilePath name( dEnt->d_name );
      
      if( match.size() && ! name.match( match ) )
	continue;

      name.setPrefix( dirPath );
      
      FileStat fs( name );

      list.push_back( fs );

      
      if( fs.good() && fs.isDir() &&
	  strcmp( dEnt->d_name, "." ) && strcmp( dEnt->d_name, ".." ) &&
	  (recurs || match.size() < matchPath.getFullName().size() ) )
	{
	  FilePath subDirPath;
	  FilePath subMatchPath;

	  subDirPath = name;
	  subMatchPath = matchPath.getFullName().after( match.size() );

	  DIR * subDir = opendir( subDirPath );

	  if( ! subDir ||
	      ! readDir( subDir, subDirPath, subMatchPath, recurs ) )
	    // FIXME - strange error;
	    break;
	}
    }

  return( true );
}
	    
      

  
bool
Directory::set(
  const char *			path,
  const SortOrder< FileStat > & order,
  bool				recurs
  )
{
  return( set( path, recurs ) );
}
  
// getClassName - return the name of this class
const char *
Directory::getClassName( void ) const
{
  return( "Directory" );
}

// good - return TRUE if no detected errors
bool
Directory::good( void ) const
{
  return( true );
}

// error - return a string describing the current state
const char *
Directory::error( void ) const
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




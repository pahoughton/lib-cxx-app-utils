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
// Revision 1.2  1995/11/05 13:22:38  houghton
// New Implementation
//
//

#include "Directory.hh"
#include "Compare.hh"

#include <unistd.h>
#include <dirent.h>

#ifdef  CLUE_DEBUG
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


const Directory::DirOrder SortName( DirSortName() );
const Directory::DirOrder SortExt( DirSortExt() );
const Directory::DirOrder SortSize( DirSortSize() );
const Directory::DirOrder SortTime( DirSortTime() );

Directory::~Directory( void )
{
}

bool
Directory::set( const char * path, bool recurs = false )
{
  Str dirName( path );
  
  size_t wild = dirName.find_first_of( "*?" );

  size_t pathEnd = dirName.rfind( DIR_DELIM, wild );

  if( pathEnd == Str::npos )
    dirName = ".";
  else
    dirName.remove( pathEnd );

  DIR * dir = opendir( dirName );

  if( ! dir )
    return( false );

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




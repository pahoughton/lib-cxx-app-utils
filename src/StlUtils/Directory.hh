#ifndef _Directory_hh_
#define _Directory_hh_
//
// File:        Directory.hh
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     12/22/94 16:43
//
// Revision History:
//
// 
// $Log$
// Revision 1.1  1995/02/13 16:08:39  houghton
// New Style Avl an memory management. Many New Classes
//
//

#include <Common.h>

#include <unistd.h>
#include <dirent.h>

#include <StringList.hh>
#include <FileStat.hh>
#include <Stack.hh>
#include <Array.hh>

class Directory
{

public:

  enum SortOrder
  {
    SORT_NONE 	= 0,
    SORT_TYPE	= 0x01,
    SORT_NAME	= 0x02,
    SORT_MTIME	= 0x04,
    SORT_SIZE	= 0x08,
    SORT_OWNER	= 0x10,
    SORT_GROUP	= 0x20
  };
    
  Directory( const char * path, Bool recursive = NO );
  Directory( const char * path, SortOrder order = SORT_NONE, Bool recursive = NO );
  ~Directory();

  
  void 	    	    addExclude( const char * name );
  void	    	    addExcludeDir( const char * name );
  void	    	    resetExclude( void );
  void	    	    resetExcludeDir( void );
  SortOrder 	    setSortOrder( SortOrder s1,
				  SortOrder s2 = SORT_NONE,
				  SortOrder s3 = SORT_NONE,
				  SortOrder s4 = SORT_NONE,
				  SortOrder s5 = SORT_NONE,
				  SortOrder s6 = SORT_NONE,
				  SortOrder s7 = SORT_NONE,
				  SortOrder s8 = SORT_NONE,
				  SortOrder s9 = SORT_NONE,
				  SortOrder s10 = SORT_NONE );
    
  const char * 	    next( char * buf = 0 );

  const char * 	    getPath( char * buf = 0 );
  const char * 	    getFileName( char * buf = 0 ) const;  
  const char * 	    getFullName( char * buf = 0 ) const;
  const FileStat &  getStats( void ) const;

  unsigned long	    getDepth( void ) const;
  
  
  struct DirInfo
  {
    char *     	    	    	path;
    size_t  	    	    	pathLen;
    DIR *      	    	    	dir;
    long   	    	    	file;
    Array<FileStat> 	    	stats;
  };
  
protected:

private:

  static int compareDir( const FileStat ** one,
			 const FileStat ** two );
  
  void 	initialize( const char * path );

  void	readDirectory( void );
  
  Bool 	isExcludeDir();
  Bool	isExclude();
  Bool	match();

  Directory( const Directory & copyFrom );
  Directory & operator=( const Directory & assignFrom );

  SortOrder 	    sortBy[32];
  Stack<DirInfo>    dirs;

  Bool	    	    recurs;
  
  char *    	    basePath;
  char *    	    matchPattern;
  StringList   	    excludeList;
  StringList	    excludeDirList;
  
};


//
// Inline methods
//

inline
const char *
Directory::getPath( char * buf ) 
{
  if( buf != 0 )
    {
      strcpy( buf, dirs().path );
      return( buf );
    }
  else
    {
      return( dirs().path );
    }
}

inline
const char *
Directory::getFileName( char * buf ) const
{
  if( buf != 0 )
    {
      strcpy( buf, dirs().stats[ dirs().file ].getName() + dirs().pathLen + 1 );
      return( buf );
    }
  else
    {
      return( dirs().stats[ dirs().file ].getName() + dirs().pathLen + 1  );
    }
}

inline
const char *
Directory::getFullName( char * buf ) const
{
  if( buf != 0 )
    {
      strcpy( buf, dirs().stats[ dirs().file ].getName() );
      return( buf );
    }
  else
    {
      return( dirs().stats[ dirs().file ].getName() );
    }
}

inline
const FileStat &
Directory::getStats( void ) const
{
  return( dirs().stats[ dirs().file ] );
}

  
inline
void
Directory::addExclude( const char * name )
{
  excludeList.add( name );
}

inline
void
Directory::addExcludeDir( const char * name )
{
  excludeDirList.add( name );
}

inline
void
Directory::resetExclude( void )
{
  excludeList.clear();
}

inline
void
Directory::resetExcludeDir( void )
{
  excludeDirList.clear();
}

inline
unsigned long
Directory::getDepth( void ) const
{
  return( dirs.getSize() );
}




#endif // ! def _Directory_hh_ 
//
//              This software is the sole property of
// 
//                 The Williams Companies, Inc.
//                        1 Williams Center
//                          P.O. Box 2400
//        Copyright (c) 1994 by The Williams Companies, Inc.
// 
//                      All Rights Reserved.  
// 
//

//
// File:        Directory.C
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     12/22/94 16:47 
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/02/13 16:08:39  houghton
// New Style Avl an memory management. Many New Classes
//
//
static const char * RcsId =
"$Id$";

#include "Directory.hh"
#include <stdio.h>
#include <fnmatch.h>

#define SPECIAL "*?[]\\"

const char * DefaultExclude[] 	= {".","..",0};
const char * DefaultDirExclude[] = {".","..",0};

Directory::Directory(
  const char * 	path,
  Bool 	    	recursive
  ) : excludeList( DefaultExclude ), excludeDirList( DefaultDirExclude )
{
  recurs = recursive;
  sortBy[0] = SORT_NONE;
  initialize( path );
}

Directory::Directory(
  const char * 	path,
  SortOrder 	order,
  Bool	    	recursive
  ) : excludeList( DefaultExclude ), excludeDirList( DefaultDirExclude )
{
  recurs = recursive;

  int s = 0;

  if( order & SORT_TYPE ) { sortBy[s] = SORT_TYPE; s++; }
  if( order & SORT_NAME ) { sortBy[s] = SORT_NAME; s++; }
  if( order & SORT_MTIME ) { sortBy[s] = SORT_MTIME; s++; }
  if( order & SORT_SIZE ) { sortBy[s] = SORT_SIZE; s++; }
  if( order & SORT_OWNER ) { sortBy[s] = SORT_OWNER; s++; }
  if( order & SORT_GROUP ) { sortBy[s] = SORT_GROUP; s++; }

  sortBy[s] = SORT_NONE;

  initialize( path );
}


Directory::~Directory( void )
{
  while( dirs.good() )
    {
      free( dirs().path );
      if( dirs().dir != 0 )
	{
	  closedir( dirs().dir );
	}
      dirs.pop();
    }
}

const char *
Directory::next( char * buf )
{
  while( dirs.good() )
    {

      if( recurs && dirs().file >= 0 &&
	  dirs().stats[ dirs().file ].isDir() && ! isExcludeDir() )
			    
	{
	  DirInfo  dirInfo;

	  dirInfo.path	    = strdup( dirs().stats[ dirs().file ].getName() );
	  dirInfo.pathLen   = strlen( dirs().stats[ dirs().file ].getName() );
	  dirInfo.dir	    = 0;
	  dirInfo.file	    = -1;

	  dirs.push( dirInfo );
	  readDirectory();
	}

      if( dirs().file + 1 >= dirs().stats.getCount() )
	{
	  free( dirs().path );
	  if( dirs().dir != 0 )
	    {
	      closedir( dirs().dir );
	    }
	  dirs.pop();
	  continue;
	}

      dirs().file++;
      
      if( ! isExclude() &&
	  ! isExcludeDir() &&
	  match() )
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
    }
  return( 0 );
}

void
Directory::initialize( const char * path )
{
  FileStat	stats;
  
  if( strlen( path ) )
    {
      char * dirPath = strdup( path );

      stats( dirPath );
      
      if( ! stats.good() || ! stats.isDir() )
	{
	  char * findSpecial = strpbrk( dirPath, SPECIAL );
	  
	  if( findSpecial != 0 )
	    {
	      char sp = *findSpecial;
	      *findSpecial = 0;

	      char * dirNameEnd = strrchr( dirPath,'/' );
	      *findSpecial = sp;
	  
	      if( dirNameEnd != 0 )
		{
		  *dirNameEnd = 0;
		  basePath = strdup( dirPath );
		  matchPattern = strdup( dirNameEnd + 1 );
		}
	      else
		{
		  basePath = strdup( "." );
		  matchPattern = strdup( dirPath );
		}	      
	    }
	  else
	    {
	      char * dirNameEnd = strrchr( dirPath, '/' );

	      if( dirNameEnd != 0 )
		{
		  *dirNameEnd = 0;
		  basePath = strdup( dirPath );
		  matchPattern = strdup( dirNameEnd + 1 );
		}
	      else
		{
		  basePath = strdup( "." );
		  matchPattern = strdup( dirPath );
		}
	    }
	}
      else
	{
	  basePath = strdup( dirPath );
	  matchPattern = 0;
	}
      
      free( dirPath );
    }
  else
    {
      basePath = strdup(".");
      matchPattern = 0;
    }

  stats( basePath );
  
  if( stats.good() && stats.isDir() )
    {
      DirInfo  dirInfo;
      
      dirInfo.path  	= basePath;
      dirInfo.pathLen 	= strlen( basePath );
      dirInfo.dir   	= 0;      
      dirInfo.file  	= -1;
      
      dirs.push(dirInfo);      

      readDirectory();
    }

}

static Directory * currentDirectory = 0;

int
Directory::compareDir(
  const FileStat ** one,
  const FileStat ** two
  )
{
  int diff = 0;
  
  for( int s = 0; currentDirectory->sortBy[s] != SORT_NONE; s++ )
    {
      switch( currentDirectory->sortBy[s] )
	{
	case SORT_NONE:
	  return( 0 );

	case SORT_TYPE:

	  if( (*one)->isDir() && ( ! (*two)->isDir() ) ) 
	    {
	      return( 1 );
	    }
	  else
	    {
	      if( (*two)->isDir() && ( ! (*one)->isDir() ) )
		{
		  return( -1 );
		}
	    }
	  break;

	case SORT_NAME:

	  diff = strcmp( (*one)->getName(), (*two)->getName() );

	  if( diff != 0 )
	    {
	      return( diff );
	    }
	  break;

	case SORT_MTIME:

	  diff = (*one)->getMtime() - (*two)->getMtime();

	  if( diff != 0 )
	    {
	      return( diff );
	    }
	  break;

	case SORT_SIZE:

	  if( (*one)->getSize() > (*two)->getSize() )
	    {
	      return( 1 );
	    }

	  if( (*one)->getSize() < (*two)->getSize() )
	    {
	      return( -1 );
	    }

	  break;

	case SORT_OWNER:

	  diff = strcmp( (*one)->getUserName(), (*two)->getUserName() );

	  if( diff != 0 )
	    {
	      return( diff );
	    }
	  break;

	case SORT_GROUP:

	  diff = strcmp( (*one)->getGroupName(), (*two)->getGroupName() );

	  if( diff != 0 )
	    {
	      return( diff );
	    }

	  break;

	default:
	  break;
	}
    }

  return( 0 );
}


void
Directory::readDirectory( void )
{
  dirs().file = -1;
  dirs().dir = opendir( dirs().path );

  if( dirs().dir != 0 )
    {
      for( struct dirent * d = readdir( dirs().dir );
	  d != 0;
	  d = readdir( dirs().dir ) )
	{
	  char fullName[1024];
	  
	  sprintf( fullName,"%s/%s",dirs().path, d->d_name );

	  FileStat  fs( fullName);
	  dirs().stats.add( fs );
	}
    }

  if( sortBy[0] != SORT_NONE )
    {
      currentDirectory = this;
      dirs().stats.sort( compareDir );
      currentDirectory = 0;
    }
}

  

Bool
Directory::isExcludeDir( void )
{
  return( dirs().stats[ dirs().file ].isDir() &&
	  excludeDirList.isIn( dirs().stats[ dirs().file ].getName() +
			       dirs().pathLen + 1 ) );
}
  
Bool
Directory::isExclude( void )
{
  for( int e = 0; excludeList[e] != 0; e++ )
    {
      if( fnmatch( excludeList[e],
		   dirs().stats[dirs().file].getName() + dirs().pathLen + 1 ,
		   0 ) == 0 )
	{
	  return( TRUE );
	}
    }
  return( FALSE );
}

Directory::SortOrder
Directory::setSortOrder(
  SortOrder s1,
  SortOrder s2,
  SortOrder s3,
  SortOrder s4,
  SortOrder s5,
  SortOrder s6,
  SortOrder s7,
  SortOrder s8,
  SortOrder s9,
  SortOrder s10
  )
{
  SortOrder old = SORT_NONE;

  for( int i = 0; sortBy[0] != SORT_NONE; i++ )
    {
      old = (SortOrder)(old | sortBy[i]);
    }
  
  sortBy[0] = s1;
  sortBy[1] = s2;
  sortBy[2] = s3;
  sortBy[3] = s4;
  sortBy[4] = s5;
  sortBy[5] = s6;
  sortBy[6] = s7;
  sortBy[7] = s8;
  sortBy[8] = s9;
  sortBy[9] = s10;
  sortBy[10] = SORT_NONE;

  return( old );
}


  
  

int
Directory::match( void )
{
  if( matchPattern )
    {
      if( strchr( matchPattern, '/' ) )
	{
	  return( ! fnmatch( matchPattern,
			     dirs().stats[ dirs().file].getName() +
			       strlen( basePath ) + 1,
			     0 ) );
	}
      else
	{
	  return( ! fnmatch( matchPattern,
			     dirs().stats[ dirs().file].getName() +
			     strlen( basePath ) + 1 ,
			     0 ) );
	}
    }
  else
    {
      return( TRUE );
    }
}


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

#ifndef _FileStat_hh_
#define _FileStat_hh_
//
// File:        FileStat.hh
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     12/22/94 17:16
//
// Revision History:
//
// 
// $Log$
// Revision 1.1  1995/02/13 16:08:41  houghton
// New Style Avl an memory management. Many New Classes
// 
//

#if defined( AIX )
#define _ALL_SOURCE
#include <sys/mode.h>
#endif
 
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream.h>

#include <Clue.hh>

#define FS_NAME_SIZE 1024

class FileStat
{

public:

  FileStat();
  FileStat( const char * fileName, Bool linkStat = FALSE );
  FileStat( int fd );
  FileStat( const FileStat & copyFrom );
  FileStat & operator=( const FileStat & assignFrom );
  
  inline FileStat & lstat( const char * fileName );
  inline FileStat & stat( const char * fileName );
  inline FileStat & operator()( const char * fileName );

  inline FileStat & stat( int fd, Bool keepName = FALSE );
  inline FileStat & operator()( int fd, Bool keepName = FALSE );

  dev_t     	    getDevice( void ) const;
  ino_t		    getInode( void ) const;
  umode_t   	    getMode( void ) const;
  nlink_t   	    getHardLinks( void ) const;
  umode_t   	    getType( void ) const;
  
  uid_t	    	    getUID( void ) const;
  gid_t	    	    getGID( void ) const;

  dev_t	    	    getRdev( void ) const;
  off_t	    	    getSize( void ) const;
  
  time_t    	    getAtime( void ) const;
  time_t    	    getMtime( void ) const;
  time_t    	    getCtime( void ) const;

  Bool	    	    isReg( void ) const;
  Bool	    	    isDir( void ) const;
  Bool	    	    isLink( void ) const;

  Bool	    	    isSetUID( void ) const;
  Bool	    	    isSetGID( void ) const;
  
  Bool	    	    isBlock( void ) const;
  Bool	    	    isChar( void ) const;
  Bool	    	    isFifo( void ) const;
  Bool	    	    isSocket( void ) const;

  Bool	    	    canRead( void ) const;
  Bool	    	    canWrite( void ) const;
  Bool	    	    canExec( void ) const;

  const char * 	    getName( char * buf = 0 ) const;
  const char *	    getModeString( char * buf = 0 ) const;
  const char *	    getUserName( char * buf = 0 ) const;
  const char * 	    getGroupName( char * buf = 0 ) const;
  
  Bool	    	    good() const;
  const char * 	    error() const;

  int	    	    getErrno( void ) const;
  
  friend ostream & operator<<( ostream & dest, const FileStat & fs );
  
protected:

private:

  void 	setStrings( );

  
  struct stat	st;
  

  int	fd;
  
  char  name[ FS_NAME_SIZE ];
  char 	user[256];
  char 	group[256];
  char  mode[256];

  int	osErrno;
  
};


//
// Inline methods
//

inline
FileStat::FileStat( void )
{
  memset( &st, 0, sizeof( st ) );
  fd	    = -1;
  name[0]   = 0;
  user[0]   = 0;
  group[0]  = 0;
  mode[0]   = 0;

  osErrno = ENOENT;
}

inline
FileStat::FileStat( const char * fileName, Bool linkStat )
{
  fd	    = -1;
  name[0]   = 0;
  user[0]   = 0;
  group[0]  = 0;
  mode[0]   = 0;

  if( linkStat )
    {
      lstat( fileName );
    }
  else
    {	
      stat( fileName );
    }
}

inline
FileStat::FileStat( int fd )
{
  fd	    = -1;
  name[0]   = 0;
  user[0]   = 0;
  group[0]  = 0;
  mode[0]   = 0;
  stat( fd );
}

inline
FileStat::FileStat( const FileStat & copyFrom )
{
  st = copyFrom.st;
  strcpy( name, copyFrom.name );
  strcpy( user, copyFrom.user );
  strcpy( group, copyFrom.group );
  strcpy( mode, copyFrom.mode );
}

inline
FileStat &
FileStat::operator=( const FileStat & assignFrom )
{
  st = assignFrom.st;
  strcpy( name, assignFrom.name );
  strcpy( user, assignFrom.user );
  strcpy( group, assignFrom.group );
  strcpy( mode, assignFrom.mode );

  return( *this );
}

inline
FileStat &
FileStat::lstat( const char * fileName )
{
  name[0] = 0;
  user[0] = 0;
  group[0] = 0;
  mode[0] = 0;

  osErrno = 0;
  
  if( (strlen( fileName ) + 1 ) <= sizeof( name ) )
    {
      strcpy( name, fileName );
    
      if( ! ::stat( fileName, &st ) )
	{
	  setStrings();
	}
      else
	{
	  memset( &st, 0, sizeof( st ) );
	  osErrno = errno;
	}
    }
  else
    {
      memset( &st, 0, sizeof( st ) );
      osErrno = ENAMETOOLONG;
    }
  
  return( *this );
}

inline
FileStat &
FileStat::stat( const char * fileName )
{
  name[0] = 0;
  user[0] = 0;
  group[0] = 0;
  mode[0] = 0;

  osErrno = 0;
  
  if( (strlen( fileName ) + 1 ) <= sizeof( name ) )
    {
      strcpy( name, fileName );
    
      if( ! ::stat( fileName, &st ) )
	{
	  setStrings();
	}
      else
	{
	  memset( &st, 0, sizeof( st ) );
	  osErrno = errno;
	}
    }
  else
    {
      memset( &st, 0, sizeof( st ) );
      osErrno = ENAMETOOLONG;
    }
  
  return( *this );
}


inline
FileStat &
FileStat::operator() ( const char * fileName )
{
  return( stat( fileName ) );
}


inline
FileStat &
FileStat::stat( int fd, Bool keepName )
{
  if( ! keepName )
    {
      name[0] = 0;
    }
  
  user[0] = 0;
  group[0] = 0;
  mode[0] = 0;

  osErrno = 0;
  
  if( ! fstat( fd, &st ) )
    {
      setStrings();
    }
  else
    {
      memset( &st, 0, sizeof( st ) );
      osErrno = errno;
    }

  return( *this );
}

inline
FileStat &
FileStat::operator() ( int fd, Bool keepName )
{
  return( stat( fd, keepName ) );
}

inline
dev_t
FileStat::getDevice( void ) const
{
  return( st.st_dev );
}

inline
ino_t
FileStat::getInode( void ) const
{
  return( st.st_ino );
}

inline
umode_t
FileStat::getMode( void ) const
{
  return( st.st_mode );
}

inline
nlink_t
FileStat::getHardLinks( void ) const
{
  return( st.st_nlink );
}

inline
uid_t
FileStat::getUID( void ) const
{
  return( st.st_uid );
}

inline
gid_t
FileStat::getGID( void ) const
{
  return( st.st_gid );
}

inline
dev_t
FileStat::getRdev( void ) const
{
  return( st.st_rdev );
}

inline
off_t
FileStat::getSize( void ) const
{
  return( st.st_size );
}

inline
time_t
FileStat::getAtime( void ) const
{
  return( st.st_atime );
}

inline
time_t
FileStat::getMtime( void ) const
{
  return( st.st_mtime );
}

inline
time_t
FileStat::getCtime( void ) const
{
  return( st.st_ctime );
}

inline
Bool
FileStat::isReg( void ) const
{
  return( S_ISREG( getMode() ) );
}

inline
Bool
FileStat::isDir( void ) const
{
  return( S_ISDIR( getMode() ) );
}

inline
Bool
FileStat::isLink( void ) const
{
  return( S_ISLNK( getMode() ) );
}

inline
Bool
FileStat::isSetUID( void ) const
{
  return( getMode() & S_ISUID );
}

inline
Bool
FileStat::isSetGID( void ) const
{
  return( getMode() & S_ISGID );
}

inline
Bool
FileStat::isBlock( void ) const
{
  return( S_ISBLK( getMode() ) );
}

inline
Bool
FileStat::isChar( void ) const
{
  return( S_ISCHR( getMode() ) );
}

inline
Bool
FileStat::isFifo( void ) const
{
  return( S_ISFIFO( getMode() ) );
}


inline
Bool
FileStat::isSocket( void ) const
{
  return( S_ISSOCK( getMode() ) );
}


inline
const char *
FileStat::getName( char * buf ) const
{
  if( buf != 0 )
    {
      strcpy( buf, name );
      return( buf );
    }
  else
    {
      return( name );
    }
}


inline
const char *
FileStat::getModeString( char * buf ) const
{
  if( buf != 0 )
    {
      strcpy( buf, mode );
      return( buf );
    }
  else
    {
      return( mode );
    }
}

    
inline
const char *
FileStat::getUserName( char * buf ) const
{
  if( buf != 0 )
    {
      strcpy( buf, user );
      return( buf );
    }
  else
    {
      return( user );
    }
}

inline
const char *
FileStat::getGroupName( char * buf ) const
{
  if( buf != 0 )
    {
      strcpy( buf, group );
      return( buf );
    }
  else
    {
      return( group );
    }
}

  
inline
Bool
FileStat::good( void ) const
{
  return( osErrno == 0 );
}

inline
int
FileStat::getErrno( void ) const
{
  return( osErrno );
}
	

#endif // ! def _FileStat_hh_ 
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

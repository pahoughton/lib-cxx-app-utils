//
// File:        LockFile.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/14/95 09:00 
//
// Revision History:
//
// $Log$
// Revision 6.1  2003/08/09 11:22:45  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:21  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:23  houghton
// Changed to Version 4
//
// Revision 3.1  1996/11/14 01:25:24  houghton
// Changed to Release 3
//
// Revision 2.1  1995/11/10 12:47:12  houghton
// Change to Version 2
//
// Revision 1.1  1995/11/05  12:22:38  houghton
// Initial LockFile
//
//
static const char * RcsId =
"$Id$";

#include "LockFile.hh"

#include <unistd.h>
#include <fcntl.h>

#include <cerrno>

LockFile::LockFile(
  const char * 	    fileName,
  ios::open_mode    mode,
  int	    	    perm
  )
  : BinaryFile( fileName, mode, perm )
{
  ;
}


bool
LockFile::unlock( streamoff offset, ios::seek_dir dir, size_t amount )
{
  struct flock lock;

  lock.l_type   = F_UNLCK;
  lock.l_whence	= whence( dir );
  lock.l_start  = offset;
  lock.l_len 	= amount;

  if( fcntl( fd, F_SETLK, &lock ) == -1 )
    {
      state = ios::badbit;
      osError = errno;
      return( false );
    }
  return( true );
}


const char *
LockFile::getClassName( void ) const
{
  return( "LockFile" );
}


iLockFile::iLockFile( const char * fileName )
  : LockFile( fileName, ios::in )
{
  ;
}


iLockFile &
iLockFile::lread( void * dest, size_t amount )
{
  bytesRead = 0;
  
  if( ! good() )
    return( *this );
  
  if( ! rlock( 0, ios::cur, amount ) )
    return( *this );
  
  read( dest, amount );
  
  unlock( amount * -1, ios::cur, amount );
  
  return( *this );
}

  
iLockFile &
iLockFile::lread( streampos pos, void * dest, size_t amount )
{
  bytesRead = 0;
  
  if( ! good() )
    return( *this );
  
  if( ! rlock( pos, ios::beg, amount ) )
    return( *this );
  
  read( pos, dest, amount );
  
  unlock( pos, ios::beg, amount );
  
  return( *this );
}

iLockFile &
iLockFile::lread(
  streamoff     offset,
  ios::seek_dir dir,
  void * 	dest,
  size_t	amount
  )
{
  bytesRead = 0;
  
  if( ! good() )
    return( *this );
  
  if( ! rlock( offset, dir, amount ) )
    return( *this );
  
  read( offset, dir, dest, amount );
  
  unlock( offset, dir, amount );

  return( *this );
}


bool
iLockFile::rlock( streamoff offset, ios::seek_dir dir, size_t amount )
{
  struct flock lock;

  lock.l_type   = F_RDLCK;
  lock.l_whence	= whence( dir );
  lock.l_start  = offset;
  lock.l_len 	= amount;

  if( fcntl( fd, F_SETLKW, &lock ) == -1 )
    {
      state = ios::badbit;
      osError = errno;
      return( false );
    }
  return( true );
}  


const char *
iLockFile::getClassName( void ) const
{
  return( "iLockFile" );
}


oLockFile::oLockFile(
  const char * 	    fileName,
  ios::open_mode    mode,
  int	    	    perm
  )
  : LockFile( fileName, mode, perm )
{
  ;
}


oLockFile &
oLockFile::lwrite( const void * dest, size_t amount )
{
  if( ! good() )
    return( *this );
  
  if( ! wlock( 0, ios::cur, amount ) )
    return( *this );
  
  write( dest, amount );
  
  unlock( amount * -1, ios::cur, amount );
  
  return( *this );
}

  
oLockFile &
oLockFile::lwrite( streampos pos, const void * dest, size_t amount )
{
  if( ! good() )
    return( *this );
  
  if( ! wlock( pos, ios::beg, amount ) )
    return( *this );
  
  write( pos, dest, amount );
  
  unlock( pos, ios::beg, amount );
  
  return( *this );
}

oLockFile &
oLockFile::lwrite(
  streamoff     offset,
  ios::seek_dir dir,
  const void * 	dest,
  size_t	amount
  )
{
  if( ! good() )
    return( *this );
  
  if( ! wlock( offset, dir, amount ) )
    return( *this );
  
  write( offset, dir, dest, amount );
  
  unlock( offset, dir, amount );

  return( *this );
}


bool
oLockFile::wlock( streamoff offset, ios::seek_dir dir, size_t amount )
{
  struct flock lock;

  lock.l_type   = F_WRLCK;
  lock.l_whence	= whence( dir );
  lock.l_start  = offset;
  lock.l_len 	= amount;

  if( fcntl( fd, F_SETLKW, &lock ) == -1 )
    {
      state = ios::badbit;
      osError = errno;
      return( false );
    }
  return( true );
}  

const char *
oLockFile::getClassName( void ) const
{
  return( "oLockFile" );
}

ioLockFile::ioLockFile(
  const char * 	    fileName,
  ios::open_mode    mode,
  int	    	    perm
  )
  : LockFile( fileName, mode, perm )
{
  ;
}

void
ioLockFile::open( 
  const char * 	    fileName,
  ios::open_mode    mode,
  int	    	    perm
  )
{
  LockFile::open( fileName, mode, perm );
}

const char *
ioLockFile::getClassName( void ) const
{
  return( "ioLockFile" );
}

  
  

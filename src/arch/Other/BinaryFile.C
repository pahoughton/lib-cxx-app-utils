//
// File:        BinaryFile.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/14/95 10:27 
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 12:22:20  houghton
// Initial BinaryFile implementation
//
//
static const char * RcsId =
"$Id$";

#include "BinaryFile.hh"

#include <Str.hh>
#include <Utils.hh>

#include <unistd.h>
#include <fcntl.h>
#include <cerrno>

void
BinaryFile::open(
  const char *	    fileName,
  ios::open_mode    mode,
  int	    	    perm
  )
{
  osError = 0;
  state = 0;

  if( (fd = ::open( fileName, OpenFlags( mode ), perm ) ) < 0 )
    {
      osError = errno;
      state |= ios::badbit;
    }
}

void
BinaryFile::close( void )
{
  if( is_open ) ::close( fd );
  fd = -1;  
}

bool
BinaryFile::is_open( void )
{
  return( fd >= 0 );
}

streampos
BinaryFile::seekoff( streamoff offset, ios::seek_dir dir )
{
  return( seek( dir, offset ) );
}

streampos
BinaryFile::seekpos( streampos pos )
{
  return( seek( ios::beg, pos ) );
}

streampos
BinaryFile::seek( long pos )
{
  return( seek( ios::beg, pos ) );
}

streampos
BinaryFile::seek( ios::seek_dir	dir, streamoff offset )
{
  return( lseek( fd, offset, whence( dir ) ) );
}

streampos
BinaryFile::tell( void )
{
  return( seek( ios::cur, 0 ) );
}

int
BinaryFile::sync( void )
{
  return( fsync( fd ) ? EOF : 0 );
}

int
BinaryFile::rdstate( void ) const
{
  return( state );
}

void
BinaryFile::clear( int stateFlags )
{
  state = stateFlags;
}

bool
BinaryFile::operator ! ( void ) const
{
  return( fail() );
}

bool
BinaryFile::eof( void ) const
{
  return( state & ios::eofbit );
}

bool
BinaryFile::fail( void ) const
{
  return( state & (ios::failbit | ios::badbit) );
}

bool
BinaryFile::bad( void ) const
{
  return( state & ios::badbit );
}


// getClassName - return the name of this class
const char *
BinaryFile::getClassName( void ) const
{
  return( "BinaryFile" );
}

// good - return TRUE if no detected errors
bool
BinaryFile::good( void ) const
{
  return( state == ios::goodbit );
}

// error - return a string describing the current state
const char *
BinaryFile::error( void ) const
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
      if( osError != 0 )
	errStr << ": " << strerror( osError );
      else
	errStr << ": unknown error";
    }

  return( errStr.cstr() );
}


BinaryFile::BinaryFile( void )
{
  fd = 0;
  state = ios::badbit;
  osError = ENOENT;
}

BinaryFile::BinaryFile(
  const char *      fileName,
  ios::open_mode    mode,
  int   	    perm
  )
{
  open( fileName, mode, perm );
}

int
BinaryFile::whence( ios::seek_dir dir )
{
  return( dir == ios::beg ? SEEK_SET :
	  dir == ios::cur ? SEEK_CUR : SEEK_END );
}
	  

iBinaryFile::iBinaryFile( void )
{
  bytesRead = 0;
}

iBinaryFile::iBinaryFile( const char * fileName )
  : BinaryFile( fileName, ios::in )
{
  bytesRead = 0;
}

void
iBinaryFile::open( const char * fileName )
{
  BinaryFile::open( fileName, ios::in );
}

iBinaryFile &
iBinaryFile::read(
  void *    dest,
  size_t    amount
  )
{
  if( ! good() )
    return( *this );
  
  if( (bytesRead = ::read( fd, dest, amount )) == amount )
    return( *this );

  if( bytesRead == 0 )
    {
      state |= ios::eofbit;
      state |= ios::failbit;
      return( *this );
    }
	
  if( bytesRead < 0 )
    {
      state |= ios::badbit;
      osError = errno;
      return( *this );
    }

  char * rDest = (char *) dest;
  
  for( int once; bytesRead < amount; bytesRead += once )
    {
      if( (once = ::read( fd, rDest + bytesRead, amount - bytesRead )) <= 0 )
	{
	  if( once == 0 )
	    {
	      state |= ios::eofbit;
	      state |= ios::failbit;
	      break;
	    }
	  else
	    {
	      state |= ios::badbit;
	      osError = errno;
	      break;
	    }
	}
    } 

  return( *this );

}

iBinaryFile &
iBinaryFile::read( streampos pos, void * dest, size_t amount )
{
  seek( pos );
  return( read( dest, amount ) );
}

iBinaryFile &
iBinaryFile::read(
  streamoff     offset,
  ios::seek_dir	dir,
  void * 	dest,
  size_t	amount
  )
{
  seek( dir, offset );
  return( read( dest, amount ) );
}

int
iBinaryFile::gcount( void )
{
  return( bytesRead );
}

const char *
iBinaryFile::getClassName( void ) const
{
  return( "iBinaryFile" );
}

oBinaryFile::oBinaryFile( void )
{
  ;
}

oBinaryFile::oBinaryFile(
  const char * 	    fileName,
  ios::open_mode    mode,
  int	    	    perm
  )
  : BinaryFile( fileName, mode, perm )
{
  ;
}

void
oBinaryFile::open(
  const char * 	    fileName,
  ios::open_mode    mode,
  int	    	    perm
  )
{
  BinaryFile::open( fileName, mode, perm );
}

oBinaryFile &
oBinaryFile::write( const void * src, size_t amount )
{
  if( ! good() )
    return( *this );
  
  int w = ::write( fd, src, amount );

  if( w == amount )
    return( *this );

  if( w == -1 )
    {
      state |= ios::badbit;
      osError = errno;
      return( *this );
    }

  const char * wSrc = (const char *)src;
  
  for( int once; w < amount; w += once )
    {
      if( (once = ::write( fd, wSrc + w, amount - w ) ) < 0 )
	{
	  state |= ios::badbit;
	  osError = errno;
	  break;
	}
    }
  
  return( *this );
}

oBinaryFile &
oBinaryFile::write( streampos pos, const void * src, size_t amount )
{
  seek( pos );
  return( write( src, amount ) );
}

oBinaryFile &
oBinaryFile::write(
  streamoff     offset,
  ios::seek_dir	dir,
  const void * 	src,
  size_t	amount
  )
{
  seek( dir, offset );
  return( write( src, amount ) );
}

const char *
oBinaryFile::getClassName( void ) const
{
  return( "oBinaryFile" );
}


ioBinaryFile::ioBinaryFile(
  const char * 	    fileName,
  ios::open_mode    mode,
  int	    	    perm
  )
  : BinaryFile( fileName, mode, perm )
{
  ;
}

void
ioBinaryFile::open(
  const char * 	    fileName,
  ios::open_mode    mode,
  int	    	    perm
  )
{
  BinaryFile::open( fileName, mode, perm );
}

const char *
ioBinaryFile::getClassName( void ) const
{
  return( "ioBinaryFile" );
}


  
  
  


  
  
  



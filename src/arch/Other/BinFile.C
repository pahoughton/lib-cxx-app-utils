//
// File:        BinFile.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld1.wiltel.com)
// Created:     08/02/95 05:29
//
// Revision History:
//
// $Log$
// Revision 4.1  1997/09/17 15:13:20  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:09:12  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:25:14  houghton
// Changed to Release 3
//
// Revision 2.1  1995/11/10 12:47:02  houghton
// Change to Version 2
//
// Revision 1.1  1995/11/05  13:13:47  houghton
// Initial implementation
//
//

#include "BinFile.hh"
#include <StlUtils.hh>

#include <cerrno>

#include <unistd.h>
#include <fcntl.h>

#ifdef   STLUTILS_DEBUG
#define  inline
#include <BinFile.ii>
#endif

#ifdef AIX
extern "C" int fsync( int fd );
#endif

const char BinFile::version[] =
LIB_STLUTILS_VERSION
"$Id$";

BinFile::~BinFile( void )
{
  close();
}

bool
BinFile::open( const char * fn, ios::open_mode mode, int perm )
{
  openMode = mode;
  openPerm = perm;
  fileStat( fn );

  osErrno = 0;
  state = ios::goodbit;
  
  if( (fd = ::open( fn, OpenFlags( mode ), perm ) ) < 0 )
    {
      osErrno = ::errno;
      state |= ios::badbit;
    }
  
  return( good() );
}

void
BinFile::close( void )
{
  if( is_open() )
    {
      ::close( fd );
      fd = -1;
      state = ios::badbit;
    }
}

bool
BinFile::is_open( void ) const
{
  return( fd >= 0 );
}

streampos
BinFile::seek( ios::seek_dir dir, streamoff offset )
{
  if( good() )
    return( lseek( fd, offset, whence( dir ) ) );
  else
    return( -1 );
}

streampos
BinFile::tell( void ) const
{
  if( good() )
    return( lseek( fd, 0, whence( ios::cur ) ) );
  else
    return( -1 );
}

BinFile &
BinFile::read( void * dest, size_t amount )
{
  if( ! good() )
    return( *this );
  
  if( (bytesRead = ::read( fd, dest, amount )) == (long)amount )
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
      osErrno = ::errno;
      return( *this );
    }

  char * rDest = (char *) dest;
  
  for( int once; bytesRead < (long)amount; bytesRead += once )
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
	      osErrno = ::errno;
	      break;
	    }
	}
    } 

  return( *this );
}

BinFile &
BinFile::write( const void * src, size_t amount )
{
  if( ! good() )
    return( *this );
  
  int w = ::write( fd, src, amount );

  if( w == (long)amount )
    return( *this );

  if( w == -1 )
    {
      state |= ios::badbit;
      osErrno = ::errno;
      return( *this );
    }

  const char * wSrc = (const char *)src;
  
  for( int once; w < (long)amount; w += once )
    {
      if( (once = ::write( fd, wSrc + w, amount - w ) ) < 0 )
	{
	  state |= ios::badbit;
	  osErrno = ::errno;
	  break;
	}
    }
  
  return( *this );
}

int
BinFile::sync( void )
{
  return( fsync( fd ) ? EOF : 0 );
}

bool
BinFile::good( void ) const
{
  return( state == ios::goodbit && fd >= 0 );
}

const char *
BinFile::error( void ) const
{
  static Str errStr;
  errStr.reset();

  errStr << getClassName() << ": '" << fileStat.getName() << "' - ";

  if( good() )
    {
       errStr << "ok.";
    }
  else
    {
      if( osErrno )
	errStr << strerror( osErrno );
      else
	errStr << "unknown error.";
    }
  
  return( errStr.cstr() );
}

const char *
BinFile::getClassName( void ) const
{
  return( "BinFile" );
}

ostream &
BinFile::dumpInfo( ostream & dest ) const
{
  dest << getClassName() << ":\n";

  dest << "    " << version << '\n';

  if( ! good() )
    dest << "    Error: " << error() << '\n';
  else
    dest << "    " << "Good!" << '\n';

  dest << "    fd:          " << fd << '\n'
       << "    state:       " << state << '\n'
       << "    osErrno:     " << osErrno << '\n'
       << "    openMode:    " << openMode << '\n'
       << "    openPerm:    " << openPerm << '\n'
    ;

  dest << getClassName() << "::";
  fileStat.dumpInfo( dest );
  
  dest << '\n';

  return( dest );
}


  

//
// File:        File.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for File
//  
// Author:      Paul Houghton 719-527-7834 - (paul.houghton@wcom.com)
// Created:     03/08/98 07:33
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include "File.hh"
#include <Str.hh>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <fcntl.h>

#if defined( STLUTILS_DEBUG )
#include "File.ii"
#endif

STLUTILS_VERSION(
  File,
  "$Id$");


File::File( void )
  : osError( 0 )
{
}

File::File( const char * srcFn )
  : src( srcFn ),
    osError( 0 )
{
}

File::~File( void )
{
}

bool
File::copy( const char * destFn )
{
  if( ! good() )
    return( false );

  dest( destFn );

  if( dest.good() )
    {
      if( dest.isReg() )
	{
	  if( remove( dest.getName().c_str() ) )
	    return( setError( errno, "removing dest", dest.getName() ) );
	}
      else
	{
	  if(  dest.isDir() )
	    {
	      FilePath destFullName( dest.getName() );
      
	      if( destFullName.size()
		  && destFullName.at( destFullName.size() - 1 ) == '/' )
		destFullName << src.getName().getFileName();
	      else
		destFullName << '/' << src.getName().getFileName();

	      dest( destFullName );

	      if( dest.good() && dest.isReg() )
		{
		  if( remove( dest.getName().c_str() ) )
		    return( setError( errno, "removing dest", dest.getName() ) );
		}
	    }
	}
    }

  int destFd;
  int srcFd;

  if( (srcFd = open( src.getName().c_str(), O_RDONLY, 0 ) ) < 0 )
    return( setError( errno, "opening src", src.getName() ) );
    
  
  if( (destFd = open( dest.getName().c_str(),
		      O_WRONLY | O_CREAT | O_TRUNC,
		      0600 ) ) < 0 )
    {
      close( srcFd );
      return( setError( errno, "opening dest", dest.getName() ) );
    }

  
  size_type	readLen;
  char		buffer[ 1024 * 8 ];
  
  while( (readLen = readfd( srcFd, buffer, sizeof( buffer ) ) ) > 0 )
    {
      if( writefd( destFd, buffer, readLen ) < 0 )
	{
	  close( srcFd );
	  close( destFd );
	  remove( dest.getName() );
	  return( setError( errno, "writing to dest", dest.getName() ) );
	}
    }

  if( readLen < 0 )
    {
      close( srcFd );
      close( destFd );
      remove( dest.getName() );
      return( setError( errno, "reading src", src.getName() ) );
    }

  if( close( srcFd ) < 0 )
    {
      close( destFd );
      remove( dest.getName() );
      return( setError( errno, "closing src", src.getName() ) );
    }

  if( close( destFd ) < 0 )
    {
      return( setError( errno, "closing dest", dest.getName() ) );
    }

  return( setDestStat() );
  
  return( true );
}

bool
File::move( const char * destFn )
{

  if( ! good() )
    return( false );

  dest( destFn );

  if( dest.good() )
    {
      if( dest.isReg() )
	{
	  if( dest.canWrite() )
	    {
	      return( moveFile() );
	    }
	  else
	    {
	      // can not write.
	      return( setError( EPERM, "cant write to dest.", dest.getName() ) );
	    }
	}
      else
	{
	  if( dest.isDir() )
	    {
	      
	      FilePath destFullName( dest.getName() );
      
	      if( destFullName.size()
		  && destFullName.at( destFullName.size() - 1 ) == '/' )
		destFullName << src.getName().getFileName();
	      else
		destFullName << '/' << src.getName().getFileName();
	      
	      dest( destFullName );

	      return( moveFile() );
	    }
	  else
	    {
	     return( setError( 0, "dest not a file or dir", dest.getName() ) );
	    }
	}
    }
  else
    {
      FileStat destDir( dest.getName().getPath() );

      if( destDir.good() && destDir.isDir() )
	{
	  if( destDir.getDevice() == src.getDevice() )
	    {
	      if( rename( src.getName(), dest.getName() ) )
		return( setError( errno,
				  "renaming to dest",
				  dest.getName() ) );
	      return( setDestStat() );
	    }
	  else
	    {
	      if( copy( dest.getName() ) )
		{
		  if( remove( src.getName() ) )
		    return( setError( errno, "removing src", src.getName() ) );
		}
	    }
	}
    }

  return( true );
}
      

		  
				
				
		      

bool
File::clear( void )
{
  osError = 0;
  errorDesc.reset();
  return( good() );
}

bool
File::good( void ) const
{
  return( osError == 0
	  && errorDesc.size() == 0
	  && src.good() && src.isReg() && src.canRead() );
}

const char *
File::error( void ) const
{
  static Str errStr;

  errStr = File::getClassName();

  if( good() )
    {
      errStr << ": ok";
    }
  else
    {
      size_t eSize = errStr.size();

      if( errorDesc.size() )
	{
	  errStr << ": " << errorDesc;
	}

      if( ! src.good() )
	{
	  errStr << ": " << src.error();
	}
      else
	{
	  if( ! src.isReg() )
	    {
	      errStr << ": src '" << src.getName() << "' not a regular file .";
	    }
	  
	  if( ! src.canRead() )
	    {
	      errStr << ": can not read src '" << src.getName() << "'.";
	    }
	}
      
      if( eSize == errStr.size() )
        errStr << ": unknown error";
    }

  return( errStr.c_str() );
}

const char *
File::getClassName( void ) const
{
  return( "File" );
}

const char *
File::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}


ostream &
File::dumpInfo(
  ostream &	destStream,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    destStream << File::getClassName() << ":\n"
	       << File::getVersion() << '\n';

  if( ! File::good() )
    destStream << prefix << "Error: " << File::error() << '\n';
  else
    destStream << prefix << "Good" << '\n';

  Str pre;

  pre = prefix;
  pre << "src:";
  src.dumpInfo( destStream, pre, false );

  pre = prefix;
  pre << "dest:";
  dest.dumpInfo( destStream, pre, false );

  return( destStream );
}

bool
File::moveFile( void )
{
  if( dest.getDevice() == src.getDevice() )
    {
      // same device
      if( dest.getInode() == src.getInode() )
	return( setError( 0, "dest and src are the same file.", dest.getName() ) );

      if( dest.good() )
	{
	  // there is an existing file in the way.
	  if( remove( dest.getName() ) )
	    return( setError( errno, "removing dest", dest.getName() ) );
	}
      
      if( rename( src.getName(), dest.getName() ) )
	return( setError( errno, "renaming to dest", dest.getName() ) );

      return( setDestStat() );
      
    }
  else
    {
      // different device have to copy 
      if( copy( dest.getName() ) )
	{
	  if( remove( src.getName() ) )
	    return( setError( errno, "removing src", src.getName() ) );
	}
    }
  
  return( true );
}

bool
File::setDestStat( void )
{
  dest( dest.getName() );
  
  if( ! dest.setTimes( src.getAccessTime(), src.getModificationTime() ) )
    return( setError( dest.getSysError(), "setting times", dest.getName() ) );
  
  if( src.getUID() == 0 )
    {
      if( ! dest.setOwner( src.getUID(), src.getGID() ) )
	return( setError( dest.getSysError(),
			  "setting owner",
			  dest.getName() ) );
    }
  
  if( ! dest.setMode( src.getMode() & 07777 ) )
    return( setError( dest.getSysError(), "setting mode", dest.getName() ) );

  return( true );
}

File::size_type
File::readfd( int fd, void * destBuf, size_t destSize )
{
  int bytes;

  if( destSize <= 0 )
    return( destSize );

#if defined( EINTR )
  for( bytes = read( fd, (char *) destBuf, destSize );
       bytes < 0 && errno == EINTR;
       bytes = read( fd, (char *) destBuf, destSize ) );
#else
  bytes = read( fd, (char *) destBuf, destSize );
#endif
  
  return( bytes );
}

      
File::size_type
File::writefd( int fd, const void * srcBuf, size_t srcLen )
{
  int bytes(0);
  int written;
  const char * srcPtr = (const char *)srcBuf;
  
  while( srcLen > 0 )
    {
      if( (written = write( fd, srcPtr, srcLen )) < 0 )
	{
	  
#if defined( EINTR )
	  if( errno == EINTR )
	    continue;
#endif
	  return( written );
	}
      bytes += written;
      srcPtr += written;
      srcLen -= written;
    }
  return( bytes );
}
      
      
  
  

bool
File::setError( int osErr, const char * desc, const char * fileName )
{
  osError = osErr;

  errorDesc << desc << " '" << fileName << "' - "
	    << strerror( osError ) << '.';
  return( osError == 0 );
}


// Revision Log:
//
// $Log$
// Revision 1.2  1998/03/11 16:08:22  houghton
// Added setDestStat
// Bug-Fix: a few.
//
// Revision 1.1  1998/03/08 18:08:28  houghton
// Initial Version.
//
//

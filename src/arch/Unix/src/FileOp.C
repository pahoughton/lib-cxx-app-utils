//
// File:        FileOp.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for FileOp
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

#include "FileOp.hh"
#include <Str.hh>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <fcntl.h>

#if defined( STLUTILS_DEBUG )
#include "FileOp.ii"
#endif

STLUTILS_VERSION(
  FileOp,
  "$Id$");

const char *	FileOp::OpTypeName[] =
{
  "copy",
  "move",
  0
};

FileOp::FileOp( void )
  : osError( 0 )
{
}

FileOp::FileOp( const char * srcFn )
  : src( srcFn ),
    osError( 0 )
{
}

FileOp::~FileOp( void )
{
}

bool
FileOp::clear( void )
{
  osError = 0;
  errorDesc.reset();
  return( good() );
}

bool
FileOp::good( void ) const
{
  return( osError == 0
	  && errorDesc.size() == 0
	  && src.good() && src.isReg() && src.canRead() );
}

const char *
FileOp::error( void ) const
{
  static Str errStr;

  errStr = FileOp::getClassName();

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
FileOp::getClassName( void ) const
{
  return( "FileOp" );
}

const char *
FileOp::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}


ostream &
FileOp::dumpInfo(
  ostream &	destStream,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    destStream << FileOp::getClassName() << ":\n"
	       << FileOp::getVersion() << '\n';

  if( ! FileOp::good() )
    destStream << prefix << "Error: " << FileOp::error() << '\n';
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
FileOp::setDest( OpType opType, const char * fn, bool overwrite )
{
  dest( fn );

  if( dest.good() )
    {
      if( dest.isDir() )
	{
	  FilePath destFullName( dest.getName() );
	  
	  if( destFullName.size()
	      && ( destFullName.at( destFullName.size() - 1 )
		   == destFullName.dirSep() ) )
	    destFullName << src.getName().getFileName();
	  else
	    destFullName << destFullName.dirSep()
			 << src.getName().getFileName();
	  
	  dest( destFullName );

	  if( ! dest.good() )
	    return( true );
	}

      // this is now either the orig file or the orig dir
      // with the file name appended.
      if( dest.isReg() )
	{
	  if( overwrite )
	    {
	      if( opType == OT_Move )
		{
		  if( ! dest.canWrite() )
		    {
		      return( setError( EPERM,
					opType, 
					"can't write to dest",
					dest.getName() ) );
		    }
		}
	      if( ! removeFile( dest.getName() ) )
		return( false );
	    }
	  else
	    {
	      return( setError( 0,
				opType,
				"(no overwite) dest exists",
				dest.getName() ) );
	    }
	}
      else
	{
	  // not a reg && not a dir
	  return( setError( 0,
			    opType,
			    "can't overwrite NON regulare file",
			    dest.getName() ) );
	}
    }
  return( true );
}
  
bool
FileOp::copyFile( void )
{
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
	  removeFile( dest.getName() );
	  return( setError( errno, "writing to dest", dest.getName() ) );
	}
    }

  if( readLen < 0 )
    {
      close( srcFd );
      close( destFd );
      removeFile( dest.getName() );
      return( setError( errno, "reading src", src.getName() ) );
    }

  if( close( srcFd ) < 0 )
    {
      close( destFd );
      removeFile( dest.getName() );
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
FileOp::moveFile( void )
{

  FileStat destDir( dest.getName().getPath() );

  if( destDir.good() && destDir.isDir() )
    {
      if( destDir.getDevice() == src.getDevice() )
	{
	  if( ::rename( src.getName(), dest.getName() ) )
	    return( setError( errno,
			      "renaming to dest",
			      dest.getName() ) );
	  return( setDestStat() );
	}
      else
	{
	  if( ! copyFile() )
	    return( false );
	    
	  if( ! removeFile( src.getName() ) )
	    return( false );

	  return( true );
	}
    }
  else
    {
      return( setError( 0,
			"dest directory device unknown",
			destDir.getName() ) );
    }  
}

bool
FileOp::removeFile( const char * fn )
{
  if( ::remove( fn ) )
    return( setError( errno, "removing", fn ) );
  else
    return( true );
}

bool
FileOp::setDestStat( void )
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

FileOp::size_type
FileOp::readfd( int fd, void * destBuf, size_t destSize )
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

      
FileOp::size_type
FileOp::writefd( int fd, const void * srcBuf, size_t srcLen )
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
FileOp::setError( int osErr, const char * desc, const char * fileName )
{
  clear();
  
  osError = osErr;

  errorDesc << desc << " '" << fileName << '\'';

  if( osErr )
    errorDesc << " - " << strerror( osError ) << '.';
  else
    errorDesc << '.';
  
  return( osError == 0 && errorDesc.size() == 0 );
}

bool
FileOp::setError(
  int osErr,
  OpType op,
  const char * desc,
  const char * fileName
  )
{
  clear();
  
  osError = osErr;

  errorDesc << OpTypeName[ op ] << ' ' << desc << " '" << fileName << '\'';

  if( osErr )
    errorDesc << " - " << strerror( osError ) << '.';
  else
    errorDesc << '.';
  
  return( osError == 0 && errorDesc.size() == 0 );
}


// Revision Log:
//
// $Log$
// Revision 1.5  1999/03/02 12:51:23  houghton
// Bug-Fixes.
// Cleanup.
//
// Revision 1.4  1998/11/02 19:20:33  houghton
// Major rework.
// Added protected:setDest();
// Added protected:removeFile();
//
// Revision 1.3  1998/03/13 12:33:52  houghton
// Bug-Fix: if just doing a rename, don't no reason to set times or mode.
//
// Revision 1.2  1998/03/11 16:08:22  houghton
// Added setDestStat
// Bug-Fix: a few.
//
// Revision 1.1  1998/03/08 18:08:28  houghton
// Initial Version.
//
//

//
// File:        LogBuf.C
// Desc:        
//              
//
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     01/29/95 13:06 
//
// Revision History:
//
// $Log$
// Revision 2.1  1995/11/10 12:40:44  houghton
// Change to Version 2
//
// Revision 1.4  1995/11/05  15:28:39  houghton
// Revised
//
//

#include "LogBuf.hh"
#include "FileStat.hh"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>

#if defined( CLUE_DEBUG )
#define  inline
#include <LogBuf.ii>
#endif

CLUE_VERSION(
  LogBuf,
  "$Id$" );

#define LOGBUF_SIZE 512


//
// LogBuf is the streambuf for the log
//

LogBuf::~LogBuf( void )
{
  close();
  
  if( buffer )
    {
      delete buffer;
      buffer = 0;
    }
}

  

filebuf *
LogBuf::open(
    const char *    name,
    ios::open_mode  mode,
    int		    prot,
    size_t	    logMaxSize,
    size_t	    logTrimSize
    )
{
  if( stream != 0 && isFile() )
    {
      close();
    }

 maxSize = logMaxSize;
 trimSize = logTrimSize;
 logFileName = name;
 openMode = mode;
 openProt = prot;

  FileStat  stat( logFileName );
  
 if( logMaxSize && stat.good() && ( (size_t)stat.getSize() > logMaxSize ) )
   trimLog( stat.getSize(), logMaxSize );
 else
   openLog();
 
 return( (filebuf *)(stream) );
}


void
LogBuf::close( void )
{
  sync();
  closeLog();  
}

size_t
LogBuf::trim( size_t maxLog )
{
  size_t maxLogSize = ( maxLog ? maxLog : maxSize );
  size_t trimLogSize = ( trimSize ? trimSize : (maxLogSize / 4 ) );
  
  if( ! maxLogSize || ! isFile() ) return( 0 );

  if( stream )
    close();

  FileStat  stat( logFileName );

  if( ! stat.good() ||
      ( (size_t)stat.getSize() < (maxLogSize - trimLogSize) ) )
    {
      openLog();
      return( 0 );
    }

  return( trimLog( stat.getSize(), maxLogSize ) );
}

int 
LogBuf::overflow( int c )
{
  sync();
  
  if( ! stream )
    return( EOF );
  
  if( teeStream )
    {
      teeStream->overflow(c);
    }
  return( stream->overflow(c) );
}

int
LogBuf::underflow( void )
{
  if( ! stream )
    return( EOF );
  
  return( stream->underflow() );
}

int
LogBuf::sync( void )
{
  if( ! stream )
    {
      setp( pbase(), epptr() );
      return( EOF );
    }
  
  char *    base = pbase();
  int	    len = pptr() - pbase();
  
  if( logLevel.shouldOutput() && len != 0 && base != 0)
    {
      for( int cnt = stream->sputn( base, len );
	   cnt < len && cnt != 0 && len != 0;
	   len -= cnt, base += cnt );

      if( teeStream )
	{
	  for( int cnt = teeStream->sputn( base, len );
	      cnt < len && cnt != 0 && len != 0;
	      len -= cnt, base += cnt );
	  teeStream->sync();
	}
    }

  setp( pbase(), epptr() );

  int  syncResult = stream->sync();

  size_t curSize = (size_t)stream->seekoff( 0, ios::cur, ios::out );
		    
  if( isFile() && maxSize && curSize > maxSize )
    {
      closeLog();
      trimLog( curSize, maxSize );
    }
    
  return( syncResult );
}

const char *
LogBuf::getClassName( void ) const
{
  return( "LogBuf" );
}

const char *
LogBuf::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer, logLevel.getVersion( false ) ) );
}

ostream &
LogBuf::dumpInfo( 
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << LogBuf::getClassName() << ":\n"
	 << LogBuf::getVersion() << '\n';

  dest << prefix << "is file:      " << (isFile() == true ? "yes" : "no" ) << '\n';
  if( isFile() )
    dest << prefix << "logFileName:  " << logFileName << '\n';
  dest << prefix << "maxSize:      " << maxSize << '\n'
       << prefix << "trimSize:     " << trimSize << '\n'
       << prefix << "openMode:    " << openMode << '\n'
       << prefix << "openProt:    " << openProt << '\n'
    ;
  
  Str pre;
  pre = prefix;
  pre << "logLevel:" << logLevel.getClassName() << "::";

  logLevel.dumpInfo( dest, pre, false );

  dest << '\n';

  return( dest );
}

  
void
LogBuf::initLogBuffer( void )
{
  buffer = new char[LOGBUF_SIZE];
  
  setb( buffer, buffer + LOGBUF_SIZE );
  setp( buffer, buffer + LOGBUF_SIZE );
}

void
LogBuf::initbuf( streambuf * outStream )
{
  initLogBuffer();
  
  stream    	= outStream;  
  streamIsFile 	= false;
  teeStream 	= 0;  
}

void
LogBuf::initbuf(
  const char *	    fileName,
  ios::open_mode    mode,
  int		    prot,
  size_t	    logMaxSize,
  size_t	    logTrimSize
  )
{
  initLogBuffer();

  stream = 0;
  streamIsFile = true;
  teeStream 	= 0;  
  
  open( fileName, mode, prot, logMaxSize, logTrimSize );
 
}
 
filebuf *
LogBuf::openLog( void )
{
  filebuf * file = new filebuf();

  stream = file;
  streamIsFile = true;

  int prevMask = umask( 0 );

  filebuf * ret = file->open( logFileName, openMode, openProt );
  
  umask( prevMask );

  return( ret );
}


size_t
LogBuf::trimLog( size_t curSize, size_t maxLogSize )
{
  FilePath  tmpFn( logFileName );

  tmpFn.setTempName();

  if( rename( logFileName, tmpFn ) )
    {
      openLog();
      return( 0 );
    }
  
  ifstream  in( tmpFn );
  ofstream  out( logFileName, openMode, openProt );

  if( ! in.good() || ! out.good() )
    {
      rename( tmpFn, logFileName );
      openLog();
      return( 0 );
    }

  size_t  trimAmount = ( trimSize ? trimSize : maxLogSize / 4 );
  
  in.seekg( (curSize - maxLogSize) + trimAmount );

  if( ! in.good() )
    {
      in.close();
      out.close();
      rename( tmpFn, logFileName );
      open( logFileName, openMode, openProt );
      return( 0 );
    }

  char copyBuf[4096];
  bool first = true;
  
  for( in.read( copyBuf, sizeof( copyBuf ) );
       in.good() && out.good();
       in.read( copyBuf, sizeof( copyBuf ) ) )
    {
      if( first )
	{
	  const char * crPos = (const char *)memchr( (const void *)copyBuf,
						     '\n',
						     in.gcount() );
	  if( crPos )
	    {
	      out.write( crPos + 1,
			 in.gcount() - ( (crPos + 1) - copyBuf ) );
	      first = false;
	    }
	}
      else
	{
	  out.write( copyBuf, in.gcount() );
	}
    }

  if( in.gcount() )
    {
      if( first )
	{
	  const char * crPos = (const char *)memchr( (const void *)copyBuf,
						     '\n',
						     in.gcount() );
	  if( crPos )
	    {
	      out.write( crPos + 1,
			 in.gcount() - ( (crPos + 1) - copyBuf ) );
	      first = false;
	    }
	}
      else
	{
	  out.write( copyBuf, in.gcount() );
	}
    }

  streampos newSize = out.tellp();
  out.close();
  in.close();

  remove( tmpFn );
  openLog();
  
  return( curSize - newSize );
}

void
LogBuf::closeLog( void )
{
  if( isFile() && stream != 0 )
    {
      filebuf * file = (filebuf *)stream;
      
      file->close();
      delete file;
      file = 0;
    }
    
  streamIsFile = false;
  stream = 0;
}

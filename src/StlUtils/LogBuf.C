//
// File:        LogBuf.C
// Project:	Clue
// Desc:        
//
//	Compiled source for for the LogBuf class.
//
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     01/29/95 13:06 
//
// Revision History: (See end of file for Revision Log)
//

#include "LogBuf.hh"
#include "ClueUtils.hh"
#include "StringUtils.hh"
#include "FileStat.hh"
#include "FilePath.hh"
#include "RegexScan.hh"
#include <strstream.h>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <errno.h>

#if defined( CLUE_DEBUG )
#include <LogBuf.ii>
#endif

CLUE_VERSION(
  LogBuf,
  "$Id$" );


#define LOGBUF_SIZE 2048

const LogBuf::FilterId    LogBuf::badFilterId = -1;

//
// LogBuf is the streambuf for the log
//

LogBuf::LogBuf(
  LogLevel::Level   outLevel,
  streambuf *	    outStream
  )
  : maxSize( 0 ),
    trimSize( 0 ),
    streamIsFile( false ),
    buffer( 0 ),
    stream( 0 ),
    teeStream( 0 ),
    logLevel( outLevel ),
    regex( 0 ),
    newMesg( true )
{
  initbuf( outStream );
}

LogBuf::LogBuf(
  const char * 	outLevel,
  streambuf *	outStream
  )
  : maxSize( 0 ),
    trimSize( 0 ),
    streamIsFile( false ),
    buffer( 0 ),
    stream( 0 ),
    teeStream( 0 ),
    logLevel( outLevel ),
    regex( 0 ),
    newMesg( true )
{
  initbuf( outStream );
}

LogBuf::LogBuf(
  const char *	    fileName,
  LogLevel::Level   outLevel,
  ios::open_mode    mode,
  int		    prot,
  size_t	    logMaxSize,
  size_t	    logTrimSize
  )
  : maxSize( 0 ),
    trimSize( 0 ),
    streamIsFile( false ),
    buffer( 0 ),
    stream( 0 ),
    teeStream( 0 ),
    logLevel( outLevel ),
    regex( 0 ),
    newMesg( true )
{
  initbuf( fileName, mode, prot, logMaxSize, logTrimSize );
}
  
LogBuf::LogBuf(
  const char *	    fileName,
  const char *      outLevel,
  ios::open_mode    mode,
  int		    prot,
  size_t	    logMaxSize,
  size_t	    logTrimSize
  )
  : maxSize( 0 ),
    trimSize( 0 ),
    streamIsFile( false ),
    buffer( 0 ),
    stream( 0 ),
    teeStream( 0 ),
    logLevel( outLevel ),
    regex( 0 ),
    newMesg( true )
{
  initbuf( fileName, mode, prot, logMaxSize, logTrimSize );
}

LogBuf::~LogBuf( void )
{
  close();
  
  if( buffer )
    {
      delete buffer;
      buffer = 0;
    }

  if( regex )
    delete regex;
  
  for( FilterList::iterator them = filters.begin();
       them != filters.end();
       ++them )
    {
      if( (*them).regex )
	delete regex;
    }
}

size_t
LogBuf::trim( size_t maxLog )
{
  if( ! is_file() )
    return( 0 );
  
  size_t maxLogSize = ( maxLog ? maxLog : maxSize );
  size_t trimLogSize = ( trimSize ? trimSize : (maxLogSize / 4 ) );
  
  if( ! maxLogSize )
    return( 0 );

  if( stream )
    close();

  FileStat  stat( logFileName );

  if( ! stat.good() ||
      ( (size_t)stat.getSize() < (maxLogSize - trimLogSize) ) )
    {
      openLog(ios::app);
      return( 0 );
    }

  return( trimLog( stat.getSize(), maxLogSize ) );
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
  if( stream != 0 && is_file() )
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
   openLog( mode );
 
 return( (filebuf *)(stream) );
}


void
LogBuf::close( void )
{
  sync();
  closeLog();  
}

LogBuf::FilterId
LogBuf::addFilter(
  streambuf *		    destBuf,
  const LogLevel::Level &   output,
  const char *		    regexString
  )
{
  sync();
  {
    // look for an empty slot
    for( FilterId f = 0; f < (long)filters.size(); ++f )
      {      
	if( filters[f].dest == 0 )
	  {
	    if( filters[f].regex )
	      delete filters[f].regex;
	    
	    filters[f].dest	    = destBuf;
	    filters[f].outputLevel  = output;
	    
	    if( regexString )
	      filters[f].regex	    = new RegexScan( regexString, true );
	    else
	      filters[f].regex	    = 0;
	    
	    return( f );
	}
      }
  }
  
  filters.push_back( Filter() );
  
  FilterId  f = filters.size() - 1;

  filters[f].dest	    = destBuf;
  filters[f].outputLevel    = output;

  if( regexString )
    filters[f].regex	    = new RegexScan( regexString );
  else
    filters[f].regex	    = 0;
  

  return( f );
}
	  
bool
LogBuf::filter( const char * regexStr )
{
  sync();
  if( regex )
    {     
      delete regex;
      regex = 0;
    }

  if( regexStr )
    {
      regex = new RegexScan( regexStr, true );
      newMesg = false;
    }
  
  return( regex != 0 && regex->good() );
}

const char *
LogBuf::getFilter( void ) const
{
  return( regex ? regex->getPattern() : 0 );
}

streambuf *
LogBuf::getFilterStream( LogBuf::FilterId id )
{
  if( id < (long)filters.size() )
    return( filters[id].dest );
  else
    return( 0 );
}

LogLevel::Level
LogBuf::getFilterLogLevel( LogBuf::FilterId id )
{
  if( id < (long)filters.size() )
    return( filters[id].outputLevel );
  else
    return( LogLevel::None );
}

const char *
LogBuf::getFilterRegex( LogBuf::FilterId id )
{
  if( id < (long)filters.size() )
    return( filters[id].regex ?
	    filters[id].regex->getPattern() : 0 );
  else
    return( 0 );
}
  
streambuf *
LogBuf::delFilter( FilterId id )
{
  sync();
  streambuf * dest = 0;
  if( id < (long)filters.size() && filters[id].dest != 0 )
    {
      dest = filters[id].dest;
      filters[id].dest = 0;
      if( filters[id].regex )
	delete filters[id].regex;
      filters[id].regex = 0;
    }
  return( dest );
}

int 
LogBuf::overflow( int c )
{
  if( sync() == EOF )
    return( EOF );

  if( c == EOF )
    return 0;
  
  sputc( c );
  return( c );
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
  int	    syncResult = 0;
  
  if( base && len > 0 )
    {
      // first take care of my dest & the tee dest

      bool outputMesg = logLevel.shouldOutput();
      
      if( outputMesg && newMesg && regex )
	{
	  // if it's a new mesg and I'm filtering
	  outputMesg = regex->search( base, 0, len );
	}

      if( outputMesg )
	{
	  sendToStream( stream, base, len );
	  // stream's sync occures below.
	  
	  if( teeStream )
	    {
	      sendToStream( teeStream, base, len );
	      teeStream->sync();
	    }
	}
      
      // now take care of the filters
      for( FilterList::iterator them = filters.begin();
	   them != filters.end();
	   ++them )
	{
	  if( ! (*them).dest )
	    continue;
	  
	  outputMesg = (bool)(((*them).outputLevel & logLevel.getCurrent()));

	  if( outputMesg && newMesg && (*them).regex )
	    {
	      outputMesg = (*them).regex->search( base, 0, len );
	    }

	  if( outputMesg )
	    {
	      sendToStream( (*them).dest, base, len );
	      (*them).dest->sync();
	    }
	}
      
      syncResult = stream->sync();

    }

  newMesg = false;
  
  setp( pbase(), epptr() );

  size_t curSize = (size_t)stream->seekoff( 0, ios::cur, ios::out );
		    
  if( is_file() && maxSize && curSize > maxSize )
    {
      closeLog();
      trimLog( curSize, maxSize );
    }
    
  return( syncResult );
}

bool
LogBuf::good( void ) const
{
  return( errorDesc.size() == 0 );
}

const char *
LogBuf::error( void ) const
{
  static Str errStr;

  errStr = getClassName();

  if( good() )
    errStr << ": ok";
  else
    errStr << ": " << errorDesc;

  return( errStr.c_str() );
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

  dest << prefix << "is file:      "
       << (is_file() == true ? "yes" : "no" ) << '\n';
  
  if( is_file() )
    dest << prefix << "logFileName:  " << logFileName << '\n';
  
  dest << prefix << "maxSize:      " << maxSize << '\n'
       << prefix << "trimSize:     " << trimSize << '\n'
       << prefix << "openMode:    " << openMode << '\n'
       << prefix << "openProt:    " << openProt << '\n'
    ;

  {
    Str pre;
    pre = prefix;
    pre += "logLevel:" ;
    pre += logLevel.getClassName() ;
    pre += "::";
    logLevel.dumpInfo( dest, pre, false );
  }

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

  stream	= 0;
  streamIsFile  = true;
  teeStream 	= 0;  
  
  open( fileName, mode, prot, logMaxSize, logTrimSize );
 
}

int
LogBuf::sendToStream( streambuf * dest, char * base, int len )
{
  int total = 0;
  int cnt = 0;
  
  for( cnt = dest->sputn( base, len );
       cnt > 0 && cnt < len && len > 0;
       len -= cnt, base += cnt )
  {
    total += cnt;
    cnt = stream->sputn( base, len );
  }

  total += cnt;
  
  return( total );
}

//
// the openMask lets me reopen in ios::app when I have to
// reopen the file.
//
filebuf *
LogBuf::openLog( ios::open_mode openMask )
{
  filebuf * file = new filebuf();

  streamIsFile = true;

  int prevMask = umask( 0 );

  stream = file->open( logFileName,
		       (ios::open_mode)(openMode | openMask),
		       openProt );
  
  umask( prevMask );

  if( ! stream )
    {
      errorDesc << "open '" << logFileName
		<< "' mode: " << IosOpenModeToString( openMode )
		<< " prot: " << StringFrom( openProt, 8 ) << " failed: "
		<< strerror( errno ) ;
      
      delete file;
      file = 0;
    }
  return( file );
}


//
// trimLog
//
//  curSize     the current size of the log
//  maxLogSize	the log should be no larger than this
//
//  this->trimSize  the amout to trim off the begining of the file.
//		    if it is 0, maxLogSize / 4 is used.
//
//  This method keeps the reduces the size of the log file
//  by removeing the first 'trimSize' bytes from the file.
//
//  It does this by seeking into the file by 'trimSize' bytes.
//  Then it looks for the first '\n' (new line) character. Once
//  the '\n' is found, the rest of the data (after the '\n') is
//  written to the new log file.
//
size_t
LogBuf::trimLog( size_t curSize, size_t maxLogSize )
{
  FilePath  tmpFn( logFileName );
  tmpFn.setTempName();
  
  if( rename( logFileName, tmpFn ) )
    {
      openLog( ios::app );
      return( 0 );
    }
  
  ifstream  in( tmpFn );
  ofstream  out( logFileName, openMode, openProt );

  if( ! in.good() || ! out.good() )
    {
      rename( tmpFn, logFileName );
      openLog( ios::app );
      return( 0 );
    }

  size_t  trimAmount = ( trimSize ? trimSize : maxLogSize / 4 );
  
  in.seekg( (curSize - maxLogSize) + trimAmount );

  if( ! in.good() )
    {
      in.close();
      out.close();
      rename( tmpFn, logFileName );
      openLog( ios::app );
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
  openLog( ios::app );
  
  return( curSize - newSize );
}

void
LogBuf::closeLog( void )
{
  if( is_file() && stream != 0 )
    {
      filebuf * file = (filebuf *)stream;
      
      file->close();
      delete file;
      stream = 0;
    }
}

// Revision Log:
//
// $Log$
// Revision 3.8  1997/05/02 12:15:54  houghton
// Changed all LogLevel::Level args to const & to avoid copy constructor calls.
//
// Revision 3.7  1997/04/05 11:58:00  houghton
// Changed needed to include errno.h
//
// Revision 3.6  1997/04/04 20:53:25  houghton
// Added log file error checking.
// Cleanup.
//
// Revision 3.5  1997/04/04 03:10:09  houghton
// Changed constructors (and some other methods) to non-inline.
// Added getFilterStream
// Added getFilterLogLevel
// Added getFilterRegex
//
// Revision 3.4  1997/03/03 19:00:06  houghton
// Cleanup sync funct (while tracking a bug under AIX).
//
// Revision 3.3  1997/03/03 14:36:31  houghton
// Removed support for RW Tools++
//
// Revision 3.2  1996/11/20 12:04:24  houghton
// Bug-Fix: Fixed memory leaks.
//
// Revision 3.1  1996/11/14 01:23:46  houghton
// Changed to Release 3
//
// Revision 2.6  1996/11/13 16:46:00  houghton
// Changed include lines from "file" to <file"
//     to accomidate rpm.
// Changed isFile() to is_file() to be more consistant with the
//     standard filebuf::is_open().
// Changed openLog to take an ios::open_mode arg that will be
//     or'ed (|) with the original open mode. This allows the
//     log to be appended if it was not opened with 'ios::app', but
//     it was reopened from within LogBuf.
// Bug-Fix: addFilter() - added a call to sync to make sure we
//     only send entries to dest that were put in the log after the call
//     to addFilter().
// Bug-Fix: addFilter() - allow for regexString to be empty.
// Bug-Fix: sync() - only check for regex match if the entry
//     passed the level test.
// Bug-Fix: sync() - newMest must be set to false once an entry
//     has been searched.
// Bug-Fix: sync() - return EOF if there is no primary destination.
// Bug-Fix: dumpInfo() - fixed compile problems that came from
//     the change to using RWCString.
// Bug-Fix: openLog() - fixed so that if the open fails, the streambuf
//     is unuseable and the filebuf is deleted.
//
// Revision 2.5  1996/11/11 13:34:45  houghton
// Changed to specificly cast to a bool to get around a problem with AIX.
// Changed to use RWCString instead of strstream where possible because
//     of an inconsitancy in the public member of strstream.
//
// Revision 2.4  1996/11/06 18:05:22  houghton
// Bug-Fix: removed ';' from for loop in sendToStream.
//
// Revision 2.3  1996/11/04 13:57:12  houghton
// Restructure header comments layout.
// Changed LOG_BUFSIZE to 2048. So there is more data in the message
//     for the regex filter to match against.
// Added support for message filtering. (only output messages that
//     match a regex.
// Reorder methods to match header order.
// Added addFilter method to provide mutliple filtered destinations.
// Bug-Fix: overflow - before, it would place the overflow
//     character on the output stream even if it should not be output
//     according to the LogLevel. Changed to put the char in the buf
//     after the sync call.
// Bug-Fix: sync - if all the data in the buffer could not be put on
//     the destination stream in one call to sputn, the for loop would
//     be infinite.
// Rework sync to use new private sendToStream method. Also added
//     support for filters and multiple destinations.
// Changed dumpInfo to use strstream instead of Str
//     (as required by Mike Alexandar).
// Added sendToStream private method that puts the buffer data on an
//     ouptut stream.
// Changed trimLog to use RWCString instead of FilePath.
//     (as required by Mike Alexandar).
//
// Revision 2.2  1995/12/04 11:17:24  houghton
// Bug Fix - Can now compile with out '-DCLUE_DEBUG'.
//
// Revision 2.1  1995/11/10  12:40:44  houghton
// Change to Version 2
//
// Revision 1.4  1995/11/05  15:28:39  houghton
// Revised
//
//

//
// File:        LogBuf.C
// Project:	StlUtils ()
// Desc:        
//
//	Compiled source for for the LogBuf class.
//
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     01/29/95 13:06 
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//

#include "LogBuf.hh"
#include "StlUtilsMisc.hh"
#include "StringUtils.hh"
#include "FileStat.hh"
#include "FilePath.hh"
#include "RegexScan.hh"

#include <iostream>
#include <cstdio>
#include <cstring>
#include <errno.h>

#if defined( STLUTILS_DEBUG )
#include <LogBuf.ii>
#endif

STLUTILS_VERSION(
  LogBuf,
  "$Id$ " );


#define LOGBUF_SIZE 2048

const LogBuf::FilterId    LogBuf::badFilterId = -1;

//
// LogBuf is the streambuf for the log
//

LogBuf::LogBuf(
  LogLevel::Level   outLevel,
  std::streambuf *	    outStream
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
  std::streambuf *	outStream
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
  std::ios::openmode    mode,
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
  initbuf( fileName, mode, logMaxSize, logTrimSize );
}
  
LogBuf::LogBuf(
  const char *	    fileName,
  const char *      outLevel,
  std::ios::openmode    mode,
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
  initbuf( fileName, mode, logMaxSize, logTrimSize );
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
      openLog(std::ios::app);
      return( 0 );
    }

  return( trimLog( stat.getSize(), maxLogSize ) );
}

std::filebuf *
LogBuf::open(
    const char *    name,
    std::ios::openmode   mode,
    size_t	    logMaxSize,
    size_t	    logTrimSize
    )
{
  if( stream != 0 && is_file() ) {
    close();
  }

 maxSize = logMaxSize;
 trimSize = logTrimSize;
 return( open( name, mode ) );
}

std::filebuf *
LogBuf::open(
    const char *    name,
    std::ios::openmode   mode
    )
{
  if( stream != 0 && is_file() ) {
    close();
  }

 logFileName = name;
 openMode = mode;

 FileStat  stat( logFileName );
  
 if( maxSize && stat.good() && ( (size_t)stat.getSize() > maxSize ) )
   trimLog( stat.getSize(), maxSize );
 else
   openLog( mode );
 
 return( (std::filebuf *)(stream) );
}


void
LogBuf::close( void )
{
  sync();
  closeLog();  
}

LogBuf::FilterId
LogBuf::addFilter(
  std::streambuf *		    destBuf,
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

std::streambuf *
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
  
std::streambuf *
LogBuf::delFilter( FilterId id )
{
  sync();
  std::streambuf * dest = 0;
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
  
#if defined( STLUTILS_STD_STREAMBUF_STUPID )
  return( EOF );
#else
  return( stream->underflow() );
#endif
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
  long	    len = pptr() - pbase();
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
#if defined( STLUTILS_STD_STREAMBUF_STUPID )
	      teeStream->pubsync();
#else
	      teeStream->sync();
#endif
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
#if defined( STLUTILS_STD_STREAMBUF_STUPID )
	      (*them).dest->pubsync();
#else
	      (*them).dest->sync();
#endif
	    }
	}
#if defined( STLUTILS_STD_STREAMBUF_STUPID )
      syncResult = stream->pubsync();
#else
      syncResult = stream->sync();
#endif
    }

  newMesg = false;
  
  setp( pbase(), epptr() );

  if( is_file() && maxSize )
    {
#if defined( STLUTILS_STD_STREAMBUF_STUPID )
      // SUN5 BUG - FIXME - seekoff lies
      size_t curSize = (size_t)stream->pubseekoff( 0, std::ios::end, std::ios::out );
      // FileStat fdStat( logFd );
      
      // size_t curSize = (fdStat.good() ? fdStat.getSize() : 0 );
#else  
      size_t curSize = (size_t)stream->seekoff( 0, std::ios::cur, std::ios::out );
#endif

#if defined( DEBUG_LOG_TRIM )
      std::cerr << "\nlog size: max(" << maxSize
	   << ") cur (" << curSize << ")"
	   << endl;
#endif
      
      if( curSize > maxSize )
	{
	  closeLog();
	  trimLog( curSize, maxSize );
	}
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

std::ostream &
LogBuf::dumpInfo( 
  std::ostream &	dest,
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
  
  setbuf( buffer, LOGBUF_SIZE );
  setp( buffer, buffer + LOGBUF_SIZE );
}

void
LogBuf::initbuf( std::streambuf * outStream )
{
  initLogBuffer();
  
  stream    	= outStream;  
  streamIsFile 	= false;
  teeStream 	= 0;  
}

void
LogBuf::initbuf(
  const char *	    fileName,
  std::ios::openmode	    mode,
  size_t	    logMaxSize,
  size_t	    logTrimSize
  )
{
  initLogBuffer();

  stream	= 0;
  streamIsFile  = true;
  teeStream 	= 0;  
  
  open( fileName, mode, logMaxSize, logTrimSize );
 
}

std::streamsize
LogBuf::sendToStream( std::streambuf * dest, char * base, std::streamsize len )
{
  std::streamsize total = 0;
  std::streamsize cnt = 0;
  
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
// the openMask lets me reopen in std::ios::app when I have to
// reopen the file.
//
std::filebuf *
LogBuf::openLog( std::ios::openmode openMask )
{
  std::filebuf * file = new std::filebuf();

  streamIsFile = true;

  int prevMask = umask( 0 );

  // FileStat stat( logFileName );
  
  stream = file->open( logFileName,
		       (std::ios::openmode)(openMode | openMask) );

  umask( prevMask );

  if( ! stream ) {
      errorDesc << "open '" << logFileName
		<< "' mode: " << IosOpenModeToString( openMode )
		<< strerror( errno ) ;
      
      delete file;
      file = 0;
  } else {
#if defined( DEBUG_SEEK ) 
    int logFd = file->fd();
    size_t curSize = (size_t)stream->pubseekoff( 0, std::ios::cur, std::ios::out );
    size_t fcurSize = (size_t)file->pubseekoff( 0, std::ios::cur, std::ios::out );
    size_t fendSize = (size_t)file->pubseekoff( 0, std::ios::end, std::ios::out );
    FileStat fdStat( logFd );
    
    std::cerr << "Log size:\n"
	 << "   stat: " << (stat.good() ? stat.getSize() : 0) << '\n'
	 << "    cur: " << curSize << '\n'
	 << "   fcur: " << fcurSize << '\n'
	 << "   fend: " << fendSize << '\n'
	 << "     fd: " << logFd << '\n'
	 << "  fstat: " << fdStat.getSize() << '\n'
	 << endl;
#endif
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
      openLog( std::ios::app );
      errorDesc << "rename '"
		<< logFileName
		<< "' to '"
		<< tmpFn << "' failed - " << strerror( errno )
	;
      return( 0 );
    }
  
  std::ifstream  in( tmpFn );
  
  if( ! in.good() )
    {
      errorDesc << "open read '" << tmpFn << "' failed - "
		<< strerror( errno )
	;
      rename( tmpFn, logFileName );
      openLog( std::ios::app );
      return( 0 );
    }

  std::ofstream  out( logFileName, openMode );

  if( ! out.good() )
    {
      errorDesc << "open write '" << logFileName << "' failed - "
		<< strerror( errno )
	;
      rename( tmpFn, logFileName );
      openLog( std::ios::app );
      return( 0 );
    }

  size_t  trimAmount = ( trimSize ? trimSize : maxLogSize / 4 );

  // std::cerr << "seek: " << (curSize - maxLogSize) + trimAmount << endl;
  
  in.seekg( (curSize - maxLogSize) + trimAmount );

  if( ! in.good() )
    {
      in.close();
      out.close();
      rename( tmpFn, logFileName );
      openLog( std::ios::app );
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

  std::streampos newSize = out.tellp();
  out.close();
  in.close();

  remove( tmpFn );
  openLog( std::ios::app );
  
  return( curSize - newSize );
}

void
LogBuf::closeLog( void )
{
  if( is_file() && stream != 0 )
    {
      std::filebuf * file = (std::filebuf *)stream;
      
      file->close();
      delete file;
      stream = 0;
    }
}



//
// File:        Log.C
// Project:	Clue
// Desc:        
//              
//  Compiled source for Log class.
//
// Author:      Paul Houghton x2309 - (houghton@shoe)
// Created:     03/14/94 12:22 
//
// Revision History: (See end of file for Revision Log)
//

#include "Log.hh"
#include "DateTime.hh"
#include <cstdio>

#if defined( CLUE_DEBUG )
#include "Log.ii"
#endif

CLUE_VERSION(
  Log,
  "$Id$" );


Log * _LibLog = 0;

LogLevel::CommonLevelMap	    Log::commonLevelMap;

Log::Log(
  ostream & 	    outstr,
  LogLevel::Level   out,
  bool		    stampLevel,
  bool		    stampTime,
  bool		    stampLoc
  )
  : ostream( new LogBuf( out, outstr.rdbuf() ) ),
    timeStamp( stampTime ),
    levelStamp( stampLevel ),
    locStamp( stampLoc ),
    localTimeStamp( true )
{
  tie( &outstr );
}

Log::Log(
  ostream & 	outstr,
  const char *	out,
  bool		stampLevel,
  bool		stampTime,
  bool		stampLoc
  )
  : ostream( new LogBuf( out, outstr.rdbuf() ) ),
    timeStamp( stampTime ),
    levelStamp( stampLevel ),
    locStamp( stampLoc ),
    localTimeStamp( true )
{
  tie( &outstr );
}

Log::Log(
  const char *	    fileName,
  LogLevel::Level   out,
  ios::open_mode    mode,
  int		    prot,
  bool		    stampLevel,
  bool		    stampTime,
  bool		    stampLoc,
  size_t	    maxSize,
  size_t	    trimSize
  )
  : ostream( new LogBuf(fileName, out, mode, prot, maxSize, trimSize ) ),
    timeStamp( stampTime ),
    levelStamp( stampLevel ),
    locStamp( stampLoc ),
    localTimeStamp( true )
{
  if( rdbuf() && ! rdbuf()->is_open() )
    setstate( ios::badbit );
}

Log::Log(
  const char *	    fileName,
  const char *	    out,
  ios::open_mode    mode,
  int		    prot,
  bool		    stampLevel,
  bool		    stampTime,
  bool		    stampLoc,
  size_t	    maxSize,
  size_t	    trimSize
  )
  : ostream( new LogBuf(fileName, out, mode, prot, maxSize, trimSize ) ),
    timeStamp( stampTime ),
    levelStamp( stampLevel ),
    locStamp( stampLoc ),
    localTimeStamp( true )
{
  if( rdbuf() && ! rdbuf()->is_open() )
    setstate( ios::badbit );
}

Log::~Log( void )
{
  delete rdbuf();
}

Log &
Log::level( LogLevel::Level current, const char * srcFile, long srcLine )
{
  if( rdbuf()->sync() == EOF )
    {
      setstate(failbit|eofbit);
      return( *this );
    }
  
  rdbuf()->setCurrentLevel( current );

  if( timeStamp )
    {
      DateTime  now(time(0), localTimeStamp);

      *this << now << ' ';
    }

  if( levelStamp )
    {
      *this << rdbuf()->getLogLevel() << ' ';
    }

  if( locStamp && srcFile )
    {
      *this << srcFile << ':' << srcLine << ' ';
    }
  
  return( *this );
}

Log &
Log::level( const char * lvl, const char * srcFile, long srcLine )
{
  if( rdbuf()->sync() == EOF )
    {
      setstate( failbit | eofbit );
      return( *this );
    }
  
  rdbuf()->setCurrentLevel( lvl );

  if( timeStamp )
    {
      DateTime now(time(0), localTimeStamp );

      *this << now << ' ';
    }

  if( levelStamp )
    {
      *this << rdbuf()->getLogLevel() << ' ';
    }
  
  if( locStamp && srcFile )
    {
      *this << srcFile << ':' << srcLine << ' ';
    }
  
  return( *this );
}

size_t
Log::trim( size_t maxSize )
{
  return( rdbuf()->trim( maxSize ) );
}

void
Log::setFileName(
  const char *	    outFn,
  ios::open_mode    mode,
  int		    prot
  )
{
  open( outFn, mode, prot );
}

void
Log::open(
  const char *	    outFn,
  ios::open_mode    mode,
  int		    prot
  )
{
  rdbuf()->close();
  
  if( rdbuf()->open( outFn, mode, prot ) != 0 )
    clear();
  else
    setstate( badbit );
}

void
Log::close( void )
{
  if( rdbuf()->sync() == EOF )
    {
      setstate( eofbit | failbit );
    }
  
  rdbuf()->close();

  if( rdbuf() && rdbuf()->is_file() )
    setstate( badbit );
  
}


bool
Log::filter( const char * regex )
{
  return( rdbuf()->filter( regex ) );
}

LogBuf::FilterId
Log::addFilter(
  streambuf *	    dest,
  LogLevel::Level   outLevel,
  const char *	    regex
  )
{
  return( rdbuf()->addFilter( dest, outLevel, regex ) );
}

streambuf *
Log::getFilterStream( LogBuf::FilterId filter )
{
  return( rdbuf()->getFilterStream( filter ) );
}

LogLevel::Level
Log::getFilterLogLevel( LogBuf::FilterId filter )
{
  return( rdbuf()->getFilterLogLevel( filter ) );
}

const char *
Log::getFilterRegex( LogBuf::FilterId filter )
{
  return( rdbuf()->getFilterRegex( filter ) );
}

streambuf *
Log::delFilter( LogBuf::FilterId id )
{
  return( rdbuf()->delFilter( id ) );
}

bool
Log::tieCommonLogger( bool setStrings )
{
  if( commonLevelMap.size() == 0 )
    {
      commonLevelMap[ LOG_ERROR ] = LogLevel::Error;
      commonLevelMap[ LOG_WARN  ] = LogLevel::Warn;
      commonLevelMap[ LOG_APP1  ] = LogLevel::App1;
      commonLevelMap[ LOG_APP2  ] = LogLevel::App2;
      commonLevelMap[ LOG_APP3  ] = LogLevel::App3;
      commonLevelMap[ LOG_APP4  ] = LogLevel::App4;
      commonLevelMap[ LOG_APP5  ] = LogLevel::App5;
      commonLevelMap[ LOG_APP6  ] = LogLevel::App6;
      commonLevelMap[ LOG_LIB1  ] = LogLevel::Lib1;
      commonLevelMap[ LOG_LIB2  ] = LogLevel::Lib2;
      commonLevelMap[ LOG_LIB3  ] = LogLevel::Lib3;
      commonLevelMap[ LOG_LIB4  ] = LogLevel::Lib4;
      commonLevelMap[ LOG_INFO  ] = LogLevel::Info;
      commonLevelMap[ LOG_TEST  ] = LogLevel::Test;
      commonLevelMap[ LOG_DEBUG ] = LogLevel::Debug;
      commonLevelMap[ LOG_FUNCT ] = LogLevel::Funct;
    }

  if( setStrings )
    {
      LogLevel::setName( LogLevel::Error, LogLevelString( LOG_ERROR ) );
      LogLevel::setName( LogLevel::Warn,  LogLevelString( LOG_WARN ) );
      
      LogLevel::setName( LogLevel::App1,  LogLevelString( LOG_APP1 ) );
      LogLevel::setName( LogLevel::App2,  LogLevelString( LOG_APP2 ) );
      LogLevel::setName( LogLevel::App3,  LogLevelString( LOG_APP3 ) );
      LogLevel::setName( LogLevel::App4,  LogLevelString( LOG_APP4 ) );
      LogLevel::setName( LogLevel::App5,  LogLevelString( LOG_APP5 ) );
      LogLevel::setName( LogLevel::App6,  LogLevelString( LOG_APP6 ) );
      
      LogLevel::setName( LogLevel::Lib1, LogLevelString( LOG_LIB1 ) );
      LogLevel::setName( LogLevel::Lib2, LogLevelString( LOG_LIB2 ) );
      LogLevel::setName( LogLevel::Lib3, LogLevelString( LOG_LIB3 ) );
      LogLevel::setName( LogLevel::Lib4, LogLevelString( LOG_LIB4 ) );
  
      LogLevel::setName( LogLevel::Info,  LogLevelString( LOG_INFO ) );
      LogLevel::setName( LogLevel::Test,  LogLevelString( LOG_TEST ) );
      LogLevel::setName( LogLevel::Debug, LogLevelString( LOG_DEBUG ) );
      LogLevel::setName( LogLevel::Funct, LogLevelString( LOG_FUNCT ) );
    }

  LoggerSetOutputLevel( LOG_SET, LOG_ALL );
  LoggerSetFunct( commonLog, this );

  return( true );
}
  
      
      
bool
Log::good( void ) const
{
  return( rdbuf() != 0 && rdbuf()->good() && ios::good() );
}

const char *
Log::error( void ) const
{
  static Str errStr;

  errStr = getClassName();

  if( good() )
    {
       errStr += ": Ok";
    }
  else
    {
      size_t eSize = errStr.length();

      if( ! rdbuf() )
	errStr += ": no 'streambuf'";

      if( rdbuf() && ! rdbuf()->good() )
	errStr << ": " << rdbuf()->error() ;
      
      if( ! ios::good() )
	{
	  if( ios::rdstate() & ios::eofbit )
	    errStr += ": EOF bit set";
	  if( ios::rdstate() & ios::failbit )
	    errStr += ": FAIL bit set";
	  if( ios::rdstate() & ios::badbit )
	    errStr += ": BAD bit set";
	}
      
      if( eSize == errStr.length() )
	errStr += ": unknown error";      
    }

  return( errStr );
}
  
const char *
Log::getClassName( void ) const
{
  return( "Log" );
}

const char *
Log::getVersion( bool withPrjVer ) const
{
  if( rdbuf() )
    return( version.getVer( withPrjVer, rdbuf()->getVersion( false ) ) );
  else
    return( version.getVer( withPrjVer ) );
}

#define bool2str( _b_ ) ((_b_) == true ? "on" : "off" )

ostream &
Log::dumpInfo(
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << Log::getClassName() << ":\n"
	 << Log::getVersion() << '\n';
  
  if( ! Log::good() )
    dest << prefix << "Error: " << Log::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  dest << prefix << "timeStamp:    " << bool2str( timeStamp ) << '\n'
       << prefix << "levelStamp:   " << bool2str( levelStamp ) << '\n'
       << prefix << "locStamp:     " << bool2str( locStamp ) << '\n'
    ;
  
  if( rdbuf() )
    {
      Str pre;
      pre = prefix;
      pre += "rdbuf: " ;
      pre += rdbuf()->getClassName() ;
      pre += "::";
      
      rdbuf()->dumpInfo( dest, pre, false );
    }
  
  dest << '\n';
  
  return( dest  );
}

void
Log::commonLog(
   void *	    closure,
   const char *     srcFileName,
   long		    srcLineNumber,
   LogLevelBit	    level,
   const char *     mesgFmt,
   va_list	    mesgArgs
   )
{
  Log *	    self = (Log *)closure;

  static char logMesg[ 4096 ];

  vsprintf( logMesg, mesgFmt, mesgArgs );
    
  if( ! self )
    {
      cerr << "Log::commonLog - no self!\n"
	   << logMesg << endl;
    }
  else
    {
      self->level( commonLevelMap[ level ],
		   srcFileName,
		   srcLineNumber ) << logMesg;
      self->flush();
    }
}

//
// Revision Log:
//
// $Log$
// Revision 3.7  1997/04/26 14:11:09  houghton
// Added tieCommonLogger().
// Added commonLog().
//
// Revision 3.6  1997/04/04 20:52:54  houghton
// Added mode & prot specificers to open log file.
// Added LogBuf error checking.
//
// Revision 3.5  1997/04/04 03:09:05  houghton
// Moved constructors to here from .ii.
// Added getFilterStream
// Added getFilterLogLevel
// Added getFilterRegex
//
// Revision 3.4  1997/03/21 15:37:54  houghton
// Bug-Fix: date stamp was not using localTimeStamp.
//
// Revision 3.3  1997/03/21 12:21:16  houghton
// Added localTimeStamp var to determin if logtime stamp should be
//     local or GMT.
//
// Revision 3.2  1997/03/03 14:36:23  houghton
// Removed support for RW Tools++
//
// Revision 3.1  1996/11/14 01:23:45  houghton
// Changed to Release 3
//
// Revision 2.9  1996/11/13 16:25:41  houghton
// Changed include lines to use "file" instead of <file> to
//     accomidate rpm.
// Changed to use ios::setstate (instead of clear) to be compilant
//     with the ios class beheavior defined by the standard.
// Bug-Fix: Fixed some compile errors that were do to the change
//     to RWCString.
//
// Revision 2.8  1996/11/11 13:33:47  houghton
// Changed to use RWCString instead of strstream where possible because
//     of an inconsitancy in the public member of strstream.
//
// Revision 2.7  1996/11/04 13:39:33  houghton
// Restructure header comments layout.
// Changed to use rwtime instead of DateTime for time stamp output.
//     (as required by Mike Alexandar).
// Changed to work with modifications to LogBuf class.
// Changed error to use a strstream instead of an Str
//     (as required by Mike Alexandar).
//
// Revision 2.6  1996/10/22 22:05:33  houghton
// Change: Added locStamp to turn on/off output of src file & line.
//
// Revision 2.5  1996/04/27 13:02:32  houghton
// Added global _LibLog variable.
//
// Revision 2.4  1995/12/04 11:17:23  houghton
// Bug Fix - Can now compile with out '-DCLUE_DEBUG'.
//
// Revision 2.3  1995/11/12  18:49:31  houghton
// Bug fix - current (not lvl).
//
// Revision 2.2  1995/11/12  18:00:02  houghton
// Added srcFile, srcLine args to level().
//
// Revision 2.1  1995/11/10  12:40:42  houghton
// Change to Version 2
//
// Revision 1.6  1995/11/05  15:28:36  houghton
// Revised
//
//

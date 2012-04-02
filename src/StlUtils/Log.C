/**
   File:        Log.C
   Project:	StlUtils ()
   Desc:        
                
    Compiled source for Log class.
  
   Author:      Paul Houghton - (houghton@shoe)
   Created:     03/14/94 12:22 
  
   Revision History: (See end of file for Revision Log)
  
    $Author$ 
    $Date$ 
    $Name$ 
    $Revision$ 
    $State$ 
**/

#include "Log.hh"
#include "DateTime.hh"
#include "StringUtils.hh"
#include <cstdio>

#if defined( STLUTILS_DEBUG )
#include "Log.ii"
#endif

STLUTILS_VERSION(
  Log,
  "$Id$ " );


Log * _LibLog = 0;

static LogLevel::CommonLevelMap *	    commonLevelMap = 0;

const int	Log::openprot( 0666 );

Log::Log(
  ostream & 	    outstr,
  LogLevel::Level   outLvl,
  bool		    stampLevel,
  bool		    stampTime,
  bool		    stampLoc
  )
  : ostream( new LogBuf( outLvl, outstr.rdbuf() ) ),
    timeStamp( stampTime ),
    levelStamp( stampLevel ),
    locStamp( stampLoc ),
    localTimeStamp( true )
{
  tie( &outstr );
}

Log::Log(
  ostream & 	outstr,
  const char *	outLvl,
  bool		stampLevel,
  bool		stampTime,
  bool		stampLoc
  )
  : ostream( new LogBuf( outLvl, outstr.rdbuf() ) ),
    timeStamp( stampTime ),
    levelStamp( stampLevel ),
    locStamp( stampLoc ),
    localTimeStamp( true )
{
  tie( &outstr );
}

Log::Log(
  const char *	    fileName,
  LogLevel::Level   outLvl,
  ios::openmode	    mode,
  bool		    stampLevel,
  bool		    stampTime,
  bool		    stampLoc,
  size_t	    maxSize,
  size_t	    trimSize
  )
  : ostream( new LogBuf(fileName, outLvl, mode, maxSize, trimSize ) ),
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
  const char *	    outLvl,
  ios::openmode	    mode,
  bool		    stampLevel,
  bool		    stampTime,
  bool		    stampLoc,
  size_t	    maxSize,
  size_t	    trimSize
  )
  : ostream( new LogBuf(fileName, outLvl, mode, maxSize, trimSize ) ),
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
Log::level(
  const LogLevel::Level &   current,
  const char *		    srcFile,
  long			    srcLine,
  time_t		    when
  )
{
  if( rdbuf()->sync() == EOF )
    {
      setstate(failbit|eofbit);
      return( *this );
    }
  
  rdbuf()->setCurrentLevel( current );

  if( timeStamp )
    {
      DateTime  now( when, localTimeStamp);

      *this << now << ' ';
    }

  if( levelStamp )
    {
      *this << rdbuf()->getLogLevel() << ' ';
    }

  if( locStamp && srcFile )
    {
      
      *this << basename( srcFile ) << ':' << srcLine << ' ';
    }
  
  return( *this );
}

	  
Log &
Log::level(
  const char *	lvl,
  const char *	srcFile,
  long		srcLine,
  time_t	when
  )
{
  if( rdbuf()->sync() == EOF )
    {
      setstate( failbit | eofbit );
      return( *this );
    }
  
  rdbuf()->setCurrentLevel( lvl );

  if( timeStamp )
    {
      DateTime now(when, localTimeStamp );

      *this << now << ' ';
    }

  if( levelStamp )
    {
      *this << rdbuf()->getLogLevel() << ' ';
    }
  
  if( locStamp && srcFile )
    {
      *this << basename( srcFile ) << ':' << srcLine << ' ';
    }
  
  return( *this );
}

Log &
Log::appendFile(
  const LogLevel::Level &   current,
  const char *		    srcFile,
  long			    srcLine,
  const char *		    fileName 
  )
{
  level( current, srcFile, srcLine );

  ifstream  infile( fileName );

  if( ! infile.good() )
    {
      (*this) << "appending '" << fileName << "' open failed - "
	      << strerror( errno ) << endl;
    }
  else
    {
      (*this) << "contents of '" << fileName << "':\n";
      Str   line;
      while( line.getline( infile ).good() )
	{
	  (*this) << "    " << line << '\n';
	}
      (*this) << "end of '" << fileName << '\'' << endl;
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
  ios::openmode    mode,
  int		    prot
  )
{
  open( outFn, mode, prot );
}

void
Log::open(
  const char *	    outFn,
  ios::openmode    mode,
  int		    prot
  )
{
  rdbuf()->close();
  
  if( rdbuf()->open( outFn, mode ) != 0 )
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
  streambuf *		    dest,
  const LogLevel::Level &   outLevel,
  const char *		    regex
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

extern "C"  {
  static void	commonLog( void *	closure,
			   const char * srcFileName,
			   long		srcLineNumber,
			   LogLevelBit	level,
			   const char * mesgFmt,
			   va_list	mesgArgs );
};
  
const LogLevel::CommonLevelMap &
Log::getCommonLevelMap( void )
{
  if( ! commonLevelMap )
    initCommonLevelMap();
  
  return( *commonLevelMap );
}


bool
Log::tieCommonLogger( bool setStrings )
{
  if( ! commonLevelMap )
    {
      initCommonLevelMap();
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
  return( rdbuf() != 0 && rdbuf()->good() &&
#if defined( STLUTILS_HAS_CONST_IOSGOOD )
	  ios::good()
#else
	  ios::state == 0
#endif
	  );
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

#if defined( STLUTILS_HAS_CONST_IOSRDSTATE )
      if( ! ios::good() )
	{
	  if( ios::rdstate() & ios::eofbit )
	    errStr += ": EOF bit set";
	  if( ios::rdstate() & ios::failbit )
	    errStr += ": FAIL bit set";
	  if( ios::rdstate() & ios::badbit )
	    errStr += ": BAD bit set";
	}
#else
      if( state != 0 )
	{
	  if( ios::state & ios::eofbit )
	    errStr += ": EOF bit set";
	  if( ios::state & ios::failbit )
	    errStr += ": FAIL bit set";
	  if( ios::state & ios::badbit )
	    errStr += ": BAD bit set";
	}
#endif
      
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
Log::initCommonLevelMap()
{
  if( ! commonLevelMap )
    {
      commonLevelMap = new LogLevel::CommonLevelMap;
      
      (*commonLevelMap)[ LOG_ERROR ] = LogLevel::Error;
      (*commonLevelMap)[ LOG_WARN  ] = LogLevel::Warn;
      (*commonLevelMap)[ LOG_APP1  ] = LogLevel::App1;
      (*commonLevelMap)[ LOG_APP2  ] = LogLevel::App2;
      (*commonLevelMap)[ LOG_APP3  ] = LogLevel::App3;
      (*commonLevelMap)[ LOG_APP4  ] = LogLevel::App4;
      (*commonLevelMap)[ LOG_APP5  ] = LogLevel::App5;
      (*commonLevelMap)[ LOG_APP6  ] = LogLevel::App6;
      (*commonLevelMap)[ LOG_LIB1  ] = LogLevel::Lib1;
      (*commonLevelMap)[ LOG_LIB2  ] = LogLevel::Lib2;
      (*commonLevelMap)[ LOG_LIB3  ] = LogLevel::Lib3;
      (*commonLevelMap)[ LOG_LIB4  ] = LogLevel::Lib4;
      (*commonLevelMap)[ LOG_INFO  ] = LogLevel::Info;
      (*commonLevelMap)[ LOG_TEST  ] = LogLevel::Test;
      (*commonLevelMap)[ LOG_DEBUG ] = LogLevel::Debug;
      (*commonLevelMap)[ LOG_FUNCT ] = LogLevel::Funct;
    }
}

static
void
commonLog(
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
      LogLevel::Level curLvl( self->getCurrent() );
      
      self->level( (*commonLevelMap)[ level ],
		   srcFileName,
		   srcLineNumber ) << logMesg;
      
      if( self->rdbuf()->sync() == EOF )
	self->setstate( ios::failbit | ios::eofbit );
  
      self->rdbuf()->setCurrentLevel( curLvl );
    }
}


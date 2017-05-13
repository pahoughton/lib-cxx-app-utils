// 1994-03-14 (cc) Paul Houghton <paul4hough@gmail.com>

#include "Log.hpp"
#include "DateTime.hpp"
#include "StringUtils.hpp"
#include <cstdio>

namespace clue {

Log * _clueLibLog = 0;

static LogLevel::CommonLevelMap *	    commonLevelMap = 0;

Log::Log(
  std::ostream &    outstr,
  LogLevel::Level   outLvl,
  bool		    stampLevel,
  bool		    stampTime,
  bool		    stampLoc
  )
  : std::ostream( new LogBuf( outLvl, outstr.rdbuf() ) ),
    timeStamp( stampTime ),
    levelStamp( stampLevel ),
    locStamp( stampLoc ),
    localTimeStamp( true )
{
  tie( &outstr );
}

Log::Log(
  std::ostream & 	outstr,
  const char *	outLvl,
  bool		stampLevel,
  bool		stampTime,
  bool		stampLoc
  )
  : std::ostream( new LogBuf( outLvl, outstr.rdbuf() ) ),
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
  std::ios::openmode	    mode,
  bool		    stampLevel,
  bool		    stampTime,
  bool		    stampLoc,
  size_t	    maxSize,
  size_t	    trimSize
  )
  : std::ostream( new LogBuf(fileName, outLvl, mode, maxSize, trimSize ) ),
    timeStamp( stampTime ),
    levelStamp( stampLevel ),
    locStamp( stampLoc ),
    localTimeStamp( true )
{
  if( rdbuf() && ! rdbuf()->is_open() )
    setstate( std::ios::badbit );
}

Log::Log(
  const char *	    fileName,
  const char *	    outLvl,
  std::ios::openmode	    mode,
  bool		    stampLevel,
  bool		    stampTime,
  bool		    stampLoc,
  size_t	    maxSize,
  size_t	    trimSize
  )
  : std::ostream( new LogBuf(fileName, outLvl, mode, maxSize, trimSize ) ),
    timeStamp( stampTime ),
    levelStamp( stampLevel ),
    locStamp( stampLoc ),
    localTimeStamp( true )
{
  if( rdbuf() && ! rdbuf()->is_open() )
    setstate( std::ios::badbit );
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

  std::ifstream  infile( fileName );

  if( ! infile.good() )
    {
      (*this) << "appending '" << fileName << "' open failed - "
	      << strerror( errno ) << std::endl;
    }
  else
    {
      (*this) << "contents of '" << fileName << "':\n";
      Str   line;
      while( line.getline( infile ).good() )
	{
	  (*this) << "    " << line << '\n';
	}
      (*this) << "end of '" << fileName << '\'' << std::endl;
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
  std::ios::openmode    mode,
  int		    prot
  )
{
  open( outFn, mode, prot );
}

void
Log::open(
  const char *	    outFn,
  std::ios::openmode    mode,
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
  std::streambuf *		    dest,
  const LogLevel::Level &   outLevel,
  const char *		    regex
  )
{
  return( rdbuf()->addFilter( dest, outLevel, regex ) );
}

std::streambuf *
Log::getFilterStream( LogBuf::FilterId filter )
{
  return( rdbuf()->getFilterStream( filter ) );
}

LogLevel::Level
Log::getFilterLogLevel( LogBuf::FilterId filter )
{
  return( rdbuf()->getFilterLogLevel( filter ) );
}

std::streambuf *
Log::delFilter( LogBuf::FilterId id )
{
  return( rdbuf()->delFilter( id ) );
}

bool
Log::good( void ) const
{
  return( rdbuf() != 0
	  && rdbuf()->good()
	  && std::ios::good()
	  );
}

const char *
Log::error( void ) const
{
  static Str errStr;

  errStr = "Log";

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

      if( ! std::ios::good() )
	{
	  if( std::ios::rdstate() & std::ios::eofbit )
	    errStr += ": EOF bit set";
	  if( std::ios::rdstate() & std::ios::failbit )
	    errStr += ": FAIL bit set";
	  if( std::ios::rdstate() & std::ios::badbit )
	    errStr += ": BAD bit set";
	}

      if( eSize == errStr.length() )
	errStr += ": unknown error";
    }

  return( errStr );
}

#define bool2str( _b_ ) ((_b_) == true ? "on" : "off" )

std::ostream &
Log::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

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
      pre += "rdbuf:" ;

      rdbuf()->dumpInfo( dest, pre );
    }

  dest << '\n';

  return( dest  );
}


}; // namespace clue

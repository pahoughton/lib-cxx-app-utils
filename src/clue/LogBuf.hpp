#ifndef _clue_LogBuf_hpp_
#define _clue_LogBuf_hpp_
/* 1995-01-29 (cc) <paul4hough@gmail.com>

   This is a specialized streambuf used by Log to
   output log messages.
*/

#include <clue/LogLevel.hpp>
#include <clue/FilePath.hpp>

#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>

namespace clue {

class LogBuf : public std::streambuf
{

public:

  typedef long	FilterId;

  LogBuf( LogLevel::Level   outLevel,
	  std::streambuf *  outStream );

  LogBuf( const char *	    outLevel,
	  std::streambuf *  outStream );

  LogBuf( const char *		fileName,
	  LogLevel::Level	outLevel = LogLevel::Error,
	  std::ios::openmode	mode = std::ios::app,
	  size_t		maxSize = 0,
	  size_t		trimSize = 0 );

  LogBuf( const char *		fileName,
	  const char *		outLevel,
	  std::ios::openmode	mode = std::ios::app,
	  size_t		maxSize = 0,
	  size_t		trimSize = 0 );

  virtual ~LogBuf( void );

  inline LogLevel::Level    setCurrentLevel( const LogLevel::Level & level );
  inline LogLevel::Level    setCurrentLevel( const char * level );

  inline LogLevel::Level    setOutputLevel( const LogLevel::Level & level );
  inline LogLevel::Level    setOutputLevel( const char * level );

  inline const LogLevel &   getLogLevel( void ) const;

  size_t		trim( size_t maxSize = 0 );

  inline size_t	        setMaxSize( size_t maxSize );
  inline size_t		setTrimSize( size_t trimSize );
  inline size_t		getMaxSize( void ) const;
  inline size_t		getTrimSize( void ) const;

  inline std::streambuf *	tee( std::streambuf * teeStreambuf );

  inline const FilePath &	getLogFileName( void ) const;

  std::filebuf *	open( const char *	    name,
			      std::ios::openmode    mode,
			      size_t		    maxSize,
			      size_t		    trimSize );

  std::filebuf *	open( const char *	    name,
			      std::ios::openmode    mode );

  void			close (void);

  inline bool		is_file( void ) const;
  inline bool		is_open( void ) const;

  bool		    filter( const char * regex );

  FilterId	    addFilter( std::streambuf *		destBuf,
			       const LogLevel::Level &	outputLevel,
			       const char *		regex = 0 );

  std::streambuf *  getFilterStream( LogBuf::FilterId filter );
  LogLevel::Level   getFilterLogLevel( LogBuf::FilterId filter );
  std::streambuf *  delFilter( FilterId id );

  inline bool	    willOutput( const LogLevel::Level & lvl ) const;

  // streambuf virtuals
  virtual int	    overflow(int=EOF);
  virtual int	    sync() ;

  virtual bool		    good( void ) const;
  virtual const char *	    error( void ) const;
  virtual std::ostream &    dumpInfo( std::ostream &	dest = std::cerr,
				      const char *	prefix = "    " ) const;

  static const FilterId	    badFilterId;

  // do NOT use this.
  class Filter
  {
  public:
    inline Filter( void );
    inline Filter( const Filter & from );
    inline ~Filter( void );

    inline Filter & operator = ( const Filter & rhs );

    std::streambuf *	dest;
    LogLevel::Level	outputLevel;
    std::regex *	regex;
  };
  // end do NOT use this

protected:

  void initLogBuffer( void );
  void initbuf( std::streambuf * outStream );
  void initbuf( const char * fn,
		std::ios::openmode mode,
		size_t m,
		size_t t );

  std::streamsize	sendToStream( std::streambuf *	dest,
				      char *		base,
				      std::streamsize	len );

  std::filebuf *    openLog( std::ios::openmode modeMask );
  size_t	    trimLog( size_t curSize, size_t maxLogSize );
  void		    closeLog( void );

  typedef std::vector< Filter > FilterList;

  FilePath		logFileName;
  size_t		maxSize;
  size_t		trimSize;
  std::ios::openmode	openMode;
  bool			streamIsFile;

  char *	    buffer;

  std::streambuf *  stream;
  std::streambuf *  teeStream;

  LogLevel	    logLevel;
  std::regex *	    regex;
  bool		    newMesg;

  FilterList	    filters;

  Str		    errorDesc;
private:

};


inline LogLevel::Level
LogBuf::setCurrentLevel( const LogLevel::Level & cur )
{
  newMesg = true;
  return( logLevel.setCurrent( cur ) );
}

inline LogLevel::Level
LogBuf::setCurrentLevel( const char * cur )
{
  newMesg = true;
  return( logLevel.setCurrent( cur ) );
}

inline LogLevel::Level
LogBuf::setOutputLevel( const LogLevel::Level & out )
{
  newMesg = true;
  return( logLevel.setOutput( out ) );
}

inline LogLevel::Level
LogBuf::setOutputLevel( const char * out )
{
  newMesg = true;
  return( logLevel.setOutput( out ) );
}

inline
const LogLevel &
LogBuf::getLogLevel( void ) const
{
  return( logLevel );
}

inline
size_t
LogBuf::setMaxSize( size_t size )
{
  size_t old = maxSize;
  maxSize = size;
  trim();
  return( old );
}

inline
size_t
LogBuf::setTrimSize( size_t size )
{
  size_t old = trimSize;
  trimSize = size;
  return( old );
}

inline
size_t
LogBuf::getMaxSize( void ) const
{
  return( maxSize );
}

inline
size_t
LogBuf::getTrimSize( void ) const
{
  return( trimSize );
}

inline
std::streambuf *
LogBuf::tee( std::streambuf * teeStreambuf )
{
  sync();
  std::streambuf * old = teeStream;
  teeStream = teeStreambuf;
  return( old );
}

inline
bool
LogBuf::is_file( void ) const
{
  return( streamIsFile );
}

inline
bool
LogBuf::is_open( void ) const
{
  return( stream != 0 );
}

inline
const FilePath &
LogBuf::getLogFileName( void ) const
{
  return( logFileName );
}

inline
bool
LogBuf::willOutput( const LogLevel::Level & lvl ) const
{
  if( logLevel.willOutput( lvl ) )
    return( true );

  for( FilterList::const_iterator them = filters.begin();
       them != filters.end();
       ++them )
    {
      if( ! (*them).dest )
	continue;

      if( ((*them).outputLevel & lvl) == true )
	return( true );
    }

  return( false );
}

inline
LogBuf::Filter::Filter( void )
  : dest(0), outputLevel( LogLevel::None ), regex( 0 )
{
};

inline
LogBuf::Filter::Filter( const Filter & from )
  : dest( from.dest ), outputLevel( from.outputLevel )
{
  regex = (from.regex ? new std::regex( *from.regex ) : 0 );
}

inline
LogBuf::Filter::~Filter( void )
{
  if( regex ) delete regex;
};

inline
LogBuf::Filter &
LogBuf::Filter::operator = ( const Filter & rhs )
{
  dest = rhs.dest;
  outputLevel = rhs.outputLevel;
  if( regex ) delete regex;
  regex = new std::regex( *regex );
  return( *this );
}

}; // namespace clue

#endif // ! def _clue_LogBuf_hpp_

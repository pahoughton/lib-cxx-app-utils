#ifndef _clue_Log_hpp_
#define _clue_Log_hpp_
/* 1994-03-14 (cc) Paul Houghton <paul4hough@gmail.com>

   Log is a specialized std::ostream. It provides control over
   how and where the data placed in the log will be output.

   There are two types of control, Levels and Filters.

   Levels are used to indicate the type of log entry,
   (i.e. Debug, Error, Warning) that is placed in the log.

   Filters provide for control over the content of the entry.

   An application can specify what type of entries it
   wants output (i.e. Error | Warning ). It can then
   create any number of log entries and specify the level
   for each one. Only those entries specified for output
   will actually be written to the log.

   Filters can be used to write log entries with a specific
   level and content to any 'streambuf' destination.

**/

#include "LogBuf.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <mutex>

#define LogIf( lg, lvl ) \
  if( (lg)(lvl, __FILE__, __LINE__ ).changeCheckOutput( lvl ) ) (lg)

namespace clue {

class Log : public std::ostream
{

public:

  Log( std::ostream & 	outStream = std::cout,
       LogLevel::Level 	outLevel = ( LogLevel::Error |
				     LogLevel::Warn |
				     LogLevel::Info ),
       bool		stampLevel = true,
       bool		stampTime = true,
       bool		stampLoc = true );

  Log( std::ostream & 	outStream,
       const char *     outLevel,
       bool		stampLevel = true,
       bool		stampTime = true,
       bool		stampLoc = true );

  Log( const char * 	fileName,
       LogLevel::Level 	outLevel = ( LogLevel::Error |
				     LogLevel::Warn |
				     LogLevel::Info ),
       std::ios::openmode mode = (std::ios::openmode)(std::ios::app|
						      std::ios::out),
       bool		stampLevel = true,
       bool		stampTime = true,
       bool		stampLoc = true,
       size_t		maxSize = 0,
       size_t		trimSize = 0 );

  Log( const char * 	fileName,
       const char *	outLevel,
       std::ios::openmode mode = (std::ios::openmode)(std::ios::app|
						      std::ios::out),
       bool		stampLevel = true,
       bool		stampTime = true,
       bool		stampLoc = true,
       size_t		maxSize = 0,
       size_t		trimSize = 0 );

  ~Log( void );

  inline LogLevel::Level    getCurrent( void  ) const;
  inline LogLevel::Level    getOutput( void ) const;

  inline bool	    willOutput( const LogLevel::Level & outLevel ) const;
  inline bool	    changeCheckOutput( const LogLevel::Level & outLevel );


  Log &		level( const LogLevel::Level &  current = LogLevel::Error,
		       const char *		srcFile = 0,
		       long			srcLine = 0 );

  virtual Log &	level( const LogLevel::Level &  current,
		       const char *		srcFile,
		       long			srcLine,
		       time_t			when );

  inline Log &	    operator () ( void );
  inline Log &	    operator () ( const LogLevel::Level &   current );
  inline Log &	    operator () ( const LogLevel::Level &   current,
				  const char *		    srcFile,
				  long			    srcLine );
  inline Log &	    operator () ( const LogLevel::Level &   current,
				  const char *		    srcFile,
				  long			    srcLine,
				  time_t		    when );

  Log &		    level( const char *	    current,
			   const char *	    srcFile = 0,
			   long		    srcLine = 0 );

  virtual Log &	    level( const char *	    current,
			   const char *	    srcFile,
			   long		    srcLine,
			   time_t	    when );

  inline Log &      operator () ( const char *	    current );
  inline Log &      operator () ( const char *	    current,
				  const char *	    srcFile,
				  long		    srcLine );
  inline Log &      operator () ( const char *	    current,
				  const char *	    srcFile,
				  long		    srcLine,
				  time_t	    when );

  Log &	    appendFile( const LogLevel::Level &	current,
			const char *		srcFile,
			long			srcLine,
			const char *		fileName );

  inline bool		    setLevelStamp( bool stamp );
  inline bool		    setTimeStamp( bool stamp );
  inline bool		    setLocStamp( bool stamp );

  inline bool		    getLevelStamp( void ) const;
  inline bool		    getTimeStamp( void ) const;
  inline bool		    getLocStamp( void ) const;

  inline const FilePath &   getLogFileName() const;

  inline LogLevel::Level    setOutputLevel( const LogLevel::Level & output );
  inline LogLevel::Level    setOutputLevel( const char * output );

  inline void		    on( const LogLevel::Level & output );
  inline void		    off( const LogLevel::Level & output );

  inline void 	    	    tee( std::ostream & teeStream = std::cerr );

  inline size_t		    setTrimSize( size_t trimSize );
  inline size_t		    setMaxSize( size_t maxSize );

  inline size_t		    getTrimSize( void ) const;
  inline size_t		    getMaxSize( void ) const;

  size_t	    trim( size_t maxSize = 0 );

  void	    open( const char *	     fileName,
		  std::ios::openmode mode = (std::ios::openmode)(std::ios::out|
								 std::ios::app),
		  int		     prot = 0664 );

  void	    setFileName( const char *	    fileName,
			 std::ios::openmode mode = (std::ios::openmode)(std::ios::out|
									std::ios::app),
			 int		    prot = 0664 );

  void		    close( void );

  bool		    filter( const char * regex );

  LogBuf::FilterId  addFilter( std::streambuf *		destBuf,
			       const LogLevel::Level &	outputLevel,
			       const char *		regex = 0 );

  std::streambuf *  getFilterStream( LogBuf::FilterId filter );
  LogLevel::Level   getFilterLogLevel( LogBuf::FilterId filter );

  std::streambuf *	    delFilter( LogBuf::FilterId id );


  inline LogBuf *	    rdbuf( void );
  inline const LogBuf *	    rdbuf( void ) const;

  // mutex locking

  inline void		 lock( void );
  inline void		 unlock( void );

  virtual bool 		 good( void ) const;
  virtual const char *	 error( void ) const;
  virtual std::ostream & dumpInfo( std::ostream &   dest = std::cerr,
				   const char *	    prefix = "    " ) const;

private:

  Log( const Log & copyFrom );
  Log & operator=( const Log & assignFrom );

  bool		timeStamp;
  bool		levelStamp;
  bool		locStamp;
  bool		localTimeStamp;

  std::mutex	mutex;

};

inline
void
Log::tee( std::ostream & teeStream )
{
  rdbuf()->tee( teeStream.rdbuf() );
}

inline
size_t
Log::setMaxSize( size_t max )
{
  return( rdbuf()->setMaxSize( max ) );
}

inline
size_t
Log::setTrimSize( size_t size )
{
  return( rdbuf()->setTrimSize( size ) );
}

inline
size_t
Log::getMaxSize( void ) const
{
  return( rdbuf()->getMaxSize() );
}

inline
size_t
Log::getTrimSize( void ) const
{
  return( rdbuf()->getTrimSize() );
}


inline Log &
Log::level(
  const LogLevel::Level &   current,
  const char *		    srcFile,
  long			    srcLine
  )
{
  return( level( current, srcFile, srcLine, time(0) ) );
}

inline Log &
Log::level(
  const char *	lvl,
  const char *	srcFile,
  long		srcLine
  )
{
  return( level( lvl, srcFile, srcLine, time(0) ) );
}

inline
Log &
Log::operator () ( void )
{
  return( level( LogLevel::Error ) );
}

inline
Log &
Log::operator () ( const LogLevel::Level & lvl )
{
  return( level( lvl ) );
}

inline
Log &
Log::operator () (
  const LogLevel::Level &   lvl,
  const char *		    srcFile,
  long			    srcLine
  )
{
  return( level( lvl, srcFile, srcLine ) );
}

inline
Log &
Log::operator () (
  const LogLevel::Level &   lvl,
  const char *		    srcFile,
  long			    srcLine,
  time_t		    when
  )
{
  return( level( lvl, srcFile, srcLine, when ) );
}

inline
Log &
Log::operator () ( const char * lvl )
{
  return( level( lvl ) );
}

inline
Log &
Log::operator () ( const char * lvl, const char * srcFile, long srcLine )
{
  return( level( lvl, srcFile, srcLine ) );
}

inline
Log &
Log::operator () (
  const char *	lvl,
  const char *	srcFile,
  long		srcLine,
  time_t	when
  )
{
  return( level( lvl, srcFile, srcLine, when ) );
}

inline
void
Log::on( const LogLevel::Level & outLvl )
{
  rdbuf()->sync();
  rdbuf()->setOutputLevel( getOutput() | outLvl );
}

inline
void
Log::off( const LogLevel::Level & outLvl )
{
  rdbuf()->sync();
  rdbuf()->setOutputLevel( getOutput() & ~outLvl );
}

inline
LogLevel::Level
Log::getCurrent( void ) const
{
  return( rdbuf()->getLogLevel().getCurrent() );
}

inline
LogLevel::Level
Log::getOutput( void  ) const
{
  return( rdbuf()->getLogLevel().getOutput() );
}

inline
bool
Log::willOutput( const LogLevel::Level & outLevel ) const
{
  return( rdbuf()->willOutput( outLevel ) );
}

inline
bool
Log::changeCheckOutput( const LogLevel::Level & newLevel )
{
  if( rdbuf()->sync() == EOF )
    {
      setstate(failbit|eofbit);
    }
  else
    {
      rdbuf()->setCurrentLevel( newLevel );
    }

  return( willOutput( newLevel ) );
}

inline
LogLevel::Level
Log::setOutputLevel( const char * level )
{
  rdbuf()->sync();
  return( rdbuf()->setOutputLevel( level ) );
}

inline
LogLevel::Level
Log::setOutputLevel( const LogLevel::Level & level )
{
  rdbuf()->sync();
  return( rdbuf()->setOutputLevel( level ) );
}

inline
bool
Log::setLevelStamp( bool stamp )
{
  bool old = levelStamp;
  levelStamp = stamp;
  return( old );
}

inline
bool
Log::setTimeStamp( bool stamp )
{
  bool old = timeStamp;
  timeStamp = stamp;
  return( old );
}

inline
bool
Log::setLocStamp( bool stamp )
{
  bool old = locStamp;
  locStamp = stamp;
  return( old );
}

inline
bool
Log::getLevelStamp( void ) const
{
  return( levelStamp );
}

inline
bool
Log::getTimeStamp( void ) const
{
  return( timeStamp );
}

inline
bool
Log::getLocStamp( void ) const
{
  return( locStamp );
}

inline
const FilePath &
Log::getLogFileName( void ) const
{
  return( (*rdbuf()).getLogFileName() );
}

inline
LogBuf *
Log::rdbuf( void )
{
  return( (LogBuf *)(std::ios::rdbuf()) );
}

inline
const LogBuf *
Log::rdbuf( void ) const
{
  return( (const LogBuf *)(std::ios::rdbuf()) );
}

inline
void
Log::lock( void )
{
  mutex.lock();
}

inline
void
Log::unlock( void )
{
  mutex.unlock();
}


}; // namespace clue

/**

  	inline
    	Log( std::ostream &		outStream = std::cout,
    	     LogLevel::Level	outLevel = ( LogLevel::Error |
  				             LogLevel::Warn |
  				             LogLevel::Info ),
    	     bool		stampLevel = true,
    	     bool		stampTime = true,
  	     bool		stampLoc = true );
  	    Default Log Constructor 'outStream' is the destination where
  	    log entries will be written.  'outLevel' is a mask of the
  	    log levels that will be written. 'stampLevel' controls
  	    whether or not the level of a specific entry will be written to
  	    the destination before each log entry. 'stampTime' controls
  	    whether or not the time an entry was created will be written to
  	    the destination before each log entry. 'stampLoc' controls
  	    whether or not the source file and line number will be written
  	    to the destination before each log entry.

  	inline
    	Log( std::ostream &		outStream,
    	     const char *	outLevel,
    	     bool		stampLevel = true,
    	     bool		stampTime = true,
  	     bool		stampLoc = true );
  	    Log Constructor that uses a (const char *) for the output level.
  	    'outStream' is the destination where log entries will be written
  	    'outLevel' is a char string for the mask of the log levels
            that will be written. 'stampLevel' controls whether or not
            the level of a specific entry will be written to the destination
  	    before each log entry. 'stampTime' controls whether or not
            the time an entry was created will be written to the destination
            befor each log entry. 'stampLoc' controls whether or not the
            source file and line number will be written to the destination
            before each log entry.

  	inline
    	Log( const char *	fileName,
    	     LogLevel::Level	outLevel = ( LogLevel::Error |
  				             LogLevel::Warn |
  				             LogLevel::Info ),
  	     std::ios::openmode	mode = (ios::openmode)(ios::app|ios::out),
    	     int		prot = openprot,
    	     bool		stampLevel = true,
    	     bool		stampTime = true,
  	     bool		stampLoc = true,
  	     size_t		maxSize = 0,
  	     size_t		trimSize = 0 );

  	inline
    	Log( const char *	fileName,
    	     const char *	outLevel,
  	     std::ios::openmode	mode = (ios::openmode)(ios::app|ios::out),
    	     int		prot = openprot,
    	     bool		stampLevel = true,
    	     bool		stampTime = true,
  	     bool		stampLoc = true,
  	     size_t		maxSize = 0,
  	     size_t		trimSize = 0 );
  	    Log Constructor that uses a file as the primary destination
  	    for log entries. 'fileName' is the name of the file where
  	    the entries will be written.'outLevel' is a mask of the
  	    log levels that will be written. 'mode' is the mode that
  	    will be used to open the file (see fstream(3) ofstream::open).
  	    'prot' is the file's protection mask if the file is created
  	    (see fstream(3) ofstream::open). 'stampLevel' controls
  	    whether or not the level of a specific entry will be written to
  	    the destination before each log entry. 'stampTime' controls
  	    whether or not the time an entry was created will be written to
  	    the destination befor each log entry. 'stampLoc' controls
  	    whether or not the source file and line number will be written
  	    to the destination before each log entry. 'maxSize' is the
  	    maximum number of bytes for the log file. A maxSize value
  	    of 0, means no limit. If it is any other value, the file
  	    will be trimmed, according to 'trimSize' when it reaches this
  	    size. 'trimSize' is the ammount to trim from the begining of the
  	    file, when it reaches 'maxSize'. A trimSize value of 0 means
  	    25% of maxSize will be trimmed. Any other value is the number
  	    of bytes to trim.

    Public Interface:

  	inline
  	LogLevel::Level
  	getCurrent( void ) const
  	    Returns the level for the current log entry.

  	inline
  	LogLevel::Level
  	getOutput( void ) const
  	    Returns the level(s) that will be output to the primary log.

  	inline
  	bool
  	willOutput( const LogLevel::Level & outLevel ) const
  	    Returns true if 'outLevel' would be written to the destination.
            else return false.

  	Log &
  	level( const LogLevel::Level &	current = LogLevel::Error,
  	       const char *		srcFile = 0,
  	       long			srcLine = 0 );
  	    This method is used to specify the level for a log entry.
  	    'current' is the level that will be used for the entry.
  	    'srcFile' is the source file the method is being called
  	    from (i.e. __FILE__). 'srcLine' is the line number the
  	    method is being called from (i.e. __LINE__). Anything put
  	    on the log after a call to this method will be a single
  	    entry to the log for the specified level. The Log
  	    is returned (i.e. *this) so you can immediately start
  	    writing the entry
  	    (i.e. log.level( LogLevel::Error, __FILE__, __LINE__ )
  	    << "text" << endl; ).

  	inline
  	Log &
  	operator () ( void )
  	    This is just a short cut call to level with its args
  	    defaulted (i.e. log() does the same thing as log.level()
  	    and log.level( LogLevel::Error, 0, 0 ).The Log is returned
  	    (i.e. *this) so you can immediately start writing the entry
  	    (i.e. log() << "text" << endl; ).

  	inline
  	Log &
  	operator () ( const LogLevel::Level & current )
  	    This is just a short cut call to level with its last two args
  	    defaulted (i.e. log( LogLevel::Debug ) does the same thing
  	    as log.level( LogLevel::Debug ) and
  	    log.level( LogLevel::Debug, 0, 0 ).The Log is returned
  	    (i.e. *this) so you can immediately start writing the entry
  	    (i.e. log( LogLevel::Debug ) << "text" << endl; ).

  	inline
  	Log &
  	operator () ( const LogLevel::Level &	current,
  		      const char *		srcFile,
  		      long			srcLine );
  	    This is just a short cut call to level. (i.e.
  	    log( LogLevel::Debug, __FILE__, __LINE__ ) does the same thing
  	    as log.level( LogLevel::Debug, __FILE__, __LINE__ ) ). The
  	    Log is returned (i.e. *this) so you can immediately start
  	    writing the entry
  	    (i.e. log( LogLevel::Debug, __FILE__, __LINE__  ) << "text"
  	    << endl; ).

  	Log &
  	level( const char * current,
  	       const char * srcFile = 0,
  	       long	    srcLine = 0 )
  	    This is the same as level( LogLevel::Level curent ...) above
  	    only the current level can be a text string (see LogLevel(3)
  	    for conversion behavior). (i.e. log.Level( "WARN" ) is the
  	    same as log.level( LogLevel::Warning ) ).

  	inline
  	Log &
  	operator () ( const char * current,
  		      const char * srcFile,
  		      long	   srcLine );
  	    These are just short cut calls to level( const char * ... ).

  	inline
  	bool
  	setLevelStamp( bool stamp )
  	    Set whether or not the level stamp will be output before the
  	    log entry. If 'stamp' is true, the level will be prepended to
  	    the entry, else it will not be output. The previous state
  	    of the level stamp is returned.

  	inline
  	bool
  	setTimeStamp( bool stamp )
  	    Set whether or not the date and time the log entrie was
  	    created will be prepended to the entry on output. If 'stamp'
  	    is true, the date and time will be output, else
  	    it will not be output. The previous state of the time stamp
  	    is returned.

  	inline
  	bool
  	setLocStamp( bool stamp )
  	    Set whether or not the source file and line will be output
  	    before the log entry. If 'stamp' is true and the source file
  	    and line was provided, it will be output. Otherwise it will
  	    not be output. The previous state of the location stamp is
  	    returned.

  	inline
  	LogLevel::Level
  	setOutputLevel( const LogLevel::Level & output )

  	inline
  	LogLevel::Level
  	setOutputLevel( const char * output )
  	    Change the output mask. Only the entries with one of the
  	    types in 'output' will be written to the destination. The
  	    output can be specified as a set of LogLevel::Level's
  	    'OR' togther (i.e. setOutput( LogLevel::Error | LogLevel::Warn )
  	    ). Or it can be a text string containing the levels to be
  	    written (i.e. "Error | Warning" ). The previous value
  	    for the output level is returned.

  	inline
  	void
  	on( const LogLevel::Level & output )
  	    Turn on outputing for the level(s) specifed by 'output'. The
  	    state of other existing output levels is not changed.

  	inline
  	void
  	off( const LogLevel::Level & output )
  	    Turn off outputing for the level(s) specified by 'output'.
  	    The output state for other levels is not changed.

  	inline
    	void
    	tee( std::ostream & teeStream = std::cerr );
  	    This will cause all output written to the primary
  	    destination to also be written to the stream specified
  	    by 'teeStream'.

  	inline
  	size_t
  	setTrimSize( size_t trimSize )
  	    If the primary destination is a file, this sets the
  	    number of bytes to be removed from the file each
  	    time it reaches max size (see setMaxSize). A value of
  	    0 means to remove the first 25% of the file. Returns
  	    the previous value of trimSize.

  	inline
  	size_t
  	setMaxSize( size_t maxSize )
  	    If the primary log destination is a file, this sets
  	    the maximum size of the file. If it reaches this size,
  	    it will be automatically trimed according to the
  	    trim size (see setTrimSize). A maxSize of 0 removes
  	    the limit so that the file can grow indefinately.
  	    Returns the previous value of maxSize.

  	inline
  	size_t
  	trim( size_t maxSize = 0 )
  	    If the primary log is a file, this will trim off
  	    the beginning of the file so this it is smaller than
  	    maxSize - trimSize (set setTrimSize). If maxSize is '0',
  	    the current maxSize (see setMaxSize) will be used. Returns
  	    the number of bytes trimmed from the file.

  	inline
  	void
  	open( const char *	fileName,
	      std::ios::openmode	mode = (ios::openmode)(ios::out|ios::app),
	      int		prot = 0664 );
  	    This will open 'fileName' using 'mode' and make it the
  	    primary destionation for output. use 'good()' to
  	    ensure the call was successfull.

  	inline
  	void
  	setFileName( const char *	fileName,
		     std::ios::openmode	mode
		       = (ios::openmode)(ios::out|ios::app),
		     int		prot = 0664 );
  	    This is just another name for 'open'.

  	inline
  	void
  	close( void )
  	    If the primary destination is a file, close it.
  	    There will not be a primary destination until a file is
  	    'open'ed.

  	bool
  	filter( const char * regex )
  	    Create a filter using the pattern in 'regex' for the
  	    primary destination. This will filter out all log entries
  	    that do NOT contain the pattern in 'regex'. The first 2048
  	    bytes of each log entry are searched for a match will
  	    the 'regex', if there is a match, that entry is output.
  	    See RegexScan(3) for the syntax of the pattern. If 'regex'
  	    is 0, any existing filter will be removed. Returns true
  	    if a valid filter is being used.

  	LogBuf::FilterId
  	addFilter( streambuf *		    destBuf,
  		   const LogLevel::Level &  outputLevel,
  		   const char *		    regex = 0 )
  	    Add a new filtered destination for log entries. This has
  	    no impact on the primary destination specified by the
  	    constructor. 'outputLevel' specifies the level(s) to
  	    write to this destination. 'regex' specifies a pattern
  	    to filter the log entries through (see filter()). Returns
  	    a 'FilterId' that can be used to delete the destination
  	    at some later time (see delFilter).

  	streambuf *
  	delFilter( LogBuf::FilterId id )
  	    Remove a filtered destination that was created with
  	    'addFilter'. Returns the streambuf that was the
  	    destination for the filter or 0 if the filter Id was
  	    not valid.

  	inline
  	LogBuf *
  	rdbuf( void )
  	    Returns the logBuf used by this log (see LogBuf(3)).

  	inline
  	const LogBuf *
  	rdbuf( void ) const
  	    Returns the logBuf use by this log (see LogBuf(3)).

  	inline
  	bool
  	lock( void )
  	    If threads are supported, this locks the log
  	    to make it thread safe.

  	inline
  	bool
  	unlock( void )
  	    If threads are supported, this will unlock the log after
  	    it has been locked.

  	virtual
  	bool
  	good( void ) const
  	    Return true if there are no errors associated with
  	    the log, otherwise return false.

  	virtual
  	const char *
  	error( void ) const
  	    Return a text description of the current state of the log.

    	virtual
  	const char *
    	getClassName( void ) const;
    	    Returns the name of this class ( i.e. Log )

  	virtual
  	const char *
  	getVersion( bool withPrjVer = true ) const
  	    Return the version string for the Log. If
  	    withPrjVer == true, the project version info will also
  	    be returned.

  	virtual
  	std::ostream &
  	dumpInfo( std::ostream &	dest = std::cerr,
  		  const char *	prefix = "    ",
  		  bool		showVer = true ) const;
  	    Output detailed information about the current
  	    state of the Log.

  	static const ClassVersion version;
  	    This contains the version information for the Log class.


    Associated Macros:

  	LogIf( log, level )
  	    This improves performance by testing if the entry
  	    would be output before processing it. It also set
  	    the source file (__FILE__) and line (__LINE__) for
  	    the log entry.
  	    (i.e. LogIf( log, LogLevel::Debug ) << entry << endl; )

    Example:

  	Source file name - tLog.C

  	#include <Log.hh>  // includes LogBuf.hh & LogLevel.hh for you

  	int
  	main( int argc, char * argv[] )
  	{

  	    Log log( "App.log", LogLevel::All );

  	    LogIf( log, LogLevel::Info ) << "This is an info entry." << endl;

  	    log.tee( std::cerr );

  	    LogIf( log, LogLevel::Error )
  		<< "This is an error entry" << endl;

  	    log << "This is more of the same error entry" << endl;

  	    return( 0 );

  	}

  	Will write the following to 'App.log':

  	11/11/96 12:10:59 INFO tLog.C:11 This is an info entry.
  	11/11/96 12:10:59 ERROR tLog.C:15 This is an error entry
  	This is more of the same error entry

  	And the following to std::cerr (stderr):

  	11/11/96 12:10:59 ERROR tLog.C:15 This is an error entry
  	This is more of the same error entry

   See Also:

    LogLevel(3), LogBuf(3), RegexScan(3), std::ostream(3)

   Files:

  	Log.hh, Log.ii, LogBuf.hh, LogBuf.ii, LogLevel.hh, LogLevel.ii,
  	libStlUtils.a

**/

#endif // ! def _clue_Log_hpp_

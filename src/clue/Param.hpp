#ifndef _clue_Param_hpp_
#define _clue_Param_hpp_
/* 1995-01-26 (cc) Paul Houghton <paul4hough@gmail.com>

   This is the base class for providing command line argument parsing.
   It lets you identify arguemntes and/or environment varaibles
   to be parsed and converted in to program variables. It
   also create a help message that documents the
   arguments and environment varaibles.

   Param also contains an instance of the L<Log|Log> class that
   can be used for application logging by your program.

   Param defines a number of common command line arguments and
   environment variables please see the L</Usage> section for more
   information

   The most effective way to utilize this class is to create
   a subclass called 'AppParam' and customize it for your
   application (see L</Example> section below).

   Notes:

     The arg* methods contain types in there names because
     argFlag and argBool both take 'bool' types but function
     differently.
*/

#include <clue/Log.hpp>
#include <clue/DateTime.hpp>
#include <clue/LibLog.hpp>
#include <clue/DumpInfo.hpp>
#include <clue/FilePath.hpp>
#include <clue/StringUtils.hpp>
#include <deque>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>

#if !defined( CLUE_DEFAULT_LOGLEVEL )
#define CLUE_DEFAULT_LOGLEVEL "ERROR | WARNING | INFO"
#endif

#define ALog( lvl )	LogIf( (*App).log(), lvl )

#define AppWarn	    ALog( LogLevel::Warn )
#define AppError    ALog( LogLevel::Error )
#define AppInfo	    ALog( LogLevel::Info )
#define AppDebug    ALog( LogLevel::Debug )
#define AppTest     ALog( LogLevel::Test )

#define AppAbort( exitCode ) (*App).abort( exitCode, true, __FILE__, __LINE__ )

namespace clue {

class Param
{

public:

  typedef std::deque< Str >	Args;

  Param( int 		    mainArgc,
	 char const **	    mainArgv,
	 const char *	    version = 0,
	 bool		    useDefaultArgFn = false,
	 const char *	    logLevel = CLUE_DEFAULT_LOGLEVEL,
	 bool		    useDefaultLogFn = false,
	 std::ios::openmode logOpenMode = (std::ios::openmode)(std::ios::out|
							       std::ios::app) );

  Param( int 		    mainArgc,
	 char **	    mainArgv,
	 const char *	    version = 0,
	 bool		    useDefaultArgFn = false,
	 const char *	    logLevel = CLUE_DEFAULT_LOGLEVEL,
	 bool		    useDefaultLogFn = false,
	 std::ios::openmode logOpenMode = (std::ios::openmode)(std::ios::out|
							       std::ios::app) );

  virtual ~Param( void );

  void		    appendHelp( const char * helpText );

  inline Log &	    log( void );
  inline Log &	    log( LogLevel::Level lvl );

  const char *	    appName( void ) const ;
  const char *	    appFullName( void ) const;
  const char *	    appVersion( void ) const;

  pid_t		    getpid( void ) const;
  const DateTime &  startTime( void ) const;
  Log &		    logStartInfo( void );
  Log &		    logExitInfo( int exitCode );

  inline size_t	    count( void ) const;

  inline Args::const_iterator	begin( void ) const;
  inline Args::const_iterator	end( void ) const;

  inline Args::const_iterator	beginAll( void ) const;
  inline Args::const_iterator	endAll( void ) const;

  inline const char *	arg( size_t which = 0 );
  inline long		argLong( size_t which = 0 );
  inline double		argDouble( size_t which = 0 );

  inline const char *	env( const char * envVar ) const;

  inline bool		setArgFileName( const char * name );

  virtual bool	parseArgs( void );
  virtual bool	parseArgs( int argc, char * argv[] );

  bool	argChar( char &  	 dest,
		 const char *	 valueName,
		 const char *	 shortDesc,
		 const char *	 longDesc,
		 bool		 required,
		 const char *    argId,
		 const char *    envVar = 0 );
  bool	argStr( char * &  	 dest,
		const char *	 valueName,
		const char *	 shortDesc,
		const char *	 longDesc,
		bool		 required,
		const char *     argId,
		const char *     envVar = 0 );
  bool	argStr( Str & 	    	dest,
		const char *	valueName,
		const char *	shortDesc,
		const char *	longDesc,
		bool		required,
		const char *    argId,
		const char *    envVar = 0 );
  bool	argInt( int &	    	dest,
		const char *	valueName,
		const char *	shortDesc,
		const char *	longDesc,
		bool		required,
		const char *    argId,
		const char *    envVar = 0,
		int	    	minVal = INT_MIN,
		int	    	maxVal = INT_MAX );
  bool	argUInt( unsigned int &	dest,
		 const char *	valueName,
		 const char *	shortDesc,
		 const char *	longDesc,
		 bool		required,
		 const char *   argId,
		 const char *   envVar = 0,
		 unsigned int	minVal = 0,
		 unsigned int   	maxVal = UINT_MAX );
  bool	argShort( short &    	dest,
		  const char *	valueName,
		  const char *	shortDesc,
		  const char *	longDesc,
		  bool		required,
		  const char *  argId,
		  const char *  envVar = 0,
		  short	    	minVal = SHRT_MIN,
		  short	    	maxVal = SHRT_MAX );
  bool	argUShort( unsigned short & dest,
		   const char *	    valueName,
		   const char *	    shortDesc,
		   const char *	    longDesc,
		   bool		    required,
		   const char *	    argId,
		   const char *	    envVar = 0,
		   unsigned short   minVal = 0,
		   unsigned short   maxVal = USHRT_MAX );
  bool	argLong( long &	    	dest,
		 const char *	valueName,
		 const char *	shortDesc,
		 const char *	longDesc,
		 bool		required,
		 const char *   argId,
		 const char *   envVar = 0,
		 long	    	minVal = LONG_MIN,
		 long	    	maxVal = LONG_MAX );
  bool	argULong( unsigned long &   dest,
		  const char *	    valueName,
		  const char *	    shortDesc,
		  const char *	    longDesc,
		  bool		    required,
		  const char *	    argId,
		  const char *	    envVar = 0,
		  unsigned long	    minVal = 0,
		  unsigned long	    maxVal = ULONG_MAX );
  bool	argLongLong( long long &    dest,
		     const char *   valueName,
		     const char *   shortDesc,
		     const char *   longDesc,
		     bool	    required,
		     const char *   argId,
		     const char *   envVar = 0,
		     long long	    minVal = LLONG_MIN,
		     long long	    maxVal = LLONG_MAX );
  bool	argULongLong( unsigned long long &  dest,
		      const char *	    valueName,
		      const char *	    shortDesc,
		      const char *	    longDesc,
		      bool		    required,
		      const char *	    argId,
		      const char *	    envVar = 0,
		      unsigned long long    minVal = 0,
		      unsigned long long    maxVal = ULLONG_MAX );
  bool	argDouble( double & 	dest,
		   const char *	valueName,
		   const char *	shortDesc,
		   const char *	longDesc,
		   bool		required,
		   const char * argId,
		   const char * envVar = 0 );
  bool	argBool( bool &	    	dest,
		 const char *	valueName,
		 const char *	shortDesc,
		 const char *	longDesc,
		 bool		required,
		 const char *   argId,
		 const char *   envVar = 0 );
  bool	argFlag( bool &	    	dest,
		 const char *	shortDesc,
		 const char *	longDesc,
		 const char *   argId,
		 const char *   envVar = 0 );
  bool	argDateTime( time_t &	    dest,
		     const char *   valueName,
		     const char *   shortDesc,
		     const char *   longDesc,
		     bool	    required,
		     const char *   argId,
		     const char *   envVar = 0 );
  bool	argDateTime( DateTime &	    dest,
		     const char *   valueName,
		     const char *   shortDesc,
		     const char *   longDesc,
		     bool	    required,
		     const char *   argId,
		     const char *   envVar = 0 );
  bool	argDate( DateTime &	 dest,
		 const char *	 valueName,
		 const char *	 shortDesc,
		 const char *	 longDesc,
		 bool		 required,
		 const char *	 argId,
		 const char *	 envVar = 0 );
  bool	argTime( DateTime &	 dest,
		 const char *	 valueName,
		 const char *	 shortDesc,
		 const char *	 longDesc,
		 bool		 required,
		 const char *	 argId,
		 const char *	 envVar = 0 );

  inline bool	help( bool exitApp = true );

  inline bool	allArgs( void ) const;
  inline bool	extraFlags( void ) const;

  bool		haveErrorLog( void ) const;

  void		abort( int  	    exitStatus = 1,
		       bool 	    showArgs = false,
		       const char * srcFile = 0,
		       long	    srcLine = 0,
		       std::ostream &    mesgDest = std::cerr );

  virtual std::ostream &    toStream( std::ostream & dest ) const;

  virtual bool		    good( void ) const;
  virtual const char *	    error( void ) const;
  virtual std::ostream &    dumpInfo( std::ostream &	dest = std::cerr,
				      const char *	prefix = "    " ) const;

  inline
  DumpInfo< Param >
  dump( const char *  prefix = "    " ) const {
    return( DumpInfo< Param >( *this, prefix ) );
  }


  enum ErrorNum
  {
    E_OK,
    E_RANGE,
    E_CONVERT,
    E_NO_VALUE,
    E_ERRLOG_ADD,
    E_ERRLOG_OPEN,
    E_ERRLOG_NEW,
    E_ERRLOG_LEVEL,
    E_UNDEFINED
  };

  // not real ment for the public, but no harm in giving access
  inline bool	matchArg( const Str &	    arg,
			  const char *	    id,
			  Str::size_type    endPos = Str::npos );
protected:

  inline bool	readArgs( const char * fileName );
  bool		readArgs( std::istream & src );

  inline void	removeStopFlag( void );

  void init( int 	    mainArgc,
	     char const **  constMainArgv,
	     char **	    mainArgv,
	     bool	    useDefaultArgFn,
	     bool	    useDefaultLogFn );

private:

  Param( const Param & copyFrom );
  Param & operator=( const Param & assignFrom );

  Str		    getArgValue( const char *	argId,
				 const char *	envVar,
				 bool		sNum = false );

  bool		    getArgFlag( const char * argId, const char * envVar );

  size_t    appendArgInfo( const char *	argId,
			   const char *	valueName,
			   const char * shortDesc,
			   const char * longDesc,
			   bool		required,
			   const char *	envVar,
			   const char *	value,
			   bool		isflag = false );

  size_t    appendArgFile( const char *	argId,
			   size_t	argIdLen,
			   const char *	valueName,
			   const char * shortDesc,
			   const char * longDesc,
			   bool		required,
			   const char *	envVar,
			   const char *	value,
			   bool		isflag );

  size_t    appendHelp( const char *	argId,
			size_t		argIdLen,
			const char *	valueName,
			const char * shortDesc,
			const char * longDesc,
			bool		required,
			const char *	envVar,
			const char *	value );

  void	    genArgFile( bool exitApp ) const;

  DateTime	    appStartTime;

  Str		    versionText;
  Str		    helpText;
  Str    	    helpString;
  Str		    argFileString;

  Args		    allArgv;
  Args		    argv;
  Args		    allFileArgs;
  Args		    fileArgs;

  Log	    	    appLog;

  FilePath	    argFile;
  bool    	    helpFlag;
  bool		    haveStopFlag;

  Str    	     logFile;
  std::ios::openmode logMode;


  Str    	    logOutputLevel;
  Str		    logFilter;

  FilePath	    errorLogName;
  std::ofstream *   errorLogFile;
  LogBuf::FilterId  errorLogId;
  Str		    errorLogLevels;

  bool	    	    logTee;
  unsigned long	    logMaxSize;
  unsigned long	    logTrimSize;
  bool		    logTimeStamp;
  bool		    logLevelStamp;
  bool		    logLocStamp;

  bool		    generateArgFile;

  static const char *	ErrorStrings[];

  struct Error
  {
    ErrorNum	errorNum;
    Str		argId;
    Str		envVar;
    Str		desc;
  };

  bool	setError( ErrorNum err,
		  const char *	argId,
		  const char *	envVar,
		  const char *	desc );

  typedef std::vector< Error >   ErrorList;

  ErrorList		    errors;

};


inline
Log &
Param::log( void )
{
  return( appLog );
}

inline
Log &
Param::log( LogLevel::Level lvl )
{
  return( appLog.level( lvl ) );
}

inline
size_t
Param::count( void ) const
{
  return( argv.size() );
}

inline
Param::Args::const_iterator
Param::begin( void ) const
{
  return( argv.begin() );
}

inline
Param::Args::const_iterator
Param::end( void ) const
{
  return( argv.end() );
}

inline
Param::Args::const_iterator
Param::beginAll( void ) const
{
  return( allArgv.begin() );
}

inline
Param::Args::const_iterator
Param::endAll( void ) const
{
  return( allArgv.end() );
}

inline
bool
Param::setArgFileName( const char * name )
{
  if( name )
    argFile = name;
  return( argFile.size() > 0 );
}

inline
const char *
Param::arg( size_t which )
{
  return( (which < count()) ? argv[which].c_str() : 0 );
}

inline
long
Param::argLong( size_t which )
{
  if( which < count() )
    {
      return( StringToLong( argv[which].c_str() ) );
    }
  else
    {
      return( -1 );
    }
}

inline
double
Param::argDouble( size_t which )
{
  if( which < count() )
    {
      return( StringToDouble( argv[which].c_str() ) );
    }
  else
    {
      return( -1.0 );
    }
}

inline
bool
Param::readArgs( const char * fileName )
{
  std::ifstream  in( fileName );

  if( in.good() )
    return( readArgs( in ) );
  else
    return( false );
}

inline
const char *
Param::env( const char * envVar ) const
{
  return( envVar ? getenv( envVar ) : 0 );
}

inline
bool
Param::help( bool exitApp )
{
  // This is a cheat!
  //   If param is used, the app will most likely call help
  //   after all the args have been processed. If the user
  //   requested an argfile (i.e. -gen-argfile) then we
  //   should generate it, tell him about it and exit.
  //
  if( generateArgFile )
    genArgFile( exitApp );

  if( helpFlag && exitApp )
    abort( 100, true, __FILE__, __LINE__ );

  return( helpFlag );
}

inline
bool
Param::allArgs( void ) const
{
  return( count() == 0 && fileArgs.size() == 0 );
}

inline
bool
Param::extraFlags( void ) const
{
  if( fileArgs.size() )
    return( true );

  for( Args::const_iterator them = argv.begin();
       them != argv.end();
       ++ them )
    {
      if( (*them).size() && (*them)[0UL] == '-' )
	return( true );
    }
  return( false );
}


inline
std::ostream &
operator<<( std::ostream & dest, const Param & obj )
{
  return( obj.toStream( dest ) );
}

void
Param::removeStopFlag( void )
{
  if( haveStopFlag )
    {
      Args::iterator	them = argv.begin();
      for( ; them != argv.end(); ++ them )
	{
	  if( (*them).size() > 1
	      && (*them)[0UL] == '-'
	      && (*them)[1UL] == '-' )
	    {
	      argv.erase( them );
	      haveStopFlag = false;
	      break;
	    }
	}
    }
}


inline
bool
Param::matchArg( const Str & arg, const char * id, Str::size_type endPos )
{
  return( arg.size() > 1
	  && arg[0UL] == '-'
	  && ( ( ( arg[1UL] != '-'
		   && arg.substr( 1, endPos ).compare( id ) == 0 ) )
	       || ( arg.size() > 2
		    && arg.substr( 2, endPos ).compare( id ) == 0 ) ) );
}

}; // namespace clue

/*

  Types:

  	class Param

	    There are many methods in this class that process and
	    convert command line arguments to program variables
	    (i.e. arg*(...)). They all expect a 'dest' variable, a
	    'description', an 'argId' and an optional 'envVar'
	    parameters. The numeric methods can also get a 'min' and
	    max value parameters.

	    The 'dest' parameter is the program variable to be set
	    from the argId or the environment variable. First it is
	    set to the envirnment variable's value (if one is found),
	    then it is set to the argument's value (again if one is
	    found). So, the command line overides any enveronment
	    variable settings. If any errors occure trying to process
	    the arg, dest will not be modified.

	    The 'description' parameter is the description that will
	    be ised for the help output. It should be a short
	    description of how the arg is used by the application.

	    The 'argId' is the string identifier for the command line
	    argument. The command line args are searched for an exact
	    match with a preceiding '-' character. So, if 'argId' is
	    "file" then the corisponding command line arg would be
	    "-file". The argId's and there corrisponding values are
	    treated as indepenant sequences.

		prog -a a_value -b b_value -c c_value
		    is the same as
		prog -a -b -c a_value b_value c_value

	    The argFlag method is the only one that does not look for
	    a corrispondig value. So if -x was a flag then the
	    following would examples would all produce the same
	    results.

		prog -x -a a_value -b b_value -c c_value
		prog -a a_value -b -x b_value -c c_value
		prog -a a_value -b b_value -x -c c_value
		prog -x -a -b -c a_value b_value c_value
		prog -a -b -x -c a_value b_value c_value
		prog -a -b -c a_value -x b_value c_value

	    Because of the increased use of '--agr' for long arguments,
	    both '--arg' and '-arg' are treated as the same argument.

	    If there is a '--' on the command line, nothing after it
	    will be parse. So in the following:

		prog -this --that -- -otherstuf

	    Would leave the -otherstuff in the args for the application
	    to process. You can use the 'removeStopFlag()' call to
	    remove the '--' after all the args are processed.

	    The 'envVar' parameter specifies an envronment variable to
	    be used for the value.

	    The 'min' and 'max' parameters specificy the numeric
	    limits for the arg. If min <= value <= max is not true,
	    then dest is not set an good() will return false.

	class Param::Args
	    This type is used to access the args through iterators.

 Usage:

  These are the default args defined by the Param class.

	-argfile    string - the name of the argument file to read
		    for all other arguments. This file is read before
		    any other arguments are processed, so any values
		    set in it will be overriden by both environment
		    variables and command line arguments. The format
		    of the file is:

			# this is a comment
			  -arg    opt value string      # comment

		    Where arg is a whole word arguement and
		    'opt value string' will be the next argument.
		    Usually this would be the value for -arg, but
		    There is no restrictions placed on this.
		    The only syntactical restrictions is that the
		    first sequence of non whitespace characters
		    on a line are treated as a single argument. All
		    other non white space characts are treated as
		    another signle argument.

	-help	    flag - show usage help. The application must
		    check the help() method and put the
		    Param object on an std::ostream ( std::cout << param; )
		    to actually output the help text.

	-version    flag - output the version info to stdout (cout)
		    then exit(0). If the -help flag is also set, this flag
		    is ignored (the version info is included in the help).

	-gen-argfile flag - generate an argfile into the file named by
		    the -argfile argument. This file can then modified
		    and used as the application's argfile.

	-log-file   string - log file name. File name that should be used
		    for log output. Env: LOG_FILE. Default: std::cout

	-log-mode   string - this is the 'ios::openmode' for the
		    log file. It should be either 'ios::app|ios::out' or
		    'ios::out'. (note: the std::ios:: and the | are ignored,
		    so 'app out' will also work.

	-log-prot   int - this is the protection for a new log file.
		    The leading 0 is significant, so you should
		    set it with something like 0644.

	-log-level  stirng - output log level. The type of log entries
		    that will be output to the log.
		    Env: LOG_LEVEL. Default: "INFO | ERROR | WARING";

	-log-filter string - filter log entries through this
		    regex pattern. Only entries that contain
		    the pattern will be output.
		    Env: LOG_FILTER. Default: none.

	-log-tee    flag - Tee log output to std::cerr.

	-log-show-time
		    bool - write a time stamp to each
		    log entry. Env: LOG_TIME. Default: true

	-log-show-level
		    bool - output the level with each log entry
		    Env: LOG_STAMP_LEVEL. Default: true.

	-log-show-loc
		    bool - output source file and line with each
		    log entry. Env: LOG_LOC. Default: true

	-log-max	    long - max size of log file.
		    Env: LOG_MAX. Default: 0 (unlimited)

	-log-trim   long - log file trim size.
		    Env: LOG_TRIM. Default: 0 ( 25% of max ).

	-error-log  string - an additional log file to write log entries
		    to. Only those entries with the log level specified
		    by -error-log-level will be written to this file.

	-error-log-level
		    string - this is the log level
		    of the log entries that should be written to the
		    -error-log file. Default: "WARN | ERROR"


  Constructors:

  	Param( int		mainArgc,
	       char *		mainArgv[],
	       const char *	version = 0,
	       bool		useDefaultArgFn = false,
	       const char *	logLevel = STLUTILS_DEFAULT_LOGLEVEL,
	       bool		useDefaultLogfn = false,
	       std::ios::openmode	logOpenMode = (ios::out|ios::app)
	       int		logOpenProt = 0664 );
	    Construct an instance of the Param class. 'mainArgc' and
	    mainArgv should be the original argv and argc from main
	    (i.e. main( int argc, char * argv[] ). 'version' is the
	    version identification for the application.
	    If 'useDefaultArgFn' is true, then the argfile will
	    be 'mainArgv[0].args'. 'logLevel' sets the output level for
	    the log.  If 'useDefaultLogFn' is true, the logfile will
	    be 'mainArgv[0].log'. 'logOpenMode' sets the default open
	    mode for the log file. 'logOpenProg' sets the default
	    protection for the log file.

  Public Interface:

	void
	appendHelp( const char * helpText )
	    This text will be added to the help message.

	inline
  	Log &
  	log( void );
	    Return a referance to the application's log.

	inline
  	Log &
  	log( LogLevel::Level lvl );
	    Set the logs entry level and return a referance to it.

	inline
  	const char *
  	appName( void ) const ;
	    Returns the name of the application. This comes from
	    argv[0]. It only returns the name and not any directories.

	inline
  	const char *
  	appFullName( void ) const;
	    Returns the name of the application including any directory
	    information (i.e. argv[0]).

	inline
	const char *
	appVersion( void ) const
	    Return the version infomation passed to the constructor.

	pid_t
	getpid( void )
	    Return the process id for the application.

	inline
  	size_t
  	count( void ) const;
	    Return the number of unprocessed args. This includes
	    the applications name, so it should always return at least
	    '1'.

	inline
	Args::const_iterator
	begin( void ) const
	    Return an iterator for all unprocessed args. This includes argv[0].

	inline
	Args::const_iterator
	end( void  ) const
	    Return an iterator for the end of all unprocessed args.

	inline
	Args::const_iterator
	beginAll( void ) const
	    Return an interator for all args, included those that
	    have already been processed.

	inline
	Args::const_iterator
	endAll( void ) const
	    Return an iterator for the end of all args.

	inline
  	const char *
  	arg( size_t which = 1 );
	    Return the arg at position 'which' from the processed args.

	inline
  	long
  	argLong( size_t which = 1 );
	    Return the arg at position 'which' from the processed
	    args as a long.

	inline
  	double
  	argDouble( size_t which = 1 );
	    Return the arg at position 'which' from the processed
	    args as a double.

	inline
  	const char *
  	env( const char * envVar ) const;
	    Return the value for the envrionment variable 'envVar'.

	bool
	setArgFileName( const char * name )
	    Set the name of the argument file to use (i.e. -argfile).

	virtual
	bool
	parseArgs( void )
	    Process the default set of args used by Param.
	    Returns true if there were no errors, else returns
	    false. This is called by both readArgs and
	    parseArgs( int argc, char * argv[] ), so any subclass
	    (i.e. AppParam) should overide this function, call
	    Param::parseArgs() then process it's args.

	virtual
	bool
	parseArgs( int argc, char * argv[] )
	    Reset the args to argv and process them by
	    calling 'parseArgs( void )'. Note: the internal values
	    set by processArgs will NOT be reset to there default
	    values. Returns true if there were no errors, else
	    returns false.

	inline
	bool
	readArgs( const char * fileName )
	    Open 'fileName' and set the args from it. Once all the
	    args have been read, parseArgs( void ) is called to
	    process them. The format for the file is each line is
	    treated as one or two args. If there are spaces or tabs
	    in a line then a space character, the line is treated as 2
	    args (i.e. '-in' is one arg '-in this is an arg' is two args
	    where  second arg is 'this is an arg'). Blank lines and
	    lines starting with a '#' are treated as comments.
	    Returns true if there were no errors, else returns false.

	bool
	readArgs( std::istream & src )
	    Reads args from 'src' ( see readArgs( const char *) ).

  	bool
  	argStr( char * &	dest,
		const char *	description,
		const char *    argId,
		const char *    envVar = 0 );

  	bool
  	argStr( string &	dest,
		const char *	description,
		const char *    argId,
		const char *    envVar = 0 );

  	bool
  	argStr( RWCString &	dest,
		const char *	description,
		const char *    argId,
		const char *    envVar = 0 );

  	bool
  	argStr( Str &		dest,
		const char *	description,
		const char *    argId,
		const char *    envVar = 0 );
	    Process the arg and/or environment variable and set 'dest'
	    to it's value. Return true if dest was modified.

  	bool
  	argInt( Int & 	    	dest,
		const char *	description,
		const char *    argId,
	    	const char *    envVar = 0,
		int	    	minVal = INT_MIN,
		int	    	maxVal = INT_MAX );

  	bool
  	argUInt( unsigned int &	    dest,
		 const char *	    description,
		 const char *       argId,
		 const char *       envVar = 0,
		 unsigned int	    minVal = 0,
		 unsigned int       maxVal = UINT_MAX );

  	bool
  	argShort( short &    	dest,
		  const char *	description,
		  const char *  argId,
		  const char *  envVar = 0,
		  short	    	minVal = SHRT_MIN,
		  short	    	maxVal = SHRT_MAX );

  	bool
  	argUShort( unsigned short & dest,
		   const char *	    description,
		   const char *     argId,
		   const char *     envVar = 0,
		   unsigned short   minVal = 0,
		   unsigned short  maxVal = USHRT_MAX );

  	bool
  	argLong( long &	    	dest,
		 const char *	description,
		 const char *   argId,
		 const char *   envVar = 0,
		 long	    	minVal = LONG_MIN,
		 long	    	maxVal = LONG_MAX );

  	bool
  	argULong( unsigned long & dest,
		  const char *	  description,
		  const char *    argId,
		  const char *    envVar = 0,
		  unsigned long   minVal = 0,
		  unsigned long   maxVal = ULONG_MAX );
	    Process the arg and/or environment variable,
	    convert it to the appropriate type, and set 'dest'
	    to it's value. The value is converted the same
	    way that 'c' does. A leading '0' causes an octal
	    conversion and a leading '0x' causes a hex conversion.
	    Return true if dest was set.

  	bool
  	argDouble( double & 	dest,
		   const char *	description,
		   const char * argId,
		   const char * envVar = 0 );

  	bool
  	argBool( bool &	    	dest,
		 const char *   description,
		 const char *   argId,
		 const char *   envVar = 0 );
	    Process an arg and/or environment variable and set
	    dest according to it's value. The following are
	    understood and converted to true (case is NOT
	    significant): non-zero number, 't', 'y', 'true', 'yes',
	    and 'on'. The following are converted to false: 'f', 'n',
	    'false', 'no', 'off'. Returns true if dest was set.

  	bool
  	argFlag( bool &	    	dest,
		 const char *   description,
		 const char *   argId,
		 const char *   envVar = 0 );
	    Process and arg and/or environment variable and
	    set dest to 'true' if it exist. This is the only one
	    of the 'arg' methods that does not expect a value along
	    with the identifier.

    	bool
  	argDateTime( time_t &	    dest,
		     const char *   description,
		     const char *   argId,
		     const char *   envVar = 0 );

  	bool
  	argDateTime( DateTime &	    dest,
		     const char *   description,
		     const char *   argId,
		     const char *   envVar = 0 );

  	bool
  	argDateTime( RWTime &	    dest,
		     const char *   description,
		     const char *   argId,
		     const char *   envVar = 0 );
	    Process an arg and/or environment variable and
	    set dest to the corrisponding date & time value.
	    The format expected is 'MM/DD/YY HH:MM' and optional
	    seconds (i.e. 11/28/96 14:25:15). Returns true
	    if dest was set.

  	bool
  	argDate( RWDate &	dest,
		 const char *   description,
		 const char *   argId,
		 const char *   envVar = 0 );

  	bool
  	argDate( DateTime &	dest,
		 const char *   description,
		 const char *   argId,
		 const char *   envVar = 0 );
	    Process an arg and/or environment variable and
	    set dest to the corrisponding date value.
	    The format expected is 'MM/DD/YY'. (i.e. 11/28/96 ).
	    Returns true if dest was set.

  	bool
  	argTime( RWTime &	dest,
		 const char *   description,
		 const char *   argId,
		 const char *   envVar = 0 );

  	bool
  	argTime( DateTime &	dest,
		 const char *   description,
		 const char *   argId,
		 const char *   envVar = 0 );
	    Process an arg and/or environment variable and
	    set dest to the corrisponding time value.
	    The format expected is 'HH:MM:SS'. (i.e. 15:23:30 ).
	    Returns true if dest was set.


	inline
     	bool
  	help( void ) const
	    Return's true if the help flag was specified on the
	    command line (i.e. '-help' ).

	inline
      bool
  	allArgs( void ) const;
	    Returns true if all arguments have been processed.

	inline
	bool
	extraFlags( void ) const
	    Returns true if any of the remaining args have a first
	    character of - and a -- was not found on the command line.

	inline
  	void
  	abort( int  	    exitStatus = 1,
     	       bool 	    showArgs = false,
	       const char * srcFile = 0,
	       long	    srcLine = 0,
	       std::ostream &    dest = std::cerr );
	    Exit the program with 'exitStatus' and output a
	    message to 'dest'. If 'showArgs' is true, the help
	    message is output. 'srcFile' and 'srcLine' should be
	    the location abort is called from (i.e. __FILE__, __LINE__ ).

	virtual
	std::ostream &
	toStream( std::ostream & dest )
	    Output the help message to the stream 'dest'. Returns dest

  	virtual
	bool
  	good( void ) const;
  	    Returns true if there are no detected errors associated
  	    with this class, otherwise FALSE.

  	virtual
	const char *
  	error( void ) const;
  	    Returns as string description of the state of the class.

  	virtual
	const char *
  	getClassName( void ) const;
  	    Return the name of this class (i.e. Param )

  Protected:

  Private:

  Example:

	Create a class called AppParam that is a subclass
	of param. Put all your arguments into it and instanciate
	it from main().

	I highly recommend you 'new' it to a global pointer. This will
	give you both global access and control over construction order.

	There are helper macros defined that depend on the existance of
	a global AppParam * App.

	* AppParam.hh * START *

	#include <Param.hh>
	#include <FilePath.hh>

	class AppParam : public Param
	{

	public:

	  AppParam( int & argv, char ** argc, const char * ver = 0 );
	  ~AppParam( void );

	  const FilePath & inFn() { return( inFnV ); };

	  bool parseArgs( void );
	  bool parseArgs( int argc, char * argv[] );

	protected:

	  FilePath  inFnV;

	private:

	  AppParam( const AppParam & copyFrom );
	  AppParam & operator=( const AppParam & assignFrom );

	};

	extern AppParam * App;

	* AppParam.hh * END *

	* AppParam.C * START *

	AppParam::AppParam(
	  int &        mainArgc,
	  char **      mainArgv,
	  const char * mainVer
	  )
	  : Param( mainArgc, ,mainArgv, mainVer, true, "ERROR | WARN | INFO" ),
	    inFnV( "inputfile.data" )
	{

	  Str usageText;

	  usageText << "  " << appName() << " [options]\n\n"
	            << "    do something with infile.\n"
	    ;

	  appendHelp( usageText );

	  parseArgs();
	}

	inline
	AppParam::~AppParam( void )
	{
	}

	bool
	AppParam::parseArgs( int pArgc, char * pArgv[] )
	{
	  bool status = Param::parseArgs( pArgc, pArgv );

	  return( status ? parseArgs() : status );
	}

	bool
	AppParam::parseArgs( void )
	{
	  bool status = Param::parseArgs();

	  status &= argStr( inFnV, "input file name", "infile" );

        removeStopFlag();
	  return( status );
      }

	* AppParam.C * END *

	*  main.C * START *

	#include "AppParam.hh"

	const char * Version = "Param Demo V1.1";

	AppParam * App = 0;

	int
	main( int argc, char * argv[] )
	{
	  if( ! (App = new AppParam( argc, argv, Version ) ) )
	    {
	       std::cerr << "Can't new AppParam!" << endl;
	       exit( 1 );
	    }
	  if( ! (*App).good() || (*App).help() || ! (*App).allArgs() )
	    (*App).abort( AppMgr::getExitCode( AppMgr::ExitInit ),
			  true, __FILE__, __LINE__ );

	  AppInfo << (*App).appName() << "(" << (*App).getpid()
		  << ") started." << endl;

	  bool status( true );

	  std::cout << "Input is: " << App->inFn() << endl;

	  if( status )
	    {
	      AppInfo << (*App).appName() << "(" << (*App).getpid()
		      << ") completed."
		      << endl;
	    }
	  else
	    {
	      AppError << (*App).appName() << "(" << (*App).getpid()
		       << ") ABORTED!."
		       << endl;
	    }

	  if( App ) delete App;

	  return( status ? 0 : 1 );

	}

	* main.C * END *

 See Also:

  Log(3)


*/

#endif // ! def _Param_hh_

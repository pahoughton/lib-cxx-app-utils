#ifndef _Param_hh_
#define _Param_hh_
//
// File:        Param.hh
// Desc:
//
//  This is the base class for providing command line argument parsing.
//  It lets you identify arguemntes and/or environment varaibles
//  to be parsed and converted in to program variables. It
//  also create a help message that documentes the
//  arguments and environment varaibles.
//
//  There are a number of flags and enviroment varaibles already
//  defined for control of the log and help. They are described below.
//
//
//  It also contains a Log that can be used by the application.
//  
//  The most effective way to utilize this class is to create
//  a subclass called 'AppParam' and customize it for your
//  application (see Example: at end of file).
//
// Notes:
//
//	The arg* methods contain types in there names because
//	argFlag and argBool both take 'bool' types but function
//	differently.
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     01/26/95 13:28
//
// Revision History: (See end of file for Revision Log)
//
// $Id$ 
// 

#include <StlUtilsConfig.hh>
#include <Log.hh>
#include <DateTime.hh>
#include <LibLog.hh>
#include <DumpInfo.hh>
#include <deque>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>

#define STLUTILS_DEFAULT_LOGLEVEL "ERROR | WARNING | INFO"

#define ALog( lvl )	LogIf( App->log(), lvl )

#define AppWarn	    ALog( LogLevel::Warn )
#define AppError    ALog( LogLevel::Error )
#define AppInfo	    ALog( LogLevel::Info )
#define AppDebug    ALog( LogLevel::Debug )
#define AppTest     ALog( LogLevel::Test )


#if defined( STLUTILS_DEBUG )
#define inline
#endif

class Param
{

public:

  typedef deque< Str >	Args;
  
  Param( int 		    mainArgc,
	 char *		    mainArgv[],
	 const char *	    version = 0,
	 bool		    useDefaultArgFn = false,
	 const char *	    logLevel = STLUTILS_DEFAULT_LOGLEVEL,
	 bool		    useDefaultLogFn = false,
	 ios::open_mode	    logOpenMode = (ios::open_mode)(ios::out|ios::app),
	 int		    logOpenProt = 0664 );

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
 
  bool	argStr( char * &  	 dest,
		const char *	 description,
		const char *     argId,
		const char *     envVar = 0 );
  bool	argStr( Str & 	    	dest,
		const char *	description,
		const char *    argId,
		const char *    envVar = 0 );  
  bool	argInt( int &	    	dest,
		const char *	description,
		const char *    argId,
		const char *    envVar = 0,
		int	    	minVal = INT_MIN,
		int	    	maxVal = INT_MAX );
  bool	argUInt( unsigned int &	dest,
		const char *	description,
		const char *    argId,
		const char *    envVar = 0,
		unsigned int	minVal = 0,
		unsigned int   	maxVal = UINT_MAX );
  bool	argShort( short &    	dest,
		  const char *	description,
		  const char *  argId,
		  const char *  envVar = 0,
		  short	    	minVal = SHRT_MIN,
		  short	    	maxVal = SHRT_MAX );
  bool	argUShort( unsigned short & dest,
		  const char *	description,
		  const char *  argId,
		  const char *  envVar = 0,
		  unsigned short minVal = 0,
		  unsigned short maxVal = USHRT_MAX );
  bool	argLong( long &	    	dest,
		 const char *	description,
		 const char *   argId,
		 const char *   envVar = 0,
		 long	    	minVal = LONG_MIN,
		 long	    	maxVal = LONG_MAX );
  bool	argULong( unsigned long & dest,
		  const char *	  description,
		  const char *    argId,
		  const char *    envVar = 0,
		  unsigned long   minVal = 0,
		  unsigned long   maxVal = ULONG_MAX );
  bool	argDouble( double & 	dest,
		   const char *	description,
		   const char * argId,
		   const char * envVar = 0 );
  bool	argBool( bool &	    	dest,
		 const char *   description,
		 const char *   argId,
		 const char *   envVar = 0 );
  bool	argFlag( bool &	    	dest,
		 const char *   description,
		 const char *   argId,
		 const char *   envVar = 0 );
  bool	argDateTime( time_t &	    dest,
		     const char *   description,
		     const char *   argId,
		     const char *   envVar = 0 );
  bool	argDateTime( DateTime &	    dest,
		     const char *   description,
		     const char *   argId,
		     const char *   envVar = 0 );
  bool	argDate( DateTime &	    dest,
		 const char *	    description,
		 const char *	    argId,
		 const char *	    envVar = 0 );
  bool	argTime( DateTime &	    dest,
		 const char *	    description,
		 const char *	    argId,
		 const char *	    envVar = 0 );
  
  inline bool	help( void ) const;

  inline bool	allArgs( void ) const;

  void		abort( int  	    exitStatus = 1,
		       bool 	    showArgs = false,
		       const char * srcFile = 0,
		       long	    srcLine = 0,
		       ostream &    mesgDest = cerr );

  // libStlUtils Common Class Methods
  
  virtual ostream & 	toStream( ostream & dest ) const;

  virtual bool	    	good( void ) const;
  virtual const char *	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;
  
  inline
  DumpInfo< Param >	dump( const char *  prefix = "    ",
			      bool	    showVer = true ) const;
  
  static const ClassVersion version;
  
  enum ErrorNum
  {
    E_OK,
    E_RANGE,
    E_CONVERT,
    E_NO_VALUE,
    E_UNDEFINED
  };

protected:

  inline bool	readArgs( const char * fileName );
  bool		readArgs( istream & src );

private:

  Param( const Param & copyFrom );
  Param & operator=( const Param & assignFrom );

  Str		    getArgValue( const char * argId, const char * envVar );
  bool		    getArgFlag( const char * argId, const char * envVar );

  size_t    appendHelp( const char *	argId,
			const char *	desc,
			const char *	envVar,
			const char *	value );

  DateTime	    appStartTime;
  
  Str		    versionText;
  Str		    helpText;
  Str    	    helpString;
  

  Args		    allArgv;
  Args		    argv;
  Args		    allFileArgs;
  Args		    fileArgs;
  
  Log	    	    appLog;

  Str		    argFile;
  bool    	    helpFlag;

  Str    	    logFile;
  ios::open_mode    logMode;
  int		    logProt;
  
  Str    	    logOutputLevel;
  Str		    logFilter;
  
  bool	    	    logTee;
  unsigned long	    logMaxSize;
  unsigned long	    logTrimSize;
  bool		    logTimeStamp;
  bool		    logLevelStamp;
  bool		    logLocStamp;
  
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
  
  typedef vector< Error >   ErrorList;

  ErrorList		    errors;

};

#ifndef inline
#include "Param.ii"
#else
#undef inline

ostream &
operator << ( ostream & dest, const Param & obj );
    
#endif

// Detail Documentation:
//
// Desc:
//
//  These are the default args defined by the Param class.
//
//	-argfile    string - the name of the argument file to read
//		    for all other arguments. This file is read before
//		    any other arguments are processed, so any values
//		    set in it will be overriden by both environment
//		    variables and command line arguments. The format
//		    of the file is:
//
//			# this is a comment
//			  -arg    opt value string      # comment
//
//		    Where arg is a whole word arguement and
//		    'opt value string' will be the next argument.
//		    Usually this would be the value for -arg, but
//		    There is no restrictions placed on this.
//		    The only syntactical restrictions is that the
//		    first sequence of non whitespace characters
//		    on a line are treated as a single argument. All
//		    other non white space characts are treated as
//		    another signle argument.
//
//	-help	    flag - show usage help. The application must
//		    check the help() method and put the
//		    Param object on an ostream ( cout << param; )
//		    to actually output the help text.
//
//	-version    flag - output the version info to stdout (cout)
//		    then exit(0). If the -help flag is also set, this flag
//		    is ignored (the version info is included in the help).
//
//	-logfile    string - log file name. File name that should be used
//		    for log output. Env: LOG_FILE. Default: cout
//
//	-logmode    string - this is the 'ios::open_mode' for the
//		    log file. It should be either 'ios::app|ios::out' or
//		    'ios::out'. (note: the ios:: and the | are ignored,
//		    so 'app out' will also work.
//
//	-logprot    int - this is the protection for a new log file.
//		    The leading 0 is significant, so you should
//		    set it with something like 0644.
//
//	-loglevel   stirng - output log level. The type of log entries
//		    that will be output to the log.
//		    Env: LOG_LEVEL. Default: "INFO | ERROR | WARING";
//
//	-logfilter  string - filter log entries through this
//		    regex pattern. Only entries that contain
//		    the pattern will be output.
//		    Env: LOG_FILTER. Default: none.
//
//	-logtee	    flag - Tee log output to cerr.
//
//	-logshowtime
//		    bool - write a time stamp to each
//		    log entry. Env: LOG_TIME. Default: true
//
//	-logshowlevel
//		    bool - output the level with each log entry
//		    Env: LOG_STAMP_LEVEL. Default: true.
//
//	-logshowloc bool - output source file and line with each
//		    log entry. Env: LOG_LOC. Default: true
//
//	-logmax	    long - max size of log file.
//		    Env: LOG_MAX. Default: 0 (unlimited)
//
//	-logtrim    long - log file trim size.
//		    Env: LOG_TRIM. Default: 0 ( 25% of max ).
//		    
//
//  There are many methods in this class that process and convert
//  command line arguments to program variables (i.e. arg*(...)). They
//  all expect a 'dest' variable, a 'description', an 'argId' and
//  an optional 'envVar' parameters. The numeric methods can also get
//  a 'min' and max value parameters.
//
//  The 'dest' parameter is the program variable to be set from the
//  argId or the environment variable. First it is set to the
//  envirnment variable's value (if one is found), then it is set
//  to the argument's value (again if one is found). So, the command
//  line overides any enveronment variable settings. If any errors
//  occure trying to process the arg, dest will not be modified.
//
//  The 'description' parameter is the description that will be
//  ised for the help output. It should be a short description
//  of how the arg is used by the application.
//
//  The 'argId' is the string identifier for the command line
//  argument. The command line args are searched for an exact
//  match with a preceiding '-' character. So, if 'argId' is "file"
//  then the corisponding command line arg would be "-file". The
//  argId's and there corrisponding values are treated as indepenant
//  sequences.
//
//      prog -a a_value -b b_value -c c_value
//	    is the same as
//	prog -a -b -c a_value b_value c_value
//
//  The argFlag method is the only one that does not look for
//  a corrispondig value. So if -x was a flag then the following
//  would examples would all produce the same results.
//
//      prog -x -a a_value -b b_value -c c_value
//      prog -a a_value -b -x b_value -c c_value
//      prog -a a_value -b b_value -x -c c_value
//	prog -x -a -b -c a_value b_value c_value
//	prog -a -b -x -c a_value b_value c_value
//	prog -a -b -c a_value -x b_value c_value
//
//  The 'envVar' parameter specifies an envronment variable to
//  be used for the value.
//
//  The 'min' and 'max' parameters specificy the numeric limits
//  for the arg. If min <= value <= max is not true, then
//  dest is not set an good() will return false.
//  
//
//  Data Types: - data types defined by this header
//
//  	Param
//
//	Param::Args
//	    This type is used to access the args through iterators.
//
//  Constructors:
//
//  	Param( int		mainArgc,
//	       char *		mainArgv[],
//	       const char *	version = 0,
//	       bool		useDefaultArgFn = false,
//	       const char *	logLevel = STLUTILS_DEFAULT_LOGLEVEL,
//	       bool		useDefaultLogfn = false,
//	       ios::open_mode	logOpenMode = (ios::out|ios::app)
//	       int		logOpenProt = 0664 );
//	    Construct an instance of the Param class. 'mainArgc' and
//	    mainArgv should be the original argv and argc from main
//	    (i.e. main( int argc, char * argv[] ). 'version' is the
//	    version identification for the application.
//	    If 'useDefaultArgFn' is true, then the argfile will
//	    be 'mainArgv[0].args'. 'logLevel' sets the output level for
//	    the log.  If 'useDefaultLogFn' is true, the logfile will
//	    be 'mainArgv[0].log'. 'logOpenMode' sets the default open
//	    mode for the log file. 'logOpenProg' sets the default
//	    protection for the log file.
//
//  Public Interface:
//
//	void
//	appendHelp( const char * helpText )
//	    This text will be added to the help message.
//
//	inline
//  	Log &
//  	log( void );
//	    Return a referance to the application's log.
//
//	inline
//  	Log &
//  	log( LogLevel::Level lvl );
//	    Set the logs entry level and return a referance to it.
//
//	inline
//  	const char *
//  	appName( void ) const ;
//	    Returns the name of the application. This comes from
//	    argv[0]. It only returns the name and not any directories.
//
//	inline
//  	const char *
//  	appFullName( void ) const;
//	    Returns the name of the application including any directory
//	    information (i.e. argv[0]).
//
//	inline
//	const char *
//	appVersion( void ) const
//	    Return the version infomation passed to the constructor.
//
//	pid_t
//	getpid( void )
//	    Return the process id for the application.
//
//	inline
//  	size_t
//  	count( void ) const;
//	    Return the number of unprocessed args. This includes
//	    the applications name, so it should always return at least
//	    '1'.
//
//	inline
//	Args::const_iterator
//	begin( void ) const
//	    Return an iterator for all unprocessed args. This includes argv[0].
//
//	inline
//	Args::const_iterator
//	end( void  ) const
//	    Return an iterator for the end of all unprocessed args.
//
//	inline
//	Args::const_iterator
//	beginAll( void ) const
//	    Return an interator for all args, included those that
//	    have already been processed.
//
//	inline
//	Args::const_iterator
//	endAll( void ) const
//	    Return an iterator for the end of all args.
//
//	inline
//  	const char *
//  	arg( size_t which = 1 );
//	    Return the arg at position 'which' from the processed args.
//
//	inline
//  	long
//  	argLong( size_t which = 1 );
//	    Return the arg at position 'which' from the processed
//	    args as a long.
//
//	inline
//  	double
//  	argDouble( size_t which = 1 );
//	    Return the arg at position 'which' from the processed
//	    args as a double.
//
//	inline
//  	const char *
//  	env( const char * envVar ) const;
//	    Return the value for the envrionment variable 'envVar'.
//
//	bool
//	setArgFileName( const char * name )
//	    Set the name of the argument file to use (i.e. -argfile).
//
//	virtual
//	bool
//	parseArgs( void )
//	    Process the default set of args used by Param.
//	    Returns true if there were no errors, else returns
//	    false. This is called by both readArgs and
//	    parseArgs( int argc, char * argv[] ), so any subclass
//	    (i.e. AppParam) should overide this function, call
//	    Param::parseArgs() then process it's args.
//
//	virtual
//	bool
//	parseArgs( int argc, char * argv[] )
//	    Reset the args to argv and process them by
//	    calling 'parseArgs( void )'. Note: the internal values
//	    set by processArgs will NOT be reset to there default
//	    values. Returns true if there were no errors, else
//	    returns false.
//
//	inline
//	bool
//	readArgs( const char * fileName )
//	    Open 'fileName' and set the args from it. Once all the
//	    args have been read, parseArgs( void ) is called to
//	    process them. The format for the file is each line is
//	    treated as one or two args. If there are spaces or tabs
//	    in a line then a space character, the line is treated as 2
//	    args (i.e. '-in' is one arg '-in this is an arg' is two args
//	    where  second arg is 'this is an arg'). Blank lines and
//	    lines starting with a '#' are treated as comments.
//	    Returns true if there were no errors, else returns false.
//
//	bool
//	readArgs( istream & src )
//	    Reads args from 'src' ( see readArgs( const char *) ).
//
//  	bool
//  	argStr( char * &	dest,
//		const char *	description,
//		const char *    argId,
//		const char *    envVar = 0 );
//
//  	bool
//  	argStr( string &	dest,
//		const char *	description,
//		const char *    argId,
//		const char *    envVar = 0 );
//
//  	bool
//  	argStr( RWCString &	dest,
//		const char *	description,
//		const char *    argId,
//		const char *    envVar = 0 );
//
//  	bool
//  	argStr( Str &		dest,
//		const char *	description,
//		const char *    argId,
//		const char *    envVar = 0 );
//	    Process the arg and/or environment variable and set 'dest'
//	    to it's value. Return true if dest was modified.
//
//  	bool
//  	argInt( Int & 	    	dest,
//		const char *	description,
//		const char *    argId,
//	    	const char *    envVar = 0,
//		int	    	minVal = INT_MIN,
//		int	    	maxVal = INT_MAX );
//
//  	bool
//  	argUInt( unsigned int &	    dest,
//		 const char *	    description,
//		 const char *       argId,
//		 const char *       envVar = 0,
//		 unsigned int	    minVal = 0,
//		 unsigned int       maxVal = UINT_MAX );
//
//  	bool
//  	argShort( short &    	dest,
//		  const char *	description,
//		  const char *  argId,
//		  const char *  envVar = 0,
//		  short	    	minVal = SHRT_MIN,
//		  short	    	maxVal = SHRT_MAX );
//
//  	bool
//  	argUShort( unsigned short & dest,
//		   const char *	    description,
//		   const char *     argId,
//		   const char *     envVar = 0,
//		   unsigned short   minVal = 0,
//		   unsigned short  maxVal = USHRT_MAX );
//
//  	bool
//  	argLong( long &	    	dest,
//		 const char *	description,
//		 const char *   argId,
//		 const char *   envVar = 0,
//		 long	    	minVal = LONG_MIN,
//		 long	    	maxVal = LONG_MAX );
//
//  	bool
//  	argULong( unsigned long & dest,
//		  const char *	  description,
//		  const char *    argId,
//		  const char *    envVar = 0,
//		  unsigned long   minVal = 0,
//		  unsigned long   maxVal = ULONG_MAX );
//	    Process the arg and/or environment variable,
//	    convert it to the appropriate type, and set 'dest'
//	    to it's value. The value is converted the same
//	    way that 'c' does. A leading '0' causes an octal
//	    conversion and a leading '0x' causes a hex conversion.
//	    Return true if dest was set.
//
//  	bool
//  	argDouble( double & 	dest,
//		   const char *	description,
//		   const char * argId,
//		   const char * envVar = 0 );
//
//  	bool
//  	argBool( bool &	    	dest,
//		 const char *   description,
//		 const char *   argId,
//		 const char *   envVar = 0 );
//	    Process an arg and/or environment variable and set
//	    dest according to it's value. The following are
//	    understood and converted to true (case is NOT
//	    significant): non-zero number, 't', 'y', 'true', 'yes',
//	    and 'on'. The following are converted to false: 'f', 'n',
//	    'false', 'no', 'off'. Returns true if dest was set.
//		 
//  	bool
//  	argFlag( bool &	    	dest,
//		 const char *   description,
//		 const char *   argId,
//		 const char *   envVar = 0 );
//	    Process and arg and/or environment variable and
//	    set dest to 'true' if it exist. This is the only one
//	    of the 'arg' methods that does not expect a value along
//	    with the identifier.
//
//    	bool
//  	argDateTime( time_t &	    dest,
//		     const char *   description,
//		     const char *   argId,
//		     const char *   envVar = 0 );
//		     
//  	bool
//  	argDateTime( DateTime &	    dest,
//		     const char *   description,
//		     const char *   argId,
//		     const char *   envVar = 0 );
//
//  	bool
//  	argDateTime( RWTime &	    dest,
//		     const char *   description,
//		     const char *   argId,
//		     const char *   envVar = 0 );
//	    Process an arg and/or environment variable and
//	    set dest to the corrisponding date & time value.
//	    The format expected is 'MM/DD/YY HH:MM' and optional
//	    seconds (i.e. 11/28/96 14:25:15). Returns true
//	    if dest was set.
//
//  	bool
//  	argDate( RWDate &	dest,
//		 const char *   description,
//		 const char *   argId,
//		 const char *   envVar = 0 );
//
//  	bool
//  	argDate( DateTime &	dest,
//		 const char *   description,
//		 const char *   argId,
//		 const char *   envVar = 0 );
//	    Process an arg and/or environment variable and
//	    set dest to the corrisponding date value.
//	    The format expected is 'MM/DD/YY'. (i.e. 11/28/96 ).
//	    Returns true if dest was set.
//
//  	bool
//  	argTime( RWTime &	dest,
//		 const char *   description,
//		 const char *   argId,
//		 const char *   envVar = 0 );
//
//  	bool
//  	argTime( DateTime &	dest,
//		 const char *   description,
//		 const char *   argId,
//		 const char *   envVar = 0 );
//	    Process an arg and/or environment variable and
//	    set dest to the corrisponding time value.
//	    The format expected is 'HH:MM:SS'. (i.e. 15:23:30 ).
//	    Returns true if dest was set.
//
//
//	inline
//     	bool
//  	help( void ) const
//	    Return's true if the help flag was specified on the
//	    command line (i.e. '-help' ).
//
//	inline
//      bool
//  	allArgs( void ) const;
//	    Returns true if all arguments have been processed.
//
//	inline
//  	void
//  	abort( int  	    exitStatus = 1,
//     	       bool 	    showArgs = false,
//	       const char * srcFile = 0,
//	       long	    srcLine = 0,
//	       ostream &    dest = cerr );
//	    Exit the program with 'exitStatus' and output a
//	    message to 'dest'. If 'showArgs' is true, the help
//	    message is output. 'srcFile' and 'srcLine' should be
//	    the location abort is called from (i.e. __FILE__, __LINE__ ).
//
//	virtual
//	ostream &
//	toStream( ostream & dest )
//	    Output the help message to the stream 'dest'. Returns dest
//
//  	virtual
//	bool
//  	good( void ) const;
//  	    Returns true if there are no detected errors associated
//  	    with this class, otherwise FALSE.
//
//  	virtual
//	const char *
//  	error( void ) const;
//  	    Returns as string description of the state of the class.
//
//  	virtual
//	const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. Param )
//
//  Protected:
//
//  Private:
//
//  Example:
//
//	Create a class called AppParam that is a subclass
//	of param. Put all your arguments into it and instanciate
//	it from main().
//
//	I highly recommend you 'new' it to a global pointer. This will
//	give you both global access and control over construction order.
//
//	There are helper macros defined that depend on the existance of
//	a global AppParam * App.
//
//	* AppParam.hh * START * 
//	
//	#include <Param.hh>
//	#include <string
//	
//	class AppParam : public Param
//	{
//	
//	public:
//	
//	  AppParam( int & argv, char ** argc, const char * ver = 0 );
//	  ~AppParam( void );
//	
//	  bool parseArgs( void );
//
//	  const string & inputFileName() { return( vInputFileName ); };
//	  
//	protected:
//	
//	private:
//	
//	  AppParam( const AppParam & copyFrom );
//	  AppParam & operator=( const AppParam & assignFrom );
//	
//	  string  vInputFileName;
//	  
//	};
//	
//	extern AppParam * App;
//	
//	inline
//	AppParam::AppParam( int & argc, char ** argv, const char * ver )
//	  : Param( argc, argv, ver ),
//	    vInputFileName( "./inputfile.data" )
//	{
//	  parseArgs();
//	}
//	
//	inline
//	AppParam::~AppParam( void )
//	{
//	}
//	
//	* AppParam.hh * END *
//
//      * AppParam.C * END *
//
//	bool
//	AppParam::parseArgs( void )
//	{
//	  bool status = Param::parseArgs();
//
//	  status &= argStr( vInputFileName, "input file name", "in" );
//	
//	  string dataDir;
//	  status &= argStr( dataDir, "input directory", "dir", "DATA_DIR" );
//	
//	  if( dataDir.size() )
//	    vInputFileName.replace( 0, 1, dataDir );
//
//	  return( status );
//      }
//
//	* AppParam.C * END *
//
//	*  main.C * START *
//	
//	#include "AppParam.hh"
//	
//	const char * Version = "Param Demo V1.1";
//	
//	AppParam * App = 0;
//	
//	int
//	main( int argc, char * argv[] )
//	{
//	  if( ! (App = new AppParam( argc, argv, Version ) ) )
//	    {
//	       cerr << "Can't new AppParam!" << endl;
//	       exit( 1 );
//	    }
//	
//	  if( App->help() || ! App->good() )
//	    {
//	       App->abort( 0, true );
//	    }
//	
//	  cout << "Input is: " << App->inputFileName() << endl;
//	}
//	
//	* main.C * END *
//
// See Also:
//
// Files:
//
// Documented Ver: 3.14
//
// Tested Ver:
//
// Revision Log:
//
// $Log$
// Revision 3.16  1997/09/17 11:08:38  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.15  1997/09/16 11:24:19  houghton
// Added startTime method().
// Added logStartInfo method().
//
// Revision 3.14  1997/08/08 13:20:24  houghton
// Added appendHelp().
// Added -version support.
// Updated documentation.
//
// Revision 3.13  1997/07/28 16:46:21  houghton
// Added default log file support.
//
// Revision 3.12  1997/04/04 20:54:35  houghton
// Changed constructor.
// Added logmode & logprot args.
//
// Revision 3.11  1997/03/26 12:31:21  houghton
// Added constructor.
// Added setArgFileName.
//
// Revision 3.10  1997/03/21 15:39:55  houghton
// Changed readargs is now a protected member (was public).
//
// Revision 3.9  1997/03/21 12:27:26  houghton
// Changed Args to a deque (should improve performance).
// Added dump().
//
// Revision 3.8  1997/03/17 14:16:27  houghton
// Added AppTest macro.
//
// Revision 3.7  1997/03/03 19:04:13  houghton
// Bug-Fix: had and extra ',' at last ErrorNum enum.
//
// Revision 3.6  1997/03/03 14:37:21  houghton
// Removed support for RW Tools++.
//
// Revision 3.5  1997/01/18 17:33:21  houghton
// Bug-Fix: Linux - had to change the order of includes. I think this is
//    due to a bug in gcc 2.7. I should be able to change the order back
//    when 2.8 is released.
//
// Revision 3.4  1996/11/22 12:24:45  houghton
// Added AppDebug.
// Changed default log level to include 'Info'.
//
// Revision 3.3  1996/11/19 22:08:22  houghton
// Bug-Fix: remove parse flag from constructor - calling a virtual
//     from the constructor does NOT call the sub class's method.
//     so parseArgs has to be call from the app or sub class.
// Bug-Fix: there is no need for ARG_ERROR.
// Fixed header comments.
// Fixed example.
//
// Revision 3.2  1996/11/19 12:25:12  houghton
// Restructure header comments.
// Changed include lines to use " " instead of < > to accomidate rpm.
// Removed support for short file names to accomidate rpm.
// Major re-work to use 'string'
// Major re-work to use vector<string> for managing argv.
// Added readArgs to read arg from a istream.
//
// Revision 3.1  1996/11/14 01:23:54  houghton
// Changed to Release 3
//
// Revision 2.8  1996/11/08 11:46:10  houghton
// Removed Support for Str and DateTime.
//     (as required by Mike Alexander)
//
// Revision 2.7  1996/10/22 22:07:09  houghton
// Change: Added locStamp to turn on/off output of src file & line.
// Change: Added Support for Rogue Tools++ RWCString, RWDate & RWTime.
// Change: Rename arg methods for unsigned types.
//
// Revision 2.6  1996/04/27 13:07:59  houghton
// Added support for LibLog.
//
// Revision 2.5  1996/02/29 19:06:43  houghton
// *** empty log message ***
//
// Revision 2.4  1995/11/12 18:32:21  houghton
// Added logging macros.
//
// Revision 2.3  1995/11/10  14:11:43  houghton
// Cleanup (move final endif)
//
// Revision 2.2  1995/11/10  14:08:38  houghton
// Updated documentation comments
//
// Revision 2.1  1995/11/10  12:40:54  houghton
// Change to Version 2
//
// Revision 1.6  1995/11/05  15:28:44  houghton
// Revised
//
//

#endif // ! def _Param_hh_ 

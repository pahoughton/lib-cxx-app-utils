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

#include "ClueConfig.hh"
#include "Log.hh"
#include "LibLog.hh"
#include <string>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>

#define CLUE_DEFAULT_LOGLEVEL "ERROR | WARNING"

#define ALog( lvl )	LogIf( App->log(), lvl )

#define AppWarn	    ALog( LogLevel::Warn )
#define AppError    ALog( LogLevel::Error )
#define AppInfo	    ALog( LogLevel::Info )
#define AppDebug    ALog( LegLevel::Debug )


#if defined( CLUE_DEBUG )
#define inline
#endif

class Str;
class DateTime;
class RWCString;
class RWTime;
class RWDate;
class RWDBDateTime;

class Param
{

public:

  typedef vector< string >	Args;
  
  Param( int 		    mainArgc,
	 char *		    mainArgv[],
	 const char *	    version = 0,
	 const char *	    logLevel = CLUE_DEFAULT_LOGLEVEL );

  virtual ~Param( void );
  
  inline Log &     log( void );
  inline Log &     log( LogLevel::Level lvl );

  inline const char *    appName( void ) const ;
  inline const char *    appFullName( void ) const;
  inline const char *	 appVersion( void ) const;

  inline size_t    count( void ) const;

  inline Args::const_iterator	begin( void ) const;
  inline Args::const_iterator	end( void ) const;

  inline Args::const_iterator	beginAll( void ) const;
  inline Args::const_iterator	endAll( void ) const;
  
  inline const char *	arg( size_t which = 1 );
  inline long		argLong( size_t which = 1 );
  inline double		argDouble( size_t which = 1 );
  
  inline const char *	env( const char * envVar ) const;

  virtual bool	parseArgs( void );
  virtual bool	parseArgs( int argc, char * argv[] );
 
  inline bool	readArgs( const char * fileName );
  bool		readArgs( istream & src );

  bool	argStr( char * &  	 dest,
		const char *	 description,
		const char *     argId,
		const char *     envVar = 0 );
  bool	argStr( string &	dest,
		const char *	description,
		const char *    argId,
		const char *    envVar = 0 );  
  bool	argStr( RWCString &	dest,
		const char *	description,
		const char *    argId,
		const char *    envVar = 0 );
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
  bool	argDateTime( RWTime &	    dest,
		     const char *   description,
		     const char *   argId,
		     const char *   envVar = 0 );
  bool	argDate( RWDate &	    dest,
		 const char *       description,
		 const char *       argId,
		 const char *       envVar = 0 );
  bool	argDate( DateTime &	    dest,
		 const char *	    description,
		 const char *	    argId,
		 const char *	    envVar = 0 );
  bool	argTime( RWTime &	    dest,
		 const char *	    description,
		 const char *	    argId,
		 const char *	    envVar = 0 );  
  bool	argTime( DateTime &	    dest,
		 const char *	    description,
		 const char *	    argId,
		 const char *	    envVar = 0 );
  
  inline bool	help( void ) const;

  inline bool	allArgs( void ) const;

  inline void	abort( int  	    exitStatus = 1,
		       bool 	    showArgs = false,
		       const char * srcFile = 0,
		       long	    srcLine = 0,
		       ostream &    mesgDest = cerr );

  // libClue Common Class Methods
  
  virtual ostream & 	toStream( ostream & dest ) const;

  virtual bool	    	good( void ) const;
  virtual const char *	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;
  
  static const ClassVersion version;
  
protected:

private:

  Param( const Param & copyFrom );
  Param & operator=( const Param & assignFrom );

  string	    getArgValue( const char * argId, const char * envVar );
  bool		    getArgFlag( const char * argId, const char * envVar );

  size_t    appendHelp( const char *	argId,
			const char *	desc,
			const char *	envVar,
			const char *	value );

  string    	    helpString;

  Args		    allArgv;
  Args		    argv;
  
  string	    ver;
  
  Log	    	    appLog;

  bool    	    helpFlag;

  string    	    logFile;
  string    	    logOutputLevel;
  string	    logFilter;
  
  bool	    	    logTee;
  unsigned long	    logMaxSize;
  unsigned long	    logTrimSize;
  bool		    logTimeStamp;
  bool		    logLevelStamp;
  bool		    logLocStamp;
  
  enum ErrorNum
  {
    E_OK,
    E_RANGE,
    E_CONVERT,
    E_NO_VALUE,
    E_UNDEFINED,
  };

  static const char *	ErrorStrings[];
  
  struct Error
  {
    ErrorNum	errorNum;
    string	argId;
    string	envVar;
    string	desc;
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
//	-help	    flag - show usage help. The application must
//		    check the help() method and put the
//		    Param object on an ostream ( cout << param; )
//		    to actually output the help text.
//
//	-log	    String - log file name. File name that should be used
//		    for log output. Env: LOG_FILE. Default: cout
//
//	-loglevel   stirng - output log level. The type of log entries
//		    that will be output to the log.
//		    Env: LOG_LEVEL. Default: "ERROR | WARING";
//
//	-logfilter  string - filter log entries through this
//		    regex pattern. Only entries that contain
//		    the pattern will be output.
//		    Env: LOG_FILTER. Default: none.
//
//	-logtee	    flag - Tee log output to cerr.
//
//	-logtime    bool - write a time stamp to each
//		    log entry. Env: LOG_TIME. Default: true
//
//	-logstamplevel
//		    bool - output the level with each log entry
//		    Env: LOG_STAMP_LEVEL. Default: true.
//
//	-logloc	    bool - output source file and line with each
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
//  	Param( int	    mainArgc,
//	       char *	    mainArgv[],
//	       const char * version = 0,
//	       const char * logLevel = CLUE_DEFAULT_LOGLEVEL );
//	    Construct an instance of the Param class. 'mainArgc' and
//	    mainArgv should be the original argv and argc from main
//	    (i.e. main( int argc, char * argv[] ). 'version' is the
//	    version identification for the application. 'logLevel'
//	    sets the output level for the log. 
//
//  Public Interface:
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
// Revision Log:
//
// $Log$
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

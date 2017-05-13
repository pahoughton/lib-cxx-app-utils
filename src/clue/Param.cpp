// 1995-01-26 (cc) Paul Houghton <paul4hough@gmail.com>

#include "Param.hpp"
#include "StringUtils.hpp"
#include "Clue.hpp"
#include "Str.hpp"
#include "FileStat.hpp"
#include "DateTime.hpp"
#include "User.hpp"
#include "FileOp.hpp"

#include <unistd.h>


#define ARG_ID_ARGFILE	    "argfile"
#define ARG_ID_HELP	    "help"
#define ARG_ID_VERSION	    "version"
#define ARG_ID_GEN_ARGFILE  "gen-argfile"

namespace clue {

const char * Param::ErrorStrings[] =
{
  "ok",
  "range",
  "conversion",
  "no value for arg",
  "add filter",
  "open error log",
  "new ofstream",
  "no error log output level",
  "UNDEFIEND",
  0
};

Param::Param(
  int		    mainArgc,
  char **	    mainArgv,
  const char *	    appVersion,
  bool		    useDefaultArgFn,
  const char *	    logLevel,
  bool		    useDefaultLogFn,
  std::ios::openmode     logOpenMode
  )
  : versionText( appVersion ? appVersion : "version unknown" ),
    appLog( std::cout, logLevel ),
    helpFlag( false ),
    haveStopFlag( false ),
    logMode( logOpenMode ),
    logOutputLevel( logLevel ),
    errorLogFile( 0 ),
    errorLogId( LogBuf::badFilterId ),
    errorLogLevels( "ERROR | WARN" ),
    logTee( false ),
    logMaxSize( 0 ),
    logTrimSize( 0 ),
    logTimeStamp( true ),
    logLevelStamp( true ),
    logLocStamp( true ),
    generateArgFile( false )
{
  init( mainArgc, 0, mainArgv, useDefaultArgFn, useDefaultLogFn );
}

Param::Param(
  int		    mainArgc,
  char const **     mainArgv,
  const char *	    appVersion,
  bool		    useDefaultArgFn,
  const char *	    logLevel,
  bool		    useDefaultLogFn,
  std::ios::openmode	    logOpenMode
  )
  : versionText( appVersion ? appVersion : "version unknown" ),
    appLog( std::cout, logLevel ),
    helpFlag( false ),
    haveStopFlag( false ),
    logMode( logOpenMode ),
    logOutputLevel( logLevel ),
    errorLogFile( 0 ),
    errorLogId( LogBuf::badFilterId ),
    errorLogLevels( "ERROR | WARN" ),
    logTee( false ),
    logMaxSize( 0 ),
    logTrimSize( 0 ),
    logTimeStamp( true ),
    logLevelStamp( true ),
    logLocStamp( true ),
    generateArgFile( false )
{
  init( mainArgc, mainArgv, 0, useDefaultArgFn, useDefaultLogFn );
}

void
Param::init(
  int		    mainArgc,
  char const **	    constMainArgv,
  char **	    mainArgv,
  bool		    useDefaultArgFn,
  bool		    useDefaultLogFn )
{
  if( _clueLibLog  == 0 )
    _clueLibLog = &appLog;

  if( logOutputLevel.size() )
    appLog.setOutputLevel( logOutputLevel.c_str() );

  {
    const char ** tArgv = mainArgv ? (const char **)mainArgv : constMainArgv;

    for( size_t a = 0; a < mainArgc; ++a ) {

      Str tmp(tArgv[a]);
      // stop @ --
      if( (! haveStopFlag)
	  && tmp.size() == 2
	  && tmp[0] == '-' && tmp[1] == '-' )
	haveStopFlag = true;

      allArgv.push_back( tmp );
    }
  }

  argv = allArgv;

  // remove first arg (i.e appName).
  argv.erase( argv.begin() );

  if( useDefaultArgFn )
    argFile << appName() << ".args" ;

  if( useDefaultLogFn )
    logFile << appName() << ".log" ;

}

Param::~Param( void )
{
  if( _clueLibLog == &appLog )
    _clueLibLog = 0;

  if( errorLogFile )
    delete errorLogFile;
}

void
Param::appendHelp( const char * text )
{
  if( text )
    helpText = text;
}

const char *
Param::appName( void ) const
{
  return( basename( allArgv[0].c_str() ) );
}

const char *
Param::appFullName( void ) const
{
  return( allArgv[0].c_str() );
}

const char *
Param::appVersion( void ) const
{
  return( versionText.c_str() );
}

pid_t
Param::getpid( void ) const
{
  return( ::getpid() );
}

const DateTime &
Param::startTime( void ) const
{
  return( appStartTime );
}

Log &
Param::logStartInfo( void )
{
  appLog( LogLevel::Info )
    << appName() << '(' << getpid() << ") Started";

  if( ! appLog.getTimeStamp() )
    appLog << " at " << appStartTime;

  appLog << '.' << std::endl;
  return( appLog );
}

Log &
Param::logExitInfo( int exitCode )
{
  if( exitCode )
    appLog( LogLevel::Info );
  else
    appLog( LogLevel::Error );

  appLog << appName() << '(' << getpid() << ") Completed";

  if( ! appLog.getTimeStamp() )
    appLog << " at " << DateTime( time(0), true );

  appLog << '.' << std::endl;

  return( appLog );
}

bool
Param::parseArgs( void )
{
  argv = allArgv;

  // remove first arg (i.e. appName )
  argv.erase( argv.begin() );

  Str argFileEnvVar( appName() );

  argFileEnvVar.upcase();
  argFileEnvVar << "_ARGFILE";

  argStr( argFile,
	  "FILENAME",
	  "Name of file to read args from.",
	  0,
	  false,
	  ARG_ID_ARGFILE,
	  argFileEnvVar );

  if( argFile.size() )
    {
      readArgs( argFile.cstr() );
      fileArgs = allFileArgs;
    }

  argFlag( helpFlag,
	   "show usage help.",
	   0,
	   ARG_ID_HELP );

  bool	verFlag = false;
  argFlag( verFlag,
	   "show version and exit",
	   0,
	   ARG_ID_VERSION );

  if( verFlag && ! helpFlag )
    {
      if( versionText.size() )
	{
	  std::cout << "Version: " << versionText;
	}
      else
	{
	  std::cout << "Version: (unknown)";
	}
      std::cout << std::endl;
      exit( 0 );
    }

  argFlag( generateArgFile,
	   "generate an args file.",
	   0,
	   ARG_ID_GEN_ARGFILE );

  argStr( logFile,
	  "FILENAME",
	  "log file name.",
	  0,
	  false,
	  "log-file",
	  "LOG_FILE" );

  Str	  logModeStr = IosOpenModeToString( logMode );

  argStr( logModeStr,
	  "MODE STRING",
	  "log open mode.",
	  0,
	  false,
	  "log-mode",
	  "LOG_MODE" );

  logMode = IosOpenModeFromString( logModeStr );

  argStr( logOutputLevel,
	  "LOG LEVEL",
	  "log output level.",
	  0,
	  false,
	  "log-level",
	  "LOG_LEVEL" );

  argStr( logFilter,
	  "REGEX",
	  "regex for filtering log enties",
	  0,
	  false,
	  "log-filter",
	  "LOG_FILTER" );

  argFlag( logTee,
	   "Tee log output to std::cerr.",
	   0,
	   "log-tee",
	   "LOG_TEE" );

  argBool( logTimeStamp,
	   "BOOL",
	   "output time stamp with log entry.",
	   0,
	   false,
	   "log-show-time",
	   "LOG_SHOW_TIME" );

  argBool( logLevelStamp,
	   "BOOL",
	   "output level with log entry.",
	   0,
	   false,
	   "log-show-level",
	   "LOG_SHOW_LEVEL" );

  argBool( logLocStamp,
	   "BOOL",
	   "output source location with log entry",
	   0,
	   false,
	   "log-show-loc",
	   "LOG_SHOWLOC" );

  argULong( logMaxSize,
	    "SIZE",
	    "log file max size.",
	    0,
	    false,
	    "log-max",
	    "LOG_MAX" );

  argULong( logTrimSize,
	    "SIZE",
	   "log file trim size.",
	    0,
	    false,
	   "log-trim",
	   "LOG_TRIM" );

  argStr( errorLogName,
	  "FILENAME",
	  "error log file name.",
	  0,
	  false,
	  "error-log",
	  "ERROR_LOG" );

  argStr( errorLogLevels,
	  "LOG LEVEL",
	  "error log output levels.",
	  0,
	  false,
	  "error-log-level",
	  "ERROR_LOG_LEVEL" );

  if( logFilter.size() )
    appLog.filter( logFilter.c_str() );

  if( logTee )
    appLog.tee( std::cerr );

  appLog.setTimeStamp( logTimeStamp );
  appLog.setLevelStamp( logLevelStamp );
  appLog.setLocStamp( logLocStamp );

  if( logOutputLevel.size() )
    appLog.setOutputLevel( logOutputLevel.c_str() );

  if( logTrimSize )
    appLog.setTrimSize( logTrimSize );

  if( logMaxSize )
    appLog.setMaxSize( logMaxSize );

  if( ! helpFlag )
    {
      if( logFile.size() )
	appLog.setFileName( logFile.c_str(),
			    logMode );

      if( errorLogName.size() && errorLogLevels.size() )
	{
	  LogLevel errLevel( errorLogLevels );

	  if( errLevel.getOutput() != LogLevel::None )
	    {
	      errorLogFile = new std::ofstream( errorLogName,
					   std::ios::out | std::ios::app );

	      if( errorLogFile )
		{
		  if( (*errorLogFile).good() )
		    {
		      errorLogId = appLog.addFilter( (*errorLogFile).rdbuf(),
						     errLevel.getOutput() );
		      if( errorLogId == LogBuf::badFilterId )
			{
			  setError( E_ERRLOG_ADD,
				    "error-log",
				    "ERROR_LOG",
				    errorLogName );
			}
		    }
		  else
		    {
		      Str errDesc;

		      errDesc << " '"
			      << errorLogName
			      << "' - "
			      << strerror( errno );

		      setError( E_ERRLOG_OPEN,
				"error-log",
				"ERROR_LOG",
				errDesc );
		    }
		}
	      else
		{
		  setError( E_ERRLOG_NEW,
			    "error-log",
			    "ERROR_LOG",
			    0 );
		}
	    }
	  else
	    {
	      Str errDesc;
	      errDesc << "(" << errorLogLevels << ')';

	      setError( E_ERRLOG_LEVEL,
			"error-log-level",
			"ERROR_LOG_LEVEL",
			errDesc );
	    }
	}
    }

  return( good() );
}

bool
Param::parseArgs( int argCount, char * argValue[] )
{
  allArgv.erase( allArgv.begin(), allArgv.end() );

  for( int a = 0; a < argCount; ++a )
    {
      Str	tmp = argValue[a];

      allArgv.push_back( tmp );
    }

  return( parseArgs() );
}



bool
Param::readArgs( std::istream & src )
{
  Str    line;

  allFileArgs.erase( allFileArgs.begin(), allFileArgs.end() );

  while( getline( src, line ).good() )
    {
      // look for the first non white space char
      Str::size_type	pos = line.find_first_not_of( " \t" );

      // comment or blank line
      if( pos == Str::npos || line[pos] == '#' )
	continue;

      Str::size_type	delimPos = line.find_first_of( " \t", pos );

      if( delimPos != Str::npos )
	{
	  allFileArgs.push_back( line.substr( pos, delimPos - pos ) );

	  Str::size_type valuePos = line.find_first_not_of( " \t",
							    delimPos );

	  if( valuePos != Str::npos )
	    {
	      Str::size_type valueEnd = line.find_last_not_of( "# \t" );
	      allFileArgs.push_back( line.substr( valuePos, valueEnd ) );
	    }
	}
      else
	{
	  allFileArgs.push_back( line.substr( pos ) );
	}
    }

  return( good() );
}

bool
Param::argStr(
  char * &  	dest,
  const char *	valueName,
  const char *	shortDesc,
  const char *	longDesc,
  bool		required,
  const char *  argId,
  const char * 	envVar
  )
{
  Str    arg	    = getArgValue( argId, envVar );

  if( arg.size() )
    {
      dest = new char[ arg.size() + 5 ];
      arg.copy( dest, arg.size() + 2 );
      dest[ arg.size() ] = 0;
    }

  appendArgInfo( argId, valueName, shortDesc, longDesc, required, envVar, dest );

  return( arg.size() != 0 );
}

bool
Param::argStr(
  Str &  	dest,
  const char *	valueName,
  const char *	shortDesc,
  const char *	longDesc,
  bool		required,
  const char *  argId,
  const char * 	envVar
  )
{
  Str    arg	     = getArgValue( argId, envVar );

  if( arg.size() )
    dest = arg;

  appendArgInfo( argId, valueName, shortDesc, longDesc, required, envVar, dest );

  return( arg.size() != 0 );
}

bool
Param::argChar(
  char &	dest,
  const char *	valueName,
  const char *	shortDesc,
  const char *	longDesc,
  bool		required,
  const char *	argId,
  const char *	envVar
  )
{
  Str	arg = getArgValue( argId, envVar );

  if( arg.size() == 1 ) {
    dest = arg[0];
  } else if( isprint( dest ) ) {
    arg << dest;
  }

  if( arg.size() > 1 )
    {
      Str tmpErrDesc;
      tmpErrDesc << ": '" << arg << "' not a single character.";

      setError( E_RANGE, argId, envVar, tmpErrDesc.c_str() );
    }

  appendArgInfo( argId, valueName, shortDesc, longDesc, required, envVar, arg.c_str() );
  return( arg.size() != 0 );
}

template< class NumT >
inline
bool
_StlUtilsParamArgNum(
  Str &		arg,
  NumT &  	dest,
  NumT	    	minVal,
  NumT	    	maxVal,
  Str &		errDesc
  )
{
  NumT	    tmp  = 0;

  bool conv = StringTo( tmp, arg.c_str() );

  if( conv )
    {
      if( tmp >= minVal && tmp <= maxVal )
	{
	  dest = tmp;
	}
      else
	{
	  errDesc = ": '";
	  errDesc += StringFrom( tmp );
	  errDesc += "' not between '";
	  errDesc += StringFrom( minVal );
	  errDesc += "' and '";
	  errDesc += StringFrom( maxVal );
	  errDesc += "'.";
	}
    }

  return( conv );
}

#define PARAM_ARG_NUM( Name, NumType, Snum )				\
bool									\
Param::Name(								\
  NumType &  	dest,							\
  const char *	valueName,						\
  const char *	shortDesc,						\
  const char *	longDesc,						\
  bool		required,						\
  const char *  argId,							\
  const char * 	envVar,							\
  NumType    	minVal,							\
  NumType    	maxVal							\
  )									\
{									\
  Str    arg	 = getArgValue( argId, envVar, Snum );			\
  bool	    conv = false;						\
									\
  if( arg.size() )							\
    {									\
      NumType	tmp = 0;						\
									\
      conv = StringTo( tmp, arg.c_str() );				\
									\
      if( conv )							\
	{								\
	  if( tmp >= minVal && tmp <= maxVal )				\
	    {								\
	      dest = tmp;						\
	    }								\
	  else								\
	    {								\
	      Str tmpErrDesc;						\
									\
	      tmpErrDesc = ": '";					\
	      tmpErrDesc += StringFrom( tmp );				\
	      tmpErrDesc += "' not between '";				\
	      tmpErrDesc += StringFrom( minVal );			\
	      tmpErrDesc += "' and '";					\
	      tmpErrDesc += StringFrom( maxVal );			\
	      tmpErrDesc += "'.";					\
									\
	      setError( E_RANGE, argId, envVar, tmpErrDesc.c_str() );	\
	      conv = false;						\
	    }								\
	}								\
      else								\
	{								\
	  Str tmpErrDesc;						\
									\
	  tmpErrDesc = "'";						\
	  tmpErrDesc += arg;						\
	  tmpErrDesc += "'";						\
									\
	  setError( E_CONVERT, argId, envVar, tmpErrDesc.c_str() );	\
	}								\
    }									\
									\
  appendArgInfo( argId,							\
		 valueName,						\
		 shortDesc,						\
		 longDesc,						\
		 required,						\
		 envVar,						\
		 StringFrom( dest ) );					\
									\
  return( conv );							\
}

PARAM_ARG_NUM( argInt, int, true )
PARAM_ARG_NUM( argUInt, unsigned int, false )
PARAM_ARG_NUM( argShort, short, true )
PARAM_ARG_NUM( argUShort, unsigned short, false )
PARAM_ARG_NUM( argLong, long, true )
PARAM_ARG_NUM( argULong, unsigned long, false )
PARAM_ARG_NUM( argLongLong, long long, true )
PARAM_ARG_NUM( argULongLong, unsigned long long, false )

;

bool
Param::argDouble(
  double &  	dest,
  const char *	valueName,
  const char *	shortDesc,
  const char *	longDesc,
  bool		required,
  const char *  argId,
  const char * 	envVar
  )
{
  Str    arg	 = getArgValue( argId, envVar, true );
  bool	    conv = false;

  if( arg.size() )
    {
      double tmp;

      conv = StringTo( tmp, arg.c_str() );

      if( conv )
	{
	  dest = tmp;
	}
      else
	{
	  Str tmpErrDesc;

	  tmpErrDesc = "'";
	  tmpErrDesc += arg;
	  tmpErrDesc += "'";

	  setError( E_CONVERT, argId, envVar, tmpErrDesc.c_str() );
	}

    }

  appendArgInfo( argId, valueName, shortDesc, longDesc, required, envVar, StringFrom( dest ) );

  return( conv );
}

bool
Param::argBool(
  bool &  	dest,
  const char *	valueName,
  const char *	shortDesc,
  const char *	longDesc,
  bool		required,
  const char *  argId,
  const char * 	envVar
  )
{
  Str    arg	 = getArgValue( argId, envVar );
  bool	    conv = false;

  if( arg.size() )
    {
      bool tmp;

      conv = StringTo( tmp, arg.c_str() );

      if( conv )
	{
	  dest = tmp;
	}
      else
	{
	  Str tmpErrDesc;

	  tmpErrDesc = "'";
	  tmpErrDesc += arg;
	  tmpErrDesc += "'";

	  setError( E_CONVERT, argId, envVar, tmpErrDesc.c_str() );
	}
    }

  appendArgInfo( argId, valueName, shortDesc, longDesc, required, envVar,
	      (dest ? "true" : "false" ) );

  return( conv );
}

bool
Param::argFlag(
  bool &  	dest,
  const char *	shortDesc,
  const char *	longDesc,
  const char *  argId,
  const char * 	envVar
  )
{
  dest = getArgFlag( argId, envVar );

  // note: appendArgFile() depends on the 't'
  //    to determin if the flag is set.
  appendArgInfo( argId, 0, shortDesc, longDesc, false, envVar,
	      (dest ? "true" : "flag"), true );

  return( dest );
}

bool
Param::argDateTime(
  time_t &  	dest,
  const char *	valueName,
  const char *	shortDesc,
  const char *	longDesc,
  bool		required,
  const char *  argId,
  const char * 	envVar
  )
{
  DateTime  tmp;
  bool	    conv = argDateTime( tmp,
				valueName,
				shortDesc,
				longDesc,
				required,
				argId,
				envVar );

  if( conv )
    {
      dest = tmp.timet();
    }

  return( conv );
}

bool
Param::argDateTime(
  DateTime &  	dest,
  const char *	valueName,
  const char *	shortDesc,
  const char *	longDesc,
  bool		required,
  const char *  argId,
  const char * 	envVar
  )
{
  bool	    conv = false;

  Str    arg	 = getArgValue( argId, envVar );

  if( arg.size() )
    {
      DateTime	dt(0,true);
      dt.setValid( arg.c_str() );

      if( dt.good() )
	{
	  dest = dt;
	  conv = true;
	}
      else
	{
	  Str tmpErrDesc;

	  tmpErrDesc = "'";
	  tmpErrDesc += arg;
	  tmpErrDesc += "'";

	  setError( E_CONVERT, argId, envVar, tmpErrDesc.c_str() );
	}
    }

  appendArgInfo( argId, valueName,
		 shortDesc, longDesc,
		 required, envVar,
		 dest.str().c_str() );

  return( conv );
}


bool
Param::argDate(
  DateTime &  	dest,
  const char *	valueName,
  const char *	shortDesc,
  const char *	longDesc,
  bool		required,
  const char *  argId,
  const char * 	envVar
  )
{
  bool	    conv = false;

  Str    arg	 = getArgValue( argId, envVar );

  if( arg.size() )
    {
      DateTime	dt;
      dt.setValid( arg.c_str() );

      if( dt.good() )
	{
	  dest = dt;
	}
      else
	{
	  Str tmpErrDesc;

	  tmpErrDesc = "'";
	  tmpErrDesc += arg;
	  tmpErrDesc += "'";

	  setError( E_CONVERT, argId, envVar, tmpErrDesc.c_str() );
	}
    }

  appendArgInfo( argId, valueName,
		 shortDesc, longDesc,
		 required, envVar,
		 dest.str().c_str() );

  return( conv );
}

bool
Param::argTime(
  DateTime &  	dest,
  const char *	valueName,
  const char *	shortDesc,
  const char *	longDesc,
  bool		required,
  const char *  argId,
  const char * 	envVar
  )
{
  return( argDate( dest, valueName, shortDesc, longDesc, required, argId, envVar ) );
}


Str
Param::getArgValue( const char * argId, const char * envVar, bool sNum )
{
  Str	value;

  if( ! argId || ! argId[0] )
    return( value );

  // first look for file args
  {
    bool foundArg = false;

    // we don't want file args to override env values
    for( Args::iterator them = fileArgs.begin();
	 them != fileArgs.end();
	 ++ them )
      {
	if( matchArg( *them, argId ) )
	  {
	    foundArg = true;
	    // found it
	    for( ++ them; them != fileArgs.end(); ++ them )
	      {
		if( (*them).size()
		    && ( (*them)[0UL] != '-'
			 || ( sNum
			      && (*them).size() > 1
			      && isdigit( (*them)[1UL] ) ) ) )
		  {
		    foundArg = true;
		    value = *them;
		    fileArgs.erase( them );
		    break;
		  }
	      }
	    if( ! value.size() )
	      setError( E_NO_VALUE, argId, envVar, 0 );
	    break;
	  }
      }

    if( foundArg )
      {
	for( Args::iterator them = fileArgs.begin();
	     them != fileArgs.end();
	     ++ them )
	  {
	    if( (*them).size() > 1 &&
		(*them)[0UL] == '-' &&
		(*them).substr( 1 ).compare( argId ) == 0 )
	      {
		fileArgs.erase( them );
		break;
	      }
	  }
      }
  }

  // next see if there is an env value
  {
    const char *	envValue = env( envVar );
    if( envValue )
      value = envValue;
  }

  // now look for it in command line args
  {
    bool foundArg = false ;

    Args::iterator	them = argv.begin();
    for( ; them != argv.end(); ++ them )
      {
	// dont process any args after --
	if( (*them).size() == 2
	    && (*them)[0UL] == '-'
	    && (*them)[1UL] == '-' )
	  break;

	// look for -arg value
	if( matchArg( *them, argId ) )
	  {

	    // found it now get the value.
	    // and erase it from the vector.
	    for( them++; them != argv.end(); ++ them )
	      {
		if( (*them).size()
		    && ( (*them)[0UL] != '-'
			 || ( sNum
			      && (*them).size() > 1
			      && isdigit( (*them)[1UL] ) ) ) )
		  {
		    foundArg = true;
		    value = *them;
		    argv.erase( them );
		    break;
		  }
	      }

	    // no value for argId
	    if( ! value.size() )
	      setError( E_NO_VALUE, argId, envVar, 0 );

	    break;

	  }
	// look for -arg=value
	Str::size_type eqpos( (*them).find( '=' ) );

	if( eqpos != Str::npos
	    && matchArg( *them, argId, eqpos - 1 ) )
	  {
	    value = (*them).substr( eqpos + 1 );
	    // lie about foundArg because I can erase it myself
	    argv.erase( them );
	  }
      }
    // if I found it and got it's value,
    // then re-find and erase the id.
    //
    // I have to do this becuase once I call argv.erase
    // above, the iterator is no longer valid and I must
    // get a new iterator from the vector to erase
    // the id.
    //
    if( foundArg )
      {
	for( them = argv.begin(); them != argv.end(); ++ them )
	  {
	    if( matchArg( *them, argId ) )
	      {
		argv.erase( them );
		break;
	      }
	  }
      }
  }

  return( value );
}

bool
Param::getArgFlag( const char * argId, const char * envVar )
{
  bool value = false;

  const char *	envValue = env( envVar );

  if( !argId || ! argId[0] )
    return( value );

  // first look for file args
  {
    for( Args::iterator them = fileArgs.begin();
	 them != fileArgs.end();
	 ++ them )
      {
	if( matchArg( *them, argId ) )
	  {
	    // found it
	    value = true;
	    fileArgs.erase( them );
	    break;
	  }
      }
  }

  // next check for env values
  if( envValue )
    {
      Str envStr( envValue );
      value = envStr.toBool();
    }

  // now check command line args
  if( count() > 0 )
    {
      Args::iterator	them = argv.begin();
      for( ; them != argv.end(); ++ them )
	{
	// dont process any args after --
	  if( (*them).size() == 2
	      && (*them)[0UL] == '-'
	      && (*them)[1UL] == '-' )
	    break;

	  if( matchArg( *them, argId ) )
	    {
	      // found it now get the value
	      value = true;
	      argv.erase( them );
	      break;
	    }
	}
    }

  return( value );
}

bool
Param::haveErrorLog( void ) const
{
  return( errorLogFile != 0 );
}

void
Param::abort(
  int		exitStatus,
  bool		showArgs,
  const char *	srcFile,
  long		srcLine,
  std::ostream &	mesgDest )
{
  if( showArgs )
    mesgDest << *this << std::endl;

  if( exitStatus )
    mesgDest << "Aborted(" << exitStatus << ")";
  else
    mesgDest << "Exited";

  if( srcFile )
    mesgDest << ": " << srcFile << ':' << srcLine << ' ';

  if( log().rdbuf()->is_file() )
    mesgDest << ": see log (" << log().rdbuf()->getLogFileName()
	     << ") for more info." << std::endl;
  else
    mesgDest << '.' << std::endl;

  exit( exitStatus );
}



bool
Param::good( void ) const
{
  // This is a cheat!

  // If we are going to generate an args file, the logs man not
  // be good, but that doesn't matter for args generation.

  if( generateArgFile )
    return( true );


  return( appLog.good() && errors.size() == 0 );
}

const char *
Param::error( void ) const
{
  static Str errStr;

  errStr = "Param";

  if( good() )
    {
      errStr += ": ok";
    }
  else
    {
      Str::size_type	errorSize = errStr.size();

      if( ! appLog.good() )
	errStr << ": " << appLog.error() << std::endl;

      for( ErrorList::const_iterator them = errors.begin();
	   them != errors.end();
	   ++them )
	{
	  errStr += "  ";

	  if( (*them).argId.size() )
	    {
	      errStr += '-';
	      errStr += (*them).argId;
	    }

	  if( (*them).envVar.size() )
	    {
	      errStr += '(';
	      errStr += (*them).envVar;
	      errStr += ')';
	    }

	  errStr += ": ";
	  errStr += ErrorStrings[ (*them).errorNum ];

	  if( (*them).desc.size() )
	    {
	      errStr += ' ';
	      errStr += (*them).desc;
	    }

	  errStr += '\n';
	}

      if( errStr.size() == errorSize )
	errStr += ": unknown error";

    }

  return( errStr.c_str() );
}

std::ostream &
Param::toStream( std::ostream & dest ) const
{
  dest << "\n" << appName() << " usage help: \n\n";

  if( versionText.size() )
    {
      dest << "  Version: " << versionText;
    }
  else
    {
      dest << "  Version: (unknown)";
    }

  dest << "\n\n";

  if( helpText.size() )
    dest << helpText << "\n\n";

  dest << helpString;

  if( fileArgs.size() )
    {
      dest << "\nUnprocessed file args:\n" ;

      for( Args::const_iterator them = fileArgs.begin();
	   them != fileArgs.end();
	   ++ them )
	dest << "  " << (*them) << std::endl;
    }

  if( count() )
    {
      dest << "\nUnprocessed command line args:\n";

      Args::const_iterator them = argv.begin();
      for( ; them != argv.end(); ++ them )
	dest << "  " << (*them) << std::endl;
    }

  if( ! good() )
    dest << '\n' << error() << '\n';

  return( dest );
}

std::ostream &
Param::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

  if( ! Param::good() )
    dest << prefix << "Error: " << Param::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  Str pre;
  pre = prefix;
  pre += "appLog:";
  appLog.dumpInfo( dest, pre.c_str() );

  for( Args::size_type i = 0; i < allArgv.size(); i++ )
    {
      dest << prefix << "argv[" << i << "]:";
      if( i > 9 )
	dest << "  '";
      else
	dest << "   '";
      dest << allArgv[i] << "'\n";
    }

  for( Args::size_type f = 0; f < allFileArgs.size() ; ++ f )
    {
      dest << prefix << "fileArg[" << f << "]:";
      if( f > 9 )
	dest << "  '";
      else
	dest << "   '";
      dest << allFileArgs[f] << "'\n";
    }

  dest << '\n';

  dest << prefix << "helpFlag:       " << (int)helpFlag << '\n'
       << prefix << "logFile:        " << logFile << '\n'
       << prefix << "logOutputLevel: " << logOutputLevel << '\n'
       << prefix << "logTee:         " << (int)logTee << '\n'
    ;

  dest << prefix << "helpString: \n" << helpString << '\n';

  if( fileArgs.size() )
    {
      dest << "\nUnprocessed file args:\n" ;

      for( Args::const_iterator them = fileArgs.begin();
	   them != fileArgs.end();
	   ++ them )
	dest << "  " << (*them) << std::endl;
    }

  if( count() > 1 )
    {
      dest << "\nUnprocessed command line args:\n";

      Args::const_iterator them = argv.begin();
      for( ; them != argv.end(); ++ them )
	dest << "  " << (*them) << std::endl;
    }

  dest << '\n';

  return( dest  );
}

size_t
Param::appendArgInfo(
  const char * argId,
  const char * valueName,
  const char * shortDesc,
  const char * longDesc,
  bool	       required,
  const char * envVar,
  const char * value,
  bool	       isflag
  )
{
  size_t    argIdLen( strlen( argId ) );

  appendArgFile( argId,
		 argIdLen,
		 valueName,
		 shortDesc,
		 longDesc,
		 required,
		 envVar,
		 value,
		 isflag );
  return( appendHelp( argId,
		      argIdLen,
		      valueName,
		      shortDesc,
		      longDesc,
		      required,
		      envVar,
		      value ) );
}

size_t
Param::appendArgFile(
  const char *	argId,
  size_t	argIdLen,
  const char *  valueName,
  const char *  shortDesc,
  const char *  longDesc,
  bool	        required,
  const char *	envVar,
  const char *	value,
  bool		isflag
  )
{

  // i.e. don't put the flowing in args file:
  //    -argfile
  //	-help
  //	-version
  //	-gen-argfile
  //

  if( strcmp( argId, ARG_ID_ARGFILE )
      && strcmp( argId, ARG_ID_HELP )
      && strcmp( argId, ARG_ID_VERSION )
      && strcmp( argId, ARG_ID_GEN_ARGFILE ) )
    {
      if( isflag )
	{
	  if( value && value[0] == 't' )
	    argFileString << '-' << argId << '\n';
	  else
	    argFileString << "# -" << argId << '\n';
	}
      else
	{
	  size_t prefixWidth;

	  if( value && strlen( value ) )
	    {
	      prefixWidth = 1;
	      argFileString << '-' << argId << '\t';
	    }
	  else
	    {
	      prefixWidth = 3;
	      argFileString << "# -" << argId << '\t';
	    }

	  for( size_t width = argIdLen + prefixWidth + 8;
	       width < (8 * 3);
	       width += 8 )
	    argFileString << '\t';

	  if( value && strlen( value ) )
	    argFileString << value;

	  argFileString << '\n';
	}
    }

  return( argFileString.size() );
}


size_t
Param::appendHelp(
  const char *	argId,
  size_t	argIdLen,
  const char *  valueName,
  const char *  shortDesc,
  const char *  longDesc,
  bool	        required,
  const char *	envVar,
  const char *	value
  )
{
  Str argHelp;

  argHelp.setf( std::ios::left, std::ios::adjustfield );

  size_t    contLinePadSize(16);

  argHelp << shortDesc ;

  if( envVar )
    argHelp << " (" << envVar << ')' ;

  if( value && strlen( value ) )
    argHelp << " '" << value << "'\n" ;

  argHelp.wrap( 79, contLinePadSize );

  if( argIdLen >= 13 )
    {
      helpString << "  -" << argId << '\n';
    }
  else
    {
      argHelp[2UL] = '-';
      argHelp.replace( 3, argIdLen, argId );
    }

  helpString += argHelp;

  return( helpString.size() );
}

bool
Param::setError(
  ErrorNum	err,
  const char *	argId,
  const char *	envVar,
  const char *	desc
  )
{
  Error	e;

  e.errorNum	= err;

  if( argId )   e.argId	    = argId;
  if( envVar )	e.envVar    = envVar;
  if( desc )    e.desc	    = desc;

  errors.push_back( e );

  return( good() );
}

#if defined( STLUTILS_TEST )
int Stlutils_Prama_Gen_NoDate( 0 );
#endif

// If the user requested an argfile (i.e. -gen-argfile) then we
// should generate it, tell him about it and exit.bool

void
Param::genArgFile( bool exitApp ) const
{
  std::ostream * out;

  if( argFile.size() )
    {
      FileStat	fileStat( argFile );

      if( fileStat.good() )
	{
	  // backup existing argFile
	  FileOp	fileOp;
	  FilePath	destFn( argFile );

	  destFn << ".bak";
	  if( ! fileOp.copy( argFile.c_str(),
			     destFn.c_str() ) )
	    {
	      LLgError
		<< "gen args file - " << fileOp.error()
		<< std::endl;
	      if( _clueLibLog )
		(*_clueLibLog).close();

	      if( errorLogFile )
		delete errorLogFile;

	      if( exitApp )
		exit( 1 );
	    }
	}
      out = new std::ofstream( argFile );
    }
  else
    {
      out = &std::cout;
    }

  if( (*out).good() )
    {
      (*out) <<
	"#\n"
	;

      if( argFile.size() )
	(*out) << "# Title:        " << argFile.getFileName() << '\n';
      else
	(*out) << "# Title:        " << appName() << ".args\n";

      (*out) <<
	"# See Args Descriptions following args definitions.\n" <<
	"#\n" <<
	"# Generated by "
	;

      User  user;
      (*out) << user.getRealName();

      (*out) << " on ";

#if defined( CLUE_TEST )
      if( Stlutils_Prama_Gen_NoDate == 0 )
#endif
	(*out) << DateTime(time(0),true) << '\n';

      (*out) << argFileString << "\n\n" <<
	"#\n" <<
	"# Args Descriptioins:\n"
	"#\n"
	;
      {
	Str comment( helpString );

	comment.substitute( "\n","\n# " );

	(*out) << '#' << comment;
      }

      (*out) << '\n'
	;
    }

  bool status( (*out).good() ? true : false );

  if( out != &std::cout )
    delete out;

  if( helpFlag )
    std::cerr << (*this) << "\n";

  if( status )
    std::cerr << "\n Generated args file ";
  else
    std::cerr << "ERROR: Generate args file failed ";

  if( argFile.size() )
    std::cerr << '\'' << argFile << "'.\n";
  else
    std::cerr << "to std::cout.\n";

  std::cerr << std::endl;

  if( exitApp )
    exit( status ? 0 : 1 );
}

}; // namespace clue

//
// File:        Param.C
// Project:	StlUtils
// Desc:        
//              
//  Compiled sources for the Param class
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     01/26/95 14:43 
//
// Revision History: (See end of file for Revision Log)
//


#include "Param.hh"
#include "StringUtils.hh"
#include "StlUtilsMisc.hh"
#include "Str.hh"
#include "FileStat.hh"
#include "DateTime.hh"

#if defined( STLUTILS_HAS_USER )
#include "User.hh"
#endif

#include "FileOp.hh"

#include <unistd.h>

STLUTILS_VERSION(
  Param,
  "$Id$" );

#if defined( STLUTILS_DEBUG )
#include <Param.ii>
#endif

#define ARG_ID_ARGFILE	    "argfile"
#define ARG_ID_HELP	    "help"
#define ARG_ID_VERSION	    "version"
#define ARG_ID_GEN_ARGFILE  "gen-argfile"

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
  char *	    mainArgv[],
  const char *	    appVersion,
  bool		    useDefaultArgFn,
  const char *	    logLevel,
  bool		    useDefaultLogFn,
  ios::open_mode    logOpenMode,
  int		    logOpenProt
  )
  : versionText( appVersion ? appVersion : "version unknown" ),
    appLog( cout, logLevel ),
    helpFlag( false ),
    logMode( logOpenMode ),
    logProt( logOpenProt ),
    logOutputLevel( logLevel ),
    logTee( false ),
    logMaxSize( 0 ),
    logTrimSize( 0 ),
    logTimeStamp( true ),
    logLevelStamp( true ),
    logLocStamp( true ),
    generateArgFile( false ),
    errorLogFile( 0 ),
    errorLogId( LogBuf::badFilterId ),
    errorLogLevels( "ERROR | WARN" )
{
  if( _LibLog  == 0 )
    _LibLog = &appLog;

  if( logOutputLevel.size() )
    appLog.setOutputLevel( logOutputLevel.c_str() );

  for( int a = 0; a < mainArgc; ++a )
    {
      Str tmp = mainArgv[a];

      allArgv.push_back( tmp );
    }
  
  argv = allArgv;

  // remove first arg (i.e appName).
  argv.erase( argv.begin() );
  
  if( useDefaultArgFn )
    argFile << appName() << ".args" ;
    
  if( useDefaultLogFn )
    logFile << appName() << ".log" ;

  // setup the tm struct so we don't have to recalc
  appStartTime.setTm();
  
}

Param::~Param( void )
{
  if( _LibLog == &appLog )
    _LibLog = 0;
  
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

  appLog << '.' << endl;
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

  appLog << '.' << endl;
  
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
	  "Name of file to read args from.",
	  ARG_ID_ARGFILE,
	  argFileEnvVar );

  if( argFile.size() )
    {
      readArgs( argFile.cstr() );
      fileArgs = allFileArgs;
    }
  
  argFlag( helpFlag,
	   "show usage help.",
	   ARG_ID_HELP );

  bool	verFlag = false;
  argFlag( verFlag,
	   "show version and exit",
	   ARG_ID_VERSION );

  if( verFlag && ! helpFlag )
    {
      if( versionText.size() )
	{
	  cout << "Version: " << versionText;
	}
      else
	{
	  cout << "Version: (unknown)";
	}
      cout << endl;
      exit( 0 );
    }

  argFlag( generateArgFile,
	   "generate an args file.",
	   ARG_ID_GEN_ARGFILE );
  
  argStr( logFile,
	  "log file name.",
	  "log-file",
	  "LOG_FILE" );

  Str	  logModeStr = IosOpenModeToString( logMode );
  
  argStr( logModeStr,
	  "log open mode.",
	  "log-mode",
	  "LOG_MODE" );

  logMode = IosOpenModeFromString( logModeStr );
  
  argInt( logProt,
	  "log protection flag.",
	  "log-prot",
	  "LOG_PROT" );
  
  argStr( logOutputLevel,
	  "log output level.",
	  "log-level",
	  "LOG_LEVEL" );

  argStr( logFilter,
	  "regex for filtering log enties",
	  "log-filter",
	  "LOG_FILTER" );
  
  argFlag( logTee,
	   "Tee log output to cerr.",
	   "log-tee",
	   "LOG_TEE" );

  argBool( logTimeStamp,
	   "output time stamp with log entry.",
	   "log-show-time",
	   "LOG_SHOW_TIME" );

  argBool( logLevelStamp,
	   "output level with log entry.",
	   "log-show-level",
	   "LOG_SHOW_LEVEL" );

  argBool( logLocStamp,
	   "output source location with log entry",
	   "log-show-loc",
	   "LOG_SHOWLOC" );
  
  argULong( logMaxSize,
	  "log file max size.",
	  "log-max",
	  "LOG_MAX" );

  argULong( logTrimSize,
	   "log file trim size.",
	   "log-trim",
	   "LOG_TRIM" );
  
  argStr( errorLogName,
	  "error log file name.",
	  "error-log",
	  "ERROR_LOG" );

  argStr( errorLogLevels,
	  "error log output levels.",
	  "error-log-level",
	  "ERROR_LOG_LEVEL" );

  if( logFilter.size() )
    appLog.filter( logFilter.c_str() );
  
  if( logTee )
    appLog.tee( cerr );
  
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
			    logMode,
			    logProt );

      if( errorLogName.size() && errorLogLevels.size() )
	{
	  LogLevel errLevel( errorLogLevels );

	  if( errLevel.getOutput() != LogLevel::None )
	    {
	      errorLogFile = new ofstream( errorLogName,
					   ios::out | ios::app,
					   0664 );
      
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
Param::readArgs( istream & src )
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
  const char * 	desc,
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

  appendArgInfo( argId, desc, envVar, dest );

  return( arg.size() != 0 );
}

bool
Param::argStr(
  Str &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  Str    arg	     = getArgValue( argId, envVar );

  if( arg.size() )
    dest = arg;

  appendArgInfo( argId, desc, envVar, dest );

  return( arg.size() != 0 );
}

bool
Param::argChar(
  char &	dest,
  const char *	desc,
  const char *	argId,
  const char *	envVar
  )
{
  Str	arg = getArgValue( argId, envVar );

  if( arg.size() == 1 )
    dest = arg[0];

  if( arg.size() > 1 )
    {
      Str tmpErrDesc;
      tmpErrDesc << ": '" << arg << "' not a single character.";
      
      setError( E_RANGE, argId, envVar, tmpErrDesc.c_str() );
    }

  appendArgInfo( argId, desc, envVar, arg.c_str() );
  return( arg.size() != 0 );
}

template< class NumT >
inline
bool
_StlUtilsParamArgNum(
  Str &	arg,
  NumT &  	dest,
  NumT	    	minVal,
  NumT	    	maxVal,
  Str &	errDesc
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

#define PARAM_ARG_NUM( Name, NumType, Snum )				      \
bool									      \
Param::Name(								      \
  NumType &  	dest,							      \
  const char * 	desc,							      \
  const char *  argId,							      \
  const char * 	envVar,							      \
  NumType    	minVal,							      \
  NumType    	maxVal							      \
  )									      \
{									      \
  Str    arg	 = getArgValue( argId, envVar, Snum );			      \
  bool	    conv = false;						      \
  									      \
  if( arg.size() )							      \
    {									      \
      NumType	tmp = 0;						      \
									      \
      conv = StringTo( tmp, arg.c_str() );				      \
									      \
      if( conv )							      \
	{								      \
	  if( tmp >= minVal && tmp <= maxVal )				      \
	    {								      \
	      dest = tmp;						      \
	    }								      \
	  else								      \
	    {								      \
	      Str tmpErrDesc;						      \
									      \
	      tmpErrDesc = ": '";					      \
	      tmpErrDesc += StringFrom( tmp );				      \
	      tmpErrDesc += "' not between '";				      \
	      tmpErrDesc += StringFrom( minVal );			      \
	      tmpErrDesc += "' and '";					      \
	      tmpErrDesc += StringFrom( maxVal );			      \
	      tmpErrDesc += "'.";					      \
									      \
	      setError( E_RANGE, argId, envVar, tmpErrDesc.c_str() );	      \
	      conv = false;						      \
	    }								      \
	}								      \
      else								      \
	{								      \
	  Str tmpErrDesc;						      \
									      \
	  tmpErrDesc = "'";						      \
	  tmpErrDesc += arg;						      \
	  tmpErrDesc += "'";						      \
									      \
	  setError( E_CONVERT, argId, envVar, tmpErrDesc.c_str() );	      \
	}								      \
    }									      \
									      \
  appendArgInfo( argId, desc, envVar, StringFrom( dest ) );		      \
									      \
  return( conv );							      \
}

PARAM_ARG_NUM( argInt, int, true )
PARAM_ARG_NUM( argUInt, unsigned int, false )
PARAM_ARG_NUM( argShort, short, true )
PARAM_ARG_NUM( argUShort, unsigned short, false )
PARAM_ARG_NUM( argLong, long, true )
PARAM_ARG_NUM( argULong, unsigned long, false )

  ;

bool
Param::argDouble(
  double &  	dest,
  const char * 	desc,
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

  appendArgInfo( argId, desc, envVar, StringFrom( dest ) );

  return( conv );
}

bool
Param::argBool(
  bool &  	dest,
  const char * 	desc,
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

  appendArgInfo( argId, desc, envVar,
	      (dest ? "true" : "false" ) );

  return( conv );
}

bool
Param::argFlag(
  bool &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  dest = getArgFlag( argId, envVar );

  // note: appendArgFile() depends on the 't'
  //    to determin if the flag is set.
  appendArgInfo( argId, desc, envVar,
	      (dest ? "true" : "flag"), true );

  return( dest );
}

bool
Param::argDateTime(
  time_t &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  DateTime  tmp;
  bool	    conv = argDateTime( tmp, desc, argId, envVar );

  if( conv )
    {
      dest = tmp.getTimeT();
    }

  return( conv );
}

bool
Param::argDateTime(
  DateTime &  	dest,
  const char * 	desc,
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

  appendArgInfo( argId, desc, envVar, dest );

  return( conv );
}


bool
Param::argDate(
  DateTime &  	dest,
  const char * 	desc,
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

  appendArgInfo( argId, desc, envVar, dest );

  return( conv );
}

bool
Param::argTime(
  DateTime &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  return( argDate( dest, desc, argId, envVar ) );
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
	if( (*them).size() > 1 &&
	    (*them)[0UL] == '-' &&
	    (*them).substr( 1 ).compare( argId ) == 0 )
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
	// look for -arg value
	if( (*them).size() > 1
	    && (*them)[0UL] == '-'
	    && (*them).substr( 1 ).compare( argId ) == 0 )
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
	Str::size_type eqpos( Str::npos );
	
	if( (*them).size() > 1
	    && (*them)[0UL] == '-'
	    && (eqpos = (*them).find( '=' )) != Str::npos
	    && (*them).substr( 1, eqpos - 1 ).compare( argId ) == 0 )
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
	    if( (*them).size() > 1 &&
		(*them)[0UL] == '-' && 
		(*them).substr( 1 ).compare( argId ) == 0 )
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
	if( (*them).size() > 1 &&
	    (*them)[0UL] == '-' &&
	    (*them).substr( 1 ).compare( argId ) == 0 )
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
	  if( (*them).size() > 1 &&
	      (*them)[0UL] == '-' && 
	      (*them).substr( 1 ).compare( argId ) == 0 )
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
  ostream &	mesgDest )
{
  if( showArgs )
    mesgDest << *this << endl;

  if( exitStatus )
    mesgDest << "Aborted(" << exitStatus << ")";
  else
    mesgDest << "Exited";
  
  if( srcFile )
    mesgDest << ": " << srcFile << ':' << srcLine << ' ';

  if( log().rdbuf()->is_file() )
    mesgDest << ": see log (" << log().rdbuf()->getLogFileName()
	     << ") for more info." << endl;
  else
    mesgDest << '.' << endl;
  
  exit( exitStatus );
}



bool
Param::good( void ) const
{
  return( appLog.good() && errors.size() == 0 );
}

const char *
Param::error( void ) const
{
  static Str errStr;

  errStr = getClassName();
  
  if( good() )
    {
      errStr += ": ok";
    }
  else
    {
      Str::size_type	errorSize = errStr.size();
      
      if( ! appLog.good() )
	errStr << ": " << appLog.error() << endl;
      
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

const char *
Param::getClassName( void ) const
{
  return "Param";
}

const char *
Param::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer, appLog.getVersion( false ) ) );
}


ostream &
Param::toStream( ostream & dest ) const
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
	dest << "  " << (*them) << endl;
    }
	  
  if( count() )
    {
      dest << "\nUnprocessed command line args:\n";
      
      Args::const_iterator them = argv.begin();
      for( ; them != argv.end(); ++ them )
	dest << "  " << (*them) << endl;
    }

  if( ! good() )
    dest << '\n' << error() << '\n';
  
  return( dest );
}

ostream &
Param::dumpInfo(
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << Param::getClassName() << ":\n"
	 << Param::getVersion() << '\n';
    
  if( ! Param::good() )
    dest << prefix << "Error: " << Param::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  Str pre;
  pre = prefix;
  pre += "appLog:";
  pre += appLog.getClassName();
  pre += "::";
  appLog.dumpInfo( dest, pre.c_str(), false );
  
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
	dest << "  " << (*them) << endl;
    }
	  
  if( count() > 1 )
    {
      dest << "\nUnprocessed command line args:\n";
      
      Args::const_iterator them = argv.begin();
      for( ; them != argv.end(); ++ them )
	dest << "  " << (*them) << endl;
    }

  dest << '\n';
    
  return( dest  );
}

size_t
Param::appendArgInfo(
  const char * argId,
  const char * desc,
  const char * envVar,
  const char * value,
  bool	       isflag 
  )
{
  size_t    argIdLen( strlen( argId ) );
  
  appendArgFile( argId, argIdLen, desc, envVar, value, isflag );
  return( appendHelp( argId, argIdLen, desc, envVar, value ) );
}

size_t
Param::appendArgFile(
  const char *	argId,
  size_t	argIdLen,
  const char *	desc,
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
	      argFileString << '# -' << argId << '\t';
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
  const char *	desc,
  const char *	envVar,
  const char *	value
  )
{
  Str argHelp;

  argHelp.setf( ios::left, ios::adjustfield );

  size_t    contLinePadSize(16); 
    
  argHelp << desc ;

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
  
#if defined( OLD_WAY )
  Str::size_type len = helpString.size();
  
  size_t    argIdSize = strlen( argId );
  
  helpString += "  -";
  helpString += argId;
  if( argIdSize < 8 )
    helpString.append( 8 - argIdSize, ' ' );

  helpString += ' ';
  helpString += desc;

  if( envVar )
    {
      helpString += " (";
      helpString += envVar;
      helpString += ')';
    }

  if( value && strlen( value ) )
    {
      if( (strlen( value ) + ( helpString.size() - len) ) < 80 )
	helpString += " '";
      else
	helpString += "\n            '";

      helpString += value;
      helpString += "'\n";
    }
  else
    {
      helpString += " ''\n";
    }
#endif
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
Param::genArgFile( bool exitApp )
{
  ostream * out;

  if( argFile.size() )
    {
      FileStat	fileStat( argFile );

      if( fileStat.good() )
	{
	  // backup existing argFile
	  FileOp	fileOp;
	  FilePath	destFn( argFile );

	  destFn << ".bak";
	  if( ! fileOp.copy( argFile, destFn ) )
	    {
	      LogIf( log(), LogLevel::Error )
		<< "gen args file - " << fileOp.error()
		<< endl;
	      log().close();
	      
	      if( errorLogFile )
		delete errorLogFile;
	      
	      if( exitApp )
		exit( 1 );
	    }
	}
      out = new ofstream( argFile );
    }
  else
    {
      out = &cout;
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
	"# Project:      \n" <<
	"# Desc:         \n" <<
	"#\n" << 
	"#   See Args Descriptions following args definitions.\n" <<
	"#\n" << 
	"# Notes:\n"
	"#   \n" <<
	"# Author:       Generated by "
	;
#if defined( STLUTILS_HAS_USER )
      {
	User  user;
	(*out) << user.getRealName();
      }
#else
      (*out) << "unknown";
#endif
      (*out) << '\n' <<
	"# Generated:    "
	;
#if defined( STLUTILS_TEST )
      if( Stlutils_Prama_Gen_NoDate == 0 )
#endif
	(*out) << DateTime(time(0),true);
      
      (*out) << '\n' <<
	"#\n" << 
	"# Revision History: (See end of file for Revision Log)\n" << 
	"#\n" <<
	"#   Last Mod By:    $Author$\n" <<
	"#   Last Mod:       $Date$\n" <<
	"#   Version:        $Revision$\n" <<
	"#\n" <<
	"#   $Id$\n" <<
	"#\n" <<
	'\n'
	;

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

      (*out) << '\n' <<
	"#\n" <<
	"# $L" "og: $" << 
	"# " <<
	"#\n" <<
	"#\n"
	;
    }

  bool status( (*out).good() ? true : false );
  
  if( out != &cout )
    delete out;

  if( helpFlag )
    cerr << (*this) << "\n";
      
  if( status )
    cerr << "\n Generated args file ";
  else
    cerr << "ERROR: Generate args file failed ";
    
  if( argFile.size() )
    cerr << '\'' << argFile << "'.\n";
  else
    cerr << "to cout.\n";

  cerr << endl;

  if( exitApp )
    exit( status ? 0 : 1 );
}
	
//
// Revision Log:
//
// $Log$
// Revision 4.10  1999/11/09 14:06:33  houghton
// Bug-Fix: changed to prevent genArgsFile() log entry output from
//     getting Param.C's log entries.
//
// Revision 4.9  1999/11/09 14:00:37  houghton
// The Log line for generateArgFile output got the log entry for Param.
//
// Revision 4.8  1999/11/09 11:05:34  houghton
// Added generate arg file support.
// Reworked logStartInfo().
// Added logExitInfo()
// Changed to not try and open logs if -help.
// Bug-Fix: was using wrong args to call of allFileArgs.erase().
// Added argChar().
// Bug-Fix: signed num args -123 was not working.
// Added support for -arg=value.
//
// Revision 4.7  1999/11/04 17:33:06  houghton
// Changed help output format (much cleaner now i think:).
//
// Revision 4.6  1999/10/28 14:21:07  houghton
// Added errorlog support.
// Changed arg names.
//
// Revision 4.5  1998/07/20 11:24:16  houghton
// Port(Hpux): had to case const numbers used for array subscripts to
//     unsigned long.
//
// Revision 4.4  1998/02/13 01:21:04  houghton
// Cleanup.
//
// Revision 4.3  1997/09/21 13:17:37  houghton
// Bug-Fix: file arg values were overriding env var values.
//
// Revision 4.2  1997/09/20 10:46:43  houghton
// Bug-Fix: arg file was overriding env values.
//
// Revision 4.1  1997/09/17 15:12:43  houghton
// Changed to Version 4
//
// Revision 3.20  1997/09/17 14:10:18  houghton
// Renamed StlUtilsUtils.hh to StlUtilsMisc.hh
//
// Revision 3.19  1997/09/17 11:08:36  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.18  1997/09/16 11:24:49  houghton
// Added startTime method().
// Added logStartInfo method().
//
// Revision 3.17  1997/09/02 13:06:44  houghton
// Reworked so begin() does not include argv[0] (i.e. appName ).
//
// Revision 3.16  1997/08/08 13:23:58  houghton
// Added appendHelp().
// Added -version support.
// Rewored help output.
// Changed readArgs to support comment to end of line.
//
// Revision 3.15  1997/07/28 16:46:07  houghton
// Added default log file support.
//
// Revision 3.14  1997/07/25 12:17:09  houghton
// Changed help for flag type args to output 'flag' instead of false
//     when the flag is not set.
//
// Revision 3.13  1997/07/18 19:25:17  houghton
// Cleanup.
// Port(Sun5): changed local variable names to eliminate compiler warnings.
//
// Revision 3.12  1997/04/26 16:47:28  houghton
// Added env var for argfile.
//
// Revision 3.11  1997/04/04 20:54:26  houghton
// Changed constructor.
// Added logmode & logprot args.
// Added log error checking.
//
// Revision 3.10  1997/03/26 12:30:23  houghton
// Added constructor.
//
// Revision 3.9  1997/03/21 15:39:41  houghton
// Added argfile arg.
// Bug-Fix: readargs was not working correctly.
// Changed readargs is now a protected member.
//
// Revision 3.8  1997/03/21 12:26:01  houghton
// Changed file arg processing. Now file args will be overridden by
//     command line values
// Changed log level processing.
//
// Revision 3.7  1997/03/15 17:59:01  houghton
// Bug-Fix: would not find arg value 1 char wide.
//
// Revision 3.6  1997/03/03 19:02:57  houghton
// Bug-Fix: was returning 'good' changed to 'good()'.
//
// Revision 3.5  1997/03/03 14:37:17  houghton
// Removed support for RW Tools++.
//
// Revision 3.4  1997/03/02 13:19:49  houghton
// Cleanup.
//
// Revision 3.3  1996/11/19 22:07:08  houghton
// Bug-Fix: remove parse flag from constructor - calling a virtual
//     from the constructor does NOT call the sub class's method.
//     so parseArgs has to be call from the app or sub class.
// Bug-Fix: argStr( string ) - string::data did not give expected
//     results so change to string::c_str
// Bug-Fix: getArgValue - It may be ok that we reached the end
//     of the args. The proper check is if value has anything in it.
// Bug-Fix: appendHelp - cleanup helpString apperance.
// Bug-Fix: setError - core dumps where assigning to a string from
//     a 'const char * 0' changed to check first.
//
// Revision 3.2  1996/11/19 12:24:30  houghton
// Restructure header comments.
// Changed include lines to use " " instead of < > to accomidate rpm.
// Removed support for short file names to accomidate rpm.
// Major re-work of most function to use 'string'
// Major re-work to use vector<string> for managing argv.
// Added readArgs to read arg from a istream.
//
// Revision 3.1  1996/11/14 01:23:53  houghton
// Changed to Release 3
//
// Revision 2.7  1996/11/11 13:35:39  houghton
// Change to call rdbuf()-freeze beause AIX strstream does NOT have
//     a freeze method in its strstream.
//
// Revision 2.6  1996/11/08 11:46:04  houghton
// Removed Support for Str and DateTime.
//     (as required by Mike Alexander)
//
// Revision 2.5  1996/10/22 22:07:00  houghton
// Change: Added locStamp to turn on/off output of src file & line.
// Change: Added Support for Rogue Tools++ RWCString, RWDate & RWTime.
// Change: Rename arg methods for unsigned types.
//
// Revision 2.4  1996/04/27 13:07:54  houghton
// Added support for LibLog.
//
// Revision 2.3  1996/02/29 19:06:34  houghton
// *** empty log message ***
//
// Revision 2.2  1995/12/04 11:18:23  houghton
// Bug Fix - Can now compile with out '-DSTLUTILS_DEBUG'.
//
// Revision 2.1  1995/11/10  12:40:53  houghton
// Change to Version 2
//
// Revision 1.5  1995/11/05  15:28:43  houghton
// Revised
//
//

//
// File:        Param.C
// Project:	Clue
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

#if defined( CLUE_HAS_STR )
#include <Str.hh>
#endif

#if defined( CLUE_HAS_DATETIME )
#include <DateTime.hh>
#endif

#include <rw/rwdate.h>
#include <rw/rwtime.h>

CLUE_VERSION(
  Param,
  "$Id$" );

#if defined( CLUE_DEBUG )
#include <Param.ii>
#endif

const char * Param::ErrorStrings[] =
{
  "ok",
  "range",
  "conversion",
  "no value for arg",
  "UNDEFIEND",
  0
};

Param::Param(
  int 		mainArgc,
  char *	mainArgv[],
  const char *	version,
  const char *	logLevel,
  bool		parse
  )
  : appLog( cout, logLevel ),
    helpFlag( false ),
    logOutputLevel( logLevel ),
    logTee( false ),
    logMaxSize( 0 ),
    logTrimSize( 0 ),
    logTimeStamp( true ),
    logLevelStamp( true ),
    logLocStamp( true )
{
  if( version )
    ver = version;
    
  if( _LibLog  == 0 )
    _LibLog = &appLog;

  for( int a = 0; a < mainArgc; ++a )
    {
      string tmp = mainArgv[a];

      allArgv.push_back( tmp );
      argv.push_back( tmp );
    }
  
  helpString += "\n";
  helpString += appName();
  helpString += " help: \n\n";

  if( ver.size() )
    {
      helpString += "  Ver: ";
      helpString += ver;
      helpString += "\n\n";
    }

  if( parse )
    parseArgs();
}

Param::~Param( void )
{
  if( _LibLog == &appLog )
    _LibLog = 0;
}

bool
Param::parseArgs( void )
{
  argFlag( helpFlag,
	   "show usage help.",
	   "help" );

  argStr( logFile,
	  "log file name.",
	  "log",
	  "LOG_FILE" );

  argStr( logOutputLevel,
	  "log output level.",
	  "loglevel",
	  "LOG_LEVEL" );

  argStr( logFilter,
	  "regex for filtering log enties",
	  "logfilter",
	  "LOG_FILTER" );
  
  argFlag( logTee,
	   "Tee log output to cerr.",
	   "logtee",
	   "LOG_TEE" );

  argBool( logTimeStamp,
	   "output time stamp with log entry.",
	   "logtime",
	   "LOG_TIME" );

  argBool( logLevelStamp,
	   "output level with log entry.",
	   "logstamplevel",
	   "LOG_STAMP_LEVEL" );

  argBool( logLocStamp,
	   "output source location with log entry",
	   "logloc",
	   "LOG_LOC" );
  
  argULong( logMaxSize,
	  "log file max size.",
	  "logmax",
	  "LOG_MAX" );

  argULong( logTrimSize,
	   "log file trim size.",
	   "logtrim",
	   "LOG_TRIM" );
  
  if( logFilter.size() )
    appLog.filter( logFilter.c_str() );
	  
  if( logFile.size() )
    appLog.setFileName( logFile.c_str() );

  if( logTrimSize )
    appLog.setTrimSize( logTrimSize );
      
  if( logMaxSize )
    appLog.setMaxSize( logMaxSize );
  
  if( logTee )
    appLog.tee( cerr );

  appLog.setTimeStamp( logTimeStamp );
  appLog.setLevelStamp( logLevelStamp );
  appLog.setLocStamp( logLocStamp );
    
  appLog.setOutputLevel( logOutputLevel.c_str() );

  return( good );
}  

bool
Param::parseArgs( int argCount, char * argValue[] )
{
  allArgv.erase( allArgv.begin(), allArgv.end() );
  argv.erase( argv.begin(), argv.end() );
  
  for( int a = 0; a < argCount; ++a )
    {
      string	tmp = argValue[a];
      
      allArgv.push_back( tmp );
      argv.push_back( tmp );
    }

  return( parseArgs() );
}

  
  
bool
Param::readArgs( istream & src )
{
  argv.erase( argv.begin(), argv.end() );
  
  allArgv.erase( allArgv.begin(), allArgv.end() );

  string    line;

  while( getline( src, line ).good() )
    {
      // look for the first non white space char 
      string::size_type	pos = line.find_first_not_of( " \t" );

      // comment or blank line
      if( pos == string::npos || line[pos] == '#' )
	continue;

      string::size_type	delimPos = line.find_first_of( " \t", pos );

      if( delimPos != string::npos )
	{
	  allArgv.push_back( line.substr( pos, delimPos - 1 ) );
	  
	  string::size_type valuePos = line.find_first_not_of( " \t",
							    delimPos );
	  if( valuePos != string::npos )
	    allArgv.push_back( line.substr( valuePos ) );
	}
      else
	{
	  allArgv.push_back( line.substr( pos ) );
	}
    }

  argv = allArgv;
  parseArgs();
  
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
  string    arg	    = getArgValue( argId, envVar );

  if( arg.size() )
    {
      dest = new char[ arg.size() + 5 ];
      arg.copy( dest, arg.size() + 2 );
      dest[ arg.size() ] = 0;
    }

  appendHelp( argId, desc, envVar, dest );

  return( arg.size() != 0 );
}

bool
Param::argStr(
  string &	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  string    arg	    = getArgValue( argId, envVar );

  if( arg.size() )
    dest = arg;

  appendHelp( argId, desc, envVar, dest.data() );

  return( arg.size() != 0 );
}

bool
Param::argStr(
  RWCString &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  string    arg	    = getArgValue( argId, envVar );

  if( arg.size() )
    dest = arg.c_str();

  appendHelp( argId, desc, envVar, dest );

  return( arg.size() != 0 );
}

#if defined( CLUE_HAS_STR )
bool
Param::argStr(
  Str &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  string    arg	     = getArgValue( argId, envVar );

  if( arg.size() )
    dest = arg.c_str();

  appendHelp( argId, desc, envVar, dest );

  return( arg.size() != 0 );
}
#else // !def CLUE_HAS_STR

class Str
{
private:
  int dummy;
};

bool
Param::argStr(
  Str &  	CLUE_UNUSED( dest ),
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  _LLgLock;
  _LLg( LogLevel::Error )
    << Param::getClassName()
    << "::argStr( Str &, const char *, const char *, const char * ) - "
    << "called but CLUE_HAS_STR is undefined!"
    << endl;
  _LLgUnLock;
  
  appendHelp( argId, desc, envVar, "CLUE STR ERROR!!!" );
  return( false );
}
#endif // def CLUE_HAS_STR

template< class NumT >
inline
bool
_ClueParamArgNum(
  string &	arg,
  NumT &  	dest,
  NumT	    	minVal,
  NumT	    	maxVal,
  string &	errDesc
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

#define PARAM_ARG_NUM( Name, NumType )					      \
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
  string    arg	 = getArgValue( argId, envVar );			      \
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
	      string tmpErrDesc;					      \
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
	  string tmpErrDesc;						      \
									      \
	  tmpErrDesc = "'";						      \
	  tmpErrDesc += arg;						      \
	  tmpErrDesc += "'";						      \
									      \
	  setError( E_CONVERT, argId, envVar, tmpErrDesc.c_str() );	      \
	}								      \
    }									      \
									      \
  appendHelp( argId, desc, envVar, StringFrom( dest ) );		      \
									      \
  return( conv );							      \
}

PARAM_ARG_NUM( argInt, int )
PARAM_ARG_NUM( argUInt, unsigned int )
PARAM_ARG_NUM( argShort, short )
PARAM_ARG_NUM( argUShort, unsigned short )
PARAM_ARG_NUM( argLong, long )
PARAM_ARG_NUM( argULong, unsigned long )

  ;

bool
Param::argDouble(
  double &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  string    arg	 = getArgValue( argId, envVar );
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
	  string tmpErrDesc;

	  tmpErrDesc = "'";
	  tmpErrDesc += arg;
	  tmpErrDesc += "'";

	  setError( E_CONVERT, argId, envVar, tmpErrDesc.c_str() );
	}
      
    }

  appendHelp( argId, desc, envVar, StringFrom( dest ) );

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
  string    arg	 = getArgValue( argId, envVar );
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
	  string tmpErrDesc;

	  tmpErrDesc = "'";
	  tmpErrDesc += arg;
	  tmpErrDesc += "'";

	  setError( E_CONVERT, argId, envVar, tmpErrDesc.c_str() );
	}
    }

  appendHelp( argId, desc, envVar,
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
  
  appendHelp( argId, desc, envVar,
	      (dest ? "true" : "false" ) );

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
  RWTime    tmp;
  bool	    conv = argDateTime( tmp, desc, argId, envVar );

  if( conv )
    {
      struct tm tmTime;
      tmp.extract( &tmTime, RWZone::utc() );
      
      dest = mktime( &tmTime );
    }

  return( conv );
}

#if defined( CLUE_HAS_DATETIME )

bool
Param::argDateTime(
  DateTime &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  bool	    conv = false;
  
  string    arg	 = getArgValue( argId, envVar );

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
	  string tmpErrDesc;

	  tmpErrDesc = "'";
	  tmpErrDesc += arg;
	  tmpErrDesc += "'";

	  setError( E_CONVERT, argId, envVar, tmpErrDesc.c_str() );
	}
    }

  appendHelp( argId, desc, envVar, dest );

  return( conv );
}

#else // def CLUE_HAS_DATETIME

class DateTime
{
private:
  int dummy;
};

bool
Param::argDateTime(
  DateTime &  	CLUE_UNUSED( dest ),
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  _LLgLock;
  _LLg( LogLevel::Error )
    << Param::getClassName()
    << "::argDateTime( DateTime &, const char *, const char *, const char * ) - "
    << "called but CLUE_HAS_DATETIME is undefined!"
    << endl;
  _LLgUnLock;
  
  appendHelp( argId, desc, envVar, "CLUE DATETIME ERROR!!!" );
  
  return( false );
}
#endif // def CLUE_HAS_DATETIME


bool
Param::argDateTime(
  RWTime &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  bool	    conv = false;
  
  string    arg	 = getArgValue( argId, envVar );

  if( arg.size() )
    {
      bool	    convError = false;
      RWDate    dt;
      bool	dtIsSet = false;
  
      if( arg.find( '/' ) != string::npos )
	{
	  RWCString dtStr( arg.c_str() );
	  RWDate	dtTmp( dtStr );

	  if( dtTmp.isValid() )
	    dt = dtTmp;
	  else
	    convError = true;

	  dtIsSet = true;
	}

      RWTime    tm( 0, 0, 0 );
  
      if( ! convError )
	{
	  string::size_type	tPos = arg.find( ':' );

	  if( tPos != string::npos )
	    {
	      string::size_type begTimePos;
	  
	      if( isdigit( arg[ tPos - 2 ] ) )
		begTimePos = tPos - 2;
	      else
		begTimePos = tPos - 1;

	      RWCString tmStr( arg.c_str() + begTimePos );

	      RWTime tmTmp( dt, tmStr );

	      if( tmTmp.isValid() )
		tm = tmTmp;
	      else
		convError = true;
	    }
	  else
	    {
	      if( dtIsSet )
		tm = dt;
	      else
		convError = true;
	    }
	}

      if( ! convError )
	{
	  dest = tm;
	  conv = true;
	}
      else
	{
	  string tmpErrDesc;
	  
	  tmpErrDesc = "'";
	  tmpErrDesc += arg;
	  tmpErrDesc += "'";
	  
	  setError( E_CONVERT, argId, envVar, tmpErrDesc.c_str() );
	}
    }

  appendHelp( argId, desc, envVar, dest.asString() );

  return( conv );
}

bool
Param::argDate(
  RWDate &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  bool	    conv = false;
  
  string    arg	 = getArgValue( argId, envVar );

  if( arg.size() )
    {
      RWCString dtStr( arg.c_str() );
      RWDate	dtTmp( dtStr );

      if( dtTmp.isValid() )
	{
	  dest = dtTmp;
	  conv = true;
	}
      else
	{
	  string tmpErrDesc;
	  
	  tmpErrDesc = "'";
	  tmpErrDesc += arg;
	  tmpErrDesc += "'";
	  
	  setError( E_CONVERT, argId, envVar, tmpErrDesc.c_str() );
	}
    }
  
  appendHelp( argId, desc, envVar, dest.asString() );

  return( true );
}

#if defined( CLUE_HAS_DATETIME )

bool
Param::argDate(
  DateTime &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  bool	    conv = false;
  
  string    arg	 = getArgValue( argId, envVar );

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
	  string tmpErrDesc;

	  tmpErrDesc = "'";
	  tmpErrDesc += arg;
	  tmpErrDesc += "'";

	  setError( E_CONVERT, argId, envVar, tmpErrDesc.c_str() );
	}
    }

  appendHelp( argId, desc, envVar, dest );

  return( conv );
}

#else // def CLUE_HAS_DATETIME

bool
Param::argDate(
  DateTime &  	CLUE_UNUSED( dest ),
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  _LLgLock;
  _LLg( LogLevel::Error )
    << Param::getClassName()
    << "::argDate( DateTime &, const char *, const char *, const char * ) - "
    << "called but CLUE_HAS_DATETIME is undefined!"
    << endl;
  _LLgUnLock;
  
  appendHelp( argId, desc, envVar, "CLUE DATETIME ERROR!!!" );
  
  return( false );
}

#endif // def CLUE_HAS_DATETIME

bool
Param::argTime(
  RWTime &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  return( argDateTime( dest, desc, argId, envVar ) );
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


string
Param::getArgValue( const char * argId, const char * envVar )
{
  const char *	envValue = env( envVar );
  string	value;

  if( envValue )
    value = envValue;

  if( count() > 1 && argId && argId[0] )
    {
      Args::iterator	them = argv.begin();
      for( ; them != argv.end(); ++ them )
	{
	  if( (*them).size() > 1 &&
	      (*them)[0] == '-' && 
	      strcmp( (*them).c_str() + 1, argId ) == 0 )
	    {

	      // found it now get the value.
	      // and erase it from the vector.
	      for( them++; them != argv.end(); ++ them )
		{
		  if( (*them).size() > 1 &&
		      (*them)[0] != '-' )
		    {
		      value = *them;
		      argv.erase( them );
		      break;
		    }
		}

	      if( them == argv.end() )
		{
		  // no value for argId
		  setError( E_NO_VALUE, argId, envVar, 0 );
		}
	      
	      break;
	      
	    }
	}
      // if I found it and got it's value,
      // then re-find and erase the id.
      //
      // I have to do this becuase once I call argv.erase
      // aboue, the iterator is no longer valid and I must
      // get a new iterator from the vector to erase 
      // the id.
      //
      if( value.size() )
	{
	  for( them = argv.begin(); them != argv.end(); ++ them )
	    {
	      if( (*them).size() > 1 &&
		  (*them)[0] == '-' && 
		  strcmp( (*them).c_str() + 1, argId ) == 0 )
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
  bool value = ( env( envVar ) == 0 ) ? false : true;
  
  if( count() > 1 && argId && argId[0] )
    {
      Args::iterator	them = argv.begin();
      for( ; them != argv.end(); ++ them )
	{
	  if( (*them).size() > 1 &&
	      (*them)[0] == '-' && 
	      strcmp( (*them).c_str() + 1, argId ) == 0 )
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
Param::good( void ) const
{
  return( errors.size() == 0 );
}

const char *
Param::error( void ) const
{
  static string errStr;

  errStr = getClassName();
  
  if( good() )
    {
      errStr += ": ok";
    }
  else
    {
      string::size_type	errorSize = errStr.size();
      
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
  dest << helpString;

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

  string pre;
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
  
  dest << '\n';

  dest << prefix << "helpFlag:       " << helpFlag << '\n'
       << prefix << "logFile:        " << logFile << '\n'
       << prefix << "logOutputLevel: " << logOutputLevel << '\n'
       << prefix << "logTee:         " << logTee << '\n'
    ;
  
  dest << prefix << "helpString: \n" << helpString << '\n';

  dest << '\n';
    
  return( dest  );
}

size_t
Param::appendHelp( 
  const char * argId,
  const char * desc,
  const char * envVar,
  const char * value
  )
{
  string::size_type len = helpString.size();
  
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
      helpString += "''\n";
    }
  
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
  e.argId	= argId;
  e.envVar	= envVar;
  e.desc	= desc;

  errors.push_back( e );

  return( good() );
}

#if defined( OLD_WAY )
bool
Param::argUInt(
  unsigned int & dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar,
  unsigned int 	minVal,
  unsigned int 	maxVal
  )
{
  setHelp( argId, desc, envVar );
  
  char * argValue = getArgValue( argId, envVar );

  if( argValue ) dest = StringToUInt( argValue );

  strstream tmpHelp;
  
  if( dest < minVal || dest > maxVal )
    {
      tmpHelp << " '" << dest << "' not "
	      << minVal << " < n < " << maxVal << "\n";
      ok = false;
    }
  else
    {
      tmpHelp << " '" << dest << "'\n";
    }

  tmpHelp << ends;
  helpString += tmpHelp.str();
  tmpHelp.rdbuf()->freeze(0);
  
  return( argValue != 0 );
  
}

bool
Param::argShort(
  short &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar,
  short	    	minVal,
  short	    	maxVal
  )
{
  setHelp( argId, desc, envVar );
  
  char * argValue = getArgValue( argId, envVar );

  if( argValue ) dest = StringToInt( argValue );

  strstream tmpHelp;
  if( dest < minVal || dest > maxVal )
    {
      tmpHelp << " '" << dest << "' not "
	      << minVal << " < n < " << maxVal << "\n";
      ok = false;
    }
  else
    {
      tmpHelp << " '" << dest << "'\n";
    }

  tmpHelp << ends;
  helpString += tmpHelp.str();
  tmpHelp.rdbuf()->freeze(0);
  
  return( argValue != 0 );
  
}

bool
Param::argUShort(
  unsigned short & dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar,
  unsigned short minVal,
  unsigned short maxVal
  )
{
  setHelp( argId, desc, envVar );

  char * argValue = getArgValue( argId, envVar );

  if( argValue ) dest = StringToUInt( argValue );

  strstream tmpHelp;
  
  if( dest < minVal || dest > maxVal )
    {
      tmpHelp << " '" << dest << "' not "
	      << minVal << " < n < " << maxVal << "\n";
      ok = false;
    }
  else
    {
      tmpHelp << " '" << dest << "'\n";
    }

  tmpHelp << ends;
  helpString += tmpHelp.str();
  tmpHelp.rdbuf()->freeze(0);
  
  return( argValue != 0 );
  
}

bool
Param::argLong(
  long &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar,
  long	    	minVal,
  long	    	maxVal
  )
{
  setHelp( argId, desc, envVar );

  char * argValue = getArgValue( argId, envVar );

  if( argValue ) dest = StringToLong( argValue );

  strstream tmpHelp;
  if( dest < minVal || dest > maxVal )
    {
      tmpHelp << " '" << dest << "' not "
		 << minVal << " < n < " << maxVal << "\n";
      ok = false;
    }
  else
    {      
      tmpHelp << " '" << dest << "'\n";
    }

  tmpHelp << ends;
  helpString += tmpHelp.str();
  tmpHelp.rdbuf()->freeze(0);
  
  return( argValue != 0 );
  
}

bool
Param::argULong(
  unsigned long & dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar,
  unsigned long	minVal,
  unsigned long maxVal
  )
{
  setHelp( argId, desc, envVar );

  char * argValue = getArgValue( argId, envVar );

  if( argValue ) dest = StringToULong( argValue );

  strstream tmpHelp;
  if( dest < minVal || dest > maxVal )
    {
      tmpHelp << " '" << dest << "' not "
	      << minVal << " < n < " << maxVal << "\n";
      ok = false;
    }
  else
    {      
      tmpHelp << " '" << dest << "'\n";
    }

  tmpHelp << ends;
  helpString += tmpHelp.str();
  tmpHelp.rdbuf()->freeze(0);
  
  return( argValue != 0 );
  
}
#endif // def OLD_WAY

//
// Revision Log:
//
// $Log$
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
// Bug Fix - Can now compile with out '-DCLUE_DEBUG'.
//
// Revision 2.1  1995/11/10  12:40:53  houghton
// Change to Version 2
//
// Revision 1.5  1995/11/05  15:28:43  houghton
// Revised
//
//

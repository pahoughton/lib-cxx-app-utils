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
#include "Str.hh"
#include "DateTime.hh"

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
  const char *	logLevel
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

  if( logOutputLevel.size() )
    appLog.setOutputLevel( logOutputLevel.c_str() );

  for( int a = 0; a < mainArgc; ++a )
    {
      Str tmp = mainArgv[a];

      allArgv.push_back( tmp );
    }
  
  argv = allArgv;
  
  helpString += "\n";
  helpString += mainArgv[0];
  helpString += " help: \n\n";

  if( ver.size() )
    {
      helpString += "  Ver: ";
      helpString += ver;
      helpString += "\n\n";
    }
}

Param::~Param( void )
{
  if( _LibLog == &appLog )
    _LibLog = 0;
}

bool
Param::parseArgs( void )
{
  argv	    = allArgv;
  
  argStr( argFile,
	  "Name of file to read args from.",
	  "argfile" );

  if( argFile.size() )
    {
      readArgs( argFile.cstr() );
      fileArgs = allFileArgs;
    }
  
  argFlag( helpFlag,
	   "show usage help.",
	   "help" );

  argStr( logFile,
	  "log file name.",
	  "logfile",
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
	   "logshowtime",
	   "LOG_SHOW_TIME" );

  argBool( logLevelStamp,
	   "output level with log entry.",
	   "logshowlevel",
	   "LOG_SHOW_LEVEL" );

  argBool( logLocStamp,
	   "output source location with log entry",
	   "logshowloc",
	   "LOG_SHOWLOC" );
  
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

  if( logOutputLevel.size() )
    appLog.setOutputLevel( logOutputLevel.c_str() );

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

  allFileArgs.erase( fileArgs.begin(), fileArgs.end() );
  
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
	    allFileArgs.push_back( line.substr( valuePos ) );
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

  appendHelp( argId, desc, envVar, dest );

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
    dest = arg.c_str();

  appendHelp( argId, desc, envVar, dest );

  return( arg.size() != 0 );
}

template< class NumT >
inline
bool
_ClueParamArgNum(
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
  Str    arg	 = getArgValue( argId, envVar );			      \
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
  Str    arg	 = getArgValue( argId, envVar );
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

  appendHelp( argId, desc, envVar, dest );

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

  appendHelp( argId, desc, envVar, dest );

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
Param::getArgValue( const char * argId, const char * envVar )
{
  const char *	envValue = env( envVar );
  Str	value;

  if( envValue )
    value = envValue;

  if( count() <= 1 || ! argId || ! argId[0] )
    return( value );
  
  // first look in fileArgs
  {
    bool foundArg = false;
    
    for( Args::iterator them = fileArgs.begin();
	 them != fileArgs.end();
	 ++ them )
      {
	if( (*them).size() > 1 &&
	    (*them)[0] == '-' &&
	    (*them).substr( 1 ).compare( argId ) == 0 )
	  {
	    foundArg = true;
	    // found it
	    for( ++ them; them != fileArgs.end(); ++ them )
	      {
		if( (*them).size() && (*them)[0] != '-' )
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
		(*them)[0] == '-' &&
		(*them).substr( 1 ).compare( argId ) == 0 )
	      {
		fileArgs.erase( them );
		break;
	      }
	  }
      }
  }

  // now look for it in command line args
  {
    bool foundArg = false ;
	   
    Args::iterator	them = argv.begin();
    for( ; them != argv.end(); ++ them )
      {
	if( (*them).size() > 1 &&
	    (*them)[0] == '-' &&
	    (*them).substr( 1 ).compare( argId ) == 0 )
	  {
	    
	    // found it now get the value.
	    // and erase it from the vector.
	    for( them++; them != argv.end(); ++ them )
	      {
		if( (*them).size() &&
		    (*them)[0] != '-' )
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
		(*them)[0] == '-' && 
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

  if( env( envVar ) )
    {
      Str envStr( env( envVar ) );
      value = envStr.toBool();
    }

  if( count() <= 1 || !argId || ! argId[0] )
    return( value );
  
  {
    for( Args::iterator them = fileArgs.begin();
	 them != fileArgs.end();
	 ++ them )
      {
	if( (*them).size() > 1 &&
	    (*them)[0] == '-' &&
	    (*them).substr( 1 ).compare( argId ) == 0 )
	  {
	    // found it
	    value = true;
	    fileArgs.erase( them );
	    break;
	  }
      }
  }

  
  {
    Args::iterator	them = argv.begin();
    for( ; them != argv.end(); ++ them )
      {
	if( (*them).size() > 1 &&
	    (*them)[0] == '-' && 
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
Param::good( void ) const
{
  return( errors.size() == 0 );
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
      for( ++ them ; them != argv.end(); ++ them )
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

  dest << prefix << "helpFlag:       " << helpFlag << '\n'
       << prefix << "logFile:        " << logFile << '\n'
       << prefix << "logOutputLevel: " << logOutputLevel << '\n'
       << prefix << "logTee:         " << logTee << '\n'
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
      for( ++ them ; them != argv.end(); ++ them )
	dest << "  " << (*them) << endl;
    }

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
  Str argHelp;

  argHelp.setf( ios::left, ios::adjustfield );

  size_t    contLinePadSize = max( (size_t)10, strlen( argId ))  + 3 + 1;

  argHelp << desc ;

  if( envVar )
    argHelp << " (" << envVar << ')' ;

  if( value && strlen( value ) )
    argHelp << " '" << value << "'\n" ;

  argHelp.wrap( 79, contLinePadSize );

  argHelp[2] = '-';
  
  argHelp.replace( 3, strlen( argId ), argId );
  
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


//
// Revision Log:
//
// $Log$
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
// Bug Fix - Can now compile with out '-DCLUE_DEBUG'.
//
// Revision 2.1  1995/11/10  12:40:53  houghton
// Change to Version 2
//
// Revision 1.5  1995/11/05  15:28:43  houghton
// Revised
//
//

//
// File:        Param.C
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     01/26/95 14:43 
//
// Revision History:
//
// $Log$
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


#if !defined( CLUE_SHORT_FN )
#include "Param.hh"
#include "StringUtils.hh"
#else
#include "Param.hh"
#include "StrUtil.hh"
#endif

CLUE_VERSION(
  Param,
  "$Id$" );

#if defined( CLUE_DEBUG )
#include <Param.ii>
#endif

// static char DefaultLogLevel[] = DEFAULT_LOGLEVEL;


Param::Param(
  int &		mainArgc,
  char **	mainArgv,
  const char *	ver,
  const char *	logLevel
  )
  : argc( mainArgc ),
    argv( mainArgv ),
    appLog( cout, logLevel ),
    helpFlag( false ),
    logOutputLevel( logLevel ),
    logTee( false ),
    logMaxSize( 0 ),
    logTrimSize( 0 ),
    logTimeStamp( true ),
    logLevelStamp( true ),
    logLocStamp( true ),
    ok( true )
{
  if( _LibLog  == 0 )
    _LibLog = &appLog;
  
  argv = mainArgv;
  
  helpString.setf( ios::left );
  
  helpString << '\n' << appName() << " help: " << "\n\n";

  if( ver )
    helpString << "  Ver: " << ver << "\n\n";

  ok = true;
  
  //
  // set The standard values;
  //

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

  argFlag( logTee,
	   "Tee log output to cerr.",
	   "logtee",
	   "LOG_TEE" );

  argULong( logMaxSize,
	  "log file max size.",
	  "logmax",
	  "LOG_MAX" );

  argULong( logTrimSize,
	   "log file trim size.",
	   "logtrim",
	   "LOG_TRIM" );
  
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
  
	  
  if( ! logFile.empty() )
    {
      appLog.setFileName( logFile );

      if( logTrimSize )
	appLog.setTrimSize( logTrimSize );
      
      if( logMaxSize )
	appLog.setMaxSize( logMaxSize );
    }

  if( logTee )
    appLog.tee( cerr );

  appLog.setTimeStamp( logTimeStamp );
  appLog.setLevelStamp( logLevelStamp );
  appLog.setLocStamp( logLocStamp );
    
  appLog.setOutputLevel( logOutputLevel );

}


bool
Param::argStr(
  char * &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  size_t hStart = setHelp( argId, desc, envVar );
  
  char * argValue = getArgValue( argId, envVar );

  if( argValue ) dest = argValue;

  if( dest )
    {
      if( (( helpString.length() - hStart ) + strlen( dest )) < 80 )
	{
	  helpString << " '" << dest << "'\n";
	}
      else
	{
	  helpString << '\n'
		     << "            '" << dest << "'\n";
	}
    }
  else
    {
      helpString << "''\n";
    }

  return( argValue != 0 );
  
}

bool
Param::argStr(
  Str &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  size_t hStart = setHelp( argId, desc, envVar );
  
  char * argValue = getArgValue( argId, envVar );

  if( argValue ) dest = argValue;

  if( dest.length() )
    {
      if( (( helpString.length() - hStart ) +  dest.length()) < 80 )
	{
	  helpString << " '" << dest << "'\n";
	}
      else
	{
	  helpString << '\n'
		     << "            '" << dest << "'\n";
	}
    }
  else
    {
      helpString << "''\n";
    }

  return( argValue != 0 );
  
}

bool
Param::argStr(
  RWCString &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  size_t hStart = setHelp( argId, desc, envVar );
  
  char * argValue = getArgValue( argId, envVar );

  if( argValue ) dest = argValue;

  if( dest.length() )
    {
      if( (( helpString.length() - hStart ) +  dest.length()) < 80 )
	{
	  helpString << " '" << dest << "'\n";
	}
      else
	{
	  helpString << '\n'
		     << "            '" << dest << "'\n";
	}
    }
  else
    {
      helpString << "''\n";
    }

  return( argValue != 0 );
  
}

bool
Param::argInt(
  int &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar,
  int	    	minVal,
  int	    	maxVal
  )
{
  setHelp( argId, desc, envVar );
  
  char * argValue = getArgValue( argId, envVar );

  if( argValue ) dest = StringToInt( argValue );

  if( dest < minVal || dest > maxVal )
    {
      helpString << " '" << dest << "' not "
		 << minVal << " < n < " << maxVal << "\n";
      ok = false;
    }
  else
    {
      helpString << " '" << dest << "'\n";
    }

  return( argValue != 0 );
  
}

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

  if( dest < minVal || dest > maxVal )
    {
      helpString << " '" << dest << "' not "
		 << minVal << " < n < " << maxVal << "\n";
      ok = false;
    }
  else
    {
      helpString << " '" << dest << "'\n";
    }

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

  if( dest < minVal || dest > maxVal )
    {
      helpString << " '" << dest << "' not "
		 << minVal << " < n < " << maxVal << "\n";
      ok = false;
    }
  else
    {
      helpString << " '" << dest << "'\n";
    }

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

  if( dest < minVal || dest > maxVal )
    {
      helpString << " '" << dest << "' not "
		 << minVal << " < n < " << maxVal << "\n";
      ok = false;
    }
  else
    {
      helpString << " '" << dest << "'\n";
    }

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

  if( dest < minVal || dest > maxVal )
    {
      helpString << " '" << dest << "' not "
		 << minVal << " < n < " << maxVal << "\n";
      ok = false;
    }
  else
    {      
      helpString << " '" << dest << "'\n";
    }

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

  if( dest < minVal || dest > maxVal )
    {
      helpString << " '" << dest << "' not "
		 << minVal << " < n < " << maxVal << "\n";
      ok = false;
    }
  else
    {      
      helpString << " '" << dest << "'\n";
    }

  return( argValue != 0 );
  
}

bool
Param::argDouble(
  double &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  setHelp( argId, desc, envVar );

  char * argValue = getArgValue( argId, envVar );

  if( argValue ) dest = StringToDouble( argValue );

  helpString << " '" << dest << "'\n";

  return( argValue != 0 );
  
}

bool
Param::argBool(
  bool &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  setHelp( argId, desc, envVar );

  char * argValue = getArgValue( argId, envVar );

  if( argValue ) dest = StringToBool( argValue );

  helpString << " '" << ( (dest == true) ? "true" : "false" ) << "'\n";

  return( argValue != 0 );
}

bool
Param::argFlag(
  bool &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  setHelp( argId, desc, envVar );

  bool argValue = getArg( argId, envVar );

  if( argValue ) dest = argValue;

  helpString << " '" << ( (dest == true) ? "true" : "false" ) << "'\n";

  return( argValue != false );
}

bool
Param::argDateTime(
  time_t &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  setHelp( argId, desc, envVar );

  char * argValue = getArgValue( argId, envVar );

  if( argValue )
    {
      DateTime dt( argValue );
      dest = dt.getTimeT();
      helpString << " '" << dt << "'\n";
    }
  else
    {
      DateTime dt( dest );
      helpString << " '" << dt << "'\n";
    }

  return( argValue != 0 );
}

bool
Param::argDateTime(
  DateTime &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  setHelp( argId, desc, envVar );

  char * argValue = getArgValue( argId, envVar );

  if( argValue ) dest.set( argValue );
  
  helpString << " '" << dest << "'\n";

  return( argValue != 0 );
}

bool
Param::argDateTime(
  RWTime &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  setHelp( argId, desc, envVar );

  char * argValue = getArgValue( argId, envVar );

  if( argValue )
    {
      DateTime tmp;
      tmp.set( argValue );
      dest = RWTime( RWDate( tmp.getDayOfMonth(),
			     tmp.getMonth(),
			     tmp.getYear() ),
		     tmp.getHour(),
		     tmp.getMinute(),
		     tmp.getSecond() );
      
    }
  
  helpString << " '" << dest << "'\n";

  return( argValue != 0 );
}

bool
Param::argDate(
  DateTime &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  setHelp( argId, desc, envVar );

  char * argValue = getArgValue( argId, envVar );

  if( argValue )
    {
      dest.set( (time_t)0 );
      dest.set( argValue );
    }
  
  helpString << " '" << dest << "'\n";

  return( argValue != 0 );
}

bool
Param::argDate(
  RWDate &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  setHelp( argId, desc, envVar );

  char * argValue = getArgValue( argId, envVar );

  if( argValue )
    {
      DateTime tmp;
      tmp.set( argValue );
      dest = RWDate( tmp.getDayOfMonth(), tmp.getMonth(), tmp.getYear() );
    }
  
  helpString << " '" << dest << "'\n";

  return( argValue != 0 );
}

bool
Param::argTime(
  DateTime &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  setHelp( argId, desc, envVar );

  char * argValue = getArgValue( argId, envVar );

  if( argValue )
    {
      dest.set( (time_t)0 );
      dest.set( argValue );
    }
  
  helpString << " '" << dest << "'\n";

  return( argValue != 0 );
}

bool
Param::argTime(
  RWTime &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  setHelp( argId, desc, envVar );

  char * argValue = getArgValue( argId, envVar );

  if( argValue )
    {
      DateTime tmp( (time_t) 0 );
      tmp.set( argValue );
      dest = RWTime( tmp.getHour(), tmp.getMinute(), tmp.getSecond() );
    }
  
  helpString << " '" << dest << "'\n";

  return( argValue != 0 );
}

char *
Param::getArgValue( const char * argId, const char * envVar )
{
  char * value = (char *)env( envVar );
  
  if( count() > 1 && argId && argId[0] )
    {
      for( size_t a = 1; a < (count() - 1); a++ )
	{
	  if( argv[a][0] == '-' && strcmp( argId, &(argv[a][1]) ) == 0 )
	    {
	      value = argv[a+1];
	      for( ; a + 2 < count(); a++ )
		{
		  argv[a] = argv[a+2];
		}
	      argc -= 2;
	      return( value );
	    }
	}
    }
  return( value );
}

bool
Param::getArg( const char * argId, const char * envVar )
{
  bool value = ( env( envVar ) == 0 ) ? false : true;
  
  if( count() > 1 && argId && argId[0] )
    {
      for( size_t a = 1; a < count(); a++ )
	{
	  if( argv[a][0] == '-' &&  strcmp( argId, &(argv[a][1]) ) == 0 )
	    {
	      value = true;
	      for( ; a + 1 < count(); a++ )
		{
		  argv[a] = argv[a+1];
		}
	      argc -= 1;
	      return( value );
	    }
	}
    }
  return( value );
  ;
}

bool
Param::good( void ) const
{
  return( ! helpFlag && allArgs() && ok );
}

const char *
Param::error( void ) const
{
  static Str errStr;
  errStr.reset();
  errStr << getClassName();
  
  if( good() )
    {
      errStr << ": Ok";
    }
  else
    {
      if( ! allArgs() )
	{
	  errStr << ": bad args: ";
	  for( int a = 1; a < argc; a++ )
	    {
	      errStr << '\'' << argv[a] << "' ";
	    }
	}
      else
	{
	  errStr << ": unknown error";
	}
    }
  return( errStr.cstr() );  
}

const char *
Param::getClassName( void ) const
{
  return "Param";
}

const char *
Param::getVersion( bool withPrjVer ) const
{
  static Str ver;

  if( ! ver.size() )
    {
      ver << version.getVer( withPrjVer ) << '\n'
	  << "    " << appLog.getVersion( false ) << '\n'
	  << "    " << helpString.getVersion( false ) << '\n'
	;
    }
  return( ver );
}


ostream &
Param::toStream( ostream & dest ) const
{
  dest << helpString;
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
  pre << "appLog:" << appLog.getClassName() << "::";

  appLog.dumpInfo( dest, pre, false );
  
  dest << prefix;
  toStream( dest );
  dest << '\n';

  
  dest << prefix << "argc:      " << argc << '\n';
  
  for( int i = 0; i < argc; i++ )
    {
      dest << prefix << "argv[" << i << "]:";
      if( i > 9 )
	dest << "  '";
      else
	dest << "   '";
      dest << argv[i] << "'\n";
    }
  
  dest << '\n';

  dest << prefix << "helpFlag:       " << helpFlag << '\n'
       << prefix << "logFile:        " << logFile << '\n'
       << prefix << "logOutputLevel: " << logOutputLevel << '\n'
       << prefix << "logTee:         " << logTee << '\n'
    ;
  
  dest << '\n';
    
  return( dest  );
}

size_t
Param::setHelp(
  const char * argId,
  const char * desc,
  const char * envVar
  )
{
  size_t hStart =  helpString.length();
  
  helpString << "  -" << setw(8) << argId << ' ' << desc ;
  if( envVar ) helpString << " (" << envVar << ')';

  return( hStart );
}


#if !defined( AIX41 )
#endif

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
// Revision 1.4  1995/11/05 14:44:40  houghton
// Ports and Version ID changes
//
//

#include "Param.hh"

#ifdef CLUE_SHORT_FN
#include "StrUtil.hh"
#else
#include "StringUtils.hh"
#endif


const char Param::version[] =
LIB_CLUE_VERSION
"$Id$";

#ifdef   CLUE_DEBUG
#define  inline
#include <Param.ii>
#endif

Param::Param( int & mainArgc, char ** mainArgv, const char * ver )
  : argc( mainArgc ),
    argv( mainArgv ),
    appLog( cout, DEFAULT_LOGLEVEL )

{
  argv = mainArgv;
  
  helpString.setf( ios::left );
  
  helpString << '\n' << appName() << " help: " << "\n\n";

  if( ver )
    helpString << "  Ver: " << ver << "\n\n";

  ok = true;
  
  //
  // get The standard values;
  //

  helpFlag  	    = false;
  logFile   	    = 0;
  logOutputLevel    = DEFAULT_LOGLEVEL;
  logTee    	    = false;
  logMaxSize	    = 0;
  logTrimSize	    = 0;
  
  argFlag( helpFlag,
	   "show usage help.",
	   "help" );

  argString( logFile,
	     "log file name.",
	     "log",
	     "LOG_FILE" );

  argString( logOutputLevel,
	     "log output level.",
	     "loglevel",
	     "LOG_LEVEL" );

  argFlag( logTee,
	   "Tee log output to cerr.",
	   "logtee",
	   "LOG_TEE" );

  argLong( logMaxSize,
	  "log file max size.",
	  "logmax",
	  "LOG_MAX" );

  argLong( logTrimSize,
	   "log file trim size.",
	   "logtrim",
	   "LOG_TRIM" );
  
	  
  if( logFile )
    {
      appLog.setFileName( logFile );

      if( logTrimSize )
	appLog.setTrimSize( logTrimSize );
      
      if( logMaxSize )
	appLog.setMaxSize( logMaxSize );
    }

  if( logTee )
    {
      appLog.tee( cerr );
    }
  appLog.setOutputLevel( logOutputLevel );
      
}
  


bool
Param::argString(
  char * &  	dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar
  )
{
  size_t hStart = helpString.length();
  
  helpString << "  -" << setw(8) << argId << ' ' << desc ;
  if( envVar ) helpString << " (" << envVar << ')';

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
  size_t hStart = helpString.length();
  
  helpString << "  -" << setw(8) << argId << ' ' << desc ;
  if( envVar ) helpString << " (" << envVar << ')';

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
  helpString << "  -" << setw(8) << argId << ' ' << desc ;
  if( envVar ) helpString << " (" << envVar << ')';

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
Param::argInt(
  unsigned int & dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar,
  unsigned int 	minVal,
  unsigned int 	maxVal
  )
{
  helpString << "  -" << setw(8) << argId << ' ' << desc ;
  if( envVar ) helpString << " (" << envVar << ')';

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
  helpString << "  -" << setw(8) << argId << ' ' << desc ;
  if( envVar ) helpString << " (" << envVar << ')';

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
Param::argShort(
  unsigned short & dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar,
  unsigned short minVal,
  unsigned short maxVal
  )
{
  helpString << "  -" << setw(8) << argId << ' ' << desc ;
  if( envVar ) helpString << " (" << envVar << ')';

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
  helpString << "  -" << setw(8) << argId << ' ' << desc ;
  if( envVar ) helpString << " (" << envVar << ')';

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
Param::argLong(
  unsigned long & dest,
  const char * 	desc,
  const char *  argId,
  const char * 	envVar,
  unsigned long	minVal,
  unsigned long maxVal
  )
{
  helpString << "  -" << setw(8) << argId << ' ' << desc ;
  if( envVar ) helpString << " (" << envVar << ')';

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
  helpString << "  -" << setw(8) << argId << ' ' << desc ;
  if( envVar ) helpString << " (" << envVar << ')';

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
  helpString << "  -" << setw(8) << argId << ' ' << desc ;
  if( envVar ) helpString << " (" << envVar << ')';

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
  helpString << "  -" << setw(8) << argId << ' ' << desc ;
  if( envVar ) helpString << " (" << envVar << ')';

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
  helpString << "  -" << setw(8) << argId << ' ' << desc ;
  if( envVar ) helpString << " (" << envVar << ')';

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
  helpString << "  -" << setw(8) << argId << ' ' << desc ;
  if( envVar ) helpString << " (" << envVar << ')';

  char * argValue = getArgValue( argId, envVar );

  if( argValue ) dest.set( argValue );
  
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

const char *
Param::getClassName( void ) const
{
  return "Param";
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


ostream &
Param::toStream( ostream & dest ) const
{
  dest << helpString;
  return( dest );
}

ostream &
Param::dumpInfo( ostream & dest ) const
{
  dest << getClassName() << ":\n";

  dest << "    " << version << '\n';

  if( ! good() )
    dest << "    Error: " << error() << '\n';
  else
    dest << "    " << "Good!" << '\n';

  dest << "    " ;
  toStream( dest );
  dest << '\n';

  
  dest << "    " << "argc: " << argc << '\n';
  dest << "    " << "args:\n";
  
  for( int i = 0; i < argc; i++ )
    {
      dest << "      '" << argv[i] << "'\n";
    }
  
  dest << '\n';

  dest << "    helpFlag:       " << helpFlag << '\n'
       << "    logFile:        " << logFile << '\n'
       << "    logOutputLevel: " << logOutputLevel << '\n'
       << "    logTee:         " << logTee << '\n'
    ;
  
  dest << "    appLog:\n";

  appLog.dumpInfo( dest );

  dest << getClassName() << " - END\n";
  
  return( dest  );
}

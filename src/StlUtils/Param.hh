#ifndef _Param_hh_
#define _Param_hh_
//
// File:        Param.hh
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     01/26/95 13:28
//
// Revision History:
//
// 
// $Log$
// Revision 1.2  1995/07/21 15:43:20  ichudov
// DAVLs
//
// Revision 1.1  1995/02/13  16:08:53  houghton
// New Style Avl an memory management. Many New Classes
//
//


#include <Log.hh>
#include <Str.hh>
#include <DoubleLink.hh>
#include <DateTime.hh>
#include <TeleNum.h>

#include <Common.h>
#include <stdlib.h>
#include <limits.h>

#define DEFAULT_LOGLEVEL "ERROR | WARNING"

#define ALog	(App->log())

class Param
{

public:

  Param( int * mainArgc, char * mainArgv[], const char * version = 0 );

  Log &     log( void );
  Log &     log( LogLevel::Level lvl );

  char *    name( void );
  char *    next( void );
  char *    arg( int which = 1 );
  int	    count( void );
  void 	    reset( void );

  const char *	env( const char * envVar );
  
  inline Ret_Status argString( char **  	dest,
			       const char *   description,
			       const char *   argId,
			       const char *   envVar = 0 );
  
  inline Ret_Status argInt( int *  	dest,
			    const char *   description,
			    const char *   argId,
			    const char *   envVar = 0,
			    int	    	min = INT_MIN,
			    int	    	max = INT_MAX );
		     
  inline Ret_Status argLong( long *  	dest,
			     const char *   description,
			     const char *   argId,
			     const char *   envVar = 0,
			     long	    	min = LONG_MIN,
			     long	    	max = LONG_MAX );
		     
  inline Ret_Status argDouble( double *  	dest,
			       const char *   description,
			       const char *   argId,
			       const char *   envVar = 0 );
  
  inline Ret_Status argBool( Bool *  	dest,
			     const char *   description,
			     const char *   argId,
			     const char *   envVar = 0 );
		     
  inline Ret_Status argFlag( Bool *  	dest,
			     const char *   description,
			     const char *   argId,
			     const char *   envVar = 0 );

  inline Ret_Status argDateTime( time_t *   dest,
			     const char *   description,
			     const char *   argId,
			     const char *   envVar = 0,
			     time_t	    	min = LONG_MIN,
			     time_t	    	max = LONG_MAX );

  inline Ret_Status argTeleNum( TeleNumData *  dest,
				const char *   description,
				const char *   argId,
				const char *   envVar = 0 );
			     
  Bool	    	help( void ) const;

  Bool	    	allArgs( void ) const;

  void	    	abort( int exitStatus = 1, ostream & dest = cerr );
  
  virtual const char *	getClassName( void ) const { return "Param"; };
  
  virtual Bool	    	good( void ) const;
  virtual const char *	error( void ) const;
  
  enum ArgType
  {
    ARG_STRING,
    ARG_INT,
    ARG_LONG,
    ARG_FLAG,
    ARG_BOOL,
    ARG_DOUBLE,
    ARG_DATETIME,
    ARG_TELENUM
  };

  friend ostream & operator<<( ostream & dest, const Param & param );
    
protected:

private:

  Param( const Param & copyFrom );
  Param & operator=( const Param & assignFrom );

  struct Help
  {
    const char *    desc;
    const char *    argId;
    const char *    envVar;
    ArgType 	    type;
    void *  	    value;
  };

  DoubleLink<Help>  helpList;
  int *	    	    argc;
  char **    	    argv;
  const char *	    ver;
  
  Log	    	    appLog;

  Bool    	    helpFlag;

  char *    	    logFile;
  char *    	    logOutputLevel;

  Bool	    	    logTee;
  
  Bool	    	    ok;

  int	    	    curArg;
  
};


//
// Inline methods
//

inline
Param::Param( int * mainArgc, char * mainArgv[], const char * version )
  : appLog( cout, DEFAULT_LOGLEVEL )
{
  curArg = 0;
  
  argc = mainArgc;
  argv = mainArgv;
  ver = version;

  ok = TRUE;
  
  //
  // get The standard values;
  //

  helpFlag  	= FALSE;
  logFile   	= 0;
  logOutputLevel = DEFAULT_LOGLEVEL;
  logTee    	= FALSE;
  
  argFlag( &helpFlag,
	   "show usage help",
	   "help" );

  argString( &logFile,
	     "log file name",
	     "log",
	     "LOG_FILE" );

  argString( &logOutputLevel,
	     "log output level",
	     "loglevel",
	     "LOG_LEVEL" );

  argFlag( &logTee,
	   "Tee log output to cerr",
	   "logtee",
	   "LOG_TEE" );
  
  if( logFile )
    {
      appLog.setFileName( logFile );
    }

  if( logTee )
    {
      appLog.tee( cerr );
    }
  appLog.setOutputLevel( logOutputLevel );
      
}


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
Ret_Status
Param::argString(
  char **  	 dest,
  const char *   description,
  const char *   argId,
  const char *   envVar
  )
{
  Help * h = new Help;

  h->desc 	= description;
  h->argId 	= argId;
  h->envVar	= envVar;
  h->type	= ARG_STRING;
  h->value	= dest;

  helpList.append( h );

  Ret_Status ret = ArgEnvString( argc, argv, argId, envVar, dest );

  if( ret != RET_SUCCEED )
    {
      ok = FALSE;
    }

  return( ret );
			     
}

inline
Ret_Status
Param::argInt(
  int *  	 dest,
  const char *   description,
  const char *   argId,
  const char *   envVar,
  int	    	 min,
  int	    	 max
  )
{
  Help * h = new Help;

  h->desc 	= description;
  h->argId 	= argId;
  h->envVar	= envVar;
  h->type	= ARG_INT;
  h->value	= dest;

  helpList.append( h );
  
  Ret_Status ret = ArgEnvInt( argc, argv, argId, envVar, min, max, dest );

  if( ret != RET_SUCCEED )
    {
      ok = FALSE;
    }

  return( ret );
}

inline
Ret_Status
Param::argLong(
  long *  	 dest,
  const char *   description,
  const char *   argId,
  const char *   envVar,
  long	    	 min,
  long	    	 max
  )
{
  Help * h = new Help;

  h->desc 	= description;
  h->argId 	= argId;
  h->envVar	= envVar;
  h->type	= ARG_LONG;
  h->value	= dest;

  helpList.append( h );
  
  Ret_Status ret = ArgEnvLong( argc, argv, argId, envVar, min, max, dest );

  if( ret != RET_SUCCEED )
    {
      ok = FALSE;
    }

  return( ret );
}

inline
Ret_Status
Param::argDouble(
  double *  	 dest,
  const char *   description,
  const char *   argId,
  const char *   envVar
  )
{
  Help * h = new Help;

  h->desc 	= description;
  h->argId 	= argId;
  h->envVar	= envVar;
  h->type	= ARG_DOUBLE;
  h->value	= dest;

  helpList.append( h );
  
  Ret_Status ret = ArgEnvDouble( argc, argv, argId, envVar,  dest );

  if( ret != RET_SUCCEED )
    {
      ok = FALSE;
    }

  return( ret );
}


inline
Ret_Status
Param::argBool(
  Bool *  	 dest,
  const char *   description,
  const char *   argId,
  const char *   envVar
  )
{
  Help * h = new Help;

  h->desc 	= description;
  h->argId 	= argId;
  h->envVar	= envVar;
  h->type	= ARG_BOOL;
  h->value	= dest;

  helpList.append( h );
  
  Ret_Status ret = ArgEnvBool( argc, argv, argId, envVar, dest );

  if( ret != RET_SUCCEED )
    {
      ok = FALSE;
    }

  return( ret );
}

inline
Ret_Status
Param::argFlag(
  Bool *  	 dest,
  const char *   description,
  const char *   argId,
  const char *   envVar
  )
{
  Help * h = new Help;

  h->desc 	= description;
  h->argId 	= argId;
  h->envVar	= envVar;
  h->type	= ARG_FLAG;
  h->value	= dest;

  helpList.append( h );
  
  Ret_Status ret = ArgEnvFlag( argc, argv, argId, envVar, dest );

  if( ret != RET_SUCCEED )
    {
      ok = FALSE;
    }

  return( ret );
}

inline
Ret_Status
Param::argDateTime(
  time_t *  	 dest,
  const char *   description,
  const char *   argId,
  const char *   envVar,
  time_t    	 min,
  time_t    	 max
  )
{
  Help * h = new Help;

  h->desc 	= description;
  h->argId 	= argId;
  h->envVar	= envVar;
  h->type	= ARG_DATETIME;
  h->value	= dest;

  helpList.append( h );

  // FIXME - we should implement this in C

  char *    dateString = 0;
  Ret_Status ret = ArgEnvString( argc, argv, argId, envVar, &dateString );

  if( ret != RET_SUCCEED )
    {
      ok = FALSE;
    }

  if( dateString != 0 )
    {
      DateTime	dt( dateString );
      *dest = dt.getTimeT();
      if( *dest < min || *dest > max )
	{
	  ok = FALSE;
	  ret = RET_ERROR;
	}
    }  
  return( ret );
}

inline
Ret_Status
Param::argTeleNum(
  TeleNumData *  dest,
  const char *   description,
  const char *   argId,
  const char *   envVar
  )
{
  Help * h = new Help;

  h->desc 	= description;
  h->argId 	= argId;
  h->envVar	= envVar;
  h->type	= ARG_TELENUM;
  h->value	= dest;

  helpList.append( h );

  // FIXME - we should implement this in C

  char * teleString = 0;
  
  Ret_Status ret = ArgEnvString( argc, argv, argId, envVar, &teleString );

  if( ret != RET_SUCCEED )
    {
      ok = FALSE;
    }

  if( teleString )
    {
      TeleNumDataFromString( teleString, 0, dest );
    }
  return( ret );
}


inline
Bool
Param::help( void ) const
{
  return( helpFlag );
}

inline
Bool
Param::allArgs( void ) const
{
  if( *argc > 1 )
    {
      for( int a = 1; a < *argc; a++ )
	{
	  if( argv[a][0] == '-' )
	    {
	      return( FALSE );
	    }
	  else
	    {
	      return( TRUE );
	    }
	}
    }
  else
    {
      return( TRUE );
    }
}

inline
Bool
Param::good( void ) const
{
  return( allArgs() );
}

inline
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
	  for( int a = 1; a < *argc; a++ )
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

inline
char *
Param::name( void )
{
  return( argv[0] );
}

inline
char *
Param::next( void )
{
  curArg++;
  
  if( curArg == *argc )
    {
      curArg = 0;
      return(0);
    }

  return( argv[curArg] );
}

inline
char *
Param::arg( int which )
{
  return( ( which >= 0 && which < *argc ) ? argv[which] : 0 );
}

inline
int
Param::count( void )
{
  return( *argc - 1 );
}

inline
void
Param::reset( void )
{
  curArg = 0;
}

inline
const char *
Param::env( const char * envVar )
{
  return( getenv( envVar ) );
}

inline
void
Param::abort( int exitStatus, ostream & dest )
{
  dest << "Aborted - see log for more info" << endl;
  exit( exitStatus );
}

#endif // ! def _Param_hh_ 
//
//              This software is the sole property of
// 
//                 The Williams Companies, Inc.
//                        1 Williams Center
//                          P.O. Box 2400
//        Copyright (c) 1994 by The Williams Companies, Inc.
// 
//                      All Rights Reserved.  
// 
//

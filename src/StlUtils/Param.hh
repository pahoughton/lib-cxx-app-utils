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
// Revision 1.4  1995/11/05 13:29:08  houghton
// Major Implementation Changes.
// Made more consistant with the C++ Standard
//
//

#include <ClueConfig.hh>
#include <Log.hh>
#include <Str.hh>
#include <DateTime.hh>

#include <cstdlib>
#include <climits>

#define DEFAULT_LOGLEVEL "ERROR | WARNING"

#define ALog( lvl )	LogIf( App->log(), lvl )

#ifndef UTIL_OPTIMIZE
#define inline
#endif

class Param
{

public:

  Param( int & mainArgc, char * mainArgv[], const char * version = 0 );

  inline Log &     log( void );
  inline Log &     log( LogLevel::Level lvl );

  inline const char *    appName( void ) const ;
  inline const char *    appFullName( void ) const;
  
  inline char *	    arg( size_t which = 1 );
  inline int	    argInt( size_t which = 1 );

  inline size_t    count( void ) const;

  inline const char *	env( const char * envVar ) const;

  bool	argString( char * &  	    dest,
		   const char *	    description,
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

  bool	argInt( unsigned int &	dest,
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

  bool	argShort( unsigned short & dest,
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

  bool	argLong( unsigned long & dest,
		 const char *	description,
		 const char *   argId,
		 const char *   envVar = 0,
		 unsigned long 	minVal = 0,
		 unsigned long 	maxVal = ULONG_MAX );

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
		     
  inline bool	help( void ) const;

  inline bool	allArgs( void ) const;

  inline void	abort( int  	    exitStatus = 1,
		       bool 	    showArgs = false,
		       ostream &    dest = cerr );

  virtual bool	    	good( void ) const;
  virtual const char *	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual ostream & 	toStream( ostream & dest ) const;
  virtual ostream & 	dumpInfo( ostream & dest ) const;
  
  static const char version[];
  
protected:

private:

  Param( const Param & copyFrom );
  Param & operator=( const Param & assignFrom );

  char *    getArgValue( const char * argId, const char * envVar );
  bool	    getArg( const char * argId, const char * envVar );
  
  Str	    	    helpString;
  
  int &	    	    argc;
  char **    	    argv;
  const char *	    ver;
  
  Log	    	    appLog;

  bool    	    helpFlag;

  char *    	    logFile;
  char *    	    logOutputLevel;
  
  bool	    	    logTee;
  unsigned long	    logMaxSize;
  unsigned long	    logTrimSize;
  
  bool	    	    ok;
  
};

#ifndef inline
#include <Param.ii>
#else
#undef inline

ostream &
operator<<( ostream & dest, const Param & param );
    
#endif


#endif // ! def _Param_hh_ 

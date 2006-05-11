//
// File:        AppParam.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for AppParam
//  
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     07/20/97 07:08
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include "AppParam.hh"

AppParam::AppParam(
  int &		mainArgc,
  char **	mainArgv,
  const char *	mainVer
  )
  : Param( mainArgc, mainArgv, mainVer, true, "ERROR | WARN | INFO" ),
    fnPatternV( "*" ),
    inDirV( "../data/in" ),
    procDirV( "../data/proc" ),
    waitSecsV( 0 )
{
  parseArgs();
}

AppParam::~AppParam( void )
{
}

bool
AppParam::parseArgs( int pArgc, char * pArgv[] )
{
  bool status = Param::parseArgs( pArgc, pArgv );

  return( status ? parseArgs() : status );
}

bool
AppParam::parseArgs( void )
{
  bool status = Param::parseArgs();

  status &= argStr( fnPatternV,
		    "FNPATTERN",
		    "file name pattern",
		    0,
		    true,
		    "p" );

  status &= argStr( inDirV,
		    "DIR",
		    "inbound directory",
		    0,
		    true,
		    "in" );

  status &= argStr( procDirV,
		    "DIR",
		    "process direcotry",
		    0,
		    true,
		    "proc" );

  status &= argLong( waitSecsV,
		     "SECONDS",
		    "rescan wait seconds",
		     0,
		     true,
		    "w" );
		    
  // status &= argStr( varV, "desc", "argid", "envVar" );

  return( status );
}

// Revision Log:
//
// $Log$
// Revision 6.2  2006/05/11 19:38:11  houghton
// *** empty log message ***
//
// Revision 6.1  2003/08/09 11:22:54  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:33  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:15:00  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:10:20  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/07/25 12:27:32  houghton
// Changed version number to 3.
//
// Revision 1.1  1997/07/20 18:55:52  houghton
// Initial Version.
//
//

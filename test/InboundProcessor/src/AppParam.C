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
		    "file name pattern",
		    "p" );

  status &= argStr( inDirV,
		    "inbound directory",
		    "in" );

  status &= argStr( procDirV,
		    "process direcotry",
		    "proc" );

  status &= argLong( waitSecsV,
		    "rescan wait seconds",
		    "w" );
		    
  // status &= argStr( varV, "desc", "argid", "envVar" );

  return( status );
}

// Revision Log:
//
// $Log$
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

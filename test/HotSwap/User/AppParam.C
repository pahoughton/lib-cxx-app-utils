//
// File:        AppParam.C
// Project:	Clue
// Desc:        
//
//  Compiled sources for AppParam
//  
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     09/13/97 12:28
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
    lockFnV( "../data/hotswap" ),
    swapCountV( 1 ),
    sleepTimeV( 5 )
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

  status &= argInt( sleepTimeV,
		     "sleep seconds",
		     "s",
		     "SLEEP_SEC" );
  
  status &= argLong( swapCountV,
		     "swap count",
		     "n",
		     "SWAP_COUNT" );
  
  // status &= argStr( varV, "desc", "argid", "envVar" );

  return( status );
}

// Revision Log:
//
// $Log$
// Revision 1.1  1997/09/16 11:31:26  houghton
// Initial Version.
//
//

//
// File:        AppParam.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for AppParam
//  
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     03/21/97 07:00
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include "AppParam.hh"

AppParam::AppParam( int & argc, char ** argv, const char * ver )
  : Param( argc, argv, ver, "ERROR | WARN | INFO" ),
    tThreeV( 0 )
{
  parseArgs();
}

AppParam::~AppParam( void )
{
}

bool
AppParam::parseArgs( int argc, char * argv[] )
{
  bool status = Param::parseArgs( argc, argv );

  return( status ? parseArgs() : status );
}

bool
AppParam::parseArgs( void )
{
  bool status = Param::parseArgs();

  // status &= argStr( varV, "desc", "argid", "envVar" );

  status &= argStr( tOneV,
		    "arg one with a very long desc entry to verify wrap.",
		    "t1",
		    "ENV_VALUE_ONE" );
  
  status &= argStr( tTwoV,
		    "arg two.",
		    "t2",
		    "ENV_VALUE_TWO" );
  
  status &= argLong( tThreeV,
		    "arg three with a very long desc entry to verify wrapping of help works the way it should.",
		    "t3",
		    "ENV_VALUE_THREE" );
  

  return( status );
}

// Revision Log:
//
// $Log$
// Revision 5.1  2000/05/25 10:33:24  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:43  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:09:30  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/03/21 15:58:13  houghton
// Changed base version to 3
//
// Revision 1.1  1997/03/21 15:57:47  houghton
// Initial Version.
//
// Revision 1.2  1997/03/21 15:47:50  houghton
// Initial Version
//
//

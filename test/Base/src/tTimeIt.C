//
// File:        tTimeIt.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tTimeIt
//  
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     07/08/97 08:11
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include <TestConfig.hh>
#include <LibTest.hh>

bool	tTimeIt01( LibTest & tester );

bool
tTimeIt( LibTest & tester )
{
  TESTP( tTimeIt01( tester ) );

  return( true );
}


// Revision Log:
//
// $Log$
// Revision 3.2  1997/09/17 11:10:14  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/07/11 15:57:08  houghton
// Initial Version.
//
//

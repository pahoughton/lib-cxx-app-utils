//
// File:        tFile.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tFile
//  
// Author:      Paul Houghton 719-527-7834 - (paul.houghton@wcom.com)
// Created:     03/08/98 09:13
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//


#include "TestConfig.hh"
#include "LibTest.hh"

bool tFile01( LibTest & tester );
bool tFile02( LibTest & tester );


bool
tFile( LibTest & tester )
{
  TESTP( tFile01( tester ) );
  TESTP( tFile02( tester ) );
  return( true );
}


// Revision Log:
//
// $Log$
// Revision 1.1  1998/03/21 13:57:29  houghton
// Initial Version.
//
//

//
// File:        tFileOp.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tFileOp
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

bool tFileOp01( LibTest & tester );
bool tFileOp02( LibTest & tester );


bool
tFileOp( LibTest & tester )
{
  TESTP( tFileOp01( tester ) );
  TESTP( tFileOp02( tester ) );
  return( true );
}


// Revision Log:
//
// $Log$
// Revision 6.1  2003/08/09 11:22:50  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:28  houghton
// Changed Version Num to 5
//
// Revision 1.2  1998/11/02 19:36:30  houghton
// Changed: the File class was renamed to FileOp.
//
// Revision 1.1  1998/03/21 13:57:29  houghton
// Initial Version.
//
//

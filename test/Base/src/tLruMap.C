//
// File:        tLruMap.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tLruMap
//  
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     09/08/98 10:21
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include <TestConfig.hh>
#include <LibTest.hh>

bool tLruMap01( LibTest & tester );

bool
tLruMap( LibTest & tester )
{
  TESTP( tLruMap01( tester ) );

  return( true );
}

// Revision Log:
//
// $Log$
// Revision 4.1  1998/10/13 15:22:01  houghton
// Initial Version.
//
//

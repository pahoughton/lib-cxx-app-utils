//
// File:        tLruSash.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tLruSash
//  
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     10/29/98 08:00
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include <TestConfig.hh>
#include <LibTest.hh>

bool tLruSash01( LibTest & tester );

bool
tLruSash( LibTest & tester )
{
  TESTP( tLruSash01( tester ) );

  return( true );
}


// Revision Log:
//
// $Log$
// Revision 4.1  1998/11/02 15:28:47  houghton
// Initial Version.
//
//

//
// File:        tLruSash.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tLruSash
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
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
// Revision 6.2  2011/12/30 23:57:45  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:51  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:29  houghton
// Changed Version Num to 5
//
// Revision 4.1  1998/11/02 15:28:47  houghton
// Initial Version.
//
//

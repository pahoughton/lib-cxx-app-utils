//
// File:        tLruMap.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tLruMap
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
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
// Revision 6.2  2011/12/30 23:57:45  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:51  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:29  houghton
// Changed Version Num to 5
//
// Revision 4.1  1998/10/13 15:22:01  houghton
// Initial Version.
//
//

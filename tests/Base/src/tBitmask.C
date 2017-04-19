//
// File:        tBitmask.C
// Project:	StlUtils
// Desc:        
//
//  Test for Bitmask class.
//
// Source Header Version: 2.7
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     10/30/96 06:04
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#endif

bool tBitmask01( LibTest & tester );
bool tBitmask02( LibTest & tester );
bool tBitmask03( LibTest & tester );

bool
tBitmask( LibTest & tester )
{
  TESTP( tBitmask01( tester ) );
  TESTP( tBitmask02( tester ) );
  TESTP( tBitmask03( tester ) );
   
  return( true );
}

//
// $Log$
// Revision 6.2  2011/12/30 23:57:42  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:50  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:27  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:03  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:09:35  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:26:22  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:45:41  houghton
// Added header comments.
// Changed TESTP args.
//
//

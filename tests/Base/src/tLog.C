//
// File:        tLog.C
// Project:	StlUtils
// Desc:        
//
//  Test for Log class
//
// Source Header Version: 2.8
//
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     11/11/96 16:28
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//


#include "TestConfig.hh"
#include "LibTest.hh"

bool tLogLevel( LibTest & tester );
bool tLog01( LibTest & tester );
bool tLog02( LibTest & tester );
bool tLog03( LibTest & tester );
bool tLog04( LibTest & tester );
bool tLog05( LibTest & tester );
bool tLog06( LibTest & tester );
bool tLog07( LibTest & tester );
bool tLog08( LibTest & tester );
bool tLog09( LibTest & tester );


bool
tLog( LibTest & tester )
{
  TESTP( tLogLevel( tester ) );
  TESTP( tLog01( tester ) );
  TESTP( tLog02( tester ) );
  TESTP( tLog03( tester ) );
  TESTP( tLog04( tester ) );
  TESTP( tLog05( tester ) );
  TESTP( tLog06( tester ) );
  TESTP( tLog07( tester ) );
  TESTP( tLog08( tester ) );
  TESTP( tLog09( tester ) );
  return( true );
}

//
// $Log$
// Revision 6.2  2011/12/30 23:57:44  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:51  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:28  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:20  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:09:48  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1996/11/20 12:16:16  houghton
// Cleanup.
//
// Revision 3.1  1996/11/14 01:26:44  houghton
// Changed to Release 3
//
// Revision 2.3  1996/11/13 17:19:19  houghton
// Added calls to new test functions (06, 07, 08 & 09).
//
//

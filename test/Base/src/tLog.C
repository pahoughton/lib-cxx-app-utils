//
// File:        tLog.C
// Project:	Clue
// Desc:        
//
//  Test for Log class
//
// Source Header Version: 2.8
//
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
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
// Revision 2.3  1996/11/13 17:19:19  houghton
// Added calls to new test functions (06, 07, 08 & 09).
//
//

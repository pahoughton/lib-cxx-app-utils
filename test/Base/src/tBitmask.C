//
// File:        tBitmask.C
// Project:	Clue
// Desc:        
//
//  Test for Bitmask class.
//
// Source Header Version: 2.7
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/30/96 06:04
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#if !defined( CLUE_SHORT_FN )
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
// Revision 3.1  1996/11/14 01:26:22  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:45:41  houghton
// Added header comments.
// Changed TESTP args.
//
//

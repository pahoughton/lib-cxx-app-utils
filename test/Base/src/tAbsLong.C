//
// File:        tAbsLong.C
// Project:	Clue
// Desc:        
//
//  Test for abs( long ) function.
//  
// Source Header Version: 2.4
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/31/96 07:17
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <ClueUtils.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
#endif

bool
tAbsLong( LibTest & tester )
{
  {
    long  t = -12341234L;
    
    TEST( abs( t ) == 12341234L );

    t = 43214321L;
    
    TEST( abs( t ) == 43214321L );
  }

  return( true );
}

//
// $Log$
// Revision 2.3  1996/11/04 18:22:39  houghton
// Chaged include becuase Clue.hh renamed to ClueUtils.hh.
//
// Revision 2.2  1996/11/04 14:43:56  houghton
// Added header comments.
//
//


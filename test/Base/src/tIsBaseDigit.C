//
// File:        tIsBaseDigit.C
// Project:	Clue
// Desc:        
//
//  Test for IsBaseDigit function
//
// Source Header Version: 2.4
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/31/96 07:15
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
#endif


#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
#endif


bool
tIsBaseDigit( LibTest & tester )
{
  {
    // IsBaseDigit( int, unsigned short )
    
    for( unsigned short base = 2; base < 64; base++ )
      {
	for( int num = -2; num < base+2; num++ )
	  {
	    bool result = IsBaseDigit( num,  base );
	    
	    TEST( ( result == true && num >= 0 && num < base )  ||
		  ( result == false && ( num < 0 || num >= base ) ) );
	  }
      }
  }


    
  return( true );
}
	  
//
// $Log$
// Revision 2.2  1996/11/04 14:48:11  houghton
// Added header comments.
// Removed IsBaseDigit( char ) - has been changed to CharIsBaseDigit.
//
//

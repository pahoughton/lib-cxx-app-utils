//
// File:        tBetween.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tBetween
//  
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     11/04/98 10:00
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include <TestConfig.hh>
#include <LibTest.hh>
#include <StlUtilsMisc.hh>

bool
tBetween( LibTest & tester )
{
  {
    long    a( 1023 );
    long    b( a + 2732 );

    {
      for( short t = a; t <= b; ++ t )
	{
	  TEST( Between( a, b, t ) );
	  TEST( Between( b, a, t ) );
	}
    }
    TEST( ! Between( a, b, a * -1 ) );
    TEST( ! Between( b, a, a * -1 ) );
    
    TEST( ! Between( a, b, 0 ) );
    TEST( ! Between( b, a, 0 ) );
    
    TEST( ! Between( a, b, a - 1 ) );
    TEST( ! Between( b, a, a - 1 ) );
    
    TEST( ! Between( a, b, b + 1 ) );
    TEST( ! Between( b, a, b + 1 ) );
    
    TEST( ! Between( a, b, b + a ) );
    TEST( ! Between( b, a, b + a ) );
  }

  return( true );
}

// Revision Log:
//
// $Log$
// Revision 5.1  2000/05/25 10:33:27  houghton
// Changed Version Num to 5
//
// Revision 4.1  1999/03/02 12:54:21  houghton
// Initial Version.
//
//

//
// File:        tIsBaseDigit.C
// Project:	StlUtils
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

#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StlUtilsMisc.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StlUtils.hh>
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
// Revision 5.1  2000/05/25 10:33:28  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:19  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 15:11:07  houghton
// Renamed StlUtilsUtils.hh to StlUtilsMisc.hh
//
// Revision 3.2  1997/09/17 11:09:47  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:26:43  houghton
// Changed to Release 3
//
// Revision 2.3  1996/11/04 18:22:53  houghton
// Chaged include because StlUtils.hh renamed to StlUtilsUtils.hh.
//
// Revision 2.2  1996/11/04 14:48:11  houghton
// Added header comments.
// Removed IsBaseDigit( char ) - has been changed to CharIsBaseDigit.
//
//

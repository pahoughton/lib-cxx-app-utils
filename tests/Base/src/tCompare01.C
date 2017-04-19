//
// File:        tCompare01.C
// Project:	StlUtils
// Desc:        
//
//  Test for Compare functions in Compare.hh
//
// Source Header Version: 2.3
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     10/27/96 04:13
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//


#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Compare.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Compare.hh>
#endif

bool
tCompare01( LibTest & tester )
{
  {
    // compare( number, number )
    
    TEST( compare( -15, -25 ) > 0 );
    TEST( compare( -15, -15 ) == 0 );
    TEST( compare( -15,  -5 ) < 0 );
    TEST( compare( -15,   0 ) < 0 );
    TEST( compare( -15,   5 ) < 0 );
    TEST( compare( -15,  15 ) < 0 );
    TEST( compare( -15,  25 ) < 0 );
    
    TEST( compare(   0, -25 ) > 0 );
    TEST( compare(   0, -15 ) > 0 );
    TEST( compare(   0,  -5 ) > 0 );
    TEST( compare(   0,   0 ) == 0 );
    TEST( compare(   0,   5 ) < 0 );
    TEST( compare(   0,  15 ) < 0 );
    TEST( compare(   0,  25 ) < 0 );

    TEST( compare(  15, -25 ) > 0 );
    TEST( compare(  15, -15 ) > 0 );
    TEST( compare(  15,  -5 ) > 0 );
    TEST( compare(  15,   0 ) > 0 );
    TEST( compare(  15,   5 ) > 0 );
    TEST( compare(  15,  15 ) == 0 );
    TEST( compare(  15,  25 ) < 0 );

    
    TEST( compare( -15.5, -25.5 ) > 0 );
    TEST( compare( -15.5, -15.5 ) == 0 );
    TEST( compare( -15.5,  -5.5 ) < 0 );
    TEST( compare( -15.5,   0.5 ) < 0 );
    TEST( compare( -15.5,   5.5 ) < 0 );
    TEST( compare( -15.5,  15.5 ) < 0 );
    TEST( compare( -15.5,  25.5 ) < 0 );
    
    TEST( compare(   0.5, -25.5 ) > 0 );
    TEST( compare(   0.5, -15.5 ) > 0 );
    TEST( compare(   0.5,  -5.5 ) > 0 );
    TEST( compare(   0.5,   0.5 ) == 0 );
    TEST( compare(   0.5,   5.5 ) < 0 );
    TEST( compare(   0.5,  15.5 ) < 0 );
    TEST( compare(   0.5,  25.5 ) < 0 );

    TEST( compare(  15.5, -25.5 ) > 0 );
    TEST( compare(  15.5, -15.5 ) > 0 );
    TEST( compare(  15.5,  -5.5 ) > 0 );
    TEST( compare(  15.5,   0.5 ) > 0 );
    TEST( compare(  15.5,   5.5 ) > 0 );
    TEST( compare(  15.5,  15.5 ) == 0 );
    TEST( compare(  15.5,  25.5 ) < 0 );

  }

  return( true );
}

//
// $Log$
// Revision 6.2  2011/12/30 23:57:43  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:50  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:27  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:07  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:09:39  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:26:26  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:47:17  houghton
// Added header comments.
//
//

//
// File:        tRound.C
// Project:	StlUtils
// Desc:        
//
//  Test for Round functions
//
// Source Header Version: 2.4
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/31/96 07:30
//
// Revision History: (See end of file for Revision Log)
//


#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StlUtilsUtils.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StlUtils.hh>
#endif

bool
tRound( LibTest & tester )
{
  {
    // Round( int, number )

    int t = 50;

    TEST( Round( t, 10 ) == 50 );
    t = 51;
    TEST( Round( t, 10 ) == 50 );
    t = 55;
    TEST( Round( t, 10 ) == 60 );
    t = 59;
    TEST( Round( t, 10 ) == 60 );

    t = 10;
    TEST( Round( t, 5 ) == 10 );
    t = 11;
    TEST( Round( t, 5 ) == 10 );
    t = 12;
    TEST( Round( t, 5 ) == 10 );
    t = 13;
    TEST( Round( t, 5 ) == 15 );
    t = 14;
    TEST( Round( t, 5 ) == 15 );

    TEST( Round( 23, 5 ) == 25 ); // doc example
  }

  {
    long t = 50;
   
    TEST( Round( t, 10 ) == 50 );
    t = 51;
    TEST( Round( t, 10 ) == 50 );
    t = 55;
    TEST( Round( t, 10 ) == 60 );
    t = 59;
    TEST( Round( t, 10 ) == 60 );

    t = 10;
    TEST( Round( t, 5 ) == 10 );
    t = 11;
    TEST( Round( t, 5 ) == 10 );
    t = 12;
    TEST( Round( t, 5 ) == 10 );
    t = 13;
    TEST( Round( t, 5 ) == 15 );
    t = 14;
    TEST( Round( t, 5 ) == 15 );
  }

  {
    // RoundUp( int, number )

    int t = 50;

    TEST( RoundUp( t, 10 ) == 50 );
    t = 51;
    TEST( RoundUp( t, 10 ) == 60 );
    t = 55;
    TEST( RoundUp( t, 10 ) == 60 );
    t = 59;
    TEST( RoundUp( t, 10 ) == 60 );

    t = 10;
    TEST( RoundUp( t, 5 ) == 10 );
    t = 11;
    TEST( RoundUp( t, 5 ) == 15 );
    t = 12;
    TEST( RoundUp( t, 5 ) == 15 );
    t = 13;
    TEST( RoundUp( t, 5 ) == 15 );
    t = 14;
    TEST( RoundUp( t, 5 ) == 15 );

    TEST( RoundUp( 22, 5 ) == 25 ); // doc example
  }
  
  {
    // RoundDown( int, number )

    int t = 50;

    TEST( RoundDown( t, 10 ) == 50 );
    t = 51;
    TEST( RoundDown( t, 10 ) == 50 );
    t = 55;
    TEST( RoundDown( t, 10 ) == 50 );
    t = 59;
    TEST( RoundDown( t, 10 ) == 50 );

    t = 10;
    TEST( RoundDown( t, 5 ) == 10 );
    t = 11;
    TEST( RoundDown( t, 5 ) == 10 );
    t = 12;
    TEST( RoundDown( t, 5 ) == 10 );
    t = 13;
    TEST( RoundDown( t, 5 ) == 10 );
    t = 14;
    TEST( RoundDown( t, 5 ) == 10 );

    TEST( RoundDown( 23, 5 ) == 20 ); // doc example
  }

  return( true );
}

//
// $Log$
// Revision 3.2  1997/09/17 11:09:56  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:26:55  houghton
// Changed to Release 3
//
// Revision 2.3  1996/11/04 18:22:54  houghton
// Chaged include because StlUtils.hh renamed to StlUtilsUtils.hh.
//
// Revision 2.2  1996/11/04 14:50:49  houghton
// Added header comments.
// Chagned to test everything in RegexScan.hh.
//
//

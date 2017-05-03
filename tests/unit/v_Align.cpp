//
// File:        tAlign.C
// Project:	StlUtils
// Desc:        
//
//  Test for Align functions.
//  
// Source Header Version: 2.4
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     10/31/96 06:53
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
tAlign( LibTest & tester )
{
  {
    // Align( value, size_t )

    int	    tInt;
    short   tShort;
    long    tLong;

    tInt = 4096;
    TEST( Align( tInt, 4096 ) == 4096 );
    tInt = 4095;
    TEST( Align( tInt, 4096 ) == 4096 );
    tInt = 1;
    TEST( Align( tInt, 4096 ) == 4096 );
    tShort = 11;
    TEST( Align( tShort, 5 ) == 15 );
    tLong = 0;
    TEST( Align( tLong, 2048 ) == 2048 );
  }

  {
    // Align( value )

    char    tChar  = 41;
    short   tShort = 41;
    int	    tInt   = 41; 
    long    tLong  = 41;

    TEST( Align( tChar ) == 41 );
    TEST( ( sizeof( short ) == 1 && Align( tShort ) == 41 ) ||
	  ( sizeof( short ) == 2 && Align( tShort ) == 42 ) ||
	  ( sizeof( short ) == 4 && Align( tShort ) == 44 ) );
    TEST( ( sizeof( int ) == 2 && Align( tInt ) == 42 ) ||
	  ( sizeof( int ) == 4 && Align( tInt ) == 44 ) ||
	  ( sizeof( int ) == 8 && Align( tInt ) == 48 ) );
    TEST( ( sizeof( long ) == 4 && Align( tLong ) == 44 ) ||
	  ( sizeof( long ) == 8 && Align( tLong ) == 48 ) );
  }

  return( true );
}

      
//
// $Log$
// Revision 6.2  2011/12/30 23:57:41  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:50  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:26  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:02  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 15:11:07  houghton
// Renamed StlUtilsUtils.hh to StlUtilsMisc.hh
//
// Revision 3.2  1997/09/17 11:09:34  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:26:18  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 18:22:52  houghton
// Chaged include because StlUtils.hh renamed to StlUtilsUtils.hh.
//
// Revision 2.1  1996/11/04 14:44:08  houghton
// Initial Version.
//
//

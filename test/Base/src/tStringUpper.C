//
// File:        tStringUpper.C
// Project:	StlUtils
// Desc:        
//
//  Test StringUpper Function
//  
// Source Header Version: StringUtils.hh 2.4
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     10/29/96 07:15
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StringUtils.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StrUtil.hh>
#endif

bool
tStringUpper( LibTest & tester )
{
  {
    const char su[] = "THIS IS A 1234567890-=!@#$%^&*()_+[]{};':\",./<>? TEST";

    char sul[] = "THIS IS A 1234567890-=!@#$%^&*()_+[]{};':\",./<>? TEST";
    char sml[] = "tHIS is A 1234567890-=!@#$%^&*()_+[]{};':\",./<>? teST";
    char sll[] = "this is a 1234567890-=!@#$%^&*()_+[]{};':\",./<>? test";

    StringUpper( sul );
    StringUpper( sml );
    StringUpper( sll );

    TEST( strcmp( sul, su ) == 0 );
    TEST( strcmp( sml, su ) == 0 );
    TEST( strcmp( sll, su ) == 0 );
  }

  {
    const char su[] = "THIS IS AsiZE 12345-=!@#$%^&*()_+[]{};':\",./<>? teST";
    //                01234567890

    char suu[] = "THIS IS AsiZE 12345-=!@#$%^&*()_+[]{};':\",./<>? teST";
    char smu[] = "thIS IS AsiZE 12345-=!@#$%^&*()_+[]{};':\",./<>? teST";
    char slu[] = "this is asiZE 12345-=!@#$%^&*()_+[]{};':\",./<>? teST";
    
    StringUpper( slu, 9 );
    StringUpper( smu, 9 );
    StringUpper( suu, 9 );

    TEST( strcmp( slu, su ) == 0 );
    TEST( strcmp( smu, su ) == 0 );
    TEST( strcmp( suu, su ) == 0 );
  }

  return( true );
}

    
      
//
// $Log$
// Revision 6.2  2011/12/30 23:57:48  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:52  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:31  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:47  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:10:10  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:27:14  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:53:02  houghton
// Added header comments.
//
//

//
// File:        tStringUpper.C
// Project:	Clue
// Desc:        
//
//  Test StringUpper Function
//  
// Source Header Version: StringUtils.hh 2.4
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/29/96 07:15
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#if !defined( CLUE_SHORT_FN )
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
// Revision 2.2  1996/11/04 14:53:02  houghton
// Added header comments.
//
//

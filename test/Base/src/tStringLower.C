//
// File:        tStringLower.C
// Project:	Clue
// Desc:        
//
//  Test StringLower function.
//  
// Source Header Version: StringUtils.hh 2.4
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/29/96 06:59
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
tStringLower( LibTest & tester )
{
  {
    // StringLower( char * )
    
    const char sl[] = "this is a 1234567890-=!@#$%^&*()_+[]{};':\",./<>? test";

    char sul[] = "THIS IS A 1234567890-=!@#$%^&*()_+[]{};':\",./<>? TEST";
    char sml[] = "tHIS is A 1234567890-=!@#$%^&*()_+[]{};':\",./<>? teST";
    char sll[] = "this is a 1234567890-=!@#$%^&*()_+[]{};':\",./<>? test";

    StringLower( sul );
    StringLower( sml );
    StringLower( sll );

    TEST( strcmp( sul, sl ) == 0 );
    TEST( strcmp( sml, sl ) == 0 );
    TEST( strcmp( sll, sl ) == 0 );
  }

  {
    // StringLower( char *, size_t )
    
    const char sl[] = "this is aSIZE 12345-=!@#$%^&*()_+[]{};':\",./<>? teST";
    //                01234567890
    
    char sul[] = "THIS IS ASIZE 12345-=!@#$%^&*()_+[]{};':\",./<>? teST";
    char sml[] = "thIS is aSIZE 12345-=!@#$%^&*()_+[]{};':\",./<>? teST";
    char sll[] = "this is aSIZE 12345-=!@#$%^&*()_+[]{};':\",./<>? teST";

    StringLower( sul, 9 );
    StringLower( sml, 9 );
    StringLower( sll, 9 );

    TEST( strcmp( sul, sl ) == 0 );
    TEST( strcmp( sml, sl ) == 0 );
    TEST( strcmp( sll, sl ) == 0 );
  }

  return( true );
}

//
// $Log$
// Revision 3.1  1996/11/14 01:27:11  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:52:11  houghton
// Added header comments.
//
//

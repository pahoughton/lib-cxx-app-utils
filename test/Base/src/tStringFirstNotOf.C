//
// File:        tStringFirstNotOf.C
// Project:	Clue
// Desc:        
//
//  Test for StringFirstNotOf function.
//
// Source Header Version: 
//
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     08/12/97 03:57
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include <TestConfig.hh>
#include <LibTest.hh>
#include <StringUtils.hh>

#define HAY "this is the 123 haystack to search in 123 .,? aabbbcc 123"
//           012345678901234567890123456789012345678901234567890123456
//                     1         2         3         4         5

bool
tStringFirstNotOf( LibTest & tester )
{
  {
    const char * hay = HAY;
    const char * needle = "this ";

    TEST( StringFirstNotOf( hay, NPOS, needle, NPOS ) == 10 );

    needle = "this e123ayckorn,.?b";

    TEST( StringFirstNotOf( hay, NPOS, needle, NPOS ) == NPOS );

    hay = "abcdefghijklmnop12345,.!@#-+=_";
//         012345678901234567890123456789012345678901234567890123456
//                   1         2         3         4         5
    needle = "abcdefghijklmnopqrstuvwxyz";
//            012345678901234567890123456789012345678901234567890123456
//                      1         2         3         4         5
    TEST( StringFirstNotOf( hay, 16, needle, NPOS ) == NPOS );
    TEST( StringFirstNotOf( hay, 17, needle, NPOS ) == 16 );

    hay = "abcdefghijklmnopqrstuvwxyz";
    
    TEST( StringFirstNotOf( hay, NPOS, needle, NPOS ) == NPOS );
    TEST( StringFirstNotOf( hay, NPOS, needle, 17 ) == 17 );
      
      
  }

  return( true );
}
    
// Revision Log:
//
// $Log$
// Revision 3.1  1997/08/12 11:11:58  houghton
// Initial Version.
//
//

//
// File:        tStringCapitalize.C
// Project:	StlUtils
// Desc:        
//
//  Test StringCapitalize function.
//  
// Source Header Version: StringUtils.hh 2.4
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/29/96 09:59
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
tStringCapitalize( LibTest & tester )
{
  {
    // StringCapialize( char * )
    
    const char * sc =   "This-Is.A Test 12a34 Abc123 -Abc- Abc-Def? Good?";

    char su[] = "THIS-IS.A TEST 12A34 ABC123 -ABC- ABC-DEF? GOOD?";
    char sm[] = "thIS-IS.a tesT 12a34 abc123 -Abc- abc-def? GOod?";
    char sl[] = "this-is.a test 12a34 abc123 -abc- abc-def? good?";

    StringCapitalize( su );
    StringCapitalize( sm );
    StringCapitalize( sl );

    TEST( strcmp( su, sc ) == 0 );
    TEST( strcmp( sm, sc ) == 0 );
    TEST( strcmp( sl, sc ) == 0 );

  }

  {
    // StringCapialize( char *, size_t )
    
    const char * sc =   "This-Is.A test 12a34 abc123 -abc- abc-def? good?";
    //                  0123456789 1
    char su[] = "THIS-IS.A test 12a34 abc123 -abc- abc-def? good?";
    char sm[] = "thIS-Is.a test 12a34 abc123 -abc- abc-def? good?";
    char sl[] = "this-is.a test 12a34 abc123 -abc- abc-def? good?";

    StringCapitalize( su, 10 );
    StringCapitalize( sm, 10 );
    StringCapitalize( sl, 10 );

    TEST( strcmp( su, sc ) == 0 );
    TEST( strcmp( sm, sc ) == 0 );
    TEST( strcmp( sl, sc ) == 0 );

  }

  return( true );
}

//
// $Log$
// Revision 5.1  2000/05/25 10:33:31  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:43  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:10:07  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:27:10  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:51:24  houghton
// Added header comments.
//
//

//
// File:        tbasename.C
// Project:	StlUtils
// Desc:        
//
//  Test for basename functions
//  
// Source Header Version: StringUtils.hh 2.4
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/30/96 04:08
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StringUtils.hh>
#include <Compare.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StrUtil.hh>
#include <Compare.hh>
#endif

bool
tbasename( LibTest & tester )
{
  {
    // basename( const char * fn )

    const char * t;

    t = "/this/is/a/test";
    TEST( compare( basename( t ) , "test" ) == 0 );

    t = "another/test.try";
    TEST( compare( basename( t ) , "test.try" ) == 0 );

    t = "one.more";
    TEST( compare( basename( t ) , "one.more" ) == 0 );
  }
  
  {
    // basename( char * fn )

    char t[100];

    strcpy( t, "/this/is/a/test");
    TEST( compare( basename( t ) , "test" ) == 0 );

    strcpy( t, "another/test.try");
    TEST( compare( basename( t ) , "test.try" ) == 0 );

    strcpy( t, "one.more");
    TEST( compare( basename( t ) , "one.more" ) == 0 );
  }

  return( true );
}
      
//
// $Log$
// Revision 6.1  2003/08/09 11:22:53  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:32  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:55  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:10:17  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:27:24  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:53:58  houghton
// Added header comments.
//
//

//
// File:        tStripTrailing.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tStripTrailing
//  
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     12/20/97 08:20
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

bool
tStripTrailing( LibTest & tester )
{
  {
    char t[ 1024 ];

    const char * exp = "this is a test";

    strcpy( t, exp );

    StripTrailing( t );
    TEST( strcmp( t, exp ) == 0 );

    strcpy( t, exp );
    strcat( t, "\t\t  " );

    StripTrailing( t );
    TEST( strcmp( t, exp ) == 0 );

    strcpy( t, "\t\t  \t\t" );

    StripTrailing( t );
    TEST( t[0] == 0 );
  }

  return( true );
}


    

// Revision Log:
//
// $Log$
// Revision 6.1  2003/08/09 11:22:53  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:31  houghton
// Changed Version Num to 5
//
// Revision 1.1  1997/12/20 16:13:47  houghton
// Initial Version.
//
//

//
// File:        tMfNumTo.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tMfNumTo
//  
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     12/15/97 17:00
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
tMfNumTo( LibTest & tester )
{
  char  dest[20];

  memset( dest, 'x', 19 );
  
  TEST( MfNumTo( dest, 10, 1, "1234567L", 8 ) );

  dest[19] = 0;

  TEST( strcmp( dest, "-1234567.3xxxxxxxxx" ) == 0 );

  
  memset( dest, 'x', 19 );
  
  TEST( MfNumTo( dest, 10, 3, "    ", 4 ) );

  dest[19] = 0;

  TEST( strcmp( dest, "000000.000xxxxxxxxx" ) == 0 );

  
  memset( dest, 'x', 19 );
  
  TEST( MfNumTo( dest, 10, 0, "1234", 4 ) );

  dest[19] = 0;

  TEST( strcmp( dest, "0000001234xxxxxxxxx" ) == 0 );

  
  memset( dest, 'x', 19 );
  
  TEST( MfNumTo( dest, 10, 4, "1234", 4 ) );

  dest[19] = 0;

  TEST( strcmp( dest, "00000.1234xxxxxxxxx" ) == 0 );
  
  // cout << "\n'" << dest << '\'' << endl;

  return( true );
}


// Revision Log:
//
// $Log$
// Revision 1.1  1997/12/19 12:53:17  houghton
// Initial Version.
//
//

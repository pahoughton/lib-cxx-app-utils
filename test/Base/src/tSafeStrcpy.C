//
// File:        tSafeStrcpy.C
// Project:	StlUtils
// Desc:        
//
//  Test for SafeStrcpy function.
//
// Source Header Version: StringUtils.hh 2.4
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/30/96 04:20
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StringUtils.hh>
#include <algorithm>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StrUtil.hh>
#include <algorithm>
#endif


bool
tSafeStrcpy( LibTest & tester )
{

  // SafeStrcpy( char *, const char *, size_t )
  char  b[ 15 ];
  char  tBuffer[ 128 ];

  memset( tBuffer, '*', sizeof( tBuffer ) );
  
  SafeStrcpy( tBuffer, "short", sizeof( b ) );

  TEST( ! strcmp( tBuffer, "short" ) );
  TEST( tBuffer[ 14 ] == 0 );
  TEST( tBuffer[ 15 ] == '*' );

  memset( tBuffer, '*', sizeof( tBuffer ) );
  
  SafeStrcpy( tBuffer, "123456789 123456789", sizeof( b ) );

  TEST( ! strcmp( tBuffer, "123456789 1234" ) );
  TEST( tBuffer[ 14 ] == 0 );
  TEST( tBuffer[ 15 ] == '*' );
  
  memset( tBuffer, '*', sizeof( tBuffer ) );
  
  SafeStrcpy( tBuffer, "short", min( strlen( "short" ) + 1, sizeof( b ) ) );

  TEST( ! strcmp( tBuffer, "short" ) );
  TEST( tBuffer[ 5 ] == 0 );
  TEST( tBuffer[ 6 ] == '*' );

  return( true );
}


//
// $Log$
// Revision 5.1  2000/05/25 10:33:29  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:30  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:09:57  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:26:55  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:51:01  houghton
// Added header comments.
//
//

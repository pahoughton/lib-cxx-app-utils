//
// File:        tMemOverlap.C
// Project:	StlUtils
// Desc:        
//
//  Test for MemOverlap function.
//  
// Source Header Version: 2.4
//
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/31/96 07:12
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
tMemOverlap( LibTest & tester )
{
  char   buffer[128];
  size_t size = sizeof( buffer );
  
  char *  t = buffer;
  size_t  ts = size;

  // t = b
  TEST( MemOverlap( buffer, size, t, ts ) );

  // front 
  ts = 0;
  TEST( ! MemOverlap( buffer, size, t, ts ) );

  ts = 1;
  TEST( MemOverlap( buffer, size, t, ts ) );

  ts = 200;
  TEST( MemOverlap( buffer, size, t, ts ) );
  
  t -= 10;
  ts = 10;
  TEST( ! MemOverlap( buffer, size, t, ts ) );

  ts++;
  TEST( MemOverlap( buffer, size, t, ts ) );
  
  ts = 200;
  TEST( MemOverlap( buffer, size, t, ts ) );

  ts = 9;
  TEST( ! MemOverlap( buffer, size, t, ts ) );

  t = buffer + 50;
  ts = 10;
  TEST( MemOverlap( buffer, size, t, ts ) );

  ts = 200;
  TEST( MemOverlap( buffer, size, t, ts ) );

  t = buffer + (size - 1);
  ts = 0;
  TEST( ! MemOverlap( buffer, size, t, ts ) );

  ts = 1;
  TEST( MemOverlap( buffer, size, t, ts ) );
  
  ts = 100;
  TEST( MemOverlap( buffer, size, t, ts ) );
  
  t++;
  ts = 0;
  TEST( ! MemOverlap( buffer, size, t, ts ) );
  
  ts = 5;
  TEST( ! MemOverlap( buffer, size, t, ts ) );

  return( true );
}

//
// $Log$
// Revision 5.1  2000/05/25 10:33:29  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:27  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 15:11:08  houghton
// Renamed StlUtilsUtils.hh to StlUtilsMisc.hh
//
// Revision 3.2  1997/09/17 11:09:54  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:26:52  houghton
// Changed to Release 3
//
// Revision 2.3  1996/11/04 18:22:53  houghton
// Chaged include because StlUtils.hh renamed to StlUtilsUtils.hh.
//
// Revision 2.2  1996/11/04 14:50:07  houghton
// Added header comments.
//
//


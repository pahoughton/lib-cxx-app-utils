//
// File:        tArraySize.C
// Project:	StlUtils
// Desc:        
//
//  Test for the ArraySize macro.
//  
// Source Header Version: 2.4
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/31/96 06:42
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

struct TestValue
{
  long  a;
  char  b;
  short c;
};

static char 	CharArray[] =  	{ '1', '2', '3', '4' };
static int 	IntArray[] = 	{ 1, 2, 3, 4, 5, 6 };
static short 	ShortArray[] =  { 1, 2, 3, 4, 5, 6, 7 };
static long 	LongArray[] =   { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
static const char *	StringArray[] = { "1", "2", "3", "4", "5", 0 };

static TestValue TestArray[] =
{
  { 1, 'a', 1 },
  { 2, 'b', 2 },
  { 3, 'c', 3 },
  { 4, 'd', 4 },
  { 5, 'e', 5 }
};

bool
tArraySize( LibTest & tester )
{
  // ArraySize( array )
  
  TEST( ArraySize( CharArray ) 	 == 4 );
  TEST( ArraySize( IntArray )  	 == 6 );
  TEST( ArraySize( ShortArray )  == 7 );
  TEST( ArraySize( LongArray ) 	 == 9 );
  TEST( ArraySize( StringArray ) == 6 );
  TEST( ArraySize( TestArray ) 	 == 5 );
  
  return( true );
}

//
// $Log$
// Revision 6.1  2003/08/09 11:22:50  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:26  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:02  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 15:11:07  houghton
// Renamed StlUtilsUtils.hh to StlUtilsMisc.hh
//
// Revision 3.2  1997/09/17 11:09:34  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:26:19  houghton
// Changed to Release 3
//
// Revision 2.4  1996/11/04 18:22:52  houghton
// Chaged include because StlUtils.hh renamed to StlUtilsUtils.hh.
//
// Revision 2.3  1996/11/04 14:44:25  houghton
// Added header comments.
//
//

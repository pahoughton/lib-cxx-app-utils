//
// File:        tArraySize.C
// Project:	Clue
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


#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
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
// Revision 2.3  1996/11/04 14:44:25  houghton
// Added header comments.
//
//

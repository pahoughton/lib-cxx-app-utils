//
// File:        tDwordAlign.C
// Project:	Clue
// Desc:        
//
//  Test for DwordAlign functions.
//  
// Source Header Version: 2.4
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/31/96 07:10
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <ClueUtils.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
#endif

bool
tDwordAlign( LibTest & tester )
{
  {
    // DwordAlign( unsigned long value )
    long	num;
    
    num = 400;
    TEST( DwordAlign( num ) == 400 );
    TEST( DwordAlign( num + 1) == 404 );
    TEST( DwordAlign( num + 2) == 404 );
    TEST( DwordAlign( num + 3) == 404 );
    TEST( DwordAlign( num + 4) == 404 );

  }

  {
    // DwordAlign( void * addr )
    long    num = 400;
    
    long * lPtr = &num;
    
    char * ptr = (char *)lPtr;

#if defined( COMPARE_UNLIKE_POINTERS )
    TEST( ( ((long*)ptr ) == ptr) );
    TEST( ( ((long*)(ptr + 1)) == (ptr + 1) ) );
    TEST( ( ((long*)(ptr + 2)) == (ptr + 2) ) );
#endif
    
    TEST( ( ((long*)DwordAlign( ptr )) == lPtr ) );

    lPtr++;
    TEST( ( ((long*)DwordAlign( ptr + 1 )) == lPtr ) );
    TEST( ( ((long*)DwordAlign( ptr + 2 )) == lPtr ) );
    TEST( ( ((long*)DwordAlign( ptr + 3 )) == lPtr ) );
    TEST( ( ((long*)DwordAlign( ptr + 4 )) == lPtr ) );
  }
  
  return( true );
}

//
// $Log$
// Revision 2.3  1996/11/04 18:22:52  houghton
// Chaged include because Clue.hh renamed to ClueUtils.hh.
//
// Revision 2.2  1996/11/04 14:47:43  houghton
// Added header comments.
//
//

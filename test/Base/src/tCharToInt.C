//
// File:        tCharToInt.C
// Project:	Clue
// Desc:        
//
//  Test for CharToInt function.
//  
// Source Header Version: StringUtils.hh 2.4
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/30/96 04:21
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//
#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StringUtils.hh>
#include <climits>
#include <cctype>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StrUtil.hh>
#include <climits>
#include <cctype>
#endif


bool
tCharToInt( LibTest & tester )
{
  for( char c = 0; c < CHAR_MAX; c++ )
    {
      int   n = CharToInt( c );

      TEST( ( ! isalpha( c ) && ! isdigit( c ) && n == -1 ) ||
	    ( isalpha(c) && ( n == ( 10 + (tolower(c) - 'a') ) ) ) ||
	    ( isdigit(c) && ( n == ( c - '0' ) ) ) );
      
    }
  return( true );
}

//
// $Log$
// Revision 3.1  1996/11/14 01:26:25  houghton
// Changed to Release 3
//
// Revision 2.3  1996/11/04 14:46:47  houghton
// Added header comments.
//
//
	  

//
// File:        tCharToInt.C
// Project:	StlUtils
// Desc:        
//
//  Test for CharToInt function.
//  
// Source Header Version: StringUtils.hh 2.4
//  
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     10/30/96 04:21
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//
#if !defined( STLUTILS_SHORT_FN )
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
// Revision 6.2  2011/12/30 23:57:42  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:50  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:27  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:06  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:09:38  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:26:25  houghton
// Changed to Release 3
//
// Revision 2.3  1996/11/04 14:46:47  houghton
// Added header comments.
//
//
	  

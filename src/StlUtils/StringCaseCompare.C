//
// File:        StringCaseCompare.C
// Project:	StlUtils (%PP%)
// Item:   	%PI% (%PF%)
// Desc:        
//
//  StringCaseCompare( const char * one, const char * two );
//	Compare two strings ignoring case. return 0 if one == two,
//	< 0 if one < two and > 0 if one > two.
//
//  StringCaseCompare( const char * one, const char * two, size_t len );
//	Compare the first 'len' chars of two strings ignoring case.
//	return 0 if one == two, < 0 if one < two and > 0 if one > two.
//	
//  StringCaseCompare( const char * one, size_t lenOne,
//  		       const char * two, size_t lenTwo );
//      Compare the two strings ignoring case. The first
//      min( lenOne, lenTwo) char are check first if they are
//      not the same, the difference is return. If they are the
//      same, the differance of lenOne and lenTwo is returnd.
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/01/95 07:07 
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    %PO%
//  Last Mod:	    %PRT%
//  Version:	    %PIV%
//  Status: 	    %PS%
//
// %PID%

#include "StringUtils.hh"
#include "Compare.hh"
#include <functional>
#include <algorithm>
#include <cstddef>
#include <cctype>

STLUTILS_FUNCT_VERSION(
  StringCaseCompare,
  "%PID%" );


int
StringCaseCompare( const char * one, const char * two )
{
  register int diff;
  register const char * s1 = one;
  register const char * s2 = two;
  
  for( ; !( (diff = tolower( *s1 ) - tolower( *s2 ) ) ) ; s1++, s2++ )
    {
      if( !(*s1) )
	{
	  break;
	}
    }
  return( diff );
      
}

int
StringCaseCompare( const char * one, const char * two, size_t len )
{
  register int diff = 0;
  register size_t maxChars = len;
  register const char * s1 = one;
  register const char * s2 = two;
  
  for( ; maxChars && !( (diff = tolower( *s1 ) - tolower( *s2 ) ) ) ;
	 s1++, s2++, maxChars-- )
    {
      if( !(*s1) )
	{
	  break;
	}
    }
  return( diff );
  ;
}

int
StringCaseCompare(
  const char * one,
  size_t lenOne,
  const char * two,
  size_t lenTwo
  )
{
  int diff = StringCaseCompare( one, two, min( lenOne, lenTwo ) );
  return( diff ? diff : compare( lenOne, lenTwo ) );
}

//
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 5.2  2001/07/26 19:28:58  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:17  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:00  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:08:50  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1996/11/24 19:05:16  houghton
// Removed support for short filenames.
//
// Revision 3.1  1996/11/14 01:24:16  houghton
// Changed to Release 3
//
// Revision 2.3  1996/11/04 14:29:55  houghton
// Restructure header comments layout.
//
// Revision 2.2  1995/12/04 11:18:29  houghton
// Bug Fix - Can now compile with out '-DSTLUTILS_DEBUG'.
//
// Revision 2.1  1995/11/10  12:41:09  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:47  houghton
// Ports and Version ID changes
//
//

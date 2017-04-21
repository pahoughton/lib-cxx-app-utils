// 1995-05-01 (cc) <paul4hough@gmail.com>

#include "StringUtils.hpp"
#include "compare"
#include <functional>
#include <algorithm>
#include <cstddef>
#include <cctype>

namespace clue {

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
  int diff = StringCaseCompare( one, two, std::min( lenOne, lenTwo ) );
  return( diff ? diff : compare( lenOne, lenTwo ) );
}
}
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

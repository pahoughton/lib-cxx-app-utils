//
// File:        tCharIsBaseDigit.C
// Project:	StlUtils
// Desc:        
//
//  Test for CharIsBaseDigit function.
//  
// Source Header Version: StringUtils.hh 2.4
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/30/96 04:23
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StringUtils.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StrUtil.hh>
#endif

bool
tCharIsBaseDigit( LibTest & tester )
{
  {
    // IsBaseDigit( char, unsigned short)

    for( unsigned short base = 2; base < 36; base++ )
      {
	{
	  for( char num = ('0' - 2 ); num <= '9'; num++ )
	    {
	      bool result = CharIsBaseDigit( num, base );
	      
	      TEST( ( result == true && num >= '0' && (num - '0') < base ) ||
		    ( result == false && ( num < '0' || (num - '0') >= base ) ) );
	    }
	}

	{
	  for( char num = ('a' - 2 ); num <= 'z'; num++ )
	    {
	      bool result = CharIsBaseDigit( num, base );
	      
	      TEST( ( result == true && ( base > 10 &&
					  (10 + (num - 'a')) >= 10 &&
					  (10 + (num - 'a')) < base ) ) ||
		    ( result == false && ( base < 10 ||
					   (10 + (num - 'a')) < 10 ||
					   (10 + (num - 'a')) >= base ) ) );
	    }
	}

	{
	  for( char num = ('A' - 2 ); num <= 'Z'; num++ )
	    {
	      bool result = CharIsBaseDigit( num, base );
	      
	      TEST( ( result == true && ( base > 10 &&
					  (10 + (num - 'A')) >= 10 &&
					  (10 + (num - 'A')) < base ) ) ||
		    ( result == false && ( base < 10 ||
					   (10 + (num - 'A')) < 10 ||
					   (10 + (num - 'A')) >= base ) ) );
	    }
	}
		    
      }
  }

  return( true );
}

//
// Revision Log:
//
// $Log$
// Revision 6.1  2003/08/09 11:22:50  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:27  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:05  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:09:38  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:26:24  houghton
// Changed to Release 3
//
// Revision 2.1  1996/11/04 14:46:20  houghton
// Initial Version.
//
//

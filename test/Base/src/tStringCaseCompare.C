//
// File:        tStringCaseCompare.C
// Project:     StlUtils
// Desc:        
//
//  Test StringCaseCompare functions.
//  
// Source Header Version: StringUtils.hh 2.4
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/29/96 06:54
//
// Revision History: (See end of file for Revision Log)
//
// $Id$
//

#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StringUtils.hh>
#include <cstdio>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StrUtil.hh>
#include <cstdio>
#endif

struct TestVal
{
  const char * 	sone;
  size_t    	lone;
  const char *  stwo;
  size_t    	ltwo;
  int	    	useLen;
  int	    	diff;
};

static struct TestVal TestValues[] =
{
  { "STRING", 0,    	    "string", 0, 0, 0 },
  { "this string", 0,	    "THISSTRING ", 0, 0, -1 },
  { "another", 0,    	    "anoTHer", 0, 0, 0 },
  { "longer than most", 8,  "longer than", 7, 2, 1 },
  { "longer than most", 8,  "longer than", 8, 2, 0 },
  { "1234567890", 9,	    "1234567899", 0, 1, 0 },
  { "Case Doesn't Matter",0,"cASE dOESN't mATTER",0, 0, 0 },
  { "TestMENOW", 7, 	    "tESTMENZZ", 7, 2, 0 },
  { 0,0,0,0,0,0 }
};

bool
tStringCaseCompare( LibTest & tester )
{
  // StringCaseCompare( const char *, const char * )
  // StringCaseCompare( const char *, const char *, size_t )
  // StringCaseCompare( const char *, size_t, const char *, size_t )

  char reason[1024];
  
  for( int t = 0; TestValues[t].sone; t++ )
    {
      int result;
      
      switch( TestValues[t].useLen )
	{
	case 0:
	  result = StringCaseCompare( TestValues[t].sone,
				      TestValues[t].stwo );
	  break;

	case 1:
	  result = StringCaseCompare( TestValues[t].sone,
				      TestValues[t].stwo,
				      TestValues[t].lone );
	  break;

	case 2:
	  result = StringCaseCompare( TestValues[t].sone,
				      TestValues[t].lone,
				      TestValues[t].stwo,
				      TestValues[t].ltwo );
	  break;

	default:
	  return( false );
	}
      
      switch( TestValues[t].diff )
	{
	case -1:
	  if( result >= 0 )
	    {
	      sprintf( reason,
		       "%d Expected < 0 - "
		       "One: '%s' l: %d "
		       "Two: '%s' l: %d "
		       "UseLen: %d",
		       result,
		       TestValues[t].sone,
		       TestValues[t].lone,
		       TestValues[t].stwo,
		       TestValues[t].ltwo,
		       TestValues[t].useLen );
	      TESTR( reason, false );
	      return( false );
	    }
	  break;
		
	case 0:
	  if( result != 0 )
	    {
	      sprintf( reason,
		       "%d Expected < 0 - "
		       "One: '%s' l: %d "
		       "Two: '%s' l: %d "
		       "UseLen: %d",
		       result,
		       TestValues[t].sone,
		       TestValues[t].lone,
		       TestValues[t].stwo,
		       TestValues[t].ltwo,
		       TestValues[t].useLen );
	      TESTR( reason, false );
	      return( false );
	    }
	  break;
		
	case 1:
	  if( result <= 0 )
	    {
	      sprintf( reason,
		       "%d Expected < 0 - "
		       "One: '%s' l: %d "
		       "Two: '%s' l: %d "
		       "UseLen: %d",
		       result,
		       TestValues[t].sone,
		       TestValues[t].lone,
		       TestValues[t].stwo,
		       TestValues[t].ltwo,
		       TestValues[t].useLen );
	      TESTR( reason, false );
	      return( false );
	    }
	  break;
	}
    }
  return( true );
}
		
    
//
// $Log$
// Revision 6.1  2003/08/09 11:22:52  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:31  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:43  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:10:07  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:27:11  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:52:04  houghton
// Added header comments.
//
//

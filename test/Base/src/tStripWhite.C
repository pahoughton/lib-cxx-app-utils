//
// File:        tStripWhite.C
// Project:	StlUtils
// Desc:        
//
//  Test for StripWhite function
//
// Source Header Version: StringUtils.hh 2.4
//  
// Author:      Paul Houghton - (houghton@cmore.wiltel.com)
// Created:     10/29/96 05:04
//
// Revision History: (See end of file for Revision Log)
//
// $Id$

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

struct TestVals
{
  char      	from[ 100 ];
  char      	to[ 100 ];
  const char *  stripChars;
};

static TestVals TestValues[] =
{
  { { "no white in me" 	            }, { "no white in me"         }, 0 },
  { { "\t leading"  	    	    }, { "leading"  	    	  }, 0 },
  { { "\nnewlines\n"	    	    }, { "newlines" 	    	  }, 0 },
  { { "trailing \t\n\r   "  	    }, { "trailing"               }, 0 },
  { { "    both lead & trail    "   }, { "both lead & trail" 	  }, 0 },
  { { "---  special  ----"     	    }, { "  special  "	    	  }, "-" },
  { { "!,-()\nstuff  "	    	    }, { "\nstuff"                }, "(),-! " },
  { {0},{0},0 }
};

bool
tStripWhite( LibTest & tester )
{
  // StripWhite( char *, const char * )
  
  char * result;
  char reason[1024];
  
  for( int t = 0; TestValues[t].from[0]; t++ )
    {
      if( TestValues[t].stripChars )
	{
	  result = StripWhite( TestValues[t].from, TestValues[t].stripChars );
	}
      else
	{
	  result = StripWhite( TestValues[t].from );
	}

      if( result != TestValues[t].from ||
	  strcmp( TestValues[t].from, TestValues[t].to ) )
	{
	  sprintf( reason, "'%s' should be '%s'",
		   TestValues[t].from,
		   TestValues[t].to );
	  
	  TESTR( reason, false );
	  return( false );
	}
    }

  {
    // StripWhite( char *, const char *, size_t )
    
    static char SizeTest[50] = "   cleanup   this mess  ";

    result = StripWhite( SizeTest, " ", 11 );
    
    if( result != SizeTest || strcmp( SizeTest, "cleanup" ) )
      {
	sprintf( reason, "'%s' should be 'cleanup'", SizeTest );
	TESTR( reason, false );
	return( false );
      }
  }

  {
    // StripWhite( char *, const char *, size_t )

    // special test for bufSize of 0

#define TEST_STRING	"  abc  "
    static char src[32] = TEST_STRING;

    TEST( strcmp( StripWhite( src, " ", 0 ), TEST_STRING ) == 0 );
  }
    

  return( true );
}
  
//
// $Log$
// Revision 3.2  1997/09/17 11:10:11  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:27:14  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:53:42  houghton
// Added header comments.
// Added more test to verify function.
//
//

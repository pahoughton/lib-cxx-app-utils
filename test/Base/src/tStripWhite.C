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

#if defined( Hpux10 )

struct TestVals
{
  const char *  from;
  const char *  to; //     	to[ 100 ];
  const char *  stripChars;
};

#else

struct TestVals
{
  const char	from[ 100 ];
  const char	to[ 100 ];
  const char *  stripChars;
};

#endif
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
  char from[ 100 ];
  
  for( int t = 0; TestValues[t].from[0]; t++ )
    {
      strcpy( from, TestValues[t].from );
      
      if( TestValues[t].stripChars )
	{
	  result = StripWhite( from, TestValues[t].stripChars );
	}
      else
	{
	  result = StripWhite( from );
	}

      if( result != from ||
	  strcmp( from, TestValues[t].to ) )
	{
	  sprintf( reason, "'%s' should be '%s'",
		   from,
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
// Revision 4.5  1998/10/23 13:09:46  houghton
// Bug-Fix: check the first character of 'from'.
//
// Revision 4.4  1998/10/13 16:41:03  houghton
// Cleanup.
//
// Revision 4.3  1998/10/13 15:21:28  houghton
// Workaround for Hpux compiler.
//
// Revision 4.2  1998/07/20 11:33:40  houghton
// Port(Hpux): had to change test struct vars from char [] to char *.
//
// Revision 4.1  1997/09/17 15:14:47  houghton
// Changed to Version 4
//
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

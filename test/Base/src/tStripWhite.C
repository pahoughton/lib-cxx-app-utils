#if !defined( CLUE_SHORT_FN )
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

static char SizeTest[50] = "   cleanup this mess  ";

bool
tStripWhite( LibTest & tester )
{
  // StripWhite( char *, const char *, size_t )
  
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

  // special test for bufsize

  result = StripWhite( SizeTest, " ", 11 );
  
  if( result != SizeTest || strcmp( SizeTest, "cleanup" ) )
    {
      sprintf( reason, "'%s' should be 'cleanup'", SizeTest );
      TESTR( reason, false );
      return( false );
    }

  return( true );
}
  

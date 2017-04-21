// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/StringUtils.hpp>
#include <clue/compare>

#define VALID_VALIDATOR verify
#include <valid/verify>
#define TEST VVTRUE

#include <cstdio>

static valid::verify verify("clue::StripWhite");
using namespace clue;

struct TestVals
{
  const char	from[ 100 ];
  const char	to[ 100 ];
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
v_StripWhite( void )
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

	  VVFAIL( reason );
	}
    }

  {
    // StripWhite( char *, const char *, size_t )

    static char SizeTest[50] = "   cleanup   this mess  ";

    result = StripWhite( SizeTest, " ", 11 );

    if( result != SizeTest || strcmp( SizeTest, "cleanup" ) )
      {
	sprintf( reason, "'%s' should be 'cleanup'", SizeTest );
	VVFAIL( reason );
      }
  }

  {
    // StripWhite( char *, const char *, size_t )

    // special test for bufSize of 0

#define TEST_STRING	"  abc  "
    static char src[32] = TEST_STRING;

    TEST( strcmp( StripWhite( src, " ", 0 ), TEST_STRING ) == 0 );
  }

  return( verify.is_valid() );
}

#include <LibTest.hh>

#include <Clue.hh>

struct TestVals
{
  char      	from[ 100 ];
  char      	to[ 100 ];
  const char *  stripChars;
};

static TestVals TestValues[] =
{
  { { "no white in me" 	            }, { "no white in me"         }, 0 },
  { { "\t leading"  	    	    }, { "leading",  	    	  }, 0 },
  { { "\nnewlines\n"	    	    }, { "newlines" 	    	  }, 0 },
  { { "trailing \t\n\r   "  	    }, { "trailing"               }, 0 },
  { { "    both lead & trail    "   }, { "both lead & trail" 	  }, 0 },
  { { "---  special  ----"     	    }, { "  special  "	    	  }, "-" },
  { { "!,-()\nstuff  "	    	    }, { "\nstuff"                }, "(),-! " },
  { {0},{0},0 }
};

static char SizeTest[50] = "   cleanup this mess  ";

bool
tStripWhite( LibTest & test )
{
  // StripWhite( char *, const char *, size_t )
  
  char * result;
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
	  cerr << " Failed: '" << TestValues[t].from
	       << "' should be: " << TestValues[t].to << '\''
	       << endl;
	  test( false );
	  return( false );
	}
    }

  // special test for bufsize

  result = StripWhite( SizeTest, " ", 11 );
  
  if( result != SizeTest || strcmp( SizeTest, "cleanup" ) )
    {
      cerr << " Failed: '" << SizeTest
	   << "' should be: '" << "cleanup"  << '\''
	   << endl;
      test( false );
      return( false );
    }

  return( true );
}
  

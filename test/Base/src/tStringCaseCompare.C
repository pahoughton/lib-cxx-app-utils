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
		
    

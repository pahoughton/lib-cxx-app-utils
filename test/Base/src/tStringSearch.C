#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StringUtils.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StrUtil.hh>
#endif

#define HAY "this is the 123 haystack to search in 123 .,? aabbbcc 123"
//           012345678901234567890123456789012345678901234567890123456
//                     1         2         3         4         5

bool
tStringSearch( LibTest & tester )
{
  {
    // StringSearch( const char *, size_t, const char *, size_t )
    // StringReverseSearch( const char *, size_t, const char *, size_t )
    // StringCaseSearch( const char *, size_t, const char *, size_t )
    // StringCaseReverseSearch( const char *, size_t, const char *, size_t )

    const char * hay = HAY;
    TEST( (StringSearch( hay, 53, "123xx", 3 ) - hay) == 12 );
    TEST( (StringReverseSearch( hay, 53, "123xx", 3 ) - hay) == 38 );
    TEST( (StringReverseSearch( hay, 0, "123xx", 3 ) - hay) == 54 );
    TEST( (StringCaseSearch( hay, 53, "HayStackXXX", 8 ) - hay ) == 16 );
    TEST( (StringCaseReverseSearch( hay, 53, "IsXX", 2 ) - hay ) == 5 );
  }

  {
    const char * hay = "test,string,search,,function";
//                      012345678901234567890123456789
//                                1         2         
    const char * found = StringSearch( hay, strlen( hay ), ",", 1 );

    TEST( (found - hay) == 4 );

    found = StringSearch( found + 1, strlen( found + 1 ), ",", 1 );

    TEST( (found - hay) == 11 );

    found = StringSearch( found + 1, strlen( found + 1 ), ",", 1 );

    TEST( (found - hay) == 18 );

    found = StringSearch( found + 1, strlen( found + 1 ), ",", 1 );

    TEST( (found - hay) == 19 );

    found = StringSearch( found + 1, strlen( found + 1 ), ",", 1 );

    TEST( found == (const char *) 0 );
    
  }
  
	 
  return( true );
}


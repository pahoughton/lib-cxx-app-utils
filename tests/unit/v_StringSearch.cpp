// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/StringUtils.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify>
#define TEST VVTRUE

static valid::verify verify("clue::StringSearch");
using namespace clue;

#define HAY "this is the 123 haystack to search in 123 .,? aabbbcc 123"
//           012345678901234567890123456789012345678901234567890123456
//                     1         2         3         4         5

bool
v_StringSearch( void )
{
  {
    // StringSearch( const char *, size_t, const char *, size_t )

    const char * hay = HAY;
    TEST( (StringSearch( hay, 53, "123xx", 3 ) - hay) == 12 );
    TEST( (StringSearch( hay, NPOS, "123xx", 3 ) - hay) == 12 );
    TEST( (StringSearch( hay, NPOS, "123", NPOS ) - hay) == 12 );

    TEST( (StringSearch( hay, 13, "123", 3 )) == 0);
    TEST( (StringSearch( hay, 13, "123", NPOS )) == 0);
    TEST( (StringSearch( hay, NPOS, "1234", NPOS )) == 0 );

    // make sure case really matters

    TEST( (StringSearch( hay, NPOS, "haystack", NPOS ) - hay) == 16 );
    TEST( (StringSearch( hay, NPOS, "hayStack", NPOS )) == 0 );

  }

  {
    // Just verifing I can keep finding the next instance
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

  {
    // Bad args

    const char * hay = "this is the hay with the needle";
    const char * shortHay = "hay";
    const char * needle = "needle";

    size_t hayLen = strlen( hay );
    size_t needleLen = strlen( needle );

    TEST( StringSearch( 0, hayLen, needle, needleLen ) == 0 );
    TEST( StringSearch( hay, 0, needle, needleLen ) == 0 );
    TEST( StringSearch( hay, hayLen, 0, needleLen ) == 0 );
    TEST( StringSearch( hay, hayLen, needle, 0 ) == 0 );
    TEST( StringSearch( shortHay, NPOS, needle, NPOS ) == 0 );
    TEST( StringSearch( shortHay, strlen( shortHay ), needle, NPOS ) == 0 );
    TEST( StringSearch( shortHay, strlen( shortHay ),
			needle, needleLen ) == 0 );
    TEST( StringSearch( shortHay, NPOS,
			needle, needleLen ) == 0 );
    TEST( StringSearch( shortHay, NPOS,
			needle, NPOS ) == 0 );

  }

  {
    // StringReverseSearch( const char *, size_t, const char *, size_t )

    const char * hay = HAY;

    TEST( (StringReverseSearch( hay, 53, "123xx", 3 ) - hay) == 38 );
    TEST( (StringReverseSearch( hay, NPOS, "123xx", 3 ) - hay) == 54 );
    TEST( (StringReverseSearch( hay, NPOS, "123", NPOS ) - hay) == 54 );


    TEST( (StringReverseSearch( hay, 13, "123", 3 )) == 0 );
    TEST( (StringReverseSearch( hay, 13, "123", NPOS )) == 0 );
    TEST( (StringReverseSearch( hay, NPOS, "123x", NPOS )) == 0 );

    // make sure case really matters

    TEST( (StringReverseSearch( hay, NPOS, "haystack", NPOS ) - hay) == 16 );
    TEST( (StringReverseSearch( hay, NPOS, "hayStack", NPOS )) == 0 );

  }
  {
    // Bad args

    const char * hay = "this is the hay with the needle";
    const char * shortHay = "hay";
    const char * needle = "needle";

    size_t hayLen = strlen( hay );
    size_t needleLen = strlen( needle );

    TEST( StringReverseSearch( 0, hayLen, needle, needleLen ) == 0 );
    TEST( StringReverseSearch( hay, 0, needle, needleLen ) == 0 );
    TEST( StringReverseSearch( hay, hayLen, 0, needleLen ) == 0 );
    TEST( StringReverseSearch( hay, hayLen, needle, 0 ) == 0 );
    TEST( StringReverseSearch( shortHay, NPOS, needle, NPOS ) == 0 );
    TEST( StringReverseSearch( shortHay, strlen( shortHay ),
			       needle, NPOS ) == 0 );
    TEST( StringReverseSearch( shortHay, strlen( shortHay ),
			       needle, needleLen ) == 0 );
    TEST( StringReverseSearch( shortHay, NPOS,
			       needle, needleLen ) == 0 );
    TEST( StringReverseSearch( shortHay, NPOS,
			       needle, NPOS ) == 0 );

  }


  {
    // StringCaseSearch( const char *, size_t, const char *, size_t )

    const char * hay = HAY;

    TEST( (StringCaseSearch( hay, 53, "HayStackXXX", 8 ) - hay ) == 16 );
    TEST( (StringCaseSearch( hay, NPOS, "HayStackXXX", 8 ) - hay ) == 16 );
    TEST( (StringCaseSearch( hay, NPOS, "HayStack", NPOS ) - hay ) == 16 );

    TEST( (StringCaseSearch( hay, 15, "HayStackXXX", 8 )) == 0 );
    TEST( (StringCaseSearch( hay, 15, "HayStack", NPOS )) == 0 );
    TEST( (StringCaseSearch( hay, NPOS, "HayStackX", NPOS )) == 0 );
  }

  {
    // Bad args

    const char * hay = "this is the hay with the needle";
    const char * shortHay = "hay";
    const char * needle = "needle";

    size_t hayLen = strlen( hay );
    size_t needleLen = strlen( needle );

    TEST( StringCaseSearch( 0, hayLen, needle, needleLen ) == 0 );
    TEST( StringCaseSearch( hay, 0, needle, needleLen ) == 0 );
    TEST( StringCaseSearch( hay, hayLen, 0, needleLen ) == 0 );
    TEST( StringCaseSearch( hay, hayLen, needle, 0 ) == 0 );
    TEST( StringCaseSearch( shortHay, NPOS, needle, NPOS ) == 0 );
    TEST( StringCaseSearch( shortHay, strlen( shortHay ),
			    needle, NPOS ) == 0 );
    TEST( StringCaseSearch( shortHay, strlen( shortHay ),
			    needle, needleLen ) == 0 );
    TEST( StringCaseSearch( shortHay, NPOS,
			    needle, needleLen ) == 0 );
    TEST( StringCaseSearch( shortHay, NPOS,
			    needle, NPOS ) == 0 );

  }

  {
    // StringCaseReverseSearch( const char *, size_t, const char *, size_t )

    const char * hay = HAY;

    TEST( (StringCaseReverseSearch( hay, 53, "IsXX", 2 ) - hay ) == 5 );
    TEST( (StringCaseReverseSearch( hay, 5, "IsXX", 2 ) - hay ) == 2 );

    TEST( (StringCaseReverseSearch( hay, NPOS, "IsXX", 2 ) - hay ) == 5 );
    TEST( (StringCaseReverseSearch( hay, NPOS, "Is", NPOS ) - hay ) == 5 );

    TEST( (StringCaseReverseSearch( hay, 12, "HayStackXX", 8 )) == 0 );
    TEST( (StringCaseReverseSearch( hay, 12, "HayStack", NPOS )) == 0 );
    TEST( (StringCaseReverseSearch( hay, NPOS, "IsX", NPOS )) == 0 );

  }
    {
    // Bad args

    const char * hay = "this is the hay with the needle";
    const char * shortHay = "hay";
    const char * needle = "needle";

    size_t hayLen = strlen( hay );
    size_t needleLen = strlen( needle );

    TEST( StringCaseReverseSearch( 0, hayLen, needle, needleLen ) == 0 );
    TEST( StringCaseReverseSearch( hay, 0, needle, needleLen ) == 0 );
    TEST( StringCaseReverseSearch( hay, hayLen, 0, needleLen ) == 0 );
    TEST( StringCaseReverseSearch( hay, hayLen, needle, 0 ) == 0 );
    TEST( StringCaseReverseSearch( shortHay, NPOS, needle, NPOS ) == 0 );
    TEST( StringCaseReverseSearch( shortHay, strlen( shortHay ),
				   needle, NPOS ) == 0 );
    TEST( StringCaseReverseSearch( shortHay, strlen( shortHay ),
				   needle, needleLen ) == 0 );
    TEST( StringCaseReverseSearch( shortHay, NPOS,
				   needle, needleLen ) == 0 );
    TEST( StringCaseReverseSearch( shortHay, NPOS,
				   needle, NPOS ) == 0 );

  }

  return( verify.is_valid() );
}

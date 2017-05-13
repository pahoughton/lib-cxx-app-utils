// 1997-08-12 (cc) <paul4hough@gmail.com>

#include <clue/StringUtils.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::StringFirstNotOf");
using namespace clue;

#define HAY "this is the 123 haystack to search in 123 .,? aabbbcc 123"
//           012345678901234567890123456789012345678901234567890123456
//                     1         2         3         4         5

bool
v_StringFirstNotOf( void )
{
  {
    const char * hay = HAY;
    const char * needle = "this ";

    TEST( StringFirstNotOf( hay, NPOS, needle, NPOS ) == 10 );

    needle = "this e123ayckorn,.?b";

    TEST( StringFirstNotOf( hay, NPOS, needle, NPOS ) == NPOS );

    hay = "abcdefghijklmnop12345,.!@#-+=_";
//         012345678901234567890123456789012345678901234567890123456
//                   1         2         3         4         5
    needle = "abcdefghijklmnopqrstuvwxyz";
//            012345678901234567890123456789012345678901234567890123456
//                      1         2         3         4         5
    TEST( StringFirstNotOf( hay, 16, needle, NPOS ) == NPOS );
    TEST( StringFirstNotOf( hay, 17, needle, NPOS ) == 16 );

    hay = "abcdefghijklmnopqrstuvwxyz";

    TEST( StringFirstNotOf( hay, NPOS, needle, NPOS ) == NPOS );
    TEST( StringFirstNotOf( hay, NPOS, needle, 17 ) == 17 );


  }
  return( verify.is_valid() );
}

// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/StringUtils.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>

static valid::verify verify("clue::StringCapitalize");
using namespace clue;

bool
v_StringCapitalize( void )
{
  {
    // StringCapialize( char * )

    const char * sc =   "This-Is.A Test 12a34 Abc123 -Abc- Abc-Def? Good?";

    char su[] = "THIS-IS.A TEST 12A34 ABC123 -ABC- ABC-DEF? GOOD?";
    char sm[] = "thIS-IS.a tesT 12a34 abc123 -Abc- abc-def? GOod?";
    char sl[] = "this-is.a test 12a34 abc123 -abc- abc-def? good?";

    StringCapitalize( su );
    StringCapitalize( sm );
    StringCapitalize( sl );

    VVTRUE( strcmp( su, sc ) == 0 );
    VVTRUE( strcmp( sm, sc ) == 0 );
    VVTRUE( strcmp( sl, sc ) == 0 );

  }

  {
    // StringCapialize( char *, size_t )

    const char * sc =   "This-Is.A test 12a34 abc123 -abc- abc-def? good?";
    //                  0123456789 1
    char su[] = "THIS-IS.A test 12a34 abc123 -abc- abc-def? good?";
    char sm[] = "thIS-Is.a test 12a34 abc123 -abc- abc-def? good?";
    char sl[] = "this-is.a test 12a34 abc123 -abc- abc-def? good?";

    StringCapitalize( su, 10 );
    StringCapitalize( sm, 10 );
    StringCapitalize( sl, 10 );

    VVTRUE( strcmp( su, sc ) == 0 );
    VVTRUE( strcmp( sm, sc ) == 0 );
    VVTRUE( strcmp( sl, sc ) == 0 );

  }

  return( verify.is_valid() );
}

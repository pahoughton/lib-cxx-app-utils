// 1997-12-20 (cc) <paul4hough@gmail.com>

#include <clue/StringUtils.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify>
#define TEST VVTRUE

static valid::verify verify("clue::StripTrailing");
using namespace clue;

bool
v_StripTrailing( void )
{
  {
    char t[ 1024 ];

    const char * exp = "this is a test";

    strcpy( t, exp );

    StripTrailing( t );
    TEST( strcmp( t, exp ) == 0 );

    strcpy( t, exp );
    strcat( t, "\t\t  " );

    StripTrailing( t );
    TEST( strcmp( t, exp ) == 0 );

    strcpy( t, "\t\t  \t\t" );

    StripTrailing( t );
    TEST( t[0] == 0 );
  }

  return( verify.is_valid() );
}

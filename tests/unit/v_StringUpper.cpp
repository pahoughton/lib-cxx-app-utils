// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/StringUtils.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::StringUpper");
using namespace clue;

bool
v_StringUpper( void )
{
  {
    const char su[] = "THIS IS A 1234567890-=!@#$%^&*()_+[]{};':\",./<>? TEST";

    char sul[] = "THIS IS A 1234567890-=!@#$%^&*()_+[]{};':\",./<>? TEST";
    char sml[] = "tHIS is A 1234567890-=!@#$%^&*()_+[]{};':\",./<>? teST";
    char sll[] = "this is a 1234567890-=!@#$%^&*()_+[]{};':\",./<>? test";

    StringUpper( sul );
    StringUpper( sml );
    StringUpper( sll );

    TEST( strcmp( sul, su ) == 0 );
    TEST( strcmp( sml, su ) == 0 );
    TEST( strcmp( sll, su ) == 0 );
  }

  {
    const char su[] = "THIS IS AsiZE 12345-=!@#$%^&*()_+[]{};':\",./<>? teST";
    //                01234567890

    char suu[] = "THIS IS AsiZE 12345-=!@#$%^&*()_+[]{};':\",./<>? teST";
    char smu[] = "thIS IS AsiZE 12345-=!@#$%^&*()_+[]{};':\",./<>? teST";
    char slu[] = "this is asiZE 12345-=!@#$%^&*()_+[]{};':\",./<>? teST";

    StringUpper( slu, 9 );
    StringUpper( smu, 9 );
    StringUpper( suu, 9 );

    TEST( strcmp( slu, su ) == 0 );
    TEST( strcmp( smu, su ) == 0 );
    TEST( strcmp( suu, su ) == 0 );
  }

  return( verify.is_valid() );
}

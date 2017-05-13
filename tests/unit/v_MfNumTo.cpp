// 1997-12-15 (cc) <paul4hough@gmail.com>

#include <clue/StringUtils.hpp>
#include <cstring>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::AbsLong");
using namespace clue;

bool
v_MfNumTo( void )
{
  char  dest[20];

  memset( dest, 'x', 19 );

  TEST( MfNumTo( dest, 10, 1, "1234567L", 8 ) );

  dest[19] = 0;

  TEST( strcmp( dest, "-1234567.3xxxxxxxxx" ) == 0 );


  memset( dest, 'x', 19 );

  TEST( MfNumTo( dest, 10, 3, "    ", 4 ) );

  dest[19] = 0;

  TEST( strcmp( dest, "000000.000xxxxxxxxx" ) == 0 );


  memset( dest, 'x', 19 );

  TEST( MfNumTo( dest, 10, 0, "1234", 4 ) );

  dest[19] = 0;

  TEST( strcmp( dest, "0000001234xxxxxxxxx" ) == 0 );


  memset( dest, 'x', 19 );

  TEST( MfNumTo( dest, 10, 4, "1234", 4 ) );

  dest[19] = 0;

  TEST( strcmp( dest, "00000.1234xxxxxxxxx" ) == 0 );

  // cout << "\n'" << dest << '\'' << endl;
  return( verify.is_valid() );
}

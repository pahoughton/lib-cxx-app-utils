// 1996-10-30 (cc) <paul4hough@gmail.com>

#include <clue/StringUtils.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <algorithm>
#include <cstring>

static valid::verify verify("clue::SafeStrcpy");
using namespace clue;

bool
v_SafeStrcpy( void )
{

  // SafeStrcpy( char *, const char *, size_t )
  char  b[ 15 ];
  char  tBuffer[ 128 ];

  memset( tBuffer, '*', sizeof( tBuffer ) );

  SafeStrcpy( tBuffer, "short", sizeof( b ) );

  TEST( ! strcmp( tBuffer, "short" ) );
  TEST( tBuffer[ 14 ] == 0 );
  TEST( tBuffer[ 15 ] == '*' );

  memset( tBuffer, '*', sizeof( tBuffer ) );

  SafeStrcpy( tBuffer, "123456789 123456789", sizeof( b ) );

  TEST( ! strcmp( tBuffer, "123456789 1234" ) );
  TEST( tBuffer[ 14 ] == 0 );
  TEST( tBuffer[ 15 ] == '*' );

  memset( tBuffer, '*', sizeof( tBuffer ) );

  SafeStrcpy( tBuffer, "short", std::min( strlen( "short" ) + 1, sizeof( b ) ) );

  TEST( ! strcmp( tBuffer, "short" ) );
  TEST( tBuffer[ 5 ] == 0 );
  TEST( tBuffer[ 6 ] == '*' );

  return( verify.is_valid() );
}

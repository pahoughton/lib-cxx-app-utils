#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StringUtils.hh>
#include <algorithm>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StrUtil.hh>
#include <algorithm>
#endif


bool
tSafeStrcpy( LibTest & tester )
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
  
  SafeStrcpy( tBuffer, "short", min( strlen( "short" ) + 1, sizeof( b ) ) );

  TEST( ! strcmp( tBuffer, "short" ) );
  TEST( tBuffer[ 5 ] == 0 );
  TEST( tBuffer[ 6 ] == '*' );

  return( true );
}


#include <LibTest.hh>
#include <StringUtils.hh>

#include <algorithm>

bool
tSafeStrcpy( LibTest & test )
{

  // SafeStrcpy( char *, const char *, size_t )
  
  char  b[ 15 ];
  
  char  tBuffer[ 128 ];

  memset( tBuffer, '*', sizeof( tBuffer ) );
  
  SafeStrcpy( tBuffer, "short", sizeof( b ) );

  test( ! strcmp( tBuffer, "short" ) );
  test( tBuffer[ 14 ] == 0 );
  test( tBuffer[ 15 ] == '*' );

  memset( tBuffer, '*', sizeof( tBuffer ) );
  
  SafeStrcpy( tBuffer, "123456789 123456789", sizeof( b ) );

  test( ! strcmp( tBuffer, "123456789 1234" ) );
  test( tBuffer[ 14 ] == 0 );
  test( tBuffer[ 15 ] == '*' );
  
  memset( tBuffer, '*', sizeof( tBuffer ) );
  
  SafeStrcpy( tBuffer, "short", min( strlen( "short" ) + 1, sizeof( b ) ) );

  test( ! strcmp( tBuffer, "short" ) );
  test( tBuffer[ 5 ] == 0 );
  test( tBuffer[ 6 ] == '*' );

  return( true );
}

#include <LibTest.hh>

bool tParam01( LibTest & test );

bool
tParam( LibTest & test )
{
  test( tParam01( test ), true );

  return( true );
}

#include <LibTest.hh>

bool tDirectory01( LibTest & test );

bool
tDirectory( LibTest & test )
{
  test( tDirectory01( test ), true );

  return( true );
}

#include <LibTest.hh>

bool tDirectory01( LibTest & tester );

bool
tDirectory( LibTest & tester )
{
  TESTP( tDirectory01( tester ) );

  return( true );
}

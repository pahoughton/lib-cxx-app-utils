#include <LibTest.hh>
#include <Bitmask.hh>

bool tBitmask01( LibTest & tester );
bool tBitmask02( LibTest & tester );
bool tBitmask03( LibTest & tester );

bool
tBitmask( LibTest & test )
{
  test( tBitmask01( test ), true );
  test( tBitmask02( test ), true );
  test( tBitmask03( test ), true );
   
  return( true );
}

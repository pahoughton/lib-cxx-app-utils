#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#endif

bool tBitmask01( LibTest & tester );
bool tBitmask02( LibTest & tester );
bool tBitmask03( LibTest & tester );

bool
tBitmask( LibTest & tester )
{
  TESTP( tBitmask01( tester ), true );
  TESTP( tBitmask02( tester ), true );
  TESTP( tBitmask03( tester ), true );
   
  return( true );
}

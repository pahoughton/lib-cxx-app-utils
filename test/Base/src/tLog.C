#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#else
#include <TestCfg.hh>
#include <LibTest.hh>
#endif

bool tLogLevel( LibTest & tester );
bool tLog01( LibTest & tester );
bool tLog02( LibTest & tester );
bool tLog03( LibTest & tester );
bool tLog04( LibTest & tester );
bool tLog05( LibTest & tester );


bool
tLog( LibTest & tester )
{
  TESTP( tLogLevel( tester ) );
  TESTP( tLog01( tester ) );
  TESTP( tLog02( tester ) );
  TESTP( tLog03( tester ) );
  TESTP( tLog04( tester ) );
  TESTP( tLog05( tester ) );

  return( true );
}

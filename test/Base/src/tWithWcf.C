#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#else
#include <TestCfg.hh>
#include <LibTest.hh>
#endif

bool tWithWcf01( LibTest & tester );
bool tWithWcf02( LibTest & tester );

bool
tWithWcf( LibTest & tester )
{
  TESTP( tWithWcf01( tester ), true );
  TESTP( tWithWcf02( tester ), true );
  return( true );
}

    

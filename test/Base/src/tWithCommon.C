#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#else
#include <TestCfg.hh>
#include <LibTest.hh>
#endif

bool tWithCommon01( LibTest & tester );
bool tWithCommon02( LibTest & tester );

bool
tWithCommon( LibTest & tester )
{
  TESTP( tWithCommon01( tester ), true );
  TESTP( tWithCommon02( tester ), true );
  return( true );
}

    

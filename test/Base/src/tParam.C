#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#else
#include <TestCfg.hh>
#include <LibTest.hh>
#endif

bool tParam01( LibTest & test );

bool
tParam( LibTest & tester )
{
  TESTP( tParam01( tester ) );

  return( true );
}

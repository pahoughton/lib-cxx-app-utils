#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#else
#include <TestCfg.hh>
#include <LibTest.hh>
#endif

bool tFileStat01( LibTest & tester );
bool tFileStat02( LibTest & tester );
bool tFileStat03( LibTest & tester );
bool tFileStat04( LibTest & tester );
bool tFileStat05( LibTest & tester );
bool tFileStat06( LibTest & tester );

bool
tFileStat( LibTest & tester )
{
  TESTP( tFileStat01( tester ), true  );
  TESTP( tFileStat02( tester ), true  );
  TESTP( tFileStat03( tester ), true  );
  TESTP( tFileStat04( tester ), true  );
  TESTP( tFileStat05( tester ), true  );
  TESTP( tFileStat06( tester ), true  );

  return( true );
}

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
  TESTP( tFileStat01( tester ));
  TESTP( tFileStat02( tester ));
  TESTP( tFileStat03( tester ));
  TESTP( tFileStat04( tester ));
  TESTP( tFileStat05( tester ));
  TESTP( tFileStat06( tester ));

  return( true );
}

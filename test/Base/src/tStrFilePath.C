#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#endif

bool tFilePath01( LibTest & tester );
bool tFilePath02( LibTest & tester );
bool tFilePath03( LibTest & tester );
bool tFilePath04( LibTest & tester );

bool
tFilePath( LibTest & tester )
{
  TESTP( tFilePath01( tester ), true );
  TESTP( tFilePath02( tester ), true );
  TESTP( tFilePath03( tester ), true );
  TESTP( tFilePath04( tester ), true );

  return( true );
}

    

#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#endif

bool tSubStr01( LibTest & tester );
bool tSubStr02( LibTest & tester );
bool tSubStr03( LibTest & tester );
bool tSubStr04( LibTest & tester );
bool tSubStr05( LibTest & tester );
bool tSubStr06( LibTest & tester );
bool tSubStr07( LibTest & tester );

bool
tSubStr( LibTest & tester )
{
  TESTP( tSubStr01( tester ), true );
  TESTP( tSubStr02( tester ), true );
  TESTP( tSubStr03( tester ), true );
  TESTP( tSubStr04( tester ), true );
  TESTP( tSubStr05( tester ), true );
  TESTP( tSubStr06( tester ), true );
  TESTP( tSubStr07( tester ), true );

  return( true );
}

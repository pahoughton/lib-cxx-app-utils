#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
#endif

bool
tAbsLong( LibTest & tester )
{
  {
    long  t = -12341234L;
    
    TEST( abs( t ) == 12341234L );

    t = 43214321L;
    
    TEST( abs( t ) == 43214321L );
  }

  return( true );
}


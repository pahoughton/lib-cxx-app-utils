#include <LibTest.hh>
#include <Clue.hh>

bool
tAbsLong( LibTest & test )
{
  {
    long  t = -12341234;
    
    test( abs( t ) == 12341234 );

    t = 43214321;
    
    test( abs( t ) == 43214321 );
  }

  return( true );
}


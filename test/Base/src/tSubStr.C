#include <LibTest.hh>

bool tSubStr01( LibTest & tester );
bool tSubStr02( LibTest & tester );
bool tSubStr03( LibTest & tester );
bool tSubStr04( LibTest & tester );
bool tSubStr05( LibTest & tester );
bool tSubStr06( LibTest & tester );
bool tSubStr07( LibTest & tester );

bool
tSubStr( LibTest & test )
{
  test( tSubStr01( test ), true );
  test( tSubStr02( test ), true );
  test( tSubStr03( test ), true );
  test( tSubStr04( test ), true );
  test( tSubStr05( test ), true );
  test( tSubStr06( test ), true );
  test( tSubStr07( test ), true );

  return( true );
}

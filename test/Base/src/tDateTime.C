#include <LibTest.hh>

#include <DateTime.hh>
#include <stdlib.h>

bool tDateTime01( LibTest & tester );
bool tDateTime02( LibTest & tester );
bool tDateTime03( LibTest & tester );
bool tDateTime04( LibTest & tester );
bool tDateTime05( LibTest & tester );
bool tDateTime06( LibTest & tester );
bool tDateTime07( LibTest & tester );
bool tDateTime08( LibTest & tester );

bool
tDateTime( LibTest & test )
{
  
  putenv( "TZ=CST6CDT" );

  test( tDateTime01( test ), true );
  test( tDateTime02( test ), true );
  test( tDateTime03( test ), true ); 
  test( tDateTime04( test ), true ); 
  test( tDateTime05( test ), true ); 
  test( tDateTime06( test ), true ); 
  test( tDateTime07( test ), true ); 
  test( tDateTime08( test ), true ); 
 
  return( true );
  
}

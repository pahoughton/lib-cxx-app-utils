
#include <LibTest.hh>

bool tLogLevel( LibTest & test );
bool tLog01( LibTest & test );
bool tLog02( LibTest & test );
bool tLog03( LibTest & test );
bool tLog04( LibTest & test );
bool tLog05( LibTest & test );


bool
tLog( LibTest & test )
{
  test( tLogLevel( test ), true );
  test( tLog01( test ), true );
  test( tLog02( test ), true );
  test( tLog03( test ), true );
  test( tLog04( test ), true );
  test( tLog05( test ), true );

  return( true );
}

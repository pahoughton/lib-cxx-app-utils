#include <LibTest.hh>

bool tFileStat01( LibTest & test );
bool tFileStat02( LibTest & test );
bool tFileStat03( LibTest & test );
bool tFileStat04( LibTest & test );
bool tFileStat05( LibTest & test );
bool tFileStat06( LibTest & test );

bool
tFileStat( LibTest & test )
{
  test( tFileStat01( test ), true  );
  test( tFileStat02( test ), true  );
  test( tFileStat03( test ), true  );
  test( tFileStat04( test ), true  );
  test( tFileStat05( test ), true  );
  test( tFileStat06( test ), true  );

  return( true );
}

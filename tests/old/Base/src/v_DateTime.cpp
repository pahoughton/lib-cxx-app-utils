#include <TestConfig.hh>
#include <LibTest.hh>
#include <DateTime.hh>
#include <cstdlib>
#include <cstdio>


bool tDateTime01( LibTest & tester );
bool tDateTime02( LibTest & tester );
bool tDateTime03( LibTest & tester );
bool tDateTime04( LibTest & tester );
bool tDateTime05( LibTest & tester );
bool tDateTime06( LibTest & tester );
bool tDateTime07( LibTest & tester );
bool tDateTime08( LibTest & tester );

bool
tDateTime( LibTest & tester )
{
  const char * oldTZ = getenv( "TZ" );
  
  putenv( (char *)"TZ=CST6CDT" );

  TESTP( tDateTime01( tester ) );
  TESTP( tDateTime02( tester ) );
  TESTP( tDateTime03( tester ) ); 
  TESTP( tDateTime04( tester ) ); 
  TESTP( tDateTime05( tester ) ); 
  TESTP( tDateTime06( tester ) ); 
  TESTP( tDateTime07( tester ) ); 
  TESTP( tDateTime08( tester ) ); 

  if( oldTZ )
    {
      char tzBuf[128];
      
      sprintf( tzBuf, "TZ=%s", oldTZ );
      
      putenv( tzBuf );
      
      DateTime t;
      t.setTimeZone( oldTZ );
    }
  
  return( true );
  
}

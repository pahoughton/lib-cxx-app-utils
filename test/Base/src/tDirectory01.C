#include <LibTest.hh>
#include <Directory.hh>

bool
tDirectory01( LibTest & test )
{
  {
    Directory  t( "/one/two/th*/four" );

    t.set( "abc" );
    t.set( "one/two" );
    t.set( "one/two" );
    
  }

  return( true );
}

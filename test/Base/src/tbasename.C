#include <LibTest.hh>
#include <StringUtils.hh>
#include <Compare.hh>

bool
tbasename( LibTest & test )
{
  {
    // basename( const char * fn )

    const char * t;

    t = "/this/is/a/test";
    test( compare( basename( t ) , "test" ) == 0 );

    t = "another/test.try";
    test( compare( basename( t ) , "test.try" ) == 0 );

    t = "one.more";
    test( compare( basename( t ) , "one.more" ) == 0 );
  }
  
  {
    // basename( char * fn )

    char t[100];

    strcpy( t, "/this/is/a/test");
    test( compare( basename( t ) , "test" ) == 0 );

    strcpy( t, "another/test.try");
    test( compare( basename( t ) , "test.try" ) == 0 );

    strcpy( t, "one.more");
    test( compare( basename( t ) , "one.more" ) == 0 );
  }

  return( true );
}

    
      

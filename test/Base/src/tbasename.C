#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StringUtils.hh>
#include <Compare.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <StrUtil.hh>
#include <Compare.hh>
#endif

bool
tbasename( LibTest & tester )
{
  {
    // basename( const char * fn )

    const char * t;

    t = "/this/is/a/test";
    TEST( compare( basename( t ) , "test" ) == 0 );

    t = "another/test.try";
    TEST( compare( basename( t ) , "test.try" ) == 0 );

    t = "one.more";
    TEST( compare( basename( t ) , "one.more" ) == 0 );
  }
  
  {
    // basename( char * fn )

    char t[100];

    strcpy( t, "/this/is/a/test");
    TEST( compare( basename( t ) , "test" ) == 0 );

    strcpy( t, "another/test.try");
    TEST( compare( basename( t ) , "test.try" ) == 0 );

    strcpy( t, "one.more");
    TEST( compare( basename( t ) , "one.more" ) == 0 );
  }

  return( true );
}

    
      

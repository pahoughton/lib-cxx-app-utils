#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Compare.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Compare.hh>
#endif

bool
tCompare01( LibTest & tester )
{
  {
    // compare( number, number )
    
    TEST( compare( -15, -25 ) > 0 );
    TEST( compare( -15, -15 ) == 0 );
    TEST( compare( -15,  -5 ) < 0 );
    TEST( compare( -15,   0 ) < 0 );
    TEST( compare( -15,   5 ) < 0 );
    TEST( compare( -15,  15 ) < 0 );
    TEST( compare( -15,  25 ) < 0 );
    
    TEST( compare(   0, -25 ) > 0 );
    TEST( compare(   0, -15 ) > 0 );
    TEST( compare(   0,  -5 ) > 0 );
    TEST( compare(   0,   0 ) == 0 );
    TEST( compare(   0,   5 ) < 0 );
    TEST( compare(   0,  15 ) < 0 );
    TEST( compare(   0,  25 ) < 0 );

    TEST( compare(  15, -25 ) > 0 );
    TEST( compare(  15, -15 ) > 0 );
    TEST( compare(  15,  -5 ) > 0 );
    TEST( compare(  15,   0 ) > 0 );
    TEST( compare(  15,   5 ) > 0 );
    TEST( compare(  15,  15 ) == 0 );
    TEST( compare(  15,  25 ) < 0 );

    
    TEST( compare( -15.5, -25.5 ) > 0 );
    TEST( compare( -15.5, -15.5 ) == 0 );
    TEST( compare( -15.5,  -5.5 ) < 0 );
    TEST( compare( -15.5,   0.5 ) < 0 );
    TEST( compare( -15.5,   5.5 ) < 0 );
    TEST( compare( -15.5,  15.5 ) < 0 );
    TEST( compare( -15.5,  25.5 ) < 0 );
    
    TEST( compare(   0.5, -25.5 ) > 0 );
    TEST( compare(   0.5, -15.5 ) > 0 );
    TEST( compare(   0.5,  -5.5 ) > 0 );
    TEST( compare(   0.5,   0.5 ) == 0 );
    TEST( compare(   0.5,   5.5 ) < 0 );
    TEST( compare(   0.5,  15.5 ) < 0 );
    TEST( compare(   0.5,  25.5 ) < 0 );

    TEST( compare(  15.5, -25.5 ) > 0 );
    TEST( compare(  15.5, -15.5 ) > 0 );
    TEST( compare(  15.5,  -5.5 ) > 0 );
    TEST( compare(  15.5,   0.5 ) > 0 );
    TEST( compare(  15.5,   5.5 ) > 0 );
    TEST( compare(  15.5,  15.5 ) == 0 );
    TEST( compare(  15.5,  25.5 ) < 0 );

  }

  return( true );
}

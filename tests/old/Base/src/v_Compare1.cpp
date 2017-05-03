
#include <LibTest.hh>
#include <Compare.hh>

bool
tCompare1( LibTest & test )
{
  {
    // compare( number, number )
    
    test( compare( -15, -25 ) > 0 );
    test( compare( -15, -15 ) == 0 );
    test( compare( -15,  -5 ) < 0 );
    test( compare( -15,   0 ) < 0 );
    test( compare( -15,   5 ) < 0 );
    test( compare( -15,  15 ) < 0 );
    test( compare( -15,  25 ) < 0 );
    
    test( compare(   0, -25 ) > 0 );
    test( compare(   0, -15 ) > 0 );
    test( compare(   0,  -5 ) > 0 );
    test( compare(   0,   0 ) == 0 );
    test( compare(   0,   5 ) < 0 );
    test( compare(   0,  15 ) < 0 );
    test( compare(   0,  25 ) < 0 );

    test( compare(  15, -25 ) > 0 );
    test( compare(  15, -15 ) > 0 );
    test( compare(  15,  -5 ) > 0 );
    test( compare(  15,   0 ) > 0 );
    test( compare(  15,   5 ) > 0 );
    test( compare(  15,  15 ) == 0 );
    test( compare(  15,  25 ) < 0 );

    
    test( compare( -15.5, -25.5 ) > 0 );
    test( compare( -15.5, -15.5 ) == 0 );
    test( compare( -15.5,  -5.5 ) < 0 );
    test( compare( -15.5,   0.5 ) < 0 );
    test( compare( -15.5,   5.5 ) < 0 );
    test( compare( -15.5,  15.5 ) < 0 );
    test( compare( -15.5,  25.5 ) < 0 );
    
    test( compare(   0.5, -25.5 ) > 0 );
    test( compare(   0.5, -15.5 ) > 0 );
    test( compare(   0.5,  -5.5 ) > 0 );
    test( compare(   0.5,   0.5 ) == 0 );
    test( compare(   0.5,   5.5 ) < 0 );
    test( compare(   0.5,  15.5 ) < 0 );
    test( compare(   0.5,  25.5 ) < 0 );

    test( compare(  15.5, -25.5 ) > 0 );
    test( compare(  15.5, -15.5 ) > 0 );
    test( compare(  15.5,  -5.5 ) > 0 );
    test( compare(  15.5,   0.5 ) > 0 );
    test( compare(  15.5,   5.5 ) > 0 );
    test( compare(  15.5,  15.5 ) == 0 );
    test( compare(  15.5,  25.5 ) < 0 );

  }

  return( true );
}

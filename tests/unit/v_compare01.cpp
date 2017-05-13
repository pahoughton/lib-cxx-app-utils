// 1996-10-27 (cc) <paul4hough@gmail.com>

#include <clue/compare>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>

static valid::verify verify("clue::compare01");

bool
v_compare01( void )
{
  {
    // clue::compare( number, number )

    VVTRUE( clue::compare( -15, -25 ) > 0 );
    VVTRUE( clue::compare( -15, -15 ) == 0 );
    VVTRUE( clue::compare( -15,  -5 ) < 0 );
    VVTRUE( clue::compare( -15,   0 ) < 0 );
    VVTRUE( clue::compare( -15,   5 ) < 0 );
    VVTRUE( clue::compare( -15,  15 ) < 0 );
    VVTRUE( clue::compare( -15,  25 ) < 0 );

    VVTRUE( clue::compare(   0, -25 ) > 0 );
    VVTRUE( clue::compare(   0, -15 ) > 0 );
    VVTRUE( clue::compare(   0,  -5 ) > 0 );
    VVTRUE( clue::compare(   0,   0 ) == 0 );
    VVTRUE( clue::compare(   0,   5 ) < 0 );
    VVTRUE( clue::compare(   0,  15 ) < 0 );
    VVTRUE( clue::compare(   0,  25 ) < 0 );

    VVTRUE( clue::compare(  15, -25 ) > 0 );
    VVTRUE( clue::compare(  15, -15 ) > 0 );
    VVTRUE( clue::compare(  15,  -5 ) > 0 );
    VVTRUE( clue::compare(  15,   0 ) > 0 );
    VVTRUE( clue::compare(  15,   5 ) > 0 );
    VVTRUE( clue::compare(  15,  15 ) == 0 );
    VVTRUE( clue::compare(  15,  25 ) < 0 );


    VVTRUE( clue::compare( -15.5, -25.5 ) > 0 );
    VVTRUE( clue::compare( -15.5, -15.5 ) == 0 );
    VVTRUE( clue::compare( -15.5,  -5.5 ) < 0 );
    VVTRUE( clue::compare( -15.5,   0.5 ) < 0 );
    VVTRUE( clue::compare( -15.5,   5.5 ) < 0 );
    VVTRUE( clue::compare( -15.5,  15.5 ) < 0 );
    VVTRUE( clue::compare( -15.5,  25.5 ) < 0 );

    VVTRUE( clue::compare(   0.5, -25.5 ) > 0 );
    VVTRUE( clue::compare(   0.5, -15.5 ) > 0 );
    VVTRUE( clue::compare(   0.5,  -5.5 ) > 0 );
    VVTRUE( clue::compare(   0.5,   0.5 ) == 0 );
    VVTRUE( clue::compare(   0.5,   5.5 ) < 0 );
    VVTRUE( clue::compare(   0.5,  15.5 ) < 0 );
    VVTRUE( clue::compare(   0.5,  25.5 ) < 0 );

    VVTRUE( clue::compare(  15.5, -25.5 ) > 0 );
    VVTRUE( clue::compare(  15.5, -15.5 ) > 0 );
    VVTRUE( clue::compare(  15.5,  -5.5 ) > 0 );
    VVTRUE( clue::compare(  15.5,   0.5 ) > 0 );
    VVTRUE( clue::compare(  15.5,   5.5 ) > 0 );
    VVTRUE( clue::compare(  15.5,  15.5 ) == 0 );
    VVTRUE( clue::compare(  15.5,  25.5 ) < 0 );

  }

  return( verify.is_valid() );
}

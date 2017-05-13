// 2017-05-11 (cc) <paul4hough@gmail.com>

#include <clue/PidFile.hpp>
#include <valid/verify.hpp>

#define TEST_FN "data/PidFile/unit.pid"

valid::verify &
v_PidFile( void )
{
  static VVDESC( "clue::PidFile" );
  {
    VVWHEN( clue::PidFile t(TEST_FN) );
    {
      VVTRUE( t.good() );
    }
  }

  return( VALID_VALIDATOR );
}

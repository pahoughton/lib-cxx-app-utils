// 2017-05-11 (cc) <paul4hough@gmail.com>

#include <clue/HotSwap.hpp>
#include <valid/verify.hpp>

#define TEST_FN "data/HotSwap/lock.01"

valid::verify &
v_HotSwap( void )
{
  static VVDESC( "clue::HotSwap" );
  {
    VVWHEN( clue::HotSwap t(TEST_FN, std::ios::out ) );
    {
      VVTRUE( t.good() );
    }
  }

  return( VALID_VALIDATOR );
}

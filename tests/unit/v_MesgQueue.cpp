// 2017-05-11 (cc) <paul4hough@gmail.com>

#include <clue/MesgQueue.hpp>
#include <valid/verify.hpp>

#define TEST_FN "data/MesgQueue/queue.01"

valid::verify &
v_MesgQueue( void )
{
  static VVDESC( "clue::MesgQueue" );
  {
    VVWHEN( clue::MesgQueue t(TEST_FN, 'a', std::ios::out|std::ios::in, true) );
    {
      VVTRUE( t.good() );
    }
  }

  return( VALID_VALIDATOR );
}

// 2017-05-11 (cc) <paul4hough@gmail.com>

#include <clue/Semaphore.hpp>
#include <clue/FileStat.hpp>
#include <valid/verify.hpp>

#define TEST_FN "data/Semaphore/lock.01"

valid::verify &
v_Semaphore( void )
{
  static VVDESC( "clue::Semaphore" );
  {
    VVWHEN( clue::Semaphore t(TEST_FN) );
    {
      VVTRUE( t.good() );
    }
  }

  return( VALID_VALIDATOR );
}

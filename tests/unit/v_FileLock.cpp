// 2017-05-09 (cc) <paul4hough@gmail.com>

#include <clue/FileLock.hpp>
#include <valid/verify.hpp>

#define TEST_FN "data/FileBatch/tdata.01"

valid::verify &
v_FileLock( void )
{
  static VVDESC( "clue::FileLock" );
  {

    VVWHEN( clue::FileLock t(TEST_FN) );
    {
      VVTRUE( t.good() );
    }
  }

  return( VALID_VALIDATOR );
}

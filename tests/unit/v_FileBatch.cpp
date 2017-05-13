// 2017-05-09 (cc) <paul4hough@gmail.com>

#include <clue/FileBatch.hpp>
#include <valid/verify.hpp>

#define TEST_FN "data/FileBatch/tdata.01"

struct BatchRec {
  char ymd[8];
  char name[24];
  char size[15];
  char eol;
};

valid::verify &
v_FileBatch( void )
{
  static VVDESC( "clue::FileBatch" );
  {

    VVWHEN( clue::FileBatch<BatchRec> t(TEST_FN) );
    {
      VVTRUE( t.good() );
    }
  }

  return( VALID_VALIDATOR );
}

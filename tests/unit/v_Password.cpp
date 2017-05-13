// 2017-05-09 (cc) <paul4hough@gmail.com>

#include <clue/Password.hpp>
#include <valid/verify.hpp>

valid::verify &
v_Password( void )
{
  static VVDESC( "clue::Password" );
  {
    VVWHEN( clue::Password t(TEST_USER) );
    {
      VVTRUE( t.good() );
      VVTRUE(! strcmp(t.name(),TEST_USER) );
    }
  }

  return( VALID_VALIDATOR );
}

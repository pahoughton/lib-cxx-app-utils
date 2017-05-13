// 2017-05-10 (cc) <paul4hough@gmail.com>

#include <clue/SigCatcher.hpp>
#include <valid/verify.hpp>
#include <signal.h>


valid::verify &
v_SigCatcher( void )
{
  static VVDESC( "clue::SigCatcher" );
  {

    VVWHEN( clue::SigCatcher t(SIGQUIT) );
    {
      VVTRUE( t.good() );
    }
  }

  return( VALID_VALIDATOR );
}

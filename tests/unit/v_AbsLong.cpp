// 1996-10-31 (cc) <paul4hough@gmail.com>

#include <clue/Clue.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::AbsLong");
using namespace clue;

bool
v_AbsLong( void )
{
  {
    long  t = -12341234L;

    TEST( abs( t ) == 12341234L );

    t = 43214321L;

    TEST( abs( t ) == 43214321L );
  }
  return( verify.is_valid() );
}

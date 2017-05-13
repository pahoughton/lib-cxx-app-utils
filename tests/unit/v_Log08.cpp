// 1996-11-13 (cc) <paul4hough@gmail.com>

#include <clue/Log.hpp>
#include <clue/compare>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <cstdio>

static valid::verify verify("clue::Log08");
using namespace clue;

#define TEST_DATA_DIR "data/Log"

#define T_CLASS_NAME	"Log"

bool
v_Log08( void )
{
  {
    // lock( void );
    // unlock( void );

    // just making sure the calls link ok, cant really test it.
    Log t;

    t.lock();
    t.unlock();
  }

  {
    // good( void ) const;
    // error( void ) const;
    const char * TestFn = TEST_DATA_DIR "/log.37";
    const char * TestBadFn = "BAD_DIR_NAME/BAD_FILENAME";

    {
      Log t( TestFn );

      TEST( t.good() );
    }
    {
      const Log t( TestBadFn );

      TEST( ! t.good() );
      TEST( strstr( t.error(), "BAD" ) != 0 );
    }
  }
  return( verify.is_valid() );
}

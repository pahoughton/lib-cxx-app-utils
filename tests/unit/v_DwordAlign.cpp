// 1996-10-31 (cc) <paul4hough@gmail.com>

#include <clue/Clue.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::AbsLong");
using namespace clue;

bool
v_DwordAlign( void )
{
  {
    // DwordAlign( unsigned long value )
    long	num;

    num = 400;
    TEST( DwordAlign( num ) == 400 );
    TEST( DwordAlign( num + 1) == 404 );
    TEST( DwordAlign( num + 2) == 404 );
    TEST( DwordAlign( num + 3) == 404 );
    TEST( DwordAlign( num + 4) == 404 );

  }

  {
    // DwordAlign( void * addr )
    int    num = 400;

    int * lPtr = &num;

    char * ptr = (char *)lPtr;

#if defined( COMPARE_UNLIKE_POINTERS )
    TEST( ( ((long*)ptr ) == ptr) );
    TEST( ( ((long*)(ptr + 1)) == (ptr + 1) ) );
    TEST( ( ((long*)(ptr + 2)) == (ptr + 2) ) );
#endif

    TEST( ( ((int*)DwordAlign( ptr )) == lPtr ) );

    lPtr++;
    TEST( ( ((int*)DwordAlign( ptr + 1 )) == lPtr ) );
    TEST( ( ((int*)DwordAlign( ptr + 2 )) == lPtr ) );
    TEST( ( ((int*)DwordAlign( ptr + 3 )) == lPtr ) );
    TEST( ( ((int*)DwordAlign( ptr + 4 )) == lPtr ) );
  }

  return( verify.is_valid() );
}

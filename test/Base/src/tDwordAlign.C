#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Clue.hh>
#endif

bool
tDwordAlign( LibTest & tester )
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
    long    num = 400;
    
    long * lPtr = &num;
    
    char * ptr = (char *)lPtr;

#if defined( COMPARE_UNLIKE_POINTERS )
    TEST( ( ((long*)ptr ) == ptr) );
    TEST( ( ((long*)(ptr + 1)) == (ptr + 1) ) );
    TEST( ( ((long*)(ptr + 2)) == (ptr + 2) ) );
#endif
    
    TEST( ( ((long*)DwordAlign( ptr )) == lPtr ) );

    lPtr++;
    TEST( ( ((long*)DwordAlign( ptr + 1 )) == lPtr ) );
    TEST( ( ((long*)DwordAlign( ptr + 2 )) == lPtr ) );
    TEST( ( ((long*)DwordAlign( ptr + 3 )) == lPtr ) );
    TEST( ( ((long*)DwordAlign( ptr + 4 )) == lPtr ) );
  }
  
  return( true );
}


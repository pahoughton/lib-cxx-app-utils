
#include <LibTest.hh>

#include <Clue.hh>

bool
tDwordAlign( LibTest & test )
{
  {
    // DwordAlign( unsigned long value )
    long	num;
    
    num = 400;
    test( DwordAlign( num ) == 400 );
    test( DwordAlign( num + 1) == 404 );
    test( DwordAlign( num + 2) == 404 );
    test( DwordAlign( num + 3) == 404 );
    test( DwordAlign( num + 4) == 404 );

  }

  {
    // DwordAlign( void * addr )
    long    num = 400;
    
    long * lPtr = &num;
    
    char * ptr = (char *)lPtr;

#if ! defined(AIX)
    test( ( ((long*)ptr ) == ptr) );
    test( ( ((long*)(ptr + 1)) == (ptr + 1) ) );
    test( ( ((long*)(ptr + 2)) == (ptr + 2) ) );
#endif
    test( ( ((long*)DwordAlign( ptr )) == lPtr ) );

    lPtr++;
    test( ( ((long*)DwordAlign( ptr + 1 )) == lPtr ) );
    test( ( ((long*)DwordAlign( ptr + 2 )) == lPtr ) );
    test( ( ((long*)DwordAlign( ptr + 3 )) == lPtr ) );
    test( ( ((long*)DwordAlign( ptr + 4 )) == lPtr ) );
  }
  
  return( true );
}


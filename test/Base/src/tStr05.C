#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <cstring>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <cstring>
#endif

// Str::remove( ... )

#define T1 "first part"
#define T2 " second part"
#define T3 " third part"
#define T4 " forth part"
#define T5 " fifth part"

bool
tStr05( LibTest & tester )
{

  {
    // remove( size_t )

    Str t( T1 T2 T3 );

    t.remove( strlen( T1 T2 ) );

    TEST( t == T1 T2 );
  }

  {
    // remove( size_t, size_t )

    Str t( T1 T2 T3 );

    t.remove( strlen( T1 ), strlen( T2 ) );

    TEST( t == T1 T3 );
  }

  {
    // remove( iterator )

    Str t( "12345" );

    Str::iterator it = t.begin();
    it++;
    it++;

    t.remove( it );

    TEST( t == "1245" );
  }

  {
    // remove( iterator, iterator )
    
    Str t( "12345" );

    Str::iterator f = t.begin();
    Str::iterator l = f;
    l++;
    l++;
    
    t.remove( f, l );

    TEST( t == "345" );
  }

  return( true );
}

#include <LibTest.hh>
#include <Str.hh>

// Str::insert( ... )

#define T1 "first part"
#define T2 " second part"
#define T3 " third part"
#define T4 " forth part"
#define T5 " fifth part"

bool
tStr04( LibTest & test )
{

  {
    // insert( size_t, const Str &, size_t, size_t )

    Str t;

    Str src( T1 T2 T3 );

    t.insert( 0, src );

    test( t == src );

    t.insert( strlen( T1 ), src, strlen( T1 T2 ) );

    test( t == T1 T3 T2 T3 );

    t.insert( strlen( T1 T3 ), src, strlen( T1 ), strlen( T2 ) );

    test( t == T1 T3 T2 T2 T3 );
    
    t.insert( 0, src );

    test( t == T1 T2 T3 T1 T3 T2 T2 T3 );

    t.insert( t.size(), src );

    test( t == T1 T2 T3 T1 T3 T2 T2 T3 T1 T2 T3 );

    t.insert( strlen( T1 T2 T3 ), t, strlen( T1 T2 ), strlen( T3 ) );

    test( t == T1 T2 T3 T3 T1 T3 T2 T2 T3 T1 T2 T3 );
  }

  {
    // insert( size_t, const SubStr &, size_t size_t )

    Str t( T1 T2 );

    Str src( T1 T2 T3 T4 );

    t.insert( strlen( T1 ), src.substr( strlen( T1 ), strlen( T2 ) ) );

    test( t == T1 T2 T2 );

    t.insert( strlen( T1 ), src.substr( strlen( T1 ), strlen( T2 T3 ) ),
	      strlen( T2 ) );

    test( t == T1 T3 T2 T2 );

    t.insert( 0,  src.substr( strlen( T1 ), strlen( T2 T3 T4 ) ),
	      strlen( T2 ), strlen( T3 ) );

    test( t == T3 T1 T3 T2 T2 );
  }

  {
    // insert( size_t, const char *, size_t )

    Str t( T1 T2 T3 );

    t.insert( strlen( T1 T2 ), T4 );

    test( t == T1 T2 T4 T3 );

    t.insert( t.size(), T2 T3 T4, strlen( T2 T3 ) );

    test( t == T1 T2 T4 T3 T2 T3 );
    
  }

  {
    // insert( size_t, size_t, char )

    Str t( T1 T2 T3 );

    t.insert( strlen( T1 ), 5, 'x' );

    test( t == T1 "xxxxx" T2 T3 );

  }

  {
    // insert( size_t, char )

    Str t( T1 T2 );

    t.insert( 0, 'x' );

    test( t == "x" T1 T2 );
  }
    
  return( true );
}

#include <LibTest.hh>
#include <Str.hh>

// Str::remove( ... )

#define T1 "first part"
#define T2 " second part"
#define T3 " third part"
#define T4 " forth part"
#define T5 " fifth part"

bool
tStr05( LibTest & test )
{

  {
    // remove( size_t )

    Str t( T1 T2 T3 );

    t.remove( strlen( T1 T2 ) );

    test( t == T1 T2 );
  }

  {
    // remove( size_t, size_t )

    Str t( T1 T2 T3 );

    t.remove( strlen( T1 ), strlen( T2 ) );

    test( t == T1 T3 );
  }

  {
    // remove( iterator )

    Str t( "12345" );

    Str::iterator it = t.begin();
    it++;
    it++;

    t.remove( it );

    test( t == "1245" );
  }

  {
    // remove( iterator, iterator )
    
    Str t( "12345" );

    Str::iterator f = t.begin();
    Str::iterator l = f;
    l++;
    l++;
    
    t.remove( f, l );

    test( t == "345" );
  }

  return( true );
}

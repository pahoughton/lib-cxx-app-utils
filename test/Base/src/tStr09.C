#include <LibTest.hh>
#include <Str.hh>

// Str::misc

#define T1 "first part"
#define T2 " second part"
#define T3 " third part"
#define T4 " forth part"
#define T5 " fifth part"

bool
tStr09( LibTest & test )
{
  {
    // at( size_t )

    Str t( "0123456789" );

    test( t.at( 4 ) == '4' );

    test( t.at( (size_t)0 ) == '0');

    t.at( 3 ) = 'a';

    test( t == "012a456789" );
    test( t.at(3) == 'a' );

  }

  {
    // at( size_t ) const

    const Str t( "012345" );

    test( t.at(2) == '2');
  }

  {
    // operator [] ( size_t )

    Str t( "0123456789" );

    test( t[ 4 ] == '4' );

    test( t[ 0 ] == '0' );

    t[3] = 'a';

    test( t == "012a456789" );
    test( t[3] == 'a' );
  }

  {
    // operator[] ( size_t ) const

    const Str t( "012345" );

    test( t[4] == '4' );
  }

  return( true );
}

  
    
    


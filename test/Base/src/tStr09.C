#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#endif

// Str::misc

#define T1 "first part"
#define T2 " second part"
#define T3 " third part"
#define T4 " forth part"
#define T5 " fifth part"

bool
tStr09( LibTest & tester )
{
  {
    // at( size_t )

    Str t( "0123456789" );

    TEST( t.at( 4 ) == '4' );

    TEST( t.at( (size_t)0 ) == '0');

    t.at( 3 ) = 'a';

    TEST( t == "012a456789" );
    TEST( t.at(3) == 'a' );

  }

  {
    // at( size_t ) const

    const Str t( "012345" );

    TEST( t.at(2) == '2');
  }

  {
    // operator [] ( size_t )

    Str t( "0123456789" );

    TEST( t[ 4 ] == '4' );

    TEST( t[ 0 ] == '0' );

    t[3] = 'a';

    TEST( t == "012a456789" );
    TEST( t[3] == 'a' );
  }

  {
    // operator[] ( size_t ) const

    const Str t( "012345" );

    TEST( t[4] == '4' );
  }

  return( true );
}

  
    
    


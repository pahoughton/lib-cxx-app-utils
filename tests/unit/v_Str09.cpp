// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/Str.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::Str09");
using namespace clue;

// Str::misc

#define T1 "first part"
#define T2 " second part"
#define T3 " third part"
#define T4 " forth part"
#define T5 " fifth part"

bool
v_Str09( void )
{
  {
    // at( size_t )

    Str t( "0123456789" );

    TEST( t.at( 4 ) == '4' );

    TEST( t.at( (Str::size_type)0 ) == '0');

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

    TEST( t[ 4UL ] == '4' );

    TEST( t[ 0UL ] == '0' );

    t[3UL] = 'a';

    TEST( t == "012a456789" );
    TEST( t[3UL] == 'a' );
  }

  {
    // operator[] ( size_t ) const

    const Str t( "012345" );

    TEST( t[4UL] == '4' );
  }

  return( verify.is_valid() );
}

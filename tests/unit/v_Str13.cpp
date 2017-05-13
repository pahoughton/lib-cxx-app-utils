// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/Str.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <cstring>

static valid::verify verify("clue::Str13");
using namespace clue;

// Str::find

#define HAY "THIS is the 123 haYSTACK to search in 123 .,? AABBBCC"
//           01234567890123456789012345678901234567890123456789012
//                     1         2         3         4         5

bool
v_Str13( void )
{
  {
    // ffind( const Str & ) const
    // ffind( const Str &, size_t ) const

    Str t( HAY );

    Str s;

    s = "Hay";

    TEST( t.ffind( s ) == 16 );

    s = "123";

    TEST( t.ffind( s ) == 12 );
    TEST( t.ffind( s, 12 ) == 12 );
    TEST( t.ffind( s, 13 ) == 38 );

    s = "nope";

    TEST( t.ffind( s ) == Str::npos );
  }

  {
    // ffind( const SubStr & ) const
    // ffind( const SubStr &, size_t ) const

    Str t( HAY );

    Str s( "xx123xx" );

    TEST( t.ffind( s.substr( 2,3 ) ) == 12 );
    TEST( t.ffind( s.substr( 2,3 ), 13 ) == 38 );
  }

  {
    // ffind( const char * ) const
    // ffind( const char *, size_t ) const
    // ffind( const char *, size_t, size_t ) const

    Str t( HAY );

    TEST( t.ffind( ".,?" ) == 42 );
    TEST( t.ffind( "no" ) == Str::npos );
    TEST( t.ffind( "is", 3 ) == 5 );
    TEST( t.ffind( "isnot", 3, 2 ) == 5 );
  }

  {
    // ffind( char ) const
    // ffind( char, size_t ) const

    Str t( HAY );

    TEST( t.ffind( 'A' ) == 17 );
    TEST( t.ffind( 'a', 18 ) == 21 );
    TEST( t.ffind( 'x' ) == Str::npos );
  }

  return( verify.is_valid() );
}

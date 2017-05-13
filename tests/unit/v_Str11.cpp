// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/Str.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::Str11");
using namespace clue;

// Str::find

#define HAY "this is the 123 haystack to search in 123 .,? aabbbcc"
//           01234567890123456789012345678901234567890123456789012
//                     1         2         3         4         5

bool
v_Str11( void )
{
  {
    // find( const Str & ) const
    // find( const Str &, size_t ) const

    const Str t( HAY );

    Str s;

    s = "hay";

    TEST( t.find( s ) == 16 );

    s = "123";

    TEST( t.find( s ) == 12 );
    TEST( t.find( s, 12 ) == 12 );
    TEST( t.find( s, 13 ) == 38 );

    s = "nope";

    TEST( t.find( s ) == Str::npos );
  }

  {
    // find( const SubStr & ) const
    // find( const SubStr &, size_t ) const

    Str t( HAY );

    Str s( "xx123xx" );

    TEST( t.find( s.substr( 2,3 ) ) == 12 );
    TEST( t.find( s.substr( 2,3 ), 13 ) == 38 );
  }

  {
    // find( const char * ) const
    // find( const char *, size_t ) const
    // find( const char *, size_t, size_t ) const

    Str t( HAY );

    TEST( t.find( ".,?" ) == 42 );
    TEST( t.find( "no" ) == Str::npos );
    TEST( t.find( "is", 3 ) == 5 );
    TEST( t.find( "isnot", 3, 2 ) == 5 );

  }

  {
    // find( char ) const
    // find( char, size_t ) const

    Str t( HAY );

    TEST( t.find( 'a' ) == 17 );
    TEST( t.find( 'a', 18 ) == 21 );
    TEST( t.find( 'x' ) == Str::npos );
  }

  return( verify.is_valid() );
}

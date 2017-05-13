// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/Str.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <cstring>

static valid::verify verify("clue::Str04");
using namespace clue;

// Str::insert( ... )

#define T1 "first part"
#define T2 " second part"
#define T3 " third part"
#define T4 " forth part"
#define T5 " fifth part"

bool
v_Str04( void )
{

  {
    // insert( size_t, const Str &, size_t, size_t )

    Str t;

    Str src( T1 T2 T3 );

    t.insert( 0, src );

    TEST( t == src );

    t.insert( strlen( T1 ), src, strlen( T1 T2 ) );

    TEST( t == T1 T3 T2 T3 );

    t.insert( strlen( T1 T3 ), src, strlen( T1 ), strlen( T2 ) );

    TEST( t == T1 T3 T2 T2 T3 );

    t.insert( 0, src );

    TEST( t == T1 T2 T3 T1 T3 T2 T2 T3 );

    t.insert( t.size(), src );

    TEST( t == T1 T2 T3 T1 T3 T2 T2 T3 T1 T2 T3 );

    t.insert( strlen( T1 T2 T3 ), t, strlen( T1 T2 ), strlen( T3 ) );

    TEST( t == T1 T2 T3 T3 T1 T3 T2 T2 T3 T1 T2 T3 );
  }

  {
    // insert( size_t, const SubStr &, size_t size_t )

    Str t( T1 T2 );

    Str src( T1 T2 T3 T4 );

    t.insert( strlen( T1 ), src.substr( strlen( T1 ), strlen( T2 ) ) );

    TEST( t == T1 T2 T2 );

    t.insert( strlen( T1 ), src.substr( strlen( T1 ), strlen( T2 T3 ) ),
	      strlen( T2 ) );

    TEST( t == T1 T3 T2 T2 );

    t.insert( 0,  src.substr( strlen( T1 ), strlen( T2 T3 T4 ) ),
	      strlen( T2 ), strlen( T3 ) );

    TEST( t == T3 T1 T3 T2 T2 );
  }

  {
    // insert( size_t, const char *, size_t )

    Str t( T1 T2 T3 );

    t.insert( strlen( T1 T2 ), T4 );

    TEST( t == T1 T2 T4 T3 );

    t.insert( t.size(), T2 T3 T4, strlen( T2 T3 ) );

    TEST( t == T1 T2 T4 T3 T2 T3 );

  }

  {
    // insert( size_t, size_t, char )

    Str t( T1 T2 T3 );

    t.insert( strlen( T1 ), 5, 'x' );

    TEST( t == T1 "xxxxx" T2 T3 );

  }

  {
    // insert( size_t, char )

    Str t( T1 T2 );

    t.insert( 0, 'x' );

    TEST( t == "x" T1 T2 );
  }

  return( verify.is_valid() );
}

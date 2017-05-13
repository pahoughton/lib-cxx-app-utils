// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/Str.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <cstring>

static valid::verify verify("clue::Str03");
using namespace clue;

// Str::assign( ... )

#define T1 "first part"
#define T2 " second part"
#define T3 " third part"
#define T4 " forth part"
#define T5 " fifth part"

bool
v_Str03( void )
{
  {
    // assign( const Str &, size_t, size_t )

    Str t( T1 );

    Str src( T1 T2 T3 );

    t.assign( src );

    TEST( t == T1 T2 T3 );

    t.assign( src, strlen( T1 ) );

    TEST( t == T2 T3 );

    t.assign( src, strlen( T1 ), strlen( T2 ) );

    TEST( t == T2 );
  }

  {
    // assign( const SubStr &, size_t, size_t )

    Str t( T1 T2 );
    Str src( T1 T2 T3 T4 T5 );

    t.assign( t.substr( strlen( T1 ), strlen( T2 ) ) );

    TEST( t == T2 );

    t.assign( src.substr( strlen( T1 ), strlen( T2 T3 ) ), strlen( T2 ) );

    TEST( t == T3 );

    t.assign( src.substr( strlen( T1 ), strlen( T2 T3 T4 ) ),
	      strlen( T2 ), strlen( T3 ) );

    TEST( t == T3 );

  }

  {
    // assign( const char *, size_t )

    Str t( T1 T2 );

    t.assign( T2 T3 );

    TEST( t == T2 T3 );

    t.assign( T2 T3 T4, strlen( T2 T3 ) );

    TEST( t == T2 T3 );
  }

  {
    // assign( size_t, char )

    Str t( T4 );

    t.assign( 5, 'x' );

    TEST( t == "xxxxx" );

  }

  {
    // assign( char )

    Str t( T2 );

    t.assign( 'x' );

    TEST( t == "x" );

  }

  {
    // operator =  ( const Str & )
    // operator =  ( const SubStr & )
    // operator =  ( const char * )
    // operator =  ( char )

    Str t( T3 T4 );

    Str str( T1 T2 );
    Str sub( T1 T2 T3 );

    t = str;

    TEST( t == str );

    t = sub.substr( strlen(T1), strlen(T2) );

    TEST( t == T2 );

    t = T2 T4;

    TEST( t == T2 T4 );

    t = 'x';

    TEST( t == "x" );

  }

  return( verify.is_valid() );
}

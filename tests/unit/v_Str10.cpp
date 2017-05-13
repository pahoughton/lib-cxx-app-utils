// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/Str.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <cstring>

static valid::verify verify("clue::Str10");
using namespace clue;



// Str::iterators

#define T1 "first part"
#define T2 " second part"
#define T3 " third part"
#define T4 " forth part"
#define T5 " fifth part"

#define T1u "FIRST part"
#define T2u " second PART"
#define T3u " THIRD part"
#define T4u " forth PART"
#define T5u " FIFTH part"

bool
v_Str10( void )
{
  {
    // substr( void )
    // substr( size_t )
    // substr( size_t, size_t )
    // at( size_t, size_t )
    // SubStr::length( void ) const
    // SubStr::size( void ) const
    // SubStr::empty( void ) const

    Str t( T1 T2 T3 );

    TEST( t.substr() == T1 T2 T3 );

    TEST( t.substr( strlen( T1 ) ) == T2 T3 );

    TEST( t.substr( 0, strlen( T1 ) ) == T1 );

    TEST( t.substr( strlen(T1), strlen(T2) ).length() == strlen( T2 ) );

    TEST( t.substr( strlen(T1), strlen(T2) ).size() == strlen( T2 ) );

    TEST( t.substr( strlen(T1), strlen(T2) ) ==
	  t.at( strlen(T1), strlen(T2) ) );

    TEST( t.substr( 0, 0 ).empty() );

  }

  {
    // substr( void ) const
    // substr( size_t ) const
    // substr( size_t, size_t ) const
    // at( size_t, size_t ) const
    // SubStr::length( void ) const
    // SubStr::size( void ) const
    // SubStr::empty( void ) const

    const Str t( T1 T2 T3 );

    TEST( t.substr() == T1 T2 T3 );

    TEST( t.substr( strlen( T1 ) ) == T2 T3 );

    TEST( t.substr( 0, strlen( T1 ) ) == T1 );

    TEST( t.substr( strlen(T1), strlen(T2) ).length() == strlen( T2 ) );

    TEST( t.substr( strlen(T1), strlen(T2) ).size() == strlen( T2 ) );

    TEST( t.substr( strlen(T1), strlen(T2) ) ==
	  t.at( strlen(T1), strlen(T2) ) );

    TEST( t.substr( 0, 0 ).empty() );

  }

  {
    // at( const char * )
    // at( const char *, size_t )
    // at( const char *, size_t, size_t )

    Str t( T1 T2 T3 );

    TEST( t.at( T1 ) == T1 );
    TEST( t.at( T2 ) == T2 );
    TEST( t.at( T3 ) == T3 );

    t = T1 T2 T3 T1 T4;
    TEST( t.at( T1, strlen( T1 T2 ) ) == T1 );
    TEST( t.at( T1 T2, strlen( T1 T2 ), strlen( T1 ) ) == T1 );

    t.at( T1, strlen( T1 T2 ) ) = T3;
    TEST( t == T1 T2 T3 T3 T4 );
  }

  {
    // at( const char * ) const
    // at( const char *, size_t ) const
    // at( const char *, size_t, size_t ) const

    Str t( T1 T2 T3 );

    TEST( t.at( T1 ) == T1 );
    TEST( t.at( T2 ) == T2 );
    TEST( t.at( T3 ) == T3 );

    t = T1 T2 T3 T1 T4;
    TEST( t.at( T1, strlen( T1 T2 ) ) == T1 );
    TEST( t.at( T1 T2, strlen( T1 T2 ), strlen( T1 ) ) == T1 );
  }

  {
    // at( const Str & )
    // at( const Str &, size_t )

    Str t( T1 T2 T3 );
    Str pat;

    pat = T1;
    TEST( t.at( pat ) == T1 );

    t = T1 T2 T3 T1 T4;
    TEST( t.at( pat, strlen( T1 T2 ) ) == T1 );

    t.at( pat, strlen( T1 T2 ) ) = T3;
    TEST( t == T1 T2 T3 T3 T4 );
  }

  {
    // at( const Str & )
    // at( const Str &, size_t )

    Str t( T1 T2 T3 );
    Str pat;

    pat = T1;
    TEST( t.at( pat ) == T1 );

    t = T1 T2 T3 T1 T4;
    TEST( t.at( pat, strlen( T1 T2 ) ) == T1 );
  }

  {
    // at( const SubStr & )
    // at( const SubStr &, size_t )

    Str t( T1 T2 T3 );
    Str pat;

    pat = T1 T2;
    TEST( t.at( pat.substr( 0, strlen( T1 ) ) ) == T1 );

    t = T1 T2 T3 T1 T4;
    TEST( t.at( pat.substr( 0, strlen( T1 ) ), strlen( T1 T2 ) ) == T1 );

    t.at( pat.substr( 0, strlen( T1 ) ), strlen( T1 T2 ) ) = T3;
    TEST( t == T1 T2 T3 T3 T4 );
  }

  {
    // at( const SubStr & ) const
    // at( const SubStr &, size_t ) const

    Str t( T1 T2 T3 );
    Str pat;

    pat = T1 T2;
    TEST( t.at( pat.substr( 0, strlen( T1 ) ) ) == T1 );

    t = T1 T2 T3 T1 T4;
    TEST( t.at( pat.substr( 0, strlen( T1 ) ), strlen( T1 T2 ) ) == T1 );
  }

  {
    // before( size_t )
    Str t( T1 T2 T3 );

    TEST( t.before( strlen( T1 T2 ) ) == T1 T2 );
  }

  {
    // before( size_t ) const
    const Str t( T1 T2 T3 );

    TEST( t.before( strlen( T1 T2 ) ) == T1 T2 );
  }

  {
    // after( size_t )
    Str t( T1 T2 T3 );

    TEST( t.after( strlen( T1 ) ) == T2 T3 );
  }

  {
    // after( size_t ) const
    const Str t( T1 T2 T3 );

    TEST( t.after( strlen( T1 ) ) == T2 T3 );
  }

  return( verify.is_valid() );
}

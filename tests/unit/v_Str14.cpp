#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <RegexScan.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <RxScan.hh>
#endif

// Str::rfind

#define HAY "THIS IS THE 123 Haystack TO SEARCH IN 123 .,? aabbbcc"
//           01234567890123456789012345678901234567890123456789012
//                     1         2         3         4         5

bool
tStr14( LibTest & tester )
{
  {
    // rffind( const Str & ) const
    // rffind( const Str &, size_t ) const

    Str t( HAY );

    Str s;

    s = "hAY";

    TEST( t.rffind( s ) == 16 );

    s = "123";

    TEST( t.rffind( s ) == 38 );
    TEST( t.rffind( s, 37 ) == 12 );

    s = "nope";

    TEST( t.rffind( s ) == Str::npos );
  }

  {
    // rffind( const SubStr & ) const
    // rffind( const SubStr &, size_t ) const

    Str t( HAY );

    Str s( "xx123xx" );

    TEST( t.rffind( s.substr( 2,3 ) ) == 38 );
    TEST( t.rffind( s.substr( 2,3 ), 37 ) == 12 );
  }

  {
    // rffind( const char * ) const
    // rffind( const char *, size_t ) const
    // rffind( const char *, size_t, size_t ) const

    Str t( HAY );

    TEST( t.rffind( ".,?" ) == 42 );
    TEST( t.rffind( "no" ) == Str::npos );
    TEST( t.rffind( "c" ) == 52 );
    TEST( t.rffind( "th" ) == 8 );
    TEST( t.rffind( "th", 7 ) == 0 );
    TEST( t.rffind( "ThXX", 7, 2 ) == 0 );
  }

  {
    // rffind( char ) const
    // rffind( char, size_t ) const

    Str t( HAY );

    TEST( t.rffind( 'c' ) == 52 );
    TEST( t.rffind( 'A' ) == 47 );
    TEST( t.rffind( 'a', 40 ) == 30 );
    TEST( t.rffind( 'x' ) == Str::npos );
    TEST( t.rffind( 't', 7 ) == 0 );
  }
    
  return( true );
}


      

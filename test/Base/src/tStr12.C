#if !defined( CLUE_SHORT_FN )
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

#define HAY "this is the 123 haystack to search in 123 .,? aabbbcc"
//           01234567890123456789012345678901234567890123456789012
//                     1         2         3         4         5

bool
tStr12( LibTest & tester )
{
  {
    // rfind( const Str & ) const
    // rfind( const Str &, size_t ) const

    Str t( HAY );

    Str s;

    s = "hay";

    TEST( t.rfind( s ) == 16 );

    s = "123";

    TEST( t.rfind( s ) == 38 );
    TEST( t.rfind( s, 37 ) == 12 );

    s = "nope";

    TEST( t.rfind( s ) == Str::npos );
  }

  {
    // rfind( const SubStr & ) const
    // rfind( const SubStr &, size_t ) const

    Str t( HAY );

    Str s( "xx123xx" );

    TEST( t.rfind( s.substr( 2,3 ) ) == 38 );
    TEST( t.rfind( s.substr( 2,3 ), 37 ) == 12 );
  }

  {
    // rfind( const char * ) const
    // rfind( const char *, size_t ) const
    // rfind( const char *, size_t, size_t ) const

    Str t( HAY );

    TEST( t.rfind( ".,?" ) == 42 );
    TEST( t.rfind( "no" ) == Str::npos );
    TEST( t.rfind( "c" ) == 52 );
    TEST( t.rfind( "th" ) == 8 );
    TEST( t.rfind( "th", 7 ) == 0 );
    TEST( t.rfind( "thXX", 7, 2 ) == 0 );
  }

  {
    // rfind( char ) const
    // rfind( char, size_t ) const

    Str t( HAY );

    TEST( t.rfind( 'c' ) == 52 );
    TEST( t.rfind( 'a' ) == 47 );
    TEST( t.rfind( 'a', 40 ) == 30 );
    TEST( t.rfind( 'x' ) == Str::npos );
    TEST( t.rfind( 't', 7 ) == 0 );
  }
    
  return( true );
}


      

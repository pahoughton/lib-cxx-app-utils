#include <LibTest.hh>
#include <Str.hh>
#include <RegexScan.hh>

// Str::rfind

#define HAY "this is the 123 haystack to search in 123 .,? aabbbcc"
//           01234567890123456789012345678901234567890123456789012
//                     1         2         3         4         5

bool
tStr12( LibTest & test )
{
  {
    // rfind( const Str & ) const
    // rfind( const Str &, size_t ) const

    Str t( HAY );

    Str s;

    s = "hay";

    test( t.rfind( s ) == 16 );

    s = "123";

    test( t.rfind( s ) == 38 );
    test( t.rfind( s, 37 ) == 12 );

    s = "nope";

    test( t.rfind( s ) == Str::npos );
  }

  {
    // rfind( const SubStr & ) const
    // rfind( const SubStr &, size_t ) const

    Str t( HAY );

    Str s( "xx123xx" );

    test( t.rfind( s.substr( 2,3 ) ) == 38 );
    test( t.rfind( s.substr( 2,3 ), 37 ) == 12 );
  }

  {
    // rfind( const char * ) const
    // rfind( const char *, size_t ) const
    // rfind( const char *, size_t, size_t ) const

    Str t( HAY );

    test( t.rfind( ".,?" ) == 42 );
    test( t.rfind( "no" ) == Str::npos );
    test( t.rfind( "c" ) == 52 );
    test( t.rfind( "th" ) == 8 );
    test( t.rfind( "th", 7 ) == 0 );
    test( t.rfind( "thXX", 7, 2 ) == 0 );
  }

  {
    // rfind( char ) const
    // rfind( char, size_t ) const

    Str t( HAY );

    test( t.rfind( 'c' ) == 52 );
    test( t.rfind( 'a' ) == 47 );
    test( t.rfind( 'a', 40 ) == 30 );
    test( t.rfind( 'x' ) == Str::npos );
    test( t.rfind( 't', 7 ) == 0 );
  }
    
  return( true );
}


      

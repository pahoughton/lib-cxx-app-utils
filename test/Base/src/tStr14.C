#include <LibTest.hh>
#include <Str.hh>
#include <RegexScan.hh>

// Str::rfind

#define HAY "THIS IS THE 123 Haystack TO SEARCH IN 123 .,? aabbbcc"
//           01234567890123456789012345678901234567890123456789012
//                     1         2         3         4         5

bool
tStr14( LibTest & test )
{
  {
    // rffind( const Str & ) const
    // rffind( const Str &, size_t ) const

    Str t( HAY );

    Str s;

    s = "hAY";

    test( t.rffind( s ) == 16 );

    s = "123";

    test( t.rffind( s ) == 38 );
    test( t.rffind( s, 37 ) == 12 );

    s = "nope";

    test( t.rffind( s ) == Str::npos );
  }

  {
    // rffind( const SubStr & ) const
    // rffind( const SubStr &, size_t ) const

    Str t( HAY );

    Str s( "xx123xx" );

    test( t.rffind( s.substr( 2,3 ) ) == 38 );
    test( t.rffind( s.substr( 2,3 ), 37 ) == 12 );
  }

  {
    // rffind( const char * ) const
    // rffind( const char *, size_t ) const
    // rffind( const char *, size_t, size_t ) const

    Str t( HAY );

    test( t.rffind( ".,?" ) == 42 );
    test( t.rffind( "no" ) == Str::npos );
    test( t.rffind( "c" ) == 52 );
    test( t.rffind( "th" ) == 8 );
    test( t.rffind( "th", 7 ) == 0 );
    test( t.rffind( "ThXX", 7, 2 ) == 0 );
  }

  {
    // rffind( char ) const
    // rffind( char, size_t ) const

    Str t( HAY );

    test( t.rffind( 'c' ) == 52 );
    test( t.rffind( 'A' ) == 47 );
    test( t.rffind( 'a', 40 ) == 30 );
    test( t.rffind( 'x' ) == Str::npos );
    test( t.rffind( 't', 7 ) == 0 );
  }
    
  return( true );
}


      

#include <LibTest.hh>
#include <Str.hh>
#include <RegexScan.hh>

// Str::find

#define HAY "THIS is the 123 haYSTACK to search in 123 .,? AABBBCC"
//           01234567890123456789012345678901234567890123456789012
//                     1         2         3         4         5

bool
tStr13( LibTest & test )
{
  {
    // ffind( const Str & ) const
    // ffind( const Str &, size_t ) const

    Str t( HAY );

    Str s;

    s = "Hay";

    test( t.ffind( s ) == 16 );

    s = "123";

    test( t.ffind( s ) == 12 );
    test( t.ffind( s, 12 ) == 12 );
    test( t.ffind( s, 13 ) == 38 );

    s = "nope";

    test( t.ffind( s ) == Str::npos );
  }

  {
    // ffind( const SubStr & ) const 
    // ffind( const SubStr &, size_t ) const 

    Str t( HAY );

    Str s( "xx123xx" );

    test( t.ffind( s.substr( 2,3 ) ) == 12 );
    test( t.ffind( s.substr( 2,3 ), 13 ) == 38 );
  }

  {
    // ffind( const char * ) const
    // ffind( const char *, size_t ) const
    // ffind( const char *, size_t, size_t ) const

    Str t( HAY );

    test( t.ffind( ".,?" ) == 42 );
    test( t.ffind( "no" ) == Str::npos );
    test( t.ffind( "is", 3 ) == 5 );
    test( t.ffind( "isnot", 3, 2 ) == 5 );
  }

  {
    // ffind( char ) const
    // ffind( char, size_t ) const

    Str t( HAY );

    test( t.ffind( 'A' ) == 17 );
    test( t.ffind( 'a', 18 ) == 21 );
    test( t.ffind( 'x' ) == Str::npos );
  }
    
  return( true );
}


      

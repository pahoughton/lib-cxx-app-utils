#include <LibTest.hh>
#include <Str.hh>
#include <RegexScan.hh>

// Str::find

#define HAY "this is the 123 haystack to search in 123 .,? aabbbcc"
//           01234567890123456789012345678901234567890123456789012
//                     1         2         3         4         5

bool
tStr11( LibTest & test )
{
  {
    // find( const Str & ) const
    // find( const Str &, size_t ) const

    const Str t( HAY );

    Str s;

    s = "hay";

    test( t.find( s ) == 16 );

    s = "123";

    test( t.find( s ) == 12 );
    test( t.find( s, 12 ) == 12 );
    test( t.find( s, 13 ) == 38 );

    s = "nope";

    test( t.find( s ) == Str::npos );
  }

  {
    // find( const SubStr & ) const
    // find( const SubStr &, size_t ) const

    Str t( HAY );

    Str s( "xx123xx" );

    test( t.find( s.substr( 2,3 ) ) == 12 );
    test( t.find( s.substr( 2,3 ), 13 ) == 38 );
  }

  {
    // find( const RegexScan & ) const
    // find( const RegexScan &, size_t ) const
    Str t( HAY );

    RegexScan e( "((is)|(was)) the [1-3]+ ..[a-z]+ to" );

    test( t.find( e ) == 5 );
    test( t.find( e, 6 ) == Str::npos );
  }

  {
    // find( const char * ) const
    // find( const char *, size_t ) const
    // find( const char *, size_t, size_t ) const

    Str t( HAY );

    test( t.find( ".,?" ) == 42 );
    test( t.find( "no" ) == Str::npos );
    test( t.find( "is", 3 ) == 5 );
    test( t.find( "isnot", 3, 2 ) == 5 );
    
  }

  {
    // find( char ) const
    // find( char, size_t ) const

    Str t( HAY );

    test( t.find( 'a' ) == 17 );
    test( t.find( 'a', 18 ) == 21 );
    test( t.find( 'x' ) == Str::npos );
  }
    
  return( true );
}


      

#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <cstring>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <cstring>
#endif

// Str::replace( ... )

#define T1 "first part"
#define T2 " second part"
#define T3 " third part"
#define T4 " forth part"
#define T5 " fifth part"

bool
tStr06( LibTest & tester )
{
  {
    // replace( size_t, size_t, const char * )
    // replace( size_t, size_t, const char *, size_t )

    Str t( T1 T2 T3 T4 );

    t.replace( 0, strlen( T1 ), T3 );

    TEST( t == T3 T2 T3 T4 );

    t.replace( strlen( T3 T2 T3 ), strlen( T4 ), T5 T3, strlen( T5 ) );

    TEST( t == T3 T2 T3 T5 );

    t.replace( strlen( T3 T2 ), strlen( T3 ), (char*)0 );

    TEST( t == T3 T2 T5 );
  }

  {
    // replace( size_t, size_t, size_t, char )

    Str t( T1 T2 T3 );

    t.replace( strlen( T1 ), strlen( T2 ), 5, 'x' );

    TEST( t == T1 "xxxxx" T3 );
  }

  {
    // replace( size_t, size_t, const Str &)
    // replace( size_t, size_t, const Str &, size_t, size_t )

    Str t( T1 T2 T3 );

    Str s( T3 T4 T5 );

    t.replace( 0, strlen( T1 ), s );

    TEST( t == T3 T4 T5 T2 T3 );

    t.replace( strlen( T3 T4 ), strlen( T5 T2 ), s, strlen( T3 ), strlen( T4 ) );

    TEST( t == T3 T4 T4 T3 );
  }

  {
    // replace( size_t, size_t, const SubStr & )
    // replace( size_t, size_t, const SubStr &, size_t, size_t )
    
    Str t( T3 T4 T5 );

    Str s( T1 T2 T3 );

    t.replace( strlen( T3 ), strlen( T4 ), s.substr( strlen( T1 ), strlen( T2 ) ) );

    TEST( t == T3 T2 T5 );
    
    t.replace( strlen( T3 ), strlen( T2 ),
	       s.substr( strlen( T1 ), strlen( T2 T3 ) ), strlen( T2 ) );

    TEST( t == T3 T3 T5 );

    t.replace( strlen( T3 ), strlen( T3 T5 ),
	       s.substr( 0, strlen( T1 T2 ) ), 0, strlen( T1 ) );

    TEST( t == T3 T1 );
  }

  {
    // replace( size_t, size_t, char )

    Str t( T1 T2 T3 );

    t.replace( 0, 0, 'a' );

    TEST( t == "a" T1 T2 T3 );
  }

  {
    // replace( iterator, iterator, const Str & )
    // replace( iterator, iterator, const Str &, size_t )
    // replace( iterator, iterator, const Str &, size_t, size_t )
    
    Str t( "123456" );
    Str s( "abcdef" );
    
    Str::iterator f = t.begin();
    Str::iterator l = f;

    f++; f++;
    l++; l++; l++; l++;

    t.replace( f, l, s);

    TEST( t == "12abcdef56" );

    t.replace( f, l, s, 3 );

    TEST( t == "12defcdef56" );

    t.replace( f, l, s, 0, 2 );

    TEST( t == "12abfcdef56" );
  }

  return( true );
}

#if !defined( CLUE_SHORT_FN )
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

// Str::append( ... )

#define T1 "first part"
#define T2 " second part"
#define T3 " third part"
#define T4 " forth part"

bool
tStr02( LibTest & tester )
{
  {
    // append( const Str & )

    Str t;

    {
      Str src( T1 );
    
      t.append( src );

      TEST( t == src );
    }

    {
      Str src( T2 );
    
      t.append( src );

      TEST( t == T1 T2 );
    }

    // overlap test

    t.append( t );

    TEST( t == T1 T2 T1 T2 );    
  }

  {
    // append( const Str &, size_t )

    Str t;

    Str src( "123" T1 );

    t.append( src, 3 );
    
    TEST( t == T1 );

  }

  {
    // append( const Str &, size_t, size_t )

    Str t;
    
    Str src( "123" T1 "12345" );

    t.append( src, 3, strlen( T1 ) );

    TEST( t == T1 );
  }

  {
    // append( const SubStr & )

    Str t( T1 T2 T3 );

    t.append( t.substr( strlen( T1 ), strlen( T2 ) ) );

    TEST( t == T1 T2 T3 T2 );
  }

  {
    // append( const SubStr &, size_t )
    Str t( T1 T2 T3 );

    t.append( t.substr( 0, strlen( T1 T2 ) ), strlen( T1 ) );

    TEST( t == T1 T2 T3 T2 );
  }

  {
    // append( const SubStr &, size_t, size_t )
    Str t( T1 T2 T3 T4);

    t.append( t.substr( 0, strlen( T1 T2 T3 ) ), strlen( T1 ), strlen( T2 ) );

    TEST( t == T1 T2 T3 T4 T2 );
  }
  
  {
    // append( const char * )

    Str t;

    t.append( T1 );

    TEST( t == T1 );

    t.append( T2 ).append( T3 ).append( T4 );

    TEST( t == T1 T2 T3 T4 );
    
  }

  {
    // append( const char *, size_t )

    Str t;

    t.append( T1 T2, strlen( T1 ) );

    TEST( t == T1 );
  }

  {
    // append( size_t, char )

    Str t;

    t.append( 5, 'x' );

    TEST( t == "xxxxx" );
  }

  {
    // append( char )

    Str t;

    t.append( '1' ).append( '2' ).append( '3' );

    TEST( t == "123" );
  }

  {
    Str t( T1 );

    t.append( t.begin(), t.end() );

    TEST( t == T1 T1 );
  }

  {
    // operator += ( const Str & )
    // operator += ( const SubStr & )
    // operator += ( const char * )
    // operator += ( char )
    
    
    Str t;

    Str str( T1 );
    Str sub( T1 T2 T3 );

    t += str;

    TEST( t == T1 );

    t += sub.substr( strlen( T1 ), strlen( T2 ) );

    TEST( t == T1 T2 );

    t += T3;

    TEST( t == T1 T2 T3 );

    t += 'x';

    TEST( t == T1 T2 T3 "x" );

    (t += T2) += T3;

    TEST( t == T1 T2 T3 "x" T2 T3 );
  }
  
  return( true );
}
  

#include <LibTest.hh>
#include <Str.hh>

#define T1 "first part"
#define T2 " second part"
#define T3 " third part"
#define T4 " forth part"
#define T5 " fifth part"

bool
tSubStr01( LibTest & test )
{
  {
    // Str::substr( size_t, size_t )
    // operator == ( const char * ) const
    // operator != ( const char * ) const
    // Str::operator == ( const SubStr & ) const
    // Str::operator != ( const SubStr & ) const

    Str t;

    t << "123" << T1 << "junk";

    test( t.substr( 3, strlen( T1 ) ) == T1 );
    test( t.substr( 3, strlen( T1 ) ) != "diff string" );

    Str s;

    s << T1;

    test( s == t.substr( 3, strlen( T1 ) ) );
    test( s != t.substr( 2, strlen( T1 ) ) );
    test( s != t.substr( 3, strlen( T1 ) + 1 ) );
    test( s != t.substr( 4, strlen( T1 ) ) );
    test( s != t.substr( 3, strlen( T1 ) - 1 ) );
  }
    
  {
    // SubStr( Str & src )

    Str	    s( T1 T2 T3 );
    SubStr  t( s );

    test( t == T1 T2 T3 );
  }
  
  {
    // SubStr( Str & src, size_t )

    Str	    s( T1 T2 T3 );
    SubStr  t( s, strlen( T1 ) );

    test( t == T2 T3 );
  }

  {
    // SubStr( Str & src, size_t, size_t )

    Str	    s( T1 T2 T3 );
    SubStr  t( s, strlen( T1 ), strlen( T2 ) );

    test( t == T2 );
  }
  
  {
    // SubStr( const Str & src )

    const Str	s( T1 T2 T3 );
    SubStr	t( s );

    test( t == T1 T2 T3 );
  }
  
  {
    // SubStr( const Str & src, size_t )

    const Str   s( T1 T2 T3 );
    SubStr	t( s, strlen( T1 ) );

    test( t == T2 T3 );
  }

  {
    // SubStr( const Str & src, size_t, size_t )

    const Str	s( T1 T2 T3 );
    SubStr	t( s, strlen( T1 ), strlen( T2 ) );

    test( t == T2 );
  }
  
  {
    // size( void ) const
    // length( void ) const
    // empty( void ) const

    const Str	t( T1 T2 T3 );

    test( t( strlen(T1), strlen( T2 ) ).size() == strlen( T2 ) );
    test( t( strlen(T1), strlen( T2 ) ).length() == strlen( T2 ) );
    test( ! t( strlen(T1), strlen( T2 ) ).empty() );
    test( t( 0, 0 ).empty() );
  }

  // test operator = ( const char * ) so it can
  // be used in the other test

  
  {
    // operator =  (const char *)
    
    Str t( T1 T2 T3 T4 );

    t.substr( 0, strlen( T1 ) ) = T5;

    test( t == T5 T2 T3 T4 );

    t.substr( strlen( T5 ), strlen( T2 T3 ) ) = T4 T1 T3 T1;

    test( t == T5 T4 T1 T3 T1 T4 );

    t.substr( strlen( T5 T4 T1 T3 T1 T4 ), 0 ) = T1;

    test( t == T5 T4 T1 T3 T1 T4 T1 );
  }

  return( true );
}


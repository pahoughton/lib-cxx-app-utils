#include <LibTest.hh>
#include <Str.hh>

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
tSubStr04( LibTest & test )
{
  {
    // operator [] ( size_t ) 

    Str t( "1234567890" );
    
    test( t.substr( 2, 4 )[2] == '5' );

    t.substr( 3, 5 )[1] = 'a';

    test( t == "1234a67890" );

  }

  {
    // operator [] ( size_t ) const
    const Str t( "1234567890" );
    
    test( t.substr( 2, 4 )[2] == '5' );
  }

  {
    // operator = ( const SubStr & )

    Str t( T1 T2 T3 );
    Str s( T1 T2 T3 T4 );

    t.substr( strlen(T1), strlen(T2 T3) ) = s.substr( 0, strlen( T1 ) );

    test( t == T1 T1 );
  }

  {
    // operator = ( const Str & )
    
    Str t( T1 T2 T3 );
    Str s( T4 T5 );

    t.substr( strlen( T1 ), strlen( T2 ) ) = s;

    test( t == T1 T4 T5 T3 );
  }

  {
    // operator = ( const char * )
    
    Str t( T1 T2 T3 );

    t.substr( strlen( T1 ), strlen( T2 ) ) = T4 T5;

    test( t == T1 T4 T5 T3 );
  }

  {
    // operator = ( char )

    Str t( T1 T2 T3 );

    t.substr( strlen( T1 T2 T3 ), 0 ) = 'a';

    test( t == T1 T2 T3 "a" );
  }

  {
    // operator += ( const Str & )

    Str t( T1 T2 T3 );
    Str s( T4 T5 );

    t.substr( strlen(T1), strlen(T2) ) += s;

    test( t == T1 T2 T4 T5 T3 );
  }

  {
    // operator += ( const SubStr & )
    
    Str t( T1 T2 T3 );
    Str s( T3 T4 T5 );

    t.substr( 0, strlen( T1 T2 ) ) += s.substr( strlen(T3), strlen(T4) );

    test( t == T1 T2 T4 T3 );
  }

  {
    // operator += ( const char * )

    Str t( T2 T3 T4 );

    t.substr( 0, strlen( T2 ) ) += T5;

    test( t == T2 T5 T3 T4 );
  }

  {
    // operator += ( char )

    Str t( T1 T2 T3 );

    t.substr( strlen( T1 ), strlen( T2 ) ) += 'x';

    test( t == T1 T2 "x" T3 );
  }

  {
    // operator == ( const SubStr & ) const
    
    const Str t( T1 T2 T3 T4 );
    const Str s( T1 T2 T3 T4 );

    test( t.substr( strlen( T1 ), strlen( T2 T3 ) ) ==
	  s.substr( strlen( T1 ), strlen( T2 T3 ) ) );
    
    test( ! ( t.substr( strlen( T1 ), strlen( T2 T3 ) ) ==
	      s.substr( strlen( T1 ), strlen( T2 T3 ) + 1 ) ) );
  }

  {
    // operator == ( const Str & ) const

    const Str t( T1 T2 T3 T4 );
    const Str s( T2 T3 );

    test( t.substr( strlen(T1), strlen(T2 T3) ) == s );
    test( ! ( t.substr( strlen( T1 ), strlen(T2 T3) + 1 ) == s ) );
  }
  
  {
    // operator == ( const char * ) const

    const Str t( T1 T2 T3 T4 );

    test( t.substr( 0, strlen( T1 T2 ) ) == T1 T2 );
    test( ! (t.substr( 0, strlen( T1 T2 ) ) == T1 T2 "x" ) );
  }

  {
    // operator < ( const SubStr & ) const

    const Str t( T1 T2 T3 T4 );
    const Str s( T1 T2 T3 );

    test( t.substr( 0, strlen( T1 ) ) < s.substr( 0, strlen( T1 ) + 1 ) );
    test( t.substr( strlen(T1), strlen(T2) ) < s.substr( 0, strlen(T1 T2) ) );
    test( ! (t.substr( 0, strlen(T1) ) < s.substr( strlen(T1), strlen(T2) ) ));
  }

  {
    // operator < ( const Str & ) const

    Str t( T1 T2 T3 T4 );
    Str s( T2 T3 );

    test( t.substr( strlen(T1), strlen(T2) ) < s );
    test( ! (t.substr( strlen(T1), strlen(T2 T3) ) < s ) );
  }

  {
    // operator < ( const char * ) const

    Str t( T1 T2 T3 T4 );

    test( t.substr( 0, strlen( T1 T2 ) ) < T1 T2 T3 );
    test( t.substr( strlen( T1 ), strlen( T2 ) ) < T1 T2 T3 );
    test( ! (t.substr( strlen(T1), strlen(T2) ) < T2 ) );
  }

  {
    // operator != ( const SubStr & ) const
    
    Str t( T1 T2 T3 T4 );
    Str s( T1 T2 T3 T4 );

    test( ! (t.substr( strlen( T1 ), strlen( T2 T3 ) ) !=
	     s.substr( strlen( T1 ), strlen( T2 T3 ) ) ) );
    
    test( t.substr( strlen( T1 ), strlen( T2 T3 ) ) !=
	  s.substr( strlen( T1 ), strlen( T2 T3 ) + 1 ) );
  }

  {
    // operator != ( const Str & ) const

    Str t( T1 T2 T3 T4 );
    Str s( T2 T3 );

    test( ! ( t.substr( strlen(T1), strlen(T2 T3) ) != s ) );
    test( t.substr( strlen( T1 ), strlen(T2 T3) + 1 ) != s );
  }
  
  {
    // operator != ( const char * ) const

    Str t( T1 T2 T3 T4 );

    test( ! ( t.substr( 0, strlen( T1 T2 ) ) != T1 T2 ) );
    test( t.substr( 0, strlen( T1 T2 ) ) != T1 T2 "x" );
  }

  {
    // operator > ( const SubStr & ) const

    const Str t( T1 T2 T3 T4 );
    const Str s( T1 T2 T3 );

    test( t.substr( 0, strlen( T1 ) ) > s.substr( 0, strlen( T1 ) - 1 ) );
    test( ! (t.substr( 0, strlen( T1 ) ) > s.substr( 0, strlen( T1 ) ) ) );
  }

  {
    // operator > ( const Str & ) const

    Str t( T1 T2 T3 T4 );
    Str s( T2 T3 );

    test( t.substr( strlen(T1), strlen(T2 T3) + 1) > s );
    test( ! (t.substr( strlen(T1), strlen(T2 T3) ) > s ) );
  }

  {
    // operator > ( const char * ) const

    Str t( T1 T2 T3 T4 );

    test( t.substr( 0, strlen( T1 T2 ) + 1 ) > T1 T2 );
    test( ! ( t.substr( 0, strlen( T1 T2 ) ) > T1 T2 ) );
  }

  {
    // operator <= ( const SubStr & ) const

    const Str t( T1 T2 T3 T4 );
    const Str s( T1 T2 T3 );

    test( t.substr( 0, strlen( T1 ) ) <= s.substr( 0, strlen( T1 ) + 1 ) );
    test( t.substr( strlen(T1), strlen(T2) ) <= s.substr( 0, strlen(T1 T2) ) );
    test( t.substr( 0, strlen( T1 ) ) <= s.substr( 0, strlen( T1 ) ) );
    test( ! (t.substr( 0, strlen(T1) ) <=
	     s.substr( strlen(T1), strlen(T2) ) ));
  }

  {
    // operator <= ( const Str & ) const

    Str t( T1 T2 T3 T4 );
    Str s( T2 T3 );

    test( t.substr( strlen(T1), strlen(T2) ) <= s );
    test( t.substr( strlen(T1), strlen(T2 T3) ) <= s );
    test( ! (t.substr( strlen(T1), strlen(T2 T3) + 1 ) <= s ) );
  }

  {
    // operator <= ( const char * ) const

    Str t( T1 T2 T3 T4 );

    test( t.substr( 0, strlen( T1 T2 ) ) <= T1 T2 T3 );
    test( t.substr( strlen( T1 ), strlen( T2 ) ) <= T1 T2 T3 );
    test( t.substr( 0, strlen( T1 T2 ) ) <= T1 T2 );
    test( ! (t.substr( strlen(T1), strlen(T2 T3) ) <= T2 ) );
  }

  {
    // operator >= ( const SubStr & ) const

    const Str t( T1 T2 T3 T4 );
    const Str s( T1 T2 T3 );

    test( t.substr( 0, strlen( T1 ) ) >= s.substr( 0, strlen( T1 ) - 1 ) );
    test( t.substr( 0, strlen( T1 ) ) >= s.substr( 0, strlen( T1 ) ) );
    test( ! (t.substr( 0, strlen( T1 ) ) >= s.substr( 0, strlen(T1) + 1 ) ) );
  }

  {
    // operator >= ( const Str & ) const

    Str t( T1 T2 T3 T4 );
    Str s( T2 T3 );

    test( t.substr( strlen(T1), strlen(T2 T3) + 1) >= s );
    test( t.substr( strlen(T1), strlen(T2 T3) ) >= s );
    test( ! (t.substr( strlen(T1), strlen(T2 T3) -1 ) >= s ) );
  }

  {
    // operator >= ( const char * ) const

    Str t( T1 T2 T3 T4 );

    test( t.substr( 0, strlen( T1 T2 ) + 1 ) >= T1 T2 );
    test( t.substr( 0, strlen( T1 T2 ) ) >= T1 T2 );
    test( ! ( t.substr( 0, strlen( T1 T2 ) - 1 ) >= T1 T2 ) );
  }

  return( true );
}





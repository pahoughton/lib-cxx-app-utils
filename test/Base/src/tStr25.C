#include <LibTest.hh>
#include <Str.hh>

#include <fstream>

#define T1 "first part"
#define T2 " second part"
#define T3 " third part"
#define T4 " forth part"
#define T5 " fifth part"


bool
tStr25( LibTest & test )
{
  {
    // operator + ( const Str &, const Str & )
    // operator + ( const Str &, const SubStr & )
    // operator + ( const Str &, const char * )
    
    Str t;

    const Str l( T1 );
    const Str r( T2 );

    t = l + r;
    test( t == T1 T2 );

    const Str s( T1 T2 T3 );

    t = l + s.substr( strlen( T1 ), strlen( T2 ) );
    test( t == T1 T2 );

    t = l + T2;
    test( t == T1 T2 );    
  }

  {
    // operator +  ( const char *, const Str & )

    const Str r( T2 );

    Str t;
    
    t = T1 + r;
    test( t == T1 T2 );
  }

  {
    // operator == ( const SubStr &, const Str & )
    // operator != ( const SubStr &, const Str & )

    const Str l( T1 T2 T3 );
    const Str r( T2 );

    test( l.substr( strlen( T1 ), strlen( T2 ) ) == r );
    test( ! ( l.substr( 0, strlen( T1 ) ) == r ) );

    test( l.substr( 0, strlen( T1 ) ) != r );
    test( ! ( l.substr( strlen( T1 ), strlen( T2 ) ) != r ) );
  }

  {
    // operator == ( const char *, const Str & )
    // operator != ( const char *, const Str & )

    const Str r( T2 );

    test( T2 == r );
    test( ! ( T2 "a" == r ) );

    test( T2 "a" != r );
    test( ! ( T2 != r ) );
  }

  {
    // operator <  ( const SubStr &, const Str & )
    // operator <  ( const char *, const Str & )

    Str t( T2 T3 );
    Str s( T1 T2 T3 T4 );

    test( s.substr( strlen( T1 ), strlen( T2 T3 ) - 1 ) < t );
    test( ! ( s.substr( strlen( T1 ), strlen( T2 T3 ) ) < t ) );

    test( T2 < t );
    test( ! ( T2 T3 < t ) );
  }
  
  {
    // operator >  ( const SubStr &, const Str & )
    // operator >  ( const char *, const Str & )
    
    Str t( T2 T3 );
    Str s( T1 T2 T3 T4 );

    test( s.substr( strlen( T1 ), strlen( T2 T3 ) + 1 ) > t );
    test( ! ( s.substr( strlen( T1 ), strlen( T2 T3 ) ) > t ) );

    test( T2 T3 T4 > t );
    test( ! ( T2 T3 > t ) );
  }

  {
    // operator <= ( const SubStr &, const Str & )
    // operator <= ( const char *, const Str & )

    Str t( T2 T3 );
    Str s( T1 T2 T3 T4 );

    test( s.substr( strlen( T1 ), strlen( T2 T3 ) - 1 ) <= t );
    test( s.substr( strlen( T1 ), strlen( T2 T3 ) ) <= t );
    test( ! ( s.substr( strlen( T1 ), strlen( T2 T3 ) + 1 ) <= t ) );

    test( T2 <= t );
    test( T2 T3 <= t );
    test( ! ( T2 T3 T4 <= t ) );
  }

  {
    // operator >= ( const SubStr &, const Str & )
    // operator >= ( const char *, const Str & )

    Str t( T2 T3 );
    Str s( T1 T2 T3 T4 );

    test( s.substr( strlen( T1 ), strlen( T2 T3 ) + 1 ) >= t );
    test( s.substr( strlen( T1 ), strlen( T2 T3 ) ) >= t );
    test( ! ( s.substr( strlen( T1 ), strlen( T2 T3 ) - 1 ) >= t ) );

    test( T2 T3 T4 >= t );
    test( T2 T3 >= t );
    test( ! ( T2 >= t ) );
  }

  {
    // ::getline( istream &, Str &, char )
    
    Str t( T1 T2 );

    ifstream in( "data/getline.Str.input" );

    test( getline( in, t ).good() );
    test( t == "first line of text" );
    test( getline( in, t, '\n' ).good() );
    test( t == "last line of text" );
    test( ! getline( in, t ).good() );
  }
  
  return( true );
}

    

    

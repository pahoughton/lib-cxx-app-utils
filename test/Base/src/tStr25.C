#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <fstream>
#include <cstring>
#else
#include <TestCfg.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <fstream>
#include <cstring>
#endif



#define T1 "first part"
#define T2 " second part"
#define T3 " third part"
#define T4 " forth part"
#define T5 " fifth part"


bool
tStr25( LibTest & tester )
{
  {
    // operator + ( const Str &, const Str & )
    // operator + ( const Str &, const SubStr & )
    // operator + ( const Str &, const char * )
    
    Str t;

    const Str l( T1 );
    const Str r( T2 );

    t = l + r;
    TEST( t == T1 T2 );

    const Str s( T1 T2 T3 );

    t = l + s.substr( strlen( T1 ), strlen( T2 ) );
    TEST( t == T1 T2 );

    t = l + T2;
    TEST( t == T1 T2 );    
  }

  {
    // operator +  ( const char *, const Str & )

    const Str r( T2 );

    Str t;
    
    t = T1 + r;
    TEST( t == T1 T2 );
  }

  {
    // operator == ( const SubStr &, const Str & )
    // operator != ( const SubStr &, const Str & )

    const Str l( T1 T2 T3 );
    const Str r( T2 );

    TEST( l.substr( strlen( T1 ), strlen( T2 ) ) == r );
    TEST( ! ( l.substr( 0, strlen( T1 ) ) == r ) );

    TEST( l.substr( 0, strlen( T1 ) ) != r );
    TEST( ! ( l.substr( strlen( T1 ), strlen( T2 ) ) != r ) );
  }

  {
    // operator == ( const char *, const Str & )
    // operator != ( const char *, const Str & )

    const Str r( T2 );

    TEST( T2 == r );
    TEST( ! ( T2 "a" == r ) );

    TEST( T2 "a" != r );
    TEST( ! ( T2 != r ) );
  }

  {
    // operator <  ( const SubStr &, const Str & )
    // operator <  ( const char *, const Str & )

    Str t( T2 T3 );
    Str s( T1 T2 T3 T4 );

    TEST( s.substr( strlen( T1 ), strlen( T2 T3 ) - 1 ) < t );
    TEST( ! ( s.substr( strlen( T1 ), strlen( T2 T3 ) ) < t ) );

    TEST( T2 < t );
    TEST( ! ( T2 T3 < t ) );
  }
  
  {
    // operator >  ( const SubStr &, const Str & )
    // operator >  ( const char *, const Str & )
    
    Str t( T2 T3 );
    Str s( T1 T2 T3 T4 );

    TEST( s.substr( strlen( T1 ), strlen( T2 T3 ) + 1 ) > t );
    TEST( ! ( s.substr( strlen( T1 ), strlen( T2 T3 ) ) > t ) );

    TEST( T2 T3 T4 > t );
    TEST( ! ( T2 T3 > t ) );
  }

  {
    // operator <= ( const SubStr &, const Str & )
    // operator <= ( const char *, const Str & )

    Str t( T2 T3 );
    Str s( T1 T2 T3 T4 );

    TEST( s.substr( strlen( T1 ), strlen( T2 T3 ) - 1 ) <= t );
    TEST( s.substr( strlen( T1 ), strlen( T2 T3 ) ) <= t );
    TEST( ! ( s.substr( strlen( T1 ), strlen( T2 T3 ) + 1 ) <= t ) );

    TEST( T2 <= t );
    TEST( T2 T3 <= t );
    TEST( ! ( T2 T3 T4 <= t ) );
  }

  {
    // operator >= ( const SubStr &, const Str & )
    // operator >= ( const char *, const Str & )

    Str t( T2 T3 );
    Str s( T1 T2 T3 T4 );

    TEST( s.substr( strlen( T1 ), strlen( T2 T3 ) + 1 ) >= t );
    TEST( s.substr( strlen( T1 ), strlen( T2 T3 ) ) >= t );
    TEST( ! ( s.substr( strlen( T1 ), strlen( T2 T3 ) - 1 ) >= t ) );

    TEST( T2 T3 T4 >= t );
    TEST( T2 T3 >= t );
    TEST( ! ( T2 >= t ) );
  }

  {
    // ::getline( istream &, Str &, char )
    
    Str t( T1 T2 );
#ifdef SHORT_NAMES
    const char * fn = TESTDATA_PATH "glstr.in";
#else
    const char * fn = TESTDATA_PATH "getline.Str.input";
#endif

    ifstream in( fn );

    TEST( in.good() );

    TEST( getline( in, t ).good() );
    TEST( t == "first line of text" );
    TEST( getline( in, t, '\n' ).good() );
    TEST( t == "last line of text" );
    TEST( ! getline( in, t ).good() );
  }
  
  return( true );
}

    

    

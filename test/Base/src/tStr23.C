#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <functional>
#include <cstring>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <functional>
#include <cstring>
#endif


//           0123456789 123456789 123456789 12345
#define T1  "T1 Test string to test the Str Class"
#define M1  "compare string r"
#define L1  "compare string k"

bool
tStr23( LibTest & tester )
{
  {
    // operator const char * ( void ) const

    const Str t( T1 );

    TEST( strcmp( t, T1 ) == 0 );
  }

  {
    // operator [] ( size_t )

    Str t( "operator [] test." );
    //      0123456789 123456
    
    TEST( t[0UL] == 'o' );
    TEST( t[5UL] == 't' );
    TEST( t[16UL] == '.' );

    t[0UL] = 'O';
    t[5UL] = 'T';
    t[16UL] = '!';
    TEST( t == "OperaTor [] test!" );
    
  }

  {
    // operator [] ( size_t ) const

    const Str t( "operator [] test." );
    //            0123456789 123456
    TEST( t[0UL] == 'o' );
    TEST( t[5UL] == 't' );
    TEST( t[16UL] == '.' );

  }
    
  {
    // operator () ( size_t, size_t )

    Str t( T1 );

    TEST( t.substr( 0,5 ) == t( 0,5 ) );
    TEST( t.substr( 3,6 ).size() == t( 3,6 ).size() );
  }

  {
    // operator () ( size_t, size_t ) const

    const Str t( T1 );

    TEST( t.substr( 0,5 ) == t( 0,5 ) );
    TEST( t.substr( 3,6 ).size() == t( 3,6 ).size() );
  }

  {
    // operator =  ( const Str & src ) - see tStr03
    // operator =  ( const SubStr & ) - see tStr03
    // operator =  ( const char * ) - see tStr03
    // operator =  ( char ) - see tStr03
    // operator += ( const Str & src ) - see tStr02
    // operator += ( const SubStr & ) - see tStr02
    // operator += ( const char * ) - see tStr02
    // operator += ( char ) - see tStr02
    // operator == ( const Str & two ) - see tStr01
    // operator == ( const Str & two ) - see tStr01
    // operator == ( const Str & two ) - see tStr01
    // operator != ( const Str & two ) - see tStr01
    // operator != ( const Str & two ) - see tStr01
    // operator != ( const Str & two ) - see tStr01
  }

  {
    // operator <  ( const Str & ) const
    // operator <  ( const SubStr & ) const
    // operator <  ( const char * ) const

    Str l( L1 );
    Str m( M1 );
    Str ls( "123" L1 "321" );
    Str ms( "123" M1 "321" );

    TEST( l < m );
    TEST( ! ( l < l ) );
    TEST( ! ( m < l ) );

    TEST( l < ms( 3, strlen( M1 ) ) );
    TEST( ! ( l < ls( 3, strlen( L1 ) ) ) );
    TEST( ! ( m < ls( 3, strlen( L1 ) ) ) );

    TEST( l < M1 );
    TEST( ! ( l < L1 ) );
    TEST( ! ( m < L1 ) );
  }

  {
    // operator >  ( const Str & ) const
    // operator >  ( const SubStr & ) const
    // operator >  ( const char * ) const

    
    const Str l( L1 );
    const Str m( M1 );
    const Str ls( "123" L1 "321" );
    const Str ms( "123" M1 "321" );

    TEST( m > l );
    TEST( ! ( m > m ) );
    TEST( ! ( l > m ) );

    TEST( m > ls( 3, strlen( L1 ) ) );
    TEST( ! ( m > ms( 3, strlen( M1 ) ) ) );
    TEST( ! ( l > ms( 3, strlen( M1 ) ) ) );

    TEST( m > L1 );
    TEST( ! ( m > M1 ) );
    TEST( ! ( l > M1 ) );
  }

  {
    // operator <= ( const Str & ) const
    // operator <= ( const SubStr & ) const
    // operator <= ( const char * ) const

    Str l( L1 );
    Str m( M1 );
    Str ls( "123" L1 "321" );
    Str ms( "123" M1 "321" );

    TEST( l <= m );
    TEST( l <= l );
    TEST( ! ( m <= l ) );

    TEST( l <= ms( 3, strlen( M1 ) ) );
    TEST( l <= ls( 3, strlen( L1 ) ) );
    TEST( ! ( m < ls( 3, strlen( L1 ) ) ) );

    TEST( l <= M1 );
    TEST( l <= L1 );
    TEST( ! ( m <= L1 ) );
  }

  {
    // operator >= ( const Str & ) const
    // operator >= ( const SubStr & ) const
    // operator >= ( const char * ) const

    
    Str l( L1 );
    Str m( M1 );
    Str ls( "123" L1 "321" );
    Str ms( "123" M1 "321" );

    TEST( m >= l );
    TEST( m >= m );
    TEST( ! ( l >= m ) );

    TEST( m >= ls( 3, strlen( L1 ) ) );
    TEST( m >= ms( 3, strlen( M1 ) ) );
    TEST( ! ( l > ms( 3, strlen( M1 ) ) ) );

    TEST( m >= L1 );
    TEST( m >= M1 );
    TEST( ! ( l > M1 ) );
  }

  return( true );
}




  

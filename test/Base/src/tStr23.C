#include <LibTest.hh>
#include <Str.hh>

//           0123456789 123456789 123456789 12345
#define T1  "T1 Test string to test the Str Class"
#define M1  "compare string r"
#define L1  "compare string k"

bool
tStr23( LibTest & test )
{
  {
    // operator const char * ( void ) const

    const Str t( T1 );

    test( strcmp( t, T1 ) == 0 );
  }

  {
    // operator [] ( size_t )

    Str t( "operator [] test." );
    //      0123456789 123456
    
    test( t[0] == 'o' );
    test( t[5] == 't' );
    test( t[16] == '.' );

    t[0] = 'O';
    t[5] = 'T';
    t[16] = '!';
    test( t == "OperaTor [] test!" );
    
  }

  {
    // operator [] ( size_t ) const

    const Str t( "operator [] test." );
    //            0123456789 123456
    test( t[0] == 'o' );
    test( t[5] == 't' );
    test( t[16] == '.' );

  }
    
  {
    // operator () ( size_t, size_t )

    Str t( T1 );

    test( t.substr( 0,5 ) == t( 0,5 ) );
    test( t.substr( 3,6 ).size() == t( 3,6 ).size() );
  }

  {
    // operator () ( size_t, size_t ) const

    const Str t( T1 );

    test( t.substr( 0,5 ) == t( 0,5 ) );
    test( t.substr( 3,6 ).size() == t( 3,6 ).size() );
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

    test( l < m );
    test( ! ( l < l ) );
    test( ! ( m < l ) );

    test( l < ms( 3, strlen( M1 ) ) );
    test( ! ( l < ls( 3, strlen( L1 ) ) ) );
    test( ! ( m < ls( 3, strlen( L1 ) ) ) );

    test( l < M1 );
    test( ! ( l < L1 ) );
    test( ! ( m < L1 ) );
  }

  {
    // operator >  ( const Str & ) const
    // operator >  ( const SubStr & ) const
    // operator >  ( const char * ) const

    
    Str l( L1 );
    Str m( M1 );
    Str ls( "123" L1 "321" );
    Str ms( "123" M1 "321" );

    test( m > l );
    test( ! ( m > m ) );
    test( ! ( l > m ) );

    test( m > ls( 3, strlen( L1 ) ) );
    test( ! ( m > ms( 3, strlen( M1 ) ) ) );
    test( ! ( l > ms( 3, strlen( M1 ) ) ) );

    test( m > L1 );
    test( ! ( m > M1 ) );
    test( ! ( l > M1 ) );
  }

  {
    // operator <= ( const Str & ) const
    // operator <= ( const SubStr & ) const
    // operator <= ( const char * ) const

    Str l( L1 );
    Str m( M1 );
    Str ls( "123" L1 "321" );
    Str ms( "123" M1 "321" );

    test( l <= m );
    test( l <= l );
    test( ! ( m <= l ) );

    test( l <= ms( 3, strlen( M1 ) ) );
    test( l <= ls( 3, strlen( L1 ) ) );
    test( ! ( m < ls( 3, strlen( L1 ) ) ) );

    test( l <= M1 );
    test( l <= L1 );
    test( ! ( m <= L1 ) );
  }

  {
    // operator >= ( const Str & ) const
    // operator >= ( const SubStr & ) const
    // operator >= ( const char * ) const

    
    Str l( L1 );
    Str m( M1 );
    Str ls( "123" L1 "321" );
    Str ms( "123" M1 "321" );

    test( m >= l );
    test( m >= m );
    test( ! ( l >= m ) );

    test( m >= ls( 3, strlen( L1 ) ) );
    test( m >= ms( 3, strlen( M1 ) ) );
    test( ! ( l > ms( 3, strlen( M1 ) ) ) );

    test( m >= L1 );
    test( m >= M1 );
    test( ! ( l > M1 ) );
  }

  return( true );
}




  

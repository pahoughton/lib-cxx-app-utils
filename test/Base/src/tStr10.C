#include <LibTest.hh>
#include <Str.hh>
#include <RegexScan.hh>

// Str::iterators

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
tStr10( LibTest & test )
{
  {
    // substr( void )
    // substr( size_t )
    // substr( size_t, size_t )
    // at( size_t, size_t )
    // SubStr::length( void ) const
    // SubStr::size( void ) const
    // SubStr::empty( void ) const
    
    Str t( T1 T2 T3 );

    test( t.substr() == T1 T2 T3 );

    test( t.substr( strlen( T1 ) ) == T2 T3 );

    test( t.substr( 0, strlen( T1 ) ) == T1 );

    test( t.substr( strlen(T1), strlen(T2) ).length() == strlen( T2 ) );

    test( t.substr( strlen(T1), strlen(T2) ).size() == strlen( T2 ) );

    test( t.substr( strlen(T1), strlen(T2) ) ==
	  t.at( strlen(T1), strlen(T2) ) );

    test( t.substr( 0, 0 ).empty() );

  }
  
  {
    // substr( void ) const
    // substr( size_t ) const
    // substr( size_t, size_t ) const
    // at( size_t, size_t ) const
    // SubStr::length( void ) const
    // SubStr::size( void ) const
    // SubStr::empty( void ) const
    
    const Str t( T1 T2 T3 );

    test( t.substr() == T1 T2 T3 );

    test( t.substr( strlen( T1 ) ) == T2 T3 );

    test( t.substr( 0, strlen( T1 ) ) == T1 );

    test( t.substr( strlen(T1), strlen(T2) ).length() == strlen( T2 ) );

    test( t.substr( strlen(T1), strlen(T2) ).size() == strlen( T2 ) );

    test( t.substr( strlen(T1), strlen(T2) ) ==
	  t.at( strlen(T1), strlen(T2) ) );

    test( t.substr( 0, 0 ).empty() );

  }

  {
    // at( const char * )
    // at( const char *, size_t )
    // at( const char *, size_t, size_t )

    Str t( T1 T2 T3 );

    test( t.at( T1 ) == T1 );
    test( t.at( T2 ) == T2 );
    test( t.at( T3 ) == T3 );

    t = T1 T2 T3 T1 T4;
    test( t.at( T1, strlen( T1 T2 ) ) == T1 );
    test( t.at( T1 T2, strlen( T1 T2 ), strlen( T1 ) ) == T1 );

    t.at( T1, strlen( T1 T2 ) ) = T3;
    test( t == T1 T2 T3 T3 T4 );
  }
  
  {
    // at( const char * ) const
    // at( const char *, size_t ) const
    // at( const char *, size_t, size_t ) const

    Str t( T1 T2 T3 );

    test( t.at( T1 ) == T1 );
    test( t.at( T2 ) == T2 );
    test( t.at( T3 ) == T3 );

    t = T1 T2 T3 T1 T4;
    test( t.at( T1, strlen( T1 T2 ) ) == T1 );
    test( t.at( T1 T2, strlen( T1 T2 ), strlen( T1 ) ) == T1 );
  }

  {
    // at( const RegexScan & )
    // at( const RegexScan &, size_t )
    
    RegexScan exp( T2 );
    Str t( T1 T2 T3 );

    test( t.at( exp ) == T2 );

    t = T1 T2 T1 T3;
    exp = T1;
    test( t.at( exp, strlen( T1 T2 ) ) == T1 );

    exp = T2;
    t.at( exp ) = T4;
    test( t == T1 T4 T1 T3 );
  }

  {
    // at( const RegexScan & ) const
    // at( const RegexScan &, size_t ) const
    
    RegexScan exp( T2 );
    Str t( T1 T2 T3 );

    test( t.at( exp ) == T2 );

    t = T1 T2 T1 T3;
    exp = T1;
    test( t.at( exp, strlen( T1 T2 ) ) == T1 );
  }

  {
    // at( const Str & )
    // at( const Str &, size_t )

    Str t( T1 T2 T3 );
    Str pat;

    pat = T1;
    test( t.at( pat ) == T1 );

    t = T1 T2 T3 T1 T4;    
    test( t.at( pat, strlen( T1 T2 ) ) == T1 );

    t.at( pat, strlen( T1 T2 ) ) = T3;
    test( t == T1 T2 T3 T3 T4 );
  }
  
  {
    // at( const Str & )
    // at( const Str &, size_t )

    Str t( T1 T2 T3 );
    Str pat;

    pat = T1;
    test( t.at( pat ) == T1 );

    t = T1 T2 T3 T1 T4;    
    test( t.at( pat, strlen( T1 T2 ) ) == T1 );
  }

  {
    // at( const SubStr & )
    // at( const SubStr &, size_t )

    Str t( T1 T2 T3 );
    Str pat;

    pat = T1 T2;
    test( t.at( pat.substr( 0, strlen( T1 ) ) ) == T1 );

    t = T1 T2 T3 T1 T4;    
    test( t.at( pat.substr( 0, strlen( T1 ) ), strlen( T1 T2 ) ) == T1 );

    t.at( pat.substr( 0, strlen( T1 ) ), strlen( T1 T2 ) ) = T3;
    test( t == T1 T2 T3 T3 T4 );
  }
  
  {
    // at( const SubStr & ) const
    // at( const SubStr &, size_t ) const

    Str t( T1 T2 T3 );
    Str pat;

    pat = T1 T2;
    test( t.at( pat.substr( 0, strlen( T1 ) ) ) == T1 );

    t = T1 T2 T3 T1 T4;    
    test( t.at( pat.substr( 0, strlen( T1 ) ), strlen( T1 T2 ) ) == T1 );
  }
  
  {
    // before( size_t )
    Str t( T1 T2 T3 );

    test( t.before( strlen( T1 T2 ) ) == T1 T2 );
  }

  {
    // before( size_t ) const
    const Str t( T1 T2 T3 );

    test( t.before( strlen( T1 T2 ) ) == T1 T2 );
  }

  {
    // after( size_t )
    Str t( T1 T2 T3 );

    test( t.after( strlen( T1 ) ) == T2 T3 );
  }
  
  {
    // after( size_t ) const
    const Str t( T1 T2 T3 );

    test( t.after( strlen( T1 ) ) == T2 T3 );
  }
  
  return( true );
}

      
    

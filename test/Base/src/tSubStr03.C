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
tSubStr03( LibTest & tester )
{
  {
    // compare( const Str & ) const

    const Str t( T1 T2 T3 T4 );
    const Str s( T1 T2 T3 );

    TEST( t.substr( 0, strlen( T1 T2 T3 ) ).compare( s ) == 0 );
    TEST( t.substr( 0, strlen( T1 T2 ) ).compare( s ) < 0 );
    TEST( t.substr( 0, strlen( T1 T2 T3 ) + 2 ).compare( s ) > 0 );

  }
  
  {
    // compare( const Str, size_t ) const 
    // compare( const Str, size_t, size_t ) const

    const Str ts( T1 T2 T3 T4 T5 );
    Str s;

    const SubStr t( ts( strlen( T1 ), strlen( T2 T3 T4 ) ) );

    s =  T2 T3 T4;
    
    TEST( t.compare( s ) == 0 );

    s += "a";
    TEST( t.compare( s ) < 0 );

    s = T2 T3;    
    TEST( t.compare( s ) > 0 );

    s = T3 T4;
    TEST( t.compare( s, strlen( T2 ) ) == 0 );

    s = T3;
    TEST( t.compare( s, strlen( T2 ), strlen( T3 ) ) == 0 );    
  }
  
  {
    // compare( const SubStr & ) const

    const Str ts( T1 T2 T3 T4 );
    const Str ss( T1 T2 T3 T4 );

    const SubStr t( ts, strlen( T1 ), strlen( T2 T3 ) );

    TEST( t.compare( ss.substr( strlen( T1 ), strlen( T2 T3 ) ) ) == 0 );
    TEST( t.compare( ss.substr( strlen( T1 ), strlen( T2 T3 ) + 1 ) ) < 0 );
    TEST( t.compare( ss.substr( strlen( T1 ), strlen( T2 T3 ) - 1 ) ) > 0 );
  }

  {
    // compare( const SubStr &, size_t ) const
    // compare( const SubStr &, size_t, size_t ) const
    
    const Str ts( T1 T2 T3 T4 );
    const Str ss( T1 T2 T3 T5 );

    const SubStr t( ts, strlen( T1 ), strlen( T2 T3 ) );

    TEST( t.compare( ss.substr( strlen( T1 T2 ), strlen( T3 ) ),
		     strlen( T2 ) ) == 0 );
    TEST( t.compare( ss.substr( strlen( T1 T2 ), strlen( T3 T4 ) ),
		     strlen( T2 ),
		     strlen( T3 ) ) == 0 );
  }
  
  {
    // compare( const char * ) const
    
    Str t( T1 T2 T3 );

    TEST( t.substr( strlen(T1), strlen(T2) ).compare( T2 ) == 0 );
    TEST( t.substr( strlen(T1), strlen(T2) ).compare( T2 "x" ) < 0 );
    TEST( t.substr( strlen(T1), strlen(T2) ).compare( "abc" ) < 0 );
    TEST( t.substr( strlen(T1), strlen(T2) ).compare( " second par" ) > 0 );
    TEST( t.substr( strlen(T1), strlen(T2) ).compare( " recond partxx" ) > 0 );

  }

  {
    // compare( const char *, size_t ) const
    // compare( const char *, size_t, size_t ) const
    

    Str t( T1 T2 T3 T4 T5 );

    TEST( t.substr( 0, strlen( T1 T2 T3 ) ).compare( T2 T3,
						     strlen( T1 ) ) == 0 );
    TEST( t.substr( 0, strlen( T1 T2 T3 ) ).compare( T2 T3 "x",
						     strlen(T1) ) < 0 );
    TEST( t.substr( strlen(T1), strlen(T2) ).compare( T1 " " T2,
						      strlen(T1) ) > 0 );
    TEST( t.substr( 0, strlen( T1 )  ).compare( T3 T1 T3,
						strlen( T3 ),
						strlen( T3 ) ) == 0 );
  }

  {
    // ::compare( const char *, const SubStr & )
    // ::compare( const char *, const SubStr &, size_t )

    const Str	 ts( T1 T2 T3 T4 );
    const SubStr t( ts( strlen( T1 ), strlen( T2 T3 T4 ) ) );

    TEST( compare( T2 T3 T4, t ) == 0 );
    TEST( compare( T2 T3, t ) < 0 );
    TEST( compare( T2 T3 T4 "a", t ) > 0 );

    TEST( compare( T2 T3 T5, t, strlen( T2 T3 ) ) == 0 );
    TEST( compare( T2 T3 "z", t, strlen( T2 T3 ) + 1 ) > 0 );
  }
    
  {
    // fcompare( const Str & ) const

    const Str t( T1 T2 T3 T4 );
    const Str s( T1u T2u T3u );

    TEST( t.substr( 0, strlen( T1 T2 T3 ) ).fcompare( s ) == 0 );
    TEST( t.substr( 0, strlen( T1 T2 ) ).fcompare( s ) < 0 );
    TEST( t.substr( 0, strlen( T1 T2 T3 ) + 2 ).fcompare( s ) > 0 );

  }
  
  {
    // fcompare( const Str, size_t ) const 
    // fcompare( const Str, size_t, size_t ) const

    const Str ts( T1 T2 T3 T4 T5 );
    Str s;

    const SubStr t( ts( strlen( T1 ), strlen( T2 T3 T4 ) ) );

    s =  T2u T3u T4u;
    
    TEST( t.fcompare( s ) == 0 );

    s += "a";
    TEST( t.fcompare( s ) < 0 );

    s = T2 T3;    
    TEST( t.fcompare( s ) > 0 );

    s = T3 T4;
    TEST( t.fcompare( s, strlen( T2 ) ) == 0 );

    s = T3;
    TEST( t.fcompare( s, strlen( T2 ), strlen( T3 ) ) == 0 );    
  }
  
  {
    // fcompare( const SubStr & ) const

    const Str ts( T1u T2u T3u T4u );
    const Str ss( T1 T2 T3 T4 );

    const SubStr t( ts, strlen( T1 ), strlen( T2 T3 ) );

    TEST( t.fcompare( ss.substr( strlen( T1 ), strlen( T2 T3 ) ) ) == 0 );
    TEST( t.fcompare( ss.substr( strlen( T1 ), strlen( T2 T3 ) + 1 ) ) < 0 );
    TEST( t.fcompare( ss.substr( strlen( T1 ), strlen( T2 T3 ) - 1 ) ) > 0 );
  }

  {
    // fcompare( const SubStr &, size_t ) const
    // fcompare( const SubStr &, size_t, size_t ) const
    
    const Str ts( T1u T2u T3u T4u );
    const Str ss( T1 T2 T3 T5 );

    const SubStr t( ts, strlen( T1 ), strlen( T2 T3 ) );

    TEST( t.fcompare( ss.substr( strlen( T1 T2 ), strlen( T3 ) ),
		     strlen( T2 ) ) == 0 );
    TEST( t.fcompare( ss.substr( strlen( T1 T2 ), strlen( T3 T4 ) ),
		     strlen( T2 ),
		     strlen( T3 ) ) == 0 );
  }
  
  {
    // fcompare( const char * ) const
    
    Str t( T1u T2u T3u );

    TEST( t.substr( strlen(T1), strlen(T2) ).fcompare( T2 ) == 0 );
    TEST( t.substr( strlen(T1), strlen(T2) ).fcompare( T2 "x" ) < 0 );
    TEST( t.substr( strlen(T1), strlen(T2) ).fcompare( "abc" ) < 0 );
    TEST( t.substr( strlen(T1), strlen(T2) ).fcompare( " second par" ) > 0 );
    TEST( t.substr( strlen(T1), strlen(T2) ).fcompare( " second partx" ) < 0 );

  }

  {
    // fcompare( const char *, size_t ) const
    // fcompare( const char *, size_t, size_t ) const
    

    Str t( T1u T2u T3 T4 T5 );

    TEST( t.substr( 0, strlen( T1 T2 T3 ) ).fcompare( T2 T3,
						     strlen( T1 ) ) == 0 );
    TEST( t.substr( 0, strlen( T1 T2 T3 ) ).fcompare( T2 T3 "x",
						     strlen(T1) ) < 0 );
    TEST( t.substr( strlen(T1), strlen(T2) ).fcompare( T1 " " T2,
						      strlen(T1) ) > 0 );
    TEST( t.substr( 0, strlen( T1 T2 T3)  ).fcompare( T2 T4,
						      strlen( T1 ),
						      strlen( T2 ) ) == 0 );
  }

  {
    // ::fcompare( const char *, const SubStr & )
    // ::fcompare( const char *, const SubStr &, size_t )

    const Str	 ts( T1u T2u T3u T4u );
    const SubStr t( ts( strlen( T1 ), strlen( T2 T3 T4 ) ) );

    TEST( fcompare( T2 T3 T4, t ) == 0 );
    TEST( fcompare( T2 T3, t ) < 0 );
    TEST( fcompare( T2 T3 T4 "a", t ) > 0 );

    TEST( fcompare( T2 T3 T5, t, strlen( T2 T3 ) ) == 0 );
    TEST( fcompare( T2 T3 "z", t, strlen( T2 T3 ) + 1 ) > 0 );
  }
  
  return( true );
}

  
  

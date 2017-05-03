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
tSubStr06( LibTest & tester )
{
  {
    // ::compare( const SubStr &, const char * )
    // ::compare( const SubStr &, const char *, size_t )

    Str t( T1 T2 T3 T4 );
    
    TEST( compare( t.substr( strlen(T1), strlen( T2 T3 ) ), T2 T3 ) == 0 );
    TEST( compare( t.substr( strlen(T1), strlen( T2 T3 ) + 1), T2 T3 ) > 0 );
    TEST( compare( t.substr( strlen(T1), strlen( T2 T3 ) - 1 ), T2 T3 ) < 0 );
    TEST( compare( t.substr( strlen( T1 ), strlen( T2 ) ), T1 ) < 0 );

    TEST( compare( t.substr( strlen(T1), strlen( T2 T3 ) ),
		   T2 T3 T4,
		   strlen( T2 T3 ) ) == 0 );
    TEST( compare( t.substr( strlen(T1), strlen( T2 T3 ) + 1),
		   T2 T3 T4,
		   strlen( T2 T3 ) ) == 0 );
    TEST( compare( t.substr( strlen(T1), strlen( T2 T3 ) - 1 ),
		   T2 T3 T4,
		   strlen( T2 T3 ) ) < 0 );
     TEST( compare( t.substr( strlen( T1 ), strlen( T2 ) ),
		    T1 T4,
		    strlen( T1 ) ) < 0 );
  }
      
  {
    // ::fcompare( const SubStr &, const char * )
    // ::fcompare( const SubStr &, const char *, size_t )

    Str t( T1 T2 T3 T4 );
    
    TEST( fcompare( t.substr( strlen(T1), strlen( T2 T3 ) ), T2u T3 ) == 0 );
    TEST( fcompare( t.substr( strlen(T1), strlen( T2 T3 ) + 1), T2u T3u ) > 0 );
    TEST( fcompare( t.substr( strlen(T1), strlen( T2 T3 ) - 1 ), T2 T3u ) < 0 );
    TEST( fcompare( t.substr( strlen(T1), strlen( T2 ) ), T1u ) < 0 );

    TEST( fcompare( t.substr( strlen(T1), strlen( T2 T3 ) ),
		   T2u T3 T4,
		   strlen( T2 T3 ) ) == 0 );
    TEST( fcompare( t.substr( strlen(T1), strlen( T2 T3 ) + 1),
		   T2 T3u T4,
		   strlen( T2 T3 ) ) == 0 );
    TEST( fcompare( t.substr( strlen(T1), strlen( T2 T3 ) - 1 ),
		   T2u T3u T4u,
		   strlen( T2 T3 ) ) < 0 );
    TEST( fcompare( t.substr( strlen( T1 ), strlen( T2 ) ),
		    T1u T4,
		    strlen( T1 ) ) < 0 );
  }

  {
    // operator + ( const SubStr &, const Str & )
    // operator + ( const SubStr &, const SubStr & )
    
    Str t;

    const Str	 ls( T1 T2 T3 );
    const SubStr l( ls, 0, strlen( T1 ) );

    const Str	 r( T2 );

    t = l + r;
    TEST( t == T1 T2 );

    const Str s( T1 T2 T3 );

    t = l + s.substr( strlen( T1 ), strlen( T2 ) );
    TEST( t == T1 T2 );
  }

  {
    // operator +  ( const char *, const SubStr & )

    const Str r( T2 T3 );

    Str t;
    
    t = T1 + r( 0, strlen(T2) );
    TEST( t == T1 T2 );
  }

  {
    // operator == ( const char *, const SubStr & )
    // operator != ( const char *, const SubStr & )

    const Str rs( T2 );
    const SubStr r( rs );
    
    TEST( T2 == r );
    TEST( ! ( T2 "a" == r ) );

    TEST( T2 "a" != r );
    TEST( ! ( T2 != r ) );
  }

  {
    // operator <  ( const char *, const SubStr & )

    const Str ts( T1 T2 T3 );
    
    const SubStr t( ts, strlen( T1 ) );

    TEST( T2 < t );
    TEST( ! ( T2 T3 < t ) );
  }
  
  {
    // operator >  ( const char *, const SubStr & )
    
    const Str	 ts( T2 T3 T4);
    const SubStr t( ts, 0, strlen( T2 T3 ) );
    
    TEST( T2 T3 T4 > t );
    TEST( ! ( T2 T3 > t ) );
  }

  {
    // operator <= ( const char *, const SubStr & )

    const Str	    ts( T1 T2 T3 T4);
    const SubStr    t( ts, strlen( T1 ), strlen( T2 T3 ) );
    
    TEST( T2 <= t );
    TEST( T2 T3 <= t );
    TEST( ! ( T2 T3 T4 <= t ) );
  }

  {
    // operator >= ( const char *, const Sub & )

    const Str ts( T2 T3 );
    const SubStr t( ts );
    
    TEST( T2 T3 T4 >= t );
    TEST( T2 T3 >= t );
    TEST( ! ( T2 >= t ) );
  }

  return( true );
}

    

    
    

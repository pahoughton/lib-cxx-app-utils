#include <LibTest.hh>
#include <Str.hh>

#define T1 "first part"
#define T2 " second part"
#define T3 " third part"
#define T4 " forth part"
#define T5 " fifth part"


bool
tSubStr06( LibTest & test )
{
  {
    // operator + ( const SubStr &, const Str & )
    // operator + ( const SubStr &, const SubStr & )
    
    Str t;

    const Str	 ls( T1 T2 T3 );
    const SubStr l( ls, 0, strlen( T1 ) );

    const Str	 r( T2 );

    t = l + r;
    test( t == T1 T2 );

    const Str s( T1 T2 T3 );

    t = l + s.substr( strlen( T1 ), strlen( T2 ) );
    test( t == T1 T2 );
  }

  {
    // operator +  ( const char *, const SubStr & )

    const Str r( T2 T3 );

    Str t;
    
    t = T1 + r( 0, strlen(T2) );
    test( t == T1 T2 );
  }

  {
    // operator == ( const char *, const SubStr & )
    // operator != ( const char *, const SubStr & )

    const Str rs( T2 );
    const SubStr r( rs );
    
    test( T2 == r );
    test( ! ( T2 "a" == r ) );

    test( T2 "a" != r );
    test( ! ( T2 != r ) );
  }

  {
    // operator <  ( const char *, const SubStr & )

    const Str ts( T1 T2 T3 );
    
    const SubStr t( ts, strlen( T1 ) );

    test( T2 < t );
    test( ! ( T2 T3 < t ) );
  }
  
  {
    // operator >  ( const char *, const SubStr & )
    
    const Str	 ts( T2 T3 T4);
    const SubStr t( ts, 0, strlen( T2 T3 ) );
    
    test( T2 T3 T4 > t );
    test( ! ( T2 T3 > t ) );
  }

  {
    // operator <= ( const char *, const SubStr & )

    const Str	    ts( T1 T2 T3 T4);
    const SubStr    t( ts, strlen( T1 ), strlen( T2 T3 ) );
    
    test( T2 <= t );
    test( T2 T3 <= t );
    test( ! ( T2 T3 T4 <= t ) );
  }

  {
    // operator >= ( const char *, const Sub & )

    const Str ts( T2 T3 );
    const SubStr t( ts );
    
    test( T2 T3 T4 >= t );
    test( T2 T3 >= t );
    test( ! ( T2 >= t ) );
  }

  return( true );
}

    

    
    

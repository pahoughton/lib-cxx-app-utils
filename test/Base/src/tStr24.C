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
tStr24( LibTest & test )
{
  {
    // ::compare( const Str &, const Str & )
    // ::compare( const Str &, const Str &, size_t )
    
    Str t( "abcdefg" );
    Str s( "abcdefg" );

    test( compare( t, s ) == 0 );

    s += 'h';
    test( compare( t, s ) < 0 );
    
    t += "hi";

    test( compare( t, s ) > 0 );

    s = "b";

    test( compare( t, s ) < 0 );

    s = "abcdef";
    t = "abcyyydef";
    
    test( compare( t, s, 3 ) == 0 );

  }

  {
    // ::compare( const Str &, const SubStr & )
    // ::compare( const Str &, const SubStr &, size_t )

    Str t( T2 T3 );
    Str s( T1 T2 T3 T4 );

    test( compare( t, s.substr( strlen( T1 ), strlen( T2 T3 ) ) ) == 0 );
    test( compare( t, s.substr( strlen( T1 ), strlen( T2 T3 ) + 1 ) ) < 0 );
    test( compare( t, s.substr( strlen( T1 ), strlen( T2 T3 ) - 1 ) ) > 0 );

    test( compare( t, s.substr( strlen(T1), strlen(T2 T3) ), strlen( T2 ) ) == 0 );
  }

  {
    // ::compare( const Str &, const char * )
    // ::compare( const Str &, const char *, size_t )

    Str t( T1 T2 T3 );

    test( compare( t, T1 T2 T3 ) == 0 );
    test( compare( t, "zz" ) < 0 );
    test( compare( t, "aa" ) > 0 );
    test( compare( t, T1 T2 T3 "a" ) < 0 );
    test( compare( t, T1 T2 ) > 0 );

    test( compare( t, T1 T3, strlen( T1 ) ) == 0 );
  }
  
  {
    // ::fcompare( const Str &, const Str & )
    // ::fcompare( const Str &, const Str &, size_t )

    Str t( "ABCDEFG" );
    Str s( "abcdefg" );

    test( fcompare( t, s ) == 0 );

    s += 'h';
    test( fcompare( t, s ) < 0 );
    
    t += "hi";

    test( fcompare( t, s ) > 0 );

    s = "b";

    test( fcompare( t, s ) < 0 );

    s = "ABCDEF";
    t = "abcyyydef";
    
    test( fcompare( t, s, 3 ) == 0 );

  }

  {
    // ::fcompare( t, const SubStr & )
    // ::fcompare( t, const SubStr &, size_t )
    
    Str t( T2 T3 );
    Str s( T1u T2u T3u T4u );

    test( fcompare( t, s.substr( strlen( T1 ), strlen( T2 T3 ) ) ) == 0 );
    test( fcompare( t, s.substr( strlen( T1 ), strlen( T2 T3 ) + 1 ) ) < 0 );
    test( fcompare( t, s.substr( strlen( T1 ), strlen( T2 T3 ) - 1 ) ) > 0 );

    test( fcompare( t, s.substr( strlen(T1), strlen(T2 T3) ), strlen( T2 ) ) == 0 );
  }

  {
    // ::fcompare( t, const char * ) 
    // ::fcompare( t, const char *, size_t )

    Str t( T1 T2 T3 );

    test( fcompare( t, T1 T2u T3 ) == 0 );
    test( fcompare( t, "zz" ) < 0 );
    test( fcompare( t, "aa" ) > 0 );
    test( fcompare( t, T1u T2u T3u "a" ) < 0 );
    test( fcompare( t, T1 T2 ) > 0 );

    test( fcompare( t, T1u T3, strlen( T1 ) ) == 0 );
  }

  return( true );
}

#if !defined( CLUE_SHORT_FN )
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

// Str::comprare

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
tStr08( LibTest & tester )
{
  {
    // compare( const Str & ) const
    // compare( const Str &, size_t ) const
    // compare( const Str &, size_t, size_t ) const

    Str t( "abcdefg" );
    Str s( "abcdefg" );

    TEST( t.compare( s ) == 0 );

    s += 'h';
    TEST( t.compare( s ) < 0 );
    
    t += "hi";

    TEST( t.compare( s ) > 0 );

    s = "b";

    TEST( t.compare( s ) < 0 );

    s = "abcdef";
    t = "yyyabcdef";
    
    TEST( t.compare( s, 3 ) == 0 );

    t += "yyy";

    TEST( t.compare( s, 3, 6 ) == 0 );

  }

  {
    // compare( const SubStr & ) const
    // compare( const SubStr &, size_t ) const
    // compare( const SubStr &, size_t, size_t ) const

    Str t( T2 T3 );
    Str s( T1 T2 T3 T4 );

    TEST( t.compare( s.substr( strlen( T1 ), strlen( T2 T3 ) ) ) == 0 );
    TEST( t.compare( s.substr( strlen( T1 ), strlen( T2 T3 ) + 1 ) ) < 0 );
    TEST( t.compare( s.substr( strlen( T1 ), strlen( T2 T3 ) - 1 ) ) > 0 );

    TEST( t.compare( s.substr( strlen(T1 T2), strlen(T3) ), strlen( T2 ) ) == 0 );
    TEST( t.compare( s.substr( strlen(T1), strlen(T2 T3 T4) ),
		     0, strlen(T2) ) == 0 );
  }

  {
    // compare( const char * ) const
    // compare( const char *, size_t ) const
    // compare( const char *, size_t, size_t ) const

    Str t( T1 T2 T3 );

    TEST( t.compare( T1 T2 T3 ) == 0 );
    TEST( t.compare( "zz" ) < 0 );
    TEST( t.compare( "aa" ) > 0 );
    TEST( t.compare( T1 T2 T3 "a" ) < 0 );
    TEST( t.compare( T1 T2 ) > 0 );

    TEST( t.compare( T2 T3, strlen( T1 ) ) == 0 );
    TEST( t.compare( T2, strlen(T1), strlen(T2) ) == 0 );
  }

  {
    // ::compare( const SubStr &, const Str & )
    // ::compare( const SubStr &, const Str &, size_t )

    Str t( T2 T3 );
    Str s( T1 T2 T3 T4 );

    TEST( compare( s.substr( strlen( T1 ), strlen( T2 T3 ) ), t ) == 0 );
    TEST( compare( s.substr( strlen( T1 ), strlen( T2 T3 ) + 1 ), t ) > 0 );
    TEST( compare( s.substr( strlen( T1 ), strlen( T2 T3 ) - 1 ), t ) < 0 );

    t = T2 T1;
    TEST( compare( s.substr( strlen(T1), strlen(T2) ), t, strlen( T2 ) )
	  == 0 );
  }
  
  {
    // ::compare( const char *, const Str & ) const
    // ::compare( const char *, const Str & t, size_t ) const

    Str t( T1 T2 T3 );

    TEST( compare( T1 T2 T3, t ) == 0 );
    TEST( compare( "zz", t ) > 0 );
    TEST( compare( "aa", t ) < 0 );
    TEST( compare( T1 T2 T3 "a", t ) > 0 );
    TEST( compare( T1 T2, t ) < 0 );

    TEST( compare( T1 T3, t, strlen( T1 ) ) == 0 );
  }

  {
    // fcompare( const Str & ) const
    // fcompare( const Str &, size_t ) const
    // fcompare( const Str &, size_t, size_t ) const

    Str t( "ABCDEFG" );
    Str s( "abcdefg" );

    TEST( t.fcompare( s ) == 0 );

    s += 'h';
    TEST( t.fcompare( s ) < 0 );
    
    t += "hi";

    TEST( t.fcompare( s ) > 0 );

    s = "b";

    TEST( t.fcompare( s ) < 0 );

    s = "ABCDEF";
    t = "yyyabcdef";
    
    TEST( t.fcompare( s, 3 ) == 0 );

    t += "yyy";

    TEST( t.fcompare( s, 3, 6 ) == 0 );

  }

  {
    // fcompare( const SubStr & ) const
    // fcompare( const SubStr &, size_t ) const
    // fcompare( const SubStr &, size_t, size_t ) const

    Str t( T2 T3 );
    Str s( T1u T2u T3u T4u );

    TEST( t.fcompare( s.substr( strlen( T1 ), strlen( T2 T3 ) ) ) == 0 );
    TEST( t.fcompare( s.substr( strlen( T1 ), strlen( T2 T3 ) + 1 ) ) < 0 );
    TEST( t.fcompare( s.substr( strlen( T1 ), strlen( T2 T3 ) - 1 ) ) > 0 );

    TEST( t.fcompare( s.substr( strlen(T1 T2), strlen(T3) ), strlen( T2 ) ) == 0 );
    TEST( t.fcompare( s.substr( strlen(T1), strlen(T2 T3 T4) ),
		     0, strlen(T2) ) == 0 );
  }

  {
    // fcompare( const char * ) const
    // fcompare( const char *, size_t ) const
    // fcompare( const char *, size_t, size_t ) const

    Str t( T1 T2 T3 );

    TEST( t.fcompare( T1 T2u T3 ) == 0 );
    TEST( t.fcompare( "zz" ) < 0 );
    TEST( t.fcompare( "aa" ) > 0 );
    TEST( t.fcompare( T1u T2u T3u "a" ) < 0 );
    TEST( t.fcompare( T1 T2 ) > 0 );

    TEST( t.fcompare( T2u T3, strlen( T1 ) ) == 0 );
    TEST( t.fcompare( T2u, strlen(T1), strlen(T2) ) == 0 );
  }

  {
    // ::fcompare( const SubStr &, const Str & )
    // ::fcompare( const SubStr &, const Str & size_t )

    Str t( T2 T3 );
    Str s( T1u T2u T3u T4u );

    TEST( fcompare( s.substr( strlen( T1 ), strlen( T2 T3 ) ), t ) == 0 );
    TEST( fcompare( s.substr( strlen( T1 ), strlen( T2 T3 ) + 1 ), t ) > 0 );
    TEST( fcompare( s.substr( strlen( T1 ), strlen( T2 T3 ) - 1 ), t ) < 0 );

    TEST( fcompare( s.substr( strlen(T1), strlen(T2 T3 T4) ), t, strlen(T2) )
	  == 0 );
  }

  {
    // ::fcompare( const char *, const Str & )
    // ::fcompare( const char *, const Str &, size_t )

    Str t( T1 T2 T3 );

    TEST( fcompare( T1 T2u T3, t  ) == 0 );
    TEST( fcompare( "zz", t ) > 0 );
    TEST( fcompare( "aa", t ) < 0 );
    TEST( fcompare( T1u T2u T3u "a", t ) > 0 );
    TEST( fcompare( T1 T2, t ) < 0 );

    TEST( fcompare( T1u T3u, t, strlen(T1) ) == 0 );
  }
  
  return( true );
}


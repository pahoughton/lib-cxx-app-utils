#include <LibTest.hh>
#include <Str.hh>

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
tStr08( LibTest & test )
{
  {
    // compare( const Str & ) const
    // compare( const Str &, size_t ) const
    // compare( const Str &, size_t, size_t ) const

    Str t( "abcdefg" );
    Str s( "abcdefg" );

    test( t.compare( s ) == 0 );

    s += 'h';
    test( t.compare( s ) < 0 );
    
    t += "hi";

    test( t.compare( s ) > 0 );

    s = "b";

    test( t.compare( s ) < 0 );

    s = "abcdef";
    t = "yyyabcdef";
    
    test( t.compare( s, 3 ) == 0 );

    t += "yyy";

    test( t.compare( s, 3, 6 ) == 0 );

  }

  {
    // compare( const SubStr & ) const
    // compare( const SubStr &, size_t ) const
    // compare( const SubStr &, size_t, size_t ) const

    Str t( T2 T3 );
    Str s( T1 T2 T3 T4 );

    test( t.compare( s.substr( strlen( T1 ), strlen( T2 T3 ) ) ) == 0 );
    test( t.compare( s.substr( strlen( T1 ), strlen( T2 T3 ) + 1 ) ) < 0 );
    test( t.compare( s.substr( strlen( T1 ), strlen( T2 T3 ) - 1 ) ) > 0 );

    test( t.compare( s.substr( strlen(T1 T2), strlen(T3) ), strlen( T2 ) ) == 0 );
    test( t.compare( s.substr( strlen(T1), strlen(T2 T3 T4) ),
		     0, strlen(T2) ) == 0 );
  }

  {
    // compare( const char * ) const
    // compare( const char *, size_t ) const
    // compare( const char *, size_t, size_t ) const

    Str t( T1 T2 T3 );

    test( t.compare( T1 T2 T3 ) == 0 );
    test( t.compare( "zz" ) < 0 );
    test( t.compare( "aa" ) > 0 );
    test( t.compare( T1 T2 T3 "a" ) < 0 );
    test( t.compare( T1 T2 ) > 0 );

    test( t.compare( T2 T3, strlen( T1 ) ) == 0 );
    test( t.compare( T2, strlen(T1), strlen(T2) ) == 0 );
  }

  {
    // ::compare( const SubStr &, const Str & )
    // ::compare( const SubStr &, const Str &, size_t )

    Str t( T2 T3 );
    Str s( T1 T2 T3 T4 );

    test( compare( s.substr( strlen( T1 ), strlen( T2 T3 ) ), t ) == 0 );
    test( compare( s.substr( strlen( T1 ), strlen( T2 T3 ) + 1 ), t ) > 0 );
    test( compare( s.substr( strlen( T1 ), strlen( T2 T3 ) - 1 ), t ) < 0 );

    t = T2 T1;
    test( compare( s.substr( strlen(T1), strlen(T2) ), t, strlen( T2 ) )
	  == 0 );
  }
  
  {
    // ::compare( const char *, const Str & ) const
    // ::compare( const char *, const Str & t, size_t ) const

    Str t( T1 T2 T3 );

    test( compare( T1 T2 T3, t ) == 0 );
    test( compare( "zz", t ) > 0 );
    test( compare( "aa", t ) < 0 );
    test( compare( T1 T2 T3 "a", t ) > 0 );
    test( compare( T1 T2, t ) < 0 );

    test( compare( T1 T3, t, strlen( T1 ) ) == 0 );
  }

  {
    // fcompare( const Str & ) const
    // fcompare( const Str &, size_t ) const
    // fcompare( const Str &, size_t, size_t ) const

    Str t( "ABCDEFG" );
    Str s( "abcdefg" );

    test( t.fcompare( s ) == 0 );

    s += 'h';
    test( t.fcompare( s ) < 0 );
    
    t += "hi";

    test( t.fcompare( s ) > 0 );

    s = "b";

    test( t.fcompare( s ) < 0 );

    s = "ABCDEF";
    t = "yyyabcdef";
    
    test( t.fcompare( s, 3 ) == 0 );

    t += "yyy";

    test( t.fcompare( s, 3, 6 ) == 0 );

  }

  {
    // fcompare( const SubStr & ) const
    // fcompare( const SubStr &, size_t ) const
    // fcompare( const SubStr &, size_t, size_t ) const

    Str t( T2 T3 );
    Str s( T1u T2u T3u T4u );

    test( t.fcompare( s.substr( strlen( T1 ), strlen( T2 T3 ) ) ) == 0 );
    test( t.fcompare( s.substr( strlen( T1 ), strlen( T2 T3 ) + 1 ) ) < 0 );
    test( t.fcompare( s.substr( strlen( T1 ), strlen( T2 T3 ) - 1 ) ) > 0 );

    test( t.fcompare( s.substr( strlen(T1 T2), strlen(T3) ), strlen( T2 ) ) == 0 );
    test( t.fcompare( s.substr( strlen(T1), strlen(T2 T3 T4) ),
		     0, strlen(T2) ) == 0 );
  }

  {
    // fcompare( const char * ) const
    // fcompare( const char *, size_t ) const
    // fcompare( const char *, size_t, size_t ) const

    Str t( T1 T2 T3 );

    test( t.fcompare( T1 T2u T3 ) == 0 );
    test( t.fcompare( "zz" ) < 0 );
    test( t.fcompare( "aa" ) > 0 );
    test( t.fcompare( T1u T2u T3u "a" ) < 0 );
    test( t.fcompare( T1 T2 ) > 0 );

    test( t.fcompare( T2u T3, strlen( T1 ) ) == 0 );
    test( t.fcompare( T2u, strlen(T1), strlen(T2) ) == 0 );
  }

  {
    // ::fcompare( const SubStr &, const Str & )
    // ::fcompare( const SubStr &, const Str & size_t )

    Str t( T2 T3 );
    Str s( T1u T2u T3u T4u );

    test( fcompare( s.substr( strlen( T1 ), strlen( T2 T3 ) ), t ) == 0 );
    test( fcompare( s.substr( strlen( T1 ), strlen( T2 T3 ) + 1 ), t ) > 0 );
    test( fcompare( s.substr( strlen( T1 ), strlen( T2 T3 ) - 1 ), t ) < 0 );

    test( fcompare( s.substr( strlen(T1), strlen(T2 T3 T4) ), t, strlen(T2) )
	  == 0 );
  }

  {
    // ::fcompare( const char *, const Str & )
    // ::fcompare( const char *, const Str &, size_t )

    Str t( T1 T2 T3 );

    test( fcompare( T1 T2u T3, t  ) == 0 );
    test( fcompare( "zz", t ) > 0 );
    test( fcompare( "aa", t ) < 0 );
    test( fcompare( T1u T2u T3u "a", t ) > 0 );
    test( fcompare( T1 T2, t ) < 0 );

    test( fcompare( T1u T3u, t, strlen(T1) ) == 0 );
  }
  
  return( true );
}


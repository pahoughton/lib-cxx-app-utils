#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <RegexScan.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#include <RxScan.hh>
#endif

bool
tStr19( LibTest & tester )
{
  {
    // substitute( char, char )
    // substitute( char, char, size_t )
    // substitute( char, char, size_t, bool )

    const char * from = "this is the source string to be changed";
    const char * to   = "xhis is xhe source sxring xo be changed";
    const char * tos  = "this is the source sxring xo be changed";
    const char * tosg = "this is the source sxring to be changed";
    
    Str t( from );

    t.substitute( 't', 'x' );
    TEST( t == to );

    t = from;
    t.substitute( 't', 'x', 10 );
    TEST( t == tos );

    t = from;
    t.substitute( 't', 'x', 10, false );
    TEST( t == tosg );
  }

  {
    // substitute( const char *, const char * )
    // substitute( const char *, const char *, size_t )
    // substitute( const char *, const char *, size_t, bool )

    const char * from  = "this is the string isis getting changed";
    const char * to    = "thwas was the string waswas getting changed";
    const char * tos   = "this is the string waswas getting changed";
    const char * tosg  = "this is the string wasis getting changed";

    Str t( from );

    t.substitute( "is", "was" );
    TEST( t == to );

    t = from;
    t.substitute( "is", "was", 10 );
    TEST( t == tos );

    t = from;
    t.substitute( "is", "was", 10, false );
    TEST( t == tosg );
  }
  
  {
    // substitute( const RegexScan &, const char * )
    // substitute( const RegexScan &, const char *, size_t )
    // substitute( const RegexScan &, const char *, size_t, bool )

    const char * from = "A regex test 123 to test 5 subst 98";
    const char * to   = "A regex test NUM to test NUM subst NUM";
    const char * tos  = "A regex test 123 to test NUM subst NUM";
    const char * tosg = "A regex test 123 to test NUM subst 98";

    const char * tor = "A regex test 5 to test 123 subst 98";

    RegexScan	pat( "[0-9]+" );

    Str t( from );

    t.substitute( pat, "NUM" );
    TEST( t == to );
    t = from;
    t.substitute( pat, "NUM", 18 );
    TEST( t == tos );

    t = from;
    t.substitute( pat, "NUM", 18, false );
    TEST( t == tosg );

    t = from;
    pat = "test ([0-9]+) to test ([0-9]+)";
    t.substitute( pat,"test \\2 to test \\1" );
    TEST( t == tor );
  }

  return( true );
}

  
    

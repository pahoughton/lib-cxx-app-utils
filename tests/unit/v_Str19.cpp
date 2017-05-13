// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/Str.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::Str19");
using namespace clue;


bool
v_Str19( void )
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

    const char * from2 = "if this don''t work, fixem.";
    const char * to2 = "if this don''''''t work, fixem.";

    t = from2;
    t.substitute( "'", "'''" );
    TEST( t == to2 );

  }

  return( verify.is_valid() );
}

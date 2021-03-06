// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/Str.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <cstring>

static valid::verify verify("clue::Str18");
using namespace clue;


bool
v_Str18( void )
{
  {
    // upcase( void )
    Str t;

    const char * from = "this IS a test 123 @!#$% OK?";
    const char * to = "THIS IS A TEST 123 @!#$% OK?";

    t.assign( from );
    t.upcase();
    TEST( t == to );
  }

  {
    // downcase( void )
    Str t;

    const char * from = "THIS IS a tEst 123 @!#$% OK?";
    const char * to =   "this is a test 123 @!#$% ok?";

    t.assign( from );
    t.downcase();
    TEST( t == to );
  }

  {
    // capitalize( void )
    Str t;

    const char * from = "this-is.a test 12a34 abc123 -abc- abc-def? good?";
    const char * to =   "This-Is.A Test 12a34 Abc123 -Abc- Abc-Def? Good?";

    t.assign( from );
    t.capitalize();
    TEST( t == to );
  }

  {
    // strip( const char * )

    Str t;

    {
      // nothing to strip
      const char * from = "do_not_strip_any";
      const char * to = from;

      t.assign( from );
      t.strip( ",. !" );
      TEST( t == to );
    }

    {
      // strip 1 from front
      const char * from = ".this is only a test";
      const char * to = "this is only a test";

      t.assign( from );
      t.strip( ",.!" );
      TEST( t == to );
    }

    {
      // strip a few from the front

      const char * from = ".,.,this is only a test";
      const char * to = "this is only a test";

      t.assign( from );
      t.strip( ",.!" );
      TEST( t == to );
    }

    {
      // strip all

      const char * from = ".a,b.c,,,,abc...";
      const char * to = "";

      t.assign( from );
      t.strip( ",.abc" );
      TEST( t == to );
    }

    {
      // strip 1 from the back

      const char * from = "this is only a test.";
      const char * to = "this is only a test";

      t.assign( from );
      t.strip( ",.!" );
      TEST( t == to );
    }

    {
      // strip a few from the back

      const char * from = "this is only a test..,,";
      const char * to = "this is only a test";

      t.assign( from );
      t.strip( ",.!" );
      TEST( t == to );
    }

    {
      // strip an empty string

      const char * from = "";
      const char * to = "";

      t.assign( from );
      t.strip( ",.!" );
      TEST( t == to );
    }

    {
      // stuff in the middle
      const char * from = "str-ip. (all# pu%nct #$% from-+= me.";
      const char * to   = "strip all punct  from me";

      t.assign( from );
      t.strip( "-.(#%$+=" );
      TEST( t == to );
    }


  }

  {
    // stripLeading( const char * )
    Str t;

    const char * from = "123\t \n   " "strip only leading stuff" " 123   ";
    const char * to   = "strip only leading stuff" " 123   ";

    t.assign( from );
    t.stripLeading( "123 \t\n" );
    TEST( t == to );

  }

  {
    // stripTrailing( const char * )
    Str t;

#define TRAIL_STR "123\t \n   "

    const char * from = "123\t \n   " "strip only trailing stuff" TRAIL_STR;
    const char * to   = "123\t \n   " "strip only trailing stuff";

    t.assign( from );
    TEST( t.stripTrailing( "123 \t\n" ) == strlen( TRAIL_STR ) );
    TEST( t == to );

  }

  {
    // stripEnds( const char * )
    Str t;

    const char * from = "123\t \n   " "strip both ends" "123\t \n   ";
    const char * to   = "strip both ends";

    t.assign( from );
    t.stripEnds( "123 \t\n" );
    TEST( t == to );

  }

  return( verify.is_valid() );
}

#include <LibTest.hh>
#include <Str.hh>

bool
tStr18( LibTest & test )
{
  {
    // upcase( void )
    Str t;

    const char * from = "this IS a test 123 @!#$% OK?";
    const char * to = "THIS IS A TEST 123 @!#$% OK?";

    t.assign( from );
    t.upcase();
    test( t == to );
  }

  {
    // downcase( void )
    Str t;

    const char * from = "THIS IS a tEst 123 @!#$% OK?";
    const char * to =   "this is a test 123 @!#$% ok?";

    t.assign( from );
    t.downcase();
    test( t == to );
  }

  {
    // capitalize( void )
    Str t;

    const char * from = "this-is.a test 12a34 abc123 -abc- abc-def? good?";
    const char * to =   "This-Is.A Test 12a34 Abc123 -Abc- Abc-Def? Good?";

    t.assign( from );
    t.capitalize();
    test( t == to );
  }

  {
    // strip( const char * )

    Str t;

    const char * from = "str-ip. (all# pu%nct #$% from-+= me.";
    const char * to   = "strip all punct  from me";

    t.assign( from );
    t.strip( "-.(#%$+=" );
    test( t == to );
  }

  {
    // stripLeading( const char * )
    Str t;

    const char * from = "123\t \n   " "strip only leading stuff" " 123   ";
    const char * to   = "strip only leading stuff" " 123   ";

    t.assign( from );
    t.stripLeading( "123 \t\n" );
    test( t == to );

  }

  {
    // stripTrailing( const char * )
    Str t;

    const char * from = "123\t \n   " "strip only trailing stuff" "123\t \n   ";
    const char * to   = "123\t \n   " "strip only trailing stuff";

    t.assign( from );
    t.stripTrailing( "123 \t\n" );
    test( t == to );

  }

  {
    // stripEnds( const char * )
    Str t;

    const char * from = "123\t \n   " "strip both ends" "123\t \n   ";
    const char * to   = "strip both ends";

    t.assign( from );
    t.stripEnds( "123 \t\n" );
    test( t == to );

  }

  

  return( true );
}

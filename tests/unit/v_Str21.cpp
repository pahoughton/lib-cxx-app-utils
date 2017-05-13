// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/Str.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::Str10");
using namespace clue;

// Str::scan

bool
v_Str21( void )
{

  {
    // scan( const char * )


    Str t( "this:is : a ; test - it ; is :-; only : a:test" );
    //      0123456789 123456789 123456789 123456789 12345678901234567890

    TEST( t.scan( ":;-" ) == 10 );
    TEST( t.scanMatchStart(0) == 0 );
    TEST( t.scanMatchLength(0) == t.size() );
    TEST( t.scanMatch(1) == "this" );
    TEST( t.scanMatch(2) == "is " );
    TEST( t.scanMatch(3) == " a " );
    TEST( t.scanMatch(4) == " test " );
    TEST( t.scanMatch(5) == " it " );
    TEST( t.scanMatch(6) == " is " );
    TEST( t.scanMatch(7) == " only " );
    TEST( t.scanMatch(8) == " a" );
    TEST( t.scanMatch(9) == "test" );

    TEST( t.scan( "@#$" ) == 1 );

    TEST( t.scan( "@#$:;-" ) == 10 );
    TEST( t.scanMatchStart(0) == 0 );
    TEST( t.scanMatchLength(0) == t.size() );
    TEST( t.scanMatch(1) == "this" );
    TEST( t.scanMatch(2) == "is " );
    TEST( t.scanMatch(3) == " a " );
    TEST( t.scanMatch(4) == " test " );
    TEST( t.scanMatch(5) == " it " );
    TEST( t.scanMatch(6) == " is " );
    TEST( t.scanMatch(7) == " only " );
    TEST( t.scanMatch(8) == " a" );
    TEST( t.scanMatch(9) == "test" );

    t =  "---this:is : a ; test - it ; is :-; only : a:test";
    //    0123456789 123456789 123456789 123456789 12345678901234567890

    TEST( t.scan( ":;-" ) == 10 );
    TEST( t.scanMatchStart(0) == 0 );
    TEST( t.scanMatchLength(0) == t.size() );
    TEST( t.scanMatch(1) == "this" );
    TEST( t.scanMatch(2) == "is " );
    TEST( t.scanMatch(3) == " a " );
    TEST( t.scanMatch(4) == " test " );
    TEST( t.scanMatch(5) == " it " );
    TEST( t.scanMatch(6) == " is " );
    TEST( t.scanMatch(7) == " only " );
    TEST( t.scanMatch(8) == " a" );
    TEST( t.scanMatch(9) == "test" );

  }

  {
    // scan( const char *, bool )

    Str t( "this,is,,a,test,,of,scan.");

    TEST( t.scan( "," ) == 7 );
    TEST( t.scanMatch(1) == "this" );
    TEST( t.scanMatch(2) == "is" );
    TEST( t.scanMatch(3) == "a" );
    TEST( t.scanMatch(4) == "test" );
    TEST( t.scanMatch(5) == "of" );
    TEST( t.scanMatch(6) == "scan." );
    TEST( t.scan( ",", true ) == 7 );
    TEST( t.scanMatch(1) == "this" );
    TEST( t.scanMatch(2) == "is" );
    TEST( t.scanMatch(3) == "a" );
    TEST( t.scanMatch(4) == "test" );
    TEST( t.scanMatch(5) == "of" );
    TEST( t.scanMatch(6) == "scan." );
    TEST( t.scan( ",", false ) == 9 );
    TEST( t.scanMatch(1) == "this" );
    TEST( t.scanMatch(2) == "is" );
    TEST( t.scanMatch(3) == "" );
    TEST( t.scanMatch(4) == "a" );
    TEST( t.scanMatch(5) == "test" );
    TEST( t.scanMatch(6) == "" );
    TEST( t.scanMatch(7) == "of" );
    TEST( t.scanMatch(8) == "scan." );

  }

  {
    // scan( const char *, bool, size_t )

    Str t( "this:is : a ; test - it ; is :-; only : a:test" );

    TEST( t.scan( "@#$:;-", true, 13 ) == 7 );
    TEST( t.scanMatchStart(0) == 13 );
    TEST( t.scanMatchLength(0) == t.size() - 13 );
    TEST( t.scanMatch(1) == " test " );
    TEST( t.scanMatch(2) == " it " );
    TEST( t.scanMatch(3) == " is " );
    TEST( t.scanMatch(4) == " only " );
    TEST( t.scanMatch(5) == " a" );
    TEST( t.scanMatch(6) == "test" );

  }

  {
    // scan( const Str & )

    Str t( "this:is : a ; test - it ; is :-; only : a:test" );
    //      0123456789 123456789 123456789 123456789 12345678901234567890

    Str d( ":;-" );
    TEST( t.scan( d ) == 10 );
    TEST( t.scanMatchStart(0) == 0 );
    TEST( t.scanMatchLength(0) == t.size() );
    TEST( t.scanMatch(1) == "this" );
    TEST( t.scanMatch(2) == "is " );
    TEST( t.scanMatch(3) == " a " );
    TEST( t.scanMatch(4) == " test " );
    TEST( t.scanMatch(5) == " it " );
    TEST( t.scanMatch(6) == " is " );
    TEST( t.scanMatch(7) == " only " );
    TEST( t.scanMatch(8) == " a" );
    TEST( t.scanMatch(9) == "test" );

    d = "@#$";
    TEST( t.scan( d ) == 1 );

    d = "@#$:;-";
    TEST( t.scan( d ) == 10 );
    TEST( t.scanMatchStart(0) == 0 );
    TEST( t.scanMatchLength(0) == t.size() );
    TEST( t.scanMatch(1) == "this" );
    TEST( t.scanMatch(2) == "is " );
    TEST( t.scanMatch(3) == " a " );
    TEST( t.scanMatch(4) == " test " );
    TEST( t.scanMatch(5) == " it " );
    TEST( t.scanMatch(6) == " is " );
    TEST( t.scanMatch(7) == " only " );
    TEST( t.scanMatch(8) == " a" );
    TEST( t.scanMatch(9) == "test" );

    t =  "---this:is : a ; test - it ; is :-; only : a:test";
    //    0123456789 123456789 123456789 123456789 12345678901234567890

    d = ":;-";

    TEST( t.scan( d ) == 10 );
    TEST( t.scanMatchStart(0) == 0 );
    TEST( t.scanMatchLength(0) == t.size() );
    TEST( t.scanMatch(1) == "this" );
    TEST( t.scanMatch(2) == "is " );
    TEST( t.scanMatch(3) == " a " );
    TEST( t.scanMatch(4) == " test " );
    TEST( t.scanMatch(5) == " it " );
    TEST( t.scanMatch(6) == " is " );
    TEST( t.scanMatch(7) == " only " );
    TEST( t.scanMatch(8) == " a" );
    TEST( t.scanMatch(9) == "test" );

  }

  {
    // scan( const Str &, bool, size_t )

    Str t( "this:is : a ; test - it ; is :-; only : a:test" );
    //      0123456789 123456789 123456789 123456789 12345678901234567890

    Str d( "@#$:;-" );
    TEST( t.scan( d, true, 13 ) == 7 );
    TEST( t.scanMatchStart(0) == 13 );
    TEST( t.scanMatchLength(0) == t.size() - 13 );
    TEST( t.scanMatch(1) == " test " );
    TEST( t.scanMatch(2) == " it " );
    TEST( t.scanMatch(3) == " is " );
    TEST( t.scanMatch(4) == " only " );
    TEST( t.scanMatch(5) == " a" );
    TEST( t.scanMatch(6) == "test" );

  }

  {
    // scan( char )

    Str t( "this:is : a ; test - it ; is :-; only : a:test" );
    //      0123456789 123456789 123456789 123456789 12345678901234567890

    TEST( t.scan( ':' ) == 7 );
    TEST( t.scanMatchStart(0) == 0 );
    TEST( t.scanMatchLength(0) == t.size() );
    TEST( t.scanMatch(1) == "this" );
    TEST( t.scanMatch(2) == "is " );
    TEST( t.scanMatch(3) == " a ; test - it ; is " );
    TEST( t.scanMatch(4) == "-; only " );
    TEST( t.scanMatch(5) == " a" );
    TEST( t.scanMatch(6) == "test" );

  }

  {
    // scan( char, size_t )

    Str t( "this:is : a ; test - it ; is :-; only : a:test" );
    //      0123456789 123456789 123456789 123456789 12345678901234567890

    TEST( t.scan( ':', true, 13 ) == 5 );
    TEST( t.scanMatchStart(0) == 13 );
    TEST( t.scanMatchLength(0) == t.size() - 13 );
    TEST( t.scanMatch(1) == " test - it ; is " );
    TEST( t.scanMatch(2) == "-; only " );
    TEST( t.scanMatch(3) == " a" );
    TEST( t.scanMatch(4) == "test" );
  }
  {
    // scan( const char *   quoteChars,
    //	     char	    escChar,
    //	     const char *   delimChars,
    //	     bool	    multiDelim,
    //	     size_type	    start )
    //

    Str	t( "'this is, a test',1234,\\'abc\\',\"more testing\"" );

    // cout << '\n' << t << endl;

    TEST( t.scan( "'", '\\', ",", false, 0 ) == 5 );
    TEST( t.scanMatch( 0 ) == t );
    TEST( t.scanMatch( 1 ) == "this is, a test" );
    TEST( t.scanMatch( 2 ) == "1234" );
    TEST( t.scanMatch( 3 ) == "'abc'" );
    TEST( t.scanMatch( 4 ) == "\"more testing\"" );

  }

  {
    // scanString( const char * )

    Str t( "ThisDELIM is a testDELIMitDELIM might work" );

    TEST( t.scanString( "DELIM" ) == 5 );
    TEST( t.scanMatchStart(0) == 0 );
    TEST( t.scanMatchLength(0) == t.size() );
    TEST( t.scanMatch(1) == "This" );
    TEST( t.scanMatch(2) == " is a test" );
    TEST( t.scanMatch(3) == "it" );
    TEST( t.scanMatch(4) == " might work" );
  }

  return( verify.is_valid() );
}

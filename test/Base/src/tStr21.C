#if !defined( STLUTILS_SHORT_FN )
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

// Str::scan

bool
tStr21( LibTest & tester )
{
  {
    // scan( const RegexScan & )
    // scan( const RegexScan &, size_t )
    // scanMatchCount( void ) const
    // scanMatchStart( void ) const
    // scanMatchLength( void ) const
    // scanMatch( size_t )
    
    RegexScan e( "is .+ test" );

    Str t( "This is a test it is only a test no other value implied" );
    //      0123456789 123456789 123456789 123456789 12345678901234567890
    
    TEST( t.scan( e ) );

    TEST( t.scanMatchCount() == 1 );
    TEST( t.scanMatchStart() == 2 );
    TEST( t.scanMatchLength() == 32 - 2 );
    TEST( t.scanMatch( 0 ) == "is is a test it is only a test" );

    TEST( t.scan( e, 6 ) );
    TEST( t.scanMatchCount() == 1 );
    TEST( t.scanMatchStart() == 18 );
    TEST( t.scanMatchLength() == 32 - 18 );
    TEST( t.scanMatch( 0 ) == "is only a test" );

    
    t = "This! isn't a test that will be true";

    TEST( ! t.scan(e) );
    TEST( t.scanMatchCount() == 0 );
  }

  {
    // register tests
    // scanMatchStart( size_t ) const
    // scanMatchLength( size_t ) const
    
    RegexScan re(":(.+): to t(e*)st ([[:digit:]]+) [a-z ]+ [A-Z]{3}.+ ([a-z]+)$");

    Str t( "a :string: to tst 1234 regist and THE the scanner" );
    //      0123456789 123456789 123456789 123456789 12345678901234567890

    TEST( t.scan( re ) == 5 );
    TEST( t.scanMatch(0) == ":string: to tst 1234 regist and THE the scanner" );
    TEST( t.scanMatch(1) == "string" );
    TEST( t.scanMatchStart(2) == 15 );
    TEST( t.scanMatchLength(2) == 0 );
    TEST( t.scanMatch(3) == "1234" );
    TEST( t.scanMatch(4) == "scanner" );

    t.scanMatch(3) = "no more numbers";
    TEST( t == "a :string: to tst no more numbers regist and THE the scanner" );
  }

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
    // scanPattern( const RegexScan & )
    
    Str t( "this12is9a test32467it is 98. only a0test" );
    //      0123456789 123456789 123456789 123456789 12345678901234567890

    RegexScan exp( "[0-9]+" );

    TEST( t.scanPattern( exp ) == 7 );
    TEST( t.scanMatchStart(0) == 0 );
    TEST( t.scanMatchLength(0) == t.size() );
    TEST( t.scanMatch(1) == "this" );
    TEST( t.scanMatch(2) == "is" );
    TEST( t.scanMatch(3) == "a test" );
    TEST( t.scanMatch(4) == "it is " );
    TEST( t.scanMatch(5) == ". only a" );
    TEST( t.scanMatch(6) == "test" );

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
    
  return( true );
}
    
    
    

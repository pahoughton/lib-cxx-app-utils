#include <LibTest.hh>
#include <Str.hh>
#include <RegexScan.hh>

// Str::scan

bool
tStr21( LibTest & test )
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
    
    test( t.scan( e ) );

    test( t.scanMatchCount() == 1 );
    test( t.scanMatchStart() == 2 );
    test( t.scanMatchLength() == 32 - 2 );
    test( t.scanMatch( 0 ) == "is is a test it is only a test" );

    test( t.scan( e, 6 ) );
    test( t.scanMatchCount() == 1 );
    test( t.scanMatchStart() == 18 );
    test( t.scanMatchLength() == 32 - 18 );
    test( t.scanMatch( 0 ) == "is only a test" );

    
    t = "This! isn't a test that will be true";

    test( ! t.scan(e) );
    test( t.scanMatchCount() == 0 );
  }

  {
    // register tests
    // scanMatchStart( size_t ) const
    // scanMatchLength( size_t ) const
    
    RegexScan re(":(.+): to t(e*)st ([[:digit:]]+) [a-z ]+ [A-Z]{3}.+ ([a-z]+)$");

    Str t( "a :string: to tst 1234 regist and THE the scanner" );
    //      0123456789 123456789 123456789 123456789 12345678901234567890

    test( t.scan( re ) == 5 );
    test( t.scanMatch(0) == ":string: to tst 1234 regist and THE the scanner" );
    test( t.scanMatch(1) == "string" );
    test( t.scanMatchStart(2) == 15 );
    test( t.scanMatchLength(2) == 0 );
    test( t.scanMatch(3) == "1234" );
    test( t.scanMatch(4) == "scanner" );

    t.scanMatch(3) = "no more numbers";
    test( t == "a :string: to tst no more numbers regist and THE the scanner" );
  }

  {
    // scan( const char * )
    // scan( const char *, size_t )
    

    Str t( "this:is : a ; test - it ; is :-; only : a:test" );
    //      0123456789 123456789 123456789 123456789 12345678901234567890

    test( t.scan( ":;-" ) == 10 );
    test( t.scanMatchStart(0) == 0 );
    test( t.scanMatchLength(0) == t.size() );
    test( t.scanMatch(1) == "this" );
    test( t.scanMatch(2) == "is " );
    test( t.scanMatch(3) == " a " );
    test( t.scanMatch(4) == " test " );
    test( t.scanMatch(5) == " it " );
    test( t.scanMatch(6) == " is " );
    test( t.scanMatch(7) == " only " );
    test( t.scanMatch(8) == " a" );
    test( t.scanMatch(9) == "test" );

    test( t.scan( "@#$" ) == 1 );
    
    test( t.scan( "@#$:;-" ) == 10 );
    test( t.scanMatchStart(0) == 0 );
    test( t.scanMatchLength(0) == t.size() );
    test( t.scanMatch(1) == "this" );
    test( t.scanMatch(2) == "is " );
    test( t.scanMatch(3) == " a " );
    test( t.scanMatch(4) == " test " );
    test( t.scanMatch(5) == " it " );
    test( t.scanMatch(6) == " is " );
    test( t.scanMatch(7) == " only " );
    test( t.scanMatch(8) == " a" );
    test( t.scanMatch(9) == "test" );
    
    test( t.scan( "@#$:;-",13 ) == 7 );
    test( t.scanMatchStart(0) == 13 );
    test( t.scanMatchLength(0) == t.size() - 13 );
    test( t.scanMatch(1) == " test " );
    test( t.scanMatch(2) == " it " );
    test( t.scanMatch(3) == " is " );
    test( t.scanMatch(4) == " only " );
    test( t.scanMatch(5) == " a" );
    test( t.scanMatch(6) == "test" );
    
    t =  "---this:is : a ; test - it ; is :-; only : a:test";
    //    0123456789 123456789 123456789 123456789 12345678901234567890

    test( t.scan( ":;-" ) == 10 );
    test( t.scanMatchStart(0) == 0 );
    test( t.scanMatchLength(0) == t.size() );
    test( t.scanMatch(1) == "this" );
    test( t.scanMatch(2) == "is " );
    test( t.scanMatch(3) == " a " );
    test( t.scanMatch(4) == " test " );
    test( t.scanMatch(5) == " it " );
    test( t.scanMatch(6) == " is " );
    test( t.scanMatch(7) == " only " );
    test( t.scanMatch(8) == " a" );
    test( t.scanMatch(9) == "test" );

  }
  
  {
    // scan( const Str & )
    // scan( const Str &, size_t )

    Str t( "this:is : a ; test - it ; is :-; only : a:test" );
    //      0123456789 123456789 123456789 123456789 12345678901234567890

    Str d( ":;-" );
    test( t.scan( d ) == 10 );
    test( t.scanMatchStart(0) == 0 );
    test( t.scanMatchLength(0) == t.size() );
    test( t.scanMatch(1) == "this" );
    test( t.scanMatch(2) == "is " );
    test( t.scanMatch(3) == " a " );
    test( t.scanMatch(4) == " test " );
    test( t.scanMatch(5) == " it " );
    test( t.scanMatch(6) == " is " );
    test( t.scanMatch(7) == " only " );
    test( t.scanMatch(8) == " a" );
    test( t.scanMatch(9) == "test" );

    d = "@#$";
    test( t.scan( d ) == 1 );

    d = "@#$:;-";
    test( t.scan( d ) == 10 );
    test( t.scanMatchStart(0) == 0 );
    test( t.scanMatchLength(0) == t.size() );
    test( t.scanMatch(1) == "this" );
    test( t.scanMatch(2) == "is " );
    test( t.scanMatch(3) == " a " );
    test( t.scanMatch(4) == " test " );
    test( t.scanMatch(5) == " it " );
    test( t.scanMatch(6) == " is " );
    test( t.scanMatch(7) == " only " );
    test( t.scanMatch(8) == " a" );
    test( t.scanMatch(9) == "test" );

    d = "@#$:;-";
    test( t.scan( d, 13 ) == 7 );
    test( t.scanMatchStart(0) == 13 );
    test( t.scanMatchLength(0) == t.size() - 13 );
    test( t.scanMatch(1) == " test " );
    test( t.scanMatch(2) == " it " );
    test( t.scanMatch(3) == " is " );
    test( t.scanMatch(4) == " only " );
    test( t.scanMatch(5) == " a" );
    test( t.scanMatch(6) == "test" );
    
    t =  "---this:is : a ; test - it ; is :-; only : a:test";
    //    0123456789 123456789 123456789 123456789 12345678901234567890

    d = ":;-";
    
    test( t.scan( d ) == 10 );
    test( t.scanMatchStart(0) == 0 );
    test( t.scanMatchLength(0) == t.size() );
    test( t.scanMatch(1) == "this" );
    test( t.scanMatch(2) == "is " );
    test( t.scanMatch(3) == " a " );
    test( t.scanMatch(4) == " test " );
    test( t.scanMatch(5) == " it " );
    test( t.scanMatch(6) == " is " );
    test( t.scanMatch(7) == " only " );
    test( t.scanMatch(8) == " a" );
    test( t.scanMatch(9) == "test" );

  }

  {
    // scan( char )
    // scan( char, size_t )
    Str t( "this:is : a ; test - it ; is :-; only : a:test" );
    //      0123456789 123456789 123456789 123456789 12345678901234567890

    test( t.scan( ':' ) == 7 );
    test( t.scanMatchStart(0) == 0 );
    test( t.scanMatchLength(0) == t.size() );
    test( t.scanMatch(1) == "this" );
    test( t.scanMatch(2) == "is " );
    test( t.scanMatch(3) == " a ; test - it ; is " );
    test( t.scanMatch(4) == "-; only " );
    test( t.scanMatch(5) == " a" );
    test( t.scanMatch(6) == "test" );

    test( t.scan( ':', 13 ) == 5 );
    test( t.scanMatchStart(0) == 13 );
    test( t.scanMatchLength(0) == t.size() - 13 );
    test( t.scanMatch(1) == " test - it ; is " );
    test( t.scanMatch(2) == "-; only " );
    test( t.scanMatch(3) == " a" );
    test( t.scanMatch(4) == "test" );

  }

  {
    // scanPattern( const RegexScan & )
    
    Str t( "this12is9a test32467it is 98. only a0test" );
    //      0123456789 123456789 123456789 123456789 12345678901234567890

    RegexScan exp( "[0-9]+" );

    test( t.scanPattern( exp ) == 7 );
    test( t.scanMatchStart(0) == 0 );
    test( t.scanMatchLength(0) == t.size() );
    test( t.scanMatch(1) == "this" );
    test( t.scanMatch(2) == "is" );
    test( t.scanMatch(3) == "a test" );
    test( t.scanMatch(4) == "it is " );
    test( t.scanMatch(5) == ". only a" );
    test( t.scanMatch(6) == "test" );

  }

  {
    // scanString( const char * )
    
    Str t( "ThisDELIM is a testDELIMitDELIM might work" );

    test( t.scanString( "DELIM" ) == 5 );
    test( t.scanMatchStart(0) == 0 );
    test( t.scanMatchLength(0) == t.size() );
    test( t.scanMatch(1) == "This" );
    test( t.scanMatch(2) == " is a test" );
    test( t.scanMatch(3) == "it" );
    test( t.scanMatch(4) == " might work" );
  }
    
  
    
  return( true );
}
    
    
    

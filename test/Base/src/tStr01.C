#include <LibTest.hh>
#include <Str.hh>

#include <vector>
#include <set>
#include <functional>

static const char * Tstr = "This is a test it is only at test ...";
static const char * TstrJunk = "This is a test it is only at test ... with Junk";

bool
tStr01( LibTest & test )
{
  {
    // Str( void ) const
    // size( void ) const
    // length( void ) const
    // empty( void ) const
    // max_size( void ) const
    // cstr( void ) const
    // operator == ( const char * )
    // operator != ( const char * )
    
    Str t;
    
    test( t.size() == 0 );
    test( t.length() == t.size() );
    test( t.empty() );
    test( t.max_size() > 0 );
    
    t << Tstr;

    test( ! strcmp( t.cstr(), Tstr ) );
    test( strcmp( t.cstr(), "diff string" ) );
    test( t.size() == strlen( Tstr ) );
    test( t.length() == t.size() );
    test( ! t.empty() );
    
    // Test operator == next so I can use it for the rest of the tests

    test( t == Tstr );
    test( ! (t == "diff string" ) );
    test( ! ( t != Tstr ) );
    test( t != "diff string" );    
  }

  {
    // Str( const Str & )
    // operator == ( const Str & ) const
    // operator != ( const Str & ) const
    
    Str s;

    s << Tstr;
    
    Str t( s );

    test( s == Tstr );
    test( t == Tstr );
    test( t == s );
    test( ! (t != s) );

    Str x;

    x << "diff string";

    test( t != x );
    test( ! (t == x) );
  }

  {
    // Str( const Str &, size_t )

    Str s;

    s << "123" << Tstr;

    test( ! (s == Tstr) );

    Str t( s, 3 );

    test( t == Tstr );
    test( ! (t == s) );
  }

  {
    // Str( const Str &, size_t, size_t )

    Str s;

    s << "123" << Tstr << "junk";

    Str t( s, 3, strlen( Tstr ) );

    test( t == Tstr );
    test( ! (t == s) );
  }

  // 
  // need to test substr now so it can be used by the
  // other test.
  //
  
  {
    // substr( size_t, size_t )
    // SubStr::operator == ( const char * ) const
    // SubStr::operator != ( const char * ) const
    // operator == ( const SubStr & ) const
    // operator != ( const SubStr & ) const

    Str t;

    t << "123" << Tstr << "junk";

    test( t.substr( 3, strlen( Tstr ) ) == Tstr );
    test( t.substr( 3, strlen( Tstr ) ) != "diff string" );

    Str s;

    s << Tstr;

    test( s == t.substr( 3, strlen( Tstr ) ) );
    test( s != t.substr( 2, strlen( Tstr ) ) );
    test( s != t.substr( 3, strlen( Tstr ) + 1 ) );
    test( s != t.substr( 4, strlen( Tstr ) ) );
    test( s != t.substr( 3, strlen( Tstr ) - 1 ) );
    

  }
  
  {
    // Str( const SubStr & )

    Str s;

    s << "123" << Tstr << "junk";

    Str t( s.substr( 3, strlen( Tstr ) ) );

    test( t == Tstr );
    test( ! (t == s) );

  }
  
  {
    // Str( const SubStr &, size_t )

    Str s;

    s << "123" << "12345" << Tstr << "junk";

    Str t( s.substr( 3, strlen( Tstr ) + 5 ), 5 );

    test( t == Tstr );
    test( ! (t == s) );

  }
  
  {
    // Str( const SubStr &, size_t, size_t )

    Str s;

    s << "123" << "12345" << Tstr << "junk" << " more junk ";

    Str t( s.substr( 3, strlen( Tstr ) + 5 + 10 ), 5, strlen( Tstr ) );

    test( t == Tstr );
    test( ! (t == s) );

  }

  {
    // Str( const char * )
    
    Str t( Tstr );

    test( t == Tstr );
  }

  {
    // Str( const char *, size_t )
    
    Str t( TstrJunk, strlen( Tstr ) );

    test( t == Tstr );
  }

  {
    // Str( size_t, char )
    
    Str t( 5, 'x' );

    test( t == "xxxxx" );
  }

  {
    // Str( InputIterator, InputIterator )

    Str t( Tstr, Tstr + strlen( Tstr ) );

    test( t == Tstr );
  }
  
  {
    // verify support for stl vector<> & set<>

    // vector< Str >
    // less< Str >
    // set< Str >
    
    //    vector< Str > tV;
    //    set< Str, less< Str > > tS;

  }

  return( true );
}

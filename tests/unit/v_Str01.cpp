// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/Str.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <vector>
#include <set>
#include <string>
#include <functional>
#include <cstring>

static valid::verify verify("clue::Str01");
using namespace clue;


static const char * Tstr = "This is a test it is only at test ...";
static const char * TstrJunk = "This is a test it is only at test ... with Junk";

bool
v_Str01( void )
{
  {
    // Str( void ) const
    // good( void ) const
    // reset( void )
    // size( void ) const
    // length( void ) const
    // empty( void ) const
    // max_size( void ) const
    // cstr( void ) const
    // operator == ( const char * )
    // operator != ( const char * )

    Str t;

    TEST( t.good() );
    t.reset();
    TEST( t.good() );

    TEST( t.size() == 0 );
    TEST( t.length() == t.size() );
    TEST( t.empty() );
    TEST( t.max_size() > 0 );
    TEST( t.good() );

    t << Tstr;

    TEST( t.good() );
    TEST( ! strcmp( t.cstr(), Tstr ) );
    TEST( strcmp( t.cstr(), "diff string" ) );
    TEST( t.size() == strlen( Tstr ) );
    TEST( t.length() == t.size() );
    TEST( ! t.empty() );
    TEST( t.good() );

    // Test operator == next so I can use it for the rest of the tests

    TEST( t == Tstr );
    TEST( ! (t == "diff string" ) );
    TEST( ! ( t != Tstr ) );
    TEST( t != "diff string" );
    TEST( t.good() );
  }

  {
    // Str( const Str & )
    // operator == ( const Str & ) const
    // operator != ( const Str & ) const

    Str s;

    s << Tstr;

    Str t( s );

    TEST( s == Tstr );
    TEST( t == Tstr );
    TEST( t == s );
    TEST( ! (t != s) );

    Str x;

    x << "diff string";

    TEST( t != x );
    TEST( ! (t == x) );
  }

  {
    // Str( const Str &, size_t )

    Str s;

    s << "123" << Tstr;

    TEST( ! (s == Tstr) );

    Str t( s, 3 );

    TEST( t == Tstr );
    TEST( ! (t == s) );
  }

  {
    // Str( const Str &, size_t, size_t )

    Str s;

    s << "123" << Tstr << "junk";

    Str t( s, 3, strlen( Tstr ) );

    TEST( t == Tstr );
    TEST( ! (t == s) );
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

    TEST( t.substr( 3, strlen( Tstr ) ) == Tstr );
    TEST( t.substr( 3, strlen( Tstr ) ) != "diff string" );

    Str s;

    s << Tstr;

    TEST( s == t.substr( 3, strlen( Tstr ) ) );
    TEST( s != t.substr( 2, strlen( Tstr ) ) );
    TEST( s != t.substr( 3, strlen( Tstr ) + 1 ) );
    TEST( s != t.substr( 4, strlen( Tstr ) ) );
    TEST( s != t.substr( 3, strlen( Tstr ) - 1 ) );


  }

  {
    // Str( const SubStr & )

    Str s;

    s << "123" << Tstr << "junk";

    Str t( s.substr( 3, strlen( Tstr ) ) );

    TEST( t == Tstr );
    TEST( ! (t == s) );

  }

  {
    // Str( const std::string & )

    std::string s("test std::string");

    Str t(s);
    TEST( t == s );
    TEST( strcmp( t.c_str(), s.c_str() ) == 0 );
  }

  {
    // Str( const SubStr &, size_t )

    Str s;

    s << "123" << "12345" << Tstr << "junk";

    Str t( s.substr( 3, strlen( Tstr ) + 5 ), 5 );

    TEST( t == Tstr );
    TEST( ! (t == s) );

  }

  {
    // Str( const SubStr &, size_t, size_t )

    Str s;

    s << "123" << "12345" << Tstr << "junk" << " more junk ";

    Str t( s.substr( 3, strlen( Tstr ) + 5 + 10 ), 5, strlen( Tstr ) );

    TEST( t == Tstr );
    TEST( ! (t == s) );

  }

  {
    // Str( const char * )

    Str t( Tstr );

    TEST( t == Tstr );
  }

  {
    // Str( const char *, size_t )

    Str t( TstrJunk, strlen( Tstr ) );

    TEST( t == Tstr );
  }

  {
    // Str( size_t, char )

    Str t( 5, 'x' );

    TEST( t == "xxxxx" );
  }

  {
    // Str( InputIterator, InputIterator )

    Str t( Tstr, Tstr + strlen( Tstr ) );

    TEST( t == Tstr );
  }

  {
    // verify working vector support

    typedef std::vector< Str > StrVect;

    StrVect tvect;

    const char * data[] =
    {
      "S 1",
      "S 2",
      "S 3",
      "S 4",
      "S 5",
      0
    };

    for( int i = 0; data[i]; i++ )
      tvect.push_back( Str( data[i] ) );

    {
      StrVect & t( tvect );

      int count = 0;

      for( StrVect::iterator them = t.begin();
	   them != t.end();
	   ++ them, ++ count )
	{
	  TEST( (*them) == data[count] );
	}
    }
  }

  return( verify.is_valid() );
}

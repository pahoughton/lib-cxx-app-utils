#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <Str.hh>
#endif

// Str::find_*

static const char * Hay =

   "This is the hay to search : it will be (0123456689) used to test Str::find_";
//  01234567890123456789012345678901234567890123456789012345678901234567890123456
//            1         2         3         4         5         6         7

bool
tStr15( LibTest & tester )
{
  {
    // find_first_of( const Str & ) const
    // find_first_of( const Str &, size_t ) const

    const Str t( Hay );

    Str pat;

    pat = ":w1234";
    TEST( t.find_first_of( pat ) == 26 );
    pat = ":123";
    TEST( t.find_first_of( pat, 28 ) == 41 );
  }
  
  {
    // find_first_of( const SubStr & ) const
    // find_first_of( const SubStr &, size_t ) const

    const Str t( Hay );

    Str pat;

    pat = "###:w1234";
    TEST( t.find_first_of( pat.after( 3 ) ) == 26 );
    pat = "###:123";
    TEST( t.find_first_of( pat.after( 3 ), 28 ) == 41 );
  }
  
  {
    // find_first_of( const char * ) const
    // find_first_of( const char *, size_t ) const
    // find_first_of( const char *, size_t, size_t ) const

    const Str t( Hay );
    
    TEST( t.find_first_of( ":w1234" ) == 26 );
    TEST( t.find_first_of( "!@#$:w1234" ) == 26 );
    TEST( t.find_first_of( "!@#$w:" ) == 26 );
    TEST( t.find_first_of( ":iea" ) == 2 );
    TEST( t.find_first_of( ":123", 28 ) == 41 );
    TEST( t.find_first_of( "!@#$" ) == Str::npos );
    TEST( t.find_first_of( "!@#$:123", 0, 4 ) == Str::npos );

  }

  {
    // find_last_of( const Str & ) const
    // find_last_of( const Str &, size_t ) const
    
    const Str t( Hay );

    Str pat;

    pat = ":w1234";
    TEST( t.find_last_of( pat ) == 69 );
    pat = ":123";
    TEST( t.find_last_of( pat, 69 ) == 68 );
    pat = "!@#$";
    TEST( t.find_last_of( pat ) == Str::npos );
  }

  {
    // find_last_of( const SubStr & ) const
    // find_last_of( const SubStr &, size_t ) const
    
    const Str t( Hay );

    Str pat;

    pat = "###:w1234";
    TEST( t.find_last_of( pat.after( 3 ) ) == 69 );
    pat = "###:123";
    TEST( t.find_last_of( pat.after( 3 ), 69 ) == 68 );
    pat = "123!@#$";
    TEST( t.find_last_of( pat.after( 3 ) ) == Str::npos );
  }

  {
    // find_last_of( const char * ) const
    // find_last_of( const char *, size_t ) const
    // find_last_of( const char *, size_t, size_t ) const
    
    const Str t( Hay );    
  
    TEST( t.find_last_of( ":w1234" ) == 69 );
    TEST( t.find_last_of( "!@#$:w1234" ) == 69 );
    TEST( t.find_last_of( "!@#$w:" ) == 69 );
    TEST( t.find_last_of( ":iea" ) == 71 );
    TEST( t.find_last_of( ":123", 69 ) == 68 );
    TEST( t.find_last_of( "!@#$:123", 0, 4 ) == Str::npos );

  }

  {
    // find_first_not_of( const Str & ) const
    // find_first_not_of( const Str &, size_t ) const

    const Str t( Hay );    

    Str pat;

    pat = "iTsh etay";
    TEST( t.find_first_not_of( pat ) == 17 );
    pat = "the ay";
    TEST( t.find_first_not_of( pat, 10 ) == 17 );
  }
  
  {
    // find_first_not_of( const SubStr & ) const
    // find_first_not_of( const SubStr &, size_t ) const

    const Str t( Hay );    

    Str pat;

    pat = "###iTsh etay";
    TEST( t.find_first_not_of( pat.after( 3 ) ) == 17 );
    pat = "###the ay";
    TEST( t.find_first_not_of( pat.after( 3 ), 10 ) == 17 );
  }

  {
    // find_first_not_of( const char * ) const
    // find_first_not_of( const char *, size_t ) const
    // find_first_not_of( const char *, size_t, size_t ) const
    
    const Str t( Hay );    

    TEST( t.find_first_not_of( "This teay" ) == 17 );
    TEST( t.find_first_not_of( "the ay", 10 ) == 17 );
    TEST( t.find_first_not_of( "This teayo", 0, 9 ) == 17 );
  }

  {
    // find_last_not_of( const Str & ) const
    // find_last_not_of( const Str &, size_t ) const

    const Str t( Hay );    

    Str pat;

    pat = "_Str:find ";
    TEST( t.find_last_not_of( pat ) == 62 );
    pat = "to es";
    TEST( t.find_last_not_of( pat, 64 ) == 55 );
  }
  
  {
    // find_last_not_of( const SubStr & ) const
    // find_last_not_of( const SubStr &, size_t ) const

    const Str t( Hay );    

    Str pat;

    pat = "s_Str:find ";
    TEST( t.find_last_not_of( pat.after( 1 ) ) == 62 );
    pat = "dto es";
    TEST( t.find_last_not_of( pat.after( 1 ), 64 ) == 55 );
  }

  {
    // find_last_not_of( const char * ) const
    // find_last_not_of( const char *, size_t ) const
    // find_last_not_of( const char *, size_t, size_t ) const
    
    const Str t( Hay );    
    
    TEST( t.find_last_not_of( "_Str:find " ) == 62 );
    TEST( t.find_last_not_of( "to es", 64 ) == 55 );
    TEST( t.find_last_not_of( "to esd", 64, 5 ) == 55 );
  }

  return( true );
}

#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <FilePath.hh>
#include <functional>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <FilePath.hh>
#endif

#define P   "dir"
#define F   "filename"
#define E   "ext"
#define DD  "/"
#define DE  "."

bool
tFilePath03( LibTest & tester )
{
  {
    // setFileName( const char * )
    // setName( const char * )
    // setPath( const char * )
    // setName( const char *, char )
    // setName( const char *, const char * )
    // setExt( const char * )
    // setExt( const char *, char )
    // setExt( const char *, const char * )
    
    
    FilePath t('/','-');

    t.setFileName( F "-" E );
    TEST( compare( t.getFullName().c_str(), F "-" E ) == 0 );

    t.setName( "fn" );
    TEST( compare( t.getFullName().c_str(), "fn" "-" E ) == 0 );

    t.setPath( "dir" );
    TEST( compare( t.getFullName().c_str(), "dir" "/" "fn" "-" E ) == 0 );

    t.setFileName( F "." "a" "-" "b" );
    TEST( compare( t.getFullName().c_str(), "dir" "/" F "." "a" "-" "b" ) == 0 );

    t.setName( "FN", '.' );
    TEST( compare( t.getFullName().c_str(), "dir" "/" "FN" "." "a" "-" "b" ) == 0 );
	  
    t.setName( "file", ".a-b" );
    TEST( compare( t.getFullName().c_str(), "dir" "/" "file" "." "a" "-" "b" ) == 0 );

    t.setExt( "bak" );
    TEST( compare( t.getFullName().c_str(), "dir" "/" "file" "." "a" "-" "bak" ) == 0 );

    t.setFileName( "file" "-" "bak" "." "exe" );
    TEST( compare( t.getFullName().c_str(), "dir" "/" "file" "-" "bak" "." "exe" ) == 0 );

    t.setExt( "o", '.' );
    TEST( compare( t.getFullName().c_str(), "dir" "/" "file" "-" "bak" "." "o" ) == 0 );

    t.setExt( "ak.o", "rown" );
    TEST( compare( t.getFullName().c_str(), "dir" "/" "file" "-" "brown" ) == 0 );
  }
  
  {
    // compare( const FilePath & ) const
    // operator == ( const FilePath & ) const
    // operator <  ( const FilePath & ) const
    // operator >  ( const FilePath & ) const

    const FilePath l( "dir/test.oper" );
    const FilePath re( "dir/test.oper" );
    const FilePath rl( "c/test.oper" );
    const FilePath rm( "e/test" );

    TEST( l.compare( re ) == 0 );
    TEST( l == re );
    TEST( ! ( l == rl ) );

    TEST( l.compare( rm ) < 0 );
    TEST( l < rm );
    TEST( ! ( l < rl ) );

    TEST( l.compare( rl ) > 0 );
    TEST( l > rl );
    TEST( ! ( l > rm ) );
    
  }

  {
    // const char * c_str( void ) const

    FilePath	t( ":usr:src", "test.c", ':' );

    TEST( strcmp( ":usr:src:test.c", t.c_str() ) == 0 );
  }

    
  return( true );
}

    

#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <FilePath.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <FilePath.hh>
#endif

#define D   "dir"
#define F   "filename"
#define E   "ext"
#define DD  "/"
#define DE  "."

bool
tFilePath02( LibTest & tester )
{
  {
    // getPath( void ) const
    // getFileName( void ) const
    // getName( void ) const
    // getExt( void ) const

    FilePath	t( D DD F DE E );

    TEST( compare( t.getPath(), D ) == 0 );
    TEST( compare( t.getFileName(), F DE E ) == 0 );
    TEST( compare( t.getName(), F ) == 0 );
    TEST( compare( t.getExt(), E ) == 0 );
  }
  
  {
    FilePath	t( D DD D DD D DD F DE E );

    TEST( compare( t.getPath(), D DD D DD D ) == 0 );
    TEST( compare( t.getFileName(), F DE E ) == 0 );
    TEST( compare( t.getName(), F ) == 0 );
    TEST( compare( t.getExt(), E ) == 0 );
  }
  
  {
    FilePath	t( D DD D DD D DD F DE "abc" DE E );

    TEST( compare( t.getPath(), D DD D DD D ) == 0 );
    TEST( compare( t.getFileName(), F DE "abc" DE E ) == 0 );
    TEST( compare( t.getName(), F DE "abc" ) == 0 );
    TEST( compare( t.getExt(), E ) == 0 );
  }

  {
    // set( const char * )
    
    FilePath	t( D DD F DE E );

    t.set( D DD D DD D DD F DE "abc" DE E );

    TEST( compare( t.getPath(), D DD D DD D ) == 0 );
    TEST( compare( t.getFileName(), F DE "abc" DE E ) == 0 );
    TEST( compare( t.getName(), F DE "abc" ) == 0 );
    TEST( compare( t.getExt(), E ) == 0 );
  }

  {
    // setPrefix( const char * )

    FilePath	t( D DD F DE E );

    t.setPrefix( D );

    TEST( compare( t.getPath(), D DD D ) == 0 );
    TEST( compare( t.getFileName(), F DE E ) == 0 );

    t.setPrefix( D DE );
    TEST( compare( t.getPath(), D DE DD D DD D ) == 0 );
    TEST( compare( t.getFileName(), F DE E ) == 0 );
  }
  
  {
    // setPath( const char * )
    FilePath t( D DD D DD F );

    t.setPath( D );

    TEST( compare( t.getFullName(), D DD F ) == 0 );
    TEST( compare( t.getPath(), D ) == 0 );    
  }

  {
    // setPath( const char * )
    FilePath t( D DD D DD F );

    t.setPath( D DD );

    TEST( compare( t.getFullName(), D DD F ) == 0 );
    TEST( compare( t.getPath(), D ) == 0 );    
  }

  {
    // setPath( const char * )
    FilePath t( F );

    t.setPath( D );

    TEST( compare( t.getFullName(), D DD F ) == 0 );
    TEST( compare( t.getPath(), D ) == 0 );    
  }

  {
    // changePath( const char *, const char * )

    FilePath t( "d1/d2/d3/d4/filename" );

    t.changePath( "d2/d3", "other" );

    TEST( compare( t.getFullName(), "d1/other/d4/filename" ) == 0 );

    t.changePath( "d1/", "/new/base/" );
    TEST( compare( t.getFullName(), "/new/base/other/d4/filename" ) == 0 );
  }

  return( true );
}

    
    
    

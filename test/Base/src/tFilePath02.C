#if !defined( CLUE_SHORT_FN )
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

    TEST( compare( t.getPath().c_str(), D ) == 0 );
    TEST( compare( t.getFileName().c_str(), F DE E ) == 0 );
    TEST( compare( t.getName().c_str(), F ) == 0 );
    TEST( compare( t.getExt().c_str(), E ) == 0 );
  }
  
  {
    FilePath	t( D DD D DD D DD F DE E );

    TEST( compare( t.getPath().c_str(), D DD D DD D ) == 0 );
    TEST( compare( t.getFileName().c_str(), F DE E ) == 0 );
    TEST( compare( t.getName().c_str(), F ) == 0 );
    TEST( compare( t.getExt().c_str(), E ) == 0 );
  }
  
  {
    FilePath	t( D DD D DD D DD F DE "abc" DE E );

    TEST( compare( t.getPath().c_str(), D DD D DD D ) == 0 );
    TEST( compare( t.getFileName().c_str(), F DE "abc" DE E ) == 0 );
    TEST( compare( t.getName().c_str(), F DE "abc" ) == 0 );
    TEST( compare( t.getExt().c_str(), E ) == 0 );
  }

  {
    // set( const char * )
    
    FilePath	t( D DD F DE E );

    t.set( D DD D DD D DD F DE "abc" DE E );

    TEST( compare( t.getPath().c_str(), D DD D DD D ) == 0 );
    TEST( compare( t.getFileName().c_str(), F DE "abc" DE E ) == 0 );
    TEST( compare( t.getName().c_str(), F DE "abc" ) == 0 );
    TEST( compare( t.getExt().c_str(), E ) == 0 );
  }

  {
    // setPrefix( const char * )

    FilePath	t( D DD F DE E );

    t.setPrefix( D );

    TEST( compare( t.getPath().c_str(), D DD D ) == 0 );
    TEST( compare( t.getFileName().c_str(), F DE E ) == 0 );

    t.setPrefix( D DE );
    TEST( compare( t.getPath().c_str(), D DE DD D DD D ) == 0 );
    TEST( compare( t.getFileName().c_str(), F DE E ) == 0 );
  }
  
  {
    // setPath( const char * )
    FilePath t( D DD D DD F );

    t.setPath( D );

    TEST( compare( t.getFullName().c_str(), D DD F ) == 0 );
    TEST( compare( t.getPath().c_str(), D ) == 0 );    
  }

  {
    // setPath( const char * )
    FilePath t( D DD D DD F );

    t.setPath( D DD );

    TEST( compare( t.getFullName().c_str(), D DD F ) == 0 );
    TEST( compare( t.getPath().c_str(), D ) == 0 );    
  }

  {
    // setPath( const char * )
    FilePath t( F );

    t.setPath( D );

    TEST( compare( t.getFullName().c_str(), D DD F ) == 0 );
    TEST( compare( t.getPath().c_str(), D ) == 0 );    
  }

  {
    // changePath( const char *, const char * )

    FilePath t( "d1/d2/d3/d4/filename" );

    TEST( t.changePath( "d2/d3", "other" ) );

    TEST( compare( t.getFullName().c_str(), "d1/other/d4/filename" ) == 0 );

    TEST( t.changePath( "d1/", "/new/base/" ) );
    
    TESTR( t.getFullName().c_str(),
	   compare( t.getFullName().c_str(), "/new/base/other/d4/filename" )
	  == 0 );

    TEST( ! t.changePath( "notfound", "xxxxxxxxxx" ) );
    
    TESTR( t.getFullName().c_str(),
	   compare( t.getFullName().c_str(), "/new/base/other/d4/filename" )
	  == 0 );

  }

  return( true );
}

    
    
    

#include <LibTest.hh>
#include <FilePath.hh>

#define D   "dir"
#define F   "filename"
#define E   "ext"
#define DD  "/"
#define DE  "."

bool
tFilePath02( LibTest & test )
{
  {
    // getPath( void ) const
    // getFileName( void ) const
    // getName( void ) const
    // getExt( void ) const

    FilePath	t( D DD F DE E );

    test( compare( t.getPath(), D ) == 0 );
    test( compare( t.getFileName(), F DE E ) == 0 );
    test( compare( t.getName(), F ) == 0 );
    test( compare( t.getExt(), E ) == 0 );
  }
  
  {
    FilePath	t( D DD D DD D DD F DE E );

    test( compare( t.getPath(), D DD D DD D ) == 0 );
    test( compare( t.getFileName(), F DE E ) == 0 );
    test( compare( t.getName(), F ) == 0 );
    test( compare( t.getExt(), E ) == 0 );
  }
  
  {
    FilePath	t( D DD D DD D DD F DE "abc" DE E );

    test( compare( t.getPath(), D DD D DD D ) == 0 );
    test( compare( t.getFileName(), F DE "abc" DE E ) == 0 );
    test( compare( t.getName(), F DE "abc" ) == 0 );
    test( compare( t.getExt(), E ) == 0 );
  }

  {
    // set( const char * )
    
    FilePath	t( D DD F DE E );

    t.set( D DD D DD D DD F DE "abc" DE E );

    test( compare( t.getPath(), D DD D DD D ) == 0 );
    test( compare( t.getFileName(), F DE "abc" DE E ) == 0 );
    test( compare( t.getName(), F DE "abc" ) == 0 );
    test( compare( t.getExt(), E ) == 0 );
  }

  {
    // setPrefix( const char * )

    FilePath	t( D DD F DE E );

    t.setPrefix( D );

    test( compare( t.getPath(), D DD D ) == 0 );
    test( compare( t.getFileName(), F DE E ) == 0 );

    t.setPrefix( D DE );
    test( compare( t.getPath(), D DE DD D DD D ) == 0 );
    test( compare( t.getFileName(), F DE E ) == 0 );
  }
  
  {
    // setPath( const char * )
    FilePath t( D DD D DD F );

    t.setPath( D );

    test( compare( t.getFullName(), D DD F ) == 0 );
    test( compare( t.getPath(), D ) == 0 );    
  }

  {
    // setPath( const char * )
    FilePath t( D DD D DD F );

    t.setPath( D DD );

    test( compare( t.getFullName(), D DD F ) == 0 );
    test( compare( t.getPath(), D ) == 0 );    
  }

  {
    // setPath( const char * )
    FilePath t( F );

    t.setPath( D );

    test( compare( t.getFullName(), D DD F ) == 0 );
    test( compare( t.getPath(), D ) == 0 );    
  }

  {
    // changePath( const char *, const char * )

    FilePath t( "d1/d2/d3/d4/filename" );

    t.changePath( "d2/d3", "other" );

    test( compare( t.getFullName(), "d1/other/d4/filename" ) == 0 );

    t.changePath( "d1/", "/new/base/" );
    test( compare( t.getFullName(), "/new/base/other/d4/filename" ) == 0 );
  }

  return( true );
}

    
    
    

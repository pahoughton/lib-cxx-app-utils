#include <LibTest.hh>
#include <FilePath.hh>

#include <Compare.hh>

#define D   "dir"
#define F   "filename"
#define E   "ext"
#define DD  "/"
#define DE  "."

bool
tFilePath01( LibTest & test )
{
  {
    // FilePath( void )
    FilePath	t;
  }

  {
    // FilePath( char )

    FilePath	t('\\');
  }

  {
    // FilePath( char, char )
    
    FilePath	t(':', '.' );		  
  }

  {
    // FilePath( const char * )
    // getFullName( void ) const

    FilePath	t( D DD F DE E );

    test( compare( t.getFullName(), D DD F DE E ) == 0 );
  }

  {
    // FilePath( const char *, char )

    FilePath	t( D ":" F DE E,':' );

    test( compare( t.getFullName(), D ":" F DE E ) == 0 );
  }
  
  {  
    // FilePath( const char *, char, char )
    FilePath	t( D ":" F "-" E,':','-' );

    test( compare( t.getFullName(), D ":" F "-" E ) == 0 );
  }

  {
    // FilePath( const char *, const char * )

    FilePath	t( D, F );

    test( compare( t.getFullName(), D DD F ) == 0 );
  }

  {
    // FilePath( const char *, const char *, char )

    FilePath	t( D, F, ':' );

    test( compare( t.getFullName(), D ":" F ) == 0 );
  }

  {
    // FilePath( const char *, const char *, char, char )

    FilePath	t( D, F "-" E, ':', '-' );

    test( compare( t.getFullName(), D ":" F "-" E ) == 0 );
  }

  return( true );
}

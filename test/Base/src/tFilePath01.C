#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <FilePath.hh>
#include <Compare.hh>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <FilePath.hh>
#include <Compare.hh>
#endif

#define D   "dir"
#define F   "filename"
#define E   "ext"
#define DD  "/"
#define DE  "."

bool
tFilePath01( LibTest & tester )
{
  {
    // FilePath( void )
    FilePath	t;

    TESTR( t.error(), t.good() );    
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

    TEST( compare( t.getFullName(), D DD F DE E ) == 0 );
  }

  {
    // FilePath( const char *, char )

    FilePath	t( D ":" F DE E,':' );

    TEST( compare( t.getFullName(), D ":" F DE E ) == 0 );
  }
  
  {  
    // FilePath( const char *, char, char )
    FilePath	t( D ":" F "-" E,':','-' );

    TEST( compare( t.getFullName(), D ":" F "-" E ) == 0 );
  }

  {
    // FilePath( const char *, const char * )

    FilePath	t( D, F );

    TEST( compare( t.getFullName(), D DD F ) == 0 );
  }

  {
    // FilePath( const char *, const char *, char )

    FilePath	t( D, F, ':' );

    TEST( compare( t.getFullName(), D ":" F ) == 0 );
  }

  {
    // FilePath( const char *, const char *, char, char )

    FilePath	t( D, F "-" E, ':', '-' );

    TEST( compare( t.getFullName(), D ":" F "-" E ) == 0 );
  }

  return( true );
}

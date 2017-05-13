// 1995-06-15 (cc) Paul Houghton <paul4hough@gmail.com>

#include <clue/FilePath.hpp>
#include <clue/compare>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::FilePath01");
using namespace clue;

#define D   "dir"
#define F   "filename"
#define E   "ext"
#define DD  "/"
#define DE  "."

bool
v_FilePath01( void )
{
  {
    // FilePath( void )
    FilePath	t;

    TEST( t.good() );
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

    TEST( compare( t.getFullName().c_str(), D DD F DE E ) == 0 );
  }

  {
    // FilePath( const char *, char )

    FilePath	t( D ":" F DE E,':' );

    TEST( compare( t.getFullName().c_str(), D ":" F DE E ) == 0 );
  }

  {
    // FilePath( const char *, char, char )
    FilePath	t( D ":" F "-" E,':','-' );

    TEST( compare( t.getFullName().c_str(), D ":" F "-" E ) == 0 );
  }

  {
    // FilePath( const char *, const char * )

    FilePath	t( D, F );

    TEST( compare( t.getFullName().c_str(), D DD F ) == 0 );
  }

  {
    // FilePath( const char *, const char *, char )

    FilePath	t( D, F, ':' );

    TEST( compare( t.getFullName().c_str(), D ":" F ) == 0 );
  }

  {
    // FilePath( const char *, const char *, char, char )

    FilePath	t( D, F "-" E, ':', '-' );

    TEST( compare( t.getFullName().c_str(), D ":" F "-" E ) == 0 );
  }

  return( verify.is_valid() );
}

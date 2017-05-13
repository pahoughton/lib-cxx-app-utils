// 1995-06-15 (cc) Paul Houghton <paul4hough@gmail.com>

#include <clue/FileStat.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <sstream>

static valid::verify verify("clue::FileStat03");
using namespace clue;

#define TEST_DATA_DIR "data/FileStat"

bool
v_FileStat06( void )
{
  {
    // compare( const FileStat & ) const
    // operator == ( const FileStat & ) const
    // operator <  ( const FileStat & ) const
    // operator >  ( const FileStat & ) const

    const FileStat tl( TEST_DATA_DIR "/FileStat.01" );
    const FileStat tm( TEST_DATA_DIR "/FileStat.l1" );

    TEST( tl.compare( tl ) == 0 );
    TEST( tl == tl );
    TEST( tl.compare( tm ) <  0 );
    TEST( tl < tm );
    TEST( tm.compare( tl ) >  0 );
    TEST( tm > tl );
  }

  {
    // toStream( ostream & ) const
    // operator << ( ostream &, const FilePath & )

    std::stringstream tStrm;
    const FileStat t( TEST_DATA_DIR "/FileStat.01" );

    t.toStream( tStrm );
    tStrm << t;
  }

  {
    // good( void ) const
    // error( void ) const
    // getClassName( void ) const
    // getVersion( void ) const
    // getVersion( bool ) const

    const FileStat t( TEST_DATA_DIR "/FileStat.01" );

    TEST( t.good() );
    TEST( t.error() != 0 );
  }

  {
    // ::compare( const FileStat &, const FileStat & )

    const FileStat tl( TEST_DATA_DIR "/FileStat.01" );
    const FileStat tm( TEST_DATA_DIR "/FileStat.l1" );

    TEST( compare( tl, tl ) == 0 );
    TEST( compare( tl, tm ) <  0 );
    TEST( compare( tm, tl ) >  0 );
  }
  return( verify.is_valid() );
}

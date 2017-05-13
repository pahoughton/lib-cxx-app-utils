// 1998-03-08 (cc) Paul Houghton <paul4hough@gmail.com>

#include <clue/FileOp.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::FileOp01");
using namespace clue;

#define TEST_DATA_DIR "data/FileOp"

#if !defined( TEST_TEMP_DIR )
#define TEST_TEMP_DIR	"/tmp"
#endif

bool
v_FileOp01( void )
{
  {
    // FileOp( const char * )

    static const char * TestFn = TEST_DATA_DIR "/FileOp.01.01.exp";

    FileOp  t( TestFn );

    TEST( t.good() );
  }

  {
    // copy( const char * dest )
    //	same dir different name
    static const char * TestFn = TEST_DATA_DIR "/FileOp.01.01";

    FileOp    t( TEST_DATA_DIR "/FileOp.01.01.exp" );

    TEST( t.good() );

    TEST( t.copy( TestFn ) );
    VVFILE( TestFn );
  }

  {
    // copy( const char * dest )
    //	different filesystem

    static const char * ExpFn = TEST_DATA_DIR "/FileOp.01.01.exp";
    static const char * TestFn = TEST_TEMP_DIR "/FileOp.01.01";

    FileStat	srcDir( TEST_DATA_DIR );
    FileStat	destDir( TEST_TEMP_DIR );

    TEST(  srcDir.good() );
    TEST( destDir.good() );

    FileOp    t( ExpFn  );

    TEST( t.good() );
    TEST( t.copy( TestFn ) );

    VVEXPFILE( TestFn, ExpFn );

    remove( TestFn );

  }

  {
    // copy( const char * dest )
    //	copy to directory
    static const char * ExpFn = TEST_DATA_DIR "/FileOp.01.01.exp";
    static const char * TestFn = TEST_TEMP_DIR "/FileOp.01.01.exp";

    FileOp    t( ExpFn  );

    TEST( t.good() );

    TEST( t.copy( TEST_TEMP_DIR ) );

    VVEXPFILE( TestFn, ExpFn );
    remove( TestFn );
  }

  {
    // copy( const char * src, const char * dest )

    static const char * ExpFn = TEST_DATA_DIR "/FileOp.01.01.exp";
    static const char * TestFn = TEST_DATA_DIR "/FileOp.01.01";

    FileOp t;

    TEST( t.copy( ExpFn, TestFn ) );

    VVEXPFILE( TestFn, ExpFn );

    remove( TestFn );
  }

  {
    // copy()
    //	write only dest dir
#define TEST_RONLY_DIR	TEST_DATA_DIR "/ro-dir"

    FileStat	destDir( TEST_RONLY_DIR );

    if( destDir.good() )
      {
	TEST( destDir.getMode() == 040555 );
      }
    else
      {
	TEST( mkdir( TEST_RONLY_DIR, 0555 ) == 0 );
      }

    static const char * ExpFn = TEST_DATA_DIR "/FileOp.01.01.exp";
    static const char * TestFn = TEST_RONLY_DIR;

    FileOp t( ExpFn );

    TEST( t.good() );

    TEST( ! t.copy( TestFn ) );
  }

  {
    // copy()
    //	write only dest dir

    static const char * ExpFn = TEST_DATA_DIR "/FileOp.01.01.exp";
    static const char * TestFn = TEST_RONLY_DIR "/FileOp.01.01";

    FileOp t( ExpFn );

    TEST( t.good() );

    TEST( ! t.copy( TestFn ) );
  }

  {
    // copy( const char * dest, overwrite )

    static const char * ExpFn = TEST_DATA_DIR "/FileOp.01.01.exp";

    static const char * Test01Fn = TEST_DATA_DIR "/FileOp.01.01";

    static const char * Test02Dir = TEST_TEMP_DIR;
    static const char * Test02Fn = TEST_TEMP_DIR "/FileOp.01.01";

    FileOp t( ExpFn );

    TEST( t.good() );

    TEST( t.copy( Test01Fn, true ) );

    TEST( t.copy( Test01Fn, true ) );

    TEST( ! t.copy( Test01Fn, false ) );

    TEST( t.copy( Test01Fn, Test02Fn, true ) );
    TEST( ! t.copy( Test02Dir, false ) );

  }

  return( verify.is_valid() );
}

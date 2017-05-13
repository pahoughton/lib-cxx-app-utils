// 1998-03-08 (cc) Paul Houghton <paul4hough@gmail.com>

#include <clue/FileOp.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <cstdio>

static valid::verify verify("clue::FileOp02");
using namespace clue;

#define TEST_DATA_DIR "data/FileOp"

bool
v_FileOp02( void )
{
  static const char * ExpFn = TEST_DATA_DIR "/FileOp.01.01.exp";

  {
    static const char * TestFn = TEST_DATA_DIR "/FileOp.02.01";

    FileOp    t( ExpFn );

    TEST(  t.good() );

    TEST(  t.copy( TestFn ) );

    VVEXPFILE( TestFn, ExpFn );
  }

  {
    static const char * SrcFn  = TEST_DATA_DIR "/FileOp.02.01";
    static const char * TestFn = TEST_DATA_DIR "/FileOp.02.01.01";

    FileOp t( SrcFn );

    TEST( t.good() );

    TEST( t.move( TestFn ) );

    FileStat destStat( TestFn );

    TEST( destStat.good() && destStat.isReg() );

    VVEXPFILE( TestFn, ExpFn );

    FileStat srcStat( SrcFn );

    TEST( ! srcStat.good() );
  }

  {
    static const char * SrcFn = TEST_DATA_DIR "/FileOp.02.01.01";
    static const char * TestFn = "/tmp/FileOp.02.01.01";
    static const char * TestDir = "/tmp";

    FileOp t( SrcFn );

    TEST( t.good() );

    TEST( t.move( TestDir ) );

    FileStat destStat( TestFn );

    TEST( destStat.good() && destStat.isReg() );

    VVEXPFILE( TestFn, ExpFn );

    FileStat srcStat( SrcFn );

    TEST( ! srcStat.good() );
  }

  {
    static const char * SrcFn = "/tmp/FileOp.02.01.01";
    static const char * TestFn = TEST_DATA_DIR "/FileOp.02.01.01";

    FileOp t( SrcFn );

    TEST( t.good() );

    TEST( t.move( TestFn ) );

    FileStat destStat( TestFn );

    TEST( destStat.good() && destStat.isReg() );

    VVEXPFILE( TestFn, ExpFn );

    FileStat srcStat( SrcFn );

    TEST( ! srcStat.good() );
  }
  return( verify.is_valid() );
}

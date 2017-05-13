// 1995-06-15 (cc) Paul Houghton <paul4hough@gmail.com>

#include <clue/FileStat.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::FileStat03");
using namespace clue;

#define TEST_DATA_DIR "data/FileStat"

bool
v_FileStat03( void )
{
  {
    // canRead( void ) const
    // canWrite( void ) const
    // canExec( void ) const
    // canRead( Who ) const
    // canWrite( Who ) const
    // canExec( Who ) const

    const FileStat t( TEST_DATA_DIR "/FileStat.h.t.yyy.yyy.yyy" );

    TEST(   t.good() );

    TEST(   t.canRead() );
    TEST(   t.canWrite() );
    TEST(   t.canExec() );

    TEST(   t.canRead( FileStat::USER ) );
    TEST(   t.canWrite( FileStat::USER ) );
    TEST(   t.canExec( FileStat::USER ) );

    TEST(   t.canRead( FileStat::GROUP ) );
    TEST(   t.canWrite( FileStat::GROUP ) );
    TEST(   t.canExec( FileStat::GROUP ) );

    TEST(   t.canRead( FileStat::OTHER ) );
    TEST(   t.canWrite( FileStat::OTHER ) );
    TEST(   t.canExec( FileStat::OTHER ) );

  }

  {
    const FileStat t( TEST_DATA_DIR "/FileStat.h.t.nnn.nnn.nnn" );

    TEST( ! t.canRead() );
    TEST( ! t.canWrite() );
    TEST( ! t.canExec() );

    TEST( ! t.canRead( FileStat::USER ) );
    TEST( ! t.canWrite( FileStat::USER ) );
    TEST( ! t.canExec( FileStat::USER ) );

    TEST( ! t.canRead( FileStat::GROUP ) );
    TEST( ! t.canWrite( FileStat::GROUP ) );
    TEST( ! t.canExec( FileStat::GROUP ) );

    TEST( ! t.canRead( FileStat::OTHER ) );
    TEST( ! t.canWrite( FileStat::OTHER ) );
    TEST( ! t.canExec( FileStat::OTHER ) );

  }

  {
    const FileStat t( TEST_DATA_DIR "/FileStat.h.t.nnn.yyy.nnn" );

    TEST( ! t.canRead() );
    TEST( ! t.canWrite() );
    TEST( ! t.canExec() );

    TEST( ! t.canRead( FileStat::USER ) );
    TEST( ! t.canWrite( FileStat::USER ) );
    TEST( ! t.canExec( FileStat::USER ) );

    TEST(   t.canRead( FileStat::GROUP ) );
    TEST(   t.canWrite( FileStat::GROUP ) );
    TEST(   t.canExec( FileStat::GROUP ) );

    TEST( ! t.canRead( FileStat::OTHER ) );
    TEST( ! t.canWrite( FileStat::OTHER ) );
    TEST( ! t.canExec( FileStat::OTHER ) );

  }

  {
    const FileStat t( TEST_DATA_DIR "/FileStat.b.b.yyy.yyy.nnn" );

    TEST(   t.canRead( FileStat::USER ) );
    TEST(   t.canWrite( FileStat::USER ) );
    TEST(   t.canExec( FileStat::USER ) );

    TEST(   t.canRead( FileStat::GROUP ) );
    TEST(   t.canWrite( FileStat::GROUP ) );
    TEST(   t.canExec( FileStat::GROUP ) );

    TEST( ! t.canRead( FileStat::OTHER ) );
    TEST( ! t.canWrite( FileStat::OTHER ) );
    TEST( ! t.canExec( FileStat::OTHER ) );

  }

  {
    const FileStat t( TEST_DATA_DIR "/FileStat.b.b.yyy.yny.yny" );

    TEST(   t.canRead() );
    TEST(   t.canWrite() );
    TEST(   t.canExec() );

    TEST(   t.canRead( FileStat::USER ) );
    TEST(   t.canWrite( FileStat::USER ) );
    TEST(   t.canExec( FileStat::USER ) );

    TEST(   t.canRead( FileStat::GROUP ) );
    TEST( ! t.canWrite( FileStat::GROUP ) );
    TEST(   t.canExec( FileStat::GROUP ) );

    TEST(   t.canRead( FileStat::OTHER ) );
    TEST( ! t.canWrite( FileStat::OTHER ) );
    TEST(   t.canExec( FileStat::OTHER ) );

  }
  return( verify.is_valid() );
}

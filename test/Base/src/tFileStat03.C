#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <FileStat.hh>
#else
#include <TestCfg.hh>
#include <LibTest.hh>
#include <FileStat.hh>
#endif

bool
tFileStat03( LibTest & tester )
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
#ifdef HAVE_BIN_UID
  {
    const FileStat t( TEST_DATA_DIR "/FileStat.b.b.yyy.yyy.nnn" );

    TEST( ! t.canRead() );
    TEST( ! t.canWrite() );
    TEST( ! t.canExec() );

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
    TEST( ! t.canWrite() );
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
#endif
  return( true );
}


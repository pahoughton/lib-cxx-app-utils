// 1995-06-15 (cc) Paul Houghton <paul4hough@gmail.com>

#include <clue/FileStat.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::FileStat05");
using namespace clue;

#define TEST_DATA_DIR "data/FileStat"

bool
v_FileStat05( void )
{
  {
    // setMode( mode_t )

    FileStat t( TEST_DATA_DIR "/FileStat.set" );
    FileStat c;

    TEST( t.setMode( 0777 ) );

    c.stat( TEST_DATA_DIR "/FileStat.set" );

    TEST( (c.getMode() & 0777) == 0777 );
    TEST( (t.getMode() & 0777) == 0777 );

    TEST( t.setMode( 0644 ) );

    c.stat( TEST_DATA_DIR "/FileStat.set" );

    TEST( (c.getMode() & 0777) == 0644 );
    TEST( (t.getMode() & 0777) == 0644 );

  }

  {
    // set( Who, What );

    FileStat t( TEST_DATA_DIR "/FileStat.set" );
    FileStat c;

    TEST( t.setMode( 0444 ) );

    c.stat( TEST_DATA_DIR "/FileStat.set" );

    TEST( (c.getMode() & 0777) == 0444 );
    TEST( (t.getMode() & 0777) == 0444 );

    TEST( t.setMode( FileStat::USER, FileStat::EXEC ) );

    c.stat( TEST_DATA_DIR "/FileStat.set" );

    TEST( c.canExec( FileStat::USER ) );
    TEST( t.canExec( FileStat::USER ) );

    TEST( (c.getMode() & 0777) == 0544 );
    TEST( (t.getMode() & 0777) == 0544 );

    TEST( t.setMode( FileStat::USER | FileStat::GROUP | FileStat::OTHER,
		     FileStat::WRITE ) );

    c.stat( TEST_DATA_DIR "/FileStat.set" );

    TEST( c.canWrite( FileStat::USER ) );
    TEST( c.canWrite( FileStat::GROUP ) );
    TEST( c.canWrite( FileStat::OTHER ) );

    TEST( t.canWrite( FileStat::USER ) );
    TEST( t.canWrite( FileStat::GROUP ) );
    TEST( t.canWrite( FileStat::OTHER ) );

    TEST( (c.getMode() & 0777) == 0766 );
    TEST( (t.getMode() & 0777) == 0766 );

  }

  {
    // set( Who, What, bool )

    FileStat t( TEST_DATA_DIR "/FileStat.set" );
    FileStat c;

    TEST( t.setMode( 0777 ) );

    c.stat( TEST_DATA_DIR "/FileStat.set" );

    TEST( (c.getMode() & 0777) == 0777 );
    TEST( (t.getMode() & 0777) == 0777 );

    TEST( t.setMode( FileStat::OTHER, FileStat::EXEC, false ) );

    c.stat( TEST_DATA_DIR "/FileStat.set" );

    TEST( (c.getMode() & 0777) == 0776 );
    TEST( (t.getMode() & 0777) == 0776 );


    TEST( t.setMode( FileStat::USER | FileStat::GROUP | FileStat::OTHER,
		     FileStat::WRITE, false ) );

    c.stat( TEST_DATA_DIR "/FileStat.set" );

    TEST( (c.getMode() & 0777) == 0554 );
    TEST( (t.getMode() & 0777) == 0554 );
  }

  {
    // setRead( Who )
    // setRead( Who, bool )
    // setWrite( Who )
    // setWrite( Who, bool )
    // setExec( Who )
    // setExec( Who, bool )

    FileStat t( TEST_DATA_DIR "/FileStat.set" );
    FileStat c;

    TEST( t.setMode( 0 ) );

    c.stat( TEST_DATA_DIR "/FileStat.set" );
#if !defined(VAGRANT) // can't set to 0 on /vagrant
    TEST( (c.getMode() & 0777) == 0 );
#endif
    TEST( (t.getMode() & 0777) == 0 );

    TEST( t.setRead( FileStat::ALL ) );

    c.stat( TEST_DATA_DIR "/FileStat.set" );

    TEST( (c.getMode() & 0777) == 0444 );
    TEST( (t.getMode() & 0777) == 0444 );

    TEST( t.setRead( FileStat::OTHER, false ) );

    c.stat( TEST_DATA_DIR "/FileStat.set" );

    TEST( (c.getMode() & 0777) == 0440 );
    TEST( (t.getMode() & 0777) == 0440 );

    TEST( t.setWrite( FileStat::ALL ) );

    c.stat( TEST_DATA_DIR "/FileStat.set" );

    TEST( (c.getMode() & 0777) == 0662 );
    TEST( (t.getMode() & 0777) == 0662 );

    TEST( t.setWrite( FileStat::OTHER, false ) );

    c.stat( TEST_DATA_DIR "/FileStat.set" );

    TEST( (c.getMode() & 0777) == 0660 );
    TEST( (t.getMode() & 0777) == 0660 );

    TEST( t.setExec( FileStat::ALL ) );

    c.stat( TEST_DATA_DIR "/FileStat.set" );

    TEST( (c.getMode() & 0777) == 0771 );
    TEST( (t.getMode() & 0777) == 0771 );

    TEST( t.setExec( FileStat::OTHER, false ) );

    c.stat( TEST_DATA_DIR "/FileStat.set" );

    TEST( (c.getMode() & 0777) == 0770 );
    TEST( (t.getMode() & 0777) == 0770 );

  }
  return( verify.is_valid() );
}

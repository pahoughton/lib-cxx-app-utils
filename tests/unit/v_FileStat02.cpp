// 1995-06-15 (cc) Paul Houghton <paul4hough@gmail.com>

#include <clue/FileStat.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <fstream>

static valid::verify verify("clue::FileStat02");
using namespace clue;

#define TEST_DATA_DIR "data/FileStat"

#define TEST_BLOCK_DEVICE   "/dev/loop0"
#define TEST_CHAR_DEVICE    "/dev/tty"
#define TEST_SOCKET_DEVICE  "/dev/log"
#define TEST_SETUID_FILE    "/bin/su"
#define TEST_SETGID_FILE    "/usr/bin/write"

bool
v_FileStat02( void )
{
  {
    // isLink( void ) const
    // isReg( void ) const
    // isDir( void ) const
    // isBlock( void ) const
    // isChar( void ) const
    // isFifo( void ) const
    // isSocket( void ) const
    // isSetUID( void ) const
    // isSetGID( void ) const

    const FileStat t( TEST_DATA_DIR "/FileStat.01" );

    TEST( ! t.isLink() );
    TEST(   t.isReg() );
    TEST( ! t.isDir() );
    TEST( ! t.isBlock() );
    TEST( ! t.isChar() );
    TEST( ! t.isSocket() );
    TEST( ! t.isSetUID() );
    TEST( ! t.isSetGID() );
  }

  {

    const FileStat t( TEST_DATA_DIR "/FileStat.l1", true );

    TEST(   t.isLink() );
    TEST( ! t.isReg() );
    TEST( ! t.isDir() );
    TEST( ! t.isBlock() );
    TEST( ! t.isChar() );
    TEST( ! t.isSocket() );
    TEST( ! t.isSetUID() );
    TEST( ! t.isSetGID() );
  }

  {
    const FileStat t( TEST_DATA_DIR );

    TEST( ! t.isLink() );
    TEST( ! t.isReg() );
    TEST(   t.isDir() );
    TEST( ! t.isBlock() );
    TEST( ! t.isChar() );
    TEST( ! t.isSocket() );
    TEST( ! t.isSetUID() );
    TEST( ! t.isSetGID() );
  }

  {
    const FileStat t( TEST_BLOCK_DEVICE );

    TEST( t.good() );
    TEST( ! t.isLink() );
    TEST( ! t.isReg() );
    TEST( ! t.isDir() );
    TEST(   t.isBlock() );
    TEST( ! t.isChar() );
    TEST( ! t.isSocket() );
    TEST( ! t.isSetUID() );
    TEST( ! t.isSetGID() );
  }

  {
    const FileStat t( TEST_CHAR_DEVICE );

    TEST( ! t.isLink() );
    TEST( ! t.isReg() );
    TEST( ! t.isDir() );
    TEST( ! t.isBlock() );
    TEST(   t.isChar() );
    TEST( ! t.isSocket() );
    TEST( ! t.isSetUID() );
    TEST( ! t.isSetGID() );
  }

  {
    const FileStat t( TEST_SOCKET_DEVICE );

    TEST( ! t.isLink() );
    TEST( ! t.isReg() );
    TEST( ! t.isDir() );
    TEST( ! t.isBlock() );
    TEST( ! t.isChar() );
    TEST(   t.isSocket() );
    TEST( ! t.isSetUID() );
    TEST( ! t.isSetGID() );
  }

  {
    const FileStat t( TEST_SETUID_FILE );

    TEST( ! t.isLink() );
    TEST(   t.isReg() );
    TEST( ! t.isDir() );
    TEST( ! t.isBlock() );
    TEST( ! t.isChar() );
    TEST( ! t.isSocket() );
    TEST(   t.isSetUID() );
    TEST( ! t.isSetGID() );
  }

  {
    const FileStat t( TEST_SETGID_FILE );

    TEST( ! t.isLink() );
    TEST(   t.isReg() );
    TEST( ! t.isDir() );
    TEST( ! t.isBlock() );
    TEST( ! t.isChar() );
    TEST( ! t.isSocket() );
    TEST( ! t.isSetUID() );
    TEST(   t.isSetGID() );
  }

  return( verify.is_valid() );
}

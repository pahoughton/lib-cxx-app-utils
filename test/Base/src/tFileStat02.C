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
tFileStat02( LibTest & tester )
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
    const FileStat t( "data" );

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
    const FileStat t( "/dev/fd0" );

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
    const FileStat t( "/dev/tty" );

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
    const FileStat t("/dev/log" );

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
    const FileStat t( "/bin/passwd" );
    
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
#ifdef AIX
    const FileStat t( "/usr/local/bin/elm" );
#else    
    const FileStat t( "/usr/bin/elm" );
#endif
    TEST( ! t.isLink() );
    TEST(   t.isReg() );
    TEST( ! t.isDir() );
    TEST( ! t.isBlock() );
    TEST( ! t.isChar() );
    TEST( ! t.isSocket() );
    TEST( ! t.isSetUID() );
    TEST(   t.isSetGID() );
  }

  return( true );
}

#include <LibTest.hh>
#include <FileStat.hh>

bool
tFileStat02( LibTest & test )
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
    
    const FileStat t( "data/FileStat.01" );
    
    test( ! t.isLink() );
    test(   t.isReg() );
    test( ! t.isDir() );
    test( ! t.isBlock() );
    test( ! t.isChar() );
    test( ! t.isSocket() );
    test( ! t.isSetUID() );
    test( ! t.isSetGID() );
  }

  {
    
    const FileStat t( "data/FileStat.l1", true );
    
    test(   t.isLink() );
    test( ! t.isReg() );
    test( ! t.isDir() );
    test( ! t.isBlock() );
    test( ! t.isChar() );
    test( ! t.isSocket() );
    test( ! t.isSetUID() );
    test( ! t.isSetGID() );
  }

  {
    const FileStat t( "data" );

    test( ! t.isLink() );
    test( ! t.isReg() );
    test(   t.isDir() );
    test( ! t.isBlock() );
    test( ! t.isChar() );
    test( ! t.isSocket() );
    test( ! t.isSetUID() );
    test( ! t.isSetGID() );
  }

  {
    const FileStat t( "/dev/fd0" );

    test( ! t.isLink() );
    test( ! t.isReg() );
    test( ! t.isDir() );
    test(   t.isBlock() );
    test( ! t.isChar() );
    test( ! t.isSocket() );
    test( ! t.isSetUID() );
    test( ! t.isSetGID() );
  }

  {
    const FileStat t( "/dev/tty" );

    test( ! t.isLink() );
    test( ! t.isReg() );
    test( ! t.isDir() );
    test( ! t.isBlock() );
    test(   t.isChar() );
    test( ! t.isSocket() );
    test( ! t.isSetUID() );
    test( ! t.isSetGID() );
  }

  {
    const FileStat t("/dev/log" );

    test( ! t.isLink() );
    test( ! t.isReg() );
    test( ! t.isDir() );
    test( ! t.isBlock() );
    test( ! t.isChar() );
    test(   t.isSocket() );
    test( ! t.isSetUID() );
    test( ! t.isSetGID() );
  }

  {
    const FileStat t( "/bin/passwd" );
    
    test( ! t.isLink() );
    test(   t.isReg() );
    test( ! t.isDir() );
    test( ! t.isBlock() );
    test( ! t.isChar() );
    test( ! t.isSocket() );
    test(   t.isSetUID() );
    test( ! t.isSetGID() );
  }

  {
#ifdef AIX
    const FileStat t( "/usr/local/bin/elm" );
#else    
    const FileStat t( "/usr/bin/elm" );
#endif
    test( ! t.isLink() );
    test(   t.isReg() );
    test( ! t.isDir() );
    test( ! t.isBlock() );
    test( ! t.isChar() );
    test( ! t.isSocket() );
    test( ! t.isSetUID() );
    test(   t.isSetGID() );
  }

  return( true );
}

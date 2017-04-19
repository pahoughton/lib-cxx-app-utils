#if !defined( STLUTILS_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <FileStat.hh>
#include <User.hh>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#else
#include <TestCfg.hh>
#include <LibTest.hh>
#include <FileStat.hh>
#include <User.hh>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#endif


bool
tFileStat01( LibTest & tester )
{
  {
    // FileStat( void )

    FileStat t;

    TEST( ! t.good() );
  }

  {
    // FileStat( const char * )

    FileStat t( TEST_DATA_DIR "/FileStat.01" );

    TEST( t.good() );
  }

  {
    // FileStat( const char *, bool )

    FileStat t( TEST_DATA_DIR "/FileStat.l1", true );

    TESTR( t.error(), t.good() );
  }

  {
    // FileStat( int fd )

    int fd = open( TEST_DATA_DIR "/FileStat.01", O_RDONLY, 0 );

    TEST( fd >= 0 );

    FileStat t( fd );

    TEST( t.good() );
  }

  {
    // getUID( void ) const
    // getGID( void ) const
    // getMode( void ) const
    // getSize( void ) const
    // getDevice( void ) const
    // getDeviceType( void ) const
    // getInode( void ) const
    // getHardLinks( void ) const
    // getBlockSize( void ) const
    // getBlocks( void ) const
    // getAccessTime( void ) const
    // getModificationTime( void ) const
    // getStatusChangeTime( void ) const

    FileStat t( TEST_DATA_DIR "/FileStat.01" );
    User     h( TEST_USER );
    
    struct stat fstat;

    TEST( ! stat( TEST_DATA_DIR "/FileStat.01", &fstat ) );

    TEST( t.getUID() == fstat.st_uid );
    TEST( t.getUID() == h.getUID() );

    TEST( t.getGID() == fstat.st_gid );

    TEST( t.getMode() == fstat.st_mode );
    TEST( (t.getMode() & 0777) == 0664 );
    
    TEST( t.getSize() == fstat.st_size );
    TEST( t.getSize() == 10240 );

    TEST( t.getDevice() == fstat.st_dev );
    TEST( t.getDeviceType() == fstat.st_rdev );
    TEST( t.getInode() == fstat.st_ino );

    TEST( t.getHardLinks() == fstat.st_nlink );
    TEST( t.getHardLinks() == 1 );

    TEST( t.getBlockSize() == fstat.st_blksize );
    TEST( t.getBlocks() == fstat.st_blocks );

    TEST( t.getAccessTime() == fstat.st_atime );
    TEST( t.getModificationTime() == fstat.st_mtime );
    TEST( t.getStatusChangeTime() == fstat.st_ctime );
  }

  {
    FileStat t( TEST_DATA_DIR "/FileStat.l1", true );
    User     h( TEST_USER );
    
    struct stat fstat;

    TEST( ! lstat( TEST_DATA_DIR "/FileStat.l1", &fstat ) );

    TEST( t.getUID() == fstat.st_uid );
    TEST( t.getUID() == h.getUID() );

    TEST( t.getGID() == fstat.st_gid );

    TEST( t.getMode() == fstat.st_mode );
    
    TEST( t.getSize() == fstat.st_size );

    TEST( t.getDevice() == fstat.st_dev );
    TEST( t.getDeviceType() == fstat.st_rdev );
    TEST( t.getInode() == fstat.st_ino );

    TEST( t.getHardLinks() == fstat.st_nlink );
    TEST( t.getHardLinks() == 1 );

    TEST( t.getBlockSize() == fstat.st_blksize );
    TEST( t.getBlocks() == fstat.st_blocks );

    TEST( t.getAccessTime() == fstat.st_atime );
    TEST( t.getModificationTime() == fstat.st_mtime );
    TEST( t.getStatusChangeTime() == fstat.st_ctime );
  }
  
  {
 
    FileStat t( TEST_DATA_DIR "/FileStat.l1" );
    User     h( TEST_USER );
    
    struct stat fstat;

    TEST( ! stat( TEST_DATA_DIR "/FileStat.01", &fstat ) );

    TEST( t.getUID() == fstat.st_uid );
    TEST( t.getUID() == h.getUID() );

    TEST( t.getGID() == fstat.st_gid );

    TEST( t.getMode() == fstat.st_mode );
    TEST( (t.getMode() & 0777) == 0664 );
    
    TEST( t.getSize() == fstat.st_size );
    TEST( t.getSize() == 10240 );

    TEST( t.getDevice() == fstat.st_dev );
    TEST( t.getDeviceType() == fstat.st_rdev );
    TEST( t.getInode() == fstat.st_ino );

    TEST( t.getHardLinks() == fstat.st_nlink );
    TEST( t.getHardLinks() == 1 );

    TEST( t.getBlockSize() == fstat.st_blksize );
    TEST( t.getBlocks() == fstat.st_blocks );

    TEST( t.getAccessTime() == fstat.st_atime );
    TEST( t.getModificationTime() == fstat.st_mtime );
    TEST( t.getStatusChangeTime() == fstat.st_ctime );
  }

  return( true );
}

    
    

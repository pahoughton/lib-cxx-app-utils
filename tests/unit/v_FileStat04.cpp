// 1995-06-15 (cc) Paul Houghton <paul4hough@gmail.com>

#include <clue/FileStat.hpp>
#include <clue/User.hpp>
#include <clue/compare>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

static valid::verify verify("clue::FileStat03");
using namespace clue;

#define TEST_DATA_DIR "data/FileStat"

bool
v_FileStat04( void )
{
  {
    // getName( void ) const
    // getModeString( void ) const
    // getUserName( void ) const
    // getGroupName( void ) const

    const FileStat t( TEST_DATA_DIR "/FileStat.01" );

    TEST( t.good() );
    TEST( compare( (const char *)t.getName(), TEST_DATA_DIR "/FileStat.01" ) == 0 );
    TEST( compare( t.getModeString(), "-rw-rw-r--" ) == 0 );
    TEST( compare( t.getUserName(), TEST_USER ) == 0 );
    TEST( compare( t.getGroupName(), TEST_GROUP ) == 0 );
  }

  {
    // stat( const char * )

    FileStat t( "data" );
    User     h( TEST_USER );

    t.stat( TEST_DATA_DIR "/FileStat.01" );

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
    // stat( int )

    int fd = open( TEST_DATA_DIR "/FileStat.01", O_RDONLY, 0 );

    TEST( fd >= 0 );

    FileStat t( "data" );
    User     h( TEST_USER );

    t.stat( fd );

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
    // lstat( const char * )


    FileStat t( "data" );
    User     h( TEST_USER );


    t.lstat( TEST_DATA_DIR "/FileStat.l1" );
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
    // operator () ( const char * )

    FileStat t( "data" );
    User     h( TEST_USER );

    t( TEST_DATA_DIR "/FileStat.01" );

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
    // operator () ( int )

    int fd = open( TEST_DATA_DIR "/FileStat.01", O_RDONLY, 0 );

    TEST( fd >= 0 );

    FileStat t( "data" );
    static const User     h( TEST_USER );

    t( fd );

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
  return( verify.is_valid() );
}

#include <LibTest.hh>
#include <Compare.hh>
#include <FileStat.hh>
#include <User.hh>

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

bool
tFileStat04( LibTest & test )
{
  {
    // getName( void ) const
    // getModeString( void ) const
    // getUserName( void ) const
    // getGroupName( void ) const

    const FileStat t( "data/FileStat.01" );

    test( t.good() );
    test( compare( (const char *)t.getName(), "data/FileStat.01" ) == 0 );
    test( compare( t.getModeString(), "-rw-rw-r--" ) == 0 );
    test( compare( t.getUserName(), "houghton" ) == 0 );
    test( compare( t.getGroupName(), "tools" ) == 0 );
  }
  
  {
    // stat( const char * )

    FileStat t( "data" );
    User     h( "houghton" );

    t.stat( "data/FileStat.01" );
    
    struct stat fstat;
    
    test( ! stat( "data/FileStat.01", &fstat ) );

    test( t.getUID() == fstat.st_uid );
    test( t.getUID() == h.getUID() );

    test( t.getGID() == fstat.st_gid );

    test( t.getMode() == fstat.st_mode );
    test( (t.getMode() & 0777) == 0664 );
    
    test( t.getSize() == fstat.st_size );
    test( t.getSize() == 10240 );

    test( t.getDevice() == fstat.st_dev );
    test( t.getDeviceType() == fstat.st_rdev );
    test( t.getInode() == fstat.st_ino );

    test( t.getHardLinks() == fstat.st_nlink );
    test( t.getHardLinks() == 1 );

    test( t.getBlockSize() == fstat.st_blksize );
    test( t.getBlocks() == fstat.st_blocks );

    test( t.getAccessTime() == fstat.st_atime );
    test( t.getModificationTime() == fstat.st_mtime );
    test( t.getStatusChangeTime() == fstat.st_ctime );
  }

  {
    // stat( int )

    int fd = open( "data/FileStat.01", O_RDONLY, 0 );

    test( fd >= 0 );

    FileStat t( "data" );
    User     h( "houghton" );

    t.stat( fd );
    
    struct stat fstat;
    
    test( ! stat( "data/FileStat.01", &fstat ) );

    test( t.getUID() == fstat.st_uid );
    test( t.getUID() == h.getUID() );

    test( t.getGID() == fstat.st_gid );

    test( t.getMode() == fstat.st_mode );
    test( (t.getMode() & 0777) == 0664 );
    
    test( t.getSize() == fstat.st_size );
    test( t.getSize() == 10240 );

    test( t.getDevice() == fstat.st_dev );
    test( t.getDeviceType() == fstat.st_rdev );
    test( t.getInode() == fstat.st_ino );

    test( t.getHardLinks() == fstat.st_nlink );
    test( t.getHardLinks() == 1 );

    test( t.getBlockSize() == fstat.st_blksize );
    test( t.getBlocks() == fstat.st_blocks );

    test( t.getAccessTime() == fstat.st_atime );
    test( t.getModificationTime() == fstat.st_mtime );
    test( t.getStatusChangeTime() == fstat.st_ctime );
  }

  {
    // lstat( const char * )

    
    FileStat t( "data" );
    User     h( "houghton" );

    
    t.lstat( "data/FileStat.l1" );
    struct stat fstat;
    
    test( ! lstat( "data/FileStat.l1", &fstat ) );

    test( t.getUID() == fstat.st_uid );
    test( t.getUID() == h.getUID() );

    test( t.getGID() == fstat.st_gid );

    test( t.getMode() == fstat.st_mode );
    
    test( t.getSize() == fstat.st_size );

    test( t.getDevice() == fstat.st_dev );
    test( t.getDeviceType() == fstat.st_rdev );
    test( t.getInode() == fstat.st_ino );

    test( t.getHardLinks() == fstat.st_nlink );
    test( t.getHardLinks() == 1 );

    test( t.getBlockSize() == fstat.st_blksize );
    test( t.getBlocks() == fstat.st_blocks );

    test( t.getAccessTime() == fstat.st_atime );
    test( t.getModificationTime() == fstat.st_mtime );
    test( t.getStatusChangeTime() == fstat.st_ctime );
  }
    
  {
    // operator () ( const char * )

    FileStat t( "data" );
    User     h( "houghton" );

    t( "data/FileStat.01" );
    
    struct stat fstat;
    
    test( ! stat( "data/FileStat.01", &fstat ) );

    test( t.getUID() == fstat.st_uid );
    test( t.getUID() == h.getUID() );

    test( t.getGID() == fstat.st_gid );

    test( t.getMode() == fstat.st_mode );
    test( (t.getMode() & 0777) == 0664 );
    
    test( t.getSize() == fstat.st_size );
    test( t.getSize() == 10240 );

    test( t.getDevice() == fstat.st_dev );
    test( t.getDeviceType() == fstat.st_rdev );
    test( t.getInode() == fstat.st_ino );

    test( t.getHardLinks() == fstat.st_nlink );
    test( t.getHardLinks() == 1 );

    test( t.getBlockSize() == fstat.st_blksize );
    test( t.getBlocks() == fstat.st_blocks );

    test( t.getAccessTime() == fstat.st_atime );
    test( t.getModificationTime() == fstat.st_mtime );
    test( t.getStatusChangeTime() == fstat.st_ctime );
  }
  
  {
    // operator () ( int )

    int fd = open( "data/FileStat.01", O_RDONLY, 0 );

    test( fd >= 0 );

    FileStat t( "data" );
    static const User     h( "houghton" );

    t( fd );
    
    struct stat fstat;
    
    test( ! stat( "data/FileStat.01", &fstat ) );

    test( t.getUID() == fstat.st_uid );
    test( t.getUID() == h.getUID() );

    test( t.getGID() == fstat.st_gid );

    test( t.getMode() == fstat.st_mode );
    test( (t.getMode() & 0777) == 0664 );
    
    test( t.getSize() == fstat.st_size );
    test( t.getSize() == 10240 );

    test( t.getDevice() == fstat.st_dev );
    test( t.getDeviceType() == fstat.st_rdev );
    test( t.getInode() == fstat.st_ino );

    test( t.getHardLinks() == fstat.st_nlink );
    test( t.getHardLinks() == 1 );

    test( t.getBlockSize() == fstat.st_blksize );
    test( t.getBlocks() == fstat.st_blocks );

    test( t.getAccessTime() == fstat.st_atime );
    test( t.getModificationTime() == fstat.st_mtime );
    test( t.getStatusChangeTime() == fstat.st_ctime );
  }

  return( true );
}
  

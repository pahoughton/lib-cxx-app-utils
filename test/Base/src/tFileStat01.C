#include <LibTest.hh>
#include <FileStat.hh>
#include <User.hh>

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

bool
tFileStat01( LibTest & test )
{
  {
    // FileStat( void )

    FileStat t;

    test( ! t.good() );
  }

  {
    // FileStat( const char * )

    FileStat t( "data/FileStat.01" );

    test( t.good() );
  }

  {
    // FileStat( const char *, bool )

    FileStat t( "data/FileStat.l1", true );

    test( t.good() );
  }

  {
    // FileStat( int fd )

    int fd = open( "data/FileStat.01", O_RDONLY, 0 );

    test( fd >= 0 );

    FileStat t( fd );

    test( t.good() );
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

    FileStat t( "data/FileStat.01" );
    User     h( "houghton" );
    
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
    FileStat t( "data/FileStat.l1", true );
    User     h( "houghton" );
    
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

    FileStat t( "data/FileStat.l1" );
    User     h( "houghton" );
    
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

    
    

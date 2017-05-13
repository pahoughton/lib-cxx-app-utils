#ifndef _clue_FileStat_hpp_
#define _clue_FileStat_hpp_
/* 1995-06-15 (cc) Paul Houghton <paul4hough@gmail.com>

   FileStat is provides information about files and modification
   of file permisions. It is basically just a wrapper around
   the stat and chmod calls.
*/

#include <clue/Bitmask.hpp>
#include <clue/FilePath.hpp>
#include <clue/DumpInfo.hpp>

#include <cerrno>
#include <sys/stat.h>

namespace clue {

class FileStat
{

public:

  typedef off_t	size_type;

  typedef Bitmask   Who;
  typedef Bitmask   What;

  static const Who  USER;
  static const Who  GROUP;
  static const Who  OTHER;
  static const Who  ALL;

  static const What READ;
  static const What WRITE;
  static const What EXEC;

  inline FileStat( void );
  inline FileStat( const char * fileName, bool linkStat = false );
  inline FileStat( int fd );
  inline FileStat( const FileStat & from );

  inline uid_t	    	getUID( void ) const;
  inline gid_t	    	getGID( void ) const;

  inline mode_t   	getMode( void ) const;
  inline size_type    	getSize( void ) const;

  inline dev_t	    	getDevice( void ) const;
  inline dev_t		getDeviceType( void ) const;
  inline ino_t	    	getInode( void ) const;
  inline nlink_t   	getHardLinks( void ) const;
  inline unsigned long	getBlockSize( void ) const;
  inline unsigned long	getBlocks( void ) const;

  inline time_t    	getAccessTime( void ) const;
  inline time_t    	getModificationTime( void ) const;
  inline time_t    	getStatusChangeTime( void ) const;

  inline bool		isLink( void ) const;
  inline bool	    	isReg( void ) const;
  inline bool	    	isDir( void ) const;

  inline bool	    	isBlock( void ) const;
  inline bool	    	isChar( void ) const;
  inline bool	    	isFifo( void ) const;
  inline bool		isSocket( void ) const;

  inline bool	    	isSetUID( void ) const;
  inline bool	    	isSetGID( void ) const;

  inline bool	    	canRead( void ) const;
  inline bool	    	canWrite( void ) const;
  inline bool	    	canExec( void ) const;

  inline bool	    	canRead( Who who ) const;
  inline bool	    	canWrite( Who who ) const;
  inline bool	    	canExec( Who who ) const;

  inline const FilePath &   getName( void ) const;
  inline const char *	    getFileName( void ) const;
  inline const char *	    getModeString( void ) const;
  inline const char *	    getUserName( void ) const;
  inline const char *	    getGroupName( void ) const;

  inline FileStat & 	stat( const char * fileName );
  inline FileStat & 	stat( int fd, bool keepName = false );

  inline FileStat &	lstat( const char * fileName );

  bool			setTimes( time_t accessTime,
				  time_t modificationTime );

  bool			setMode( mode_t mode );
  bool			setMode( Who who, What what, bool on = true );

  inline bool	    	setRead( Who who, bool on = true );
  inline bool	    	setWrite( Who who, bool on = true );
  inline bool	    	setExec( Who who, bool on = true );

  bool			setUser( uid_t uid );
  bool			setGroup( gid_t gid );
  bool			setOwner( uid_t uid, gid_t gid );

  inline int		getSysError( void ) const;

  inline FileStat & 	operator () ( const char * fileName );
  inline FileStat & 	operator () ( int fd, bool keepName = false );

  inline FileStat &	operator = ( const FileStat & rhs );

  inline int		compare( const FileStat & two ) const;

  inline bool	    	operator == ( const FileStat & rhs ) const;
  inline bool	    	operator <  ( const FileStat & rhs ) const;
  inline bool		operator != ( const FileStat & rhs ) const;
  inline bool		operator >  ( const FileStat & rhs ) const;
  inline bool		operator <= ( const FileStat & rhs ) const;
  inline bool		operator >= ( const FileStat & rhs ) const;

  std::ostream &	toStream( std::ostream & dest = std::cout ) const;

  bool		clear( void );

  bool		    good( void ) const;
  inline bool	    exist( void ) const;
  const char *	    error( void ) const;
  std::ostream &    dumpInfo( std::ostream &	dest = std::cerr,
			      const char *	prefix = "    " ) const;

  inline DumpInfo< FileStat >
  dump( const char * prefix = "    " ) const {
    return( DumpInfo< FileStat >( *this, prefix ) );
  }

  static const int badFd;

private:

  bool	canDo( mode_t uMode, mode_t gMode, mode_t oMode ) const;

  void 	setStrings( bool keepName = false );
  void  setStrings( const char * fileName );

  void	setUserString( void );
  void	setGroupString( void );
  void	setModeString( void );

  int	fd;

  FilePath	name;
  Str		userName;
  Str		groupName;
  Str		modeString;

  struct stat	st;

  int	sysError;

};

inline
FileStat::FileStat()
{
  fd = badFd;
  memset( &st, 0, sizeof( st ) );
  sysError = ENOENT;
}


inline
FileStat::FileStat( const char * fileName, bool linkStat )
{
  fd = badFd;
  sysError = 0;
  if( linkStat )
    lstat( fileName );
  else
    stat( fileName );
}

inline
FileStat::FileStat( int fileDescriptor )
{
  fd = fileDescriptor;
  sysError = 0;
  stat( fd );
}

inline
FileStat::FileStat( const FileStat & from )
  : fd( from.fd ),
    name( from.name ),
    userName( from.userName ),
    groupName( from.groupName ),
    modeString( from.modeString ),
    st( from.st ),
    sysError( from.sysError )
{
}

inline
uid_t
FileStat::getUID( void ) const
{
  return( st.st_uid );
}


inline
gid_t
FileStat::getGID( void ) const
{
  return( st.st_gid );
}


inline
mode_t
FileStat::getMode( void ) const
{
  return( st.st_mode );
}


inline
FileStat::size_type
FileStat::getSize( void ) const
{
  return( st.st_size );
}


inline
dev_t
FileStat::getDevice( void ) const
{
  return( st.st_dev );
}

inline
dev_t
FileStat::getDeviceType( void ) const
{
  return( st.st_rdev );
}

inline
ino_t
FileStat::getInode( void ) const
{
  return( st.st_ino );
}

inline
nlink_t
FileStat::getHardLinks( void ) const
{
  return( st.st_nlink );
}

inline
unsigned long
FileStat::getBlockSize( void ) const
{
  return( st.st_blksize );
}

inline
unsigned long
FileStat::getBlocks( void ) const
{
  return( st.st_blocks );
}


inline
time_t
FileStat::getAccessTime( void ) const
{
  return( st.st_atime );
}

inline
time_t
FileStat::getModificationTime( void ) const
{
  return( st.st_mtime );
}

inline
time_t
FileStat::getStatusChangeTime( void ) const
{
  return( st.st_ctime );
}


inline
bool
FileStat::isLink( void ) const
{
  return( S_ISLNK( getMode() ) );
}

inline
bool
FileStat::isReg( void ) const
{
  return( S_ISREG( getMode() ) );
}

inline
bool
FileStat::isDir( void ) const
{
  return( S_ISDIR( getMode() ) );
}


inline
bool
FileStat::isBlock( void ) const
{
  return( S_ISBLK( getMode() ) );
}


inline
bool
FileStat::isChar( void ) const
{
  return( S_ISCHR( getMode() ) );
}


inline
bool
FileStat::isFifo( void ) const
{
  return( S_ISFIFO( getMode() ) );
}

inline
bool
FileStat::isSocket( void ) const
{
  return( S_ISSOCK( getMode() ) );
}


inline
bool
FileStat::isSetUID( void ) const
{
  return( getMode() & S_ISUID );
}

inline
bool
FileStat::isSetGID( void ) const
{
  return( getMode() & S_ISGID );
}



inline
bool
FileStat::canRead( void ) const
{
  return( canDo( S_IRUSR, S_IRGRP, S_IROTH ) );
}


inline
bool
FileStat::canWrite( void ) const
{
  return( canDo( S_IWUSR, S_IWGRP, S_IWOTH ) );
}


inline
bool
FileStat::canExec( void ) const
{
  return( canDo( S_IXUSR, S_IXGRP, S_IXOTH ) );
}


inline
bool
FileStat::canRead( Who who ) const
{
  if( (who & USER) == true && (getMode() & S_IRUSR ) )
    return( true );

  if( (who & GROUP) == true && (getMode() & S_IRGRP) )
    return( true );

  if( (who & OTHER) == true && (getMode() & S_IROTH ) )
    return( true );

  return( false );
}


inline
bool
FileStat::canWrite( Who who ) const
{
  if( (who & USER) == true && (getMode() & S_IWUSR ) )
    return( true );

  if( (who & GROUP) == true && (getMode() & S_IWGRP ) )
    return( true );

  if( (who & OTHER) == true && (getMode() & S_IWOTH ) )
    return( true );

  return( false );
}


inline
bool
FileStat::canExec( Who who ) const
{
  if( (who & USER) == true && (getMode() & S_IXUSR ) )
    return( true );

  if( (who & GROUP) == true && (getMode() & S_IXGRP ) )
    return( true );

  if( (who & OTHER) == true && (getMode() & S_IXOTH ) )
    return( true );

  return( false );
}

inline
const FilePath &
FileStat::getName( void ) const
{
  return( name );
}

inline
const char *
FileStat::getFileName( void ) const
{
  return( name );
}

inline
const char *
FileStat::getModeString( void ) const
{
  return( modeString );
}

inline
const char *
FileStat::getUserName( void ) const
{
  return( userName );
}

inline
const char *
FileStat::getGroupName( void ) const
{
  return( groupName );
}


inline
FileStat &
FileStat::stat( const char * fileName )
{
  fd = badFd;

  if( ::stat( fileName, &st ) )
    sysError = errno;
  else
    sysError = 0;

  setStrings( fileName );

  return( *this );
}

inline
FileStat &
FileStat::stat( int fileDesc, bool keepName )
{
  fd = fileDesc;

  if( ::fstat( fd, &st ) )
    sysError = errno;
  else
    sysError = 0;

  setStrings( keepName );

  return( *this );
}

inline
FileStat &
FileStat::lstat( const char * fileName )
{
  fd = badFd;

  if( ::lstat( fileName, &st ) )
    sysError = errno;
  else
    sysError = 0;

  setStrings( fileName );

  return( *this );
}

inline
bool
FileStat::setRead( Who who, bool on )
{
  return( setMode( who, READ, on ) );
}

inline
bool
FileStat::setWrite( Who who, bool onOff )
{
  return( setMode( who, WRITE, onOff ) );
}

inline
bool
FileStat::setExec( Who who, bool onOff )
{
  return( setMode( who, EXEC, onOff ) );
}

inline
int
FileStat::getSysError( void ) const
{
  return( sysError );
}

inline
FileStat &
FileStat::operator () ( const char * fileName )
{
  return( stat( fileName ) );
}

inline
FileStat &
FileStat::operator () ( int f, bool keepName )
{
  return( stat( f, keepName ) );
}

inline
FileStat &
FileStat::operator = ( const FileStat & rhs )
{
  fd		= rhs.fd;
  name		= rhs.name;
  userName	= rhs.userName;
  groupName	= rhs.groupName;
  modeString	= rhs.modeString;
  st		= rhs.st;
  sysError	= rhs.sysError;

  return( *this );
}

inline
int
FileStat::compare( const FileStat & two ) const
{
  return( strcmp( name, two.name ) );
}

inline
bool
FileStat::operator == ( const FileStat & two ) const
{
  return( compare( two ) == 0 );
}

inline
bool
FileStat::operator <  ( const FileStat & two ) const
{
  return( compare( two ) < 0 );
}

inline
bool
FileStat::operator != ( const FileStat & rhs ) const
{
  return( ! (*this == rhs) );
}

inline
bool
FileStat::operator > ( const FileStat & rhs ) const
{
  return( rhs < *this );
}

inline
bool
FileStat::operator <= ( const FileStat & rhs ) const
{
  return( ! (rhs < *this) );
}

inline
bool
FileStat::operator >= ( const FileStat & rhs ) const
{
  return( ! (*this < rhs) );
}

inline
bool
FileStat::exist( void ) const
{
  return( ! (getSysError() == ENOENT ) );
}

inline
int
compare( const FileStat & one, const FileStat & two )
{
  return( one.compare( two ) );
}

inline
std::ostream &
operator << ( std::ostream & dest, const FileStat & obj )
{
  return( obj.toStream( dest ) );
}

}; // namespace clue

/**
    Types: - data types defined by this header

    	FileStat	class

  	Who
  	    This is a bitmast for a files permision bits that specify
  	    who (i.e. user, group, other, all).

  	What
  	    This is a bitmask for a files permision bits that specify
  	    the type of access (i.e. read, write, exec).

    Constructors:

  	inline
    	FileStat(void);
  	    Construct an empty FileStat.

  	inline
  	FileStat( const char * fileName, bool linkStat = false )
  	    Construct a FileStat initalizing it by getting the
  	    stats for 'fileName'. If linkStat is true and
  	    the file is a symbolic link. The stats will be on
  	    the symbolic link file instead of the file the link
  	    points to.

  	inline
  	FileStat( int fd )
  	    Construct a FileStat initiaizing it by getting the
  	    stats for 'fd'. 'fd' must be a valid file descriptor
  	    on an open file (See open(2)).

  	inline
  	FileStat( const FileStat & from )
  	    Copy Constructor.

    Public Interface:

  	static const Who USER
  	    Use this to specify the owner of a file.

  	static const Who GROUP
  	    Use this to specify the group of a file.

  	static const Who Other
  	    Use this to specify other users that can access the file.

  	static const What READ
  	    Use this to specify the read permision.

  	static const What WRITE
  	    Use this to specify the write permision.

  	static const What EXEC
  	    Use this to specifiy execute permision.

  	inline
  	uid_t
  	getUID( void ) const
  	    Return the user id of the owner of the file.

  	inline
  	gid_t
  	getGID( void ) const
  	    Return the group id of the file.

  	inline
  	mode_t
  	getMode( void ) const
  	    Return the complete mode (permisions) of the file.

  	inline
  	off_t
  	getSize( void ) const
  	    Return the size of the file.

  	inline
  	dev_t
  	getDevice( void ) const
  	    Returns the file's device.

  	inline
  	dev_t
  	getDeviceType( void ) const
  	    Return the file's device type.

  	inline
  	dev_t
  	getInode( void ) const
  	    Return the inode number of the file.

  	inline
  	nlink_t
  	getHardLinks( void ) const
  	    Return the number of hardlinks to the file.

  	inline
  	unsigned long
  	getBlockSize( void ) const
  	    Return the block size for the file.

  	inline
  	unsigned long
  	getBlocks( void ) const
  	    Return the number of blocks for the file.

  	inline
  	time_t
  	getAccessTime( void ) const
  	    Return the time of the last access to the file.

  	inline
  	time_t
  	getModificationTime( void ) const
  	    Return the time of the last modification to the file.

  	inline
  	time_t
  	getStatusChangeTime( void ) const
  	    Return the time of the last status change to the file.

  	inline
  	bool
  	isLink( void ) const
  	    Return true if the file is a symbolic link.

  	inline
  	bool
  	isReg( void ) const
  	    Return true if the file is a regular file.

  	inline
  	bool
  	isDir( void ) const
  	    Return true if the file is a directory.

  	inline
  	bool
  	isBlock( void ) const
  	    Return true if the file is a block special file.

  	inline
  	bool
  	isChar( void ) const
  	    Return true if the file is a character special file.

  	inline
  	bool
  	isFifo( void ) const
  	    Return true if the file is a FIFO.

  	inline
  	bool
  	isSocket( void ) const
  	    Return true if the file is a unix socket file.

  	inline
  	bool
  	isSetUID( void ) const
  	    Return true if the file has the sticky user bit set.

  	inline
  	bool
  	isSetGID( void ) const
  	    Return true if the file has the sticky group bit set.

  	inline
  	bool
  	canRead( void ) const
  	    Return true if the current application can open
  	    the file for reading. This uses the applications
  	    effective uid and gid along with the files permisions
  	    to determine accessiblilty.

  	inline
  	bool
  	canWrite( void ) const
  	    Return true if the current application can open
  	    the file for writing. This uses the applications
  	    effective uid and gid along with the files permisions
  	    to determine accessiblilty.

  	inline
  	bool
  	canWrite( void ) const
  	    Return true if the current application can open
  	    the file for execution. This uses the applications
  	    effective uid and gid along with the files permisions
  	    to determine accessiblilty.

  	inline
  	bool
  	canRead( Who who ) const
  	    Returns true if any of the bits in who has read access.

  	inline
  	bool
  	canWrite( Who who ) const
  	    Returns true if any of the bits in who has write access.

  	inline
  	bool
  	canExec( Who who ) const
  	    Returns true if any of the bits in who has write access.

  	inline
  	const char *
  	getName( void ) const
  	    Return the full path name of the file the FileStat is for.

  	inline
  	const char *
  	getModeString( void ) const
  	    Returns the mode as a string. The format is like
  	    the one you get when you use 'ls -l' (i.e. '-rwxrwxr-x' ).

  	inline
  	const char *
  	getUserName( void ) const
  	    Return the name of the file's owner.

  	inline
  	const char *
  	getGroupName( void ) const
  	    Return the name of the file's group.

  	inline
  	FileStat &
  	stat( const char * fileName )
  	    Set the FileStat by getting the information on 'fileName'.

  	inline
  	FileStat &
  	stat( int fd, bool keepName = false )
  	    Set the FileStat by getting the information on the file
  	    file descriptor 'fd'. If keepName is true the file's name
  	    will not be reset.

  	inline
  	FileStat &
  	lstat( const char * fileName )
  	    Set the FileStat by getting the information on the file
  	    'fileName'. If 'fileName' is a sybolic link, get the
  	    information on the link and not what it points to.

  	bool
  	setMode( mode_t mode )
  	    Set the file's mode (i.e. permisions) to the value
  	    specified by 'mode'. Returns true if the mode was changed.

  	bool
  	setMode( Who who, What what, bool on = true )
  	    Set the files mode by changed the items specified by
  	    'who' and 'what' to 'on'.
  	    (i.e. setMode( USER | GROUP, READ | WRITE, false ) will
  	    turn off read and write access for the owner and group, but
  	    will not modify any other bits). Returns true if the
  	    set was successfull.

  	inline
  	bool
  	setRead( Who who, bool on = true )
  	    Change the files read bit for 'who' to 'on'. Returns true
  	    if the change was successful.

  	inline
  	bool
  	setWrite( Who who, bool on = true )
  	    Change the files write bit for 'who' to 'on'. Returns true
  	    if the change was successful.

  	inline
  	bool
  	setExec( Who who, bool on = true )
  	    Change the files execute bit for 'who' to 'on'. Returns true
  	    if the change was successful.

  	bool
  	setUser( uid_t uid )
  	    Change the file's owner to 'uid'. Returns true if the
  	    change was successful.

  	bool
  	setGroup( gid_t gid )
  	    Change the file's group to 'gid'. Returns true if the
  	    change was successful.

  	bool
  	setOwner( uid_t uid, gid_t gid )
  	    Change the files owner to 'uid' and group to 'gid'. Returns
  	    true if the change was successful.

  	inline
  	int
  	getSysError( void ) const
  	    Get the 'errno' of the system error that caused the last
  	    operation to fail.

  	inline
  	FileStat &
  	operator () ( const char * fileName )
  	    Set the FileStat by getting the information on 'fileName'.

  	inline
  	FileStat &
  	operator () ( int fd, bool keepName = false )
  	    Set the FileStat by getting the information on the file
  	    file descriptor 'fd'. If keepName is true the file's name
  	    will not be reset.

  	inline
  	FileStat &
  	operator = ( const FileStat & rhs )
  	    Set the FileStat from rhs.

  	inline
  	int
  	compare( const FileStat & two ) const
  	    Compare the FileStat's value with the value of two and
  	    return 0 if == two, <0 if < two  or >0 if > two.
  	    This uses the file's name as the basis for comparison.

  	inline
  	bool
  	operator == ( const FileStat & rhs ) const
  	    Returns true if FileStat == rhs.

  	inline
  	bool
  	operator <  ( const FileStat & rhs ) const
  	    Returns true if FileStat < rhs.

  	std::ostream &
  	toStream( std::ostream & dest = std::cout ) const
  	    Write a formated string of the FileStat to 'dest'.

  	bool
  	const good( void ) const
  	    Return true if there are no errors associated with the
  	    FileStat.

  	const char *
  	error( void ) const
  	    Return a string description of the state of the class.

  	const char *
  	getClassName( void ) const
  	    Return the class's name (i.e. "FileStat" ).

  	const char *
  	getVersion( bool withPrjVer = true ) const
  	    Return the version string for the FileStat. If
  	    withPrjVer == true, the project version info will also
  	    be returned.

  	virtual
  	std::ostream &
  	dumpInfo( std::ostream &	dest = std::cerr,
  		  const char *	prefix = "    ",
  		  bool		showVer = true ) const
  	    Output detailed information about the current
  	    state of the FileStat.

  	static const ClassVersion version;
  	    This contains the version information for the FileStat class.

  	static const int badFd
  	    This is a constant that represents an invalid file descriptor.

    Associated Functions:

    	std::ostream &
    	operator <<( std::ostream & dest, const FileStat & obj )
  	    Uses FileStat::toStream to write the FileStat as a string
  	    to the std::ostream.


  	int
  	compare( const FileStat & one, const FileStat & two )
  	    Returns the differance between one and two by comparing
  	    their values.


**/
#endif // ! def _clue_FileStat_hpp_

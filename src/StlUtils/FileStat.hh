#ifndef _FileStat_hh_
#define _FileStat_hh_
//
// File:        FileStat.hh
// Project:	Clue
// Desc:        
//
//  FileStat is provides information about files and modification
//  of file permisions. It is basically just a wrapper around
//  the stat and chmod calls.
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/11/95 10:10
//
// Revision History: (See end of file for Revisio Log)
//
// $Id$
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <Bitmask.hh>
#include <ClueSysStat.hh>
#else
#include <ClueCfg.hh>
#include <Str.hh>
#include <FilePath.hh>
#include <Bitmask.hh>
#endif

#if defined( CLUE_DEBUG )
#define inline
#endif

class FileStat
{

public:

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
  inline off_t	    	getSize( void ) const;
  
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

  inline const char *   getName( void ) const;
  inline const char *	getModeString( void ) const;
  inline const char *	getUserName( void ) const;
  inline const char * 	getGroupName( void ) const;
  
  inline FileStat & 	stat( const char * fileName );
  inline FileStat & 	stat( int fd, bool keepName = false );

  inline FileStat &	lstat( const char * fileName );
  
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

  inline FileStat &	operator = ( const FileStat & rhs ) const;
  
  inline int		compare( const FileStat & two ) const;
  
  inline bool	    	operator == ( const FileStat & rhs ) const;
  inline bool	    	operator <  ( const FileStat & rhs ) const;

  // libClue Common Class Methods
  
  ostream &		toStream( ostream & dest = cout ) const;
  
  bool		good() const;
  const char *	error() const;
  const char *	getClassName( void ) const;
  const char *	getVersion( bool withPrjVer = true ) const;
  ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;
  
  static const ClassVersion version;

  static const int badFd;
  
protected:

private:

  bool	canDo( mode_t uMode, mode_t gMode, mode_t oMode ) const;
  
  void 	setStrings( bool keepName = false );
  void  setStrings( const char * fileName );

  void	setUserString( void );
  void	setGroupString( void );
  void	setModeString( void );
  
  int	fd;
  
  RWCString  name;
  RWCString  userName;
  RWCString  groupName;
  RWCString  modeString;

  struct stat	st;
  
  int	sysError;
  
};

#ifndef inline
#include <FileStat.ii>
#else
#undef inline

ostream &
operator << ( ostream & dest, const FileStat & obj );
    
int
compare( const FileStat & one, const FileStat & two );

#endif


//  Types: - data types defined by this header
//
//  	FileStat	class
//
//	Who
//	    This is a bitmast for a files permision bits that specify
//	    who (i.e. user, group, other, all). 
//
//	What
//	    This is a bitmask for a files permision bits that specify
//	    the type of access (i.e. read, write, exec).
//
//  Constructors:
//
//	inline
//  	FileStat(void);
//	    Construct an empty FileStat.
//
//	inline
//	FileStat( const char * fileName, bool linkStat = false )
//	    Construct a FileStat initalizing it by getting the
//	    stats for 'fileName'. If linkStat is true and
//	    the file is a symbolic link. The stats will be on
//	    the symbolic link file instead of the file the link
//	    points to.
//
//	inline
//	FileStat( int fd )
//	    Construct a FileStat initiaizing it by getting the
//	    stats for 'fd'. 'fd' must be a valid file descriptor
//	    on an open file (See open(2)).
//
//	inline
//	FileStat( const FileStat & from )
//	    Copy Constructor.
//
//  Public Interface:
//
//	static const Who USER
//	    Use this to specify the owner of a file.
//
//	static const Who GROUP
//	    Use this to specify the group of a file.
//
//	static const Who Other
//	    Use this to specify other users that can access the file.
//
//	static const What READ
//	    Use this to specify the read permision.
//
//	static const What WRITE
//	    Use this to specify the write permision.
//
//	static const What EXEC
//	    Use this to specifiy execute permision.
//
//	inline
//	uid_t
//	getUID( void ) const
//	    Return the user id of the owner of the file.
//
//	inline
//	gid_t
//	getGID( void ) const
//	    Return the group id of the file.
//
//	inline
//	mode_t
//	getMode( void ) const
//	    Return the complete mode (permisions) of the file.
//
//	inline
//	off_t
//	getSize( void ) const
//	    Return the size of the file.
//
//	inline
//	dev_t
//	getDevice( void ) const
//	    Returns the file's device.
//
//	inline
//	dev_t
//	getDeviceType( void ) const
//	    Return the file's device type.
//
//	inline
//	dev_t
//	getInode( void ) const
//	    Return the inode number of the file.
//
//	inline
//	nlink_t
//	getHardLinks( void ) const
//	    Return the number of hardlinks to the file.
//
//	inline
//	unsigned long
//	getBlockSize( void ) const
//	    Return the block size for the file.
//
//	inline
//	unsigned long
//	getBlocks( void ) const
//	    Return the number of blocks for the file.
//
//	inline
//	time_t
//	getAccessTime( void ) const
//	    Return the time of the last access to the file.
//
//	inline
//	time_t
//	getModificationTime( void ) const
//	    Return the time of the last modification to the file.
//
//	inline
//	time_t
//	getStatusChangeTime( void ) const
//	    Return the time of the last status change to the file.
//
//	inline
//	bool
//	isLink( void ) const
//	    Return true if the file is a symbolic link.
//
//	inline
//	bool
//	isReg( void ) const
//	    Return true if the file is a regular file.
//
//	inline
//	bool
//	isDir( void ) const
//	    Return true if the file is a directory.
//
//	inline
//	bool
//	isBlock( void ) const
//	    Return true if the file is a block special file.
//
//	inline
//	bool
//	isChar( void ) const
//	    Return true if the file is a character special file.
//	    
//	inline
//	bool
//	isFifo( void ) const
//	    Return true if the file is a FIFO.
//
//	inline
//	bool
//	isSocket( void ) const
//	    Return true if the file is a unix socket file.
//
//	inline
//	bool
//	isSetUID( void ) const
//	    Return true if the file has the sticky user bit set.
//
//	inline
//	bool
//	isSetGID( void ) const
//	    Return true if the file has the sticky group bit set.
//
//	inline
//	bool
//	canRead( void ) const
//	    Return true if the current application can open
//	    the file for reading. This uses the applications
//	    effective uid and gid along with the files permisions
//	    to determine accessiblilty.
//
//	inline
//	bool
//	canWrite( void ) const
//	    Return true if the current application can open
//	    the file for writing. This uses the applications
//	    effective uid and gid along with the files permisions
//	    to determine accessiblilty.
//
//	inline
//	bool
//	canWrite( void ) const
//	    Return true if the current application can open
//	    the file for execution. This uses the applications
//	    effective uid and gid along with the files permisions
//	    to determine accessiblilty.
//
//	inline
//	bool
//	canRead( Who who )
//	    Returns true if any of the bits in who has read access.
//
//	inline
//	bool
//	canWrite( Who who )
//	    Returns true if any of the bits in who has write access.
//
//	inline
//	bool
//	canExec( Who who )
//	    Returns true if any of the bits in who has write access.
//
//	inline
//	const char *
//	getName( void ) const
//	    Return the full path name of the file the FileStat is for.
//
//	inline
//	const char *
//	getModeString( void ) const
//	    Returns the mode as a string. The format is like
//	    the one you get when you use 'ls -l' (i.e. '-rwxrwxr-x' ).
//
//	inline
//	const char *
//	getUserName( void ) const
//	    Return the name of the file's owner.
//
//	inline
//	const char *
//	getGroupName( void ) const
//	    Return the name of the file's group.
//
//	inline
//	FileStat &
//	stat( const char * fileName )
//	    Set the FileStat by getting the information on 'fileName'.
//
//	inline
//	FileStat &
//	stat( int fd, bool keepName = false )
//	    Set the FileStat by getting the information on the file
//	    file descriptor 'fd'. If keepName is true the file's name
//	    will not be reset.
//
//	inline
//	FileStat &
//	lstat( const char * fileName )
//	    Set the FileStat by getting the information on the file
//	    'fileName'. If 'fileName' is a sybolic link, get the
//	    information on the link and not what it points to.
//
//	bool
//	setMode( mode_t mode )
//	    Set the file's mode (i.e. permisions) to the value
//	    specified by 'mode'. Returns true if the mode was changed.
//
//	bool
//	setMode( Who who, What what, bool on = true )
//	    Set the files mode by changed the items specified by
//	    'who' and 'what' to 'on'.
//	    (i.e. setMode( USER | GROUP, READ | WRITE, false ) will
//	    turn off read and write access for the owner and group, but
//	    will not modify any other bits). Returns true if the
//	    set was successfull.
//
//	inline
//	bool
//	setRead( Who who, bool on = true )
//	    Change the files read bit for 'who' to 'on'. Returns true
//	    if the change was successful.
//  
//	inline
//	bool
//	setWrite( Who who, bool on = true )
//	    Change the files write bit for 'who' to 'on'. Returns true
//	    if the change was successful.
//  
//	inline
//	bool
//	setExec( Who who, bool on = true )
//	    Change the files execute bit for 'who' to 'on'. Returns true
//	    if the change was successful.
//
//	bool
//	setUser( uid_t uid )
//	    Change the file's owner to 'uid'. Returns true if the
//	    change was successful.
//
//	bool
//	setGroup( uid_t uid )
//	    Change the file's group to 'gid'. Returns true if the
//	    change was successful.
//
//	bool
//	setOwner( uid_t uid, gid_t gid )
//	    Change the files owner to 'uid' and group to 'gid'. Returns
//	    true if the change was successful.
//
//	inline
//	int
//	getSysError( void ) const
//	    Get the 'errno' of the system error that caused the last
//	    operation to fail.
//
//	inline
//	FileStat &
//	operator () ( const char * fileName )
//	    Set the FileStat by getting the information on 'fileName'.
//
//	inline
//	FileStat &
//	operator () ( int fd, bool keepName = false )
//	    Set the FileStat by getting the information on the file
//	    file descriptor 'fd'. If keepName is true the file's name
//	    will not be reset.
//
//	inline
//	FileStat &
//	operator = ( const FileStat & rhs )
//	    Set the FileStat from rhs.
//
//	inline
//	int
//	compare( const FileStat & two ) const
//	    Compare the FileStat's value with the value of two and
//	    return 0 if == two, <0 if < two  or >0 if > two.
//	    This uses the file's name as the basis for comparison.
//	    
//	inline
//	bool
//	operator == ( const FileStat & rhs ) const
//	    Returns true if FileStat == rhs.
//
//	inline
//	bool
//	operator <  ( const FileStat & rhs ) const
//	    Returns true if FileStat < rhs.
//
//	ostream &
//	toStream( ostream & dest = cout ) const
//	    Write a formated string of the FileStat to 'dest'.
//
//	bool
//	const good( void ) const
//	    Return true if there are no errors associated with the
//	    FileStat.
//
//	const char *
//	error( void ) const
//	    Return a string description of the state of the class.
//
//	const char *
//	getClassName( void ) const
//	    Return the class's name (i.e. "FileStat" ).
//
//	const char *
//	getVersion( void ) const
//	    Return the version string for the FileStat. If
//	    withPrjVer == true, the project version info will also
//	    be returned.
//
//	virtual
//	ostream &
//	dumpInfo( ostream &	dest = cerr,
//		  const char *	prefix = "    ",
//		  bool		showVer = true );
//	    Output detailed information about the current
//	    state of the FileStat. 
//
//	static const ClassVersion version;
//	    This contains the version information for the FileStat class.
//
//	static const int badFd
//	    This is a constant that represents an invalid file descriptor.
//
//  Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const FileStat & obj )
//	    Uses FileStat::toStream to write the FileStat as a string
//	    to the ostream.
//
//
//	int
//	compare( const FileStat & one, const FileStat & two )
//	    Returns the differance between one and two by comparing
//	    their values.
//
// See Also:
//
//	stat(2)
//
// Files:
//
//	FileStat.hh, FileStat.ii, libClue.a
//
//  Documented Ver: 2.2
//  Tested Ver: 2.2
//	
// Revision Log:
//
// $Log$
// Revision 2.2  1996/11/04 14:39:22  houghton
// Restructure header comments layout.
// Updated and verified header comment documentation.
// Changed varaibles to use RWCString instead of Str and or FilePath
//     (as required by Mike Alexandar).
// Changed getName to return a const char * instead of a FilePath
//     (as required by Mike Alexandar).
//
// Revision 2.1  1995/11/10 12:47:11  houghton
// Change to Version 2
//
// Revision 1.5  1995/11/05  16:04:15  houghton
// Revised
//
//
#endif // ! def _FileStat_hh_ 

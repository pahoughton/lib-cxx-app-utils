#ifndef _FileStat_hh_
#define _FileStat_hh_
//
// File:        FileStat.hh
// Desc:        
//
//
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/11/95 10:10
//
// Revision History:
//
// $Log$
// Revision 1.2  1995/11/05 12:55:20  houghton
// Put inlines in their own source file
// Change to be more consistant with the C++ Standard
//
//


#include <ClueConfig.hh>

#include <Str.hh>

#include <Bitmask.hh>

#include <sys/stat.h>

#ifdef  CLUE_DEBUG
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
  
  inline FileStat();
  inline FileStat( const char * fileName, bool linkStat = false );
  inline FileStat( int fd );
  
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

  inline const char * 	getName( void ) const;
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
  
  inline FileStat & 	operator () ( const char * fileName );
  inline FileStat & 	operator () ( int fd, bool keepName = false );

  inline int		compare( const FileStat & two ) const;
  
  inline bool	    	operator == ( const FileStat & two ) const;
  inline bool	    	operator <  ( const FileStat & two ) const;
  
  bool			good() const;
  const char *		error() const;
  const char *		getClassName( void ) const;
  ostream &		toStream( ostream & dest = cout ) const;
  ostream &		dumpInfo( ostream & dest = cerr ) const;
  
  static const int badFd;
  
  static const char version[];
  
protected:

private:

  bool	canDo( mode_t uMode, mode_t gMode, mode_t oMode ) const;
  
  void 	setStrings( bool keepName = false );
  void  setStrings( const char * fileName );

  void	setUserString( void );
  void	setGroupString( void );
  void	setModeString( void );
  
  int	fd;
  
  Str   name;
  Str 	userName;
  Str 	groupName;
  Str  	modeString;

  struct stat	st;
  
  int	sysError;
  
};

#ifndef inline
#include <FileStat.ii>
#else
#undef inline

int
compare( const FileStat & one, const FileStat & two );

ostream &
operator<<( ostream & dest, const FileStat & obj );

#endif


//  Quick Start: - short example of class usage
//
//  Data Types: - data types defined by this header
//
//  	FileStat	class
//
//  Constructors:
//
//  	FileStat( );
//
//  Destructors:
//
//  Public Interface:
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. FileStat )
//
//  	virtual Bool
//  	good( void ) const;
//  	    Returns true if there are no detected errors associated
//  	    with this class, otherwise FALSE.
//
//  	virtual const char *
//  	error( void ) const
//  	    Returns as string description of the state of the class.
//
//  Protected Interface:
//
//  Private Methods:
//
//  Other Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const FileStat & obj );
#endif // ! def _FileStat_hh_ 

#ifndef _FileLock_hh_
#define _FileLock_hh_
//
// File:        FileLock.hh
// Project:	StlUtils ()
// Desc:        
//
//  Provides unix file locking (flock) functionallity.
//
// Quick Start: - short example of class usage
//
// Author:      Paul A. Houghton - (paul.houghton@mci.com)
// Created:     09/12/97 11:04
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//
//  $Id$ 
//

#include <StlUtilsConfig.hh>
#include <FilePath.hh>
#include <DumpInfo.hh>
#include <iostream>
#include <vector>

#if defined( STLUTILS_DEBUG )
#define inline
#endif


class FileLock
{

public:

  enum Type
  {
    Read = 0,
    Shared = 0,
    Write = 1,
    Exclusive = 1,
    Unlock = 2,
    T_Undefined
  };
  
  FileLock( const char * fileName, ios::open_mode mode = ios::in );
  FileLock( int fd );
  
  virtual ~FileLock( void );

  inline bool	lockread( streamoff	offset = 0,
			  ios::seek_dir dir = ios::beg,
			  size_t	amount = 0,
			  bool		block = true );

  inline bool	lockwrite( streamoff	    offset = 0,
			   ios::seek_dir    dir = ios::beg,
			   size_t	    amount = 0,
			   bool		    block = true );

  inline bool	unlock( streamoff	offset = 0,
			ios::seek_dir	dir = ios::beg,
			size_t		amount = 0 );
  
  bool	lock( Type  type,
	      streamoff	    offset = 0,
	      ios::seek_dir dir = ios::beg,
	      size_t	    amount = 0,
	      bool	    block = true );

  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  bool			blocked( void ) const;
  virtual int		oserror( void ) const;
  virtual bool		clear( void );
  
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  inline DumpInfo< FileLock >
  dump( const char * preifx = "    ", bool showVer = true ) const;

  static const ClassVersion version;

  static const char *	typeName( Type t );
  
protected:

  FilePath  lockFn;
  int	    fd;

  struct Lock
  {
    Type	    type;
    streamoff	    offset;
    ios::seek_dir   dir;
    size_t	    amount;

    Lock( void )
      : type( T_Undefined ), offset( 0 ), dir( ios::beg ), amount( 0 ) {};
    
    Lock( Type		t,
	  streamoff	o = 0,
	  ios::seek_dir	d = ios::beg,
	  size_t	a = 0 )
      : type( t ), offset( o ), dir( d ), amount( a ) {};
    
  };

  typedef vector< Lock >	LockList;

  LockList	locks;
  int		oserrno;
  bool		closefd;
  
private:

  FileLock( const FileLock & from );
  FileLock & operator =( const FileLock & from );

};

#if !defined( inline )
#include <FileLock.ii>
#else
#undef inline

#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	FileLock	class
//
//  Constructors:
//
//  	FileLock( );
//
//  Destructors:
//
//  Public Interface:
//
//	virtual ostream &
//	write( ostream & dest ) const;
//	    write the data for this class in binary form to the ostream.
//
//	virtual istream &
//	read( istream & src );
//	    read the data in binary form from the istream. It is
//	    assumed it stream is correctly posistioned and the data
//	    was written to the istream with 'write( ostream & )'
//
//	virtual ostream &
//	toStream( ostream & dest ) const;
//	    output class as a string to dest (used by operator <<)
//
//	virtual istream &
//	fromStream( istream & src );
//	    Set this class be reading a string representation from
//	    src. Returns src.
//
//  	virtual Bool
//  	good( void ) const;
//  	    Return true if there are no detected errors associated
//  	    with this class, otherwise false.
//
//  	virtual const char *
//  	error( void ) const;
//  	    Return a string description of the state of the class.
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. FileLock )
//
//  	virtual const char *
//  	getVersion( bool withPrjVer = true ) const;
//  	    Return the version string of this class.
//
//	virtual ostream &
//	dumpInfo( ostream & dest, const char * prefix, bool showVer );
//	    output detail info to dest. Includes instance variable
//	    values, state info & version info.
//
//	static const ClassVersion version
//	    Class and project version information. (see ClassVersion.hh)
//
//  Protected Interface:
//
//  Private Methods:
//
//  Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const FileLock & src );
//
//	istream &
//	operator >> ( istream & src, FileLock & dest );
//
// Example:
//
// See Also:
//
// Files:
//
// Documented Ver:
//
// Tested Ver:
//
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 5.3  2003/08/09 11:21:00  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:28:58  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:22  houghton
// Changed Version Num to 5
//
// Revision 4.3  1997/10/22 16:03:01  houghton
// Added file name so it could be placed in the error string.
//
// Revision 4.2  1997/09/21 21:21:14  houghton
// Port(Sun5): had to add a default constructor to prevent compiler crashes.
//
// Revision 4.1  1997/09/17 15:13:31  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:09:19  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/09/16 11:21:18  houghton
// Initial Version.
//
//
#endif // ! def _FileLock_hh_ 


#ifndef _Semaphore_hh_
#define _Semaphore_hh_
//
// File:        Semaphore.hh
// Project:	StlUtils (%PP%)
// Item:   	%PI% (%PF%)
// Desc:        
//
//  Provides an interface to Unix semaphores
//
// Quick Start: - short example of class usage
//
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     06/10/97 05:24
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    %PO%
//  Last Mod:	    %PRT%
//  Version:	    %PIV%
//  Status: 	    %PS%
//
//  %PID%
//

#include <StlUtilsConfig.hh>
#include <StlUtilsSem.hh>
#include <iostream>

#if defined( STLUTILS_DEBUG )
#define inline
#endif


class Semaphore
{

public:

  Semaphore( void );
  
  Semaphore( key_t  semKey,
	     int    numSems = 1,
	     int    flags = (IPC_CREAT | 0664) );

  Semaphore( const char *   keyPath,
	     char	    proj = ' ',
	     int	    numSems = 1,
	     int	    flags = (IPC_CREAT | 0664) );
  
  virtual ~Semaphore( void );

  bool	    create( key_t   semKey,
		    int	    numSems = 1,
		    int	    flags = (IPC_CREAT | 0664) );
  
  bool	    create( const char *    keyPath,
		    char	    proj = ' ',
		    int		    numSems = 1,
		    int		    flags = (IPC_CREAT | 0664) );

  bool	    open( key_t semKey, int numSems = 1 );
  bool	    open( const char * keyPath, char proj = ' ', int numSems = 1 );
  
  bool	    remove( void );
  
  bool	    lock( bool wait = true );
  bool	    unlock( void );
  bool	    islocked( void ) const;
  
  bool	    waitfor( void );

  inline bool	wouldBlock( void ) const;

  bool			clear( void );
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  static const ClassVersion version;

  static const key_t	badKey;
  static const int	badSem;

protected:

  inline bool	setError( int err );
  
private:

  Semaphore( const Semaphore & from );
  Semaphore & operator =( const Semaphore & from );

  key_t	    key;
  int	    semId;

  int	    osErrno;
};

#if !defined( inline )
#include <Semaphore.ii>
#else
#undef inline


#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	Semaphore	class
//
//  Constructors:
//
//  	Semaphore( );
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
//  	    Return the name of this class (i.e. Semaphore )
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
//  	operator <<( ostream & dest, const Semaphore & src );
//
//	istream &
//	operator >> ( istream & src, Semaphore & dest );
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
// Revision 5.2  2001/07/26 19:28:57  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:23  houghton
// Changed Version Num to 5
//
// Revision 4.2  1998/03/30 14:17:44  houghton
// Added open() and clear() methods.
//
// Revision 4.1  1997/09/17 15:13:36  houghton
// Changed to Version 4
//
// Revision 3.4  1997/09/17 11:09:23  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/09/16 11:28:12  houghton
// Added islocked method().
//
// Revision 3.2  1997/07/20 18:51:23  houghton
// Bug-Fix: forgot to set default file mode in create( const char *).
//
// Revision 3.1  1997/06/10 13:54:25  houghton
// Initial Version.
//
//
#endif // ! def _Semaphore_hh_ 


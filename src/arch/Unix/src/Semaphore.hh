#ifndef _Semaphore_hh_
#define _Semaphore_hh_
//
// File:        Semaphore.hh
// Project:	Clue
// Desc:        
//
//
//
// Quick Start: - short example of class usage
//
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     06/10/97 05:24
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#include <ClueConfig.hh>
#include <ClueSem.hh>
#include <iostream>

#if defined( CLUE_DEBUG )
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
		    int		    flags = IPC_CREAT );

  bool	    remove( void );
  
  bool	    lock( bool wait = true );
  bool	    unlock( void );
  
  bool	    waitfor( void );

  inline bool	wouldBlock( void ) const;
  
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
// $Log$
// Revision 3.1  1997/06/10 13:54:25  houghton
// Initial Version.
//
//
#endif // ! def _Semaphore_hh_ 

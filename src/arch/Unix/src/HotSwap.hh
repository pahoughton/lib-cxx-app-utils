#ifndef _HotSwap_hh_
#define _HotSwap_hh_
//
// File:        HotSwap.hh
// Project:	StlUtils
// Desc:        
//
//
//
// Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     05/04/99 05:21
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#include <StlUtilsConfig.hh>

#include <FilePath.hh>
#include <FileLock.hh>
#include <Semaphore.hh>

#include <DumpInfo.hh>
#include <iostream>

#if defined( STLUTILS_DEBUG )
#define inline
#endif


class HotSwap
{

public:

  HotSwap( const FilePath &	lockFileName,
	   ios::open_mode	mode );

  virtual ~HotSwap( void );

  // user methods
  bool	    lock( void );
  bool	    check( void );
  bool	    waitForSwap( void );

  // swapper methods
  bool	    swapLock( void );
  bool	    swapUnLock( void );
  
  bool	    swap( const FilePath &  linkName,
		  const FilePath &  linkDest );
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  inline DumpInfo< HotSwap >
  dump( const char * preifx = "    ", bool showVer = true ) const;

  static const ClassVersion version;

protected:

  enum ErrorNum
  {
    E_OK,
    E_NOT_LINK,
    E_UNDEFINED
  };

  bool	setError( int osErr, const char * desc );
  bool	setErrorDesc( int osErr, const char * desc );
  bool	setErrorFn( ErrorNum err, const char * fn );
  bool	setErrorFn( int osErr, const char * fn );
  bool	setErrorFnDesc( int osErr, const char * fn, const char * desc );
  
  static const char *	ErrorDesc[];
  
  FilePath	lockFn;
  Semaphore	sem;
  FileLock 	filelock;

  ErrorNum	errorNum;
  FilePath	errorFileName;
  Str		errorDesc;
  int		osErrno;
  
private:

  HotSwap( const HotSwap & from );
  HotSwap & operator =( const HotSwap & from );

};

#if !defined( inline )
#include <HotSwap.ii>
#else
#undef inline

ostream &
operator << ( ostream & dest, const HotSwap & src );

istream &
operator >> ( istream & src, const HotSwap & dest );


#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	HotSwap	class
//
//  Constructors:
//
//  	HotSwap( );
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
//  	    Return the name of this class (i.e. HotSwap )
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
//  	operator <<( ostream & dest, const HotSwap & src );
//
//	istream &
//	operator >> ( istream & src, HotSwap & dest );
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
// Revision 5.1  2000/05/25 10:33:22  houghton
// Changed Version Num to 5
//
// Revision 4.2  2000/03/21 23:30:56  houghton
// Added swapLock() and swapUnLock() methods.
//
// Revision 4.1  1999/05/09 13:08:19  houghton
// Initial Version.
//
//
#endif // ! def _HotSwap_hh_ 


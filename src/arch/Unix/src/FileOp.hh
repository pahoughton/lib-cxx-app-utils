#ifndef _File_hh_
#define _File_hh_
//
// File:        File.hh
// Project:	StlUtils
// Desc:        
//
//
// Notes:
//
//  This class is not fully developed or tested yet. I have only
//  tested the following so far:
//
//	copy( filename, filename )
//	copy( filename, dir )
//	move( filename, filename )
//	move( filename, dir )
//
//  I have tested the move across devices (file systems) works
//  correctly. But I have not verified it deals with file system
//  full yet.
//
// Quick Start: - short example of class usage
//
// Author:      Paul Houghton 719-527-7834 - (paul.houghton@wcom.com)
// Created:     03/08/98 07:31
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
#include <FileStat.hh>
#include <DumpInfo.hh>
#include <iostream>

#if defined( STLUTILS_DEBUG )
#define inline
#endif


class File
{

public:

  typedef int	size_type;
  
  File( void );
  File( const char * src );
  
  virtual ~File( void );

  bool		copy( const char * dest );
  inline bool	copy( const char * src, const char * dest );
  
  bool		move( const char * dest );
  inline bool	move( const char * src, const char * dest );

  virtual bool		clear( void );
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  inline DumpInfo< File >
  dump( const char * preifx = "    ", bool showVer = true ) const;

  static const ClassVersion version;

protected:

  bool		moveFile( void );
  size_type	readfd( int fd, void * dest, size_t destSize );
  size_type	writefd( int fd, const void * src, size_t srcLen );
  
  bool	setError( int osErr, const char * desc, const char * fn );
  
  FileStat  src;
  FileStat  dest;

  Str	errorDesc;
  int	osError;
  
private:

  // defaults are ok
  // File( const File & from );
  // File & operator =( const File & from );

};

#if !defined( inline )
#include <File.ii>
#else
#undef inline

ostream &
operator << ( ostream & dest, const File & src );

istream &
operator >> ( istream & src, const File & dest );


#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	File	class
//
//  Constructors:
//
//  	File( );
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
//  	    Return the name of this class (i.e. File )
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
//  	operator <<( ostream & dest, const File & src );
//
//	istream &
//	operator >> ( istream & src, File & dest );
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
// Revision 1.1  1998/03/08 18:08:28  houghton
// Initial Version.
//
//
#endif // ! def _File_hh_ 


#ifndef _File_hh_
#define _File_hh_
//
// File:        File.hh
// Desc:        
//
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     08/02/95 04:44
//
// Revision History:
//
// $Log$
// Revision 3.2  1997/09/17 11:09:14  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:25:21  houghton
// Changed to Release 3
//
// Revision 2.1  1995/11/10 12:47:09  houghton
// Change to Version 2
//
// Revision 1.1  1995/11/05  13:12:39  houghton
// Initial implementation of File Class
//
//

#include <StlUtilsConfig.hh>

#include <iostream>
#include <stddef>

#ifdef	STLUTILS_DEBUG
#define inline
#endif

class File
{

public:

  virtual ~File( void ) {};

  virtual void	close( void ) = 0;
  virtual bool	is_open( void ) const = 0;

  inline streampos  seekoff( streamoff  offset, ios::seek_dir  direction );
  inline streampos  seekpos( streampos  pos );
  inline streampos  seek( long  pos );

  virtual streampos seek( ios::seek_dir dir, streamoff offset ) = 0;
  virtual streampos tell( void ) const = 0;

  virtual File &    read( void * dest, size_t amount ) = 0;
  inline File &     read( void * dest, size_t amount, streampos pos );
  inline File &	    read( void * dest, size_t amount,
			  ios::seek_dir dir, streamoff offset );

  inline int	    gcount( void ) const;
  
  virtual File &    write( const void * dest, size_t amount ) = 0;
  inline File &     write( const void * dest, size_t amount, streampos pos );
  inline File &	    write( const void * dest, size_t amount,
			  ios::seek_dir dir, streamoff offset );

  virtual int	    sync( void ) = 0;

  inline int	    rdstate( void ) const;
  virtual bool	    clear( int state = ios::goodbit );
  
  inline bool	    eof( void ) const;
  inline bool	    bad( void ) const;
  inline bool	    fail( void ) const;
  inline int	    errno( void ) const;
  
  inline bool 	    operator !  ( void ) const;

  virtual bool	    	good( void ) const = 0;
  virtual const char * 	error( void ) const = 0;
  virtual const char *	getClassName( void ) const = 0;
  virtual ostream &	dumpInfo( ostream & dest = cerr ) const = 0;

protected:
  
  inline File( void );
  
  inline int	whence( ios::seek_dir dir ) const;

  int	bytesRead;
  int	state;
  int	osErrno;
  
};

#ifndef  inline
#include <File.ii>
#else
#undef inline
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
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. File )
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
//  	operator <<( ostream & dest, const File & obj );

#endif // ! def _File_hh_ 


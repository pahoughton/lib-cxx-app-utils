#ifndef _LockFile_hh_
#define _LockFile_hh_
//
// File:        LockFile.hh
// Desc:        
//
//
//  Quick Start: - short example of class usage
//
//  Data Types: - data types defined by this header
//
//  	LockFile	class
//
//  Constructors:
//
//  	LockFile( );
//
//  Destructors:
//
//  Public Interface:
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. LockFile )
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
//  	operator <<( ostream & dest, const LockFile & obj );
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/14/95 08:38
//
// Revision History:
//
// $Log$
// Revision 6.1  2003/08/09 11:22:45  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:21  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:24  houghton
// Changed to Version 4
//
// Revision 3.1  1996/11/14 01:25:25  houghton
// Changed to Release 3
//
// Revision 2.1  1995/11/10 12:47:13  houghton
// Change to Version 2
//
// Revision 1.1  1995/11/05  12:20:51  houghton
// Initial LockFile.hh
//
//

#include <BinaryFile.hh>

class LockFile : virtual public BinaryFile
{
protected:

  LockFile( void ) {};
  LockFile( const char *    fileName,
	    ios::open_mode  mode,
	    int	    	    perm = 0664 );

public:

  bool	unlock( streamoff offset, ios::seek_dir dir, size_t amount );

  virtual const char * getClassName( void ) const;
  
};
  
class iLockFile : virtual public LockFile, public iBinaryFile
{

public:

  iLockFile( void ) {};
  iLockFile( const char *    fileName );

  iLockFile & 	lread( void * dest, size_t amount );
  iLockFile &	lread( streampos pos, void * dest, size_t amount );
  iLockFile &	lread( streamoff     offset,
		      ios::seek_dir dir,
		      void * 	    dest,
		      size_t	    amount );

  bool	    rlock( streamoff offset, ios::seek_dir dir, size_t amount );

  virtual const char * getClassName( void ) const;
};

class oLockFile : virtual public LockFile, public oBinaryFile
{
public:
  
  oLockFile( void ) {};
  oLockFile( const char *     fileName,
	       ios::open_mode   mode = ios::out,
	       int	    	perm = 0664 );

  void	    open( const char * 	    fileName,
		  ios::open_mode    mode = ios::out,
		  int	    	    perm = 0664 );

  oLockFile & 	lwrite( const void * src, size_t amount );
  oLockFile &	lwrite( streampos pos, const void * src, size_t amount );
  oLockFile &	lwrite( streamoff     	offset,
			ios::seek_dir 	dir,
			const void * 	src,
			size_t	    	amount );

  bool	    wlock( streamoff offset, ios::seek_dir dir, size_t amount );

  virtual const char * getClassName( void ) const;
};

class ioLockFile : public iLockFile, public oLockFile
{
  ioLockFile( void ) {};
  ioLockFile( const char *   	fileName,
	      ios::open_mode 	mode = (ios::open_mode)(ios::in|ios::out),
	      int	    	perm = 0664 );

  void	    open( const char * 	    fileName,
		  ios::open_mode    mode = (ios::open_mode)(ios::in|ios::out),
		  int	    	    perm = 0664 );
  
  virtual const char * getClassName( void ) const;
};
  


#endif // ! def _LockFile_hh_ 

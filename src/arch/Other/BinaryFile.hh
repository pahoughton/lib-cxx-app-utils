#ifndef _BinaryFile_hh_
#define _BinaryFile_hh_
//
// File:        BinaryFile.hh
// Desc:        
//
//
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/14/95 09:25
//
// Revision History:
//
// $Log$
// Revision 4.1  1997/09/17 15:13:22  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:09:13  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:25:16  houghton
// Changed to Release 3
//
// Revision 2.1  1995/11/10 12:47:04  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  13:11:28  houghton
// Major rework
//
//

#include <StlUtilsConfig.hh>

#include <FileStat.hh>

#include <iostream>
#include <cstddef>

#ifdef  STLUTILS_DEBUG
#define inline
#endif

class BinaryFile
{
  
public:
  
  // BinaryFile is a BASE class only, No public Constructors

  virtual ~BinaryFile( void );
  
  virtual bool	open( const char * fn, ios::open_mode mode, int	perm = 0664 );
  virtual void	close( void );
  virtual bool  is_open( void ) const;
  
  inline streampos  seekoff( streamoff  offset, ios::seek_dir  direction );
  inline streampos  seekpos( streampos  pos );
  inline streampos  seek( long  pos );

  virtual streampos  seek( ios::seek_dir dir, streamoff offset );
  virtual streampos  tell( void ) const;

  virtual int	    sync( void );

  inline const FileStat &   getFileStat( void ) const;
  
  inline int	    rdstate( void ) const;
  inline void	    clear( int state = ios::goodbit );
  
  inline bool	    eof( void ) const;
  inline bool	    bad( void ) const;
  inline bool	    fail( void ) const;
  
  inline bool 	    operator !  ( void ) const;
  
  virtual bool		good( void ) const;
  virtual const char *		error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual ostream &	dumpInfo( ostream & dest = cerr ) const;

  static const char version[];
  
protected:
  
  BinaryFile( void );
  BinaryFile( const char *  	fn,
	      ios::open_mode	mode,
	      int   	    	perm = 0664 );

  int	whence( ios::seek_dir dir ) const;
  
  int	    fd;
  int	    state;
  int	    osError;
  
  FileStat  fileStat;
  
private:

  BinaryFile( const BinaryFile & from );
  BinaryFile & operator =( const BinaryFile & from );

};



class iBinaryFile : virtual public BinaryFile
{
public:

  inline iBinaryFile( void );
  inline iBinaryFile( const char * fileName );

  virtual bool	    	open( const char * fileName );
  
  virtual iBinaryFile &	read( void * dest, size_t amount );
  inline iBinaryFile &	read( streampos pos, void * dest, size_t amount );
  inline iBinaryFile &	read( streamoff     offset,
			      ios::seek_dir dir,
			      void * 	    dest,
			      size_t	    amount );

  inline int	    	gcount( void );

  virtual const char *	getClassName( void ) const;
  virtual ostream &	dumpInfo( ostream & dest = cerr ) const;

  static const char version[];
  
protected:

  int	bytesRead;
  
};

class oBinaryFile : virtual public BinaryFile
{
public:
  
  inline oBinaryFile( void );
  inline oBinaryFile( const char *	fileName,
		      ios::open_mode    mode = ios::out,
		      int	    	perm = 0664 );

  virtual bool	open( const char * 	fileName,
		      ios::open_mode	mode = ios::out,
		      int	    	perm = 0664 );

  virtual oBinaryFile &	write( const void * src, size_t amount );

  inline oBinaryFile &	write( streampos	pos,
			       const void *	src,
			       size_t		amount );
  inline oBinaryFile &	write( streamoff	offset,
			       ios::seek_dir	dir,
			       const void *    	src,
			       size_t	    	amount );

  virtual const char *	getClassName( void ) const;
  virtual ostream &	dumpInfo( ostream & dest = cerr ) const;

  static const char version[];
  
};

class ioBinaryFile : public iBinaryFile, public oBinaryFile
{
  ioBinaryFile( const char *   fileName,
		ios::open_mode mode = (ios::open_mode)(ios::in|ios::out),
		int	    perm = 0664 );

  virtual bool	open( const char * 	fileName,
		      ios::open_mode	mode = (ios::open_mode)(ios::in|ios::out),
		      int	    	    perm = 0664 );

  virtual const char *	getClassName( void ) const;
  virtual ostream &	dumpInfo( ostream & dest = cerr ) const;

  static const char version[];
  
};
  
  
#ifndef inline
#include <BinaryFile.ii>
#else
#undef inline
#endif

  
//  Quick Start: - short example of class usage
//
//  Data Types: - data types defined by this header
//
//  	BinaryFile	class
//
//  Constructors:
//
//  	BinaryFile( );
//
//  Destructors:
//
//  Public Interface:
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. BinaryFile )
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
//  	operator <<( ostream & dest, const BinaryFile & obj );
#endif // ! def _BinaryFile_hh_ 





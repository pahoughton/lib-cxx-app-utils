#ifndef _BinaryFile_hh_
#define _BinaryFile_hh_
//
// File:        BinaryFile.hh
// Desc:        
//
//
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
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/14/95 09:25
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 12:22:21  houghton
// Initial BinaryFile implementation
//
//

#include <iostream>
#include <cstddef>

class BinaryFile
{
  
public:
  
  virtual ~BinaryFile( void );
  
  void	    	open( const char * 	fileName, 
		      ios::open_mode 	mode,
		      int	    	perm = 0664 );

  void	    	close( void );

  bool	    	is_open( void );
  
  streampos 	seekoff( streamoff  offset,
		     ios::seek_dir  direction );

  streampos 	seekpos( streampos  pos );

  streampos 	seek( long  pos );
  streampos 	seek( ios::seek_dir dir, streamoff offset );
  
  streampos 	tell( void );
  
  int	    	sync( void );

  int	    	rdstate( void ) const;
  void	    	clear( int state = ios::goodbit );
  
  bool 	    	operator !  ( void ) const;
  
  bool	    	eof( void ) const;
  bool	    	fail( void ) const;
  bool	    	bad( void ) const;
  
  bool	    	good( void ) const;
  const char * 	error( void ) const;

  virtual const char *	getClassName( void ) const;

protected:
  
  BinaryFile( void );
  BinaryFile( const char *  	fileName,
	      ios::open_mode	mode,
	      int   	    	perm = 0664 );

  int	whence( ios::seek_dir dir );
  
  int	fd;
  int	state;
  int	osError;
  
private:

  BinaryFile( const BinaryFile & from );
  BinaryFile & operator =( const BinaryFile & from );

};


class iBinaryFile : virtual public BinaryFile
{
public:

  iBinaryFile( void );
  iBinaryFile( const char * fileName );

  void	    	open( const char * fileName );
  
  iBinaryFile & read( void * dest, size_t amount );
  iBinaryFile &	read( streampos pos, void * dest, size_t amount );
  iBinaryFile &	read( streamoff     offset,
		      ios::seek_dir dir,
		      void * 	    dest,
		      size_t	    amount );

  int	    	gcount( void );

  virtual const char *	getClassName( void ) const;
  
protected:

  int	bytesRead;
  
};

class oBinaryFile : virtual public BinaryFile
{
public:
  oBinaryFile( void );
  oBinaryFile( const char *     fileName,
	       ios::open_mode   mode = ios::out,
	       int	    	perm = 0664 );

  void	    open( const char * 	    fileName,
		  ios::open_mode    mode = ios::out,
		  int	    	    perm = 0664 );

  oBinaryFile & write( const void * src, size_t amount );
  oBinaryFile &	write( streampos pos, const void * src, size_t amount );
  oBinaryFile &	write( streamoff     	offset,
		       ios::seek_dir 	dir,
		       const void *    	src,
		       size_t	    	amount );

  virtual const char *	getClassName( void ) const;
  
};

class ioBinaryFile : public iBinaryFile, public oBinaryFile
{
  ioBinaryFile( const char *   fileName,
		ios::open_mode mode = (ios::open_mode)(ios::in|ios::out),
		int	    perm = 0664 );

  void	    open( const char * 	    fileName,
		  ios::open_mode    mode = (ios::open_mode)(ios::in|ios::out),
		  int	    	    perm = 0664 );

  virtual const char *	getClassName( void ) const;
  
};
  
  

  
#endif // ! def _BinaryFile_hh_ 





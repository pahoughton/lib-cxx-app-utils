#ifndef _BinFile_hh_
#define _BinFile_hh_
//
// File:        BinFile.hh
// Desc:        
//
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     08/02/95 05:05
//
// Revision History:
//
// $Log$
// Revision 3.2  1997/09/17 11:09:13  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:25:15  houghton
// Changed to Release 3
//
// Revision 2.1  1995/11/10 12:47:03  houghton
// Change to Version 2
//
// Revision 1.1  1995/11/05  13:13:48  houghton
// Initial implementation
//
//

#include <StlUtilsConfig.hh>

#include <File.hh>
#include <FileStat.hh>

#ifdef	STLUTILS_DEBUG
#define inline
#endif

class BinFile : public File
{

public:

  inline BinFile( void );
  inline BinFile( const char * fn, ios::open_mode mode, int perm = 0664 );
  
  virtual ~BinFile( void );

  virtual bool	open( const char * fn, ios::open_mode mode, int	perm = 0664 );
  virtual void	close( void );
  virtual bool	is_open( void ) const;
  
  virtual streampos seek( ios::seek_dir dir, streamoff offset );
  virtual streampos tell( void ) const;

  virtual BinFile & read( void * dest, size_t amount );
  virtual BinFile & write( const void * dest, size_t amount );

  virtual int	    sync( void );

  inline size_t	    truncate( size_t end );
  
  inline const FileStat &   getFileStat( void ) const;
  inline ios::open_mode	    getOpenMode( void ) const;
  inline int		    getFD( void ) const;
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual ostream &	dumpInfo( ostream & dest = cerr ) const;

  static const char version[];
  
protected:

private:
  
  FileStat	    fileStat;
  int		    fd;
  ios::open_mode    openMode;
  int		    openPerm;  

  BinFile( const BinFile & from );
  BinFile & operator =( const BinFile & from );

};


#ifndef  inline
#include <BinFile.ii>
#else
#undef inline
#endif

//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	BinFile	class
//
//  Constructors:
//
//  	BinFile( );
//
//  Destructors:
//
//  Public Interface:
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. BinFile )
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
//  	operator <<( ostream & dest, const BinFile & obj );

#endif // ! def _BinFile_hh_ 


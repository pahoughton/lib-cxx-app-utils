#ifndef _MapFile_hh_
#define _MapFile_hh_
//
// File:        MapFile.hh
// Desc:        
//
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     08/01/95 10:17
//
// Revision History:
//
// $Log$
// Revision 3.1  1996/11/14 01:25:26  houghton
// Changed to Release 3
//
// Revision 2.1  1995/11/10 12:47:14  houghton
// Change to Version 2
//
// Revision 1.1  1995/11/05  13:13:49  houghton
// Initial implementation
//
//

#include <ClueConfig.hh>

#include <File.hh>
#include <BinFile.hh>

#ifdef	CLUE_DEBUG
#define inline
#endif

class MapFile : public File
{

public:

  inline MapFile( void );
  inline MapFile( const char *	    fileName,
		  ios::open_mode    mode,
		  int		    perm = 0664,
		  caddr_t	    mapAddr = 0,
		  streampos	    mapPos = 0,
		  size_t	    mapSize = 0 );
  
  virtual ~MapFile( void );

  virtual bool	    open( const char *	    fileName,
			  ios::open_mode    mode,
			  int		    perm = 0664,
			  caddr_t	    mapAddr = 0,
			  streampos	    mapPos = 0,
			  size_t	    mapSize = 0 );

  virtual void	    close( void );
  virtual bool	    is_open( void ) const;
  
//  inline streampos  seekoff( streamoff  offset, ios::seek_dir  direction );
//  inline streampos  seekpos( streampos  pos );
//  inline streampos  seek( long  pos );

  virtual streampos seek( ios::seek_dir dir, streamoff offset );
  virtual streampos tell( void ) const;

  virtual MapFile & read( void * dest, size_t amount );
  virtual MapFile & write( const void * src, size_t amount );

  inline MapFile &  read( streampos pos, void * dest, size_t amount );
  inline MapFile &  read( streamoff     offset,
			  ios::seek_dir dir,
			  void * 	    dest,
			  size_t	    amount );

  inline MapFile &  write( streampos	pos,
			   const void *	src,
			   size_t	amount );
  inline MapFile &  write( streamoff	    offset,
			   ios::seek_dir    dir,
			   const void *     src,
			   size_t	    amount );
  
  virtual int	    sync( void );
  virtual size_t    size( void );
  inline int	    gcount( void );
  
  inline const FileStat &   getFileStat( void ) const;

  inline int		rdstate( void ) const;
  inline bool		clear( int state = ios::goodbit );
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual ostream &	dumpInfo( ostream & dest = cerr ) const;

  static const char version[];
  
protected:

  caddr_t   map( size_t size );
  inline size_t    pageAlign( size_t size );
  inline caddr_t   pageAlign( caddr_t addr );
  
private:

  MapFile( const MapFile & from );
  MapFile & operator =( const MapFile & from );

  
  BinFile	file;

  caddr_t	    openBase;
  streampos	    openPos;
  size_t	    openSize;
  
  caddr_t	mapBase;
  size_t	mapSize;
  streampos	mapPos;
  streampos	mapEnd;
  int		mapErrno;
  
  static const size_t	pageSize;
  
};

#ifndef inline
#include <MapFile.ii>
#else
#undef inline
#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	MapFile	class
//
//  Constructors:
//
//  	MapFile( );
//
//  Destructors:
//
//  Public Interface:
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. MapFile )
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
//  	operator <<( ostream & dest, const MapFile & obj );

#endif // ! def _MapFile_hh_ 


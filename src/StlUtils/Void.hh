#ifndef _Void_hh_
#define _Void_hh_
//
// File:        Void.hh
// Desc:        
//
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     11/11/95 05:08
//
// Revision History: (See end of file for Revision Log)
//
//

#include "ClueConfig.hh"
#include <iostream>

#if defined( CLUE_DEBUG )
#define inline
#endif


class Void
{

public:

  Void( void );
  Void( const void * src, size_t size );
  Void( const Void & src );

  virtual ~Void( void );

  inline size_t		size( void ) const;

  inline const void *	vptr( void ) const;
  
  inline bool		get( void * 	dest,
			     size_t	destSize,
			     size_t	start = 0 ) const;
  
  Void &		append( const void * src, size_t size );
  inline Void &		append( const Void & src );
  
  inline Void &		assign( const void * src, size_t size );
  inline Void &		assign( const Void & src );

  inline Void &		insert( size_t 	    	before,
				const void * 	src,
				size_t		srcSize );
  inline Void &		insert( size_t 	    	before,
				const Void & 	src );
  
  Void &		replace( size_t     	start,
				 size_t     	len,
				 const void * 	src,
				 size_t		srcSize );
  
  inline Void &		replace( size_t     	start,
				 size_t     	len,
				 const Void & 	src );
  
  inline Void &		remove( size_t start, size_t len = NPOS );

  
  inline void		reset( void );
  
  bool			resize( size_t newSize, bool trunc = false );
  
  virtual int		compare( const Void & rhs ) const;
  
  inline Void &	    operator =  ( const Void & rhs );
  
  inline bool	    operator == ( const Void & rhs ) const;
  inline bool	    operator <  ( const Void & rhs ) const;

  inline       	    operator const void * ( void ) const;
  
  // libClue Common Class Methods
  
  virtual size_t    	getBinSize( void ) const;
  
  virtual ostream & 	write( ostream & dest ) const;
  virtual istream & 	read( istream & src );

  
  virtual ostream &	    toStream( ostream & dest ) const;

  friend inline ostream &   operator << ( ostream & dest,
                                          const Void & obj );

  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  static const ClassVersion version;

protected:

  
private:

  char *    data;
  size_t    dataSize;
  size_t    dataBufSize;

  enum ErrorNum
  {
    E_OK,
    E_NODATA,
    E_RANGE,
    E_ALLOC,
    E_UNDEFINED
  };

  ErrorNum  errorNum;
  static const char * ErrorStrings[];

  Void &    setError( ErrorNum errorNum );
  
};

#if !defined( inline )
#include <Void.ii>
#else
#undef inline

int
compare( const Void & lhs, const Void & rhs );

#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	Void	class
//
//  Constructors:
//
//  	Void( );
//
//  Destructors:
//
//  Public Interface:
//
//	virtual ostream &
//	toStream( ostream & dest ) const
//	    output class as a string to dest (used by operator <<)
//
//  	virtual Bool
//  	good( void ) const;
//  	    Return true if there are no detected errors associated
//  	    with this class, otherwise false.
//
//  	virtual const char *
//  	error( void ) const
//  	    Return a string description of the state of the class.
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. Void )
//
//  	virtual const char *
//  	getVersion( bool withPrjVer = true ) const;
//  	    Return the version string of this class.
//
//	virtual ostream &
//	dumpInfo( ostream & dest, const char * prefix, bool showVer )
//	    output detail info to dest. Includes instance variable
//	    values, state info & version info.
//
//	static const ClassVersion
//	version
//	    class & project version information. (see ClassVersion.hh)
//
//  Protected Interface:
//
//  Private Methods:
//
//  Other Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const Void & obj );
//
// Revision Log:
//
// $Log$
// Revision 3.3  1997/03/07 11:56:37  houghton
// Cleanup.
//
// Revision 3.2  1996/11/20 12:13:11  houghton
// Removed support for BinStream.
//
// Revision 3.1  1996/11/14 01:24:29  houghton
// Changed to Release 3
//
// Revision 2.5  1996/05/14 13:53:54  houghton
// Added ::compare( const Void & lhs, const Void & rhs )
//
// Revision 2.4  1996/04/27 13:13:26  houghton
// Bug-Fix: '#else was missing'
//
// Revision 2.3  1995/12/04 11:18:31  houghton
// Bug Fix - Can now compile with out '-DCLUE_DEBUG'.
//
// Revision 2.2  1995/11/13  11:31:02  houghton
// Changed compare to const.
// Changed date type from void * to char *.
//
// Revision 2.1  1995/11/12  18:33:34  houghton
// Initial Version.
//
#endif // ! def _Void_hh_ 


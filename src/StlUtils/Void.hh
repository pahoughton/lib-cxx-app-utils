#ifndef _Void_hh_
#define _Void_hh_
//
// File:        Void.hh
// Project:	StlUtils ()
// Desc:        
//
//  Provides an expandable storage location for objects.
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     11/11/95 05:08
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//
// $Id$ 
//

#include <StlUtilsConfig.hh>
#include <DumpInfo.hh>

#include <iostream>

#include <cstring>

#if defined( STLUTILS_DEBUG )
#define inline
#endif


class Void
{

public:

  typedef STLUTILS_U64_SIZE_T	size_type;
  
  Void( void );
  Void( const void * src, size_type size );
  Void( const Void & src );

  virtual ~Void( void );

  inline size_type		size( void ) const;

  inline const void *	vptr( void ) const;
  
  inline bool		get( void * 	dest,
			     size_type	destSize,
			     size_type	start = 0 ) const;
  
  Void &		append( const void * src, size_type size );
  inline Void &		append( const Void & src );
  
  inline Void &		assign( const void * src, size_type size );
  inline Void &		assign( const Void & src );

  inline Void &		insert( size_type 	before,
				const void * 	src,
				size_type	srcSize );
  inline Void &		insert( size_type 	before,
				const Void & 	src );
  
  Void &		replace( size_type     	start,
				 size_type     	len,
				 const void * 	src,
				 size_type	srcSize );
  
  inline Void &		replace( size_type     	start,
				 size_type     	len,
				 const Void & 	src );
  
  inline Void &		remove( size_type start, size_type len = NPOS );

  
  inline void		reset( void );
  
  bool			resize( size_type newSize, bool trunc = false );
  
  virtual int		compare( const Void & rhs ) const;
  
  inline Void &	    operator =  ( const Void & rhs );
  
  inline bool	    operator == ( const Void & rhs ) const;
  inline bool	    operator <  ( const Void & rhs ) const;

  inline       	    operator const void * ( void ) const;
  
  // libStlUtils Common Class Methods
  
  virtual size_type    	getBinSize( void ) const;
  
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

  inline
  DumpInfo< Void >	dump( const char *  prefix = "    ",
			      bool	    showVer = true ) const;
  
protected:

  
private:

  char *	data;
  size_type     dataSize;
  size_type     dataBufSize;

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
// 
// %PL%
// 
// $Log$
// Revision 5.4  2003/08/09 11:21:00  houghton
// Changed ver strings.
//
// Revision 5.3  2003/07/19 09:17:12  houghton
// Port to 64 bit.
//
// Revision 5.2  2001/07/26 19:28:58  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:18  houghton
// Changed Version Num to 5
//
// Revision 4.2  1997/09/19 11:21:24  houghton
// Changed to use new portable types (STLUTILS*_T).
//
// Revision 4.1  1997/09/17 15:13:09  houghton
// Changed to Version 4
//
// Revision 3.6  1997/09/17 11:08:59  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.5  1997/07/18 19:31:22  houghton
// Port(Sun5): added include <cstring>.
//
// Revision 3.4  1997/03/14 14:48:15  houghton
// Added dump() method.
//
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
// Bug Fix - Can now compile with out '-DSTLUTILS_DEBUG'.
//
// Revision 2.2  1995/11/13  11:31:02  houghton
// Changed compare to const.
// Changed date type from void * to char *.
//
// Revision 2.1  1995/11/12  18:33:34  houghton
// Initial Version.
//
#endif // ! def _Void_hh_ 


#ifndef _SizeIt_hh_
#define _SizeIt_hh_
//
// File:        SizeIt.hh
// Desc:        
//
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     03/11/96 05:59
//
// Revision History:
//
// $Id$
//
// $Log$
// Revision 4.1  1997/09/17 15:12:48  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:08:41  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1997/04/03 23:23:20  houghton
// Changed include stddef to stddef.h
//
// Revision 3.1  1996/11/14 01:23:59  houghton
// Changed to Release 3
//
// Revision 2.1  1996/03/13 11:28:13  houghton
// Initial Version
//
//

#include <StlUtilsConfig.hh>
#include <iostream>
#include <stddef.h>

#if defined( STLUTILS_DEBUG )
#define inline
#endif

#define STLUTILS_SIZEIT_SIZE    8

class SizeIt
{

public:

  static const size_t	factor;
  
  inline SizeIt( size_t size = 0 );
  inline SizeIt( const SizeIt & from );


  virtual ~SizeIt( void );

  inline	    operator size_t ( void ) const;
  
  inline size_t	    operator () ( void ) const;
  inline size_t     operator () ( size_t size );
  
  inline SizeIt &   operator =	( const SizeIt & from );

  inline bool	    operator == ( const SizeIt & rhs ) const;
  inline bool	    operator == ( size_t rhs ) const;

  inline bool	    operator <  ( const SizeIt & rhs ) const;
  inline bool	    operator <  ( size_t rhs ) const;

  inline bool	    operator >  ( size_t rhs ) const;
  inline bool	    operator <= ( size_t rhs ) const;
  inline bool	    operator >= ( size_t rhs ) const;
  
  virtual ostream &	    toStream( ostream & dest ) const;

  friend inline ostream &   operator << ( ostream & dest,
                                          const SizeIt & obj );

  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  static const ClassVersion version;

protected:

  virtual size_t    setSize( size_t size );
  
private:

  size_t    it;
  
};

#if !defined( inline )
#include <SizeIt.ii>
#else
#undef inline
#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	SizeIt	class
//
//  Constructors:
//
//  	SizeIt( );
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
//  	    Return the name of this class (i.e. SizeIt )
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
//  	operator <<( ostream & dest, const SizeIt & obj );
//
#endif // ! def _SizeIt_hh_ 


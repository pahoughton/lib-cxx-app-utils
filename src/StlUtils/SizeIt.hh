#ifndef _SizeIt_hh_
#define _SizeIt_hh_
//
// File:        SizeIt.hh
// Project:	StlUtils ()
// Desc:        
//
//  This class provides an object that can be used to manage the size of
//  something. The sizing value is maintained as a factor of 2. This
//  reduces the chance that the sizing value will be increased as the
//  object using it continues to grow.
//
//	Values: 8, 16, 32, 64, 128, 256 ...
//
// Quick Start: - short example of class usage
//
//  SizeIt  size( 10 );  // at least 10
//  long *  array;
//  
//  array = new long[ size() ];
//  
//  // now you need room for at least 20
//  size( 20 );
//  delete array;
//  array = new long[ size() ];
//
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     03/11/96 05:59
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//
//  $Id$ 
//

#include <StlUtilsConfig.hh>
#include <DumpInfo.hh>
#include <iostream>
#include <cstddef>

#if defined( STLUTILS_DEBUG )
#define inline
#endif

#define STLUTILS_SIZEIT_SIZE    8

class SizeIt
{

public:

  typedef size_t    size_type;
  
  static const size_type	factor;
  
  inline SizeIt( size_type size = 0 );
  inline SizeIt( const SizeIt & from );

  virtual ~SizeIt( void );

  inline size_type	grow( void );
  inline size_type	shrink( void );
  
  virtual std::ostream &	    write( std::ostream & dest ) const;
  virtual std::istream &	    read( std::istream & src );

  virtual std::ostream &	    toStream( std::ostream & dest ) const;
  virtual std::istream &	    fromStream( std::istream & src );

  inline	    operator size_type ( void ) const;
  
  inline size_type  operator () ( void ) const;
  inline size_type  operator () ( size_type size );
  
  inline SizeIt &   operator =	( const SizeIt & from );

  inline bool	    operator == ( const SizeIt & rhs ) const;
  inline bool	    operator <  ( const SizeIt & rhs ) const;
  
  inline bool	    operator == ( size_type rhs ) const;
  inline bool	    operator != ( size_type rhs ) const;
  inline bool	    operator <  ( size_type rhs ) const;
  inline bool	    operator >  ( size_type rhs ) const;
  inline bool	    operator <= ( size_type rhs ) const;
  inline bool	    operator >= ( size_type rhs ) const;
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual std::ostream &     dumpInfo( std::ostream &	dest = std::cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  inline DumpInfo< SizeIt >
  dump( const char * preifx = "    ", bool showVer = true ) const;

  static const ClassVersion version;

protected:

  virtual size_type setSize( size_type size );
  
private:

  size_type it;

};

#if !defined( inline )
#include <SizeIt.ii>
#else
#undef inline

std::ostream &
operator << ( std::ostream & dest, const SizeIt & src );

std::istream &
operator >> ( std::istream & src, const SizeIt & dest );


#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	SizeIt	class
//	SizeIt::size_type
//
//  Constructors:
//
//  	SizeIt( size_type size = 0 );
//	    instanciate an object who's value will be >= 'size'.
//
//	SizeIt( const SizeIt & from );
//	    instanciate an object with the value in 'from'
//
//  Destructors:
//
//  Public Interface:
//
//	inline size_type
//	grow( void )
//	    Double the sizing value and return the new value.
//
//	inline size_type
//	shrink( void )
//	    Half the sizing value and return the new value.
//
//	virtual std::ostream &
//	write( std::ostream & dest ) const;
//	    write the data for this class in binary form to the std::ostream.
//
//	virtual std::istream &
//	read( std::istream & src );
//	    read the data in binary form from the std::istream. It is
//	    assumed it stream is correctly posistioned and the data
//	    was written to the std::istream with 'write( std::ostream & )'
//
//	virtual std::ostream &
//	toStream( std::ostream & dest ) const;
//	    output class as a string to dest (used by operator <<)
//
//	virtual std::istream &
//	fromStream( std::istream & src );
//	    Set this class be reading a string representation from
//	    src. Returns src.
//
//	inline
//	operator size_type  ( void ) const;
//	    Return the curent sizing value.
//
//	inline size_type
//	operator () ( void ) const;
//	    Return the current sizing value.
//
//	inline size_type
//	operator () ( size_type size )
//	    Set the sizing value to be >= 'size' and return the new value.
//	    If the current sizeing value is > size, it will be reduced to
//	    the smallest 'sizing' value that is >= size.
//
//	inline SizeIt &
//	operator = ( const SizeIt & rhs )
//	    Set the sizing value to be the same as 'rhs'.
//
//	inline bool
//	operator == ( const SizeIt & rhs ) const
//	    Return true if the sizing value is == rhs else return false.
//
//	inline bool
//	operator < ( const SizeIt & rhs ) const
//	    Return true if the sizing value is < rhs else return false.
//
//	inline bool
//	operator == ( size_type rhs ) const
//	    Return true if the sizing value is == rhs else return false.
//
//	inline bool
//	operator != ( size_type rhs ) const
//	    Return true if the sizing value is != rhs else return false.
//
//	inline bool
//	operator < ( size_type rhs ) const
//	    Return true if the sizing value is < rhs else return false.
//
//	inline bool
//	operator > ( size_type rhs ) const
//	    Return true if the sizing value is > rhs else return false.
//
//	inline bool
//	operator <= ( size_type rhs ) const
//	    Return true if the sizing value is <= rhs else return false.
//
//	inline bool
//	operator >= ( size_type rhs ) const
//	    Return true if the sizing value is >= rhs else return false.
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
//  	    Return the name of this class (i.e. SizeIt )
//
//  	virtual const char *
//  	getVersion( bool withPrjVer = true ) const;
//  	    Return the version string of this class.
//
//	virtual std::ostream &
//	dumpInfo( std::ostream & dest, const char * prefix, bool showVer );
//	    output detail info to dest. Includes instance variable
//	    values, state info & version info.
//
//	static const ClassVersion version
//	    Class and project version information. (see ClassVersion.hh)
//
//  Protected Interface:
//
//	virtual size_type
//	setSize( size_type size );
//	    Set the sizing value to be >= 'size' and return the new value.
//	    If the current sizeing value is > size, it will be reduced to
//	    the smallest 'sizing' value that is >= size.
//
//  Private Methods:
//
//  Associated Functions:
//
//  	std::ostream &
//  	operator <<( std::ostream & dest, const SizeIt & src );
//
//	std::istream &
//	operator >> ( std::istream & src, SizeIt & dest );
//
// Example:
//
// See Also:
//
// Files:
//
// Documented Ver:  4.3
//
// Tested Ver:
//
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.3  2012/04/26 20:08:50  paul
// *** empty log message ***
//
// Revision 6.2  2011/12/30 23:57:18  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:42  houghton
// Changed to version 6
//
// Revision 5.3  2003/08/09 11:20:59  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:28:59  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:17  houghton
// Changed Version Num to 5
//
// Revision 4.3  1998/11/02 15:28:07  houghton
// Added SizeIt::size_type type.
// Cleanup.
//
// Revision 4.2  1998/10/13 16:21:53  houghton
// Changed to include cstddef
//
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
#endif // ! def _SizeIt_hh_ 

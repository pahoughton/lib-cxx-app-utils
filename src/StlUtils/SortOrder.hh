#ifndef _SortOrder_hh_
#define _SortOrder_hh_
//
// File:        SortOrder.hh
// Project:	StlUtils
// Desc:        
//
//
//
// Quick Start: - short example of class usage
//
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     09/19/95 09:05
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#include <StlUtilsConfig.hh>
#include <vector>

template < class T >
class SortOrder
{

public:

  class LessBase
  {
  public:
    virtual bool    operator () ( const T & one, const T & two ) const = 0;
    
    virtual LessBase *	dup( void ) const = 0;
  };

  class Less
  {
  public:
    inline Less( void ) : less( 0 ) {};
    inline Less( const LessBase & lessBase ) : less( lessBase.dup() ) {};
    inline Less( const Less & from ) : less( from.less ?
					     from.less->dup() : 0 ) {};
    inline Less &   operator = ( const Less & rhs ) {
      if( less ) delete less;
      less = (rhs.less ? rhs.less->dup() : 0 );
      return( *this );
    };
	
    inline ~Less( void ) { if( less ) delete less; };

  private:
    friend class SortOrder<T>;
    
    LessBase * less;
  };
  
  typedef vector< Less >	    Order;
  
  inline SortOrder( const LessBase & lessBase ) {
    Less l( lessBase );
    order.push_back( l );
  };

  inline bool	    operator () ( const T & one, const T & two ) const;

  inline SortOrder<T>  operator + ( const SortOrder<T> & rhs ) const;
  
protected:

private:

  Order	    order;
};

#include <SortOrder.ii>


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	SortOrder	class
//
//  Constructors:
//
//  	SortOrder( );
//
//  Destructors:
//
//  Public Interface:
//
//	virtual ostream &
//	write( ostream & dest ) const;
//	    write the data for this class in binary form to the ostream.
//
//	virtual istream &
//	read( istream & src );
//	    read the data in binary form from the istream. It is
//	    assumed it stream is correctly posistioned and the data
//	    was written to the istream with 'write( ostream & )'
//
//	virtual ostream &
//	toStream( ostream & dest ) const;
//	    output class as a string to dest (used by operator <<)
//
//	virtual istream &
//	fromStream( istream & src );
//	    Set this class be reading a string representation from
//	    src. Returns src.
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
//  	    Return the name of this class (i.e. SortOrder )
//
//  	virtual const char *
//  	getVersion( bool withPrjVer = true ) const;
//  	    Return the version string of this class.
//
//	virtual ostream &
//	dumpInfo( ostream & dest, const char * prefix, bool showVer );
//	    output detail info to dest. Includes instance variable
//	    values, state info & version info.
//
//	static const ClassVersion version
//	    Class and project version information. (see ClassVersion.hh)
//
//  Protected Interface:
//
//  Private Methods:
//
//  Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const SortOrder & src );
//
//	istream &
//	operator >> ( istream & src, SortOrder & dest );
//
// Example:
//
// See Also:
//
// Files:
//
// Documented Ver:
//
// Tested Ver: 3.2
//
// Revision Log:
//
// $Log$
// Revision 3.4  1997/09/17 11:08:41  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/07/18 19:26:09  houghton
// Bug-Fix: added include <vector>
//
// Revision 3.2  1997/06/09 12:02:33  houghton
// Complete rework.
//
// Revision 3.1  1996/11/14 01:24:04  houghton
// Changed to Release 3
//
// Revision 2.1  1995/11/10 12:41:02  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  15:28:45  houghton
// Revised
//
//
#endif // ! def _SortOrder_hh_ 

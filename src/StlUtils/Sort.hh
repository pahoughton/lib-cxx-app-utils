#ifndef _Sort_hh_
#define _Sort_hh_
//
// File:        Sort.hh
// Project:	StlUtils ()
// Desc:        
//
//  Provides templates for sorting collections of objects.
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     09/19/95 08:53
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

#include <StlUtilsConfig.hh>

#error Not ready

template < class T >
class SortCompare
{
public:

  virtual bool	operator () ( const T & one, const T & two ) const = 0;

};
  
			      
template < class T >
class Sort
{

public:

  typedef SortCompare< T >	Compare;
  typedef vector< Compare >	Order;
  
  inline Sort( const Compare & comp );

  inline bool	    operator () ( const T & one, const T & two ) const;

  inline Sort	    operator + ( const Sort & rhs ) const;
  inline friend	    operator + ( const Compare & one,
				 const Sort &    two ) const;
  
protected:

private:

  Order	    order;
  
};

#include <Sort.ii>


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	Sort	class
//
//  Constructors:
//
//  	Sort( );
//
//  Destructors:
//
//  Public Interface:
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. Sort )
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
//  	operator <<( ostream & dest, const Sort & obj );

// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.1  2003/08/09 11:22:42  houghton
// Changed to version 6
//
// Revision 5.4  2003/08/09 11:20:59  houghton
// Changed ver strings.
//
// Revision 5.3  2001/07/29 19:56:38  houghton
// *** empty log message ***
//
// Revision 5.2  2001/07/26 19:28:59  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:17  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:12:48  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:08:41  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:24:02  houghton
// Changed to Release 3
//
// Revision 2.2  1995/12/04 11:18:26  houghton
// Bug Fix - Can now compile with out '-DSTLUTILS_DEBUG'.
//
// Revision 2.1  1995/11/10  12:41:01  houghton
// Change to Version 2
//
// Revision 1.1  1995/11/05  13:23:30  houghton
// Initaial implementation
//
//
#endif // ! def _Sort_hh_ 


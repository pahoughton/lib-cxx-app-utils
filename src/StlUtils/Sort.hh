#ifndef _Sort_hh_
#define _Sort_hh_
//
// File:        Sort.hh
// Desc:        
//
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     09/19/95 08:53
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 13:23:30  houghton
// Initaial implementation
//
//

#include <ClueConfig.hh>

template < class T >
class SortCompare
{
public:

  virtual bool	operator () ( const T & one, const T & two ) const = 0;

};
  
			      
template < class T >
class 
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

#endif // ! def _Sort_hh_ 


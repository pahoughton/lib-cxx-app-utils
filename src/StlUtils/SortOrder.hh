#ifndef _SortOrder_hh_
#define _SortOrder_hh_
//
// File:        SortOrder.hh
// Desc:        
//
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     09/19/95 09:05
//
// Revision History:
//
// $Log$
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

#ifdef CLUE_SHORT_FN
#include <ClueCfg.hh>
#else
#include <ClueConfig.hh>
#endif

template < class T >
class SortCompareBase
{
public:
  virtual int operator () ( const T & one, const T & two ) const = 0;
};

  
template < class T >
class SortCompare
{
public:

  inline SortCompare();
  inline SortCompare( const SortCompareBase<T> & cmp );
  
  inline int compare( const T & one, const T & two ) const;

private:

  const SortCompareBase<T> *  compareT;

};

template < class T >
class SortOrder
{

public:

  typedef SortCompare< T >	    Compare;
  typedef vector< Compare >	    Order;
  
  inline SortOrder( const SortCompareBase<T> & cmp );
  inline SortOrder( const Compare & cmp );

  inline bool	    operator () ( const T & one, const T & two ) const;

  inline SortOrder<T>  operator + ( const SortOrder<T> & rhs ) const;
  
protected:

private:

  Order	    order;
};

#if !defined( CLUE_SHORT_FN )
#include <SortOrder.ii>
#else
#include <SortOrdr.ii>
#endif


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
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. SortOrder )
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
//  	operator <<( ostream & dest, const SortOrder & obj );

#endif // ! def _SortOrder_hh_ 


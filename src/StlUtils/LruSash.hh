#ifndef _LruSash_hh_
#define _LruSash_hh_
//
// File:        LruSash.hh
// Project:	StlUtils ()
// Desc:        
//
//  Provides a Least Recently Used manager that uses a hash table for
//  storage.
//
// Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul.houghton@mci.com)
// Created:     10/29/98 04:30
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
#include <SizeIt.hh>
#include <DumpInfo.hh>

#include <vector>
#include <iostream>


template< class Obj, class ObjKey, class LruHashFunct, class LruMax >
class LruSash
{

public:

  typedef unsigned long	    LruKey;
  
  struct Rec
  {
    LruKey  key;
    Obj *   obj;
    Rec *   next;
    Rec *   prev;

    Rec( LruKey k, Rec * n )
      : key( k ), obj( new Obj( k ) ), next( n ), prev( 0 ) {};

    ~Rec( void ) { delete obj; };
  };

  class Sash
  {
  public:

    typedef vector< Rec * >	Table;
    typedef Table::size_type	size_type;
    typedef Table::iterator	iterator;
    typedef Table::reference	reference;
    typedef Table::value_type	value_type;
    
    Sash( size_type initSize ) : size( initSize ), table( size(),
							  value_type(0) ) {};

    ~Sash( void ) {};
    
    reference  operator [] ( LruKey k ) {
      if( k >= size() )
	{
	  size( k + 1 );
	  table.resize( size(), value_type(0) );
	}

      return( table[k] );
    }

  private:

    SizeIt  size;
    Table   table;
  };
      
  typedef size_t    size_type;

  LruSash( LruHashFunct &	hashFunctObj,
	   LruMax &		maxObj,
	   size_type		initHashSize = 128 )
    : lruFunct( hashFunctObj ),
      maxAlloc( maxObj ),
      sash( initHashSize ),
      qFirst( 0 ),
      qLast( 0 ),
      qSize( 0 ) {};
      
  virtual ~LruSash( void ) {
    Rec *   q;
    Rec *   nq;
    
    for( q = qFirst; q; q = nq )
      {
	nq = (*q).next;
	delete q;
      }
  };

  Obj &		obj( const ObjKey & objKey ) {

    Sash::reference	it( sash[ lruFunct( objKey ) ] );

    if( it == 0 )
      {
	// not currently allocated
	if( qSize >= maxAlloc() )
	  {
	    // release the last entry in the queue

	    if( qLast )
	      sash[ (*qLast).key ] = 0;

	    Rec * pq( (*qLast).prev );
	    delete qLast;

	    if( pq )
	      (*pq).next = 0;
	    
	    qLast = pq;
	    if( ! qLast )
	      qFirst = 0;
	    
	    -- qSize;
	  }
	it = new Rec( lruFunct( objKey ), qFirst );

	if( qFirst )
	  (*qFirst).prev = it;
	else
	  qLast = it;

	qFirst = it;
	++ qSize;
      }
    else
      {
	// already allocated so shuffle as needed
	if( it != qFirst )
	  {
	    // not first so shuffle
	    (*(*it).prev).next = (*it).next;

	    if( it != qLast )
	      (*(*it).next).prev = (*it).prev;
	    else
	      qLast = (*it).prev;

	    (*qFirst).prev = it;
	    (*it).next = qFirst;
	    (*it).prev = 0;
	    qFirst = it;
	  }
      }
    return( (*(*it).obj) );
  }

#if defined( FIXME )
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  inline DumpInfo< LruSash >
  dump( const char * preifx = "    ", bool showVer = true ) const;

  static const ClassVersion version;
#endif
  
protected:

  LruHashFunct &    lruFunct;
  LruMax &	    maxAlloc;

  Sash		sash;
  
  Rec *		qFirst;
  Rec *		qLast;
  size_type	qSize;
  
private:

  LruSash( const LruSash & from );
  LruSash & operator =( const LruSash & from );

};

#include <LruSash.ii>


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	LruSash	class
//
//  Constructors:
//
//  	LruSash( );
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
//  	    Return the name of this class (i.e. LruSash )
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
//  	operator <<( ostream & dest, const LruSash & src );
//
//	istream &
//	operator >> ( istream & src, LruSash & dest );
//
// Example:
//
// See Also:
//
// Files:
//
// Documented Ver:
//
// Tested Ver:
//
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 5.3  2003/08/09 11:20:59  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:28:59  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:16  houghton
// Changed Version Num to 5
//
// Revision 4.2  1999/03/02 12:48:23  houghton
// Bug-Fixes.
// Cleanup.
//
// Revision 4.1  1998/11/02 15:26:14  houghton
// Initial Version.
//
//
#endif // ! def _LruSash_hh_ 


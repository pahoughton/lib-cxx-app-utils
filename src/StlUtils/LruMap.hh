#ifndef _LruMap_hh_
#define _LruMap_hh_
//
// File:        LruMap.hh
// Project:	StlUtils
// Desc:        
//
//
//
// Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     09/08/98 09:08
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
#include <DumpInfo.hh>
#include <iostream>
#include <map>

template< class Obj, class ObjKey, class LruKey, class LruFunct, class LruMax >
class LruMap
{

public:

  struct Rec
  {
    LruKey	key;
    Obj *	obj;
    Rec *	next;
    Rec *	prev;

    Rec( const LruKey & k, Rec * n )
      : key( k ), obj( new Obj( k ) ), next( n ), prev( 0 ) {};

    ~Rec( void ) { delete obj; };
    
  };

  typedef size_t	size_type;
  
  typedef map< LruKey, Rec *, less< LruKey > >	Index;
  
  LruMap( LruFunct  &	lruFunctObj,
	  LruMax &	maxObj )
    : lruFunct( lruFunctObj ),
      maxAlloc( maxObj ),
      qFirst( 0 ),
      qLast( 0 ),
      qSize( 0 ) {};

  virtual ~LruMap( void ) {
    Rec * r;
    Rec *	n;
    
    for( r = qFirst;  r; r = n )
      {
	n = (*r).next;
	delete r;
      }
  };
  
  
  Obj &		obj( const ObjKey & objKey ) {

    pair< Index::iterator, bool >	ins = index.insert(
      Index::value_type( lruFunct( objKey ), (Rec *)0 ) );

    if( ! (*ins.first).second )
      {
	// either a new entry or existing entry that is not
	// currently allocated.

	if( qSize >= maxAlloc() )
	  {
	    // release the last entry in the queue
	    Index::iterator it = index.find( (*qLast).key );

	    if( it != index.end() )
	      (*it).second = 0;

	    Rec * pq( (*qLast).prev );

	    delete qLast;

	    (*pq).next = 0;
	    qLast = pq;
	    -- qSize;
	  }

	(*ins.first).second = new Rec( (*ins.first).first,
				       qFirst );

	if( qFirst )
	  (*qFirst).prev = (*ins.first).second;
	else
	  qLast = (*ins.first).second;

	qFirst = (*ins.first).second;
	++ qSize;
      }
    else
      {
	// already allocated so shuffle if needed

	if( (*ins.first).second != qFirst )
	  {
	    // not first, do the shuffle

	    (*(*(*ins.first).second).prev).next = (*(*ins.first).second).next;

	    if( (*ins.first).second != qLast )
	      (*(*(*ins.first).second).next).prev
		= (*(*ins.first).second).prev;
	    else
	      qLast = (*(*ins.first).second).prev;

	    (*qFirst).prev = (*ins.first).second;

	    (*(*ins.first).second).next = qFirst;
	    (*(*ins.first).second).prev = 0;
	    qFirst = (*ins.first).second;
	  }
      }
    return( (*(*(*ins.first).second).obj) );
  };
  
  // virtual bool	    	good( void ) const;
  // virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const {
    return( "LruMap<>" );
  };

  // virtual const char *  getVersion( bool withPrjVer = true ) const;
  
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  inline DumpInfo< LruMap >
  dump( const char * preifx = "    ", bool showVer = true ) const;

  // static const ClassVersion version;

protected:

  LruFunct &	lruFunct;
  LruMax &	maxAlloc;
  Rec *		qFirst;
  Rec *		qLast;
  size_type	qSize;

  Index		index;
  
private:

  LruMap( const LruMap & from );
  LruMap & operator =( const LruMap & from );

};


#include <LruMap.ii>


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	LruMap	class
//
//  Constructors:
//
//  	LruMap( );
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
//  	    Return the name of this class (i.e. LruMap )
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
//  	operator <<( ostream & dest, const LruMap & src );
//
//	istream &
//	operator >> ( istream & src, LruMap & dest );
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
// $Log$
// Revision 5.1  2000/05/25 10:33:16  houghton
// Changed Version Num to 5
//
// Revision 4.3  2000/01/26 15:35:12  houghton
// Moved destructor code from .ii to here.
//
// Revision 4.2  1998/10/23 13:05:14  houghton
// Changed: the 'map' class no longer defines the type 'pair_iterator_bool'.
//
// Revision 4.1  1998/10/13 15:19:14  houghton
// Initial Version.
//
//
#endif // ! def _LruMap_hh_ 


#ifndef _LruMap_hh_
#define _LruMap_hh_
/**
   File:        LruMap.hh
   Project:	StlUtils ()
   Desc:        
  
    Provides a Least Recently used object manager.
  
   Quick Start: - short example of class usage
  
   Author:      Paul Houghton - (paul4hough@gmail.com)
   Created:     09/08/98 09:08
  
   Revision History: (See end of file for Revision Log)
  
    $Author$ 
    $Date$ 
    $Name$ 
    $Revision$ 
    $State$ 
  
    $Id$ 

**/

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


/**
   
   Detail Documentation
  
    Data Types: - data types defined by this header
  
    	LruMap	class
  
    Constructors:
    
    Destructors:
  
    Public Interface:
  
    	virtual const char *
    	getClassName( void ) const;
    	    Return the name of this class (i.e. LruMap )
  
  	virtual
  	ostream &
  	dumpInfo( ostream &	dest = cerr,
  		  const char *	prefix = "    ",
  		  bool		showVer = true ) const;
  	    Output detailed information about the current
  	    state of the Log. 
  
    Protected Interface:
  
    Private Methods:
  
    Associated Functions:
  
   Example:
  
   See Also:
  
   Files:
  
   Documented Ver:
  
   Tested Ver:
   
**/
//
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.2  2011/12/30 23:57:16  paul
// First go at Mac gcc Port
//
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


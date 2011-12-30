#ifndef _DumpInfo_hh_
#define _DumpInfo_hh_
//
// File:        DumpInfo.hh
// Project:	StlUtils ()
// Desc:        
//
//  Most of my classes have a method called dumpInfo that is
//  used to dump the entire contents of the instance to an
//  ostream. This is mostly used for debuging.
//
//  The DumpInfo<T> template class makes it easier to use the
//  dumpInfo methdod. To use it, your class must have a the
//  a 'ostream & dumpInfo( ostream &, const char * , bool )' method
//  that dumps an instance to the stream in a readable form.
//  The DumpInf<T> object can only be instaciated by the
//  class specified as 'T' and only has a toStream method.
//  
//  A class that uses this should return an instance that can
//  then be inserted (i.e. <<) into an ostream. Please see the
//  example.
//
//  Example:
//	
//	class MyClass
//	{
//	public:
//	  ostream & dumpInfo( ostream &	    dest,
//			      const char *  prefix = "    ",
//			      bool	    showVer = true ) const;
//	
//	  inline
//	  DumpInfo<MyClass> dump( const char *  prefix = "    ",
//				  bool		showVer = true ) const;
//	
//	}
//	
//	inline
//	DumpInfo<MyClass>
//	MyClass::dump( const char * prefix, bool showVer )
//	{
//	  return( DumpInfo<MyClass>( *this, prefix, showVer ) );
//	}
//	
//	// So Now you can do the follwing
//
//	MyClass obj;
//	
//	cerr << obj.dump() << endl;
//	
//	// Without dump info you would have to
//
//	dumpInfo( cerr ) << endl; 
//
//
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     12/08/96 07:46
//
// Revision History: (See end of file for Revision Log)
//
// $Id$ 
//

#include <StlUtilsConfig.hh>
#include <iostream>

template< class T >
class DumpInfo
{

public:
  inline ostream &	    toStream( ostream & dest ) const {
    return( obj.dumpInfo( dest, prefix, showVer ) ); };

  inline DumpInfo( const T & dumpObj, const char * pre, bool ver )
    : obj( dumpObj ), prefix( pre ), showVer( ver ) {};
  
protected:

  // friend T;
  
  const T &	obj;
  const char *	prefix;
  bool		showVer;
  
};

template< class T >
inline
ostream &
operator << ( ostream & dest, const DumpInfo<T> & src )
{
  return( src.toStream( dest ) );
}



//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	DumpInfo	class
//
//  Constructors:
//
//  	DumpInfo( );
//
//  Destructors:
//
//  Public Interface:
//
//	virtual ostream &
//	toStream( ostream & dest ) const;
//	    output class as a string to dest (used by operator <<)
//

//  Protected Interface:
//
//  Private Methods:
//
//  Associated Functions:
//
//	inline
//  	ostream &
//  	operator <<( ostream & dest, const DumpInfo & src );
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
// Revision 6.2  2011/12/30 23:57:12  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:41  houghton
// Changed to version 6
//
// Revision 5.3  2003/08/09 11:20:58  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:29:00  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:15  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:12:24  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:08:20  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/01/18 17:28:53  houghton
// Initial version checked in with StlUtils.
//
// Revision 1.1  1996/12/10 00:53:19  houghton
// Initial revision
//
//
#endif // ! def _DumpInfo_hh_ 


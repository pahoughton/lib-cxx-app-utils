#ifndef _ThreadTest_hh_
#define _ThreadTest_hh_
//
// File:        ThreadTest.hh
// Desc:        
//
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     06/19/96 06:48
//
// Revision History:
//
// $Id$
//
// $Log$
// Revision 3.1  1996/11/14 01:28:09  houghton
// Changed to Release 3
//
// Revision 1.2  1996/07/16 13:54:09  houghton
// *** empty log message ***
//
// Revision 1.1  1996/06/20 15:26:22  houghton
// Initial Version.
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <ThreadBase.hh>
#include <iostream>
#else
#include <ClueCfg.hh>
#include <iostream>
#endif

#if defined( CLUE_DEBUG )
#define inline
#endif


class ThreadTest : public ThreadBase
{

public:

  ThreadTest( bool detach = false ) : ThreadBase( detach ) {};

  virtual ~ThreadTest( void );

protected:

  bool	    main( void );
  
private:

  ThreadTest( const ThreadTest & from );
  ThreadTest & operator =( const ThreadTest & from );

};

#if !defined( inline )
#if !defined( CLUE_SHORT_FN )
#include <ThreadTest.ii>
#else
#include <ThreadTest.ii>
#endif
#else
#undef inline
#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	ThreadTest	class
//
//  Constructors:
//
//  	ThreadTest( );
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
//  	    Return the name of this class (i.e. ThreadTest )
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
//  	operator <<( ostream & dest, const ThreadTest & obj );
//
#endif // ! def _ThreadTest_hh_ 


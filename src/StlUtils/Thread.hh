#ifndef _Thread_hh_
#define _Thread_hh_
//
// File:        Thread.hh
// Desc:        
//
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     02/06/96 07:14
//
// Revision History:
//
// $Id$
//
// $Log$
// Revision 2.1  1996/02/29 19:07:53  houghton
// Initial Version
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <iostream>
#include <pthread.h>
#else
#include <ClueCfg.hh>
#include <iostream>
#include <pthread.h>
#endif

#if defined( CLUE_DEBUG )
#define inline
#endif


class Thread
{

protected:

  // MUST subclass and overide pure virtual main (entry point) method.
  
  Thread( void );
  
public:

  virtual ~Thread( void );

  virtual bool	start( void );

  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  static const ClassVersion version;

protected:

  virtual bool	main( void ) = 0;

  pthread_t	threadId;
  
private:

  static void * threadEntry( void * );
  
  Thread( const Thread & from );
  Thread & operator =( const Thread & from );

};

#if !defined( inline )
#if !defined( CLUE_SHORT_FN )
#include <Thread.ii>
#else
#include <Thread.ii>
#endif
#undef inline
#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	Thread	class
//
//  Constructors:
//
//  	Thread( );
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
//  	    Return the name of this class (i.e. Thread )
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
//  	operator <<( ostream & dest, const Thread & obj );
//
#endif // ! def _Thread_hh_ 


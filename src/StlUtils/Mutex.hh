#ifndef _Mutex_hh_
#define _Mutex_hh_
//
// File:        Mutex.hh
// Desc:        
//
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     02/06/96 07:15
//
// Revision History:
//
// $Id$
//
// $Log$
// Revision 3.1  1996/11/14 01:23:51  houghton
// Changed to Release 3
//
// Revision 2.4  1996/11/04 14:20:26  houghton
// Changed to work even if CLUE_THREADS is not defined.
//
// Revision 2.3  1996/05/03 16:13:29  houghton
// Cleanup.
//
// Revision 2.2  1996/04/27 13:05:06  houghton
// Implemented Mutex locking. For theads.
//
// Revision 2.1  1996/02/29 19:06:08  houghton
// Initial Version
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <iostream>
#else
#include <ClueCfg.hh>
#include <iostream>
#endif

#if defined( CLUE_DEBUG )
#define inline
#endif

class Mutex
{

public:

  Mutex( void );

  virtual ~Mutex( void );

  bool		lock( void );
  bool		trylock( void );
  bool		unlock( void );
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  static const ClassVersion version;

protected:

private:

  Mutex( const Mutex & from );
  Mutex & operator =( const Mutex & from );

#if defined( CLUE_THREADS )
  pthread_mutex_t   mutex;
#endif
  int		    errorNum;
  
};

#if !defined( inline )
#if !defined( CLUE_SHORT_FN )
#include <Mutex.ii>
#else
#include <Mutex.ii>
#endif
#else
#undef inline
#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	Mutex	class
//
//  Constructors:
//
//  	Mutex( );
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
//  	    Return the name of this class (i.e. Mutex )
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
//  	operator <<( ostream & dest, const Mutex & obj );
//
#endif // ! def _Mutex_hh_ 


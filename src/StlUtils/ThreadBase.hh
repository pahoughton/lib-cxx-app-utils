#ifndef _ThreadBase_hh_
#define _ThreadBase_hh_
//
// File:        ThreadBase.hh
// Desc:        
//
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     04/25/96 06:16
//
// Revision History:
//
// $Id$
//
// $Log$
// Revision 3.1  1996/11/14 01:24:25  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:34:35  houghton
// Changed to be compilable even if CLUE_THREADS is not defined.
//
// Revision 2.1  1996/04/27 13:11:52  houghton
// Initial version.
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#else
#include <ClueCfg.hh>
#endif

#if defined( CLUE_DEBUG )
#define inline
#endif


class ThreadBase
{

public:

  ThreadBase( bool  detach );

  virtual ~ThreadBase( void );

  virtual bool	start( void );

  inline void		attach( void );
  inline void		detach( void );
  
  bool		join( void );
  
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

#if defined( CLUE_THREADS )
  pthread_t	threadId;
#endif
  bool		cleanup;
  int		errorNum;
  
private:

  static void * threadEntry( void * );
  
  ThreadBase( const ThreadBase & from );
  ThreadBase & operator =( const ThreadBase & from );

};

#if !defined( inline )
#if !defined( CLUE_SHORT_FN )
#include <ThreadBase.ii>
#else
#include <ThreadBase.ii>
#endif
#else
#undef inline
#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	ThreadBase	class
//
//  Constructors:
//
//  	ThreadBase( );
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
//  	    Return the name of this class (i.e. ThreadBase )
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
//  	operator <<( ostream & dest, const ThreadBase & obj );
//
#endif // ! def _ThreadBase_hh_ 


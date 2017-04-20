#ifndef _Mutex_hh_
#define _Mutex_hh_
//
// File:        Mutex.hh
// Project:	StlUtils ()
// Desc:        
//
//  Provides an interface to Thread mutexes.
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     02/06/96 07:15
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//
// $Id$ 

#if !defined( STLUTILS_SHORT_FN )
#include <StlUtilsConfig.hh>
#include <iostream>
#else
#include <StlUtilsCfg.hh>
#include <iostream>
#endif

#if defined( STLUTILS_DEBUG )
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
  virtual std::ostream &     dumpInfo( std::ostream &	dest = std::cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  static const ClassVersion version;

protected:

private:

  Mutex( const Mutex & from );
  Mutex & operator =( const Mutex & from );

#if defined( STLUTILS_THREADS )
  pthread_mutex_t   mutex;
#endif
  int		    errorNum;
  
};

#if !defined( inline )
#if !defined( STLUTILS_SHORT_FN )
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
//	virtual std::ostream &
//	toStream( std::ostream & dest ) const
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
//	virtual std::ostream &
//	dumpInfo( std::ostream & dest, const char * prefix, bool showVer )
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
//  	std::ostream &
//  	operator <<( std::ostream & dest, const Mutex & obj );
//

// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.3  2012/04/26 20:08:50  paul
// *** empty log message ***
//
// Revision 6.2  2011/12/30 23:57:17  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:42  houghton
// Changed to version 6
//
// Revision 5.3  2003/08/09 11:20:59  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:28:59  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:16  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:12:41  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:08:35  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:23:51  houghton
// Changed to Release 3
//
// Revision 2.4  1996/11/04 14:20:26  houghton
// Changed to work even if STLUTILS_THREADS is not defined.
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
#endif // ! def _Mutex_hh_ 


#ifndef _TimeIt_hh_
#define _TimeIt_hh_
//
// File:        TimeIt.hh
// Project:	Clue
// Desc:        
//
//
//
// Quick Start: - short example of class usage
//
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     01/17/97 07:55
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#include "ClueConfig.hh"
#include "DumpInfo.hh"
#include <iostream>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

#if defined( CLUE_DEBUG )
#define inline
#endif


class TimeIt
{

public:

  TimeIt( bool start = false );

  virtual ~TimeIt( void );

  inline void	    start( void );
  inline void	    stop( void );

  
  virtual ostream &	toStream( ostream & dest ) const;
  // virtual istream &	fromStream( istream & src );

  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  static const ClassVersion version;

  inline
  DumpInfo<TimeIt> dump( const char *   prefix = "    ",
			 bool		showVer = true ) const;

protected:

  struct timeval diffTimeVal( const timeval & t1,
			      const timeval & t2 ) const;
  
private:

  TimeIt( const TimeIt & from );
  TimeIt & operator =( const TimeIt & from );

  struct timeval realStart;
  struct timeval realStop;

  struct rusage	 usageStart;
  struct rusage  usageStop;

  int	osErrnum;
  
};

#if !defined( inline )
#include <TimeIt.ii>
#else
#undef inline

ostream &
operator << ( ostream & dest, const TimeIt & src );

#if defined( DO_FROMSTREAM )
istream &
operator >> ( istream & src, const TimeIt & dest );
#endif

#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	TimeIt	class
//
//  Constructors:
//
//  	TimeIt( );
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
//  	    Return the name of this class (i.e. TimeIt )
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
//  	operator <<( ostream & dest, const TimeIt & src );
//
//	istream &
//	operator >> ( istream & src, TimeIt & dest );
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
// Revision 3.1  1997/03/03 14:37:42  houghton
// Initial Version.
//
// Revision 1.1  1997/02/26 17:17:25  houghton
// Initial revision
//
//
#endif // ! def _TimeIt_hh_ 


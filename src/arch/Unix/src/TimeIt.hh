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
  TimeIt( const timeval & realStop, const rusage & usageStop );
  // TimeIt( const TimeIt & from ); default ok
  
  virtual ~TimeIt( void );

  inline void	    start( bool realOnly = false );
  inline void	    stop( void );

  inline timeval    getRealDiff( void ) const;
  inline rusage	    getUsageDiff( void ) const;
  
  virtual ostream &	toStream( ostream & dest ) const;
  // virtual istream &	fromStream( istream & src );

  // TimeIt &		operator = ( const TimeIt & from ); default ok
  
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

  timeval diffTimeVal( const timeval & t1,
		       const timeval & t2 ) const;
  
protected:

private:

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

template< class TimeItIterator >
inline
TimeIt
TimeItAverage( TimeItIterator first, TimeItIterator last )
{
  timeval   accumReal;
  rusage    accumUsage;

  accumReal.tv_usec	= 0;
  accumReal.tv_sec	= 0;

  accumUsage.ru_maxrss	    = 0;
  accumUsage.ru_ixrss	    = 0;
  accumUsage.ru_idrss	    = 0;
  accumUsage.ru_isrss	    = 0;
  accumUsage.ru_minflt	    = 0;
  accumUsage.ru_majflt	    = 0;
  accumUsage.ru_nswap	    = 0;
  accumUsage.ru_inblock	    = 0;
  accumUsage.ru_oublock	    = 0;
  accumUsage.ru_msgsnd	    = 0;
  accumUsage.ru_msgrcv	    = 0;
  accumUsage.ru_nsignals    = 0;
  accumUsage.ru_nvcsw	    = 0;
  accumUsage.ru_nivcsw	    = 0;
    
  long counter = 0;
  
  for( TimeItIterator it = first; it != last; ++ it )
    {
      ++ counter;
      
      accumReal.tv_usec += (*it).getRealDiff().tv_usec;
     
      if( accumReal.tv_usec > 1000000 )
	{
	  accumReal.tv_sec += (accumReal.tv_usec / 1000000);
	  accumReal.tv_usec = (accumReal.tv_usec % 1000000);
	}
	  
      accumReal.tv_sec += (*it).getRealDiff().tv_sec;
      
      accumUsage.ru_maxrss	+= (*it).getUsageDiff().ru_maxrss;
      accumUsage.ru_ixrss	+= (*it).getUsageDiff().ru_ixrss;
      accumUsage.ru_idrss	+= (*it).getUsageDiff().ru_idrss;
      accumUsage.ru_isrss	+= (*it).getUsageDiff().ru_isrss;
      accumUsage.ru_minflt	+= (*it).getUsageDiff().ru_minflt;
      accumUsage.ru_majflt	+= (*it).getUsageDiff().ru_majflt;
      accumUsage.ru_nswap	+= (*it).getUsageDiff().ru_nswap;
      accumUsage.ru_inblock	+= (*it).getUsageDiff().ru_inblock;
      accumUsage.ru_oublock	+= (*it).getUsageDiff().ru_oublock;
      accumUsage.ru_msgsnd	+= (*it).getUsageDiff().ru_msgsnd;
      accumUsage.ru_msgrcv	+= (*it).getUsageDiff().ru_msgrcv;
      accumUsage.ru_nsignals	+= (*it).getUsageDiff().ru_nsignals;
      accumUsage.ru_nvcsw	+= (*it).getUsageDiff().ru_nvcsw;
      accumUsage.ru_nivcsw	+= (*it).getUsageDiff().ru_nivcsw;
    }
  
  if( counter )
    {
      accumReal.tv_usec	/= counter;
      accumReal.tv_sec	/= counter;

      accumUsage.ru_maxrss	/= counter;
      accumUsage.ru_ixrss	/= counter;
      accumUsage.ru_idrss	/= counter;
      accumUsage.ru_isrss	/= counter;
      accumUsage.ru_minflt	/= counter;
      accumUsage.ru_majflt	/= counter;
      accumUsage.ru_nswap	/= counter;
      accumUsage.ru_inblock	/= counter;
      accumUsage.ru_oublock	/= counter;
      accumUsage.ru_msgsnd	/= counter;
      accumUsage.ru_msgrcv	/= counter;
      accumUsage.ru_nsignals	/= counter;
      accumUsage.ru_nvcsw	/= counter;
      accumUsage.ru_nivcsw	/= counter;
    }

  TimeIt    timer( accumReal, accumUsage );

  return( timer );
}

template< class TimeItIterator >
inline
TimeItIterator
TimeItBestReal( TimeItIterator first, TimeItIterator last )
{
  TimeItIterator    best = first;

  for( TimeItIterator them = first;
       them != last;
       ++ them )
    {
      if( (*them).tv_sec == (*best).tv_sec )
	{
	  if( (*them).tv_usec < (*best).tv_usec )
	    best = them;
	}
      else
	{
	  if( (*them).tv_sec < (*best).tv_sec )
	    best = them;
	}
    }

  return( best );
}

template< class TimeItIterator >
inline
TimeItIterator
TimeItWorstReal( TimeItIterator first, TimeItIterator last )
{
  TimeItIterator    worst = first;

  for( TimeItIterator them = first;
       them != last;
       ++ them )
    {
      if( (*them).tv_sec == (*worst).tv_sec )
	{
	  if( (*them).tv_usec > (*worst).tv_usec )
	    worst = them;
	}
      else
	{
	  if( (*them).tv_sec > (*worst).tv_sec )
	    worst = them;
	}
    }

  return( worst );
}

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
// Revision 3.2  1997/03/19 16:26:48  houghton
// Added constructor.
// Added TimeItAverate template funct.
// Added TimeItBestReal template funct.
// Added TimeItWorstReal template funct.
//
// Revision 3.1  1997/03/03 14:37:42  houghton
// Initial Version.
//
// Revision 1.1  1997/02/26 17:17:25  houghton
// Initial revision
//
//
#endif // ! def _TimeIt_hh_ 


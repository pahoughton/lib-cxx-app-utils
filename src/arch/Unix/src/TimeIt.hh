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
#include <cstring>
#include <algorithm>

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

  timeval diffTimeVal( const timeval & stopTime,
		       const timeval & startTime ) const;
  
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

class TimeItAccuBinaryOp
{
public:

  TimeIt operator () ( const TimeIt & accu, const TimeIt & src ) const {
    
    timeval   accumReal( accu.getRealDiff() );
    rusage    accumUsage( accu.getUsageDiff() );

    // real time
    accumReal.tv_usec += src.getRealDiff().tv_usec;
    
    if( accumReal.tv_usec > 1000000 )
      {
	accumReal.tv_sec += (accumReal.tv_usec / 1000000);
	accumReal.tv_usec = (accumReal.tv_usec % 1000000);
      }
    
    accumReal.tv_sec += src.getRealDiff().tv_sec;
    
    // user time
    accumUsage.ru_utime.tv_usec += src.getUsageDiff().ru_utime.tv_usec;
    
    if( accumUsage.ru_utime.tv_usec > 1000000 )
      {
	accumUsage.ru_utime.tv_sec +=
	  (accumUsage.ru_utime.tv_usec / 1000000);
	accumUsage.ru_utime.tv_usec =
	  (accumUsage.ru_utime.tv_usec % 1000000);
      }
    
    accumUsage.ru_utime.tv_sec += src.getUsageDiff().ru_utime.tv_sec;
    
    // sys time
    accumUsage.ru_stime.tv_usec += src.getUsageDiff().ru_stime.tv_usec;
    
    if( accumUsage.ru_stime.tv_usec > 1000000 )
      {
	accumUsage.ru_stime.tv_sec +=
	  (accumUsage.ru_stime.tv_usec / 1000000);
	accumUsage.ru_stime.tv_usec =
	  (accumUsage.ru_stime.tv_usec % 1000000);
      }
    
    accumUsage.ru_stime.tv_sec	+= src.getUsageDiff().ru_stime.tv_sec;
    
    accumUsage.ru_maxrss	+= src.getUsageDiff().ru_maxrss;
    accumUsage.ru_ixrss		+= src.getUsageDiff().ru_ixrss;
    accumUsage.ru_idrss		+= src.getUsageDiff().ru_idrss;
    accumUsage.ru_isrss		+= src.getUsageDiff().ru_isrss;
    accumUsage.ru_minflt	+= src.getUsageDiff().ru_minflt;
    accumUsage.ru_majflt	+= src.getUsageDiff().ru_majflt;
    accumUsage.ru_nswap		+= src.getUsageDiff().ru_nswap;
    accumUsage.ru_inblock	+= src.getUsageDiff().ru_inblock;
    accumUsage.ru_oublock	+= src.getUsageDiff().ru_oublock;
    accumUsage.ru_msgsnd	+= src.getUsageDiff().ru_msgsnd;
    accumUsage.ru_msgrcv	+= src.getUsageDiff().ru_msgrcv;
    accumUsage.ru_nsignals	+= src.getUsageDiff().ru_nsignals;
    accumUsage.ru_nvcsw		+= src.getUsageDiff().ru_nvcsw;
    accumUsage.ru_nivcsw	+= src.getUsageDiff().ru_nivcsw;

    return( TimeIt( accumReal, accumUsage ) );
    
  };
};

  
template< class TimeItIterator >
inline
TimeIt
TimeItAccumulate( TimeItIterator first, TimeItIterator last )
{
  return( accumulate( first, last, TimeIt(), TimeItAccuBinaryOp() ) );
}

template< class TimeItIterator >
inline
TimeIt
TimeItAverage( TimeItIterator first, TimeItIterator last )
{
    
  long counter = 0;

  for( TimeItIterator it = first; it != last; ++ it )
    {
      ++ counter;
    }
  
  TimeIt    accu( TimeItAccumulate( first, last ) );

  timeval   accumReal( accu.getRealDiff() );
  rusage    accumUsage( accu.getUsageDiff() );
  
  if( counter )
    {
      accumReal.tv_usec	/= counter;
      accumReal.tv_sec	/= counter;

      accumUsage.ru_utime.tv_usec /= counter;
      accumUsage.ru_utime.tv_sec  /= counter;
      
      accumUsage.ru_stime.tv_usec /= counter;
      accumUsage.ru_stime.tv_sec  /= counter;
      
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
      if( (*them).getRealDiff().tv_sec == (*best).getRealDiff().tv_sec )
	{
	  if( (*them).getRealDiff().tv_usec < (*best).getRealDiff().tv_usec )
	    best = them;
	}
      else
	{
	  if( (*them).getRealDiff().tv_sec < (*best).getRealDiff().tv_sec )
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
      if( (*them).getRealDiff().tv_sec == (*worst).getRealDiff().tv_sec )
	{
	  if( (*them).getRealDiff().tv_usec > (*worst).getRealDiff().tv_usec )
	    worst = them;
	}
      else
	{
	  if( (*them).getRealDiff().tv_sec > (*worst).getRealDiff().tv_sec )
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
// Revision 3.4  1997/07/11 15:53:25  houghton
// Bug-Fix: TimeItAverage() - was not averageing stime or utime.
// Changed TimeItAverage() to use new TimeItAccumulate.
// Added TimeItAccumulate.
//
// Revision 3.3  1997/03/21 12:29:19  houghton
// Cleanup.
//
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


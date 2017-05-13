#ifndef _clue_TimeIt_hpp_
#define _clue_TimeIt_hpp_
/* 1997-01-17 (cc) Paul Houghton <paul4hough@gmail.com>

  Time an operation.
*/

#include "DumpInfo.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

namespace clue {

class TimeIt
{

public:

  TimeIt( bool start = false );
  TimeIt( const timeval & realStop, const rusage & usageStop );
  // TimeIt( const TimeIt & from ); default ok

  virtual ~TimeIt( void );

  inline void	    start( bool realOnly = false );
  inline void	    stop( void );

  inline const timeval &    getStartRealTime( void ) const;

  inline timeval    getRealDiff( void ) const;
  inline rusage	    getUsageDiff( void ) const;

  inline time_t	    getRealStartTimeT( void ) const;
  inline time_t	    getRealStopTimeT( void ) const;

  virtual std::ostream &	toStream( std::ostream & dest ) const;
  // virtual istream &	fromStream( istream & src );

  // TimeIt &		operator = ( const TimeIt & from ); default ok

  virtual bool	    	 good( void ) const;
  virtual const char * 	 error( void ) const;
  virtual std::ostream & dumpInfo( std::ostream & dest = std::cerr,
				   const char *   prefix = "    " ) const;

  inline
  DumpInfo<TimeIt> dump( const char *   prefix = "    ") const;

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


inline
void
TimeIt::start( bool realOnly )
{
  if( ! realOnly )
    {
      if( getrusage( RUSAGE_SELF, &usageStart ) )
	osErrnum = (osErrnum ? osErrnum : errno );
    }

  if( gettimeofday( &realStart, 0 ) )
    osErrnum = (osErrnum ? osErrnum : errno );
}

inline
void
TimeIt::stop( void )
{

  if( gettimeofday( &realStop, 0 ) )
    osErrnum = (osErrnum ? osErrnum : errno );

  if( getrusage( RUSAGE_SELF, &usageStop ) )
    osErrnum = (osErrnum ? osErrnum : errno );

}

inline
const timeval &
TimeIt::getStartRealTime( void ) const
{
  return( realStart );
}

inline
timeval
TimeIt::getRealDiff( void ) const
{
  return( diffTimeVal( realStop, realStart ) );
}

inline
rusage
TimeIt::getUsageDiff( void ) const
{
  rusage    diffUsage;

  diffUsage.ru_utime	    = diffTimeVal( usageStop.ru_utime,
					   usageStart.ru_utime );
  diffUsage.ru_stime	    = diffTimeVal( usageStop.ru_stime,
					   usageStart.ru_stime );

  diffUsage.ru_maxrss	    = usageStop.ru_maxrss - usageStart.ru_maxrss;
  diffUsage.ru_ixrss	    = usageStop.ru_ixrss - usageStart.ru_ixrss;
  diffUsage.ru_idrss	    = usageStop.ru_idrss - usageStart.ru_idrss;
  diffUsage.ru_isrss	    = usageStop.ru_isrss - usageStart.ru_isrss;
  diffUsage.ru_minflt	    = usageStop.ru_minflt - usageStart.ru_minflt;
  diffUsage.ru_majflt	    = usageStop.ru_majflt - usageStart.ru_majflt;
  diffUsage.ru_nswap	    = usageStop.ru_nswap - usageStart.ru_nswap;
  diffUsage.ru_inblock	    = usageStop.ru_inblock - usageStart.ru_inblock;
  diffUsage.ru_oublock	    = usageStop.ru_oublock - usageStart.ru_oublock;
  diffUsage.ru_msgsnd	    = usageStop.ru_msgsnd - usageStart.ru_msgsnd;
  diffUsage.ru_msgrcv	    = usageStop.ru_msgrcv - usageStart.ru_msgrcv;
  diffUsage.ru_nsignals     = usageStop.ru_nsignals - usageStart.ru_nsignals;
  diffUsage.ru_nvcsw	    = usageStop.ru_nvcsw - usageStart.ru_nvcsw;
  diffUsage.ru_nivcsw	    = usageStop.ru_nivcsw - usageStart.ru_nivcsw;

  return( diffUsage );
}

inline
time_t
TimeIt::getRealStartTimeT( void ) const
{
  return( realStart.tv_sec );
}

inline
time_t
TimeIt::getRealStopTimeT( void ) const
{
  return( realStop.tv_sec );
}

inline
DumpInfo<TimeIt>
TimeIt::dump( const char * prefix ) const
{
  return( DumpInfo<TimeIt>( *this, prefix ) );
}


inline
std::ostream &
operator << ( std::ostream & dest, const TimeIt & obj )
{
  return( obj.toStream( dest ) );
}


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

}; // namespace clue

#endif // ! def _clue_TimeIt_hpp_

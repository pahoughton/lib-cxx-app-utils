// 1997-01-17 (cc) Paul Houghton <paul4hough@gmail.com>

#include "TimeIt.hpp"
#include "Str.hpp"
#include "Clue.hpp"

#include <iomanip>
#include <cstring>

namespace clue {

TimeIt::TimeIt( bool startTimer )
  : osErrnum(0)
{
  memset( &realStart,  0, sizeof( realStart ) );
  memset( &realStop,   0, sizeof( realStop ) );
  memset( &usageStart, 0, sizeof( usageStart ) );
  memset( &usageStop,  0, sizeof( usageStop ) );

  if( startTimer )
    start();
}

TimeIt::TimeIt( const timeval & stopReal, const rusage & stopUsage )
  : osErrnum(0)
{
  memset( &realStart,  0, sizeof( realStart ) );
  memset( &usageStart, 0, sizeof( usageStart ) );

  memcpy( &realStop,   &stopReal, sizeof( realStop ) );
  memcpy( &usageStop,  &stopUsage, sizeof( usageStop ) );
}


TimeIt::~TimeIt( void )
{
}

std::ostream &
TimeIt::toStream( std::ostream & dest ) const
{
  if( good() )
    {
      struct timeval rDiff( diffTimeVal( realStop, realStart ) );
      struct timeval uDiff( diffTimeVal( usageStop.ru_utime,
					 usageStart.ru_utime ) );
      struct timeval sDiff( diffTimeVal( usageStop.ru_stime,
					 usageStart.ru_stime ) );

      char ofill = dest.fill('0');

      dest << "Times: "
	   << " real: " << rDiff.tv_sec << '.' << std::setw(6) << rDiff.tv_usec
	   << " user: " << uDiff.tv_sec << '.' << std::setw(6) << uDiff.tv_usec
	   << " sys: "  << sDiff.tv_sec << '.' << std::setw(6) << sDiff.tv_usec
	;
      dest.fill(ofill);
    }
  else
    {
      dest << error();
    }


  return( dest );
}

struct timeval
TimeIt::diffTimeVal( const timeval & t1, const timeval & t2 ) const
{
  struct timeval dif;

  dif.tv_sec  = t1.tv_sec  - t2.tv_sec;
  dif.tv_usec = t1.tv_usec - t2.tv_usec;

  if( dif.tv_sec > 0 && dif.tv_usec < 0 )
    {
      dif.tv_sec--;
      dif.tv_usec += 1000000;
    }
  else
    {
      if( dif.tv_sec < 0 && dif.tv_usec > 0 )
	{
	  dif.tv_sec++;
	  dif.tv_usec = labs(dif.tv_usec - 1000000);
	}
    }
  return( dif );
}


bool
TimeIt::good( void ) const
{
  return( ! osErrnum );
}

const char *
TimeIt::error( void ) const
{
  static Str errStr;

  errStr = "TimeIt::";

  if( good() )
    {
      errStr << ": ok";
    }
  else
    {
      size_t eSize = errStr.size();

      if( osErrnum )
	errStr << ": " << strerror( osErrnum );

      if( eSize == errStr.size() )
        errStr += ": unknown error";
    }

  return( errStr.c_str() );
}

std::ostream &
TimeIt::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

  if( ! TimeIt::good() )
    dest << prefix << "Error: " << TimeIt::error() << '\n';
  else
    dest << prefix << "Good" << '\n';

  struct timeval rDiff( diffTimeVal( realStop, realStart ) );
  struct timeval uDiff( diffTimeVal( usageStop.ru_utime,
				     usageStart.ru_utime ) );
  struct timeval sDiff( diffTimeVal( usageStop.ru_stime,
				     usageStart.ru_stime ) );

  char ofill;

  dest << prefix << "real time diff:       "
       << std::setw(8) << rDiff.tv_sec << '.'
    ;

  ofill = dest.fill('0');
  dest << std::setw(6) << rDiff.tv_usec << '\n';
  dest.fill(ofill);

  dest << prefix << "user time diff:       "
       << std::setw(8) << uDiff.tv_sec << '.'
    ;

  ofill = dest.fill('0');
  dest << std::setw(6) << uDiff.tv_usec << '\n';
  dest.fill(ofill);

  dest << prefix << "sys time diff:        "
       << std::setw(8) << sDiff.tv_sec << '.'
    ;

  ofill = dest.fill('0');
  dest << std::setw(6) << sDiff.tv_usec << '\n';
  dest.fill(ofill);

  dest << prefix << "max rss diff:         "
       << std::setw(8) << usageStop.ru_maxrss - usageStart.ru_maxrss << '\n'
       << prefix << "shared mem size diff: "
       << std::setw(8) << usageStop.ru_ixrss - usageStart.ru_ixrss << '\n'
       << prefix << "data size diff:       "
       << std::setw(8) << usageStop.ru_idrss - usageStart.ru_idrss << '\n'
       << prefix << "stack size diff:      "
       << std::setw(8) << usageStop.ru_isrss - usageStart.ru_isrss << '\n'
       << prefix << "page reclaims diff:   "
       << std::setw(8) << usageStop.ru_minflt - usageStart.ru_minflt << '\n'
       << prefix << "page faults diff:     "
       << std::setw(8) << usageStop.ru_majflt - usageStart.ru_majflt << '\n'
       << prefix << "swaps diff:           "
       << std::setw(8) << usageStop.ru_nswap - usageStart.ru_nswap << '\n'
       << prefix << "in block diff:        "
       << std::setw(8) << usageStop.ru_inblock - usageStart.ru_inblock << '\n'
       << prefix << "out block diff:       "
       << std::setw(8) << usageStop.ru_oublock - usageStart.ru_oublock << '\n'
       << prefix << "msgs sent diff:       "
       << std::setw(8) << usageStop.ru_msgsnd - usageStart.ru_msgsnd << '\n'
       << prefix << "msgs rcvd diff:       "
       << std::setw(8) << usageStop.ru_msgrcv - usageStart.ru_msgrcv << '\n'
       << prefix << "signals diff:         "
       << std::setw(8) << usageStop.ru_nsignals - usageStart.ru_nsignals << '\n'
       << prefix << "vol ctx swt diff:     "
       << std::setw(8) << usageStop.ru_nvcsw - usageStart.ru_nvcsw << '\n'
       << prefix << "invol ctx swt diff:   "
       << std::setw(8) << usageStop.ru_nivcsw - usageStart.ru_nivcsw << '\n'
    ;

  return( dest );
}

}; // namespace clue

//
// File:        TimeIt.C
// Project:	Clue
// Desc:        
//
//  Compiled sources for TimeIt
//  
// Author:      Paul A. Houghton - (houghton@cshore.wcom.com)
// Created:     01/17/97 07:59
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include "TimeIt.hh"
#include <ClueUtils.hh>
#include <Str.hh>
#include <iomanip>
#include <cstring>

#if defined( CLUE_DEBUG )
#include "TimeIt.ii"
#endif

CLUE_VERSION(
  TimeIt,
  "$Id$");


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

ostream &
TimeIt::toStream( ostream & dest ) const
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
	   << "real: " << rDiff.tv_sec << '.' << setw(6) << rDiff.tv_usec
	   << "user: " << uDiff.tv_sec << '.' << setw(6) << uDiff.tv_usec
	   << "sys: " << sDiff.tv_sec << '.' << setw(6) << sDiff.tv_usec
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
	  dif.tv_usec = abs(dif.tv_usec - 1000000);
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

  errStr = TimeIt::getClassName();

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

const char *
TimeIt::getClassName( void ) const
{
  return( "TimeIt" );
}

const char *
TimeIt::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}


ostream &
TimeIt::dumpInfo(
  ostream &	dest,
  const char *	prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << TimeIt::getClassName() << ":\n"
	 << TimeIt::getVersion() << '\n';

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
       << setw(8) << rDiff.tv_sec << '.'
    ;
  
  ofill = dest.fill('0');
  dest << setw(6) << rDiff.tv_usec << '\n';
  dest.fill(ofill);

  dest << prefix << "user time diff:       "
       << setw(8) << uDiff.tv_sec << '.'
    ;

  ofill = dest.fill('0');
  dest << setw(6) << uDiff.tv_usec << '\n';
  dest.fill(ofill);
  
  dest << prefix << "sys time diff:        "
       << setw(8) << sDiff.tv_sec << '.'
    ;
  
  ofill = dest.fill('0');
  dest << setw(6) << sDiff.tv_usec << '\n';
  dest.fill(ofill);

  dest << prefix << "max rss diff:         "
       << setw(8) << usageStop.ru_maxrss - usageStart.ru_maxrss << '\n'
       << prefix << "shared mem size diff: "
       << setw(8) << usageStop.ru_ixrss - usageStart.ru_ixrss << '\n'
       << prefix << "data size diff:       "
       << setw(8) << usageStop.ru_idrss - usageStart.ru_idrss << '\n'
       << prefix << "stack size diff:      "
       << setw(8) << usageStop.ru_isrss - usageStart.ru_isrss << '\n'
       << prefix << "page reclaims diff:   "
       << setw(8) << usageStop.ru_minflt - usageStart.ru_minflt << '\n'
       << prefix << "page faults diff:     "
       << setw(8) << usageStop.ru_majflt - usageStart.ru_majflt << '\n'
       << prefix << "swaps diff:           "
       << setw(8) << usageStop.ru_nswap - usageStart.ru_nswap << '\n'
       << prefix << "in block diff:        "
       << setw(8) << usageStop.ru_inblock - usageStart.ru_inblock << '\n'
       << prefix << "out block diff:       "
       << setw(8) << usageStop.ru_oublock - usageStart.ru_oublock << '\n'
       << prefix << "msgs sent diff:       "
       << setw(8) << usageStop.ru_msgsnd - usageStart.ru_msgsnd << '\n'
       << prefix << "msgs rcvd diff:       "
       << setw(8) << usageStop.ru_msgrcv - usageStart.ru_msgrcv << '\n'
       << prefix << "signals diff:         "
       << setw(8) << usageStop.ru_nsignals - usageStart.ru_nsignals << '\n'
       << prefix << "vol ctx swt diff:     "
       << setw(8) << usageStop.ru_nvcsw - usageStart.ru_nvcsw << '\n'
       << prefix << "invol ctx swt diff:   "
       << setw(8) << usageStop.ru_nivcsw - usageStart.ru_nivcsw << '\n'
    ;
  
  return( dest );
}

// Revision Log:
//
// $Log$
// Revision 3.3  1997/03/19 16:25:43  houghton
// Added constructor.
//
// Revision 3.2  1997/03/03 19:05:20  houghton
// Changed from using 'string' to 'Str'
//
// Revision 3.1  1997/03/03 14:37:41  houghton
// Initial Version.
//
// Revision 1.1  1997/02/26 17:17:25  houghton
// Initial revision
//
//

// 1994-02-20 (cc) Paul Houghton <paul4hough@gmail.com>

#include "DateRangeWeekly.hpp"
#include "DateTimeUtils.hpp"
#include "Clue.hpp"
#include "Str.hpp"

#include <iomanip>

namespace clue {

const time_t DateRangeWeekly::M_freq = (24 * 60 * 60 * 7);


bool
DateRangeWeekly::isIn( const DateTime & dateTwo ) const
{
  return( dayOfWeek() == dateTwo.dayOfWeek()
	  && DateRangeDaily::isIn( dateTwo ) );
}

time_t
DateRangeWeekly::secIn( const DateRange & dateTwo ) const
{
  time_t   secOfWeek = ( (dateTwo.dayOfWeek() * SecPerDay) +
       	 	         dateTwo.secOfDay() );

  return( UnionOfDur( start(), dur(),
		      secOfWeek, dateTwo.dur(),
		      freq() ) );
}

time_t
DateRangeWeekly::startsIn( const DateRange & dateTwo ) const
{
  time_t  secs = 0;
  time_t  secOfWeek = ( (dateTwo.dayOfWeek() * SecPerDay) +
    		      	dateTwo.secOfDay() );

  if( secOfWeek >= start() &&
      secOfWeek <= start() + dur() )
    {
      secs = secIn( dateTwo );
    }
  return( secs );
}

std::ostream &
DateRangeWeekly::toStream( std::ostream & dest ) const
{
  dest << "Start: "
       << AbbrWeekDays[ dayOfWeek() ] << ' '
       << std::setfill('0')
       << std::setw(2) << HourInTimeT( start() ) << ':'
       << std::setw(2) << MinInTimeT( start() ) << ':'
       << std::setw(2) << SecInTimeT( start() ) << ' '
       << "Dur: "
       << std::setw(2) << HourInTimeT( dur() ) << ':'
       << std::setw(2) << MinInTimeT( dur() ) << ':'
       << std::setw(2) << SecInTimeT( dur() )
       << std::setfill(' ')
       ;
  return( dest );
}

bool
DateRangeWeekly::good( void ) const
{
  return( start() >= 0 );
}

const char *
DateRangeWeekly::error( void ) const
{
  static Str errStr;
  errStr.reset();

  errStr << "DateRangeWeekly:";


  if( good() )
    {
      errStr << "Ok";
    }
  else
    {
      if( ! DateRange::good() )
	{
	  errStr << ' ' << DateRange::error();
	}

      if( ! (start() >= 0 ) )
	{
	  errStr << " getStart < 0";
	}

      if( ! (start() < (SecPerDay * 7) ) )
	{
	  errStr << " start >= 7 days";
	}
    }
  return( errStr.cstr() );
}


std::ostream &
DateRangeWeekly::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

  if( ! DateRangeWeekly::good() )
    dest << prefix << "Error: " << DateRangeWeekly::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  dest << prefix << "range:    ";
  DateRangeWeekly::toStream( dest );
  dest << '\n';

  Str pre;
  pre << prefix << "DateRangeDaily::";

  DateRangeDaily::dumpInfo( dest, pre );
  dest << prefix << "dow:     " << dayOfWeek() << '\n'
       << prefix << "freq:    " << freq() << '\n';

  dest << '\n';

  return( dest  );
}

}; // namespace clue

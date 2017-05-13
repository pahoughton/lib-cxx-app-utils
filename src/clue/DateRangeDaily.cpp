// 1994-02-20 (cc) Paul Houghton <paul4hough@gmail.com>

#include "DateRangeDaily.hpp"
#include "DateTimeUtils.hpp"
#include "Clue.hpp"
#include "Str.hpp"
#include <iomanip>

namespace clue {

const time_t DateRangeDaily::M_freq = (24 * 60 * 60); // SecPerDay

bool
DateRangeDaily::isIn( const DateTime & dateTwo )  const
{
  return( secOfDay() <= dateTwo.secOfDay()
	  && dateTwo.secOfDay() <= (secOfDay() + dur()) );
}

time_t
DateRangeDaily::secIn( const DateRange & dateTwo ) const
{
  return( UnionOfDur( timet(), dur(),
		      dateTwo.secOfDay(), dateTwo.dur(),
		      freq() ) );
}


time_t
DateRangeDaily::startsIn( const DateRange & dateTwo ) const
{
  time_t  secs = 0;

  if( dateTwo.secOfDay() >= timet() &&
      dateTwo.secOfDay() <= timet() + dur() )
    {
      secs = secIn( dateTwo );
    }
  return( secs );
}

int
DateRangeDaily::compare( const DateTime & two ) const
{
  return( DateRange::compare( two ) );
}

int
DateRangeDaily::compare( const DateRange & two ) const
{
  int diff = clue::compare( start(), (time_t)two.secOfDay() );
  if( diff )
    return( diff );
  else
    return( clue::compare( dur(), two.dur() ) );
}

int
DateRangeDaily::compare( const DateRangeDaily & two ) const
{
  int diff = clue::compare( start(), two.start() );
  if( diff )
    return( diff );
  else
    return( clue::compare( dur(), two.dur() ) );
}

std::ostream &
DateRangeDaily::toStream( std::ostream & dest ) const
{

  dest << "Start: "
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
DateRangeDaily::good( void ) const
{
  return( DateRange::good() &&
	  timet() >= 0 && timet() < SecPerDay );
}

const char *
DateRangeDaily::error( void ) const
{
  static Str errStr;
  errStr.reset();

  errStr << "DateRangeDaily:";


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

      if( ! (timet() >= 0 ) )
	{
	  errStr << " start < 0";
	}

      if( ! (timet() < SecPerDay ) )
	{
	  errStr << " start >= 1 day";
	}
    }
  return( errStr.cstr() );
}


std::ostream &
DateRangeDaily::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

  if( ! DateRangeDaily::good() )
    dest << prefix << "Error: " << DateRangeDaily::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  dest << prefix << "range:    ";
  DateRangeDaily::toStream( dest );
  dest << '\n';

  Str pre;
  pre << prefix << "DateRange::";

  DateRange::dumpInfo( dest, pre );

  dest << prefix << "freq:     " << freq() << '\n'
    ;

  dest << '\n';

  return( dest  );
}

}; // namespace clue

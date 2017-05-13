// 2017-05-05 (cc) <paul4hough@gmail.com>

#include "DateTimeUtils.hpp"
#include <cstdlib>
#include <ctime>

namespace clue {

time_t
TimetFrom(
  int 	year,
  int 	month,
  int	day,
  int 	hour,
  int	min,
  int	sec
  )
{
  time_t secs = 0;

  if( year >= 0 ) {
    // this is a best guess for 2 digit years
    if( year > 100 )
      year = year;
    else
      year = 1900 + ( year < 50 ? year + 100 : year );

    // safty valve - if year is out of range, use min/max
    // posible time_t value
    if( year > MaxYear )
      return( MaxTimeT );
    else
      if( year < MinYear )
	return( MinTimeT );

    // 1968 was a leap year
    // leap years are every 4 years except centuries unless the centruy
    // is divisable by 400 (i.e. 1600 & 2000 are leap years and
    // 1700, 1800, 1900 are not leap years).
    //
    long	leapCount = 0;
    leapCount = ( ((abs( year - 1970 ) + 2) / 4)
		  - (abs( year - 1900 ) / 100)
		  );

    leapCount += ( ( year < 2000  ?
		     abs( year - 2000 ) / 400 :
		     abs( year - 1600 ) / 400 ));

    if( IsLeapYear( year ) && year > 1970 )
      -- leapCount;

    if( year < 1970 )
      leapCount *= -1;

    secs = ((year - 1970) * SecPerYear) + (leapCount * SecPerDay);
  }

  if( month > 0 ) {
    secs += SecPerDay * MonthDayOfYear[ month - 1 ];

    if( IsLeapYear( year ) && month > 2 )
      secs += SecPerDay;
  }

  if( day > 0 ) {
    day--;

    secs += SecPerDay * day;
  }

  secs += ( (hour * 60 * 60 ) + (min * 60) + sec );

  return( secs );
}

time_t
TimetFrom( const struct tm & tm )
{
  time_t secs = TimetFrom( tm.tm_year + 1900,
			   tm.tm_mon + 1,
			   tm.tm_mday,
			   tm.tm_hour,
			   tm.tm_min,
			   tm.tm_sec );
  return( secs + tm.tm_gmtoff );
}


}; // namespace clue

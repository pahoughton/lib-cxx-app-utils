#ifndef _clue_DateRangeWeekly_hpp_
#define _clue_DateRangeWeekly_hpp_
/* 1994-02-20 (cc) Paul Houghton <paul4hough@gmail.com>

   A DateRange who's operations only apply to a specific day of the week.
*/
#include <clue/DateRangeDaily.hpp>

namespace clue {

class DateRangeWeekly : public DateRangeDaily
{

public:

  inline DateRangeWeekly( short dayOfWeek, time_t startTime, time_t durSec );

  virtual time_t    freq( void ) const { return( M_freq ); };

  virtual bool	    isIn( const DateTime & dateTwo ) const;
  virtual time_t    secIn( const DateRange & dateTwo ) const;
  virtual time_t    startsIn( const DateRange & dateTwo ) const;

  virtual std::ostream & 	toStream( std::ostream & dest ) const;

  friend inline std::ostream & operator << ( std::ostream &		dest,
					const DateRangeWeekly & obj );

  virtual bool		    good( void ) const;
  virtual const char *	    error( void ) const;
  virtual std::ostream &    dumpInfo( std::ostream &	dest = std::cerr,
				      const char *	prefix = "    " ) const;

private:

  static const time_t    M_freq;
};


inline
DateRangeWeekly::DateRangeWeekly(
  short   dayOfWeek,
  time_t  startTime,
  time_t  durSec
  )
  : DateRangeDaily( (dayOfWeek * SecPerDay) + startTime, durSec )
{
  m_tm.tm_wday = (m_tm.tm_wday + Wednesday) % 7;
}

inline
int
compare( const DateRangeWeekly & one, const DateRangeWeekly & two )
{
  return( one.compare( two ) );
}


inline
std::ostream &
operator << ( std::ostream & dest, const DateRangeWeekly & obj )
{
  return( obj.toStream( dest ) );
}

}; // namespace clue

#endif // ! def _clue_DateRangeWeekly_hpp_

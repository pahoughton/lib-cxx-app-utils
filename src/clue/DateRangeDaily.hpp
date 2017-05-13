#ifndef _clue_DateRangeDaily_hpp_
#define _clue_DateRangeDaily_hpp_
/* 1994-02-20 (cc) Paul Houghton <paul4hough@gmail.com>

   Used in comparing two DateRanges. A DateRangeDaily has a start
   (date/time) plus a duration(end date/time). All operations
   only apply to a single day.
*/

#include <clue/DateRange.hpp>

namespace clue {

class DateRangeDaily : public DateRange
{

public:

  inline DateRangeDaily( time_t startTime, time_t durSec );

  virtual time_t	    start( void ) const { return( timet() ); };
  virtual DateRangeDaily &  start( time_t val ) { timet(val);return *this; };

  virtual time_t	freq( void ) const { return( M_freq ); };

  virtual bool	    isIn( const DateTime & dateTwo ) const ;
  virtual time_t    secIn( const DateRange & dateTwo ) const;
  virtual time_t    startsIn( const DateRange & dateTwo ) const;

  virtual int	    compare( const DateTime & two ) const;
  virtual int	    compare( const DateRange & two ) const;
  virtual int	    compare( const DateRangeDaily & two ) const;

  bool		    operator == ( const DateRangeDaily & two ) const;
  bool		    operator <  ( const DateRangeDaily & two ) const;

  inline bool		operator != ( const DateRangeDaily & rhs ) const;
  inline bool		operator >  ( const DateRangeDaily & rhs ) const;
  inline bool		operator <= ( const DateRangeDaily & rhs ) const;
  inline bool		operator >= ( const DateRangeDaily & rhs ) const;

  virtual std::ostream & 	toStream( std::ostream & dest ) const;

  friend inline std::ostream & operator << ( std::ostream &		dest,
                                             const DateRangeDaily &  obj );

  virtual bool		    good( void ) const;
  virtual const char *	    error( void ) const;
  virtual std::ostream &    dumpInfo( std::ostream &	dest = std::cerr,
				      const char *	prefix = "    " ) const;

private:

  static const time_t	M_freq;

};


inline
DateRangeDaily::DateRangeDaily( time_t startTime, time_t durSec )
  : DateRange( startTime, durSec )
{
}

inline
bool
DateRangeDaily::operator == ( const DateRangeDaily & two ) const
{
  return( compare( two ) == 0 );
}

inline
bool
DateRangeDaily::operator <  ( const DateRangeDaily & two ) const
{
  return( compare( two ) < 0 );
}


inline
bool
DateRangeDaily::operator != ( const DateRangeDaily & rhs ) const
{
  return( ! (*this == rhs) );
}

inline
bool
DateRangeDaily::operator > ( const DateRangeDaily & rhs ) const
{
  return( rhs < *this );
}

inline
bool
DateRangeDaily::operator <= ( const DateRangeDaily & rhs ) const
{
  return( ! (rhs < *this) );
}

inline
bool
DateRangeDaily::operator >= ( const DateRangeDaily & rhs ) const
{
  return( ! (*this < rhs) );
}

int compare( const DateRangeDaily & one, const DateRangeDaily & two );

inline
int
compare( const DateRangeDaily & one, const DateRangeDaily & two )
{
  return( one.compare( two ) );
}

inline
std::ostream &
operator << ( std::ostream & dest, const DateRangeDaily & obj )
{
  return( obj.toStream( dest ) );
}

}; // namespace clue

#endif // ! def _clue_DateRangeDaily_hpp_

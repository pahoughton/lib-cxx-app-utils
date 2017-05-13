#ifndef _clue_DateRange_hpp_
#define _clue_DateRange_hpp_
/* 1994-02-20 (cc) Paul Houghton <paul4hough@gmail.com>

   Used in comparing two DateRanges. A DateRange has a start
   (date/time) plus a duration(end date/time)
*/

#include <clue/DateTime.hpp>

namespace clue {

class DateRange : public DateTime
{
public:

  inline DateRange( time_t startTime, time_t durSec );
  inline DateRange( const DateTime & startTime, time_t durSec );
  inline DateRange( const DateTime & startTime, const DateTime & stopTime );

  virtual time_t	dur( void ) const;
  virtual DateRange &   dur( time_t newDur );

  virtual bool	    isIn( const DateTime & dateTwo ) const;
  virtual time_t    secIn( const DateRange & dateTwo ) const;
  virtual time_t    startsIn( const DateRange & dateTwo ) const;

  virtual int	    compare( const DateTime & two ) const;
  virtual int	    compare( const DateRange & two ) const;

  inline bool	    operator == ( const DateRange & two ) const;
  inline bool	    operator == ( const DateTime & two ) const;
  inline bool	    operator <  ( const DateRange & two ) const;
  inline bool	    operator <  ( const DateTime & two ) const;

  inline bool		operator != ( const DateRange & rhs ) const;
  inline bool		operator >  ( const DateRange & rhs ) const;
  inline bool		operator <= ( const DateRange & rhs ) const;
  inline bool		operator >= ( const DateRange & rhs ) const;

  // libStlUtils Common Class Methods

  virtual size_t    	getBinSize( void ) const;

  virtual std::ostream & 	write( std::ostream & dest ) const;
  virtual std::istream & 	read( std::istream & src );

  virtual std::ostream & 	toStream( std::ostream & dest = std::cout ) const;

  friend inline std::ostream & operator << ( std::ostream &	    dest,
					const DateRange &   obj );

  virtual bool		    good( void ) const;
  virtual const char *	    error( void ) const;
  virtual std::ostream &    dumpInfo( std::ostream &	dest = std::cerr,
				      const char *	prefix = "    " ) const;

protected:

  time_t     m_dur;

private:

};


inline
DateRange::DateRange( time_t startTime, time_t durSec )
  : DateTime( startTime ),
    m_dur( durSec )
{
}

inline
DateRange::DateRange( const DateTime & startTime, time_t durSec )
  : DateTime( startTime ),
    m_dur( durSec )
{
}

inline
DateRange::DateRange( const DateTime & startTime, const DateTime & stopTime )
  : DateTime( startTime ),
    m_dur( stopTime.timet() - startTime.timet() )
{
}

inline
bool
DateRange::operator == ( const DateRange & two ) const
{
  return( compare( two ) == 0 );
}

inline
bool
DateRange::operator == ( const DateTime & two ) const
{
  return( DateTime::compare( two ) == 0 );
}

inline
bool
DateRange::operator <  ( const DateRange & two ) const
{
  return( compare( two ) < 0 );
}

inline
bool
DateRange::operator <  ( const DateTime & two ) const
{
  return( DateTime::compare( two ) < 0 );
}


inline
bool
DateRange::operator != ( const DateRange & rhs ) const
{
  return( ! (*this == rhs) );
}

inline
bool
DateRange::operator > ( const DateRange & rhs ) const
{
  return( rhs < *this );
}

inline
bool
DateRange::operator <= ( const DateRange & rhs ) const
{
  return( ! (rhs < *this) );
}

inline
bool
DateRange::operator >= ( const DateRange & rhs ) const
{
  return( ! (*this < rhs) );
}

inline
std::ostream &
operator << ( std::ostream & dest, const DateRange & obj )
{
  return( obj.toStream( dest ) );
}

inline
int
compare( const DateRange & one, const DateRange & two )
{
  return( one.compare( two ) );
}

}; // namespace clue

/*
  	DateRange( time_t startTime, time_t durSec );
  	    Set the value of startTime and duration(durSec).

  	DateRange( const DateTime & startTime, time_t durSec );

  	DateRange( const DateTime & startTime, const DateTime & stopTime );

  	virtual	time_t
  	getDur( void ) const;

  	virtual time_t
  	setDur( time_t newDur );

  	virtual time_t
  	getSecOfDay( void ) const;

  	virtual time_t
  	secIn( const DateRange & dateTwo ) const;
  	    returns the number of seconds that DateRange (two) is within
  	    DateRange (one).

  	virtual time_t
  	startsIn( const DateRange & dateTwo ) const;
  	    return the number of seconds from the start of DateRange (two)
  	    that is within DateRange (one). If the start of DateRange (two)
          is before the start of DateRange (one) a zero(0) is returned.

  	size_t
  	getStreamSize( void ) const;

  	std::ostream &
  	write( std::ostream & dest ) const;

  	std::istream &
  	read( std::istream & src );

  	virtual int
  	compare( const DateRange & two ) const;

  	bool
  	operator == ( const DateRange & two ) const;

  	bool
  	operator <  ( const DateRange & two ) const;

  	virtual bool
  	good( void ) const;
  	    return true if no detected errors exist. Only setValid will
  	    detect an invalid date/time value.

  	virtual const char *
  	error( void ) const;
  	    return a string describing the current error state.

  	virtual const char *
  	getClassName( void ) const;
  	    return the name of this class.

  	virtual std::ostream &
  	toStream( std::ostream & dest = std::cout ) const;
  	    send a formated string of the current date/time to 'dest'
  	    The format is '02/03/95 15:13:03'.

  	virtual std::ostream &
  	dumpInfo( std::ostream & dest ) const;
*/
#endif // ! def _clue_DateRange_hpp_

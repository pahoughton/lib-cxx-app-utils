// 1994-02-20 (cc) Paul Houghton <paul4hough@gmail.com>


#include "DateRange.hpp"
#include "Clue.hpp"
#include "Str.hpp"
#include "DateTimeUtils.hpp"

#include <iomanip>

namespace clue {

time_t
DateRange::dur( void ) const
{
  return( m_dur );
}

DateRange &
DateRange::dur( time_t val )
{
  m_dur = val;
  return( *this );
}

bool
DateRange::isIn( const DateTime & dateTwo ) const
{
  return( timet() <= dateTwo.timet()
	  && dateTwo.timet() <= (timet() + dur() ) );
}

time_t
DateRange::secIn( const DateRange & dateTwo ) const
{
  time_t   secs = 0;

  return( UnionOfDur( timet(), dur(),
		      dateTwo.timet(), dateTwo.dur() ) );

  return( secs );
}


time_t
DateRange::startsIn( const DateRange & dateTwo ) const
{
  time_t  secs = 0;

  if( dateTwo.timet() >= timet() &&
      dateTwo.timet() <= (timet() + dur() ) )
    {
      secs = secIn( dateTwo );
    }
  return( secs );
}


int
DateRange::compare( const DateRange & two ) const
{
  int diff = DateTime::compare( two );
  if( diff )
    return( diff );
  else
    return( clue::compare( dur(), two.dur() ) );
}

int
DateRange::compare( const DateTime & two ) const
{
  int diff = DateTime::compare( two );
  if( diff )
    return( diff );
  else
    return( 1 );
}

size_t
DateRange::getBinSize( void ) const
{
  return( DateTime::getBinSize() + sizeof( m_dur ) );
}


std::ostream &
DateRange::write( std::ostream & dest ) const
{
  DateTime::write( dest );
  dest.write( (const char *)&m_dur, sizeof( m_dur ) );
  return( dest );
}

std::istream &
DateRange::read( std::istream & src )
{
  DateTime::read( src );

  time_t    rDur;
  src.read( (char *)&rDur, sizeof( rDur ) );
  dur( rDur );
  return( src );
}

std::ostream &
DateRange::toStream( std::ostream & dest ) const
{

  dest << "Start: "
    ;

  DateTime::toStream( dest );

  dest << " Dur: "
       << std::setfill('0')
       << std::setw(2) << HoursInTimeT( dur() ) << ':'
       << std::setw(2) << MinInTimeT( dur() ) << ':'
       << std::setw(2) << SecInTimeT( dur() )
       << std::setfill(' ')
       ;

  return( dest );
}

bool
DateRange::good( void ) const
{
  return( DateTime::good() && dur() > 0 );
}

const char *
DateRange::error( void ) const
{
  static Str errStr;
  errStr.reset();

  errStr << "DateRange:";

  if( good() )
    {
      errStr << " Ok";
    }
  else
    {
      if( ! (DateTime::good() ) )
	{
	  errStr << " 0 Start DateTime";
	}
      if( ! (dur() > 0) )
	{
	  errStr << " Stop time <= StartTime";
	}
    }
  return( errStr.cstr() );
}

std::ostream &
DateRange::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

  if( ! DateRange::good() )
    dest << prefix << "Error: " << DateRange::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  dest << prefix << "range:   ";
  DateRange::toStream( dest );
  dest << '\n';

  Str pre;
  pre << prefix << "DateTime::";

  DateTime::dumpInfo( dest, pre );

  dest << prefix << "dur:     " << dur() << '\n';
  dest << '\n';

  return( dest  );
}

}; // namespace clue

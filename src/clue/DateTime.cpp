// 1994-02-09 (cc) Paul Houghton <paul4hough@gmail.com>

#include "DateTime.hpp"
#include "Str.hpp"
#include <cstdio>

namespace clue {


DateTime::~DateTime( void )
{
}

DateTime &
DateTime::year( int32_t yval )
{
  short oyr = year() - 1900;

  short leapCount = ((oyr - 70) + 2) / 4;
  int   oldIsLeap = IsLeapYear( oyr ) ? -1 : 0;
  if( oldIsLeap ) {
    leapCount--;
  }

  m_seconds -= ((oyr - 70) * SecPerYear ) + (leapCount * SecPerDay );

  // now add the new year

  if( yval > 1900 ) yval -= 1900;
  if( yval < 50 )   yval += 100;

  leapCount = ((yval - 70) + 2) / 4;

  int newIsLeap = IsLeapYear( yval ) ? 1 : 0;
  if( newIsLeap ) {
    leapCount--;
  }

  m_seconds += ((yval - 70) * SecPerYear ) + (leapCount * SecPerDay );

  if( oldIsLeap ) {
    if( ! newIsLeap && month() > 2 ) {
      m_seconds -= SecPerDay;
    }
  } else {
    if( newIsLeap && month() > 2 ) {
      m_seconds += SecPerDay;
    }
  }
  if( m_tm.tm_gmtoff ) {
    memcpy( &m_tm, localtime( &m_seconds ), sizeof( m_tm ) );
  } else {
    memcpy( &m_tm, gmtime( &m_seconds ), sizeof( m_tm ) );
  }
  return( *this );
}

DateTime &
DateTime::month( uint16_t mval )
{
  m_seconds -= MonthDayOfYear[ month() - 1 ] * SecPerDay;

  if( IsLeapYear( year() ) && month() > 2 )
    m_seconds -= SecPerDay;

  m_seconds += MonthDayOfYear[ mval - 1 ] * SecPerDay;

  if( IsLeapYear( year() ) && mval > 2 )
    m_seconds += SecPerDay;

  if( m_tm.tm_gmtoff ) {
    memcpy( &m_tm, localtime( &m_seconds ), sizeof( m_tm ) );
  } else {
    memcpy( &m_tm, gmtime( &m_seconds ), sizeof( m_tm ) );
  }

  return( *this );
}

int
DateTime::compare( const DateTime & two ) const
{
  return( (*this < two ) ? -1 :
	  (*this == two ) ? 0 : 1 );
}

std::ostream &
DateTime::toStream( std::ostream & dest ) const
{
  dest << str();

  return( dest );
}

bool
DateTime::good( void ) const
{
  return( timet() != 0 );
}

size_t
DateTime::getBinSize( void ) const
{
  return( sizeof( m_seconds ) );
}

std::ostream &
DateTime::write( std::ostream & dest ) const
{
  dest.write( (char *)&m_seconds, sizeof( m_seconds ) );
  return( dest );
}

std::istream &
DateTime::read( std::istream & src )
{
  if( ! src.read( (char *)&m_seconds, sizeof( m_seconds ) ).good() ) {
    m_seconds = 0;
    memset( &m_tm, 0, sizeof( m_tm ));
  } else {
    memcpy( &m_tm, gmtime( &m_seconds ), sizeof( m_tm ) );
  }
  return( src );
}

std::ostream &
DateTime::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

  if( ! DateTime::good() )
    dest << prefix << "Error: seconds not set\n";
  else
    dest << prefix << "Good!" << '\n';

  dest << prefix << "string: " << *this << '\n'
       << prefix << " timet: " << timet() << '\n'
       << prefix << "  year: " << m_tm.tm_year << '\n'
       << prefix << "   mon: " << m_tm.tm_mon << '\n'
       << prefix << "  mday: " << m_tm.tm_mday << '\n'
       << prefix << "  hour: " << m_tm.tm_hour << '\n'
       << prefix << "   min: " << m_tm.tm_min << '\n'
       << prefix << "   sec: " << m_tm.tm_sec << '\n'
       << prefix << "  wday: " << m_tm.tm_wday << '\n'
       << prefix << "  yday: " << m_tm.tm_yday << '\n'
       << prefix << " isdst: " << m_tm.tm_isdst << '\n'
       << prefix << "gmtoff: " << m_tm.tm_gmtoff << '\n'
       << prefix << "  zone: " <<( m_tm.tm_gmtoff ? m_tm.tm_zone : "" )<< '\n'
      ;

  return( dest  );
}


}; // namespace clue

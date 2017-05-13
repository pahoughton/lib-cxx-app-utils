// 2005-09-09 (cc) <paul4hough@gmail.com>

#include "DateTimeUtils.hpp"
#include "DateTime.hpp"

namespace clue {

bool
IsTimetDst( time_t val )
{
  struct tm t;
  gmtime_r( &val, &t );

  bool isDst( false );

  if( t.tm_mon > 2 && t.tm_mon < 10 ) {
    // april through october
    if( t.tm_mon == 3 ) {
      if( t.tm_mday < 8 ) {
	if( t.tm_wday == 0 ) {
	  if( t.tm_hour > 1 ) {
	    isDst = true;
	  }
	} else if( t.tm_mday > t.tm_wday ) {
	  isDst = true;
	}
      } else {
	isDst = true;
      }
    } else if( t.tm_mon == 9 ) {
      int lastSun;
      {
	int mday( t.tm_mday );
	int wday( t.tm_wday );

	lastSun = 31 - ((7+3-((mday + 7 - wday) % 7)) % 7);
      }
      if( t.tm_mday < lastSun ) {
	isDst = true;
      } else if( t.tm_mday == lastSun && t.tm_hour < 2 ) {
	isDst = true;
      }
    } else {
      isDst = true;
    }
  }
  return( isDst );
}
}; // namespace clue

/*
  #  (a) Duration of period; State exemption

  During the period commencing at 2 o'clock antemeridian on the first Sunday of April of each year and ending at 2 o'clock antemeridian on the last Sunday of October of each year, the standard time of each zone established by sections 261 to 264 of this title, as modified by section 265 of this title, shall be advanced one hour and such time as so advanced shall for the purposes of such sections 261 to 264, as so modified, be the standard time of such zone during such period; however, (1) any State that lies entirely within one time zone may by law exempt itself from the provisions of this subsection providing for the advancement of time, but only if that law provides that the entire State (including all political subdivisions thereof) shall observe the standard time otherwise applicable during that period, and (2) any State with parts thereof in more than one time zone may by law exempt either the entire State as provided in (1) or may exempt the entire area of the State lying within any time zone.
*/

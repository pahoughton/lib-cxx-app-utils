// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/DateTime.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <vector>
#include <set>
#include <functional>
#include <cstring>
#include <cstdio>

static valid::verify verify("clue::DateTime01");
using namespace clue;


bool
v_DateTime01( void )
{

  {
    // DateTime( void )
    // timeT( void ) const

    time_t	gtime = time(0);

    const DateTime dt;

    time_t	dtime = dt.timet();

    struct tm ltm;

    memcpy( &ltm, localtime( &gtime ), sizeof( ltm ) );

    TEST( gtime == dtime || (gtime + 1) == dtime );
    TEST( dt.month()  == ltm.tm_mon + 1 );
    TEST( dt.mday() == ltm.tm_mday );
    TEST( dt.yearOfCentury() == (ltm.tm_year % 100));
    TEST( dt.hour() == ltm.tm_hour );
    TEST( dt.minute()  == ltm.tm_min );
    // might be off by 1 second max
    TEST( dt.second()  == ltm.tm_sec ||
	  dt.second()  == (ltm.tm_sec + 1) );

  }

  {
    // DateTime( time_t )
    // DateTime( time_t, bool )
    // str( void ) const

    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    DateTime dtOneArg( when );
    DateTime dtGmt( when, true );
    DateTime dtLocal( when, false );

    struct tm check = *gmtime( &when );

    char checkStr[50];

    sprintf( checkStr, "%02d/%02d/%02d %02d:%02d:%02d",
	     check.tm_mon + 1,
	     check.tm_mday,
	     check.tm_year,
	     check.tm_hour,
	     check.tm_min,
	     check.tm_sec );


    TEST( dtGmt.str("%m/%d/%y %H:%M:%S") == checkStr );
    TEST( dtGmt == dtOneArg );

    check = *localtime( &when );

    sprintf( checkStr, "%02d/%02d/%02d %02d:%02d:%02d",
	     check.tm_mon + 1,
	     check.tm_mday,
	     check.tm_year,
	     check.tm_hour,
	     check.tm_min,
	     check.tm_sec );

    TEST( dtLocal.str("%m/%d/%y %H:%M:%S") == checkStr );

  }

  {
    // DateTime( int, int, int, int, int, int )
    // yearOfCentury( void )
    // month( void )
    // mday( void )
    // hour( void )
    // minute( void )
    // second( void )
    // str( void )

    int	    year = 95;
    int     month = 2;
    int     day = 5;
    int	    hour = 18;
    int	    min = 15;
    int	    sec = 30;

    DateTime	dt( year, month, day, hour, min, sec );

    TEST( dt.yearOfCentury() == year );
    TEST( dt.month() == month );
    TEST( dt.mday() == day );
    TEST( dt.hour() == hour );
    TEST( dt.minute() == min );
    TEST( dt.second() == sec );

    char check[50];
    sprintf( check, "%02d/%02d/%02d %02d:%02d:%02d",
	     month, day, year, hour, min, sec );

    TEST( dt.str("%m/%d/%y %H:%M:%S") == check );

  }

  {
    // DateTime( struct tm )
    // yearOfCentury( void ) const

    int	    year = 92;
    int     month = 3;
    int     day = 1;
    int	    hour = 18;
    int	    min = 15;
    int	    sec = 30;

    struct tm tm;

    tm.tm_year = year;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = min;
    tm.tm_sec = sec;

    const DateTime	dt( tm );

    TEST( dt.yearOfCentury() == year );
    TEST( dt.month() == month );
    TEST( dt.mday() == day );
    TEST( dt.hour() == hour );
    TEST( dt.minute() == min );
    TEST( dt.second() == sec );
  }

  {
    // DateTime( const char * )

    const char * dateString = "02/29/92 05:45:50";

    DateTime dt( dateString, "%m/%d/%y %H:%M:%S" );

    TEST( dt.str("%m/%d/%y %H:%M:%S") ==  dateString );
  }

  {
    // verify support for stl vector<> & set<>

    std::vector< DateTime > tV;
    std::set< DateTime, std::less< DateTime > >	tS;

  }

  return( verify.is_valid() );
}

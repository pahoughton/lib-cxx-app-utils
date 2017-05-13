// 1996-10-29 (cc) <paul4hough@gmail.com>

#include <clue/DateTime.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::DateTime03");
using namespace clue;

bool
v_DateTime03( void )
{
  {
    // set( const char * )
    // set( const char *, const char * )

    const char * dateString = "3/1/92 3:30:00";

    DateTime	when( dateString );
    DateTime 	dt( "6/28/95 18:30" );

    dt.set( dateString );

    TEST( dt.timet() == when.timet() );
    TEST( dt.tzOffset() == 0 );
    TEST( ! dt.isLocal() );
    TEST( ! dt.isDST() );

    TEST( dt.timet() == 699420600 );
    TEST( dt.secOfDay() == 12600 );
    TEST( dt.hour() == 3 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 0 );
    TEST( dt.dayOfYear() == 61 );
    TEST( dt.mday() == 1 );
    TEST( dt.month() == 3 );
    TEST( dt.yearOfCentury() == 92 );
    TEST( dt.year() == 1992 );

    dt.set( "01-Mar-92 03:30:00", "%d-%b-%y %H:%M:%S" );

    TEST( dt.timet() == 699420600 );
    TEST( dt.secOfDay() == 12600 );
    TEST( dt.hour() == 3 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 0 );

    TEST( dt.dayOfYear() == 61 );
    TEST( dt.mday() == 1 );
    TEST( dt.month() == 3 );
    TEST( dt.yearOfCentury() == 92 );
    TEST( dt.year() == 1992 );

#if defined( FIXME )
    dt.set( "06/26/1776", "%m/%d/%Y" );
    TEST( dt.timet() == MinTimeT );

    dt.set( "06/26/2076", "%m/%d/%Y" );

    TESTR( dt.string(), dt.timet() == MaxTimeT );
#endif
  }

  {
    // set( int, int, int )
    // set( int, int, int, int, int, int )

    int	    year = 1992;
    int     month = 3;
    int     day = 1;
    int	    hour = 18;
    int	    min = 15;
    int	    sec = 30;

    DateTime 	dt( "6/28/95 18:30" );

    dt.set( year, month, day );

    TEST( dt.tzOffset() == 0 );
    TEST( ! dt.isLocal() );
    TEST( ! dt.isDST() );

    TEST( dt.year() == year );
    TEST( dt.month() == month );
    TEST( dt.mday() == day );
    TEST( dt.hour() == 0 );
    TEST( dt.minute() == 0 );
    TEST( dt.second() == 0 );

    year = 10;

    dt.set( year, month, day, hour, min, sec );

    TEST( dt.year() == 2010 );
    TEST( dt.month() == month );
    TEST( dt.mday() == day );
    TEST( dt.hour() == hour );
    TEST( dt.minute() == min );
    TEST( dt.second() == sec );

    year = 1920;
    month = 1;
    day = 1;
    hour = 0;
    min = 0;
    sec = 0;

    dt.set( year, month, day, hour, min, sec );

    TEST( dt.year() == year );
    TEST( dt.month() == month );
    TEST( dt.mday() == day );
    TEST( dt.hour() == hour );
    TEST( dt.minute() == min );
    TEST( dt.second() == sec );


    year = 2000;

    dt.set( year, month, day, hour, min, sec );

    TEST( dt.year() == year );
    TEST( dt.month() == month );
    TEST( dt.mday() == day );
    TEST( dt.hour() == hour );
    TEST( dt.minute() == min );
    TEST( dt.second() == sec );

    year = 2030;

    dt.set( year, month, day, hour, min, sec );

    TEST( dt.year() == year );
    TEST( dt.month() == month );
    TEST( dt.mday() == day );
    TEST( dt.hour() == hour );
    TEST( dt.minute() == min );
    TEST( dt.second() == sec );

#if defined( FIXME )
    year = MinYear - 1;

    dt.set( year, month, day, hour, min, sec );

    TEST( dt.timet() == MinTimeT );

    year = MaxYear + 1;

    dt.set( year, month, day, hour, min, sec );

    TEST( dt.timet() == MaxTimeT );
#endif
  }

  {
    // set( const struct tm & )

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

    DateTime 	dt( "6/28/95 18:30" );

    dt.set( tm );

    TEST( dt.tzOffset() == 0 );
    TEST( ! dt.isLocal() );
    TEST( ! dt.isDST() );

    TEST( dt.year() == 1900 + year );
    TEST( dt.month() == month );
    TEST( dt.mday() == day );
    TEST( dt.hour() == hour );
    TEST( dt.minute() == min );
    TEST( dt.second() == sec );

  }

  {
    // setValid( int, int, int )
    // setValid( int, int, int, int, int, int )

    int	    year = 1992;
    int     month = 3;
    int     day = 1;
    int	    hour = 18;
    int	    min = 15;
    int	    sec = 30;

    DateTime 	dt( "6/28/95 18:30" );

    dt.setValid( year, month, day );

    TEST( dt.tzOffset() == 0 );
    TEST( ! dt.isLocal() );
    TEST( ! dt.isDST() );

    TEST( dt.year() == year );
    TEST( dt.month() == month );
    TEST( dt.mday() == day );
    TEST( dt.hour() == 0 );
    TEST( dt.minute() == 0 );
    TEST( dt.second() == 0 );

    dt.set( year, month, day, hour, min, sec );

    TEST( dt.year() == year );
    TEST( dt.month() == month );
    TEST( dt.mday() == day );
    TEST( dt.hour() == hour );
    TEST( dt.minute() == min );
    TEST( dt.second() == sec );

    dt.setValid( year, month, day );
    TEST( dt.good() );

#if defined( FIXME )
    dt.setValid( -1, month, day);
    TEST( ! dt.good() );

    dt.setValid( 2055, month, day );
    TEST( ! dt.good() );
#endif
    dt.setValid( 1969, month, day );
    TEST( dt.good() );

    dt.setValid( year, 0, day );
    TEST( ! dt.good() );

    dt.setValid( year, 13, day );
    TEST( ! dt.good() );

    dt.setValid( year, -1, day );
    TEST( ! dt.good() );

    dt.setValid( year, month, -1 );
    TEST( ! dt.good() );

    dt.setValid( year, month, 0 );
    TEST( ! dt.good() );

    dt.setValid( 0, 0, 0 );
    TEST( ! dt.good() );

    dt.setValid( 92, 1, 0 );
    TEST( ! dt.good() );

    dt.setValid( 92, 1, 31 );
    TEST( dt.good() );

    dt.setValid( 92, 1, 32 );
    TEST( ! dt.good() );

    dt.setValid( 92, 2, 28 );
    TEST( dt.good() );

    dt.setValid( 92, 2, 29 );
    TEST( dt.good() );

    dt.setValid( 93, 2, 29 );
    TEST( ! dt.good() );

    dt.setValid( 92, 3, 32 );
    TEST( ! dt.good() );

    dt.setValid( 92, 3, 31 );
    TEST( dt.good() );

    dt.setValid( 92, 4, 31 );
    TEST( ! dt.good() );

    dt.setValid( 92, 4, 30 );
    TEST( dt.good() );

    dt.setValid( 92, 5, 32 );
    TEST( ! dt.good() );

    dt.setValid( 92, 5, 31 );
    TEST( dt.good() );

    dt.setValid( 92, 6, 31 );
    TEST( ! dt.good() );

    dt.setValid( 92, 6, 30 );
    TEST( dt.good() );

    dt.setValid( 92, 7, 32 );
    TEST( ! dt.good() );

    dt.setValid( 92, 7, 31 );
    TEST( dt.good() );

    dt.setValid( 92, 8, 32 );
    TEST( ! dt.good() );

    dt.setValid( 92, 8, 31 );
    TEST( dt.good() );

    dt.setValid( 92, 9, 31 );
    TEST( ! dt.good() );

    dt.setValid( 92, 9, 30 );
    TEST( dt.good() );

    dt.setValid( 92, 10, 32 );
    TEST( ! dt.good() );

    dt.setValid( 92, 10, 31 );
    TEST( dt.good() );

    dt.setValid( 92, 11, 31 );
    TEST( ! dt.good() );

    dt.setValid( 92, 11, 30 );
    TEST( dt.good() );

    dt.setValid( 92, 12, 32 );
    TEST( ! dt.good() );

    dt.setValid( 92, 12, 31 );
    TEST( dt.good() );

    dt.setValid( 92, 1, 1, -1 );
    TEST( ! dt.good() );

    dt.setValid( 92, 1, 1, 24 );
    TEST( ! dt.good() );

    dt.setValid( 92, 1, 1, 0 );
    TEST( dt.good() );

    dt.setValid( 92, 1, 1, 0, -1 );
    TEST( ! dt.good() );

    dt.setValid( 92, 1, 1, 0, 60 );
    TEST( ! dt.good() );

    dt.setValid( 92, 1, 1, 0, 0 );
    TEST( dt.good() );

    dt.setValid( 92, 1, 1, 0, 0, -1 );
    TEST( ! dt.good() );

    dt.setValid( 92, 1, 1, 0, 0, 60 );
    TEST( ! dt.good() );

    dt.setValid( 92, 1, 1, 0, 0, 0 );
    TEST( dt.good() );

  }

  {
    // setValid( const char * )
    // setValid( const char *, const char * )

    DateTime 	dt( "6/28/95 18:30" );

    dt.setValid( "2/1/95 06:30:15" );

    TEST( dt.tzOffset() == 0 );
    TEST( ! dt.isLocal() );
    TEST( ! dt.isDST() );

    TEST( dt.timet() );
    TEST( dt.year() == 1995 );
    TEST( dt.month() == 2 );
    TEST( dt.mday() == 1 );
    TEST( dt.hour() == 6 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 15 );
    TEST( dt.good() );

    dt.setValid( "95 01 01 15 30 15", "%y %m %d %H %M %S" );

    TEST( dt.timet() );
    TEST( dt.year() == 1995 );
    TEST( dt.month() == 1 );
    TEST( dt.mday() == 1 );
    TEST( dt.hour() == 15 );
    TEST( dt.minute() == 30 );
    TEST( dt.second() == 15 );
    TEST( dt.good() );

    dt.setValid( "13/1/95", "%m/%d/%y" );
    TEST( ! dt.good() );

    dt.setValid( "1/1/95", "%m/%d/%y" );
    TEST( dt.good() );

    dt.setValid( "2/29/92" );
    TEST( ! dt.good() );

    dt.setValid( "2/29/95" );
    TEST( ! dt.good() );

    dt.setValid( "92 2 29", "%y %m %d" );
    TEST( dt.good() );

    dt.setValid( "93 2 32", "%y %m %d" );
    TEST( ! dt.good() );

    dt.setValid( "93 2 30", "%y %m %d" );
    TEST( ! dt.good() );

    dt.setValid( "1/1/65" );
    TEST( ! dt.good() );

    dt.setValid( "1/1/95 24:0:0" );
    TEST( ! dt.good() );

    dt.setValid( "1/1/95 23:60:0" );
    TEST( ! dt.good() );

    dt.setValid( "1/1/95 23:59:60" );
    TEST( ! dt.good() );

    dt.setValid( "1/1/95 23:59:59" );
    TEST( dt.good() );

  }

  {
    // setVaidYYMMDD( const char * yymmdd );

    DateTime dt;

    dt.setValidYYMMDD( "970204" );

    TEST( dt.good() );

    // FIXME - need more extensive testing.

    // cout << "\n" <<  dt << " - 970204 '" << dt.yYYYMMDD() << "'." <<  endl;
  }
  return( verify.is_valid() );
}

#if !defined( CLUE_SHORT_FN )
#include <TestConfig.hh>
#include <LibTest.hh>
#include <DateTime.hh>
#include <vector>
#include <set>
#include <functional>
#include <cstring>
#include <cstdio>
#else
#include <TestConfig.hh>
#include <LibTest.hh>
#include <DateTime.hh>
#include <vector>
#include <set>
#include <functional>
#include <cstring>
#include <cstdio>
#endif

bool
tDateTime01( LibTest & tester )
{
  
  {
    // DateTime( void )
    // getTimeT( void ) const
    
    time_t	gtime = time(0);

    const DateTime dt;

    time_t	dtime = dt.getTimeT();
    
    struct tm dtm;
    struct tm ltm;

    memcpy( &dtm, gmttime( &dtime ), sizeof( dtm ) );
    memcpy( &ltm, localtime( &gtime ), sizeof( ltm ) );

    TEST( dtm.tm_mon  == ltm.tm_mon );
    TEST( dtm.tm_mday == ltm.tm_mday );
    TEST( dtm.tm_year == ltm.tm_year );
    TEST( dtm.tm_hour == ltm.tm_hour );
    TEST( dtm.tm_min  == ltm.tm_min );
    // might be off by 1 second max
    TEST( dtm.tm_sec  == ltm.tm_sec || dtm.tm_sec  == (ltm.tm_sec + 1) );

  }

  {
    // DateTime( time_t )
    // DateTime( time_t, bool )
    // getString( void ) const
    
    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    DateTime dtOneArg( when );
    DateTime dtGmt( when, false );
    DateTime dtLocal( when, true );

    struct tm * check = gmtime( &when );

    char checkStr[50];

    sprintf( checkStr, "%02d/%02d/%02d %02d:%02d:%02d",
	     check->tm_mon + 1,
	     check->tm_mday,
	     check->tm_year,
	     check->tm_hour,
	     check->tm_min,
	     check->tm_sec );


    TEST( ! strcmp( checkStr, dtGmt.getString() ) );
    TEST( dtGmt == dtOneArg );
      
    check = localtime( &when );
    
    sprintf( checkStr, "%02d/%02d/%02d %02d:%02d:%02d",
	     check->tm_mon + 1,
	     check->tm_mday,
	     check->tm_year,
	     check->tm_hour,
	     check->tm_min,
	     check->tm_sec );
    
    TEST( ! strcmp( checkStr, dtLocal.getString() ) );
  }
  
  {
    // DateTime( time_t, time_t )
    // getYear( void ) const
    // getMonth( void ) const
    // getDayOfMonth( void ) const
    // getHour( void ) const
    // getMinute( void ) const
    // getSecond( void ) const

    const char * dateStr = "2/1/95";
    
    struct tm   tmDate;
    memset( &tmDate, 0, sizeof( tmDate ) );
    
    strptime( (char *)dateStr, "%m/%d/%y", &tmDate );
    
    time_t datePart = DateInTimeT( mktime( &tmDate ) );
    time_t timePart = (5 * 60 * 60) + (45 * 60) + 50;
    
    const DateTime	dt(datePart, timePart);

    TEST( dt.getTimeT() == (datePart + timePart) );

    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 1 );
    TEST( dt.getHour() == 5 );
    TEST( dt.getMinute() == 45 );
    TEST( dt.getSecond() == 50 );
  }
	  
  {
    // DateTime( yymmdd, hhmmss )
    
    const char *    yymmdd = "950205junk";
    const char *    hhmmss = "150550junk";
    
    DateTime	dt( yymmdd, hhmmss );

    TEST( dt.getYear() == 1995 );
    TEST( dt.getMonth() == 2 );
    TEST( dt.getDayOfMonth() == 5 );
    TEST( dt.getHour() == 15 );
    TEST( dt.getMinute() == 5 );
    TEST( dt.getSecond() == 50 );
    
  }
  
  {
    // DateTime( int, int, int, int, int, int )
    // getYearOfCentury( void )
    // getMonth( void )
    // getDayOfMonth( void )
    // getHour( void )
    // getMinute( void )
    // getSecond( void )
    // getString( void )
    
    int	    year = 95;
    int     month = 2;
    int     day = 5;
    int	    hour = 18;
    int	    min = 15;
    int	    sec = 30;
      
    DateTime	dt( year, month, day, hour, min, sec );

    TEST( dt.getYearOfCentury() == year );
    TEST( dt.getMonth() == month );
    TEST( dt.getDayOfMonth() == day );
    TEST( dt.getHour() == hour );
    TEST( dt.getMinute() == min );
    TEST( dt.getSecond() == sec );

    char check[50];
    sprintf( check, "%02d/%02d/%02d %02d:%02d:%02d",
	     month, day, year, hour, min, sec );

    TEST( ! strcmp( check, dt.getString() ) );
    
  }

  {
    // DateTime( struct tm )
    // getYearOfCentury( void ) const
    
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

    TEST( dt.getYearOfCentury() == year );
    TEST( dt.getMonth() == month );
    TEST( dt.getDayOfMonth() == day );
    TEST( dt.getHour() == hour );
    TEST( dt.getMinute() == min );
    TEST( dt.getSecond() == sec );
  }

  {
    // DateTime( const char * )
    
    const char * dateString = "02/29/92 05:45:50";

    DateTime dt( dateString );

    TEST( ! strcmp( dateString, dt.getString() ) );
  }

  {
    // verify support for stl vector<> & set<>

    vector< DateTime > tV;
    set< DateTime, less< DateTime > >	tS;

  }
  
  return( true );
}

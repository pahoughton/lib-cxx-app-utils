#include <LibTest.hh>
#include <DateTime.hh>

// stl
#include <vector>
#include <set>
#include <functional>

#include <cstring>
#include <cstdio>

bool
tDateTime01( LibTest & test )
{
  
  {
    // DateTime( void )
    // getTimeT( void ) const
    // getString( void ) const
    
    const DateTime dt;

    test( dt.getTimeT() == 0 );

    test( ! strcmp( "01/01/70 00:00:00", dt.getString() ) );
  }

  {
    // DateTime( time_t )
    // DateTime( time_t, bool )
    
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


    test( ! strcmp( checkStr, dtGmt.getString() ) );
    test( dtGmt == dtOneArg );
      
    check = localtime( &when );
    
    sprintf( checkStr, "%02d/%02d/%02d %02d:%02d:%02d",
	     check->tm_mon + 1,
	     check->tm_mday,
	     check->tm_year,
	     check->tm_hour,
	     check->tm_min,
	     check->tm_sec );
    
    test( ! strcmp( checkStr, dtLocal.getString() ) );
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

    test( dt.getTimeT() == (datePart + timePart) );

    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 1 );
    test( dt.getHour() == 5 );
    test( dt.getMinute() == 45 );
    test( dt.getSecond() == 50 );
  }
	  
  {
    // DateTime( yymmdd, hhmmss )
    
    const char *    yymmdd = "950205junk";
    const char *    hhmmss = "150550junk";
    
    DateTime	dt( yymmdd, hhmmss );

    test( dt.getYear() == 1995 );
    test( dt.getMonth() == 2 );
    test( dt.getDayOfMonth() == 5 );
    test( dt.getHour() == 15 );
    test( dt.getMinute() == 5 );
    test( dt.getSecond() == 50 );
    
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

    test( dt.getYearOfCentury() == year );
    test( dt.getMonth() == month );
    test( dt.getDayOfMonth() == day );
    test( dt.getHour() == hour );
    test( dt.getMinute() == min );
    test( dt.getSecond() == sec );

    char check[50];
    sprintf( check, "%02d/%02d/%02d %02d:%02d:%02d",
	     month, day, year, hour, min, sec );

    test( ! strcmp( check, dt.getString() ) );
    
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

    test( dt.getYearOfCentury() == year );
    test( dt.getMonth() == month );
    test( dt.getDayOfMonth() == day );
    test( dt.getHour() == hour );
    test( dt.getMinute() == min );
    test( dt.getSecond() == sec );
  }

  {
    // DateTime( const char * )
    
    const char * dateString = "02/29/92 05:45:50";

    DateTime dt( dateString );

    test( ! strcmp( dateString, dt.getString() ) );
  }

  {
    // verify support for stl vector<> & set<>

    vector< DateTime > tV;
    set< DateTime, less< DateTime > >	tS;

  }
  
  return( true );
}
